#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "windows.h"
#include "conio.h"
#define gotoxy(x,y) SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1,y-1})
#define appleRandom() gotoxy(apple.x,apple.y);putchar(' ');apple.x=((1+rand()%(width-3))+1);apple.y=((1+rand()%(height-3))+1)
#define quit() gotoxy(width+1,2);printf("GAME%cOVER",32);gotoxy(width+4,height+4);\
				getchar();system("cls");exit(0)
#define updateScore() gotoxy(width+1,1);printf("%d",tailCount)
#define delayVal 50
#define width 30
#define height 15
#define size (width*height)


typedef struct{
	int x;
	int y;
} GameObject;

GameObject head = {width/2,height/2};
GameObject apple;
GameObject tails[size];
unsigned int tailCount = 0;
unsigned char direction = 4;
void printBoard(void){
	int i,j;
	for(j = 1;j < height;j++){
		for(i = 1;i < width;i++){
			if(m == width-1 || u==height-1){
				gotoxy(m,u);
				putchar('&');
			}
		}
	}
}
void update(void){
	int i,j;
	gotoxy(head.x,head.y);
	putchar('#');
	gotoxy(apple.x,apple.y);
	putchar('@');
	for(i = 0;i < tailCount;i++){
		gotoxy(tails[i].x,tails[i].y);
		putchar('#');
	}
}
void clearSprite(void){
	int i,j;
	gotoxy(head.x,head.y);
	putchar(' ');
	for(i = 0;i < tailCount;i++){
		gotoxy(tails[i].x,tails[i].y);
		putchar(' ');
	}
}
void headTo(unsigned char val){
	switch(val){
		case 'H':
		case 'w':
		if(direction != 3)direction = 1;
		break;
		case 'P':
		case 's':
		if(direction != 1)direction = 3;
		break;
		case 'M':
		case 'd':
		if(direction != 0)direction = 2;
		break;
		case 'K':
		case 'a':
		if(direction != 2)direction = 0;
		break;
	}
}
void move(void){
	if(head.x == apple.x && head.y == apple.y){
		appleRandom();
		tails[tailCount++] = (GameObject){1,1};
		updateScore();
	}
	int i;
	for(i = tailCount - 1;i > 0;i--){
		tails[i] = tails[i - 1];
	}
	if(tailCount > 0){
		tails[0] = head;
	}
	switch(direction){
		case 1:
		head.y--;
		break;
		case 3:
		head.y++;
		break;
		case 2:
		head.x++;
		break;
		case 0:
		head.x--;
		break;
	}
}
void collisionCheck(void){
	int i;
	for(i = 0;i < tailCount;i++){
		if(tails[i].x == apple.x && tails[i].y == apple.y){
			appleRandom();			
		}
	}
	if(head.x <= 1 || head.y <= 1 || head.x >= width-1 || head.y >= height-1){
		quit();
	}
	else{
		for(i = 0;i < tailCount;i++){
			if(head.x == tails[i].x && head.y == tails[i].y){
				quit();
			}
		}
	}
}

int main(void){
	srand(time(0));
	unsigned char key;
	printBoard();
	updateScore();
	appleRandom();
	for(;;){
		move();
		update();
		collisionCheck();
		if(kbhit()){
			key = getch();
			if(key == 224)headTo(getch());
			else headTo(key);
		}
		Sleep(delayVal);
		clearSprite();
	}
	return 0;
}
