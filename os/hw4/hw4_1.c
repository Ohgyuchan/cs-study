#include <stdio.h>

#include "Console.h"

int main(int argc, char *argv)
{
	clrscr();			// clear screen

	// retrieve the size of window
	int screen_width = getWindowWidth();
	int screen_height = getWindowHeight() - 3;
	
	printf("i: up, j: left, k: down, l: right, c: change color, q: quit\n");
	printf("screen size: %d x %d\n", screen_width, screen_height);
	int x = screen_width / 2;	// horizontal coordinate
	int y = screen_height / 2;	// vertical coordinate
	int key = 0;
	int repeat = 1;
	char c = '*';		// initial color

	gotoxy(x, y);		// move the cursor to (x, y)
	putchar('#');

	int oldx = 0, oldy = 0;
	while(repeat){
		// TO DO: save current coordinate in (oldx, oldy)
		oldx = x;
		oldy = y;
		
		gotoxy(1, 3);
		printf("x = %3d, y = %3d", x, y);

		gotoxy(screen_width, 1);	// move cursor to upper right corner
		key = getch();		// read a key not waiting for ENTER

		gotoxy(x,y);
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
			
	}

	clrscr();
	printf("Bye!\n");

	return 0;
}

