#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#define HERO '@'

void MonsterMaker(int *Y, int *X){
	int YMax, XMax;
	getmaxyx(stdscr, YMax, XMax);
	*Y = rand()%YMax;
	*X = rand()%XMax;
}

void GoldMaker(int *Y, int *X){
	int YMax, XMax;
	getmaxyx(stdscr, YMax, XMax);
	*Y = rand()%YMax;
	*X = rand()%XMax;
}

void StartGame(){
	int Y, X;
	initscr();
	noecho();
	cbreak();
	srand(time(NULL));
	for(int i = 0; i < 9; i++){
		MonsterMaker(&Y, &X);
		mvaddch(Y, X, 'M');
	}
	for(int i = 0; i < 9; i++){
		GoldMaker(&Y, &X);
		mvaddch(Y, X, 'G');
	}
	move(1, 1);
}

void MoveCursor(input){
	int YPos, XPos, Pos, OldY, OldX;
	getyx(stdscr, YPos, XPos);
	OldY = YPos;
	OldX = XPos;
	input = getch();
	switch(input){
		case 'z': 
            YPos++;
            break;
        case 's': 
            XPos++;
            break;
        case 'a':
            XPos--;
            break;
        case 'w':
            YPos--;
            break;
        default:
            break;
	}
	Pos = mvinch(YPos, XPos);
	if (Pos == ' '){
		for(int i = 1; i < 9; i++){
			mvaddch(1, i, ' ');
		}
		mvaddch(YPos, XPos, HERO);
		mvaddch(OldY, OldX, ' ');
		move(YPos, XPos);
		refresh();
	}else if(Pos == 'G'){
		mvaddch(YPos, XPos, HERO);
		mvaddch(OldY, OldX, ' ');
		move(YPos, XPos);
		refresh();
	}else if (Pos == 'M'){
		mvprintw(1, 1, "Monster!");
		move(OldY, OldX);
		refresh();
	}
}

void GameLoop(){
	char input;
	do{
		input = getch();
		MoveCursor(input);
		refresh();
	}while(input != 'q');
}

void EndGame(){
	endwin();
}

int main(){
	char input;
	printf("Would you like to play a game of rogue?(y/n)\n\n");
	scanf("%c", &input);
	if(input == 'y'){
	StartGame();
	GameLoop();
	EndGame();
	}else{
		return 1;
	}
}
