import Adafruit_DHT
import time
val=Adafruit_DHT.DHT11
while True:
    temp,hum=Adafruit_DHT.read(val,DHT_PIN)
    if temp is not None and hum is not None:
        print(F'Temperature:{temp:.1f}C  Humidity:{hum:.1f}%')
    else:
        print('Failed to initialize the DHT11 Snesor')
    time.sleep(1)          
