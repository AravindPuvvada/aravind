import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

Buzzer=21

GPIO.setup(Buzzer,GPIO.OUT)

for _ in range(5):
    GPIO.output(Buzzer,GPIO.HIGH)
    print('Buzzer on')
    time.sleep(5)
    GPIO.output(Buzzer,GPIO.LOW)
    print('Buzzer off')
    time.sleep(3)
