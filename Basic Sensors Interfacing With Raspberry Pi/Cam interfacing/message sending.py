import smtplib

smtpUser = 'subanirehmanbaig@gmail.com'
smtpPass = 'tnbo ljye lgia wfzv'

receiver_addresses = ['aravindpuvvada196@gmail.com']

from_add = smtpUser

subject = 'TEST EMAIL using python'

body = 'hii'

try:
    s = smtplib.SMTP('smtp.gmail.com', 587)
    s.ehlo()
    s.starttls()
    s.ehlo()
    s.login(smtpUser, smtpPass)
    print('login successfully')
    for x in receiver_addresses:
        header = 'To: {}'.format(x) + '\nSubject: {}'.format(subject)
        s.sendmail(from_add, x, header + '\n\n' + body)
    print('Email sent successfully')
except Exception as e:
    print(e)
    print('Error sending email')
finally:
    s.quit()
