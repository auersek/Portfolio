import requests
import time
import random
import json
import argparse

def test_whg_server(server_url, num_players=3):
    """Test the WHG server functionality"""
    print(f"Testing WHG server at {server_url}")
    
    # Create some test players
    player_ids = [f"test_player_{i}" for i in range(num_players)]
    
    # Test 1: Update players
    print("\n--- Test 1: Updating Players ---")
    for player_id in player_ids:
        # Create random position data
        player_data = {
            "playerId": player_id,
            "x": random.randint(0, 500),
            "y": random.randint(0, 500),
            "level": random.randint(1, 5),
            "color": f"#{random.randint(0, 0xFFFFFF):06x}"
        }
        
        try:
            response = requests.post(f"{server_url}/update", json=player_data)
            print(f"Updated {player_id}: {response.status_code}")
            if response.status_code == 200:
                print(f"  Response: {response.json()}")
            else:
                print(f"  Error: {response.text}")
        except Exception as e:
            print(f"  Failed to update {player_id}: {e}")
    
    # Test 2: Get all players
    print("\n--- Test 2: Getting Players List ---")
    try:
        response = requests.get(f"{server_url}/players", params={"playerId": player_ids[0]})
        print(f"Get players status: {response.status_code}")
        if response.status_code == 200:
            players = response.json()
            print(f"Found {len(players)} players:")
            for player in players:
                print(f"  Player: {player['playerId']}, Pos: ({player['x']}, {player['y']}), Color: {player['color']}")
        else:
            print(f"  Error: {response.text}")
    except Exception as e:
        print(f"  Failed to get players: {e}")
    
    # Test 3: Test timeout functionality
    print("\n--- Test 3: Testing Timeout ---")
    print(f"Waiting for {server_timeout + 1} seconds to test timeout...")
    time.sleep(server_timeout + 1)
    
    try:
        response = requests.get(f"{server_url}/players", params={"playerId": "timeout_test"})
        if response.status_code == 200:
            players = response.json()
            print(f"After timeout, found {len(players)} players")
            if len(players) == 0:
                print("  Success: All players timed out as expected")
            else:
                print("  Note: Some players still active:")
                for player in players:
                    print(f"    Player: {player['playerId']}")
        else:
            print(f"  Error: {response.text}")
    except Exception as e:
        print(f"  Failed to get players after timeout: {e}")
    
    # Test 4: Update one player after timeout
    print("\n--- Test 4: Updating After Timeout ---")
    player_data = {
        "playerId": player_ids[0],
        "x": random.randint(0, 500),
        "y": random.randint(0, 500),
        "level": random.randint(1, 5),
        "color": f"#{random.randint(0, 0xFFFFFF):06x}"
    }
    
    try:
        response = requests.post(f"{server_url}/update", json=player_data)
        print(f"Updated {player_ids[0]} after timeout: {response.status_code}")
        
        # Check player list again
        response = requests.get(f"{server_url}/players", params={"playerId": "final_test"})
        if response.status_code == 200:
            players = response.json()
            print(f"After update, found {len(players)} players")
            if len(players) == 1:
                print("  Success: One player active as expected")
            else:
                print(f"  Note: Found {len(players)} players")
    except Exception as e:
        print(f"  Failed final test: {e}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Test the WHG server")
    parser.add_argument("--server", default="http://localhost:5000",
                      help="Server URL (default: http://localhost:5000)")
    parser.add_argument("--players", type=int, default=3,
                      help="Number of test players to create (default: 3)")
    parser.add_argument("--timeout", type=int, default=5,
                      help="Server timeout in seconds (default: 5)")
    
    args = parser.parse_args()
    server_url = args.server
    server_timeout = args.timeout
    
    test_whg_server(server_url, args.players)