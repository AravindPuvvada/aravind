import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(18, GPIO.OUT)

pwm = GPIO.PWM(18, 50)
pwm.start(0)

def setAngle(angle):
    duty = angle / 18.0 + 2.5
    GPIO.output(18, True)
    pwm.ChangeDutyCycle(duty)
    time.sleep(1)
    GPIO.output(18, False)
    pwm.ChangeDutyCycle(duty)
    
try:
    while True:
        setAngle(0)
        print("0 to 180 degrees")
        time.sleep(1)
        setAngle(180)
        print("180 to 0 degrees")
        time.sleep(1)

except KeyboardInterrupt:
    pwm.stop()
    GPIO.cleanup()

