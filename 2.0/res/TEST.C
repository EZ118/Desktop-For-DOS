#include <graphics.h>
#include <conio.h>
#include <string.h>
#include "mouse.h"
#include "window.h"

/*window*/
int testwin, testwin2;

/*mouse*/
int Keystate;
int MouseExist;
int MouseButton;
int MouseX;
int MouseY;
int up[16][16],down[16][16],mouse_draw[16][16],pixel_save[16][16];
int old_mx, old_my;

void testwin_update(){
	/*type your window's foreground script here*/
	SetLabel(testwin, 10, 10, "+--------------+", 15);
	SetLabel(testwin, 10, 30, "| Hello World! |", 15);
	SetLabel(testwin, 10, 50, "+--------------+", 15);
	
	SetButton(testwin, 50, 70, "Button");
}
void testwin2_update(){
	/*type your window's foreground script here*/
	SetLabel(testwin2, 10, 10, "+----------------+", 15);
	SetLabel(testwin2, 10, 30, "| GoodBye World! |", 15);
	SetLabel(testwin2, 10, 50, "+----------------+", 15);
	
	SetButton(testwin2, 50, 70, "Button");
}

void AutoStart(){
	testwin = NewWin(100, 100, 200, 200, "TestWindow1");
	testwin_update();
	
	testwin2 = NewWin(200, 200, 200, 200, "TestWindow2");
	testwin2_update();
}


int main(){
	int driver = DETECT, mode;
	int i;
	initgraph(&driver, &mode, "");

	LoadDesktop();
	AutoStart();
	
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
				MouseOff();
				MouseGetXY();

				if(WinOnMove(0) == 1){
					WinUpdate(testwin, MouseX, MouseY, "TestWindow1");
					testwin_update();
				}else if(WinOnMove(1) == 1){
					WinUpdate(testwin2, MouseX, MouseY, "TestWindow2");
					testwin2_update();
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
	closegraph();
	return 0;
}	