#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#define BUFF_SIZE 1024

char buffer[BUFF_SIZE];
int buffer_size = 0;
int buffer_pos = 0;

int ReadTextLine(int fd, char str[], int max_len);

int main() {
	
	int fd = open("/proc/cpuinfo", O_RDONLY);
	char str[BUFF_SIZE];

	if(fd == -1) {
		printf("can not open \'/proc/cpuinfo\' file!\n");
		return -1;
	}
	
	else if(fd > 0) {
		for(int i = 0; i < 12; i++)
			ReadTextLine(fd, str, BUFF_SIZE);

		puts(str);
		close(fd);	// Initialize buffer
		
		fd = open("/proc/cpuinfo", O_RDONLY);
		if(fd == -1) {
			printf("can not open \'/proc/cpuinfo\' file!\n");
			return -1;
		}
		
		for(int i = 0; i < 5; i++)
			ReadTextLine(fd, str, BUFF_SIZE);
		
		puts(str);
		close(fd);	// Close /proc/cpuinfo

		fd = open("/proc/meminfo", O_RDONLY);
		if(fd == -1) {
			printf("can not open \'/proc/meminfo/\' file!\n");
			return -1;
		}

		ReadTextLine(fd, str, BUFF_SIZE);
		puts(str);
		close(fd);	// Close /proc/meminfo

		fd = open("/proc/loadavg", O_RDONLY);
		if(fd == -1) {
			printf("can not open \'/proc/loadavg\' file!\n");
			return -1;
		}

		ReadTextLine(fd, str, BUFF_SIZE);
		
		char *ptr = strtok(str, " ");
		
		for(int i = 0; i < 5; i++) {
			printf("loadavg[%d] = %s",i+1 ,ptr);
			
			if(i != 4)
				printf(", ");
			
			ptr = strtok(NULL, " ");
		}
		printf("\n");
		close(fd);	//Close /proc/loadavg
		
	}
		
	return 0;
}

int ReadTextLine(int fd, char str[], int max_len) {
	int i = 0;
	int j = 0;
	int ret = 0;

	if(lseek(fd, 0, SEEK_CUR) == 0)
		buffer_pos = buffer_size = 0;

	while(j < max_len - 1) {
		if(buffer_pos == buffer_size) {
			buffer[0] = 0;
			buffer_size = read(fd, buffer, BUFF_SIZE);
			buffer_pos = 0;
		}
		
		if(buffer_size == 0) {
			if(j == 0)
				ret = EOF;
			break;
		}
		while(j < max_len - 2 && buffer_pos < buffer_size) {
			str[j++] = buffer[buffer_pos++];
			
			if(str[j - 1] == '\0' || str[j - 1] == 10) {
				j --;
				max_len = j;
				break;
			}
		}
	}
	str[j] = 0;

	return ret;
}
