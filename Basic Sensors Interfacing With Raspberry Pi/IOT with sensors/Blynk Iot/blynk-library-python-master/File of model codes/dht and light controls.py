import BlynkLib
import RPi.GPIO as GPIO
from BlynkTimer import BlynkTimer
import Adafruit_DHT
import time

BLYNK_AUTH_TOKEN = 'aUWImWhr51CMB-GNx6B2Q9KeGWG2yEgW'

DHT_PIN = 4
led1 = 20
led2 = 21
led3 = 16
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(led1, GPIO.OUT)
GPIO.setup(led2, GPIO.OUT)
GPIO.setup(led3, GPIO.OUT)

x = 20
# Initialize Blynk
blynk = BlynkLib.Blynk(BLYNK_AUTH_TOKEN)
DHT_SENSOR = Adafruit_DHT.DHT11
timer = BlynkTimer()

# Led control through V0 virtual pin
@blynk.on("V2")
def v0_write_handler(value):
#    global led_switch
    if int(value[0]) is not 0:
        GPIO.output(led1, GPIO.HIGH)
        print('LED1 HIGH')
    else:
        GPIO.output(led1, GPIO.LOW)
        print('LED1 LOW')

# Led control through V1 virtual pin
@blynk.on("V3")
def v1_write_handler(value):
#    global led_switch
    if int(value[0]) is not 0:
        GPIO.output(led2, GPIO.HIGH)
        print('LED2 HIGH')
    else:
        GPIO.output(led2, GPIO.LOW)
        print('LED2 LOW')


# Functon for collect data from sensor & send it to Server
def myData():
    humidity, temperature = Adafruit_DHT.read(DHT_SENSOR, DHT_PIN)
    if humidity is not None and temperature is not None:
        print("Temp={0:0.1f}C Humidity={1:0.1f}%".format(temperature, humidity))
    else:
        print("Sensor failure. Check wiring.");

    blynk.virtual_write(1, humidity,)
    blynk.virtual_write(0, temperature)
    print("Values sent to New Blynk Server!")

timer.set_interval(2, myData)


#function to sync the data from virtual pins
@blynk.on("connected")
def blynk_connected():
    print("Raspberry Pi Connected to New Blynk")

# Manually create a timer
start_time = time.time()
interval = 2  # Interval in seconds

while True:
    current_time = time.time()
    if current_time - start_time >= interval:
        myData()  # Execute function
        start_time = time.time()  # Reset timer
    blynk.run()
    
