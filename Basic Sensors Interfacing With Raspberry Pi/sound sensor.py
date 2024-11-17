import Adafruit_MCP3008
import RPi.GPIO as GPIO
import time
def setup_mcp3008():
    CLK=11
    MOSI=10
    MISO=9
    CS=8
    mcp = Adafruit_MCP3008.MCP3008(clk=CLK, mosi=MOSI, miso=MISO, cs=CS)
    return mcp
GPIO.setmode(GPIO.BCM)
def read_analog_values(mcp):
    try:
        while True:
            value = mcp.read_adc(0)
            print("sound level:", value)
            time.sleep(1)
    finally:
        mcp.close()
        GPIO.cleanup()
mcp = setup_mcp3008()
read_analog_values(mcp)
        
