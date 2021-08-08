#include <graphics.h>
#include <conio.h>
#include <string.h>
#include "mouse.h"

/*window*/
int wx, wy, wwidth, wheight;
int wIO;

/*mouse*/
int Keystate;
int MouseExist;
int MouseButton;
int MouseX;
int MouseY;
int up[16][16],down[16][16],mouse_draw[16][16],pixel_save[16][16];
int old_mx, old_my;


void WinOn(int wx, int wy, int wwidth, int wheight, char* title	){
	int i;
	for(i = 0; i < 20; i ++){
		moveto(wx, wy + i);
		setcolor(7);
		linerel(wwidth + 1, 0);
	}

	for(i = 20; i < wheight - 20; i++){
		moveto(wx, wy + i);
		setcolor(7);
		linerel(1, 0);

		moveto(wx + wwidth, wy + i);
		setcolor(7);
		linerel(1, 0);
	}
	
	
	moveto(wx, wy + wheight - 20);
	setcolor(7);
	linerel(wwidth + 1, 0);

	setcolor(0);
	outtextxy(wx + 4, wy + 6, title);
	wIO = 1;
}

void WinOff(int wx, int wy, int wwidth, int wheight){
	int i;
	for(i = 0; i <= wheight; i ++){
		moveto(wx, wy + i);
		setcolor(0);
		linerel(wwidth + 1, 0);
	}
	wIO = 0;
}

int main(){
	int driver = DETECT, mode;
	int i;
	initgraph(&driver, &mode, "");


	wx = 100;
	wy = 100;
	wwidth = 200;
	wheight = 200;

	WinOn(wx, wy, wwidth, wheight, "114514");
	
	MouseMath();
	MouseSetY(0,479);
	MouseSetX(0,639);
	MouseSetXY(100,100);
	MouseOn(MouseX,MouseY);
	/*第一次显示鼠标*/
	while(!kbhit()) {
		switch(MouseStatus()) {
			/*双键按下*/
			case 1:
				MouseOff();
				putpixel(MouseX,MouseY,YELLOW);
				MouseGetXY();
				MouseOn(MouseX,MouseY);
				break;
			
			/*左键按下*/
			case 2:
				
				if(MouseX > wx && MouseX < (wx + wwidth) && MouseY > wy && MouseY < (wy + wheight)){
					WinOff(wx, wy, wwidth, wheight);
				}
				
				MouseOff();
				putpixel(MouseX,MouseY,RED);
				MouseGetXY();
				
				if(MouseX > wx && MouseX < (wx + wwidth) && MouseY > wy && MouseY < (wy + wheight)){
					WinOn(MouseX - wwidth / 2, MouseY - 10, wwidth, wheight, "114514");
					wx = MouseX - wwidth / 2;
					wy = MouseY - 10;
				}
				
				MouseOn(MouseX,MouseY);
				
				break;
			
			/*右键按下*/
			case 3:
				MouseOff();				
				putpixel(MouseX,MouseY,GREEN);
				MouseGetXY();
				MouseOn(MouseX,MouseY);
				break;
			default:
				break;
		}
	}

	return 0;
}