#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>


int WinX[505], WinY[505], WinWidth[505], WinHeight[505], WinClosed[1005];
int wIO = 0;

void LoadDesktop(){
	int TskX, TskY;
	TskX = 580;
	TskY = 10;
	/*tskbar*/
	setcolor(8);
	setfillstyle(1,8);
	rectangle(TskX, 0, 640, 480);
	floodfill(590, 10, 8);
	
	setcolor(7);
	rectangle(TskX + 10, TskY, TskX + 50, TskY + 40);
	outtextxy(TskX + 15, TskY + 16, "Win1");
}

int WinOnMove(int winid){
	if(MouseX > WinX[winid] && MouseX < (WinX[winid] + WinWidth[winid]) && MouseY > (WinY[winid] - 15) && MouseY < (WinY[winid] + 20 + 15)){
		return 1;
	}else{
		return 0;
	}
}

void WinOn(int winid, char* title){
	int i;
	for(i = 0; i < 20; i ++){
		moveto(WinX[winid], WinY[winid] + i);
		setcolor(7);
		linerel(WinWidth[winid] + 1, 0);
	}

	for(i = 20; i < WinHeight[winid] - 20; i++){
		moveto(WinX[winid], WinY[winid] + i);
		setcolor(7);
		linerel(1, 0);

		moveto(WinX[winid] + WinWidth[winid], WinY[winid] + i);
		setcolor(7);
		linerel(1, 0);
	}
	
	
	moveto(WinX[winid], WinY[winid] + WinHeight[winid] - 20);
	setcolor(7);
	linerel(WinWidth[winid] + 1, 0);
	
	setcolor(0);
	outtextxy(WinX[winid] + 4, WinY[winid] + 6, title);
	
	setcolor(4);
	setfillstyle(1,4);
	circle(WinX[winid] + WinWidth[winid] - 10, WinY[winid] + 10, 5);
	floodfill(WinX[winid] + WinWidth[winid] - 10, WinY[winid] + 10, 4);
}

int NewWin(int wx, int wy, int wwidth, int wheight, char* title){
	WinX[wIO] = wx;
	WinY[wIO] = wy;
	WinWidth[wIO] = wwidth;
	WinHeight[wIO] = wheight;
	
	WinOn(wIO, title);
	
	WinClosed[wIO] = 0;
	
	wIO += 1;
	
	return wIO - 1;
}

void WinOff(int winid){
	int i;
	for(i = 0; i <= WinHeight[winid]; i ++){
		moveto(WinX[winid], WinY[winid] + i);
		setcolor(0);
		linerel(WinWidth[winid] + 1, 0);
	}
}

void WinUpdate(int winid, int mx, int my, char* title){
	if(WinClosed[winid] == 1) return;
	if(mx > (WinX[winid] + WinWidth[winid] - 20) && mx < (WinX[winid] + WinWidth[winid] - 3) && my > WinY[0] && my < (WinY[0] + 20)){
		WinOff(winid);
		WinClosed[winid] = 1;
		return;
	}
	if((WinX[winid] + WinWidth[winid]) >= 565){
		WinOff(winid);
		WinX[winid] = 100;
		WinOn(winid, title);
		return;
	}
	WinOff(winid);
	
	WinX[winid] = mx - WinWidth[winid] / 2;
	WinY[winid] = my - 10;
	
	WinOn(winid, title);
}

/*以下为窗体控件*/
void SetLabel(int winid, int cx, int cy, char* caption, int color){
	setcolor(color);
	outtextxy(WinX[winid] + 20 + cx, WinY[winid] + 20 + cy, caption);
}

void SetButton(int winid, int cx, int cy, char* caption){
	int wx, wy;
	wx = WinX[winid] + 20 + cx;
	wy = WinY[winid] + 20 + cy;
	
	setcolor(9);
	rectangle(wx - 20, wy - 10, wx + strlen(caption) * 11, wy + 15);
	
	setcolor(15);
	outtextxy(WinX[winid] + 20 + cx, WinY[winid] + 20 + cy, caption);
}