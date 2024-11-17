import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
led=20
switch=26
GPIO.setup(led,GPIO.OUT)
GPIO.setup(switch,GPIO.IN)
while True:
    if GPIO.input(switch)==1:
        GPIO.output(led,GPIO.HIGH)
        print("Led on")
        time.sleep(1)
    else:
        GPIO.output(led,GPIO.LOW)
        led_state=0
        print("Led off")
        time.sleep(1)
