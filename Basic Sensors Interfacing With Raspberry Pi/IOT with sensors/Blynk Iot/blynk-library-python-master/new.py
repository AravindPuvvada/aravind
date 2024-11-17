import subprocess

# Set the stream URL
stream_url = "rtmp://192.168.0.7/live/9908"

# Set video settings
video_size = "1280x720"
framerate = 30
bitrate = "2M"

# FFmpeg command
ffmpeg_cmd = [
    "ffmpeg",
    "-f", "v4l2",
    "-framerate", str(framerate),
    "-video_size", video_size,
    "-i", "/dev/video0",
    "-c:v", "h264_omx",
    "-b:v", bitrate,
    "-f", "flv",
    stream_url
]

# Start the FFmpeg process
ffmpeg_process = subprocess.Popen(ffmpeg_cmd)

# Wait for the process to finish
ffmpeg_process.wait()
