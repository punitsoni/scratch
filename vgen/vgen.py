# -*- coding: utf-8 -*-
"""
Created on Mon Jan  8 16:23:43 2018

@author: punits
"""

import subprocess as sp
import numpy as np

FFMPEG_BIN = "C:\\software\\ffmpeg-3.4.1-win64-static\\bin\\ffmpeg.exe"


# ffmpeg command to create mpeg4 video by reading raw RGB video from stdin
command = [
        FFMPEG_BIN,
        '-y', # (optional) overwrite output file if it exists
        '-f', 'rawvideo',
        '-vcodec','rawvideo',
        '-s', '420x360', # size of one frame
        '-pix_fmt', 'rgb24',
        '-r', '24', # frames per second
        '-i', '-', # The imput comes from a pipe
        '-an', # Tells FFMPEG not to expect any audio
        '-vcodec', 'mpeg',
        'vgen.mp4' ]

proc = sp.Popen(command, stdin=sp.PIPE, stderr=sp.PIPE, shell=False)

#pipe.proc.stdin.write(image_array.tostring())


for i in range(1, 100):
    # create numpy array of size 420  x 360 x 3 of random uint8
    image = (255 * np.random.random((420, 360, 3))).astype('uint8')
    proc.stdin.write(image.tostring())
    #print(image.tostring())

proc.stdin.close()
