#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

bool GameStatus;
const int length = 52;
const int width = 15;
int x, y, fruitX, fruitY, score;
int tailX[1000];
int tailY[1000];
int countTail;

enum Direction { Stop = 0, Left, Right, Up, Down };
Direction direction;

void SetSettings()
{
	srand(time(NULL));
	GameStatus = true;
	x = length / 2;
	y = width / 2;
	fruitX = rand() % (length - 1);
	fruitY = rand() % width;
	direction = Stop;
	score = 0;
	CONSOLE_CURSOR_INFO CCI;
	CCI.bVisible = false;
	CCI.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CCI);
	system("color F2");
}
void DrawMap()
{
	system("cls");
	cout << ' ';
	for (int i = 0; i < length - 1; i++)
		cout << '_';
	cout << endl;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (j == 0 or j == length - 1)
				cout << '|';
			if (i == y and j == x)
				cout << '&';
			else if (i == fruitY and j == fruitX)
				cout << '$';
			else
			{
				bool print = false;
				for (int k = 0; k < countTail; k++)
				{
					if (tailX[k] == j and tailY[k] == i)
					{
						print = true;
						cout << 'O';
					}
				}
				if (!print)
				cout << ' ';
			}
		}
		cout << endl;
	}
	for (int i = 0; i < length + 1; i++)
		cout << '"';
	cout << " Score: " << score << endl;

}
void Control()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			if (direction!=Down)
			direction = Up;
			break;
		case 72:
			if (direction != Down)
			direction = Up;
			break;
		case 's':
			if (direction != Up)
			direction = Down;
			break;
		case 80:
			if (direction != Up)
			direction = Down;
			break;
		case 'a':
			if (direction != Right)
			direction = Left;
			break;
		case 75:
			if (direction != Right)
			direction = Left;
			break;
		case 'd':
			if (direction != Left)
			direction = Right;
			break;
		case 77:
			if (direction != Left)
			direction = Right;
			break;
		case 'p':
			GameStatus = false;
			break;
		}

	}
}
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int tempX, tempY;
	tailX[0] = x;
	tailY[0] = y;
	
	for (int i = 1; i < countTail; i++)
	{
		tempX = tailX[i];
		tempY = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = tempX;
		prevY = tempY;
	}
	switch (direction)
	{
	case Up:
		y--;
		break;
	case Down:
		y++;
		break;
	case Left:
		x--;
		break;
	case Right:
		x++;
		break;
	}

	if (y == width) y = 0;
	else if (y == -1) y = width-1;
	if (x == length-1) x = 0;
	else if (x == -1) x = length-2;
	
	for (int i = 0; i < countTail; i++)
	{
		if (tailX[i] == x and tailY[i] == y)
			GameStatus = false;
	}
	if (x == fruitX and y == fruitY)
	{
		score++;
		countTail++;
		fruitX = rand() % (length - 1);
		fruitY = rand() % width;
	}
}
int main()
{
	SetSettings();
	while (GameStatus)
	{
		DrawMap();
		Control();
		Logic();
	}
	system("color 0A");
	cout << "                      GAME OVER" << endl;
}