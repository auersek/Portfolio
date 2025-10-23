import socket
import struct
import threading
import time
import logging
import random

# Configure logging
logging.basicConfig(
    level=logging.DEBUG,
    format='%(asctime)s [%(levelname)s] %(message)s',
    handlers=[
        logging.StreamHandler(),
        logging.FileHandler('hybrid_server.log')
    ]
)
logger = logging.getLogger(__name__)

UDP_HOST = '0.0.0.0'
POSITION_UPDATE_PORT = 8089
PLAYER_LIST_PORT = 8090
TIMEOUT = 5.0
players = {}
player_lock = threading.Lock()

position_update_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
position_update_socket.bind(('', POSITION_UPDATE_PORT))

player_list_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
player_list_socket.bind(('', PLAYER_LIST_PORT))

# ------------------------
# UDP SERVER FUNCTIONS
# ------------------------

def pack_players_data(exclude_id=None, combat_tag=None):
    """Create a binary packet with filtered player data
    
    Args:
        exclude_id: Player ID to exclude from response
        combat_tag: If provided, only include players with this combat tag
    """
    active_players = []
    
    with player_lock:
        # Get filtered active players
        for pid, pdata in players.items():
            if pid != exclude_id:
                logger.debug(f"Player {pid}: has tag '{pdata['combatTag']}', filter is '{combat_tag}'")
                # If combat_tag filter is provided, check that it matches
                if combat_tag is None or pdata['combatTag'] == combat_tag:
                    active_players.append(pdata)
    
    # Create binary packet - allocate more space to be safe
    # 4 bytes for player count + 8 bytes for timestamp + each player's data
    max_player_size = 100  # Increased from 50 to handle longer tags
    packet = bytearray(4 + 8 + len(active_players) * max_player_size)
    
    # Number of players (4 bytes)
    struct.pack_into('!I', packet, 0, len(active_players))
    
    # Get a more precise millisecond timestamp using time_ns() (Python 3.7+)
    try:
        # More precise method using nanoseconds divided by a million
        current_timestamp = time.time_ns() // 1_000_000  # Convert ns to ms
    except AttributeError:
        # Fallback for older Python versions
        import datetime
        current_timestamp = int(datetime.datetime.now().timestamp() * 1000)
    
    # Pack the precise timestamp (8 bytes)
    struct.pack_into('!Q', packet, 4, current_timestamp)
    
    # Log timestamp occasionally
    if random.random() < 0.001:  # Log ~0.1% of timestamps
        logger.debug(f"Precise timestamp: {current_timestamp} ms")
    
    # Start at offset 12 (after player count and timestamp)
    offset = 12
    
    for player in active_players:
        # Player ID (36 bytes)
        player_id_bytes = player['playerId'].encode('utf-8').ljust(36)
        packet[offset:offset+36] = player_id_bytes
        offset += 36
        
        # Combat tag with length prefix
        tag_bytes = player['combatTag'].encode('utf-8')
        tag_len = len(tag_bytes)
        
        # Ensure we have enough space for tag length + tag bytes
        if offset + 1 + tag_len >= len(packet):
            # Dynamically expand the packet if needed
            packet.extend(bytearray(max_player_size))
            
        # Write tag length
        packet[offset] = tag_len
        offset += 1
        
        # Write tag bytes
        packet[offset:offset+tag_len] = tag_bytes
        offset += tag_len
        
        # Ensure we have enough space for position and velocity (16 bytes)
        if offset + 16 >= len(packet):
            packet.extend(bytearray(max_player_size))
            
        # Position and velocity
        struct.pack_into('!iiii', packet, offset, 
                         player['x'], player['y'], 
                         player['velocityX'], player['velocityY'])
        offset += 16
        
        # Ensure we have enough space for color (1 byte)
        if offset + 1 >= len(packet):
            packet.extend(bytearray(max_player_size))
            
        # Color
        packet[offset] = 1 if player['color'] == 'red' else 2
        offset += 1
        last_updated_ms = int(player['timestamp'])
        struct.pack_into('!Q', packet, offset, last_updated_ms)
        offset += 8
    # Trim packet to actual size
    packet = packet[:offset]
    
    # logger.info(f"Sent UDP packet: timestamp={current_timestamp}, players={len(active_players)}")
    
    return packet, len(active_players)

def handle_udp_request(data, addr, sock):
    """Process incoming UDP request for player list"""
    try:
        # Smallest valid request is just a player ID (36 bytes)
        if len(data) < 36:
            logger.warning(f"UDP: Received invalid request from {addr}, too short")
            return
        
        # Extract player ID
        player_id = data[:36].decode('utf-8').strip()
        
        # Check if there's a combat tag filter
        combat_tag = None
        if len(data) > 36:  # Make sure we have at least one more byte for the tag length
            try:
                tag_len = data[36]
                logger.debug(f"UDP: Tag length byte = {tag_len}")
                
                # Make sure we have enough bytes for the tag
                if len(data) >= 37 + tag_len:
                    combat_tag = data[37:37+tag_len].decode('utf-8')
                    #logger.info(f"UDP: Filter request for combat tag: '{combat_tag}'")
            except Exception as e:
                logger.warning(f"UDP: Error parsing combat tag: {e}")
        
        # Update player's UDP address so we can send them updates
        with player_lock:
            if player_id in players:
                players[player_id]['addr'] = addr
                players[player_id]['timestamp'] = time.time()  # Update last seen time
                
                # Log player's current tag for debugging
                # logger.debug(f"UDP: Player {player_id} has tag '{players[player_id]['combatTag']}'")
        
        # IMPORTANT CHANGE: Don't exclude self when filtering by combat tag
        exclude_id = player_id if combat_tag is None else None
        
        # Create and send response with filtered players
        packet, count = pack_players_data(exclude_id=exclude_id, combat_tag=combat_tag)
        
        # Log the filter being applied
        #filter_info = f" with tag filter '{combat_tag}'" if combat_tag else " with no tag filter"
        #exclude_info = "" if exclude_id is None else f" (excluding self)"
        # logger.info(f"UDP: Sending response to {player_id[:8]}...{filter_info}{exclude_info}, {count} players matched")
        
        if packet:
            try:
                sock.sendto(packet, addr)
            except Exception as e:
                logger.error(f"UDP: Failed to send response: {e}")
    
    except Exception as e:
        logger.error(f"UDP: Error processing request: {e}")
        # Log more details for debugging
        import traceback
        logger.error(traceback.format_exc())
        logger.error(f"UDP: Request data length: {len(data)}")
        if len(data) > 0:
            logger.error(f"UDP: First few bytes: {' '.join(f'{b:02x}' for b in data[:min(10, len(data))])}")

