import os
import sys
import RPi.GPIO as  GPIO
import time		         
import serial               

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

ser = serial.Serial ("/dev/ttyUSB0",timeout=1)


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
    cmd='Hello from the sttmani'
    ser.write(cmd.encode())  # Message
    
    #ser.write(msg.encode())  # Message
    time.sleep(1)
    cmd = "\x1A"
    ser.write(cmd.encode()) # Enable to send SMS
    time.sleep(10)
    print('SMS Sent')
    time.sleep(1)

send_sms()
