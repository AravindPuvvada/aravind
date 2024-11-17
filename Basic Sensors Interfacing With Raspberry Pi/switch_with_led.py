import RPi.GPIO as GPIO
import time

# Set up GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
buzzer = 12
relay1 = 21
sw = 17

# Set up GPIO pins
GPIO.setup(buzzer, GPIO.OUT)
GPIO.setup(relay1, GPIO.OUT)
GPIO.setup(sw, GPIO.IN, pull_up_down=GPIO.PUD_UP)  # Use pull-up resistor for the button

# Initialize relay state
relay_state = False

# Toggle function for relay
def toggle_relay():
    global relay_state
    relay_state = not relay_state  # Toggle the state
    GPIO.output(relay1, GPIO.HIGH if relay_state else GPIO.LOW)
    print(f"Relay is {'ON' if relay_state else 'OFF'}")

# Main loop
try:
    while True:
        button_state = GPIO.input(sw)

        if button_state == GPIO.LOW:  # Button is pressed (assuming active-low)
            toggle_relay()
            time.sleep(0.5)  # Debounce delay to prevent multiple toggles
finally:
    GPIO.cleanup()
