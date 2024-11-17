import requests
import time
import RPi.GPIO as GPIO
import Adafruit_MCP3008
import Adafruit_GPIO.SPI as SPI

api_key = "R3I0NBZOT5N0TYX8"
if api_key is None:
    raise ValueError("THINGSPEAK_API_KEY environment variable not set")

api_url = "https://api.thingspeak.com/update.json"

GPIO.setmode(GPIO.BCM)
CLK = 11
MOSI = 10
MISO = 9
CS = 8
mcp = Adafruit_MCP3008.MCP3008(clk=CLK, mosi=MOSI, miso=MISO, cs=CS)

try:
    while True:        
        ldr = mcp.read_adc(0)
        print("Analog Value:", ldr)
        time.sleep(1)
        
        data = {
            "api_key": api_key,
            "field3": ldr
        }
        
        response = requests.post(api_url, data=data)
        if response.status_code == 200:
            print("Data sent successfully to ThingSpeak.")
        else:
            print("Failed to send data. Status code:", response.status_code)
        
        time.sleep(2)  # Adjust the sleep interval as needed

except KeyboardInterrupt:
    pass
finally:
    GPIO.cleanup()
