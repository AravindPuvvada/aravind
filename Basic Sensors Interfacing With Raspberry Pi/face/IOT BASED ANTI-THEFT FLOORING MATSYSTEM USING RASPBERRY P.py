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
import http.server
import socketserver
import threading

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

# Global variable to store detection status
detection_status = "Waiting for detection..."

# Function to update detection status
def update_detection_status(status):
    global detection_status
    detection_status = status

# Send email with optional image attachment
def send_email(subject, body, image_path=None):
    sender_email = 'aravindpuvvada196@gmail.com'
    sender_password = 'jwrn zfkr qqye xmfv'
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
        unique_name = os.path.basename(image_path)
        storage.child(unique_name).put(image_path)
        print("Image uploaded to Firebase")
    except Exception as e:
        print(f"Failed to upload image to Firebase: {e}")

# Set up GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
buzzer = 12
pir = 27
GPIO.setup(18, GPIO.OUT)
GPIO.setup(17, GPIO.OUT)

pwm17 = GPIO.PWM(17, 50)
pwm17.start(0)

pwm18 = GPIO.PWM(18, 50)
pwm18.start(0)

def setAngle(angle):
    duty = angle / 18.0 + 2.5
    GPIO.output(18, True)
    pwm18.ChangeDutyCycle(duty)
    time.sleep(1)
    GPIO.output(18, False)
    pwm18.ChangeDutyCycle(duty)

def servo(val):
    duty = val / 18.0 + 2.5
    GPIO.output(17, True)
    pwm17.ChangeDutyCycle(duty)
    time.sleep(1)
    GPIO.output(17, False)
    pwm17.ChangeDutyCycle(duty)

# Setup GPIO
GPIO.setup(buzzer, GPIO.OUT)
GPIO.setup(pir, GPIO.IN)

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

# Define a simple request handler for the web server
class MyHandler(http.server.SimpleHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/':
            self.send_response(200)
            self.send_header('Content-type', 'text/html')
            self.end_headers()
            self.wfile.write(bytes(f"""
                <!DOCTYPE html>
                <html>
                <head><title>Face Recognition Status</title></head>
                <body>
                    <h1>Face Recognition Status</h1>
                    <p>Status: {detection_status}</p>
                </body>
                </html>
            """, "utf-8"))
        else:
            self.send_response(404)
            self.end_headers()

# Start the HTTP server in a separate thread
def start_http_server():
    PORT = 8000
    with socketserver.TCPServer(("", PORT), MyHandler) as httpd:
        print(f"Serving at port {PORT}")
        httpd.serve_forever()

# Start the HTTP server thread
threading.Thread(target=start_http_server, daemon=True).start()

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

angle = 0
flag = 0
setAngle(0)

while True:
    pir_state = GPIO.input(pir)
    print("pir=" + str(pir_state))

    if pir_state == 0:
        print("Motion Detected!")

    if flag == 0:
        angle += 30
        setAngle(angle)
        time.sleep(1)
        print("Servo Angle:" + str(angle))
        if angle >= 90:
            flag = 1
    if flag == 1:
        angle -= 30
        setAngle(angle)
        time.sleep(1)
        print("Servo Angle:" + str(angle))
        if angle == 0:
            flag = 0

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
                update_detection_status("Unknown person detected")
                servo(0)
                buzzer_alert()
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
                update_detection_status(f"Known person: {name}")
                GPIO.output(buzzer, GPIO.LOW)
                servo(90)
                print("Door is open")
                
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
