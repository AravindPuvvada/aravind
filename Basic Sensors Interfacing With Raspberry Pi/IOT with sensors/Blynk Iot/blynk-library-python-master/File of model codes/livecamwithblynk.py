import os
import subprocess
from time import sleep
from blynklib import Blynk

# Set the IP address of your Raspberry Pi running `motion`
raspberry_pi_ip = '192.168.0.7'

# Set the port number configured in the `motion` server
motion_stream_port = '8081'

# Set the Blynk authentication token for your project
blynk_auth_token = 'B1fJ2B59i7XisXqybChnN0vwyh80raoS'

# Start the `motion` server using subprocess
subprocess.Popen(['motion'])

# Wait for the `motion` server to start
sleep(5)

# Initialize Blynk with the authentication token
blynk = Blynk(blynk_auth_token)

# Create a Video Streaming Widget in the Blynk app
def start_streaming(pin, value):
    if int(value[0]) == 1:
        streaming_url = f'http://{raspberry_pi_ip}:{motion_stream_port}'
        blynk.virtual_write(2, streaming_url)  # Update Video Streaming Widget with the streaming URL

# Run the Blynk main loop
while True:
    blynk.run()
