import io
import picamera
import logging
import socketserver
from threading import Condition
from http import server
import RPi.GPIO as GPIO
import Adafruit_DHT
import Adafruit_MCP3008 
import Adafruit_GPIO.SPI as SPI 
import Adafruit_CharLCD as LCD
from time import sleep

#Initialize the GPIO pins
servo_pin = 18 # Adjust the GPIO pin number accordingly
sensor_pin = 4 #set the  to read sensor data

CLK = 11
MOSI = 10
MISO = 9
CS = 8
DHT_sensor = Adafruit_DHT.DHT11

# Raspberry Pi GPIO pin configuration:
lcd_rs = 26
lcd_en = 19
lcd_d4 = 13
lcd_d5 = 6
lcd_d6 = 5
lcd_d7 = 0
lcd_backlight = 4

# LCD column and row size (16x2 LCD)
lcd_columns = 16
lcd_rows = 2

 
GPIO.setmode(GPIO.BCM)#set the mode as GPIO.BCM or GPIO.BOARD to access the GPIO pins
GPIO.setwarnings(False)#to disable GPIO warnings

# Initialize the LCD using the pins above.
lcd = LCD.Adafruit_CharLCD(lcd_rs, lcd_en, lcd_d4, lcd_d5, lcd_d6, lcd_d7,
                           lcd_columns, lcd_rows, lcd_backlight)


mcp = Adafruit_MCP3008.MCP3008(clk=CLK, mosi=MOSI, miso=MISO, cs=CS)

# Set up GPIO for servo control
GPIO.setup(servo_pin, GPIO.OUT)#set the servo_pin as output
sensor_pim = 17
def setAngle(angle):
    pwm = GPIO.PWM(servo_pin, 50)
    pwm.start(0)
    # Calculate the duty cycle based on the angle (0 to 180 degrees)
    # The duty cycle should be in the range of 2.5 to 12.5
    duty = angle / 18.0 + 2.5
    # Turn on the servo by setting the GPIO output to HIGH
    GPIO.output(servo_pin, True)
    # Apply the duty cycle to the PWM signal to move the servo to the specified angle
    pwm.ChangeDutyCycle(duty)
    # Wait for a moment to let the servo move to the desired position
    sleep(0.4)
    # Turn off the servo by setting the GPIO output to LOW
    GPIO.output(servo_pin, False)
    # Apply the same duty cycle again to keep the servo in position
    pwm.ChangeDutyCycle(duty)
    pwm.stop()



