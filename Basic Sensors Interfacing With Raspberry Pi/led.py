import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

led=20

GPIO.setup(led,GPIO.OUT)

for _ in range(100):
    GPIO.output(led,GPIO.HIGH)
    print("LED ON")
    time.sleep(5)
    GPIO.output(led,GPIO.LOW)
    print('led off')
    time.sleep(3)
