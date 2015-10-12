#include <stdio.h>
#include <sys/mman.h>
#include <stdint.h>
#include <fcntl.h>

int main()
{
	printf("Hello\n");
	int fd = open("/dev/uio0", O_RDWR|O_NONBLOCK);
	if (fd < 0) {
		printf("open failed\n");
		return -1;
	}

	printf("map\n");

	uint32_t *p = mmap(NULL, 8, PROT_READ, MAP_SHARED, fd, 0);
	if (p == MAP_FAILED) {
		printf("mmap failed\n");
		return -1;
	}

	sleep(5);

	printf("p = %p\n", p);
	printf("count = %u\n", *p);
	printf("unmap\n");
	munmap(p, 8);

	close(fd);
	return 0;
}