def handle_position_update(data, addr):
    """Process incoming position update packet"""
    try:
        offset = 0

        # Read player ID: 2 bytes length + variable string
        if len(data) < offset + 2:
            logger.warning("Packet too short for player ID length")
            return
        id_length = struct.unpack('!H', data[offset:offset+2])[0]
        offset += 2
        if len(data) < offset + id_length:
            logger.warning("Packet too short for player ID")
            return
        player_id = data[offset:offset + id_length].decode('utf-8')
        offset += id_length

        # Read timestamp: 8 bytes (long)
        if len(data) < offset + 8:
            logger.warning("Packet too short for timestamp")
            return
        timestamp = struct.unpack('!Q', data[offset:offset+8])[0]
        offset += 8

        # Read x: 4 bytes (int)
        if len(data) < offset + 4:
            logger.warning("Packet too short for x")
            return
        x = struct.unpack('!i', data[offset:offset+4])[0]
        offset += 4

        # Read y: 4 bytes (int)
        if len(data) < offset + 4:
            logger.warning("Packet too short for y")
            return
        y = struct.unpack('!i', data[offset:offset+4])[0]
        offset += 4

        # Read velocityX: 4 bytes (int)
        if len(data) < offset + 4:
            logger.warning("Packet too short for velocityX")
            return
        velocityX = struct.unpack('!i', data[offset:offset+4])[0]
        offset += 4

        # Read velocityY: 4 bytes (int)
        if len(data) < offset + 4:
            logger.warning("Packet too short for velocityY")
            return
        velocityY = struct.unpack('!i', data[offset:offset+4])[0]
        offset += 4

        # Read color: 2 bytes length + variable string
        if len(data) < offset + 2:
            logger.warning("Packet too short for color length")
            return
        color_length = struct.unpack('!H', data[offset:offset+2])[0]
        offset += 2
        if len(data) < offset + color_length:
            logger.warning("Packet too short for color")
            return
        color = data[offset:offset + color_length].decode('utf-8')

        # Update player data
        with player_lock:
            if player_id in players:
                if timestamp > players[player_id]['timestamp']:
                    players[player_id].update({
                        'x': x,
                        'y': y,
                        'velocityX': velocityX,
                        'velocityY': velocityY,
                        'color': color,
                        'timestamp': timestamp
                    })
            else:
                players[player_id] = {
                    'playerId': player_id,
                    'combatTag': 'Player',  # Default value; adjust if sent by client
                    'x': x,
                    'y': y,
                    'velocityX': velocityX,
                    'velocityY': velocityY,
                    'color': color,
                    'timestamp': timestamp,
                    'addr': addr  # Store address, though not used for responses here
                }
    except Exception as e:
        logger.error(f"Error processing position update: {e}")

def handle_position_updates(sock):
    """Listen for position updates on the position update socket"""
    while True:
        data, addr = sock.recvfrom(1024)
        handle_position_update(data, addr)

def handle_player_list_requests(sock):
    """Listen for player list requests on the player list socket"""
    while True:
        data, addr = sock.recvfrom(1024)
        handle_udp_request(data, addr, sock)

def cleanup_thread_func():
    """Periodically clean up inactive players"""
    while True:
        time.sleep(1)
        current_time = time.time()
        with player_lock:
            for pid in list(players.keys()):
                if current_time - players[pid]['timestamp'] / 1000 > TIMEOUT:  # Convert ms to s
                    logger.info(f"Cleanup: Player {pid} timed out")
                    players.pop(pid)

def add_dummy_player():
    """Add a dummy player for testing"""
    dummy_id = "dummy-player-id"
    players[dummy_id] = {
        'playerId': dummy_id,
        'combatTag': 'TEST_DUMMY',
        'x': 200,
        'y': 200, 
        'velocityX': 30,
        'velocityY': 20,
        'color': 'blue',
        'timestamp': time.time(),
        'addr': None
    }
    logger.info("Added dummy player for testing")

def main():
    # Add a dummy player for testing
    add_dummy_player()
    
    # Start cleanup thread
    threading.Thread(target=cleanup_thread_func, daemon=True).start()
    
    # Start position update thread
    threading.Thread(target=handle_position_updates, args=(position_update_socket,), daemon=True).start()
    
    # Start player list request thread
    threading.Thread(target=handle_player_list_requests, args=(player_list_socket,), daemon=True).start()
    
    logger.info("Server started")
    while True:
        time.sleep(1)  # Keep main thread alive

if __name__ == "__main__":
    main()