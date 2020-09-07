// Snake game in very basic level without graphic, just ascii for training

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define M 40
#define N 20
void RandomApple();
void print();
int getch_noblock();
void resetgame();
void RandomApple();
void ResetScreenPosition();
void movement();

int i, j,Gy, field[N][M],Game=1,x,y,Head,Tail,var,dir='d',speed=200,score=0,flag=0;

int main() {
	int p = 1, exit = 1;
	char reset;
	
	
	while (exit)
	{
		resetgame();
		while (Game) {

			ResetScreenPosition();
			movement();
			Sleep(speed);
			print();

		}
		
	}
	scanf_s("%d");

}

void print() {
	 
		for (i = 0; i < N; i++, printf("\n"))
			for (j = 0; j < M; j++)
				if (i == 0 && j == 0) // first line first char
					printf("%c", 201);
				else if (i == 0 && j == M - 1) // first line end char
				{
					printf("%c", 187);
					printf("         Current score: %d ", score);
				}

				else if (i == N - 1 && j == 0) // end line first char
					printf("%c", 200);
				else if (i == N - 1 && j == M - 1) //end line end char
					printf("%c", 188);
				else if (i == 0) //first line between start and end char
					printf("%c", 205);
				else if (j == 0 || j == M - 1) // start and end lines char
					printf("%c", 186);
				else if (i == N - 1) //end line between start and end char
					printf("%c", 205);
				else if (field[i][j] == 0) // if snake or apple isnt there just print blank
					printf(" ");
				else if (field[i][j] > 0 && field[i][j] != Head)
					printf("%c", 177);
				else if (field[i][j] == Head) // snake head
					printf("%c", 178);
				else if (field[i][j] == -1)
					printf("%c",153);


	
}

void snakebody() {
	for (i = 0; i < N; i++)
		for (j = 0; j < M; j++)
			field[i][j] = 0;
	Head = 5; Tail = 1;
	x = N / 2, y = M / 2; // position snake in center
	Gy = y; // setting snake head to be 5 and body to be 4 3 2 and at last 1.
	for (i = 0; i < Head; i++) {
		Gy++;
		field[x][Gy - Head] = i + 1;
	}

}
// Game based on printing so restting print place every time.
void ResetScreenPosition() {
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}
// if next moving spot is apple then this function perform eating
void eating() {

	flag = 1;
	speed -= 5;
	score++;

}
//checking every time if next move is lekgal - if not -ends the game.
void checkendgame() {
	if (x<1 || y<1 || x>N - 1 || y>M - 1 || (field[x][y] != 0 && field[x][y] != -1)) // if its ouside border or its touching itself
	{
		Game = 0; // end of game

		return;
	}
}
void movement() {

	var = getch_noblock(); // return the char value as int
	var = tolower(var); // int value of char no metter with capslock or not

	if ((var == 'w' || var == 'd' || var == 's' || var == 'a') && (abs(dir - var) > 5)) dir = var; // saving the last movement so it will be continously moving. 
	Head++;

	if (dir == 'd')
	{
		y++;
		checkendgame();
		if (field[x][y] == -1)
			eating();

		field[x][y] = Head;

	}
	else if (dir == 'a')
	{
		y--;
		checkendgame();
		if (field[x][y] == -1)
			eating();
		field[x][y] = Head;
	}
	else if (dir == 'w')
	{
		x--;
		checkendgame();
		if (field[x][y] == -1)
			eating();
		field[x][y] = Head;
	}
	else if (dir == 's')
	{
		x++;
		checkendgame();
		if (field[x][y] == -1)
			eating();
		field[x][y] = Head;
	}

	if (flag == 0) //if there isnt an apple get rid of tail
	{
		for (i = 0; i < N; i++) // getting rid of the tail
			for (j = 0; j < M; j++)
				if (field[i][j] == Tail)
				{

					field[i][j] = 0;
					break;
				}
		Tail++;
	}
	else {
		flag = 0;// apple flag resseted
		RandomApple(); // new apple

	}
}

int getch_noblock() {
	if (_kbhit())
		return _getch();
	else
		return -1;
}
void RandomApple() {
	int tempx = rand() % N;
	int tempy = rand() % M;
	while (field[tempx][tempy] != 0) // check that the apple is not generate on snake's body.
	{
		tempx = rand() % N;
		tempy = rand() % M;
	}
	field[tempx][tempy] = -1;
}

void resetgame() {
	score = 0, speed = 150;
	Game = 1, flag = 0;
	snakebody();
	RandomApple();
	dir = 'd';
}