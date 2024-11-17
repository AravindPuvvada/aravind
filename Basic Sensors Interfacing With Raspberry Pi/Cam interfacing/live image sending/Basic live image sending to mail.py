import smtplib
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
  cam.annotate_text = 'Raspberry pi'
  cam.capture('/home/raspberrypi/Desktop/VR/cam/image.jpeg')
  sleep(2)
  cam.stop_preview()
  sleep(5)


def send_mail():
 try:
    s = smtplib.SMTP('smtp.gmail.com', 587)
    s.ehlo()
    s.starttls()
    s.ehlo()
    s.login(smtpUser, smtpPass)
    print('login successfully')
    s.sendmail(fromAdd, toAdd, msg.as_string())
    print('Email sent successfully')
 except Exception as e:
    print(e)
    print('Error sending email')
 finally:
    quit()
cam_img()


smtpUser = 'subanirehmanbaig@gmail.com'
smtpPass = 'tnbo ljye lgia wfzv'
toAdd = 'klintubusy@gmail.com'
fromAdd = smtpUser

subject = 'TEST EMAIL using python'
header = 'To: {}'.format(toAdd) + '\nSubject: {}'.format(subject)

body = 'HI PI User'

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



send_mail()

