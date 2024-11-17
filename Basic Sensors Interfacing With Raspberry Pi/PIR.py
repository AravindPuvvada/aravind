import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
pir=17
led=20
GPIO.setup(led,GPIO.OUT)
GPIO.setup(pir,GPIO.IN)

while True:
    pir_state=GPIO.input(pir)
    if pir_state==0:
        
        GPIO.output(led,GPIO.HIGH)
        print("Motion Detected")
    else:
        GPIO.output(led,GPIO.LOW)
        print("No Motion Detected")
    time.sleep(1)    
    
    
