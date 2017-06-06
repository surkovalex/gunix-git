#include <fcntl.h>

int efuse_read(uint8_t *buf, uint32_t offset, uint32_t len)
{
	int avail = 0;
	ssize_t rlen;
	int fd;

	if (!buf)
		return 0;
	fd  = open("/dev/efuse", O_RDONLY | O_NOFOLLOW);
	if (fd < 0)
		return 0;
	rlen = lseek(fd, offset, SEEK_SET);
	if (rlen != -1)	{
		rlen = read(fd, buf, len);
		if (rlen == len)
			avail = 1;
    }
    close(fd);
    return avail;
}

void main()
{
	int avail;
    uint8_t buf[8];
    uint32_t offset, len;
    offset = 176;
    len = 8;

    avail = efuse_read(buf, offset, len);
	if (avail) {
		for (i=0; i<len; i++)
			printf("%02x", buf[i]);
		printf("\n");
	}
}

