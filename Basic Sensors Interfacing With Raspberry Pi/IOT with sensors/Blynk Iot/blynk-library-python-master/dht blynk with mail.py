import BlynkLib
import Adafruit_DHT
import time
from BlynkTimer import BlynkTimer
import RPi.GPIO as GPIO
import requests


# Set up GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
led = 20
GPIO.setup(led, GPIO.OUT)

# Define Blynk credentials
BLYNK_AUTH_TOKEN = 'XO_bFfARi06kTAkbOC-u2g3kTMzWphEy'

# Set up DHT11 sensor
DHT_PIN = 4
DHT_SENSOR = Adafruit_DHT.DHT11

# Initialize Blynk
blynk = BlynkLib.Blynk(BLYNK_AUTH_TOKEN)
timer = BlynkTimer()

# Virtual Pin for notifications (configured in the Blynk app)
NOTIFICATION_VPIN = 2  # Replace with the virtual pin you assigned to the Notification widget

# Function to send a notification via Blynk


# Function to collect data from the sensor and send it to the Blynk server
def myData():
    humidity, temperature = Adafruit_DHT.read(DHT_SENSOR, DHT_PIN)
    if humidity is not None and temperature is not None:
        print(f"Temp={temperature:0.1f}C Humidity={humidity:0.1f}%")
        blynk.virtual_write(1, humidity)
        blynk.virtual_write(0, temperature)
        if humidity > 60:
            GPIO.output(led, GPIO.HIGH)
            # Send a notification via Blynk
            blynk.notify("Button was pressed!")
            time.sleep(1)
        else:
            GPIO.output(led, GPIO.LOW)
        print("Values sent to Blynk server!")
    else:
        print("Sensor failure. Check wiring.")

# Set the timer to call the myData function every 2 seconds
timer.set_interval(2, myData)

# Function to sync the data from virtual pins when connected
@blynk.on("connected")
def blynk_connected():
    print("Raspberry Pi Connected to Blynk")
    blynk.sync_virtual(0, 1)  # Sync virtual pins 0 and 1

# Main loop
while True:
    blynk.run()
    timer.run()  # Run the timer
