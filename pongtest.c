/*
Use Arduino libs
*/

#include <stdio.h>

//Create structures
struct ball{
	int x;
	int y;
	int radius;
	int vx; //pixels per second
	int vy;
	int direction; //1 for left   2 for right
}

struct paddle{
	int x;
	int y;
	int width;
	int height;
}

struct screen{
	int x;
	int y;
}

//Declare items
struct ball b;
struct paddle p1;
struct paddle p2;
struct screen scrn;

void reset(){
	//Initialise Paddles
	//Paddle 1
	p1.x = (0.1*scrn.x);
	p1.y = scrn.y/2;
	p1.width = 1; //paddles will be 4x1
	p1.height = 4;
	//Paddle 2
	p2.x = scrn.x - (0.1*scrn.x);
	p2.y = scrn.y/2;
	p2.width = 1; //paddles will be 4x1
	p2.height = 4;
	//Initialise Ball
	b.x = scrn.x/2;
	b.radius = 3;
	b.vx = 5*(scrn.x/100);
	b.vy = 0;
	b.direction = 1;//starts off left
}

void initialise(){
	reset();
	//Initialise Screen
	scrn.x = 800;
	scrn.y = 600;
	LCDInit();
	//LCDClear(int color);
	LCDClear(0);
}

void updatedisplay(){
	
	int p1x,p1y,p2x,p2y,bx,by;
	
	/*-------------------------------*/
	//Paddles
	char fill = 'o';	
	//LCDSetRect(int x0, int y0, int x1, int y1, unsigned char fill, int color);
	//Draw Paddle 1
	LCDSetRect(p1.x, p1.y, p1.x+p.width, p1.y+p.height,fill,1);
	//Draw Paddle2
	LCDSetRect(p2.x, p2.y, p2.x+p.width, p2.y+p.height,fill,1);
	/*-------------------------------*/
	
	/*-------------------------------*/
	//Ball	
	bx = b.x;
	by = b.y;
	br = b.radius;
	
	//LCDSetCircle(int x0, int y0, int radius, int color);
	LCDSetCircle(bx, by, br, 1);
	/*-------------------------------*/
}

int checkBoundaries(int x,int y){
	//Returns table
	//0 - CONT - not hit side
	//1 -  CONT - hits the wall or 1 if still in play
	//2 - END - has gone on player side
	//3 - END - has gone on computer side
	if(x>1&&x<scrn.x&&y>1&&y<scrn.y){
		return 0;
	}
	if(x<scrn.x&&y<scrn.y){
		return 1;
	}
	if(x>scrn.x){
		return 3;
	}
	if(x<1){
		return 2;
	}
}

void hitWall(){
	b.vx = -1*b.vx;
	b.vy = -1*b.vy;
}

void updateBall(){
	//Bounce off of walls
	switch(checkBoundaries(b.x,b.y)){		
		case 0:
			b.x = b.x+b.vx;
			b.y = b.y+b.vy;
			break;
		case 1:
			hitwall();
			break();
		case 2:
			reset();
			break;
		case 3:
			reset();
		`	break;
	}
}

void paddleMove(){
	//Check input
	int movement;
	PORTA = movement;
	
	//Convert to y for p1
	int tmpy;
	tmpy = movement*(scrn.x/0xFF);
	//Check boundaries
	if(!(p1.y<1||p1.y>scrn.y-1)){
		p1.y = tmpy;
	}
}

void main(){
	
	initialise();
	//Begin main loop
	while(1){
		paddlemove();
		updateball();
		updatedisplay();
		//Introduce delay?
	}
}
