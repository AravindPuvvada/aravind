import blynklib
import RPi.GPIO as GPIO
import Adafruit_DHT
import time

DHT_SENSOR = Adafruit_DHT.DHT11
DHT_PIN = 4
BLYNK_AUTH_TOKEN = '4_5WRixhCYazwCUBs4nOo3CmYQXguAeb'

# Initialize Blynk
blynk = blynklib.Blynk(BLYNK_AUTH_TOKEN)


# Function to sync the data from virtual pins
@blynk.handle_event("connected")
def blynk_connected():
    print("Hi, You have connected to New Blynk 2.0")
    print(".......................................................")
    print("................... By SME Dehradun ...................")
    time.sleep(2)


# Function to collect data from sensor and send it to the server
def myData():
    humidity, temperature = Adafruit_DHT.read(DHT_SENSOR, DHT_PIN)
    if humidity is not None and temperature is not None:
        print("Temp={0:0.1f}°C Humidity={1:0.1f}%".format(temperature, humidity))
    else:
        print("Sensor failure. Check wiring.")

    blynk.virtual_write(0, humidity)
    blynk.virtual_write(1, temperature)
    print("Values sent to New Blynk Server!")


# Manually create a timer
start_time = time.time()
interval = 2  # Interval in seconds

while True:
    current_time = time.time()
    if current_time - start_time >= interval:
        myData()  # Execute function
        start_time = time.time()  # Reset timer

    blynk.run()
