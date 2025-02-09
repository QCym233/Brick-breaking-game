#if 1
#include<stdio.h>
#include <graphics.h>//EasyX_图形界面库
#include <time.h>
#include<stdlib.h>
#include<easyx.h>
#include <windows.h>
#include<iostream>

//分数和速度
int score = 0;
int speed = 8;

//各个图片的变量
IMAGE dt1;//春
IMAGE dt2;//夏
IMAGE dt3;//秋
IMAGE dt4;//冬
IMAGE dt_window;

IMAGE dt11;//春
IMAGE dt22;//夏
IMAGE dt33;//秋
IMAGE dt44;//冬

IMAGE rw1;
IMAGE rw2;
IMAGE rw3;
IMAGE rw_window;

IMAGE qiou1;
IMAGE qiou2;
IMAGE qiou3;

IMAGE speed_window;



int Character_selection;//人物选择接收变量
int Stage_selection;//关卡选择

//画砖块
int map2[21][21] = { 0 };//砖块数组
//窗口接收变量
HWND hwnd_window = NULL;
HWND hwnd3 = NULL;
//消除图片黑色背景
void transparentimage(int x, int y, IMAGE img) {
	IMAGE img1;
	DWORD* d1;
	img1 = img;
	d1 = GetImageBuffer(&img1);
	float h, s, l;
	for (int i = 0; i < img1.getheight() * img1.getwidth(); i++) {
		RGBtoHSL(BGR(d1[i]), &h, &s, &l);
		if (l < 0.03) {
			d1[i] = BGR(WHITE);
		}
		if (d1[i] != BGR(WHITE)) {
			d1[i] = 0;
		}
	}
	putimage(x, y, &img1, SRCAND);
	putimage(x, y, &img, SRCPAINT);
	//	putimage(x+100,y,&img1);
	//	putimage(x+200,y,&img);
}
//人物加载
void init_rw()
{
	loadimage(&rw1, "./tutu/44.png", 200, 200);
	loadimage(&rw2, "./tutu/55.png", 200, 200);
	loadimage(&rw3, "./tutu/666.png", 200, 200);
}
//球的图片加载
void init_qiou()
{
	if(Character_selection==1)
	loadimage(&qiou1, "D:\\c语言\\打砖块游戏\\tutu\\球\\博丽灵梦.png", 30, 30);
	if (Character_selection == 2)
	loadimage(&qiou2, "D:\\c语言\\打砖块游戏\\tutu\\球\\雾雨魔理沙.png", 30, 30);
	if (Character_selection == 3)
	loadimage(&qiou3, "D:\\c语言\\打砖块游戏\\tutu\\球\\伊吹萃香.png", 30, 30);
}
//地图加载
void init_dt()
{
	loadimage(&dt11, "D:\\c语言\\打砖块游戏\\tutu\\背景春.jpg", 1000, 800);//春
	loadimage(&dt22, "D:\\c语言\\打砖块游戏\\tutu\\背景夏.jpg", 1000, 800);//夏
	loadimage(&dt33, "D:\\c语言\\打砖块游戏\\tutu\\背景秋.jpg", 1000, 800);//秋
	loadimage(&dt44, "D:\\c语言\\打砖块游戏\\tutu\\背景冬.jpg", 1000, 800);//冬
}
//自定义速度窗口
void VariableSpeed1()
{
	initgraph(800, 500);
	HWND hwnd_speed = GetHWnd();
	SetWindowPos(hwnd_speed, NULL, 300, 150, 0, 0, SWP_NOSIZE);

	loadimage(&speed_window, "D:\\c语言\\打砖块游戏\\tutu\\菜单界面三选一\\速度选择.jpg", 800, 500);
	putimage(0, 0, &speed_window);

	settextstyle(50, 20, _T("黑体"));
	setbkmode(TRANSPARENT);//消除字体黑框

	outtextxy(70, 90, "菜鸟(0)");


	outtextxy(70, 180, "普通(1)");


	outtextxy(70, 280, "困难(2)");


	outtextxy(70, 380, "炼狱(3)");

	char inputValue[100];

	InputBox(inputValue, 100, "请选择您的关卡难度(输入对应数字)", 0, 0, 200, 30);
	sscanf_s(inputValue, "%d", &speed);


}
//关卡选择窗口
void Stage_selection_window()
{
	initgraph(800, 500);
	HWND hwnd1 = GetHWnd();
	SetWindowPos(hwnd1, NULL, 300, 150, 0, 0, SWP_NOSIZE);
	char inputValue[100];
	settextstyle(20, 0, _T("黑体"));

	loadimage(&dt_window, "D:\\c语言\\打砖块游戏\\tutu\\菜单界面三选一\\关卡选择.jpg", 800, 500);
	putimage(0, 0, &dt_window);

	setcolor(RGB(153, 255, 0));
	setbkmode(TRANSPARENT);//消除字体黑框
	outtextxy(70, 110, "春(1)");
	loadimage(&dt1, "./tutu/背景春小.jpg", 150, 150);
	putimage(30, 150, &dt1);

	outtextxy(240, 320, "夏(2)");
	loadimage(&dt2, "./tutu/背景夏小.jpg", 150, 150);
	putimage(200, 350, &dt2);

	outtextxy(520, 320, "秋(3)");
	loadimage(&dt3, "./tutu/背景秋小.jpg", 150, 150);
	putimage(480, 350, &dt3);

	outtextxy(660, 100, "冬(4)");
	loadimage(&dt4, "./tutu/背景冬小.jpg", 150, 150);
	putimage(620, 150, &dt4);

	InputBox(inputValue, 100, "请选择您的游戏关卡(输入对应数字):", 0, 0, 200, 30);
	sscanf_s(inputValue, "%d", &Stage_selection);
}
//绘制砖块和地图背景
void drawMap1()//春
{
	putimage(0, 0, &dt11);
	setlinestyle(PS_SOLID, 2);//实线
	setlinecolor(BLACK);
	for (int i = 1; i < 21; i++)
	{
		for (int j = 1; j < 21; j++)
		{
			if (i == 1 || i == 2 || i == 20)
			{
				if (map2[i][j] == 0) continue;
				if (1)
				{
					setfillcolor(LIGHTGRAY);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 3)
			{
				if (map2[i][j] == 0) continue;
				if ((j >= 1 && j <= 4) || (j >= 7 && j <= 9) || (j >= 12 && j <= 14) || (j >= 17 && j <= 20))
				{
					setfillcolor(LIGHTGRAY);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(RED);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 4)
			{
				if (map2[i][j] == 0) continue;
				if ((j >= 1 && j <= 4) || j == 13 || j == 8 || (j >= 17 && j <= 20))
				{
					setfillcolor(LIGHTGRAY);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(RED);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i >= 5 && i <= 8)
			{
				if (map2[i][j] == 0) continue;
				if ((j >= 1 && j <= 4) || (j >= 17 && j <= 20))
				{
					setfillcolor(LIGHTGRAY);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(RED);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 9)
			{
				if (map2[i][j] == 0) continue;
				if ((j >= 1 && j <= 5) || (j >= 16 && j <= 20))
				{
					setfillcolor(LIGHTGRAY);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(RED);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 10)
			{
				if (map2[i][j] == 0) continue;
				if ((j >= 1 && j <= 6) || (j >= 15 && j <= 20))
				{
					setfillcolor(LIGHTGRAY);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(RED);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 11)
			{
				if (map2[i][j] == 0) continue;
				if ((j >= 4 && j <= 5) || (j >= 16 && j <= 17))
				{
					setfillcolor(GREEN);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				if ((j >= 8 && j <= 13))
				{
					setfillcolor(RED);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(LIGHTGRAY);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 12)
			{
				if (map2[i][j] == 0) continue;
				if ((j >= 4 && j <= 6) || (j >= 10 && j <= 11) || (j >= 15 && j <= 17))
				{
					setfillcolor(GREEN);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(LIGHTGRAY);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 13)
			{
				if (map2[i][j] == 0) continue;
				if ((j >= 4 && j <= 7) || (j >= 10 && j <= 11) || (j >= 14 && j <= 17))
				{
					setfillcolor(GREEN);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(LIGHTGRAY);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 14)
			{
				if (map2[i][j] == 0) continue;
				if ((j >= 4 && j <= 8) || (j >= 10 && j <= 11) || (j >= 13 && j <= 17))
				{
					setfillcolor(GREEN);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(LIGHTGRAY);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i >= 15 && i <= 17)
			{
				if (map2[i][j] == 0) continue;
				if ((j >= 4 && j <= 17))
				{
					setfillcolor(GREEN);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(LIGHTGRAY);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 18)
			{
				if (map2[i][j] == 0) continue;
				if ((j >= 5 && j <= 16))
				{
					setfillcolor(GREEN);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(LIGHTGRAY);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 19)
			{
				if (map2[i][j] == 0) continue;
				if ((j >= 6 && j <= 15))
				{
					setfillcolor(GREEN);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(LIGHTGRAY);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
		}
	}
}
void drawMap2()//夏
{
	putimage(0, 0, &dt22);
	setlinestyle(PS_SOLID, 2);//实线
	setlinecolor(BLACK);
	for (int i = 1; i < 21; i++)
	{

		for (int j = 1; j < 21; j++)
		{
			if (i == 1 || i == 20)
			{
				if (map2[i][j] == 0) continue;
				if (j == 10 || j == 11)
				{
					setfillcolor(YELLOW);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(RED);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 2 || i == 19)
			{
				if (map2[i][j] == 0) continue;
				if (j == 6 || j == 10 || j == 11 || j == 15)
				{
					setfillcolor(YELLOW);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(RED);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 3 || i == 18)
			{
				if (map2[i][j] == 0) continue;
				if ((j <= 7 && j >= 5) || j == 10 || j == 11 || (j <= 16 && j >= 14))
				{
					setfillcolor(YELLOW);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(RED);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 4 || i == 17)
			{
				if (map2[i][j] == 0) continue;
				if ((j <= 7 && j >= 6) || (j <= 15 && j >= 14))
				{
					setfillcolor(YELLOW);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(RED);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 5 || i == 16)
			{
				if (map2[i][j] == 0) continue;
				if (j == 3 || j == 18 || (j <= 12 && j >= 9))
				{
					setfillcolor(YELLOW);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(RED);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 6 || i == 15)
			{
				if (map2[i][j] == 0) continue;
				if ((j <= 4 && j >= 2) || (j <= 14 && j >= 7) || (j <= 19 && j >= 17))
				{
					setfillcolor(YELLOW);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(RED);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 7 || i == 14)
			{
				if (map2[i][j] == 0) continue;
				if ((j <= 4 && j >= 3) || (j <= 14 && j >= 7) || (j <= 18 && j >= 17))
				{
					setfillcolor(YELLOW);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(RED);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 8 || i == 13)
			{
				if (map2[i][j] == 0) continue;
				if (j <= 15 && j >= 6)
				{
					setfillcolor(YELLOW);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(RED);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 9 || i == 12)
			{
				if (map2[i][j] == 0) continue;
				if (j <= 16 && j >= 5)
				{
					setfillcolor(YELLOW);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(RED);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 10 || i == 11)
			{
				if (map2[i][j] == 0) continue;
				if ((j <= 16 && j >= 5) || (j <= 3 && j >= 1) || (j <= 20 && j >= 18))
				{
					setfillcolor(YELLOW);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(RED);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
		}

	}
}
void drawMap3()//秋
{
	putimage(0, 0, &dt33);
	setlinestyle(PS_SOLID, 2);//实线
	setlinecolor(BLACK);

	//i是行,j是列
	for (int i = 1; i < 19; i++)
	{
		for (int j = 1; j < 19; j++)
		{
			if (i == 1)
			{
				if (map2[i][j] == 0) continue;
				if (j == 6 || j == 7 || j == 9 || j == 10 || j == 12)
				{
					setfillcolor(RGB(219, 91, 12));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(WHITE);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 2)
			{
				if (map2[i][j] == 0) continue;
				if (j == 5 || j == 8 || j == 11 || j == 13 || j == 14)
				{
					setfillcolor(RGB(219, 91, 12));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else if (j == 6 || j == 7 || j == 9 || j == 10)
				{
					setfillcolor(RGB(243, 184, 8));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(WHITE);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 3)
			{
				if (map2[i][j] == 0) continue;
				if (j == 3 || j == 5 || j == 12 || j == 15 || j == 16)
				{
					setfillcolor(RGB(219, 91, 12));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else if ((j >= 6 && j <= 11) || j == 13 || j == 14)
				{
					setfillcolor(RGB(243, 184, 8));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(WHITE);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 4)
			{
				if (map2[i][j] == 0) continue;
				if (j == 2 || j == 4 || j == 17)
				{
					setfillcolor(RGB(219, 91, 12));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else if ((j >= 5 && j <= 16) || j == 3)
				{
					setfillcolor(RGB(243, 184, 8));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(WHITE);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 5)
			{
				if (map2[i][j] == 0) continue;
				if (j == 2 || j == 17)
				{
					setfillcolor(RGB(219, 91, 12));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else if ((j >= 3 && j <= 16))
				{
					setfillcolor(RGB(243, 184, 8));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(WHITE);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 6)
			{
				if (map2[i][j] == 0) continue;
				if (j == 1 || j == 18)
				{
					setfillcolor(RGB(219, 91, 12));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else if ((j >= 2 && j <= 17))
				{
					setfillcolor(RGB(243, 184, 8));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(WHITE);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 7)
			{
				if (map2[i][j] == 0) continue;
				if (j == 1 || j == 18)
				{
					setfillcolor(RGB(219, 91, 12));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else if ((j >= 3 && j <= 16))
				{
					setfillcolor(RGB(243, 184, 8));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else if (j == 2 || j == 17)
				{
					setfillcolor(RGB(243, 157, 8));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(WHITE);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 8)
			{
				if (map2[i][j] == 0) continue;
				if (j == 1 || j == 18)
				{
					setfillcolor(RGB(219, 91, 12));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else if ((j >= 5 && j <= 13))
				{
					setfillcolor(RGB(243, 184, 8));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else if ((j >= 2 && j <= 4) || (j >= 14 && j <= 16))
				{
					setfillcolor(RGB(243, 157, 8));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(WHITE);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 9)
			{
				if (map2[i][j] == 0) continue;
				if ((j >= 2 && j <= 4) || (j >= 14 && j <= 16))
				{
					setfillcolor(RGB(219, 91, 12));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else if ((j >= 7 && j <= 11))
				{
					setfillcolor(RGB(243, 184, 8));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else if ((j >= 5 && j <= 6) || (j >= 12 && j <= 13))
				{
					setfillcolor(RGB(243, 157, 8));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(WHITE);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 10)
			{
				if (map2[i][j] == 0) continue;
				if ((j >= 5 && j <= 6) || (j >= 12 && j <= 13))
				{
					setfillcolor(RGB(219, 91, 12));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else if ((j >= 8 && j <= 10))
				{
					setfillcolor(RGB(243, 184, 8));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else if (j == 7 || j == 11)
				{
					setfillcolor(RGB(243, 157, 8));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(WHITE);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 11)
			{
				if (map2[i][j] == 0) continue;
				if (j == 7 || j == 11)
				{
					setfillcolor(RGB(219, 91, 12));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else if ((j >= 8 && j <= 10))
				{
					setfillcolor(RGB(243, 157, 8));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(WHITE);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 12)
			{
				if (map2[i][j] == 0) continue;
				if (j == 8 || j == 10)
				{
					setfillcolor(RGB(219, 91, 12));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else if (j == 9)
				{
					setfillcolor(RGB(243, 157, 8));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(WHITE);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i >= 13 && i <= 17)
			{
				if (map2[i][j] == 0) continue;
				if (j == 9)
				{
					setfillcolor(BLACK);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(WHITE);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 18)
			{
				if (map2[i][j] == 0) continue;
				if (j == 10)
				{
					setfillcolor(BLACK);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
				else
				{
					setfillcolor(WHITE);
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
		}
	}


}
void drawMap4()//冬
{
	putimage(0, 0, &dt44);
	setlinestyle(PS_SOLID, 2);//实线
	setlinecolor(BLACK);

	//i是行,j是列
	for (int i = 0; i < 21; i++)
	{

		for (int j = 0; j < 21; j++)
		{
			if (i == 0)
			{
				if (map2[i][j] == 0) continue;
				setfillcolor(RGB(0, 54, 107));
				fillrectangle(500, i * 25, 500 + 25, i * 25 + 25);
			}
			if (i == 1)
			{
				if (map2[i][j] == 0) continue;
				if (j == 8 || j == 10 || j == 12)//这个是指第i行的第j列的格子需要填色
				{
					setfillcolor(RGB(0, 100, 159));//这个格子要填的颜色
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 2)
			{
				if (map2[i][j] == 0) continue;
				if (j == 9 || j == 10 || j == 11)
				{
					setfillcolor(RGB(71, 198, 192));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 3)
			{
				if (map2[i][j] == 0) continue;
				if (j == 3 || j == 5 || j == 7 || j == 10 || j == 13 || j == 15 || j == 17)
				{
					setfillcolor(RGB(62, 81, 110));
					fillrectangle(250 + j * 25, i * 25, 250 + j * 25 + 25, i * 25 + 25);
				}
			}
			if (i == 4)
			{
				if (map2[i][j] == 0) continue;
				if (j == 4 || j == 5 || j == 8 || j == 10 || j == 12 || j == 15 || j == 16)
				{
					setfillcolor(RGB(0, 84, 105));
					fillrectangle(250 + j * 25, i * 25, 250 + j * 25 + 25, i * 25 + 25);
				}
			}
			if (i == 5)
			{
				if (map2[i][j] == 0) continue;
				if (j == 3 || j == 4 || j == 5 || j == 9 || j == 10 || j == 11 || j == 15 || j == 16 || j == 17)
				{
					setfillcolor(RGB(0, 180, 214));
					fillrectangle(250 + j * 25, i * 25, 250 + j * 25 + 25, i * 25 + 25);
				}
			}
			if (i == 6)
			{
				if (map2[i][j] == 0) continue;
				if (j == 6 || j == 10 || j == 14)
				{
					setfillcolor(RGB(0, 57, 88));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 7)
			{
				if (map2[i][j] == 0) continue;
				if (j == 3 || j == 7 || j == 9 || j == 10 || j == 11 || j == 13 || j == 17)
				{
					setfillcolor(RGB(0, 167, 177));
					fillrectangle(250 + j * 25, i * 25, 250 + j * 25 + 25, i * 25 + 25);
				}
			}
			if (i == 8)
			{
				if (map2[i][j] == 0) continue;
				if (j == 1 || j == 4 || j == 8 || j == 10 || j == 12 || j == 16 || j == 19)
				{
					setfillcolor(RGB(0, 49, 84));
					fillrectangle(250 + j * 25, i * 25, 250 + j * 25 + 25, i * 25 + 25);
				}
			}
			if (i == 9)
			{
				if (map2[i][j] == 0) continue;
				if (j == 2 || j == 5 || j == 7 || j == 9 || j == 10 || j == 11 || j == 13 || j == 15 || j == 18)
				{
					setfillcolor(RGB(95, 151, 158));
					fillrectangle(250 + j * 25, i * 25, 250 + j * 25 + 25, i * 25 + 25);
				}
			}
			if (i == 10) {
				if (map2[i][j] == 0) continue;
				if (j == 10) continue;
				setfillcolor(RGB(0, 54, 107));
				fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
			}
			if (i == 11)
			{
				if (map2[i][j] == 0) continue;
				if (j == 2 || j == 5 || j == 7 || j == 9 || j == 10 || j == 11 || j == 13 || j == 15 || j == 18)
				{
					setfillcolor(RGB(95, 151, 158));
					fillrectangle(250 + j * 25, i * 25, 250 + j * 25 + 25, i * 25 + 25);
				}
			}
			if (i == 12)
			{
				if (map2[i][j] == 0) continue;
				if (j == 1 || j == 4 || j == 8 || j == 10 || j == 12 || j == 16 || j == 19)
				{
					setfillcolor(RGB(0, 49, 84));
					fillrectangle(250 + j * 25, i * 25, 250 + j * 25 + 25, i * 25 + 25);
				}
			}
			if (i == 13)
			{
				if (map2[i][j] == 0) continue;
				if (j == 3 || j == 7 || j == 9 || j == 10 || j == 11 || j == 13 || j == 17)
				{
					setfillcolor(RGB(0, 167, 177));
					fillrectangle(250 + j * 25, i * 25, 250 + j * 25 + 25, i * 25 + 25);
				}
			}
			if (i == 14)
			{
				if (map2[i][j] == 0) continue;
				if (j == 6 || j == 10 || j == 14)
				{
					setfillcolor(RGB(0, 57, 88));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 15)
			{
				if (map2[i][j] == 0) continue;
				if (j == 3 || j == 4 || j == 5 || j == 9 || j == 10 || j == 11 || j == 15 || j == 16 || j == 17)
				{
					setfillcolor(RGB(0, 180, 214));
					fillrectangle(250 + j * 25, i * 25, 250 + j * 25 + 25, i * 25 + 25);
				}
			}
			if (i == 16)
			{
				if (map2[i][j] == 0) continue;
				if (j == 4 || j == 5 || j == 8 || j == 10 || j == 12 || j == 15 || j == 16)
				{
					setfillcolor(RGB(0, 84, 105));
					fillrectangle(250 + j * 25, i * 25, 250 + j * 25 + 25, i * 25 + 25);
				}
			}
			if (i == 17)
			{
				if (map2[i][j] == 0) continue;
				if (j == 3 || j == 5 || j == 7 || j == 10 || j == 13 || j == 15 || j == 17)
				{
					setfillcolor(RGB(62, 81, 110));
					fillrectangle(250 + j * 25, i * 25, 250 + j * 25 + 25, i * 25 + 25);
				}
			}
			if (i == 18)
			{
				if (map2[i][j] == 0) continue;
				if (j == 9 || j == 10 || j == 11)
				{
					setfillcolor(RGB(71, 198, 192));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 19)
			{
				if (map2[i][j] == 0) continue;
				if (j == 8 || j == 10 || j == 12)
				{
					setfillcolor(RGB(0, 100, 159));
					fillrectangle(j * 25 + 250, i * 25, j * 25 + 250 + 25, i * 25 + 25);
				}
			}
			if (i == 20)
			{
				if (map2[i][j] == 0) continue;
				if (j == 10) {
					setfillcolor(RGB(0, 54, 107));
					fillrectangle(500, i * 25, 500 + 25, i * 25 + 25);
				}
			}

		}

	}


}
//根据所需要的砖块位置坐标,给相应的数组赋值,没有砖块的地方不赋值(已经初始化为0)
void fuzhi1()//春
{

		//i是行,j是列
		for (int i = 1; i < 21; i++)
		{
			for (int j = 1; j < 21; j++)
			{
				map2[i][j] = rand() % 7 + 1;
			}

		}
	
}
void fuzhi2()//夏
{
	//i是行,j是列
	for (int i = 1; i < 21; i++)
	{
		for (int j = 1; j < 21; j++)
		{
			map2[i][j] = rand() % 7 + 1;
		}

	}
}
void fuzhi3()//秋
{
	//i是行,j是列
	for (int i = 1; i < 19; i++)
	{
		for (int j = 1; j < 19; j++)
		{
			map2[i][j] = rand() % 7 + 1;
		}

	}
}
void fuzhi4()//冬
{
	//i是行,j是列
	for (int i = 0; i < 21; i++)
	{

		for (int j = 0; j < 21; j++)
		{
			if (i == 0)
			{
				map2[i][j] = rand() % 7 + 1;
			}
			if (i == 1)
			{
				if (j == 8 || j == 10 || j == 12)
				{
					map2[i][j] = rand() % 7 + 1;
				}
			}
			if (i == 2)
			{
				if (j == 9 || j == 10 || j == 11)
				{
					map2[i][j] = rand() % 7 + 1;
				}
			}
			if (i == 3)
			{
				if (j == 3 || j == 5 || j == 7 || j == 10 || j == 13 || j == 15 || j == 17)
				{
					map2[i][j] = rand() % 7 + 1;
				}
			}
			if (i == 4)
			{
				if (j == 4 || j == 5 || j == 8 || j == 10 || j == 12 || j == 15 || j == 16)
				{
					map2[i][j] = rand() % 7 + 1;
				}
			}
			if (i == 5)
			{
				if (j == 3 || j == 4 || j == 5 || j == 9 || j == 10 || j == 11 || j == 15 || j == 16 || j == 17)
				{
					map2[i][j] = rand() % 7 + 1;
				}
			}
			if (i == 6)
			{
				if (j == 6 || j == 10 || j == 14)
				{
					map2[i][j] = rand() % 7 + 1;
				}
			}
			if (i == 7)
			{
				if (j == 3 || j == 7 || j == 9 || j == 10 || j == 11 || j == 13 || j == 17)
				{
					map2[i][j] = rand() % 7 + 1;
				}
			}
			if (i == 8)
			{
				if (j == 1 || j == 4 || j == 8 || j == 10 || j == 12 || j == 16 || j == 19)
				{
					map2[i][j] = rand() % 7 + 1;
				}
			}
			if (i == 9)
			{
				if (j == 2 || j == 5 || j == 7 || j == 9 || j == 10 || j == 11 || j == 13 || j == 15 || j == 18)
				{
					map2[i][j] = rand() % 7 + 1;
				}
			}
			if (i == 10) {
				if (j == 10) continue;
				else
					map2[i][j] = rand() % 7 + 1;
			}
			if (i == 11)
			{
				if (j == 2 || j == 5 || j == 7 || j == 9 || j == 10 || j == 11 || j == 13 || j == 15 || j == 18)
				{
					map2[i][j] = rand() % 7 + 1;
				}
			}
			if (i == 12)
			{
				if (j == 1 || j == 4 || j == 8 || j == 10 || j == 12 || j == 16 || j == 19)
				{
					map2[i][j] = rand() % 7 + 1;
				}
			}
			if (i == 13)
			{
				if (j == 3 || j == 7 || j == 9 || j == 10 || j == 11 || j == 13 || j == 17)
				{
					map2[i][j] = rand() % 7 + 1;
				}
			}
			if (i == 14)
			{
				if (j == 6 || j == 10 || j == 14)
				{
					map2[i][j] = rand() % 7 + 1;
				}
			}
			if (i == 15)
			{
				if (j == 3 || j == 4 || j == 5 || j == 9 || j == 10 || j == 11 || j == 15 || j == 16 || j == 17)
				{
					map2[i][j] = rand() % 7 + 1;
				}
			}
			if (i == 16)
			{
				if (j == 4 || j == 5 || j == 8 || j == 10 || j == 12 || j == 15 || j == 16)
				{
					map2[i][j] = rand() % 7 + 1;
				}
			}
			if (i == 17)
			{
				if (j == 3 || j == 5 || j == 7 || j == 10 || j == 13 || j == 15 || j == 17)
				{
					map2[i][j] = rand() % 7 + 1;
				}
			}
			if (i == 20)
			{
				if (j == 10)
					map2[i][j] = rand() % 7 + 1;
			}
			if (i == 19)
			{
				if (j == 8 || j == 10 || j == 12)
				{
					map2[i][j] = rand() % 7 + 1;
				}
			}
			if (i == 18)
			{
				if (j == 9 || j == 10 || j == 11)
				{
					map2[i][j] = rand() % 7 + 1;
				}
			}
		}

	}
}
//木板的结构体
struct Board
{
	int x;
	int y;
	int speed;
	COLORREF color;
	int width;
	int height;
};
//通过这个函数给结构体赋值
struct Board* createBoard(int x, int y, int  speed, COLORREF color, int width, int height)
{
	struct Board* pBoard = (struct Board*)malloc(sizeof(struct Board));
	if (pBoard == NULL) return 0;
	pBoard->x = x;
	pBoard->y = y;
	pBoard->speed = speed;
	pBoard->color = color;
	(*pBoard).width = width;
	(*pBoard).height = height;
	return pBoard;
}
//人物选择窗口
void Character_selection_window()
{
	initgraph(800, 500);
	HWND hwnd1 = GetHWnd();
	SetWindowPos(hwnd1, NULL, 300, 150, 0, 0, SWP_NOSIZE);
	char inputValue[100];
	settextstyle(20, 0, _T("黑体"));

	loadimage(&rw_window, "D:\\c语言\\打砖块游戏\\tutu\\菜单界面三选一\\人物选择.jpg", 800, 500);
	putimage(0, 0, &rw_window);

	setcolor(RGB(255, 204, 153));
	setbkmode(TRANSPARENT);//消除字体黑框
	outtextxy(50, 110, "博丽灵梦(1)");
	loadimage(&rw1, "./tutu/44.png", 100, 100);
	transparentimage(30, 150, rw1);



	outtextxy(350, 50, "雾雨魔理沙(2)");
	loadimage(&rw2, "./tutu/55.png", 100, 100);
	transparentimage(350, 70, rw2);



	outtextxy(680, 110, "伊吹萃香(3)");
	loadimage(&rw3, "./tutu/666.png", 100, 100);
	transparentimage(690, 150, rw3);

	InputBox(inputValue, 100, "请选择您的游戏人物(输入对应数字):", 0, 0, 200, 30);
	sscanf_s(inputValue, "%d", &Character_selection);
}
//绘制板
void drawBoard(struct Board* pBoard)
{

	if (Character_selection == 1)
		transparentimage(pBoard->x, pBoard->y, rw1);//删除透明图片黑框
	if (Character_selection == 2)
		transparentimage(pBoard->x, pBoard->y, rw2);//删除透明图片黑框
	if (Character_selection == 3)
		transparentimage(pBoard->x, pBoard->y, rw3);//删除透明图片黑框
	//putimage(pBoard->x, pBoard->y, &board1);
}
//木板的按键操作
void keyDown(struct Board* pBoard)
{

	//异步的按键操作
	if (GetAsyncKeyState('A') || GetAsyncKeyState(VK_LEFT) && pBoard->x >= 0)
	{
		pBoard->x -= pBoard->speed;
	}
	if (GetAsyncKeyState('D') || GetAsyncKeyState(VK_RIGHT) && pBoard->x <= 1200 - 200)
	{
		pBoard->x += pBoard->speed;
	}
}

//球的结构体
struct Ball
{
	int x;
	int y;
	int r;				//半径
	int dx;
	int dy;
	COLORREF color;
};
//通过这个函数给球的结构体成员赋值
struct Ball* createBall(int x, int y, int r, int dx, int dy, COLORREF color)
{
	struct Ball* pBall = (struct Ball*)malloc(sizeof(struct Ball));
	if (pBall == NULL) return 0;
	pBall->x = x;
	pBall->y = y;
	pBall->r = r;
	pBall->dx = dx;
	pBall->dy = dy;
	pBall->color = color;
	return pBall;
}

//球的绘制
void drawBall(struct Ball* pBall)
{
	if(Character_selection==1)
	transparentimage(pBall->x, pBall->y, qiou1);
	if (Character_selection == 2)
	transparentimage(pBall->x, pBall->y, qiou2);
	if (Character_selection == 3)
	transparentimage(pBall->x, pBall->y, qiou3);
}

//1.反射
//2.撞击木板
int hitBoard(struct Ball* pBall, struct Board* pBoard)
{
	if (pBall->y + pBall->r >= pBoard->y && pBall->y + pBall->r <= pBoard->y + pBoard->height) //y满足
	{
		if (pBall->x >= pBoard->x && pBall->x <= pBoard->x + pBoard->width)
		{
			return 1;
		}
	}
	return 0;
}
//死亡判定
int die(struct Ball* pBall)
{
	if (pBall->y > 1000 - 25)
	{
		return 1;
	}
	return 0;
}

//3.撞击砖块
int hitBricks(struct Ball* pBall)
{
	//1.算出球的行和列
	int ballJ = (pBall->x - 250 + 15) / 25;
	int ballI = (pBall->y + 15) / 25;
	//2.当前下标下，数组中不等于0表示有砖块需要反射和消除
	if (ballJ < 21 && ballJ >= 0 && ballI >= 0 && ballI < 21 && map2[ballI][ballJ] != 0)
	{
		map2[ballI][ballJ] = 0;
		score = score + 10;
		return 1;
	}
	return 0;
}
// 判断球是否与矩形（木板或砖块）的顶部碰撞
int hitTop(struct Ball* pBall, int objX, int objY, int objWidth, int objHeight) {
	return (pBall->y - pBall->r <= objY + objHeight &&
		pBall->y - pBall->r >= objY &&
		pBall->x >= objX && pBall->x <= objX + objWidth);
}

// 判断球是否与矩形（木板或砖块）的底部碰撞
int hitBottom(struct Ball* pBall, int objX, int objY, int objWidth, int objHeight) {
	return (pBall->y + pBall->r >= objY &&
		pBall->y + pBall->r <= objY + objHeight &&
		pBall->x >= objX && pBall->x <= objX + objWidth);
}

// 判断球是否与矩形（木板或砖块）的左侧碰撞
int hitLeft(struct Ball* pBall, int objX, int objY, int objWidth, int objHeight) {
	return (pBall->x - pBall->r <= objX + objWidth &&
		pBall->x - pBall->r >= objX &&
		pBall->y >= objY && pBall->y <= objY + objHeight);
}

// 判断球是否与矩形（木板或砖块）的右侧碰撞
int hitRight(struct Ball* pBall, int objX, int objY, int objWidth, int objHeight) {
	return (pBall->x + pBall->r >= objX &&
		pBall->x + pBall->r <= objX + objWidth &&
		pBall->y >= objY && pBall->y <= objY + objHeight);
}

// 球的反射和移动的实现（改进版，无能量损耗）
void moveBall(struct Ball* pBall, struct Board* pBoard) {
	// 先处理边界碰撞（左右边界）
	if (pBall->x - pBall->r <= 0) {
		pBall->dx = -pBall->dx;
	}
	if (pBall->x + pBall->r >= 1000) {
		pBall->dx = -pBall->dx;
	}
	// 处理顶部边界碰撞
	if (pBall->y - pBall->r <= 0) {
		pBall->dy = -pBall->dy;
	}
	// 处理与木板的碰撞
	if (hitBoard(pBall, pBoard)) {
		
		pBall->dy = -pBall->dy;
	}
	// 处理与砖块的碰撞
	if (hitBricks(pBall)) {
		int ballJ = (pBall->x - 250 + 15) / 25;
		int ballI = (pBall->y + 15) / 25;
		int brickX = ballJ * 25 + 250;
		int brickY = ballI * 25;
		int brickWidth = 25;
		int brickHeight = 25;
		// 判断具体碰撞的边，然后相应地调整球的反弹方向
		if (hitTop(pBall, brickX, brickY, brickWidth, brickHeight)) {
			pBall->dy = -pBall->dy;
		}
		else if (hitBottom(pBall, brickX, brickY, brickWidth, brickHeight)) {
			pBall->dy = -pBall->dy;
		}
		else if (hitLeft(pBall, brickX, brickY, brickWidth, brickHeight)) {
			pBall->dx = -pBall->dx;
		}
		else if (hitRight(pBall, brickX, brickY, brickWidth, brickHeight)) {
			pBall->dx = -pBall->dx;
		}
	}
	pBall->x += pBall->dx;
	pBall->y += pBall->dy;
}
//5.定时器
int Timer(time_t num, int id)
{
	static time_t start[10];
	time_t end = clock();
	if (end - start[id] > num)
	{
		start[id] = end;
		return 1;
	}
	return 0;
}
//游戏胜利判定
int gameOver()
{
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (map2[i][j] != 0)
			{
				return 0;
			}
		}
	}
	return 1;
}
//得分输出函数
void printScore()
{
	char scoreStr[20];
	sprintf_s(scoreStr, "%d", score);
	outtextxy(100, 150, scoreStr);
	settextstyle(30, 0, _T("微软雅黑"));
	setbkmode(TRANSPARENT);
	outtextxy(10, 150, _T("得分:"));
}

int main()
{
	srand((unsigned int)time(0));

	VariableSpeed1();

	Stage_selection_window();

	init_rw();
	Character_selection_window();
	init_qiou();

	init_dt();
	//固定窗口位置
	hwnd3 = initgraph(1000, 800);
	HWND hwnd_window = GetHWnd();
	SetWindowPos(hwnd_window, NULL, 200, 0, 0, 0, SWP_NOSIZE);


	struct Board* pBoard = createBoard(500, 700 - 25, 5, WHITE, 250, 10);
	struct Ball* pBall = createBall(400, 600, 15, speed * 2 + 4, -(speed * 2 + 4), RGB(rand() % 255, rand() % 255, rand() % 255));
	if (Stage_selection == 1)fuzhi1();
	else if (Stage_selection == 2)fuzhi2();
	else if (Stage_selection == 3)fuzhi3();
	else if (Stage_selection == 4)fuzhi4();
	BeginBatchDraw();
	while (1)
	{
		//cleardevice();
		if (Stage_selection == 1)drawMap1();
		else if (Stage_selection == 2)drawMap2();
		else if (Stage_selection == 3)drawMap3();
		else if (Stage_selection == 4)drawMap4();
		drawBoard(pBoard);
		drawBall(pBall);
		pBall->color = RGB(rand() % 255, rand() % 255, rand() % 255);
		
		printScore();
		FlushBatchDraw();
		if (Timer(10, 0))
			moveBall(pBall, pBoard);
		keyDown(pBoard);
		if (die(pBall))
		{
			MessageBox(hwnd3, "菜", "游戏失败", MB_OK);
			exit(0);
		}
		if (gameOver())
		{
			MessageBox(hwnd3, "不小心让你赢了,真遗憾", "游戏获胜", MB_OK);
			exit(0);
		}

		FlushBatchDraw();

	}
	EndBatchDraw();
	closegraph();

	return 0;
}
#endif