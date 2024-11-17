import RPi.GPIO as GPIO
import time
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
    time.sleep(1)

    
def back():
    GPIO.output(m1_1, GPIO.HIGH)
    GPIO.output(m1_2, GPIO.LOW)
    GPIO.output(m2_1, GPIO.HIGH)
    GPIO.output(m2_2, GPIO.LOW)
    time.sleep(1)

    
def front():
    GPIO.output(m1_1, GPIO.LOW)
    GPIO.output(m1_2, GPIO.HIGH)
    GPIO.output(m2_1, GPIO.LOW)
    GPIO.output(m2_2, GPIO.HIGH)
    time.sleep(1)


def right():
    GPIO.output(m1_1, GPIO.LOW)
    GPIO.output(m1_2, GPIO.HIGH)
    GPIO.output(m2_1, GPIO.HIGH)
    GPIO.output(m2_2, GPIO.LOW)
    time.sleep(1)

def left():
    GPIO.output(m1_1, GPIO.HIGH)
    GPIO.output(m1_2, GPIO.LOW)
    GPIO.output(m2_1, GPIO.LOW)
    GPIO.output(m2_2, GPIO.HIGH)
    time.sleep(1)



while True:
    
    submit=input('enter stop/ack/fromt/right/left:')

        
   
        
    if submit.lower() == 'stop':
        stop()
    elif submit.lower() == 'back':
        back()
    elif submit.lower() == 'front':
        front()
    elif submit.lower() == 'right':
        right()
    elif submit.lower() == 'left':
        left()
    else:
        print("Invalid command / object is nearby you. Motors are stopped.")
        stop()

