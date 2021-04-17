#include <stdio.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "Console.h"
#include "KeyBuffer.h"

#define SHM_FILE "key_buffer.shm"


int main(int argc, char *argv)
{
	int shm_fd;
	int res;
	
	shm_fd = shm_open(SHM_FILE, O_RDONLY ,0666);
    if(shm_fd == -1) {
        printf("can not open \"%s\"\n", SHM_FILE);
        return 0;
    }
	
	int buffer_size = sizeof(KeyBuffer);
	KeyBuffer *key_buffer = NULL;
	
	key_buffer = (KeyBuffer *)mmap(0, buffer_size, PROT_READ, MAP_SHARED, shm_fd, 0);
    
	if(key_buffer == MAP_FAILED) {
        printf("failed mmap\n");
        return 0;
    }

	int screen_width = getWindowWidth();
	int screen_height = getWindowHeight() - 3;

	clrscr();

	printf("screen size: %d x %d\n", screen_width, screen_height);
	int x = screen_width / 2;
	int y = screen_height / 2;
	int key = 0;
	char c = '*';
	int repeat = 1;
	
	gotoxy(x,y);
	putchar('#');

	while(repeat){
		int oldx = x;
		int oldy = y;
		
	
		key = GetKey(key_buffer, key_buffer->out);
		
        if(key == 'q')
            break;
        else if(key == 'i') {
            if(y > 1)
                y--;
            else
                y = screen_height;
        }
        else if(key == 'j') {
            if(x > 1)
                x--;
            else
                x = screen_width;
        }
        else if(key == 'k') {
            if(y < screen_height)
                y++;
            else
                y = 1;
        }
		else if(key == 'l') {
            if(x < screen_width)
                x++;
            else
                x = 1;
        }
        else if(key == 'c') {
            if(c == ' ')
                c = '*';
            else if(c == '*')
                c = ' ';
        }
        gotoxy(oldx,oldy);
        putchar(c);
        gotoxy(x,y);
        putchar('#');
		MySleep(2);
	}
	shm_unlink(SHM_FILE);
	clrscr();
	printf("Bye!\n");

	return 0;
}
