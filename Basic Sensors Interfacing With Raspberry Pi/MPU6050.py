import smbus
import time

# MPU6050 Constants
MPU6050_ADDRESS = 0x68
PWR_MGMT_1 = 0x6B
ACCEL_XOUT_H = 0x3B
ACCEL_XOUT_L = 0x3C
ACCEL_YOUT_H = 0x3D
ACCEL_YOUT_L = 0x3E
ACCEL_ZOUT_H = 0x3F
ACCEL_ZOUT_L = 0x40

# Initialize I2C
bus = smbus.SMBus(1)

# Wake up the MPU6050
bus.write_byte_data(MPU6050_ADDRESS, PWR_MGMT_1, 0)

def read_raw_data(addr):
    high = bus.read_byte_data(MPU6050_ADDRESS, addr)
    low = bus.read_byte_data(MPU6050_ADDRESS, addr + 1)
    value = ((high << 8) | low)
    if value > 32768:
        value -= 65536
    return value

def detect_fall(accel_x, accel_y, accel_z):
    # Calculate the acceleration magnitude
    magnitude = (accel_x**2 + accel_y**2 + accel_z**2)**0.5
    
    # Threshold for detecting a fall (adjust this value based on testing)
    fall_threshold = 15.0  # You may need to calibrate this value
    
    if magnitude < fall_threshold:
        return True  # Fall detected
    return False

while True:
    # Read accelerometer data
    accel_x = read_raw_data(ACCEL_XOUT_H)
    accel_y = read_raw_data(ACCEL_YOUT_H)
    accel_z = read_raw_data(ACCEL_ZOUT_H)

    # Check for a fall
    if detect_fall(accel_x, accel_y, accel_z):
        print("Fall detected!")
    else:
        print("No fall detected.")

    # Delay for a short period
    time.sleep(1)
