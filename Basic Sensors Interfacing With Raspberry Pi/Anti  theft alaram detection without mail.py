import cv2
import face_recognition
import os
import RPi.GPIO as GPIO
import Adafruit_MCP3008
def setup_mcp3008():
    CLK=11
    MOSI=10
    MISO=9
    CS=8
    mcp = Adafruit_MCP3008.MCP3008(clk=CLK, mosi=MOSI, miso=MISO, cs=CS)
    return mcp


GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
led=1
buzzer=12
ir=16
pir=17
GPIO.setup(led,GPIO.OUT)
GPIO.setup(buzzer,GPIO.OUT)
GPIO.setup(ir,GPIO.IN)
GPIO.setup(pir,GPIO.IN)
value=0
val=0

def buzzer():
    GPIO.output(buzzer,HIGH)
    time.sleep(0.6)
    GPIO.output(buzzer,LOW)
    GPIO.output(buzzer,HIGH)
    time.sleep(0.6)
    GPIO.output(buzzer,LOW)
    GPIO.output(buzzer,HIGH)
    time.sleep(0.6)
    GPIO.output(buzzer,LOW)
    GPIO.output(buzzer,HIGH)
    time.sleep(0.6)
    GPIO.output(buzzer,LOW)
# Initialize Pi Camera
video_capture = cv2.VideoCapture(0)

# Path to the folder containing the images of known faces
known_faces_dir = r"/home/raspberrypi/Desktop/Aravind/basic sensor interfacing with raspberry pi/face/images"

# Create arrays to hold known face encodings and names
known_face_encodings = []
known_face_names = []

# Loop through each image file in the known faces directory
for image_name in os.listdir(known_faces_dir):
    # Load the image
    image_path = os.path.join(known_faces_dir, image_name)
    known_image = face_recognition.load_image_file(image_path)
    
    # Get the face encoding for the current image
    face_encoding = face_recognition.face_encodings(known_image)[0]
    
    # Append the face encoding to the list
    known_face_encodings.append(face_encoding)
    
    # Get the name from the image filename (assuming the name is the part before the file extension)
    name = os.path.splitext(image_name)[0]
    
    # Append the name to the list
    known_face_names.append(name)

while True:
    # Capture a single frame from the Pi Camera
    ret, frame = video_capture.read()

    # Convert the image from BGR color (which OpenCV uses) to RGB color (which face_recognition uses)
    rgb_frame = frame[:, :, ::-1]

    # Find all the faces and face encodings in the current frame of video
    face_locations = face_recognition.face_locations(rgb_frame)
    face_encodings = face_recognition.face_encodings(rgb_frame, face_locations)

    for (top, right, bottom, left), face_encoding in zip(face_locations, face_encodings):
        # See if the face is a match for the known face(s)
        matches = face_recognition.compare_faces(known_face_encodings, face_encoding)

        name = "Unknown"

        # Use the known face with the smallest distance to the new face
        face_distances = face_recognition.face_distance(known_face_encodings, face_encoding)
        best_match_index = face_distances.argmin()

        if matches[best_match_index]:
            name = known_face_names[best_match_index]
        pir_state=GPIO.input(pir)
        ir_state=GPIO.input(ir)
        def read_analog_values(mcp):
            value = mcp.read_adc(0)
            val= mcp.read_adc(2)


        print("ir="+str(ir_state))
        print("pir="+str(pir_state))
        print("sound-level="+str(value))
        print("MQ-8"+str(val))

        
        if pir_state==0:
            print("Motion Detected!")
        if value>400:
            print("Voice Detected!")

        if val>500:
            print("Fire is Detected")


        if ir_state==0 or pir_state==0:
            if name=="Unknown":
                GPIO.output(led,GPIO.LOW)
                
                print("Unknown person is detected")
            else:
                GPIO.output(led,GPIO.HIGH)
                GPIO.output(buzzer,GPIO.LOW)
        else:
            GPIO.output(buzzer,GPIO.LOW)
            GPIO.output(led,GPIO.LOW)
        

        # Draw a box around the face
        cv2.rectangle(frame, (left, top), (right, bottom), (0, 0, 255), 2)

        # Draw a label with a name below the face
        cv2.rectangle(frame, (left, bottom - 35), (right, bottom), (0, 0, 255), cv2.FILLED)
        font = cv2.FONT_HERSHEY_DUPLEX
        cv2.putText(frame, name, (left + 6, bottom - 6), font, 1.0, (255, 255, 255), 1)

    # Display the resulting image
    cv2.imshow('Video', frame)

    # Hit 'q' on the keyboard to quit
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    

# Release the camera
video_capture.release()
cv2.destroyAllWindows()

