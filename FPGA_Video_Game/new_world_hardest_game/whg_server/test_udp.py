import socket
import struct
import time
import random
import uuid
import argparse
import threading
import sys
import binascii  # For better packet debugging

class UdpTestClient:
    def __init__(self, server_host, server_port):
        self.server_host = server_host
        self.server_port = server_port
        self.server_addr = (server_host, server_port)
        self.player_id = str(uuid.uuid4())
        self.socket = None
        self.receive_thread = None
        self.running = False
        self.players_seen = []
        self.lock = threading.Lock()
        
    def start(self):
        try:
            # Create a UDP socket and bind it to receive responses
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            
            # Explicitly bind to 0.0.0.0 and a random port
            self.socket.bind(('0.0.0.0', 0))
            local_addr = self.socket.getsockname()
            print(f"Client bound to {local_addr}")
            
            self.socket.settimeout(0.5)  # Shorter timeout for faster response
            self.running = True
            
            # Start receive thread
            self.receive_thread = threading.Thread(target=self._receive_loop)
            self.receive_thread.daemon = True
            self.receive_thread.start()
            
            return True
        except Exception as e:
            print(f"Failed to start UDP client: {e}")
            return False
            
    def stop(self):
        self.running = False
        if self.socket:
            try:
                self.socket.close()
            except:
                pass
            self.socket = None
        
        if self.receive_thread and self.receive_thread.is_alive():
            self.receive_thread.join(timeout=1.0)
    
    def create_packet(self, tag="TEST_CLIENT", x=300, y=300, vel_x=0, vel_y=0, color=1):
        """Create a test packet in the same format as the Java client would send"""
        # Format the packet according to the protocol
        packet = bytearray()
        
        # Player ID (36 bytes for UUID)
        packet.extend(self.player_id.ljust(36).encode('utf-8'))
        
        # Combat tag (variable length with null terminator)
        tag_bytes = tag.encode('utf-8')
        packet.extend(tag_bytes)
        packet.append(0)  # Null terminator
        
        # Position and velocity (4 ints, 16 bytes)
        packet.extend(struct.pack('!iiii', x, y, vel_x, vel_y))
        
        # Color (1 byte: 1=red, 2=blue)
        packet.append(color)
        
        return packet
    
    def send_update(self, x, y, vel_x, vel_y, color=1, tag="TEST_CLIENT"):
        if not self.socket or not self.running:
            return False
            
        try:
            packet = self.create_packet(tag, x, y, vel_x, vel_y, color)
            bytes_sent = self.socket.sendto(packet, self.server_addr)
            print(f"Sent {bytes_sent} bytes to server")
            
            # IMPORTANT: Wait briefly for a direct response
            # This is critical for handling NAT/firewalls
            start_time = time.time()
            timeout_time = start_time + 1.0  # 1 second timeout
            
            while time.time() < timeout_time:
                try:
                    self.socket.settimeout(0.1)
                    data, addr = self.socket.recvfrom(1024)
                    print(f"Received direct response: {len(data)} bytes from {addr}")
                    
                    # Parse the packet
                    players = self._parse_packet(data)
                    if players:
                        print(f"Successfully parsed {len(players)} players!")
                        with self.lock:
                            self.players_seen = players
                    
                    # We got data, so we can stop waiting
                    break
                except socket.timeout:
                    # Try again until timeout_time
                    continue
            
            # Reset timeout to normal
            self.socket.settimeout(0.5)
            return True
        except Exception as e:
            print(f"Failed to send update: {e}")
            return False
    
    def _parse_packet(self, data):
        """Parse received packet and update players list"""
        try:
            offset = 0
            current_players = []
            
            # Skip the first 4 bytes if they look like a packet length
            if len(data) > 4 and data[0] == 0 and data[1] == 0:
                offset = 4
                print("Skipping 4-byte header")
            
            # Debug dump first 10 bytes
            print(f"Packet start: {binascii.hexlify(data[:min(20, len(data))])}")
            
            while offset < len(data):
                print(f"Parsing at offset {offset}/{len(data)}")
                
                # Read player ID
                player_id = data[offset:offset+36].decode('utf-8').strip()
                offset += 36
                
                # Read tag length and tag
                tag_len = data[offset]
                offset += 1
                tag = data[offset:offset+tag_len].decode('utf-8')
                offset += tag_len
                
                # Read position and velocity
                x, y, vel_x, vel_y = struct.unpack('!iiii', data[offset:offset+16])
                offset += 16
                
                # Read color
                color = "RED" if data[offset] == 1 else "BLUE"
                offset += 1
                
                print(f"Parsed player: {tag} ({player_id[:8]}...) at ({x},{y})")
                
                current_players.append({
                    "playerId": player_id,
                    "tag": tag,
                    "x": x,
                    "y": y,
                    "velocityX": vel_x,
                    "velocityY": vel_y,
                    "color": color
                })
            
            # Update the players list
            with self.lock:
                self.players_seen = current_players
                
            return current_players
                
        except Exception as e:
            print(f"Error parsing packet: {e} at offset {offset}/{len(data)}")
            # Dump packet contents for debugging
            print(f"Packet hex: {binascii.hexlify(data)}")
            return []
    
    def _receive_loop(self):
        """Background thread to receive UDP packets"""
        print("Receive thread started")
        while self.running:
            try:
                data, addr = self.socket.recvfrom(1024)
                print(f"Received {len(data)} bytes of data from {addr}")
                self._parse_packet(data)
            except socket.timeout:
                # This is normal - just retry
                pass
            except Exception as e:
                if self.running:  # Only log if we're still supposed to be running
                    print(f"Error in receive loop: {e}")
    
    def get_players(self):
        with self.lock:
            return self.players_seen.copy()


