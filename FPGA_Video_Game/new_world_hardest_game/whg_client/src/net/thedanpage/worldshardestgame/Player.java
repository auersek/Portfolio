package net.thedanpage.worldshardestgame;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.Shape;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.logging.Level;

import kuusisto.tinysound.Sound;
import kuusisto.tinysound.TinySound;

public class Player {

	private Color playerColor;
	private int x;
	private int y;
	private int snapX;
	private int snapY;
	private boolean collidingUp;
	private boolean collidingDown;
	private boolean collidingLeft;
	private boolean collidingRight;
	private int deaths;
	private boolean dead;
	private double opacity;

	// New fields for FPGA controller support
	private int port;
	private double xTilt = 0.0;
	private double yTilt = 0.0;
	private FPGAServer fpgaServer;

	// Inner class to handle FPGA server for each player
	private class FPGAServer {
		private ServerSocket serverSocket;
		private Socket clientSocket;
		private BufferedReader reader;
		private Thread serverThread;

		public FPGAServer(int port) {
			this.serverThread = new Thread(() -> {
				try {
					serverSocket = new ServerSocket(port);
					System.out.println("Server started on port " + port + ". Waiting for connection...");

					clientSocket = serverSocket.accept();
					System.out.println("Connected to client on port " + port + "!");

					reader = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));

					while (true) {
						String data = reader.readLine();
						if (data != null) {
							String[] values = data.split(",");
							if (values.length == 2) {
								xTilt = Double.parseDouble(values[0].trim());
								yTilt = Double.parseDouble(values[1].trim());
							} else {
								System.out.println("Invalid data format received.");
							}
						}
					}
				} catch (Exception e) {
					e.printStackTrace();
				}
			});
		}

		public void start() {
			serverThread.start();
		}

		public void stop() {
			try {
				if (serverSocket != null) serverSocket.close();
				if (clientSocket != null) clientSocket.close();
				if (serverThread != null) serverThread.interrupt();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

	// Constructors modified to include port for FPGA server
	public Player(int x, int y, Color color, int port) {
		this.x = x;
		this.y = y;
		this.snapX = x/40;
		this.snapY = y/40;
		this.collidingUp = false;
		this.collidingDown = false;
		this.collidingLeft = false;
		this.collidingRight = false;
		this.deaths = 0;
		this.dead = false;
		this.opacity = 255;
		this.playerColor = color;
		this.port = port;

		// Initialize and start FPGA server for this player
		this.fpgaServer = new FPGAServer(port);
		this.fpgaServer.start();
	}


	public void draw(Graphics g) {
		g.setColor(new Color(0, 0, 0, (int) opacity));
		g.fillRect(x - 15, y - 15 + 22, 31, 31);
		// Use the player's color instead of always red
		g.setColor(new Color(playerColor.getRed(), playerColor.getGreen(),
				playerColor.getBlue(), (int) opacity));
		g.fillRect(x-12, y-12 + 22,
				25, 25);
	}

	public Color getPlayerColor() {
		return this.playerColor;
	}

	public void setPlayerColor(Color color) {
		this.playerColor = color;
	}



	Tile getRelativeTile(GameLevel level, int x1, int y1, int xOff, int yOff) {
		for (Tile t : level.getTileMap()) {
			if (x1/40 + xOff == t.getSnapX() && y1/40 + yOff == t.getSnapY()) {
				return t;
			}
		}
		return null;
	}
	

	
	
	Tile getTile(GameLevel level) {
		for (Tile t : level.getTileMap()) {
			if (this.x/40 == t.getSnapX() && this.y/40 == t.getSnapY()) {
				return t;
			}
		}
		return null;
	}

	boolean doesIntersect(Rectangle a, Rectangle b) {
		return (a.x + a.width < b.x || a.x > b.x + b.width
				|| a.y + a.height < b.y || a.y > b.y + b.height);
	}
	
	public Rectangle getBounds() {
		return new Rectangle(this.x - 15, this.y - 15, 31, 31);
	}
	
	void checkCollisionUp(GameLevel level) {
		if (getRelativeTile(level, this.x - 14, this.y + 24, 0, -1) != null &&
				getRelativeTile(level, this.x - 14, this.y + 24, 0, -1).getType() == 0 ||
				getRelativeTile(level, this.x + 15, this.y + 24, 0, -1) != null &&
				getRelativeTile(level, this.x + 15, this.y + 24, 0, -1).getType() == 0) {
			this.collidingUp = true;
			return;
		}
		this.collidingUp = false;
	}
	
	void checkCollisionDown(GameLevel level) {
		if (getRelativeTile(level, this.x - 14, this.y - 24, 0, 1) != null &&
				getRelativeTile(level, this.x - 14, this.y - 24, 0, 1).getType() == 0 ||
				getRelativeTile(level, this.x + 15, this.y - 24, 0, 1) != null &&
				getRelativeTile(level, this.x + 15, this.y - 24, 0, 1).getType() == 0) {
			this.collidingDown = true;
			return;
		}
		this.collidingDown = false;
	}
	
	void checkCollisionLeft(GameLevel level) {
		if (getRelativeTile(level, this.x + 24, this.y - 15, -1, 0) != null &&
				getRelativeTile(level, this.x + 24, this.y - 15, -1, 0).getType() == 0 ||
				getRelativeTile(level, this.x + 24, this.y + 14, -1, 0) != null &&
				getRelativeTile(level, this.x + 24, this.y + 14, -1, 0).getType() == 0) {
			this.collidingLeft = true;
			return;
		}
		this.collidingLeft = false;
	}
	
	void checkCollisionRight(GameLevel level) {
		if (getRelativeTile(level, this.x - 24, this.y - 15, 1, 0) != null &&
				getRelativeTile(level, this.x - 24, this.y - 15, 1, 0).getType() == 0 ||
				getRelativeTile(level, this.x - 24, this.y + 15, 1, 0) != null &&
				getRelativeTile(level, this.x - 24, this.y + 15, 1, 0).getType() == 0) {
			this.collidingRight = true;
			return;
		}
		this.collidingRight = false;
	}

	public void respawn(GameLevel level) {
		// Choose spawn point based on player color
		this.x = level.getSpawnPoint().x;
		this.y = level.getSpawnPoint().y;
		// Reset player 1's coins
		if (level.coins != null) {
			for (Coin coin : level.coins) coin.collected = false;
		}
	}

	boolean collidesWith(Shape other) {
	    return this.getBounds().getBounds2D().intersects(other.getBounds2D());
	}

	private static final int TILT_THRESHOLD_X = 100;
	private static final int TILT_THRESHOLD_Y = 100;
	private static final int MOVEMENT_STEP = 1;

	public void update(GameLevel level) {
		this.snapX = this.x / 40;
		this.snapY = this.y / 40;

		// Determine which coin collection to use based on player color
		ArrayList<Coin> playerCoins;
		playerCoins = level.coins; // Player 1 coins

		// Check for coin collection
		if (playerCoins != null) {
			for (Coin coin : playerCoins) {
				if (this.collidesWith(coin.getBounds()) && !coin.collected) {
					coin.collected = true;

					// Coin sound
					TinySound.init();
					TinySound.loadSound(Player.class.getClassLoader()
							.getResource("net/thedanpage/worldshardestgame/resources/ding.wav")).play();
				}
			}
		}

		// Level completion logic - both players need to reach the goal
		if (level.getTileMap() != new ArrayList<Tile>()) {
			if (level.allCoinsCollected()) {
				for (Tile t : level.getTileMap()) {
					if (t.getType() == 3 && this.collidesWith(t.getBounds())) {
						Game.levelNum++;
						level.init(Game.getPlayers()[0], Game.levelNum);
						Game.gameState = Game.LEVEL_TITLE;
						Game.easyLog(Game.logger, Level.INFO, "Game state set to LEVEL_TITLE");

						// Wait 1.75 seconds then start the next level
						new Thread() {
							public void run() {
								try {
									Thread.sleep(1750);
								} catch (InterruptedException e) {
									Game.easyLog(Game.logger, Level.SEVERE, Game.getStringFromStackTrace(e));
								}
								Game.gameState = Game.LEVEL;
								Game.easyLog(Game.logger, Level.INFO, "Game state set to LEVEL");
							}
						}.start();
					}
				}
			}
		}
		// Check collision in all directions
		checkCollisionUp(level);
		checkCollisionDown(level);
		checkCollisionLeft(level);
		checkCollisionRight(level);

		// Handle player death and respawn
		if (this.dead) {
			this.opacity -= 255 / 75;
			if (this.opacity < 0) this.opacity = 0;

			if (this.opacity == 0) {
				this.dead = false;
				this.opacity = 255;
				this.respawn(level);
			}
		} else {
			//Handles the TCP connection to the FPGA controller
			// Handle movement based on FPGA tilt data
			if (xTilt < -TILT_THRESHOLD_X && !this.collidingRight) {
				this.x += MOVEMENT_STEP;  // Move right
			} else if (xTilt > TILT_THRESHOLD_X && !this.collidingLeft) {
				this.x -= MOVEMENT_STEP;  // Move left
			}

			if (yTilt > TILT_THRESHOLD_Y && !this.collidingDown) {
				this.y += MOVEMENT_STEP;  // Move down
			} else if (yTilt < -TILT_THRESHOLD_Y && !this.collidingUp) {
				this.y -= MOVEMENT_STEP;  // Move up
			}
			// Player-specific movement controls based on color
			//change this if statement color changes which controls the FPGA (BLUE - RED is controlled, RED - BLUE is controlled)
			//Place to add second port setup same way as 5000 but for different client to runt the other guy
			if (this.playerColor.equals(Color.RED)) {
				// Player 1 uses arrow keys
				if (Input.up.isPressed && !this.collidingUp) this.y--;
				if (Input.down.isPressed && !this.collidingDown) this.y++;
				if (Input.left.isPressed && !this.collidingLeft) this.x--;
				if (Input.right.isPressed && !this.collidingRight) this.x++;
			} else {
				// Player 2 uses WASD
				if (Input.wKey.isPressed && !this.collidingUp) this.y--;
				if (Input.sKey.isPressed && !this.collidingDown) this.y++;
				if (Input.aKey.isPressed && !this.collidingLeft) this.x--;
				if (Input.dKey.isPressed && !this.collidingRight) this.x++;
			}
		}

		// Wrap-around logic for screen edges
		if (this.x > 800) this.x = 0;
		if (this.x < 0) this.x = 800;
		if (this.y > 600) this.y = 0;
		if (this.y < 0) this.y = 600;

		// Check for collision with dots (instant death)
		if (!this.dead) {
			for (Dot dot : level.dots) {
				if (this.collidesWith(dot.getBounds())) {
					this.deaths++;
					this.dead = true;

					// Play death sound
					if (!Game.muted) {
						TinySound.init();
						TinySound.loadSound(ClassLoader.getSystemResource(
								"net/thedanpage/worldshardestgame/resources/smack.wav")).play();
					}
				}
			}
		}
	}





	public int getX() {
		return this.x;
	}
	
	
	
	public int getY() {
		return this.y;
	}
	
	
	
	public int getSnapX() {
		return this.snapX;
	}
	
	
	
	public int getSnapY() {
		return this.snapY;
	}
	
	
	
	public int getWidth() {
		return (int) this.getBounds().getWidth();
	}
	
	
	
	public int getHeight() {
		return (int) this.getBounds().getHeight();
	}
	
	
	
	public boolean isCollidingLeft() {
		return this.collidingLeft;
	}
	
	
	
	public boolean isCollidingRight() {
		return this.collidingRight;
	}
	
	
	
	public boolean isCollidingUp() {
		return this.collidingUp;
	}
	
	
	
	public boolean isCollidingDown() {
		return this.collidingDown;
	}
	
	
	
	public int getDeaths() {
		return this.deaths;
	}
	
	
	
	public boolean isDead() {
		return this.dead;
	}
	
	
	
	public void setDead(boolean dead) {
		this.dead = dead;
	}
	
	
	
	public double getOpacity() {
		return this.opacity;
	}
	
	
	
	public void reset() {
		this.x = 400;
		this.y = 300;
		this.snapX = x/40;
		this.snapY = y/40;
		this.collidingUp = false;
		this.collidingDown = false;
		this.collidingLeft = false;
		this.collidingRight = false;
		this.deaths = 0;
		this.dead = false;
		this.opacity = 255;
	}

	public void cleanup() {
		if (fpgaServer != null) {
			fpgaServer.stop();
		}
	}



	@Override
	public String toString() {
		return "Player [x=" + x + ", y=" + y + ", snapX=" + snapX + ", snapY="
				+ snapY + ", collidingUp=" + collidingUp + ", collidingDown="
				+ collidingDown + ", collidingLeft=" + collidingLeft
				+ ", collidingRight=" + collidingRight + ", deaths=" + deaths
				+ ", dead=" + dead + "]";
	}


}
