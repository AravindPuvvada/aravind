import picamera
import time

# Initialize the camera
camera = picamera.PiCamera()

# Set the resolution (optional)
camera.resolution = (640, 480)

# Start recording
time.sleep(3)
camera.start_recording('video.h264')

# Record for a specified duration (e.g., 10 seconds)
camera.wait_recording(10)

# Stop recording
camera.stop_recording()

# Close the camera
camera.close()
