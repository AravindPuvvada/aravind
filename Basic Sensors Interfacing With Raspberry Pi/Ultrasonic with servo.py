import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

TRIG_PIN = 23
ECHO_PIN = 24

GPIO.setwarnings(False)

GPIO.setup(TRIG_PIN, GPIO.OUT)
GPIO.setup(ECHO_PIN, GPIO.IN)
GPIO.setup(18,GPIO.OUT)

pwm=GPIO.PWM(18,50)
pwm.start(0)

def setAngle(angle):
    duty = angle / 18.0 + 2.5
    GPIO.output(18, True)
    pwm.ChangeDutyCycle(duty)
    time.sleep(1)
    GPIO.output(18, False)
    pwm.ChangeDutyCycle(duty)

def get_distance():
    GPIO.output(TRIG_PIN, True)
    time.sleep(0.00001)
    GPIO.output(TRIG_PIN, False)

    while GPIO.input(ECHO_PIN) == 0:
        pulse_start = time.time()

    while GPIO.input(ECHO_PIN) == 1:
        pulse_end = time.time()

    pulse_duration = pulse_end - pulse_start
    distance = (pulse_duration * 34300) / 2

    return distance

if __name__ == '__main__':
    try:
        while True:
            dist = get_distance()
            print(f"Distance: {dist:.1f} cm")
            time.sleep(1)
            if dist<10:
                setAngle(180)
                time.sleep(1)
            else:
                setAngle(0)
                time.sleep(1)

    except KeyboardInterrupt:
        print("Measurement stopped by the user")
    finally:
        GPIO.cleanup()

