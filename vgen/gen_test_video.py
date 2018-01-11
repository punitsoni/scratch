#!python

import subprocess as sp
import numpy as np
import sys

FFMPEG_BIN = "ffmpeg"

width = 640
height = 480
frame_rate = 24
duration = 30

# ffmpeg command to create mp4 video by reading raw RGB video from stdin
ffmpeg_command = [
    FFMPEG_BIN,
    '-y', # (optional) overwrite output file if it exists
    '-f', 'rawvideo',
    '-vcodec','rawvideo',
    '-s', str(width) + 'x' + str(height),
    '-pix_fmt', 'rgb24',
    '-r', str(frame_rate), # frames per second
    '-i', '-', # The imput comes from a pipe
    '-an', # Tells FFMPEG not to expect any audio
    '-vcodec', 'libx264',
    'video1.mp4' 
]

proc = sp.Popen(ffmpeg_command, stdin=sp.PIPE, stderr=sys.stderr, shell=False)

for i in range(1, duration * frame_rate):
    # create numpy array of size 420  x 360 x 3 of random uint8
    image = (255 * np.random.random((width, height, 3))).astype('uint8')
    b = image.tostring()
    proc.stdin.write(b)

proc.communicate()

print('DONE')