# HTML page with embedded JavaScript
PAGE = """\
<!DOCTYPE html>
<html>
<head>
    <title>Raspberry Pi - Surveillance Camera</title>
    <style>
        body {
            background-color: #f0f8ff; /* Light blue background for a soothing effect */
            font-family: Arial, sans-serif;
            color: #333;
            margin: 0;
            padding: 0;
        }

        h1 {
            color: #333;
            margin-top: 20px;
        }

        h4 {
            color: #e63946; /* Red color for sensor values */
            font-size: 18px;
            margin: 0;
            font-weight: bold;
        }

        .sensor-container {
            display: flex;
            justify-content: space-around; /* Distribute boxes evenly across the screen */
            gap: 20px;
            margin: 30px auto;
            max-width: 80%;
        }

        .sensor-box {
            border: 2px solid #ccc;
            padding: 15px;
            height: 100px;
            width: 280px;
            background-color: #98c1d9; /* Slightly darker blue for sensor boxes */
            border-radius: 10px;
            display: flex;
            align-items: center;
            justify-content: center;
            box-shadow: 2px 2px 10px rgba(0, 0, 0, 0.1);
        }

        .sensor-box h4 {
            text-align: center;
            width: 100%;
        }

        #camera-container {
            text-align: center;
            margin: 20px;
        }

        #camera-container img {
            border-radius: 10px;
            box-shadow: 0px 0px 15px rgba(0, 0, 0, 0.2);
        }

        form {
            margin-top: 20px;
            font-size: 16px;
        }

        input[type="number"] {
            padding: 5px;
            font-size: 16px;
            border: 1px solid #ccc;
            border-radius: 5px;
            width: 60px;
            text-align: center;
            margin-right: 10px;
        }

        input[type="submit"] {
            padding: 5px 10px;
            font-size: 16px;
            background-color: #0077b6;
            color: white;
            border: none;
            border-radius: 5px;
            cursor: pointer;
        }

        input[type="submit"]:hover {
            background-color: #023e8a;
        }

        #response_message {
            margin-top: 15px;
            font-size: 18px;
            color: green;
            font-weight: bold;
        }

    </style>
</head>
<body>
    <div id="camera-container">
        <h1>Surveillance Camera</h1>
        <img src="stream.mjpg" width="980" height="450" alt="Camera Stream">
        <form onsubmit="setServoAngle(); return false;">
            <b><label for="servo_angle">Set Camera Angle (0-180 degrees):</label></b>
            <input type="number" id="servo_angle" name="servo_angle" min="0" max="180">
            <input type="submit" value="Set Angle">
        </form>
        <div id="response_message"></div>
    </div>

    <div class="sensor-container">
        <div class="sensor-box">
            <h4 id="temperature">Temperature: ??</h4>
        </div>
        <div class="sensor-box">
            <h4 id="humidity">Humidity: ??</h4>
        </div>
        <div class="sensor-box">
            <h4 id="mq3_value_">MQ3 Value: ??</h4>
        </div>
        <div class="sensor-box">
            <h4 id="soil_value_">Soil Value: ??</h4>
        </div>
        <div class="sensor-box">
            <h4 id="rain_value_">Rain Value: ??</h4>
        </div>
    </div>

    <script>
        function setServoAngle() {
            var angle = document.getElementById("servo_angle").value;

            fetch('/', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/x-www-form-urlencoded',
                },
                body: 'servo_angle=' + angle
            })
            .then(response => response.text())
            .then(data => {
                document.getElementById("response_message").innerText = data;
            });
        }

        function updateGPUTemperature() {
            fetch('/get_temperature')
                .then(response => response.text())
                .then(temp => {
                    document.getElementById("temperature").innerText = `Temperature: ${temp} C`;
                });
        }

        function updateHumidity() {
            fetch('/get_humidity')
                .then(response => response.text())
                .then(humidity => {
                    document.getElementById("humidity").innerText = `Humidity: ${humidity} %`;
                });
        }

        function updateMQ3Value() {
            fetch('/get_mq3_value')
                .then(response => response.text())
                .then(mq3value => {
                    document.getElementById("mq3_value_").innerText = `MQ3 Value: ${mq3value}`;
                });
        }

        function updateSoilValue() {
            fetch('/get_soil_value')
                .then(response => response.text())
                .then(soilvalue => {
                    document.getElementById("soil_value_").innerText = `Soil Value: ${soilvalue}`;
                });
        }

        function updateRainValue() {
            fetch('/get_rain_value')
                .then(response => response.text())
                .then(rainvalue => {
                    document.getElementById("rain_value_").innerText = `Rain Value: ${rainvalue}`;
                });
        }

        setInterval(updateGPUTemperature, 10000);
        setInterval(updateHumidity, 10000);
        setInterval(updateMQ3Value, 10000);
        setInterval(updateSoilValue, 10000);
        setInterval(updateRainValue, 10000);
    </script>
</body>
</html>

"""


class StreamingOutput(object):
    def __init__(self):
        self.frame = None
        self.buffer = io.BytesIO()
        self.condition = Condition()

    def write(self, buf):
        if buf.startswith(b'\xff\xd8'):
            self.buffer.truncate()
            with self.condition:
                self.frame = self.buffer.getvalue()
                self.condition.notify_all()
            self.buffer.seek(0)
        return self.buffer.write(buf)

