
uv4l2_sources = uv4l2.cpp uv4l2_hooks.cpp
uv4l2_cflags = -fPIC -shared -std=c++11

all:
	g++ main.cpp -std=c++11 -o uv4l2-test
	g++ $(uv4l2_cflags) $(uv4l2_sources) -o libuv4l2.so -ldl

clean:
	rm -rf uv4l2-test
	rm -rf libuv4l2.so
