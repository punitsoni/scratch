
uv4l2_sources = uv4l2.cpp uv4l2_hooks.cpp testgen.cpp
uv4l2_headers = uv4l2.h testgen.h log.h
uv4l2_cflags = -fPIC -shared -std=c++11

uv4l2_test_sources = main.cpp

v4l2_ex_sources = v4l2_example.c

all: uv4l2-test libuv4l2.so v4l2-ex

libuv4l2.so: $(uv4l2_sources) $(uv4l2_headers)
	g++ $(uv4l2_cflags) $(uv4l2_sources) -o libuv4l2.so -ldl -lpthread

uv4l2-test: $(uv4l2_test_sources)
	g++ main.cpp -std=c++11 -o uv4l2-test

v4l2-ex: $(v4l2_ex_sources)
	gcc $(v4l2_ex_sources) -o v4l2-ex

clean:
	rm -rf uv4l2-test
	rm -rf libuv4l2.so
