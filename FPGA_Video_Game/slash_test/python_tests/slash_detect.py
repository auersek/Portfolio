import subprocess
import re
import time

NIOS_CMD_SHELL_BAT = "C:/intelFPGA_lite/18.1/nios2eds/Nios II Command Shell.bat"

# Threshold for detecting a slash (set to ±1000 for each axis)
SLASH_THRESHOLD = 1000  # Minimum acceleration change to register a slash
TIME_WINDOW = 0.2  # Time window to check for slash (in seconds)

def detect_slash(prev_x, prev_y, prev_z, curr_x, curr_y, curr_z):
    """
    Detects a slash based on acceleration changes.
    Returns the direction of the slash if detected.
    """
    dx = abs(curr_x - prev_x)
    dy = abs(curr_y - prev_y)
    dz = abs(curr_z - prev_z)

    if dx > SLASH_THRESHOLD:
        return "Horizontal Slash" if curr_x > prev_x else "Reverse Horizontal Slash"
    elif dy > SLASH_THRESHOLD:
        return "Vertical Slash" if curr_y > prev_y else "Reverse Vertical Slash"
    elif dz > SLASH_THRESHOLD:
        return "Forward Slash" if curr_z > prev_z else "Reverse Forward Slash"
    return None

def read_from_nios():
    """
    Reads accelerometer data from the FPGA and detects slashes.
    """
    process = subprocess.Popen(
        NIOS_CMD_SHELL_BAT,
        bufsize=0,
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )

    prev_x, prev_y, prev_z = 0, 0, 0  # Store previous values
    last_slash_time = time.time()

    try:
        process.stdin.write("nios2-terminal\n")
        process.stdin.flush()

        while True:
            output = process.stdout.readline()
            if not output:
                break

            match = re.search(r"X:\s*(-?\d+),\s*Y:\s*(-?\d+),\s*Z:\s*(-?\d+)", output)
            if match:
                curr_x, curr_y, curr_z = map(int, match.groups())
                current_time = time.time()

                # Check if a slash has occurred within a time window
                if current_time - last_slash_time > TIME_WINDOW:
                    slash_detected = detect_slash(prev_x, prev_y, prev_z, curr_x, curr_y, curr_z)
                    if slash_detected:
                        print(f"Slash detected! Type: {slash_detected}")
                        last_slash_time = current_time  # Update last detected slash time

                # Update previous values
                prev_x, prev_y, prev_z = curr_x, curr_y, curr_z

    except Exception as e:
        print(f"Error: {e}")
    finally:
        process.terminate()

def main():
    read_from_nios()

if __name__ == "__main__":
    main()