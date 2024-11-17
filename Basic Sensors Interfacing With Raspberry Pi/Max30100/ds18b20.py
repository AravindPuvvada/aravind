import os
import glob
import time

# Initialize the One-Wire interface
os.system('modprobe w1-gpio')
os.system('modprobe w1-therm')

# Path to the sensor data
base_dir = '/sys/bus/w1/devices/'
device_folders = glob.glob(base_dir + '28*')

if not device_folders:
    print("No DS18B20 sensor detected. Check connections.")
    exit()

device_file = device_folders[0] + '/w1_slave'

# Function to read the raw sensor data
def read_temp_raw():
    with open(device_file, 'r') as f:
        lines = f.readlines()
    return lines

# Function to parse the temperature
def read_temp():
    lines = read_temp_raw()
    while lines[0].strip()[-3:] != 'YES':
        time.sleep(0.2)
        lines = read_temp_raw()
    equals_pos = lines[1].find('t=')
    if equals_pos != -1:
        temp_string = lines[1][equals_pos + 2:]
        temp_c = float(temp_string) / 1000.0
        temp_f = temp_c * 9.0 / 5.0 + 32.0
        return temp_c, temp_f

# Display the temperature every second
while True:
    temp_c, temp_f = read_temp()
    print(f"Temperature: {temp_c:.2f} °C / {temp_f:.2f} °F")
    time.sleep(1)
