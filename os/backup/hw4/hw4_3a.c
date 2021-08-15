#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "Console.h"
#include "KeyBuffer.h"

#define SHM_FILE "key_buffer.shm"


int main(int argc, char *argv[])
{
	int shm_fd;
	int res;
	
	shm_fd = shm_open(SHM_FILE, O_CREAT | O_RDWR, 0666);
	if(shm_fd == -1) {
		printf("can not open \"%s\"\n", SHM_FILE);
		return 0;
	}

	int buffer_size = sizeof(KeyBuffer);

	KeyBuffer *key_buffer = NULL;

	res = ftruncate(shm_fd, buffer_size);
	if(res == -1) {
		printf("failed ftruncate\n");
		return 0;
	}
	key_buffer = (KeyBuffer *)mmap(0, buffer_size, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if(key_buffer == MAP_FAILED) {
		printf("failed mmap\n");
		return 0;
	}
	InitKeyBuffer(key_buffer);
	clrscr();

	printf("i: up, j: left, k: down, l: right, c: change color, q: quit hw4_3b, ESC: quit both\n");

	while(1){
		gotoxy(1, 2);
		printf("Input a key: ");
		
		int key = getch();
		if(key == 27){          // ESC
			key = 'q';
			InsertKey(key_buffer, key);
			break;
		} else {
			InsertKey(key_buffer, key);
		}
		DisplayKeyBuffer(1, 2, key_buffer);
		MySleep(2);
		DeleteKey(key_buffer);
	}

	res = munmap(key_buffer, buffer_size);
	shm_fd = shm_unlink(SHM_FILE);
	clrscr();
	printf("Bye!\n");

	return 0;
}

