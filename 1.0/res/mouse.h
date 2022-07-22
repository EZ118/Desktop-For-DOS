#include <graphics.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>

#define WAITING 0xff00
#define LEFTPRESS 0xff01
#define LEFTCLICK 0xff10
#define LEFTDRAG 0xff19
#define RIGHTPRESS 0xff02
#define RIGHTCLICK 0xff20
#define RIGHTDRAG 0xff2a
#define MIDDLEPRESS 0xff04
#define MIDDLECLICK 0xff40
#define MIDDLEDRAG 0xff4c
#define MOUSEMOVE 0xff08

int Keystate;
int MouseExist;
int MouseButton;
int MouseX;
int MouseY;
int up[16][16],down[16][16],mouse_draw[16][16],pixel_save[16][16];
void MouseMath(){
/*计算鼠标的样子*/ 
	int i,j,jj,k;
	long UpNum[16]= {
		0x3fff,0x1fff,0x0fff,0x07ff,
		0x03ff,0x01ff,0x00ff,0x007f,
		0x003f,0x00ff,0x01ff,0x10ff,
		0x30ff,0xf87f,0xf87f,0xfc3f
	}
	;
	long DownNum[16]= {
		0x0000,0x7c00,0x6000,0x7000,
		0x7800,0x7c00,0x7e00,0x7f00,
		0x7f80,0x7e00,0x7c00,0x4600,
		0x0600,0x0300,0x0300,0x0180
	}
	;
	for (i=0;i<16;i++) {
		j=jj=15;
		while(UpNum[i]!=0) {
			up[i][j]=UpNum[i]%2;
			j--;
			UpNum[i]/=2;
		}
		while(DownNum[i]!=0) {
			down[i][jj--]=DownNum[i]%2;
			DownNum[i]/=2;
		}
		for (k=j;k>=0;k--)
		up[i][k]=0;
		for (k=jj;k>=0;k--)
		down[i][k]=0;
		for (k=0;k<16;k++)
		/*四种组合方式*/ {
			if(up[i][k]==0&&down[i][k]==0)
			mouse_draw[i][k]=1; else if(up[i][k]==0&&down[i][k]==1)
			mouse_draw[i][k]=2; else if(up[i][k]==1&&down[i][k]==0)
			mouse_draw[i][k]=3; else
			mouse_draw[i][k]=4;
		}
	}
	mouse_draw[1][2]=4;
	/*非凡点*/
}
/*鼠标光标显示*/
void MouseOn(int x,int y) {
	int i,j;
	int color;
	for (i=0;i<16;i++)
	/*画鼠标*/ {
		for (j=0;j<16;j++) {
			pixel_save[i][j]=getpixel(x+j,y+i);
			/*保存原来的颜色*/
			if(mouse_draw[i][j]==1)
			putpixel(x+j,y+i,0); else if(mouse_draw[i][j]==2)
			putpixel(x+j,y+i,15);
		}
	}
}
/*隐藏鼠标*/
void MouseOff(){
	int i,j,x,y,color;
	x=MouseX;
	y=MouseY;
	for (i=0;i<16;i++)
	/*原位置异或消去*/
	for (j=0;j<16;j++) {
		if(mouse_draw[i][j]==3||mouse_draw[i][j]==4)
		continue;
		color=getpixel(x+j,y+i);
		putpixel(x+j,y+i,color^color);
		putpixel(x+j,y+i,pixel_save[i][j]);
	}
}
void MouseLoad(){_AX=0x00;geninterrupt(0x33);MouseExist=_AX;MouseButton=_BX;}
void MouseReset(){_AX=0x00;geninterrupt(0x33);}
void MouseSetX(int lx,int rx){_CX=lx;_DX=rx;_AX=0x07;geninterrupt(0x33);}
void MouseSetY(int uy,int dy){_CX=uy;_DX=dy;_AX=0x08;geninterrupt(0x33);}
void MouseSetXY(int x,int y){_CX=x;_DX=y;_AX=0x04;geninterrupt(0x33);}
void MouseSpeed(int vx,int vy) {
	/*设置鼠标速度(缺省值:vx=8,vy=1)
	值越大速度越慢 */
	_CX=vx;
	_DX=vy;
	_AX=0x0f;
	geninterrupt(0x33);
}
/*获取鼠标按下键的信息*/
/*是否按下左键
返回值: 1=按下 0=释放*/
int LeftPress() {
	_AX=0x03;
	geninterrupt(0x33);
	return(_BX&1);
}
/*是否按下中键
返回值同上 */
int MiddlePress() {
	_AX=0x03;
	geninterrupt(0x33);
	return(_BX&4);
}
/*是否按下右键
返回值同上 */
int RightPress() {
	_AX=0x03;
	geninterrupt(0x33);
	return(_BX&2);
}
/*获取鼠标当前位置*/
void MouseGetXY() {
	_AX=0x03;
	geninterrupt(0x33);
	MouseX=_CX;
	MouseY=_DX;
}
int MouseStatus()
/*鼠标按键情况*/ {
	int x,y;
	int status;
	int press=0;
	int i,j,color;
	status=0;
	/*默认鼠标没又移动*/
	x=MouseX;
	y=MouseY;
	while(x==MouseX&&y==MouseY&&status==0&&press==0) {
		if(LeftPress()&&RightPress())
		press=1; else if(LeftPress())
		press=2; else if(RightPress())
		press=3;
		MouseGetXY();
		if(MouseX!=x||MouseY!=y)
		status=1;
	}
	if(status)
	/*移动情况才重新显示鼠标*/ {
		for (i=0;i<16;i++)
		/*原位置异或消去*/
		for (j=0;j<16;j++) {
			if(mouse_draw[i][j]==3||mouse_draw[i][j]==4)
			continue;
			color=getpixel(x+j,y+i);
			putpixel(x+j,y+i,color^color);
			putpixel(x+j,y+i,pixel_save[i][j]);
		}
		MouseOn(MouseX,MouseY);
		/*新位置显示*/
	}
	if(press!=0)
	/*有按键得情况*/
	return press;
	return 0;
	/*只移动得情况*/
}