def test_udp_server(server_host, server_port):
    """Run automated tests against the UDP server"""
    print(f"=== Testing UDP server at {server_host}:{server_port} ===")
    
    # Create test client
    client = UdpTestClient(server_host, server_port)
    if not client.start():
        print("Failed to start UDP client, tests aborted.")
        return
    
    try:
        # Test 1: Basic connectivity
        print("\n--- Test 1: Basic connectivity ---")
        print(f"Client ID: {client.player_id}")
        success = client.send_update(300, 300, 0, 0, 1, "CONNECTIVITY_TEST")
        print(f"Send status: {'Success' if success else 'Failed'}")
        
        # Wait briefly for server response
        print("Waiting for server response...")
        time.sleep(2)
        
        # Check if we received any players
        players = client.get_players()
        print(f"Received {len(players)} players from server:")
        for i, player in enumerate(players):
            print(f"  {i+1}. {player['tag']} at ({player['x']},{player['y']}) vel:({player['velocityX']},{player['velocityY']}) Color:{player['color']}")
        
        # Test 2: Movement simulation
        print("\n--- Test 2: Movement simulation ---")
        positions = [
            (200, 200, 50, 0),    # Move right
            (300, 200, 0, 50),    # Move down
            (300, 300, -50, 0),   # Move left
            (200, 300, 0, -50),   # Move up
            (200, 200, 0, 0)      # Stop
        ]
        
        for i, (x, y, vel_x, vel_y) in enumerate(positions):
            print(f"Position {i+1}: ({x},{y}) vel:({vel_x},{vel_y})")
            client.send_update(x, y, vel_x, vel_y, 1, "MOVEMENT_TEST")
            time.sleep(0.5)  # Brief delay between updates
        
        # Check final state
        time.sleep(1)
        players = client.get_players()
        print(f"After movement, server reports {len(players)} players")
        
        # Test 3: Color change
        print("\n--- Test 3: Color change ---")
        client.send_update(250, 250, 0, 0, 2, "COLOR_TEST_BLUE")
        time.sleep(1)
        
        players = client.get_players()
        print(f"After color change, server reports {len(players)} players")
        
        # Test 4: Multiple clients (simulation)
        print("\n--- Test 4: Multiple client simulation ---")
        # Simulate another client by using a different tag
        client.send_update(400, 400, 0, 0, 1, "SIMULATED_CLIENT_1")
        time.sleep(0.5)
        
        # Our own update again
        client.send_update(250, 250, 0, 0, 2, "ORIGINAL_CLIENT")
        time.sleep(1)
        
        players = client.get_players()
        print(f"After multiple updates, server reports {len(players)} players")
        
        # Test 5: Interactive mode (optional)
        if interactive:
            print("\n--- Test 5: Interactive Mode ---")
            print("Enter commands: wasd=move, r/b=change color, q=quit")
            
            x, y = 300, 300
            vel_x, vel_y = 0, 0
            color = 1
            
            while True:
                cmd = input("> ").lower()
                if cmd == 'q':
                    break
                    
                # Update position based on command
                if 'w' in cmd:
                    y -= 20
                    vel_y = -50
                if 's' in cmd:
                    y += 20
                    vel_y = 50
                if 'a' in cmd:
                    x -= 20
                    vel_x = -50
                if 'd' in cmd:
                    x += 20
                    vel_x = 50
                    
                # Change color
                if 'r' in cmd:
                    color = 1  # Red
                if 'b' in cmd:
                    color = 2  # Blue
                    
                # Send update
                client.send_update(x, y, vel_x, vel_y, color, "INTERACTIVE")
                print(f"Sent update: pos=({x},{y}) vel=({vel_x},{vel_y}) color={color}")
                
                # Reset velocity after sending
                vel_x, vel_y = 0, 0
                
                # Show current players
                time.sleep(0.5)  # Wait briefly for response
                players = client.get_players()
                print(f"Server reports {len(players)} players:")
                for i, player in enumerate(players):
                    print(f"  {i+1}. {player['tag']} at ({player['x']},{player['y']})")
        
        print("\n--- All tests completed ---")
        
    except KeyboardInterrupt:
        print("\nTest interrupted by user.")
    except Exception as e:
        print(f"\nTest error: {e}")
    finally:
        client.stop()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Test UDP server for WHG")
    parser.add_argument("--host", default="localhost", 
                        help="UDP server host (default: localhost)")
    parser.add_argument("--port", type=int, default=8089,
                        help="UDP server port (default: 8089)")
    parser.add_argument("--interactive", action="store_true",
                        help="Enable interactive mode after tests")
    
    args = parser.parse_args()
    server_host = args.host
    server_port = args.port
    interactive = args.interactive
    
    test_udp_server(server_host, server_port)