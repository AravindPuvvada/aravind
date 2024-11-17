import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

relay=21

GPIO.setup(relay,GPIO.OUT)

for _ in range(5):
    GPIO.output(relay,GPIO.HIGH)
    print('relay on')
    time.sleep(5)
    GPIO.output(relay,GPIO.LOW)
    print('relay off')
    time.sleep(3)
