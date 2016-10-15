#include <iostream>
#include <Windows.h>
#include "console.h"
#include <conio.h>
#include <time.h>
using namespace std;
enum eDirection{UP,DOWN,LEFT,RIGHT,STOP=0};
const int width = 25;
const int height = 25;
bool gameOver;
//Tọa độ x,y
struct Coordinates
{
	int x, y;
};
struct Fruit
{
	Coordinates fruit;
};
struct Snake
{
	// đốt rắn
	Coordinates dot[20];
	// rắn có n đốt
	int n;
	//Điều hướng
	eDirection dir;

};
void Initialize(Snake &snake,Fruit &fr)
{
	gameOver = false;
	//Rắn có 1 cái đầu đầu tiên
	snake.n = 1;
	snake.dot[0].x = 0;
	snake.dot[0].y = 0;
	snake.dir = RIGHT;
	
	fr.fruit.x = 10;
	fr.fruit.y = 10;
}
void Show(Snake snake,Fruit fr)
{
	system("cls");
	
	//In màu mặc định tường
	TextColor(default_ColorCode);
	for (int i = 0; i < width; i++)
	{
		gotoXY(i, height);
		putchar(196);
	}
	TextColor(default_ColorCode);
	for (int i = 0; i < height; i++)
	{
		gotoXY(width,i);
		putchar(179);
	}

	//Rắn ăn hoa quả
	TextColor(ColorCode_Blue);
	gotoXY(fr.fruit.x, fr.fruit.y);
	putchar('@');

	TextColor(ColorCode_Green);
	for (int i = 0; i < snake.n; i++)
	{
		gotoXY(snake.dot[i].x, snake.dot[i].y);
		putchar('*');
	}
}
void Direction(Snake &snake)
{
	//Cái thân theo sau cái đầu
	for (int i = snake.n - 1; i > 0; i--)
	{
		snake.dot[i] = snake.dot[i-1];
	}
	//Hàm phát hiện phím bất kỳ trên bàn phím
	if (_kbhit())
	{
		int key = _getch(); // lấy mã 
		//Điều khiển cái đầu
		if (key == 'a' || key == 'A')
			snake.dir = LEFT;
		else if (key == 'd' || key == 'D')
			snake.dir = RIGHT;
		else if (key == 'w' || key == 'W')
			snake.dir = UP;
		else if (key == 's' || key == 'S')
			snake.dir = DOWN;
	}
	//Theo tọa độ x,y hướng lên giảm y, hướng xuống tăng y, hướng trái giảm x, hướng phải tăng x
	if (snake.dir == UP)
		snake.dot[0].y--;
	else if (snake.dir == DOWN)
		snake.dot[0].y++;
	else if (snake.dir == LEFT)
		snake.dot[0].x--;
	else if (snake.dir == RIGHT)
		snake.dot[0].x++;
}
int Logic(Snake &snake, Fruit &fr, int &sleeptime)
{
	if (snake.dot[0].x == fr.fruit.x && snake.dot[0].y == fr.fruit.y)
	{
		for (int i=snake.n-1;i>0; i--)
		{
			snake.dot[i] = snake.dot[i - 1];
		}
		snake.n++;
		//Theo hướng sẽ mọc đầu theo hướng đó
		if (snake.dir == UP)
			snake.dot[0].y--;
		else if (snake.dir == DOWN)
			snake.dot[0].y++;
		else if (snake.dir == LEFT)
			snake.dot[0].x--;
		else if (snake.dir == RIGHT)
			snake.dot[0].x++;

		fr.fruit.x = rand() % width;
		fr.fruit.y = rand() % height;

		//Thời gian ăn hoa quả.
		sleeptime -= 20;
	}
	if (snake.dot[0].x < 0 || snake.dot[0].x > width || snake.dot[0].y < 0 || snake.dot[0].y > height)
	{
		return -1;
	}
	for (int i = 1; i < snake.n; i++)
	{
		if (snake.dot[0].x == snake.dot[i].x && snake.dot[0].y == snake.dot[i].y)
			return -1;
	}
}
int main()
{
	//Khởi tạo bộ sinh số ngẫu nhiên
	srand(time == (NULL));
	int key = 0;
	int sleeptime = 200;

	Snake snake;
	Fruit fr;
	Initialize(snake,fr);
	while (1)
	{
		//Hiển thị
		Show(snake,fr);
		//Điều khiển
		Direction(snake);
		//Xử lý
		key = Logic(snake, fr,sleeptime);
		if (key == -1)
		{
			gotoXY(width + 1, 10);
			cout << "Gameover";
			while (_getch() != 13);
			break;
		}

		//Kết thúc game
		Sleep(sleeptime);
	}
	
	return 0;
}