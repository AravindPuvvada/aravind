import cv2
import face_recognition
import os
import RPi.GPIO as GPIO
import Adafruit_MCP3008
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.mime.application import MIMEApplication
import time

# Set up MCP3008
def setup_mcp3008():
    CLK = 11
    MOSI = 10
    MISO = 9
    CS = 8
    mcp = Adafruit_MCP3008.MCP3008(clk=CLK, mosi=MOSI, miso=MISO, cs=CS)
    return mcp

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

# Set up GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
led = 18
buzzer = 12
ir = 1
pir = 17
IN1 = 6
IN2 = 13
relay=22
r1=20
r2=21
# Setup GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setup(IN1, GPIO.OUT)
GPIO.setup(IN2, GPIO.OUT)
GPIO.setup(led, GPIO.OUT)
GPIO.setup(buzzer, GPIO.OUT)
GPIO.setup(ir, GPIO.IN)
GPIO.setup(pir, GPIO.IN)
GPIO.setup(relay,GPIO.OUT)
GPIO.setup(r1,GPIO.OUT)
GPIO.setup(r2,GPIO.OUT)

# Initialize MCP3008
mcp = setup_mcp3008()

# Ensure the directory for saving images exists
save_dir = "/home/raspberrypi/Desktop/Aravind/unknown_persons/"
if not os.path.exists(save_dir):
    os.makedirs(save_dir)

# Function to save image of unknown person
def save_image(frame, name="unknown"):
    filename = os.path.join(save_dir, f"{name}.jpg")
    print(f"Saving image to {filename}")  # Debugging line
    cv2.imwrite(filename, frame)
    return filename


def open_door():
    GPIO.output(IN1, GPIO.HIGH)
    GPIO.output(IN2, GPIO.LOW)

def close_door():
    GPIO.output(IN1, GPIO.LOW)
    GPIO.output(IN2, GPIO.HIGH)

def stop_motor():
    GPIO.output(IN1, GPIO.LOW)
    GPIO.output(IN2, GPIO.LOW)




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
    ir_state = GPIO.input(ir)
        
    def read_analog_values(mcp):
        value = mcp.read_adc(0)
        val = mcp.read_adc(2)
        return value, val
        
    value, val = read_analog_values(mcp)

    print("ir=" + str(ir_state))
    print("pir=" + str(pir_state))
    print("sound-level=" + str(value))
    print("MQ-8=" + str(val))
    if pir_state == 0:
        print("Motion Detected!")
    if value > 400:
        print("Voice Detected!")
    if val > 350:
        print("Fire Detected")
        GPIO.output(relay,GPIO.HIGH)
        send_email(
                    subject="Security Alert: Fire is Detected",
                    body="Alert Fire is deteced in the building\n water sprinkler system is on.",
                )
    else:
        GPIO.output(relay,GPIO.LOW)

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

        if ir_state == 0 or pir_state == 0:
            if name == "Unknown":
                stop_motor()
                GPIO.output(led,GPIO.LOW)
                GPIO.output(r1, GPIO.LOW)
                GPIO.output(r2, GPIO.LOW)
                buzzer_alert()
                print("Unknown person detected")
                image_path = save_image(frame)
                send_email(
                    subject="Security Alert: Unknown Person Detected",
                    body="An unknown person has been detected by the security system.",
                    image_path=image_path
                )
                
            
                if pir==0:
                    image_path = save_image(frame)
                    send_email(
                    subject="Security Alert: Unknown Person Detected",
                    body="Somebody unknown person motion is detected.",
                    image_path=image_path
                    )

                value = mcp.read_adc(0)
                print(value)

                if value>200:
                    print("Unknown Person Voice Detected");
                    send_email(
                    subject="Security Alert: voice is  Detected",
                    body="Somebody unknown person voice is detected.",
                    )
                    
                
            else:
                GPIO.output(r1, GPIO.HIGH)
                GPIO.output(r2, GPIO.HIGH)
                GPIO.output(buzzer, GPIO.LOW)
                open_door()
                time.sleep(5)  # Keep the door open for 5 seconds
                stop_motor()
                time.sleep(1)
                close_door()
                time.sleep(5)  # Keep the door closed for 5 seconds
                stop_motor()
                GPIO.output(led,GPIO.LOW)
        else:
            GPIO.output(buzzer, GPIO.LOW)
            GPIO.output(r1, GPIO.LOW)
            GPIO.output(r2, GPIO.LOW)
            print("Lights and buzzer are off")

        cv2.rectangle(frame, (left, top), (right, bottom), (0, 0, 255), 2)
        cv2.rectangle(frame, (left, bottom - 35), (right, bottom), (0, 0, 255), cv2.FILLED)
        font = cv2.FONT_HERSHEY_DUPLEX
        cv2.putText(frame, name, (left + 6, bottom - 6), font, 1.0, (255, 255, 255), 1)

    cv2.imshow('Video', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

video_capture.release()
cv2.destroyAllWindows()
