import BlynkLib
import RPi.GPIO as GPIO
from BlynkTimer import BlynkTimer
import serial

BLYNK_AUTH_TOKEN = '3ErHgRzBtdzWr6RL-cRhR1hJDMW1laLc'
ser = serial.Serial('/dev/ttyUSB0', 9600)  # Change port if needed

bulb1 = 20
bulb2 = 16
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(bulb1, GPIO.OUT)
GPIO.setup(bulb2, GPIO.OUT)

# Initialize Blynk
blynk = BlynkLib.Blynk(BLYNK_AUTH_TOKEN)

# Led control through V0 virtual pin
@blynk.on("V0")
def v0_write_handler(value):
    if int(value[0]) != 0:
        GPIO.output(bulb1, GPIO.HIGH)
        print('BULB 1 ON')
    else:
        GPIO.output(bulb1, GPIO.LOW)
        print('BULB 1 OFF')

# Led control through V1 virtual pin
@blynk.on("V1")
def v1_write_handler(value):
    if int(value[0]) != 0:
        GPIO.output(bulb2, GPIO.HIGH)
        print('BULB 2 ON')
    else:
        GPIO.output(bulb2, GPIO.LOW)
        print('BULB 2 OFF')

# Function to send sensor values to Blynk
def send_sensor_values():
    # Read data from Arduino
    data = ser.readline().decode().strip()
    sensor_values = data.split(',')

    # Extract sensor values
    sensor1_value = float(sensor_values[0])
    sensor2_value = float(sensor_values[1])
    a = float(sensor1_value * sensor2_value)
    
    # Send sensor values to Blynk
    blynk.virtual_write(3, sensor1_value)  
    blynk.virtual_write(2, sensor2_value)
    blynk.virtual_write(4, a)
    print(f"Sensor 1: {sensor1_value}, Sensor 2: {sensor2_value}")
# Register timer to send sensor values every second
timer = BlynkTimer()
timer.set_interval(1, send_sensor_values)

# Function to handle Blynk connection
@blynk.on("connected")
def blynk_connected():
    print("Raspberry Pi Connected to Blynk") 

# Main loop
while True:
    blynk.run()
    timer.run()
    # You can add additional processing here if needed

# Close the serial connection when done
ser.close()
