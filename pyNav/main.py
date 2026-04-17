import serial
import time

from mapping import polarToCartesian, worldToGrid, Grid2D, drawLine

# Serial setup (adjust 'COM3' to your USB serial port)
arduino = serial.Serial(port='COM6', baudrate=115200, timeout=1)
time.sleep(2)  # Allow time for serial connection

# Grid setup
ORIGIN_X = 0
ORIGIN_Y = 0
GRID_W = 20
GRID_H = 20
SCALE = 0.5  # 0.05m resolution

map_grid = Grid2D(GRID_W, GRID_H)

print("Reading polar coordinates from serial... Press Ctrl+C to stop and display grid.")

try:
    while True:
        if arduino.in_waiting > 0:
            line = arduino.readline().decode('utf-8').strip()
            if line:
                try:
                    # Assume data format: "r,theta" (e.g., "1.5,45.0")
                    parts = line.split(',')
                    if len(parts) == 2:
                        r = float(parts[0])
                        theta = float(parts[1])
                        # Convert polar to Cartesian
                        cart = polarToCartesian(r, theta)
                        # Convert world coordinates to grid coordinates
                        x_grid = worldToGrid(cart.x, SCALE)
                        y_grid = worldToGrid(cart.y, SCALE)
                        # Draw line from origin (0,0) to the point
                        drawLine(map_grid, 10, 10, x_grid, y_grid)
                        print(f"Drew line to ({x_grid}, {y_grid}) from polar ({r}, {theta})")
                except ValueError as e:
                    print(f"Invalid data received: {line} - {e}")
        time.sleep(0.1)  # Small delay to avoid busy waiting
except KeyboardInterrupt:
    print("\nStopping serial read...")
finally:
    arduino.close()
    print("Serial connection closed.")
    map_grid.display()