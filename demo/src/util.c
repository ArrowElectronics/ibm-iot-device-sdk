#include <stdio.h>
#include <fcntl.h>

#define MAC_ADDR_BUF_SIZE 50

static char buf[MAC_ADDR_BUF_SIZE];

char* GetMACAddress()
{
	int fd;

	fd = open("/sys/class/net/wlan0/address", O_RDONLY);
	if(fd < 0)
		return "";
	read(fd, &buf, MAC_ADDR_BUF_SIZE);
	close(fd);

	return buf;
}