class StreamingHandler(server.BaseHTTPRequestHandler):
    def do_GET(self):
        if self.path == '/':
            self.send_response(301)
            self.send_header('Location', '/index.html')
            self.end_headers()
        elif self.path == '/index.html':
            content = PAGE.encode('utf-8')
            self.send_response(200)
            self.send_header('Content-Type', 'text/html')
            self.send_header('Content-Length', len(content))
            self.end_headers()
            self.wfile.write(content)
        elif self.path == '/stream.mjpg':
            self.send_response(200)
            self.send_header('Age', 0)
            self.send_header('Cache-Control', 'no-cache, private')
            self.send_header('Pragma', 'no-cache')
            self.send_header('Content-Type', 'multipart/x-mixed-replace; boundary=FRAME')
            self.end_headers()
            
            try:
                while True:
                    with output.condition:
                        output.condition.wait()
                        frame = output.frame
                    self.wfile.write(b'--FRAME\r\n')
                    self.send_header('Content-Type', 'image/jpeg')
                    self.send_header('Content-Length', len(frame))
                    self.end_headers()
                    self.wfile.write(frame)
                    self.wfile.write(b'\r\n')
            except Exception as e:
                logging.error(f"Error in video stream: {e}")
        elif self.path == '/get_temperature':
            humidity, temperature = Adafruit_DHT.read_retry(Adafruit_DHT.DHT11, sensor_pin)
            temperature = str(temperature)
            self.send_response(200)
            self.send_header('Content-Type', 'text/plain')
            self.send_header('Content-Length', len(temperature))
            self.end_headers()
            self.wfile.write(temperature.encode('utf-8'))
        elif self.path == '/get_humidity':
            humidity, temperature = Adafruit_DHT.read_retry(Adafruit_DHT.DHT11, sensor_pin)
            humidity = str(humidity)
            self.send_response(200)
            self.send_header('Content-Type', 'text/plain')
            self.send_header('Content-Length', len(humidity))
            self.end_headers()
            lcd.clear()
            lcd.set_cursor(0, 0)
            lcd.message('T:{0}C H:{1}'.format(temperature,humidity))
            self.wfile.write(humidity.encode('utf-8'))
            
        elif self.path == '/get_mq3_value':
            value = mcp.read_adc(3)
            value = str(value)
            self.send_response(200)
            self.send_header('Content-Type', 'text/plain')
            self.send_header('Content-Length', len(value))
            self.end_headers()
            self.wfile.write(value.encode('utf-8'))
        elif self.path == '/get_soil_value':
            value = mcp.read_adc(4)
            value = str(value)
            self.send_response(200)
            self.send_header('Content-Type', 'text/plain')
            self.send_header('Content-Length', len(value))
            self.end_headers()
            self.wfile.write(value.encode('utf-8'))
        elif self.path == '/get_rain_value':
            value = mcp.read_adc(2)
            value = str(value)
            self.send_response(200)
            self.send_header('Content-Type', 'text/plain')
            self.send_header('Content-Length', len(value))
            self.end_headers()
            self.wfile.write(value.encode('utf-8')) 
    def do_POST(self):
        if self.path == '/':
            content_length = int(self.headers['Content-Length'])
            post_data = self.rfile.read(content_length).decode('utf-8')
            
            if "servo_angle" in post_data:
                angle = int(post_data.split("=")[1])
                angle = max(0, min(180, angle))  # Limit angle to 0-180 degrees

                setAngle(angle)

                response_content = f"Servo angle set to {angle} degrees"
            else:
                response_content = "Invalid request"

            self.send_response(200)
            self.send_header('Content-Type', 'text/plain')
            self.send_header('Content-Length', len(response_content))
            self.end_headers()
            self.wfile.write(response_content.encode('utf-8'))

        
class StreamingServer(socketserver.ThreadingMixIn, server.HTTPServer):
    allow_reuse_address = True
    daemon_threads = True

try:
    with picamera.PiCamera(resolution='640x480', framerate=24) as camera:
        output = StreamingOutput()
        camera.start_recording(output, format='mjpeg')

        try:
            address = ('', 5000)
            server = StreamingServer(address, StreamingHandler)
            server.serve_forever()

        finally:
            # Stop the camera recording and clean up
            camera.stop_recording()

            # Stop the servo motor and clean up GPIO
            servo.stop()
            GPIO.cleanup()
except Exception as e:
    logging.error(f"An error occurred: {e}")
