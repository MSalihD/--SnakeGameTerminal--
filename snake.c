#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "windows.h"
#include "conio.h"
#define gotoxy(x,y) SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1})
#define appleRandom() apple.x=(1+rand()%(width-2));apple.y=(1+rand()%(height-2))
#define quit() gotoxy(width+1,2);printf("GAME%cOVER",32);gotoxy(width+4,height+4);\
				getchar();system("cls");exit(0)
#define delayVal 50
#define width 30
#define height 15
#define size (width*height)
#define left 0
#define up 1
#define right 2
#define down 3

typedef struct{
	int x;
	int y;
} Character;

Character head = {width/2,height/2};
Character apple;
Character tails[size];
unsigned int tailCount = 0;
unsigned char direction = 4;
void update(void){
	system("cls");
	int i,j;
	for(j = 1;j < height;j++){
		for(i = 1;i < width;i++){
			if(i == width-1 || j == height-1){
				gotoxy(i,j);
				putchar('&');
			}
		}
	}
	gotoxy(head.x,head.y);
	putchar('#');
	gotoxy(apple.x,apple.y);
	putchar('@');
	for(i = 0;i < tailCount;i++){
		gotoxy(tails[i].x,tails[i].y);
		putchar('#');
	}
	gotoxy(width+1,1);
	printf("%d",tailCount);
}
void headTo_Arrow(unsigned char val){
	switch(val){
		case 72:
		if(direction != down)direction = up;
		break;
		case 80:
		if(direction != up)direction = down;
		break;
		case 77:
		if(direction != left)direction = right;
		break;
		case 75:
		if(direction != right)direction = left;
		break;
	}
}
void headTo_WASD(unsigned char val){
	switch(val){
		case 'w':
		if(direction != down)direction = up;
		break;
		case 's':
		if(direction != up)direction = down;
		break;
		case 'd':
		if(direction != left)direction = right;
		break;
		case 'a':
		if(direction != right)direction = left;
		break;
	}
}
void move(void){
	if(head.x == apple.x && head.y == apple.y){
		appleRandom();
		tails[tailCount] = (Character){1,1};
		tailCount++;
	}
	int i;
	for(i = tailCount - 1;i > 0;i--){
		tails[i].x = tails[i - 1].x;
		tails[i].y = tails[i - 1].y;
	}
	if(tailCount > 0){
		tails[0].x = head.x;
		tails[0].y = head.y;
	}
	switch(direction){
		case up:
		head.y--;
		break;
		case down:
		head.y++;
		break;
		case right:
		head.x++;
		break;
		case left:
		head.x--;
		break;
	}
}
void collisionCheck(void){
	if(head.x <= 1 || head.y <= 1 || head.x >= width-1 || head.y >= height-1){
		quit();
	}
	else{
		int i;
		for(i = 0;i < tailCount;i++){
			if(head.x == tails[i].x && head.y == tails[i].y){
				quit();
			}
		}
	}
}
int main(void){
	srand(time(0));
	unsigned char sel;
	appleRandom();
	update();
	for(;;){
		move();
		update();
		collisionCheck();
		if(kbhit()){
			sel = getch();
			if(sel == 224)headTo_Arrow(getch());
			else headTo_WASD(sel);
			
		}
		Sleep(delayVal);
	}
	return 0;
}
