import cv2
import face_recognition
import os
import RPi.GPIO as GPIO
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.application import MIMEApplication
import time
from datetime import datetime
import pyrebase
import math
import smbus
ADXL345_ADDRESS = 0x53
DATA_X0 = 0x32
DATA_Y0 = 0x34
DATA_Z0 = 0x36
POWER_CTL = 0x2D

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

# Send email with optional image attachment
def send_email(subject, body, image_path=None):
    sender_email = 'aravindpuvvada196@gmail.com'
    sender_password = 'mlzz objr sllt bocu'
    receiver_email = 'aravindpuvvada196@gmail.com'
    
    msg = MIMEMultipart()
    msg['From'] = sender_email
    msg['To'] = receiver_email
    msg['Subject'] = subject
    
    msg.attach(MIMEText(body, 'plain'))

    if image_path and os.path.isfile(image_path):
        try:
            with open(image_path, 'rb') as attachment:
                part = MIMEApplication(attachment.read(), Name=os.path.basename(image_path))
                part['Content-Disposition'] = f'attachment; filename="{os.path.basename(image_path)}"'
                msg.attach(part)
        except Exception as e:
            print(f"Failed to attach image: {e}")
    else:
        print("No valid image path provided or image file does not exist.")
    
    try:
        server = smtplib.SMTP('smtp.gmail.com', 587)
        server.starttls()
        server.login(sender_email, sender_password)
        server.sendmail(sender_email, receiver_email, msg.as_string())
        server.quit()
        print("Email sent successfully!")
    except Exception as e:
        print(f"Failed to send email: {e}")

# Upload image to Firebase
def upload_image_to_firebase(image_path):
    try:
        # Ensure unique filenames by using timestamps
        unique_name = os.path.basename(image_path)
        storage.child(unique_name).put(image_path)
        print("Image uploaded to Firebase")
    except Exception as e:
        print(f"Failed to upload image to Firebase: {e}")

# Set up GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
buzzer = 12
TRIG_PIN = 23
ECHO_PIN = 24
ir=17
ir1=27
pir=22
GPIO.setup(pir,GPIO.OUT)
GPIO.setup(ir,GPIO.IN)
GPIO.setup(ir1,GPIO.IN)
GPIO.setup(TRIG_PIN, GPIO.OUT)
GPIO.setup(ECHO_PIN, GPIO.IN)
m1_1 = 26
m1_2 = 19
m2_1 = 13
m2_2 = 6

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
    time.sleep(2)
def back():
    GPIO.output(m1_1, GPIO.HIGH)
    GPIO.output(m1_2, GPIO.LOW)
    GPIO.output(m2_1, GPIO.HIGH)
    GPIO.output(m2_2, GPIO.LOW)
    print("Robo is Moving back")
    time.sleep(1)
def front():
    GPIO.output(m1_1, GPIO.LOW)
    GPIO.output(m1_2, GPIO.HIGH)
    GPIO.output(m2_1, GPIO.LOW)
    GPIO.output(m2_2, GPIO.HIGH)
    print("Robo is Moving forwarding")
    time.sleep(1)
def turn_right():
    GPIO.output(m1_1, GPIO.LOW)
    GPIO.output(m1_2, GPIO.HIGH)
    GPIO.output(m2_1, GPIO.HIGH)
    GPIO.output(m2_2, GPIO.LOW)
    print("Robo is Moving right")
    time.sleep(1)

def turn_left():
    GPIO.output(m1_1, GPIO.HIGH)
    GPIO.output(m1_2, GPIO.LOW)
    GPIO.output(m2_1, GPIO.LOW)
    GPIO.output(m2_2, GPIO.HIGH)
    print("Robo is Moving left")

    time.sleep(1)


def get_distance():
    GPIO.output(TRIG_PIN, True)
    time.sleep(0.00001)
    GPIO.output(TRIG_PIN, False)

    pulse_start = time.time()
    timeout = pulse_start + 1  # Timeout of 1 second

    # Wait for the pulse to start
    while GPIO.input(ECHO_PIN) == 0:
        pulse_start = time.time()
        if time.time() > timeout:
            print("Timeout: No pulse received.")
            return -1  # Return -1 to indicate error

    pulse_end = time.time()
    timeout = pulse_end + 1  # Timeout for the pulse to end

    # Wait for the pulse to end
    while GPIO.input(ECHO_PIN) == 1:
        pulse_end = time.time()
        if time.time() > timeout:
            print("Timeout: Pulse did not end.")
            return -1  # Return -1 to indicate error

    pulse_duration = pulse_end - pulse_start
    distance = (pulse_duration * 34300) / 2

    return distance




