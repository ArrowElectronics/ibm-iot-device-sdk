#include <stdio.h>
#include <fcntl.h>
#include <string.h>

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

char* Strip(char in[], char out[], char ch)
{
	int i,j=0;
	int size;
	
	size = strlen(in)-1;
	for(i=0;i<size;i++)
	{
		if(in[i] != ch)
		{
			out[j] = in[i];
			j++;
		}
	}
	out[j] ='\0';
	return out;
}