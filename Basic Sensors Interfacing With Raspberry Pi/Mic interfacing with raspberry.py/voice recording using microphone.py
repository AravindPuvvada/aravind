import pyaudio
import wave

# Set the parameters for recording
FORMAT = pyaudio.paInt16  # Audio format (16-bit)
CHANNELS = 1              # Mono recording
RATE = 44100              # Sampling rate (44.1 kHz)
CHUNK = 1024              # Buffer size
RECORD_SECONDS = 10       # Duration of recording in seconds
OUTPUT_FILENAME = "output.wav"  # Output filename

# Initialize PyAudio
audio = pyaudio.PyAudio()

# Open a new stream
stream = audio.open(format=FORMAT, channels=CHANNELS,
                    rate=RATE, input=True,
                    frames_per_buffer=CHUNK)

print("Recording...")

frames = []

# Record for the specified duration
for i in range(0, int(RATE / CHUNK * RECORD_SECONDS)):
    data = stream.read(CHUNK)
    frames.append(data)

print("Finished recording.")

# Stop and close the stream
stream.stop_stream()
stream.close()
audio.terminate()

# Save the recorded data to a WAV file
with wave.open(OUTPUT_FILENAME, 'wb') as wf:
    wf.setnchannels(CHANNELS)
    wf.setsampwidth(audio.get_sample_size(FORMAT))
    wf.setframerate(RATE)
    wf.writeframes(b''.join(frames))

print(f"Audio saved as {OUTPUT_FILENAME}")
