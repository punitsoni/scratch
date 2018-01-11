#!python

import subprocess as sp
import numpy as np

#FFMPEG_BIN = "C:\\software\\ffmpeg-3.4.1-win64-static\\bin\\ffmpeg.exe"
FFMPEG_BIN = "ffmpeg"

# ffmpeg command to create mpeg4 video by reading raw RGB video from stdin
command = [
    FFMPEG_BIN,
    '-y', # (optional) overwrite output file if it exists
    '-f', 'rawvideo',
    '-vcodec','rawvideo',
    '-s', '640x480', # size of one frame
    '-pix_fmt', 'rgb24',
    '-r', '24', # frames per second
    '-i', '-', # The imput comes from a pipe
    '-an', # Tells FFMPEG not to expect any audio
    '-vcodec', 'libx264',
    'video.mp4' ]

proc = sp.Popen(command, stdin=sp.PIPE, stderr=sp.PIPE, shell=False)

with open('test.bin', 'wb') as f:
    for i in range(1, 100):
        # create numpy array of size 420  x 360 x 3 of random uint8
        image = (255 * np.random.random((WIDTH, HEIGHT, 3))).astype('uint8')
        b = image.tostring()
        proc.stdin.write(b)
        f.write(b)

pout, perr = proc.communicate()

print(perr.decode('utf-8'))
print('DONE')

width = 640
height = 480
for i in range(1, 100):
    # create numpy array of size 420  x 360 x 3 of random uint8
    image = (255 * np.random.random((WIDTH, HEIGHT, 3))).astype('uint8')
    b = image.tostring()
    proc.stdin.write(b)
    f.write(b)
