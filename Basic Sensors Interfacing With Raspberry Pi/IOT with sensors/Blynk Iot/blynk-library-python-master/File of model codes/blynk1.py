import blynklib
import Adafruit_DHT
import time

# Blynk authentication token (replace with your own token)
BLYNK_AUTH = "9-gRD1rc7WZI29K48rDXG5f7xXZ39lLm"

# Set your DHT11 sensor type and GPIO pin number
DHT_SENSOR = Adafruit_DHT.DHT11
DHT_PIN = 17

# Initialize Blynk with your authentication token
blynk = blynklib.Blynk(BLYNK_AUTH)

def read_dht11():
    # Read DHT11 sensor values
    humidity, temperature = Adafruit_DHT.read_retry(DHT_SENSOR, DHT_PIN)
    return humidity, temperature

@blynk.handle_event('write V1')
def write_virtual_pin_handler(pin, value):
    # This function will be called whenever the V1 virtual pin value is updated in the Blynk app.
    # You can use this to trigger actions on the hardware.
    pass

def main():
    try:
        while True:
            # Read DHT11 sensor values
            humidity, temperature = read_dht11()

            # Check if DHT11 sensor read the data successfully
            if humidity is not None and temperature is not None:
                # Print values to the console
                print("Temperature: {}°C, Humidity: {}%".format(temperature, humidity))

                # Send sensor values to Blynk app
                blynk.virtual_write(0, temperature)  # Virtual Pin V0 for temperature
                blynk.virtual_write(1, humidity)     # Virtual Pin V1 for humidity
            else:
                # Failed to read data from the DHT11 sensor
                print("Failed to read data from DHT11 sensor.")

            # Wait for 2 seconds before reading again
            time.sleep(2)

            # Process any pending Blynk events
            blynk.run()

    except KeyboardInterrupt:
        print("Exiting...")

if __name__ == "__main__":
    main()
