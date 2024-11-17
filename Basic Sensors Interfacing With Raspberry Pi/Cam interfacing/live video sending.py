import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.base import MIMEBase
from email import encoders
import os
import picamera
import time
import subprocess

print('NOTE:while sending the video please delete the present video file before running this code ,it may cause an error')
# Set the output video file path
video_file = 'video.h264'

# Initialize the camera
camera = picamera.PiCamera()

try:
    # Start recording
    camera.start_recording(video_file)
    
    # Record for a specified duration (e.g., 10 seconds)
    camera.wait_recording(10)
    
    # Stop recording
    camera.stop_recording()
    
    print("Video recorded.")
    time.sleep(5)

finally:
    # Release the camera resources
    camera.close()

def h264_to_mp4(input_file, output_file):
    try:
        command = ["ffmpeg", "-i", input_file, "-c:v", "copy", output_file]
        subprocess.run(command, check=True)
        print(f"Video converted successfully: {output_file}")
    except subprocess.CalledProcessError as e:
        print(f"Error converting video: {e}")

if __name__ == "__main__":
    input_h264_file = "video.h264"
    output_mp4_file = "output_video.mp4"
    h264_to_mp4(input_h264_file, output_mp4_file)


def send_video_mail(sender_email, sender_password, recipient_email, video_file, body):
    """Sends a video file through email with a message.

    Args:
        sender_email (str): The sender's email address.
        sender_password (str): The sender's email password.
        recipient_email (str): The recipient's email address.
        video_file (str): The path to the video file to send.
        body (str): The message to send along with the video file.
    """

    # Create the email message
    message = MIMEMultipart()
    message['From'] = sender_email
    message['To'] = recipient_email
    message['Subject'] = 'Video from vr'

    # Attach the email body as plain text
    message.attach(MIMEText(body, 'plain'))

    # Read the video file and add it as an attachment
    with open(video_file, "rb") as f:
        attachment_data = f.read()

    filename = os.path.basename(video_file)
    part = MIMEBase('video', 'mp4')
    part.set_payload(attachment_data)
    encoders.encode_base64(part)
    part.add_header('Content-Disposition', f'attachment; filename="{filename}"')
    message.attach(part)

    # Connect to the email server and send the message
    server = smtplib.SMTP("smtp.gmail.com", 587)
    server.starttls()
    server.login(sender_email, sender_password)
    print('login successfully')
    server.sendmail(sender_email, recipient_email, message.as_string())
    print('Email sent successfully')
    server.quit()
    print('logout successfully')

if __name__ == "__main__":
    sender_email = "subanirehmanbaig@gmail.com"
    sender_password = "tnbo ljye lgia wfzv"  # Replace with your email password or use OAuth2 for security.
    recipient_email = input('enter reciver mail:' )
    video_file = "output_video.mp4"
    body = 'TEST MAIL'
    send_video_mail(sender_email, sender_password, recipient_email, video_file, body)