# Setup GPIO
GPIO.setup(buzzer, GPIO.OUT)
# Ensure the directory for saving images exists
save_dir = "/home/raspberrypi/Desktop/Aravind/unknown_persons/"
if not os.path.exists(save_dir):
    os.makedirs(save_dir)

# Function to save image of unknown person
def save_image(frame, name="unknown"):
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    filename = os.path.join(save_dir, f"{name}_{timestamp}.jpg")
    print(f"Saving image to {filename}")  # Debugging line
    cv2.imwrite(filename, frame)
    return filename

# Function to control the buzzer
def buzzer_alert():
    GPIO.output(buzzer, GPIO.HIGH)
    time.sleep(0.6)
    GPIO.output(buzzer, GPIO.LOW)
    time.sleep(0.6)
    GPIO.output(buzzer, GPIO.HIGH)
    time.sleep(0.6)
    GPIO.output(buzzer, GPIO.LOW)
    time.sleep(0.6)
    GPIO.output(buzzer, GPIO.HIGH)
    time.sleep(0.6)
    GPIO.output(buzzer, GPIO.LOW)






# Initialize Pi Camera
video_capture = cv2.VideoCapture(0)

# Path to the folder containing the images of known faces
known_faces_dir = "/home/raspberrypi/Desktop/Aravind/basic sensor interfacing with raspberry pi/face/images"

# Create arrays to hold known face encodings and names
known_face_encodings = []
known_face_names = []

# Loop through each image file in the known faces directory
for image_name in os.listdir(known_faces_dir):
    image_path = os.path.join(known_faces_dir, image_name)
    known_image = face_recognition.load_image_file(image_path)
    face_encoding = face_recognition.face_encodings(known_image)[0]
    known_face_encodings.append(face_encoding)
    name = os.path.splitext(image_name)[0]
    known_face_names.append(name)

while True:
    pir_state = GPIO.input(pir)

    print("pir=" + str(pir_state))
    if pir_state == 0:
        print("Motion Detected!")
    dist = get_distance()
    print(f"Distance: {dist:.1f} cm")
    left_ir=GPIO.input(ir)
    right_ir=GPIO.input(ir1)
    print("Left IR:"+str(left_ir))
    print("Right IR:"+str(right_ir))
    if dist > 10:  # Safe to move forward
        front()
    else:  # Obstacle detected
        if left_ir == 0 and right_ir == 0:
            # If both IR sensors detect obstacles, back up
            print("Both IR sensors triggered: Moving back")
            stop()
            back()
            time.sleep(1)
        elif left_ir == 0:
            # If left IR detects an obstacle, turn right
            print("Left IR triggered: Turning right")
            stop()
            turn_right()
            time.sleep(1)
        elif right_ir == 0:
            # If right IR detects an obstacle, turn left
            print("Right IR triggered: Turning left")
            stop()
            turn_left()
            time.sleep(1)
        else:
            # If no IR sensors are triggered, but distance is less than threshold
            print("Obstacle detected, stopping")
            stop()
            time.sleep(1)
            
    ret, frame = video_capture.read()
    rgb_frame = frame[:, :, ::-1]
    face_locations = face_recognition.face_locations(rgb_frame)
    face_encodings = face_recognition.face_encodings(rgb_frame, face_locations)

    for (top, right, bottom, left), face_encoding in zip(face_locations, face_encodings):
        matches = face_recognition.compare_faces(known_face_encodings, face_encoding)
        name = "Unknown"
        face_distances = face_recognition.face_distance(known_face_encodings, face_encoding)
        best_match_index = face_distances.argmin()

        if matches[best_match_index]:
            name = known_face_names[best_match_index]


        

        if pir_state == 0:
            if name == "Unknown":
                buzzer_alert()
                print("Unknown person detected")
                image_path = save_image(frame)
                upload_image_to_firebase(image_path)  # Upload image to Firebase
                send_email(
                    subject="Security Alert: Unknown Person Detected",
                    body="An unknown person has been detected by the security system.",
                    image_path=image_path
                )
            else:
                GPIO.output(buzzer, GPIO.LOW)
                
        else:
            GPIO.output(buzzer, GPIO.LOW)



            
        cv2.rectangle(frame, (left, top), (right, bottom), (0, 0, 255), 2)
        cv2.rectangle(frame, (left, bottom - 35), (right, bottom), (0, 0, 255), cv2.FILLED)
        font = cv2.FONT_HERSHEY_DUPLEX
        cv2.putText(frame, name, (left + 6, bottom - 6), font, 1.0, (255, 255, 255), 1)

    cv2.imshow('Video', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

video_capture.release()
cv2.destroyAllWindows()
GPIO.cleanup()

