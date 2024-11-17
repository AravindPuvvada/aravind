import speech_recognition as sr
import pyaudio
import RPi.GPIO as GPIO

# Set up GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
LED_PIN = 20
GPIO.setup(LED_PIN, GPIO.OUT)

# Function to record audio and convert it to text
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

# Main loop to continuously listen and control the LED
try:
    while True:
        recognized_text = record_audio_to_text()

        if recognized_text:

            
            if "light on" in recognized_text.lower():
                GPIO.output(LED_PIN, GPIO.HIGH)
                print("LED turned ON")
            elif "light off" in recognized_text.lower():
                GPIO.output(LED_PIN, GPIO.LOW)
                print("LED turned OFF")

except KeyboardInterrupt:
    print("Program exited by user")

finally:
    GPIO.cleanup()  # Clean up GPIO on exit
