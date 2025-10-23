from flask import Flask, request, jsonify
import time
import logging

app = Flask(__name__)

# Configure logging
logging.basicConfig(
    level=logging.DEBUG,
    format='%(asctime)s [%(levelname)s] %(message)s',
    handlers=[
        logging.StreamHandler(),
        logging.FileHandler('whg_server.log')
    ]
)
logger = logging.getLogger(__name__)

# Store player data with timestamp
players = {}
# Time in seconds before a player is considered disconnected
TIMEOUT = 5

@app.route('/update', methods=['POST'])
def update_player():
    player_data = request.json
    player_id = player_data['playerId']
    
    # Log incoming data
    logger.info(f"Received update from player {player_id}: {player_data}")
    
    # Add timestamp
    player_data['timestamp'] = time.time()
    
    # Update player data
    players[player_id] = player_data
    
    return jsonify({'status': 'success'})

@app.route('/players', methods=['GET'])
def get_players():
    current_time = time.time()
    # Get requesting player ID
    requesting_player = request.args.get('playerId')
    
    logger.info(f"Player {requesting_player} requesting player list")
    
    # Clean up old player data
    active_players = []
    for player_id, data in list(players.items()):
        if current_time - data['timestamp'] < TIMEOUT:
            active_players.append(data)
        else:
            logger.info(f"Player {player_id} timed out, removing")
            players.pop(player_id)
    
    # Add a dummy player that's always visible for testing
    dummy_player = {
        'playerId': 'dummy-player-id',
        'combatTag': 'TEST_DUMMY',
        'x': 200,  # Fixed position
        'y': 200,
        'color': 'blue',
        'timestamp': current_time
    }
    
    # Only add dummy if it's not the only player (to avoid confusing single players)
    if requesting_player != 'dummy-player-id':
        active_players.append(dummy_player)
    
    logger.info(f"Sending {len(active_players)} players to {requesting_player}")
    
    return jsonify(active_players)

if __name__ == '__main__':
    logger.info("Starting World's Hardest Game server")
    app.run(host='0.0.0.0', port=5000)