#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <Mmsystem.h>
#pragma comment(lib, "Winmm.lib") // 加载 Winmm.lib 库
#define MAXBULLET 5
#define MAXFIRE 7
#define NUM 100
//多个
struct FIRE
{
	int r;            // 当前半径
	int x, y;         // 绽放的坐标
	int cen_x, cen_y; // 绽放中心
	int max_r;        // 最大半径
	int height, width;// 图片高度和宽度
	int xy[240][240]; // 像素数据

	bool show;        // 绽放开关
	bool draw;        // 绘制开关
	DWORD t1, t2, dt; // 控制时间
	IMAGE img;

} fire[MAXFIRE];

struct BULLET
{
	int x, y;  // 发射点
	int hx, hy;// 最高点坐标
	int height;// 发射经历高度

	bool isshoot; // 发射开关
	DWORD t1, t2, dt; // 控制时间
	IMAGE img;
	byte n : 1; // 控制发射时的一明一暗

} bullet[MAXBULLET];

DWORD* pMem;// = GetImageBuffer(); // 获取像素缓冲区
void InitBullter(int i);
void InitFire(int i);


void LoadBulletAndFire_StartInit()
{
	for (int i = 0; i < 5; i++)
	{
		InitBullter(i);
	}
	for (int i = 0; i < 7; i++)
	{
		InitFire(i);
	}
}
int abs(int a, int b)
{
	if ((a - b) >= 240 || (a - b) <= -240) {
		return 1;
	}
	else
	{
		return 0;
	}

}
int prevalue = 0, current = 0;
void InitBullter(int i)
{
	while (1)
	{
		current = rand() % (1200 - 20);
		if (abs(current, prevalue) == true)
		{
			printf("%d\n", current);
			break;
		}
	}
	prevalue = current;
	bullet[i].x = current;
	bullet[i].y = 1000 - 50;
	bullet[i].hx = bullet[i].x;
	bullet[i].hy = rand() % 450;
	bullet[i].dt = 30;
	bullet[i].isshoot = true;
	char name[40];
	sprintf(name, "%s%d%s", "./img/bullters/shoot", i + 1, ".png");
	loadimage(&bullet[i].img, name, 20, 50);//得测试一下是否可行
	//putimage(bullet[i].x+100, bullet[i].y-500, &bullet[i].img, SRCINVERT);
}
void InitFire(int i)
{
	fire[i].x = 0;
	fire[i].y = 0;
	fire[i].r = 0;
	fire[i].cen_x = 120;
	fire[i].cen_y = 120;
	fire[i].max_r = 120;
	fire[i].height = 240;
	fire[i].width = 240;
	fire[i].show = false;
	fire[i].t1 = timeGetTime();
	fire[i].draw = true;
	fire[i].dt = 5;
	char name[40];
	sprintf(name, "%s%d%s", "./img/flowers/flower", i + 1, ".png");
	printf("%s  \n", name);
	loadimage(&fire[i].img, name, 240, 240);
	//putimage(fire[i].x=400, fire[i].y+500, &fire[i].img, SRCINVERT);

	SetWorkingImage(&fire[i].img);
	for (int a = 0; a < 240; a++)
	{
		for (int b = 0; b < 240; b++)
		{
			fire[i].xy[a][b] = getpixel(a, b);
		}
	}
	SetWorkingImage();

}
void ReversFire(int i)
{
	fire[i].x = 0;
	fire[i].y = 0;
	fire[i].r = 0;
	fire[i].cen_x = 120;
	fire[i].cen_y = 120;
	fire[i].max_r = 120;
	fire[i].height = 240;
	fire[i].width = 240;
	fire[i].show = false;
	fire[i].t1 = timeGetTime();
	fire[i].draw = false;
	fire[i].dt = 5;

	//loadimage(&fire[i].img, "./img/flower.png", 240, 240);

	/*SetWorkingImage(&fire[i].img);
	for (int a = 0; a < 240; a++)
	{
		for (int b = 0; b < 240; b++)
		{
			fire[i].xy[a][b] = getpixel(a, b);
		}
	}
	SetWorkingImage();*/
}
void StartInit()
{
	initgraph(1200, 800); // 初始化窗口
	settextcolor(YELLOW);
	settextstyle(25, 0, "楷体");
	outtextxy(400, 200, "浪漫烟花");

	mciSendString("open ./一次就好.mp3", 0, 0, 0);
	mciSendString("play ./一次就好.mp3 repeat", 0, 0, 0);
	pMem = GetImageBuffer();//只能放在这里初始化，开头初始化都不行
}
void InitFire(int a, int b) // 初始化单个烟花
{
	for (int i = 0; i < MAXBULLET; i++)
	{
		//printf("daadasdsa ");
		if (fire[i].show == false)//
		{
			printf("%d\n", i);
			fire[i].x = a;
			fire[i].y = b;
			fire[i].r = 0;
			fire[i].cen_x = 120;
			fire[i].cen_y = 120;
			fire[i].max_r = 120;
			fire[i].height = 240;
			fire[i].width = 240;
			fire[i].show = true;
			fire[i].t1 = timeGetTime();
			fire[i].draw = true;
			fire[i].dt = 5;

			return;
		}
		//return;写错位置坑洗我了
	}
}

