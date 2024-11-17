import RPi.GPIO as GPIO
import time

# Pin configuration
vibration_pin = 27  # GPIO pin connected to the vibration sensor

# Set up GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(vibration_pin, GPIO.IN)

try:
    while True:
        if GPIO.input(vibration_pin):
            print("No vibration")
        else:
            print("vibration Detected!!")
        time.sleep(0.5)  # Adjust the delay as needed

except KeyboardInterrupt:
    print("Program stopped")

finally:
    GPIO.cleanup()
