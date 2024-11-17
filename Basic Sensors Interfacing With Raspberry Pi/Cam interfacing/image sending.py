import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.image import MIMEImage

# Sender username and password details
smtpUser = 'klintubusy@gmail.com'
smtpPass = 'vmtguzeftscgvhsl'

#Reciever details
toAdd = 'klintubusy@gmail.com'
fromAdd = smtpUser

#Email content
subject = 'TEST EMAIL using python'
header = 'To: {}'.format(toAdd) + '\nSubject: {}'.format(subject)
body = 'from python program sending EMAIL'

image_path = '/home/raspberrypi/Desktop/VR/cam/image.jpeg'

with open(image_path, 'rb') as f:
    image_data = f.read()

#create a MIMEImage container
image = MIMEImage(image_data)
image.add_header('Content-ID', '<image1>')

#MIMEMultipart message container
msg = MIMEMultipart()
msg['From'] = fromAdd
msg['To'] = toAdd
msg['Subject'] = subject

#Attach Text and Image
msg.attach(MIMEText(body, 'plain'))
msg.attach(image)

try:
    #SMTP server login
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
    s.quit()
