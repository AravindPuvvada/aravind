import RPi.GPIO as GPIO
import time
import os
from datetime import datetime
from picamera import PiCamera
import pyrebase

# Firebase configuration
firebaseConfig = {
    'apiKey': "AIzaSyC4n8l9wRhUqgcRmWtmO5f7rjdk4AVqagM",
    'authDomain': "rpi-images-f1d81.firebaseapp.com",
    'databaseURL': "https://rpi-images-f1d81-default-rtdb.asia-southeast1.firebasedatabase.app",
    'projectId': "rpi-images-f1d81",
    'storageBucket': "rpi-images-f1d81.appspot.com",
    'messagingSenderId': "748154264731",
    'appId': "1:748154264731:web:03ecb90e27110a8bab7a3e",
    'measurementId': "G-5Z7DS54GT9"
}

# Initialize Firebase
firebase = pyrebase.initialize_app(firebaseConfig)
storage = firebase.storage()

# Initialize the camera once
camera = PiCamera()

try:
    while True:
        now = datetime.now()
        dt = now.strftime("%d%m%Y%H:%M:%S")
        image_name = dt + ".jpg"
        
        # Capture image
        camera.capture(image_name)
        print(f"{image_name} saved")
        
        # Upload to Firebase
        storage.child(image_name).put(image_name)
        print("Image sent to Firebase")

        # Remove the file locally
        os.remove(image_name)
        print("File removed from local storage")

        # Delay before the next image capture
        time.sleep(10)  # Set the delay (in seconds) as needed

except KeyboardInterrupt:
    print("Program terminated")

finally:
    # Always close the camera when done
    camera.close()
    GPIO.cleanup()
