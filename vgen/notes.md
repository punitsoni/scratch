
## create environment using pipenv
https://robots.thoughtbot.com/how-to-manage-your-python-projects-with-pipenv

## Encode raw video (RGB24) to MPEG4 using ffmpeg

```
ffmpeg -y -f rawvideo -s 420x360 -pix_fmt rgb24 -r 24 -i - -an -vcodec mpeg4 video.mp4 < test.bin
```
Here, test.bin file contains bytestream of raw video frames in RGB24 format

R G B R G B ... 

size of the file will be width x height x 3

## reading and writing video files in python

http://zulko.github.io/blog/2013/09/27/read-and-write-video-frames-in-python-using-ffmpeg/

