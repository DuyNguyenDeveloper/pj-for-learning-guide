#include <iostream>
#include <conio.h>
#include "console.h"
using namespace std;
#define MAX 100
enum eDirection{UP,LEFT,DOWN,RIGHT};
const int xwidth = 20;
const int yheight = 20;
int score;
struct Coordinates
{
	//Tọa độ x,y tương đương 1 đốt của con rắn
	int x, y;
};
struct Snake
{
	//1 đốt tương đượng 1 tọa độ gồm (x,y)
	Coordinates dot[MAX];
	//Con rắn có n đốt
	int n;
	//Điều khiển rắn
	eDirection dir;
	
};
struct Fruit
{
	Coordinates fruit;
};
void Initialize_Snake(Snake &s,Fruit &fr)
{
	s.n = 1;
	s.dot[0].x = 0;
	s.dot[0].y = 0;
	s.dir = RIGHT;
	fr.fruit.x = 10;
	fr.fruit.y = 10;

	score = 0;

}
void Show_Snake(Snake s,Fruit &fr)
{
	

	//Xóa màn hình trước
	system("cls");
	TextColor(default_ColorCode);
	//Vẽ tường
	for (int i = 0; i < xwidth; i++)
	{
		gotoXY(i, yheight);
		putchar(196);
	}
	TextColor(default_ColorCode);
	for (int i = 0; i < yheight; i++)
	{
		gotoXY(xwidth, i);
		putchar(179);
	}

	//Hiển thị thức ăn
	gotoXY(fr.fruit.x, fr.fruit.y);
	putchar('@');

	

	//Hiển thị con rắn
	TextColor(ColorCode_Yellow);
	gotoXY(s.dot[0].x, s.dot[0].y); // Di chuyển con trỏ tới tọa độ x,y
	putchar('*');
	for (int i = 1; i < s.n; i++)
	{
		gotoXY(s.dot[i].x, s.dot[i].y);
		putchar('*');
	}

	gotoXY(1,yheight+2);	
	cout << "Score = " << score;
	
}
void Direction(Snake &s)
{
	//Mỗi lần di chuyển thì rắn được thêm 1 đốt vào ( cái thân theo sau cái đầu )
	for (int i = s.n; i > 0; i--)
	{
		s.dot[i] = s.dot[i-1];
	}
	if (_kbhit())
	{
		int key = _getch();
		if (key == 'a' || key == 'A')
			s.dir = LEFT;
		else if (key == 'd' || key == 'D')
			s.dir = RIGHT;
		else if (key == 'w' || key == 'W')
			s.dir = UP;
		else if (key == 's' || key == 'S')
			s.dir = DOWN;
	}
	if (s.dir == LEFT)
		s.dot[0].x--;
	else if (s.dir == RIGHT)
		s.dot[0].x++;
	else if (s.dir == UP)
		s.dot[0].y--;
	else if (s.dir == DOWN)
		s.dot[0].y++;
}
int Logic(Snake &s, Fruit &fr,int sleeptime)
{
	if (s.dot[0].x == fr.fruit.x && s.dot[0].y == fr.fruit.y)
	{
		for (int i = s.n - 1; i > 0; i--)
		{
			s.dot[i] = s.dot[i - 1];
			
		}
		//Mỗi lần ăn xong sẽ tăng thân lên.
		s.n++;
		if (s.dir == UP)
			s.dot[0].y--;
		else if (s.dir == DOWN)
			s.dot[0].y++;
		else if (s.dir == LEFT)
			s.dot[0].x--;
		else if (s.dir == RIGHT)
			s.dot[0].x++;

		fr.fruit.x = rand() % xwidth;
		fr.fruit.y = rand() % yheight;
		score += 10;

		sleeptime -= 20;
	}
	
	//Trường hợp đụng tường
	if (s.dot[0].x<0 || s.dot[0].x>xwidth || s.dot[0].y<0 || s.dot[0].y>yheight)
		return -1;	

	//Trường hợp đầu đụng cuối
	for (int i = 1; i < s.n; i++)
	{
		if (s.dot[0].x == s.dot[i].x && s.dot[0].y == s.dot[i].y)
			return -1;
	}
}
void main()
{
START:
	Snake s;
	Fruit fr;
	Initialize_Snake(s,fr);
	int sleeptime = 200;
	while (1)
	{
	
		//Hiển thị
		Show_Snake(s,fr);
		//Điều khiển
		Direction(s);
		//Xử lý
		int key = Logic(s, fr,sleeptime);	
		if (key == -1)
		{
			gotoXY(xwidth + 15, 10);
			cout << "Rat tiec! Ban da thua!!!";
			while (_getch() != 13);
			break;
		}
		//Kết thúc game
		Sleep(sleeptime);
	}
	char question;
	gotoXY(xwidth + 15, 10);
	cout << "Do you want again!!(y/n) : ";
	cin >> question;
	switch (question)
	{
	case 'y': goto START;
	case 'n': break;
	}
}
