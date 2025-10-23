import subprocess
import re

NIOS_CMD_SHELL_BAT = "C:/intelFPGA_lite/18.1/nios2eds/Nios II Command Shell.bat"

def read_from_nios():
    """
    Opens a subprocess to read from the JTAG UART and extracts X, Y, Z values.
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
        # Start the Nios II terminal and capture output
        process.stdin.write("nios2-terminal\n")
        process.stdin.flush()

        while True:
            output = process.stdout.readline()
            if not output:
                break  # Stop if no more data

            # Extract X, Y, Z values using regex
            match = re.search(r"X:\s*(-?\d+),\s*Y:\s*(-?\d+),\s*Z:\s*(-?\d+)", output)
            if match:
                x, y, z = map(int, match.groups())
                print(f"Received Data -> X: {x}, Y: {y}, Z: {z}")

    except Exception as e:
        print(f"Error: {e}")
    finally:
        process.terminate()

def main():
    read_from_nios()

if __name__ == "__main__":
    main()
