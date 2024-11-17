import requests
import RPi.GPIO as GPIO
import Adafruit_MCP3008
import time
import Adafruit_GPIO.SPI as SPI

api_key="R3I0NBZOT5N0TYX8"

api_url = "https://api.thingspeak.com/update.json"
GPIO.setmode(GPIO.BCM)
CLK=11
MISO=9
MOSI=10
CS=8
mcp=Adafruit_MCP3008.MCP3008(clk=CLK,miso=MISO,mosi=MOSI,cs=CS)
while True:
    mq7=mcp.read_adc(0)
    print("MQ7:",mq7)
    time.sleep(1)
    data={
        "apikey":api_key,
        "field3":mq7
        }
    response=requests.post(api_url,data=data)
    if response.status_code==200:
        print("Successfully Sent Data to ThingSpeak")
    else:
        print("Failed to sent data to Thingspeak")
