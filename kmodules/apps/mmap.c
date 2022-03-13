#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	int fd;
	unsigned long *addr;
	int n = 0;
	
	fd = open("/dev/mem", O_RDWR);

	// 0x34000000 即/dev/mem的偏移，也就是保留内存在物理地址空间的偏移，我的例子就是0x34000000
	addr = mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (addr == MAP_FAILED)
    {
        perror("mmap");
        return -1;
    }
	n = atoi(argv[1]);
	printf("JYW=> memset addr %x, len %d\n", addr, n);
	memset(addr, 0, n);
	close(fd);
	munmap(addr, 4096);

	return 1;
}


