import BlynkLib
from picamera import PiCamera
import time
import subprocess

# Blynk authentication token
auth_token = 'B1fJ2B59i7XisXqybChnN0vwyh80raoS'

# Initialize Blynk
blynk = BlynkLib.Blynk(auth_token)

# Initialize PiCamera
camera = PiCamera()

# Set camera resolution (adjust as needed)
camera.resolution = (640, 480)

# Variable to track streaming status
streaming = False

# Function to capture and stream video frames
def stream_video():
    # Open a video stream using FFmpeg
    stream_cmd = ['ffmpeg', '-f', 'rawvideo', '-pix_fmt', 'rgb24', '-s', '640x480', '-i', '-', '-f', 'mpeg1video', '-b', '800k', '-r', '20', 'http://localhost:8080/stream/video.mjpeg']
    stream_process = subprocess.Popen(stream_cmd, stdin=subprocess.PIPE)

    # Capture and stream video frames continuously
    while True:
        # Capture a frame from the camera
        camera.capture(stream_process.stdin, 'rgb')

# Run the Blynk update loop
while True:
    blynk.run()

    # Check for virtual write events on pin 1
    if blynk.virtual_read(0):
        value = blynk.virtual_read(1)
        if int(value[0]) == 1:
            if not streaming:
                print('Streaming started')
                stream_video()
                streaming = True
        else:
            if streaming:
                print('Streaming stopped')
                streaming = False

    # Add a slight delay to avoid excessive CPU usage
    time.sleep(0.1)
