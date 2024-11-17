# Import the OpenCV library
import cv2

# Open the webcam using the default camera index (0)
cap = cv2.VideoCapture(0)

# Check if the webcam was opened successfully
if not cap.isOpened():
      print("Error: Could not open webcam.")
      exit()

# Get the width and height of the video frames
frame_width = int(cap.get(3))
frame_height = int(cap.get(4))

# Define the codec for the output video and create a VideoWriter object
fourcc = cv2.VideoWriter_fourcc(*'XVID')  # You can change the codec as needed

# Lower the frame rate to reduce the speed of the video
output_frame_rate = 10.0  # Change this value to your desired frame rate
out = cv2.VideoWriter('captured_video.avi', fourcc, output_frame_rate, (frame_width, frame_height))

# Start an infinite loop to continuously capture and process frames from the webcam
while True:
    # Read a frame from the webcam. 'ret' is a boolean indicating if the frame was read successfully, 'frame' contains the frame data.
    ret, frame = cap.read()

    # Check if the frame was read successfully
    if not ret:
        print("Error: Could not read frame.")
        break

    # Display the captured frame in a window titled 'Captured Video'
    cv2.imshow('Captured Video', frame)

    # Write the captured frame to the output video file
    out.write(frame)

    # Exit the loop if the 'q' key is pressed
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the resources: webcam and output video writer
cap.release()
out.release()

# Close all OpenCV windows
cv2.destroyAllWindows()
