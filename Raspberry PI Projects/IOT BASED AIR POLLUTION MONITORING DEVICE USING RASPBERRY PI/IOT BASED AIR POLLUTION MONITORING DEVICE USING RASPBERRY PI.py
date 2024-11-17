import requests
import time
import RPi.GPIO as GPIO
import Adafruit_DHT
import Adafruit_GPIO.SPI as SPI
import Adafruit_MCP3008
import Adafruit_CharLCD as LCD

# API Configuration
api_key = "S735ZEHI88Z2JL3D"
api_url = "https://api.thingspeak.com/update.json"

# GPIO Configuration
GPIO.setmode(GPIO.BCM)

# DHT Sensor Configuration
val = Adafruit_DHT.DHT11
DHT_PIN = 4

# LCD Configuration
lcd_rs = 14
lcd_en = 15
lcd_d4 = 18
lcd_d5 = 23
lcd_d6 = 24
lcd_d7 = 25
lcd_backlight = 4
lcd_columns = 16
lcd_rows = 2

# MCP3008 Configuration
CLK = 11
MOSI = 10
MISO = 9
CS = 8

# Initialize the LCD
lcd = LCD.Adafruit_CharLCD(lcd_rs, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7,
                           lcd_columns, lcd_rows, lcd_backlight)

# Print project name only once
lcd.set_cursor(1, 0)
lcd.message('IOT Based Air')
lcd.set_cursor(3, 1)
lcd.message('Pollution')
time.sleep(4)

# Initialize the MCP3008 ADC
mcp = Adafruit_MCP3008.MCP3008(clk=CLK, mosi=MOSI, miso=MISO, cs=CS)

try:
    while True:
        lcd.clear()
        
        # Read from DHT sensor
        hum, temp = Adafruit_DHT.read(val, DHT_PIN)
        mq135 = mcp.read_adc(0)  # Read the MQ-135 sensor
        
        # Display temperature and humidity on the same line
        if temp is not None and hum is not None:
            lcd.set_cursor(0, 0)
            lcd.message(f'Temperature:{temp:.1f}C')
            lcd.set_cursor(0, 1)
            lcd.message(f'Humidity:{hum:.1f}%')
            time.sleep(2)

            # Print sensor values to console
            print(f'Temperature: {temp:.1f}C  Humidity: {hum:.1f}%  MQ135 Value: {mq135}')

            # Prepare data for ThingSpeak
            data = {
                "api_key": api_key,
                "field1": temp,
                "field2": hum,
                "field3": mq135
            }

            # Send data to ThingSpeak
            response = requests.post(api_url, data=data)
            if response.status_code == 200:
                print("Data sent successfully to ThingSpeak.")
            else:
                print("Failed to send data. Status code:", response.status_code)
            lcd.clear()
            lcd.set_cursor(2, 0)
            lcd.message(f'MQ-135:{mq135}')
            if mq135>600:
                lcd.set_cursor(1,1)
                lcd.message('Toxic Gas')
            time.sleep(2)
        else:
            print("Failed to get a reading from the sensor. Trying again...")
            lcd.set_cursor(0, 0)
            lcd.message('Sensor Error')

        time.sleep(1)  # Adjust the sleep interval as needed
except KeyboardInterrupt:
    print("Program terminated by user.")
finally:
    GPIO.cleanup()
