import subprocess
import re
import threading
import time
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

# Path to your Nios II Command Shell
NIOS_CMD_SHELL_BAT = "C:/intelFPGA_lite/18.1/nios2eds/Nios II Command Shell.bat"

# Global variables to hold the current position and velocity.
current_position = {"x": 0, "y": 0, "z": 0}
current_velocity = {"x": 0, "y": 0, "z": 0}
last_time = time.time()

velocity = np.array([0.0, 0.0])  # Initial velocity (vx, vy)
position = np.array([0.0, 0.0])  # Initial position (px, py)
alpha = 0.99  # Drift correction factor

# Filter parameters
filter_alpha = 0.1
filtered_acceleration = np.array([0.0, 0.0])
high_pass_filter_alpha = 0.9
high_pass_filtered_acceleration = np.array([0.0, 0.0])
previous_raw_acceleration = np.array([0.0, 0.0])

# Flag to indicate initial calibration
initial_calibration_done = False

def read_from_nios():
    """
    Opens a subprocess to read from the JTAG UART and extract X, Y, and Z values.
    Updates the current_position dictionary.
    """
    process = subprocess.Popen(
        NIOS_CMD_SHELL_BAT,
        bufsize=0,
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )

    try:
        # Start the Nios II terminal.
        process.stdin.write("nios2-terminal\n")
        process.stdin.flush()

        while True:
            output = process.stdout.readline()
            if not output:
                break  # Stop if no more data

            # Extract X, Y, Z values using regex.
            match = re.search(r"X:\s*(-?\d+),\s*Y:\s*(-?\d+),\s*Z:\s*(-?\d+)", output)
            if match:
                x, y, z = map(int, match.groups())
                filter_and_integrate_acceleration(x, y, z)
                #print(f"Received Data -> X: {x}, Y: {y}, Z: {z}")

    except Exception as e:
        print(f"Error: {e}")
    finally:
        process.terminate()

def filter_and_integrate_acceleration(x, y, z):
    """
    Filters and integrates the acceleration values to update the velocity and position.
    """
    global position, velocity, last_time, filtered_acceleration, high_pass_filtered_acceleration, previous_raw_acceleration, initial_calibration_done

    current_time = time.time()
    dt = current_time - last_time
    last_time = current_time

    # Convert acceleration to m/s^2
    x = x * 9.81
    y = y * 9.81

    raw_acceleration = np.array([x, y])

    # Apply low-pass filter (exponential moving average)
    filtered_acceleration = filter_alpha * raw_acceleration + (1 - filter_alpha) * filtered_acceleration

    # Apply high-pass filter to correct drift and separate true acceleration
    #high_pass_filtered_acceleration = high_pass_filter_alpha * (high_pass_filtered_acceleration + raw_acceleration - previous_raw_acceleration)
    #previous_raw_acceleration = raw_acceleration

    # Reset position and velocity for initial calibration
    if not initial_calibration_done:
        position = np.array([0.0, 0.0])
        velocity = np.array([0.0, 0.0])
        initial_calibration_done = True

    # Trapezoidal integration for velocity (v = v + a * dt)
    velocity = alpha * (velocity + filtered_acceleration * dt)  # Apply drift correction

    # Trapezoidal integration for position (p = p + v * dt)
    position += velocity * dt

    # Check if position exceeds limits and reset if necessary
    if abs(position[0]) > 250 or abs(position[1]) > 250:
        position = np.array([0.0, 0.0])
        velocity = np.array([0.0, 0.0])
        print("Position reset due to exceeding limits")

    # Print real-time velocity estimates
    #print(f"Velocity: vx={velocity[0]:.2f} m/s, vy={velocity[1]:.2f} m/s")

def animate_position(frame, ax):
    """
    Animation function that updates the 2D plot with the current position.
    If any of X, Y, or Z exceeds 500, the point is drawn as a red cross.
    """
    # Clear the axis for a fresh draw
    ax.clear()
    
    # Set the fixed axis limits (adjust these as needed)
    ax.set_xlim(-250, 250)
    ax.set_ylim(-250, 250)
    ax.set_xlabel("X Position")
    ax.set_ylabel("Y Position")
    ax.set_title("Current Position on 2D Plane")
    
    x = position[0]
    y = position[1]

    # Determine marker and color based on whether any value is above 500
    if x > 500 or y > 500:
        marker = "x"  # red cross marker
        color = "red"
        s = 100      # marker size
    else:
        marker = "o"  # blue circle marker
        color = "blue"
        s = 50

    ax.scatter(x, y, color=color, s=s, marker=marker)
    return ax,

def animate_velocity(frame, ax):
    """
    Animation function that updates the 2D plot with the current velocity.
    """
    # Clear the axis for a fresh draw
    ax.clear()
    
    # Set the fixed axis limits (adjust these as needed)
    ax.set_xlim(-10, 10)
    ax.set_ylim(-10, 10)
    ax.set_xlabel("X Velocity")
    ax.set_ylabel("Y Velocity")
    ax.set_title("Current Velocity on 2D Plane")
    
    vx = velocity[0]
    vy = velocity[1]

    # Determine marker and color based on whether any value is above a threshold
    if abs(vx) > 5 or abs(vy) > 5:
        marker = "x"  # red cross marker
        color = "red"
        s = 100      # marker size
    else:
        marker = "o"  # blue circle marker
        color = "blue"
        s = 50

    ax.scatter(vx, vy, color=color, s=s, marker=marker)
    return ax,

def main():
    # Start a thread to continuously read data from the FPGA.
    reader_thread = threading.Thread(target=read_from_nios, daemon=True)
    reader_thread.start()

    # Set up the 2D plot for position.
    fig_position, ax_position = plt.subplots()
    ani_position = animation.FuncAnimation(fig_position, animate_position, fargs=(ax_position,), interval=0.16, blit=False)

    # Set up the 2D plot for velocity.
    # fig_velocity, ax_velocity = plt.subplots()
    # ani_velocity = animation.FuncAnimation(fig_velocity, animate_velocity, fargs=(ax_velocity,), interval=20, blit=False)

    # Show both plots.
    plt.show()

if __name__ == "__main__":
    main()