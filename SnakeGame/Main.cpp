#include <iostream>
#include <conio.h>
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score; // Biến toàn cục
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, UP, LEFT, RIGHT, DOWN }; // Hướng đi
eDirection dir;
void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width; // Tạo ra đồ ăn cho rắn
	fruitY = rand() % height;
	score = 0; // Cho điểm mặc định là 0 
}
void Draw()
{
	system("cls"); // system("clear");
				   //Tạo khung cho rắn chạy
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "#";

			if (i == y && j == x)
				cout << "O";
			else if (i == fruitY && j == fruitX)
				cout << "o";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if(!print)
					cout << " ";
			}

			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score : " << score << endl;
}
void Input()
{
	//hàm keyboard hit ( nhận 1 ký tự trong vùng đệm bàn phím )
	if (_kbhit())
	{
		//Tạo control điều khiển rắn
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic()
{
	//Tạo thân mình con rắn
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;

	}
	switch (dir)
	{
	case STOP:
		break;
	case UP:
		y--;
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case DOWN:
		y++;
		break;	
	default:
		break;
	}
	//Nếu con rắn đụng tường sẽ dừng lại
	/*if (x > width || x<0 || y>height || y < 0)
	{
		gameOver = true;
	}*/

	//Nếu con rắn từ 20 điểm trở lên sẽ không bị dừng khi đụng tường
	if (x >= width) x = 0; else if (x < 0) x = width - 1;
	if (y >= height) y = 0; else if (y < 0) y = height - 1;
	for (int i = 0; i < nTail; i++)
	{
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;
	}
	//Nếu đụng trúng đồ ăn sẽ tăng điểm lên
	if (x == fruitX && y == fruitY)
	{
		score += 10;
		//Tạo đồ ăn mới
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;

	}
}
int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		//Sleep(10); sleep(10);
	}
	return 0;
}