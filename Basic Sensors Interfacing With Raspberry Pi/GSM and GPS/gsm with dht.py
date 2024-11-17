import os
import sys
import RPi.GPIO as  GPIO
import time		         
import serial               
import Adafruit_DHT
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
DHT_PIN=4
val=Adafruit_DHT.DHT11

ser = serial.Serial ("/dev/ttyUSB0",timeout=1)
temp,hum=Adafruit_DHT.read(val,DHT_PIN)
print(f'Temperature:{temp:.1f}  Humidity{hum:.1f}')


def send_sms():
    print("sending SMS..")

    cmd='AT\r\n'
    ser.write(cmd.encode())
    time.sleep(2)
    rcv = ser.read(20)
    print(rcv)
    cmd='AT+CMGF=1\r\n'
    ser.write(cmd.encode())
    time.sleep(2)
    rcv = ser.read(20)
    print(rcv)                                             
    phno="9494956343"                          
    cmd='AT+CMGS="'+str(phno)+'"\r\n'
    ser.write(cmd.encode())
    rcv = ser.read(20)
    print(rcv)                        
    time.sleep(1)
    cmd=str(hum)
    ser.write(cmd.encode())  # Message
    
    #ser.write(msg.encode())  # Message
    time.sleep(1)
    cmd = "\x1A"
    ser.write(cmd.encode()) # Enable to send SMS
    time.sleep(10)
    print('SMS Sent')
    time.sleep(1)

send_sms()
