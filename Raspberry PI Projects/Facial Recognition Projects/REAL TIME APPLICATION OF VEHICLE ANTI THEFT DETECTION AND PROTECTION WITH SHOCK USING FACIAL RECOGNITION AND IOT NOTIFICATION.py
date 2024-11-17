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
switch=26


# Initialize I2C bus
bus = smbus.SMBus(1)  # For Raspberry Pi 2, 3, and 4

def initialize_adxl345():
    # Set the ADXL345 to measure mode
    bus.write_byte_data(ADXL345_ADDRESS, POWER_CTL, 0x08
                        )

def read_acceleration():
    # Read accelerometer data
    data = bus.read_i2c_block_data(ADXL345_ADDRESS, DATA_X0, 6)
    x = (data[1] << 8) | data[0]
    y = (data[3] << 8) | data[2]
    z = (data[5] << 8) | data[4]
    # Convert to signed values
    if x > 32767:
        x -= 65536
    if y > 32767:
        y -= 65536
    if z > 32767:
        z -= 65536
    return x, y, z

def detect_fall():
    initialize_adxl345()
    print("Monitoring for falls...")

    magnitudes = []

    # Reading acceleration once
    x, y, z = read_acceleration()
    print(f"X: {x}, Y: {y}, Z: {z}")

    magnitude = math.sqrt(x**2 + y**2 + z**2)
    print(f"Magnitude: {magnitude}")

    magnitudes.append(magnitude)
    if len(magnitudes) > 5:  # Keep only the last 5 readings
        magnitudes.pop(0)

    avg_magnitude = sum(magnitudes) / len(magnitudes)
    print(f"Average Magnitude: {avg_magnitude}")

    # Adjusted threshold values
    threshold_fall = 15.0  # Free fall detection (1.5g)
    threshold_impact = 300.0  # Impact detection (4g)

    # Detect fall
    if avg_magnitude < threshold_fall:
        print("Fall detected! Average Magnitude:", avg_magnitude)
        

    # Detect impact after a fall
    if avg_magnitude > threshold_impact:
        print("Impact detected! Average Magnitude:", avg_magnitude)
        
        send_email(
                subject="Security Alert: Your Car is theft by someone!!",
                body="Somebody tries to theft your car",
            )
        buzzer_alert()
        time.sleep(3)

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
relay = 20
relay1 = 21
sw = 17
# Setup GPIO
GPIO.setup(buzzer, GPIO.OUT)
GPIO.setup(relay, GPIO.OUT)
GPIO.setup(switch,GPIO.IN)
GPIO.setup(relay1, GPIO.OUT)
GPIO.setup(sw,GPIO.IN)
relay_state = False
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


relay_state = False  # Variable to keep track of relay state
last_button_state = GPIO.input(sw)  # Initial button state
debounce_time = 0.2  # Debounce time for button press

def toggle_relay():
    global relay_state, last_button_state
    current_button_state = GPIO.input(sw)

    # Check if button is pressed (falling edge detection)
    if current_button_state == 0 and last_button_state == 1:
        time.sleep(debounce_time)  # Debounce delay
        relay_state = not relay_state  # Toggle relay state
        GPIO.output(relay1, relay_state)
        print("Relay is ON" if relay_state else "Relay is OFF")

    last_button_state = current_button_state  # Update button state




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
    detect_fall()
    switchstate=GPIO.input(switch)
    if switchstate==1:
        print("Door is open")
        GPIO.output(relay,GPIO.HIGH)
        time.sleep(5)
    else:
        GPIO.output(relay,GPIO.LOW)

    toggle_relay()
    


        
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


        

        if name == "Unknown":
      
            buzzer_alert()
            detect_fall()
            GPIO.output(relay, GPIO.LOW)
            time.sleep(1)
            print("Door is Locked")
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
            GPIO.output(relay, GPIO.HIGH)
            print("Door is open")
            time.sleep(7)
            GPIO.output(relay, GPIO.LOW)
                
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

