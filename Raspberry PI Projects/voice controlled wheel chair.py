import RPi.GPIO as GPIO
import time
import Adafruit_GPIO.SPI as SPI
import speech_recognition as sr
import pyaudio

# Set up GPIO pins
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

TRIG_PIN = 23
ECHO_PIN = 24
red=26
green=1
buzzer=6
ir=18

GPIO.setup(ir,GPIO.IN)
GPIO.setup(TRIG_PIN, GPIO.OUT)
GPIO.setup(ECHO_PIN, GPIO.IN)
GPIO.setup(red,GPIO.OUT)
GPIO.setup(green,GPIO.OUT)
GPIO.setup(buzzer,GPIO.OUT)
GPIO.setup(green,GPIO.LOW)



def record_audio_to_text():
    recognizer = sr.Recognizer()
    with sr.Microphone() as source:
        print("Listening...")
        # Adjust the recognizer sensitivity to ambient noise
        recognizer.adjust_for_ambient_noise(source)
        # Listen to the microphone
        audio_data = recognizer.listen(source)
        try:
            # Convert the audio to text using Google Web Speech API
            text = recognizer.recognize_google(audio_data)
            print("Recognized Text: " + text)
            return text
        except sr.UnknownValueError:
            print("Google Speech Recognition could not understand the audio")
            return None
        except sr.RequestError:
            print("Could not request results from Google Speech Recognition service")
            return None



def get_distance():
    GPIO.output(TRIG_PIN, True)
    time.sleep(0.00001)
    GPIO.output(TRIG_PIN, False)

    while GPIO.input(ECHO_PIN) == 0:
        pulse_start = time.time()

    while GPIO.input(ECHO_PIN) == 1:
        pulse_end = time.time()

    pulse_duration = pulse_end - pulse_start
    distance = (pulse_duration * 34300) / 2

    return distance


m1_1 = 21
m1_2 = 20
m2_1 = 16
m2_2 = 12

GPIO.setup(m1_1, GPIO.OUT)
GPIO.setup(m1_2, GPIO.OUT)
GPIO.setup(m2_1, GPIO.OUT)
GPIO.setup(m2_2, GPIO.OUT)

# Define motor control functions
def stop():
    GPIO.output(m1_1, GPIO.LOW)
    GPIO.output(m1_2, GPIO.LOW)
    GPIO.output(m2_1, GPIO.LOW)
    GPIO.output(m2_2, GPIO.LOW)
    time.sleep(1)

    
def back():
    GPIO.output(m1_1, GPIO.HIGH)
    GPIO.output(m1_2, GPIO.LOW)
    GPIO.output(m2_1, GPIO.HIGH)
    GPIO.output(m2_2, GPIO.LOW)
    time.sleep(1)

    
def front():
    GPIO.output(m1_1, GPIO.LOW)
    GPIO.output(m1_2, GPIO.HIGH)
    GPIO.output(m2_1, GPIO.LOW)
    GPIO.output(m2_2, GPIO.HIGH)
    time.sleep(1)


def right():
    GPIO.output(m1_1, GPIO.LOW)
    GPIO.output(m1_2, GPIO.HIGH)
    GPIO.output(m2_1, GPIO.HIGH)
    GPIO.output(m2_2, GPIO.LOW)
    time.sleep(1)

def left():
    GPIO.output(m1_1, GPIO.HIGH)
    GPIO.output(m1_2, GPIO.LOW)
    GPIO.output(m2_1, GPIO.LOW)
    GPIO.output(m2_2, GPIO.HIGH)
    time.sleep(1)



while True:
    recognized_text = record_audio_to_text()
    dist = get_distance()
    print(f"Distance: {dist:.1f} cm")
    ir_state=GPIO.input(ir)
    print("ir:"+str(ir_state))

    time.sleep(1)
    if dist > 10:
        GPIO.output(red, GPIO.LOW)
        GPIO.output(buzzer, GPIO.LOW)
        GPIO.output(green, GPIO.HIGH)

        
    if dist<=10 and ir_state==0:
        print("Obstacle is found")
        GPIO.output(green, GPIO.LOW)
        GPIO.output(red, GPIO.HIGH)
        GPIO.output(buzzer, GPIO.HIGH)
        
    elif "stop" in recognized_text:
        stop()
    elif "back" in recognized_text.lower():
        back()
    elif "front" in recognized_text.lower():
        front()
    elif "right" in recognized_text.lower():
        right()
    elif "left" in recognized_text.lower():
        left()
    else:
        print("Invalid command / object is nearby you. Motors are stopped.")
        stop()

