# Import the OpenCV library, which is used for computer vision tasks.
import cv2

# Define a function named "cam_img" to capture images from the camera.
def cam_img():
    # Initialize a camera object to capture video frames. The argument '0' refers to the default camera (usually the built-in webcam).
    cam = cv2.VideoCapture(0)
 
    # Create an infinite loop to continuously capture frames from the camera.
    while True:
        # Read a frame from the camera. 'ret' is a boolean indicating if the frame was captured successfully, and 'image' contains the frame data.
        ret, image = cam.read()
             
        # Display the captured frame in a window titled 'Imagetest'.
        cv2.imshow('imagetest', image)
        
        # Wait for a key press and store the pressed key's ASCII value in 'k'. If no key is pressed, 'k' will be -1.
        k = cv2.waitKey(1)
        
        # If a key was pressed (key value is not -1), exit the loop.
        if k != -1:
            break 
    
    # Save the last captured image to a file named 'image.jpeg'.
    cv2.imwrite('image.jpeg', image)
    
    # Release the camera object, allowing other applications to use it.
    cam.release()
    
    # Close all OpenCV windows.
    cv2.destroyAllWindows()

# Call the 'cam_img' function to start capturing images from the camera.
cam_img()