void ReversBullter(int i)
{
	bullet[i].x = rand() % (1200 - 20);
	bullet[i].y = 800 - 50;
	bullet[i].hx = bullet[i].x;
	bullet[i].hy = rand() % 450;
	bullet[i].dt = 20;
	bullet[i].isshoot = true;
	putimage(bullet[i].x, bullet[i].y, &bullet[i].img, SRCINVERT);
}
void dram()
{
	int drt[16] = { 5, 5, 5, 5, 5, 5, 5, 5, 5, 25, 55, 55, 55, 55, 55 };
	for (int i = 0; i < MAXBULLET; i++)
	{

		fire[i].t2 = timeGetTime();
		if (fire[i].t2 - fire[i].t1 > fire[i].dt && fire[i].show == true)
		{
			if (fire[i].r < fire[i].max_r) // 判断半径是否超过最大半径
			{
				fire[i].r++;
				fire[i].dt = drt[fire[i].r / 10];
				fire[i].draw = true;//每次进来都先到这里获得true才能进入绘制中
			}
			else // 如果超过，停止画圆
			{
				fire[i].draw = false;
				//ReversFire(i);
				fire[i].show = false;
				break;
			}
			fire[i].t1 = fire[i].t2;
		}
		//绘制 利用像素
		//fire[i].draw == false 表示正在绘制中 才能进行绘制
		if (fire[i].draw == true)// 想想为什么？
		{
			for (double a = 0; a <= 6.28; a += 0.01) // 一圈一圈地输出
			{
				int x1 = (int)(fire[i].cen_x + fire[i].r * cos(a)); // x1 y1 是在烟花图片中的相对位置
				int y1 = (int)(fire[i].cen_y + fire[i].r * sin(a)); //
				if (x1 >= 0 && x1 < fire[i].width && y1 >= 0 && y1 < fire[i].height)
				{
					int b = fire[i].xy[x1][y1] & 0xff;  //得到三原色的最低字节(B)
					int g = (fire[i].xy[x1][y1] >> 8) & 0xff; //第2个字节
					int r = (fire[i].xy[x1][y1] >> 16);


					int xx = (int)(fire[i].x + fire[i].r * cos(a)); // xx yy 是在屏幕上的绝对位置
					int yy = (int)(fire[i].y + fire[i].r * sin(a)); //
					if (r > 0x20 && g > 0x20 && b > 0x20 && xx > 0 && xx < 1200 && yy > 0 && yy < 800) // 确保 xx 和 yy 在屏幕范围内
					{
						pMem[yy * 1200 + xx] = BGR(fire[i].xy[x1][y1]);
					}
				}

			}
			fire[i].draw = false;
		}
	}
}

void ShootBullter()
{
	for (int i = 0; i < 5; i++)
	{
		//Sleep(20);
		bullet[i].t2 = GetTickCount(); // 获取系统时间
		if (bullet[i].t2 - bullet[i].t1 > bullet[i].dt && bullet[i].isshoot == true)
		{
			putimage(bullet[i].x, bullet[i].y, &bullet[i].img, SRCINVERT);
			if (bullet[i].y > bullet[i].hy)
			{
				bullet[i].y -= 10;
			}
			putimage(bullet[i].x, bullet[i].y, &bullet[i].img, SRCINVERT);
			if (bullet[i].y <= bullet[i].hy)
			{
				putimage(bullet[i].x, bullet[i].y, &bullet[i].img, SRCINVERT);
				bullet[i].isshoot = false;
				bullet[i].t1 = bullet[i].t2;

				InitFire(bullet[i].x, bullet[i].y); // 初始化烟花
				//fire[i].show = true;
			}
			bullet[i].t1 = bullet[i].t2;

		}
		//bullet[i].t1 = bullet[i].t2;
		//直接在主函数绘制烟花就行
		//if (fire[i].show==true)
		//{
		//	cleardevice(); // 清屏
		//	dram(); // 绘制烟花
		//}
	}
}
void Rebullter(DWORD t1)
{
	DWORD t2 = timeGetTime();
	if (t2 - t1 > 500)//100ms之后在重置
	{
		int i = rand() % 100; //取摸的数字越大，烟花发射频率越慢，因为<13的概率就越低
		if (i < 5 && bullet[i].isshoot == false)
		{
			bullet[i].x = rand() % (1200 - 20);
			bullet[i].y = 800 - 50;
			bullet[i].hx = bullet[i].x;
			bullet[i].hy = rand() % 450;
			bullet[i].dt = 20;
			bullet[i].isshoot = true;
			putimage(bullet[i].x, bullet[i].y, &bullet[i].img, SRCINVERT);
		}
	}
}
void clearImage()
{
	int i = 4;
	while (i--)
	{
		for (int i = 0; i < 2000; i++)
		{
			int px1 = rand() % 1200; // 0..1199
			int py1 = rand() % 800;  // 0.799

			pMem[py1 * 1200 + px1] = BLACK;
			pMem[py1 * 1200 + px1 + 1] = BLACK;	// 对显存赋值擦出像素点		
		}
	}
}
int main()
{
	srand((unsigned int)time(NULL));
	StartInit();
	LoadBulletAndFire_StartInit();//初始化并加载所有数据

	/*for (int i = 0; i < 7; i++)
	{
		int x = rand() % 1000;
		int y = rand() % 1200;
		putimage(x, y, &fire[i].img, SRCINVERT);
	}*/

	DWORD t1 = timeGetTime();
	BeginBatchDraw();//
	while (1)
	{
		clearImage();
		ShootBullter();
		dram();
		Rebullter(t1);//点火 不需要内部初始化 在这里初始化，方便控制时间
		FlushBatchDraw();

		Sleep(10);//系数高了会造成卡顿
	}
	closegraph();
	return 0;
}
