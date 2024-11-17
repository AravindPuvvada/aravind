import RPi.GPIO as GPIO
import time

vibration_pin = 27  # GPIO pin number where the vibration sensor is connected

# Set up GPIO
GPIO.setmode(GPIO.BCM)  # Use BCM pin numbering
GPIO.setup(vibration_pin, GPIO.IN)  # Set vibration_pin as input

try:
    while True:
        if GPIO.input(vibration_pin) == GPIO.HIGH:  # If vibration is detected (HIGH)
            print("Vibration detected! (HIGH)")
        else:
            print("No vibration. (LOW)")  # No vibration (LOW)
        time.sleep(0.5)  # Delay for half a second

except KeyboardInterrupt:
    print("Program stopped")

finally:
    GPIO.cleanup()  # Clean up GPIO when the program is stopped
