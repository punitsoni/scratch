
uv4l2_sources = uv4l2.cpp uv4l2_hooks.cpp
uv4l2_cflags = -fPIC -shared -std=c++11

uv4l2_test_sources = main.cpp

all: uv4l2-test libuv4l2.so

libuv4l2.so: $(uv4l2_sources)
	g++ $(uv4l2_cflags) $(uv4l2_sources) -o libuv4l2.so -ldl

uv4l2-test: $(uv4l2_test_sources)
	g++ main.cpp -std=c++11 -o uv4l2-test

clean:
	rm -rf uv4l2-test
	rm -rf libuv4l2.so
