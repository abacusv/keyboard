#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
	int fd = open("./temp",O_RDONLY);
	ssize_t size;
	int code;
	if(fd < 0){
		perror("Open");
		return -1;
	}

	while(1){
		size = read(fd, (char*)&code,sizeof(int));
		if(size > 0){
			printf("%d scan code read\n",code);
			system("/bin/eject");
		}
	}
}
