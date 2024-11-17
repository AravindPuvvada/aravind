import RPi.GPIO as GPIO
import time

# Motor 1 (Left Motor) pins
IN1 = 26  # GPIO 26 for IN1
IN2 = 19  # GPIO 19 for IN2

# Motor 2 (Right Motor) pins
IN3 = 13  # GPIO 13 for IN3
IN4 = 6   # GPIO 6 for IN4

# Set up GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

# Set motor pins as output
GPIO.setup(IN1, GPIO.OUT)
GPIO.setup(IN2, GPIO.OUT)
GPIO.setup(IN3, GPIO.OUT)
GPIO.setup(IN4, GPIO.OUT)

# Motor control functions
def move_forward():
    GPIO.output(IN1, GPIO.HIGH)
    GPIO.output(IN2, GPIO.LOW)
    GPIO.output(IN3, GPIO.HIGH)
    GPIO.output(IN4, GPIO.LOW)
    print("Moving forward")

def move_backward():
    GPIO.output(IN1, GPIO.LOW)
    GPIO.output(IN2, GPIO.HIGH)
    GPIO.output(IN3, GPIO.LOW)
    GPIO.output(IN4, GPIO.HIGH)
    print("Moving backward")

def turn_left():
    GPIO.output(IN1, GPIO.LOW)   # Left motor stops
    GPIO.output(IN2, GPIO.LOW)
    GPIO.output(IN3, GPIO.HIGH)  # Right motor moves forward
    GPIO.output(IN4, GPIO.LOW)
    print("Turning left")

def turn_right():
    GPIO.output(IN1, GPIO.HIGH)  # Left motor moves forward
    GPIO.output(IN2, GPIO.LOW)
    GPIO.output(IN3, GPIO.LOW)   # Right motor stops
    GPIO.output(IN4, GPIO.LOW)
    print("Turning right")

def stop():
    GPIO.output(IN1, GPIO.LOW)
    GPIO.output(IN2, GPIO.LOW)
    GPIO.output(IN3, GPIO.LOW)
    GPIO.output(IN4, GPIO.LOW)
    print("Stopping")

# Main loop for continuous command input
try:
    while True:
        # Accepting user input for motor command
        command = input("Enter command (forward, backward, left, right, stop): ").lower()

        if command == 'forward':
            move_forward()
        elif command == 'backward':
            move_backward()
        elif command == 'left':
            turn_left()
        elif command == 'right':
            turn_right()
        elif command == 'stop':
            stop()
        else:
            print("Invalid command")
        
        # Add a small delay to avoid too frequent command execution
        time.sleep(1)

except KeyboardInterrupt:
    print("Program stopped by user")

finally:
    GPIO.cleanup()
    print("GPIO cleanup done")
