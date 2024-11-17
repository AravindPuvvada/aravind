import RPi.GPIO as GPIO
from time import sleep
import Adafruit_GPIO.SPI as SPI

# Set up GPIO pins
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

m1_1 = 21
m1_2 = 20
m2_1 = 16
m2_2 = 12

GPIO.setup(m1_1, GPIO.OUT)
GPIO.setup(m1_2, GPIO.OUT)
GPIO.setup(m2_1, GPIO.OUT)
GPIO.setup(m2_2, GPIO.OUT)

# Define motor control functions
def stop():
    GPIO.output(m1_1, GPIO.LOW)
    GPIO.output(m1_2, GPIO.LOW)
    GPIO.output(m2_1, GPIO.LOW)
    GPIO.output(m2_2, GPIO.LOW)

def back():
    GPIO.output(m1_1, GPIO.HIGH)
    GPIO.output(m1_2, GPIO.LOW)
    GPIO.output(m2_1, GPIO.HIGH)
    GPIO.output(m2_2, GPIO.LOW)

def front():
    GPIO.output(m1_1, GPIO.LOW)
    GPIO.output(m1_2, GPIO.HIGH)
    GPIO.output(m2_1, GPIO.LOW)
    GPIO.output(m2_2, GPIO.HIGH)

def right():
    GPIO.output(m1_1, GPIO.LOW)
    GPIO.output(m1_2, GPIO.HIGH)
    GPIO.output(m2_1, GPIO.HIGH)
    GPIO.output(m2_2, GPIO.LOW)
    sleep(1)

def left():
    GPIO.output(m1_1, GPIO.HIGH)
    GPIO.output(m1_2, GPIO.LOW)
    GPIO.output(m2_1, GPIO.LOW)
    GPIO.output(m2_2, GPIO.HIGH)
    sleep(1)



while True:
    submit=input("Enter Stop/back/front/right/left:")
    if submit=='stop':
        stop()
    elif submit=='back':
        back()
    elif submit=='front':
        front()
    elif submit=='right':
        right()
    elif submit=='left':
        left()
