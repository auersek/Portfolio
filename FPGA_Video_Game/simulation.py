import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

def build_rotation_matrix(ax, ay, az):
    """
    Build a rotation matrix from 3-axis accelerometer measurements.
    
    The function normalizes the input vector, computes the roll (phi) and 
    pitch (theta) angles, constructs rotation matrices for each, and combines
    them (roll is applied before pitch).
    """
    norm = np.sqrt(ax**2 + ay**2 + az**2)
    if norm == 0:
        return np.eye(3)
    ax_norm, ay_norm, az_norm = ax / norm, ay / norm, az / norm

    # Calculate roll (phi) and pitch (theta)
    phi = np.arctan2(ay_norm, az_norm)
    theta = np.arctan2(-ax_norm, np.sqrt(ay_norm**2 + az_norm**2))
    
    # Rotation matrix for roll (rotation about X-axis)
    R_roll = np.array([
        [1,            0,             0],
        [0, np.cos(phi), -np.sin(phi)],
        [0, np.sin(phi),  np.cos(phi)]
    ])
    
    # Rotation matrix for pitch (rotation about Y-axis)
    R_pitch = np.array([
        [ np.cos(theta), 0, np.sin(theta)],
        [             0, 1,            0],
        [-np.sin(theta), 0, np.cos(theta)]
    ])
    
    # Combined rotation: roll is applied before pitch
    R = R_roll @ R_pitch
    return R

class MotionSimulator:
    def __init__(self, step_size=1):
        # We now simulate motion in the Y-Z plane only. The X value remains fixed.
        self.position = np.zeros(3)  # [x, y, z]
        self.prev_rot = np.eye(3)
        self.step_size = step_size  
        # Set boundaries: x is fixed at 0; y in [-100, 100]; z in [-50, 50]
        self.boundaries = [(0, 0), (-100, 100), (-50, 50)]  

    def _clamp(self, value, min_val, max_val):
        return max(min(value, max_val), min_val)

    def apply_boundaries(self):
        """Clamp the position vector within preset boundaries."""
        for i in range(3):
            self.position[i] = self._clamp(self.position[i], *self.boundaries[i])

    def detect_slash(self, current_rot, threshold=2):
        """
        Detect a 'slash' event by comparing the current rotation matrix to the
        previous one using the Frobenius norm.
        """
        diff = np.linalg.norm(current_rot - self.prev_rot, ord='fro')
        return diff > threshold

    def update_position_from_accelerometer(self, ax, ay, az):
        """
        Update the position based on accelerometer data.
        
        The forward (device-x) direction is computed from the rotation matrix.
        To simulate motion in the Y-Z plane, we zero out the X component.
        A big change in orientation (slash) resets the position.
        """
        current_rot = build_rotation_matrix(ax, ay, az)
        
        if self.detect_slash(current_rot):
            self.position = np.zeros(3)
            print("SLASH DETECTED! Resetting position to origin.")
        else:
            # Compute the forward direction in world coordinates.
            forward = current_rot @ np.array([1, 0, 0])
            # Zero out the X component so that movement is only in Y and Z.
            forward[0] = 0
            norm = np.linalg.norm(forward)
            if norm != 0:
                forward = forward / norm
            movement_vector = self.step_size * forward
            self.position += movement_vector
            self.apply_boundaries()
            
        self.prev_rot = current_rot.copy()

def simulate_accelerometer_data_random(num_steps, small_std_deg=1.0, slash_prob=0.05, noise_std=0.05):
    """
    Generate simulated accelerometer readings with random variations.
    
    - The pitch and roll follow a random walk with small noise.
    - With probability `slash_prob`, a big random jump (between -45° and 45°)
      is introduced to mimic a 'slash' event.
    - Additionally, Gaussian noise is added to the acceleration values to
      simulate realistic sensor noise.
      
    The gravity vector (normalized) is computed as:
      a_x = -sin(pitch)
      a_y = sin(roll)*cos(pitch)
      a_z = cos(roll)*cos(pitch)
    
    Returns a list of (ax, ay, az) tuples.
    """
    pitch = 0.0  # initial pitch in radians
    roll = 0.0   # initial roll in radians
    data = []
    
    for i in range(num_steps):
        if np.random.rand() < slash_prob:
            # Big movement: random pitch and roll between -45° and 45°
            pitch = np.radians(np.random.uniform(-45, 45))
            roll = np.radians(np.random.uniform(-45, 45))
        else:
            # Small random walk (noise)
            pitch += np.radians(np.random.normal(0, small_std_deg))
            roll += np.radians(np.random.normal(0, small_std_deg))
        
        # Compute ideal accelerometer reading for gravity.
        ax = -np.sin(pitch)
        ay = np.sin(roll) * np.cos(pitch)
        az = np.cos(roll) * np.cos(pitch)
        
        # Add Gaussian noise to each axis.
        noise = np.random.normal(0, noise_std, 3)
        ax_noisy = ax + noise[0]
        ay_noisy = ay + noise[1]
        az_noisy = az + noise[2]
        
        data.append((ax_noisy, ay_noisy, az_noisy))
    return data

# ---------------------------
# Animation Setup
# ---------------------------

sim = MotionSimulator(step_size=1)
num_steps = 1000000
# Generate simulated accelerometer readings with noise.
acc_data = simulate_accelerometer_data_random(num_steps, small_std_deg=1, slash_prob=0.05, noise_std=0.5)
positions = []  # will store the (x, y, z) positions over time

fig, ax = plt.subplots(figsize=(8, 6))
# Set axis limits for Y (horizontal) and Z (vertical)
ax.set_xlim(-100, 100)
ax.set_ylim(-50, 50)
ax.set_xlabel("Y Position")
ax.set_ylabel("Z Position")
ax.set_title("Device Motion Visualization (Z vs Y) with Noise")

# Plot elements: a blue trail and a red dot representing current position.
trail_line, = ax.plot([], [], 'b-', lw=2)
current_dot, = ax.plot([], [], 'ro', markersize=8)

def init():
    """Initialize the animation plot elements."""
    trail_line.set_data([], [])
    current_dot.set_data([], [])
    return trail_line, current_dot

def animate(frame):
    """
    For each frame, update the simulator with the next random accelerometer reading,
    then update the trail and current dot using the Y and Z coordinates.
    """
    index = frame % num_steps
    ax_val, ay_val, az_val = acc_data[index]
    sim.update_position_from_accelerometer(ax_val, ay_val, az_val)
    
    positions.append(sim.position.copy())
    pos_array = np.array(positions)
    
    # Plot Y (index 1) on horizontal and Z (index 2) on vertical.
    trail_line.set_data(pos_array[:, 1], pos_array[:, 2])
    current_dot.set_data(sim.position[1], sim.position[2])
    
    return trail_line, current_dot

ani = animation.FuncAnimation(
    fig, animate, init_func=init, frames=500, interval=10, blit=True
)

plt.show()
