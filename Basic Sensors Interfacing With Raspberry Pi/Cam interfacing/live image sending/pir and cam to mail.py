import smtplib
import time
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
pir=17
GPIO.setup(pir,GPIO.IN)
from email.mime.multipart import MIMEMultipart
from email.mime.image import MIMEImage
from email.mime.text import MIMEText
import picamera
from time import sleep
def cam_img():
    
    cam = picamera.PiCamera()
    cam.resolution = (1024, 768)
    cam.brightness = 60
    cam.start_preview()
    cam.annotate_text = 'HI pi user'
    cam.capture('/home/raspberrypi/Desktop/VR/cam/image.jpeg')
    cam.capture('/home/raspberrypi/Desktop/VR/cam/image.jpeg')
    sleep(2)
    cam.stop_preview()
    sleep(5)
    
  


def send_mail():
    
    s = smtplib.SMTP('smtp.gmail.com', 587)
    s.ehlo()
    s.starttls()
    s.ehlo()
    s.login(smtpUser, smtpPass)
    print('login successfully')
    s.sendmail(fromAdd, toAdd, msg.as_string())
    print('Email sent successfully')

smtpUser = 'subanirehmanbaig@gmail.com'
smtpPass = 'tnbo ljye lgia wfzv'
toAdd = 'aravindpuvvada196@gmail.com'
fromAdd = smtpUser

subject = 'TEST EMAIL using python'
header = 'To: {}'.format(toAdd) + '\nSubject: {}'.format(subject)

body = 'Hii this is the image'

image_path = '/home/raspberrypi/Desktop/VR/cam/image.jpeg'

with open(image_path, 'rb') as f:
   image_data = f.read()

  # Check if the image file is in UTF-8 encoding
if not isinstance(image_data, bytes):
    raise UnicodeDecodeError('Image file is not in UTF-8 encoding')

image = MIMEImage(image_data)
image.add_header('Content-ID', '<image1>')

msg = MIMEMultipart()
msg['From'] = fromAdd
msg['To'] = toAdd
msg['Subject'] = subject

msg.attach(MIMEText(body, 'plain'))
msg.attach(image)

while True:
    val=GPIO.input(pir)
    if val==0:
        print("Motion Detected")
        cam_img()
        send_mail()
        time.sleep(2)
    else:
        print("No motion Detected")
        time.sleep(1)

        

