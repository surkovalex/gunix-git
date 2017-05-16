#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define FREG_DEVICE_NAME	"/dev/freg"


int main(int argc, char **argv)
{
	int fd = -1;
	int val = 0;

	fd = open(FREG_DEVICE_NAME, O_RDWR);
	if (-1 == fd) {
        printf("Failed to open device %s", FREG_DEVICE_NAME);
        return -1;
    }

	read(fd, &val, sizeof(val));
	printf("read original value: %d\n", val);

	val = 5;
	printf("write value %d to %s\n", val, FREG_DEVICE_NAME);
	write(fd, &val, sizeof(val));

	printf("read the value again: ");
    read(fd, &val, sizeof(val));
	printf("%d\n", val);

	close(fd);

    return 0;
}

