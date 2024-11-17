import cv2
import face_recognition

# Initialize Pi Camera
video_capture = cv2.VideoCapture(0)

# Load a sample picture and learn how to recognize it
# Replace 'your_image.jpg' with the path to your image
known_image = face_recognition.load_image_file(r"/home/raspberrypi/Desktop/Aravind/basic sensor interfacing with raspberry pi/face/d6cea558-dd21-40ff-8ea9-162cce2cdec3.jpeg")
known_face_encoding = face_recognition.face_encodings(known_image)[0]

# Create an array of known face encodings and their names
known_face_encodings = [known_face_encoding]

known_face_names = ["Aravind"]

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
