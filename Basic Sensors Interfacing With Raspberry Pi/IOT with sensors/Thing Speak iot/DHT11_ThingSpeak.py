import requests
import time
import RPi.GPIO as GPIO
import Adafruit_DHT
import Adafruit_GPIO.SPI as SPI

api_key = "R3I0NBZOT5N0TYX8"
api_url = "https://api.thingspeak.com/update.json"
GPIO.setmode(GPIO.BCM)
val = Adafruit_DHT.DHT11
DHT_PIN = 4

try:
    while True:        
        temp, hum = Adafruit_DHT.read(val, DHT_PIN)
        if temp is not None and hum is not None:
            print(f'Temperature: {temp:.1f}C  Humidity: {hum:.1f}%')
            data = {
                "api_key": api_key,
                "field1": temp,
                "field2": hum
            }
            response = requests.post(api_url, data=data)
            if response.status_code == 200:
                print("Data sent successfully to ThingSpeak.")
            else:
                print("Failed to send data. Status code:", response.status_code)
        else:
            print("Failed to get a reading from the sensor. Trying again...")
        
        time.sleep(1)  # Adjust the sleep interval as needed
except KeyboardInterrupt:
    pass
finally:
    GPIO.cleanup()
