
'''
This code is developed by STTMANI
'''
# Import the necessary library
import Adafruit_CharLCD as LCD
import RPi.GPIO as GPIO
import time

# Raspberry Pi GPIO pin configuration for the LCD
lcd_rs = 14
lcd_en = 15
lcd_d4 = 18
lcd_d5 = 23
lcd_d6 = 24
lcd_d7 = 25
lcd_backlight = 4

# LCD column and row dimensions (16x2 LCD)
lcd_columns = 16
lcd_rows = 2

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(lcd_rs, GPIO.OUT)
GPIO.setup(lcd_en, GPIO.OUT)
GPIO.setup(lcd_d4, GPIO.OUT)
GPIO.setup(lcd_d5, GPIO.OUT)
GPIO.setup(lcd_d6, GPIO.OUT)
GPIO.setup(lcd_d7, GPIO.OUT)
GPIO.setup(lcd_backlight, GPIO.OUT)


# Initialize the LCD using the defined pins
lcd = LCD.Adafruit_CharLCD(lcd_rs, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7,
                           lcd_columns, lcd_rows, lcd_backlight)

try:
    while True:
        # Clear the LCD display
        lcd.clear()
        # Display a message on the first row of the LCD
        lcd.set_cursor(0,0)
        lcd.message('STT-MANI')

        # Display a centered message on the second row
        lcd.set_cursor(3, 1)  # Move to the second row
        lcd.message('VIJAYAWADA')

        # Turn on the backlight
        lcd.set_backlight(1)

        # Pause for 2 seconds
        time.sleep(2)

        # Turn off the backlight
        lcd.set_backlight(0)
except KeyboardInterrupt:
    pass
finally:
    # Clean up the GPIO pins upon exiting
    lcd.clear()  # Clear the display before cleanup
    lcd.set_backlight(0)
    GPIO.cleanup()
    # Turn off the backlight before cleanup
