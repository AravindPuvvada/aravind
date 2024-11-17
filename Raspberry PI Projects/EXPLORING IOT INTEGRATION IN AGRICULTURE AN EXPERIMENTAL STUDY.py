import requests
import time
import RPi.GPIO as GPIO
import Adafruit_DHT
import Adafruit_GPIO.SPI as SPI
import Adafruit_MCP3008

def setup_mcp3008():
    CLK = 11
    MOSI = 10
    MISO = 9
    CS = 8
    mcp = Adafruit_MCP3008.MCP3008(clk=CLK, mosi=MOSI, miso=MISO, cs=CS)
    return mcp

api_key = "S735ZEHI88Z2JL3D"
api_url = "https://api.thingspeak.com/update.json"
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
val = Adafruit_DHT.DHT11
DHT_PIN = 4
relay=12
buzzer=21
GPIO.setup(relay,GPIO.OUT)
GPIO.setup(buzzer,GPIO.OUT)


mcp = setup_mcp3008()  # Initialize MCP3008

try:
    while True:        
        # Read temperature and humidity from DHT11
        hum,temp = Adafruit_DHT.read(val, DHT_PIN)
        soil = mcp.read_adc(0)
        print("Soil-value:", soil)
        if temp is not None and hum is not None:
            print(f'Temperature: {temp:.1f}C  Humidity: {hum:.1f}%')
            
            # Send temperature and humidity data to ThingSpeak
            data = {
                "api_key": api_key,
                "field1": temp,
                "field2": hum,
                "field3": soil
            }
            response = requests.post(api_url, data=data)
            if response.status_code == 200:
                print("Data sent successfully to ThingSpeak.")
                time.sleep(3);
            else:
                print("Failed to send data. Status code:", response.status_code)
        else:
            print("Failed to get a reading from the sensor. Trying again...")

        # Read soil moisture value
        
        
        if soil>600:
            GPIO.output(relay,GPIO.HIGH)
            GPIO.output(buzzer,GPIO.HIGH)

            time.sleep(2)
        else:
            GPIO.output(relay,GPIO.LOW)
            GPIO.output(buzzer,GPIO.LOW)

            time.sleep(1)
except KeyboardInterrupt:
    pass
finally:
    GPIO.cleanup()
