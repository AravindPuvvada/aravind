import time
import max30100
import os
import glob
import RPi.GPIO as GPIO
import Adafruit_GPIO.SPI as SPI
import smtplib
import requests
from email.mime.text import MIMEText

# Sensor and Email configuration
smtpUser = 'aravindpuvvada196@gmail.com'
smtpPass = 'mlzz objr sllt bocu'
toAdd = 'aravindpuvvada196@gmail.com'
fromAdd = smtpUser
subject = 'Health Report Alert!!'

# ThingSpeak configuration
THINGSPEAK_API_KEY = 'OEAM408LE5PGDU0A'
THINGSPEAK_URL = 'https://api.thingspeak.com/update'

# Threshold values
TEMP_THRESHOLD = 37.5  # Celsius
HR_THRESHOLD = 100      # BPM
SPO2_THRESHOLD = 90    # Percentage

# Initialize MAX30100 sensor
mx30 = max30100.MAX30100()
mx30.enable_spo2()

# Initialize DS18B20 temperature sensor
os.system('modprobe w1-gpio')
os.system('modprobe w1-therm')
base_dir = '/sys/bus/w1/devices/'
device_folders = glob.glob(base_dir + '28*')

if not device_folders:
    print("No DS18B20 sensor detected. Check connections.")
    exit()

device_file = device_folders[0] + '/w1_slave'

# Function to read the raw sensor data
def read_temp_raw():
    with open(device_file, 'r') as f:
        lines = f.readlines()
    return lines

# Function to parse the temperature
def read_temp():
    lines = read_temp_raw()
    while lines[0].strip()[-3:] != 'YES':
        time.sleep(0.2)
        lines = read_temp_raw()
    equals_pos = lines[1].find('t=')
    if equals_pos != -1:
        temp_string = lines[1][equals_pos + 2:]
        temp_c = float(temp_string) / 1000.0
        temp_f = temp_c * 9.0 / 5.0 + 32.0
        return temp_c, temp_f

while True:
    temp_c, temp_f = read_temp()
    print(f"Temperature: {temp_c:.2f} °C / {temp_f:.2f} °F")
    time.sleep(1)
    mx30.read_sensor()

    mx30.ir, mx30.red

    hb = int(mx30.ir / 100)
    spo2 = int(mx30.red / 100)

    if mx30.ir != mx30.buffer_ir:
        print("Heart-Rate:", hb)
    if mx30.red != mx30.buffer_red:
        print("SPO2:", spo2)

    # Send data to ThingSpeak
    try:
        payload = {
            'api_key': THINGSPEAK_API_KEY,
            'field1': hb,      # Heart Rate
            'field2': spo2,    # SPO2
            'field3': temp_c    # Temperature
        }
        response = requests.post(THINGSPEAK_URL, data=payload)
        if response.status_code == 200:
            print('Data sent to ThingSpeak successfully')
        else:
            print('Failed to send data to ThingSpeak:', response.status_code)
    except Exception as e:
        print('Error sending data to ThingSpeak:', e)

    # Check thresholds and send email if exceeded
    if temp_c > TEMP_THRESHOLD or hb > HR_THRESHOLD or spo2 < SPO2_THRESHOLD:
        # Compose the email body
        body = f'''
        Alert: Health parameters exceeded thresholds!
        Temperature: {temp_c:.2f} °C
        Heart-Rate: {hb} BPM
        SPO2: {spo2} %
        '''

        # Create MIMEText email object
        msg = MIMEText(body, 'plain', 'utf-8')
        msg['Subject'] = subject
        msg['From'] = fromAdd
        msg['To'] = toAdd

        try:
            # Send the email
            s = smtplib.SMTP('smtp.gmail.com', 587)
            s.starttls()
            s.login(smtpUser, smtpPass)
            print('Login successful')
            s.send_message(msg)
            print('Email sent successfully')
            s.quit()
        except Exception as e:
            print(e)
            print('Error sending email')

        time.sleep(1)
    time.sleep(2)  # Adjust this sleep time as necessary
