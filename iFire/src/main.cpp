#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <Mmsystem.h>
#pragma comment(lib, "Winmm.lib") // ���� Winmm.lib ��
#define MAXBULLET 5
#define MAXFIRE 7
#define NUM 100
//���
struct FIRE
{
	int r;            // ��ǰ�뾶
	int x, y;         // ���ŵ�����
	int cen_x, cen_y; // ��������
	int max_r;        // ���뾶
	int height, width;// ͼƬ�߶ȺͿ��
	int xy[240][240]; // ��������

	bool show;        // ���ſ���
	bool draw;        // ���ƿ���
	DWORD t1, t2, dt; // ����ʱ��
	IMAGE img;

} fire[MAXFIRE];

struct BULLET
{
	int x, y;  // �����
	int hx, hy;// ��ߵ�����
	int height;// ���侭���߶�

	bool isshoot; // ���俪��
	DWORD t1, t2, dt; // ����ʱ��
	IMAGE img;
	byte n : 1; // ���Ʒ���ʱ��һ��һ��

} bullet[MAXBULLET];

DWORD* pMem;// = GetImageBuffer(); // ��ȡ���ػ�����
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
	loadimage(&bullet[i].img, name, 20, 50);//�ò���һ���Ƿ����
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
	initgraph(1200, 800); // ��ʼ������
	settextcolor(YELLOW);
	settextstyle(25, 0, "����");
	outtextxy(400, 200, "�����̻�");

	mciSendString("open ./һ�ξͺ�.mp3", 0, 0, 0);
	mciSendString("play ./һ�ξͺ�.mp3 repeat", 0, 0, 0);
	pMem = GetImageBuffer();//ֻ�ܷ��������ʼ������ͷ��ʼ��������
}
void InitFire(int a, int b) // ��ʼ�������̻�
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
		//return;д��λ�ÿ�ϴ����
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
			if (fire[i].r < fire[i].max_r) // �жϰ뾶�Ƿ񳬹����뾶
			{
				fire[i].r++;
				fire[i].dt = drt[fire[i].r / 10];
				fire[i].draw = true;//ÿ�ν������ȵ�������true���ܽ��������
			}
			else // ���������ֹͣ��Բ
			{
				fire[i].draw = false;
				//ReversFire(i);
				fire[i].show = false;
				break;
			}
			fire[i].t1 = fire[i].t2;
		}
		//���� ��������
		//fire[i].draw == false ��ʾ���ڻ����� ���ܽ��л���
		if (fire[i].draw == true)// ����Ϊʲô��
		{
			for (double a = 0; a <= 6.28; a += 0.01) // һȦһȦ�����
			{
				int x1 = (int)(fire[i].cen_x + fire[i].r * cos(a)); // x1 y1 �����̻�ͼƬ�е����λ��
				int y1 = (int)(fire[i].cen_y + fire[i].r * sin(a)); //
				if (x1 >= 0 && x1 < fire[i].width && y1 >= 0 && y1 < fire[i].height)
				{
					int b = fire[i].xy[x1][y1] & 0xff;  //�õ���ԭɫ������ֽ�(B)
					int g = (fire[i].xy[x1][y1] >> 8) & 0xff; //��2���ֽ�
					int r = (fire[i].xy[x1][y1] >> 16);


					int xx = (int)(fire[i].x + fire[i].r * cos(a)); // xx yy ������Ļ�ϵľ���λ��
					int yy = (int)(fire[i].y + fire[i].r * sin(a)); //
					if (r > 0x20 && g > 0x20 && b > 0x20 && xx > 0 && xx < 1200 && yy > 0 && yy < 800) // ȷ�� xx �� yy ����Ļ��Χ��
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
		bullet[i].t2 = GetTickCount(); // ��ȡϵͳʱ��
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

				InitFire(bullet[i].x, bullet[i].y); // ��ʼ���̻�
				//fire[i].show = true;
			}
			bullet[i].t1 = bullet[i].t2;

		}
		//bullet[i].t1 = bullet[i].t2;
		//ֱ���������������̻�����
		//if (fire[i].show==true)
		//{
		//	cleardevice(); // ����
		//	dram(); // �����̻�
		//}
	}
}
void Rebullter(DWORD t1)
{
	DWORD t2 = timeGetTime();
	if (t2 - t1 > 500)//100ms֮��������
	{
		int i = rand() % 100; //ȡ��������Խ���̻�����Ƶ��Խ������Ϊ<13�ĸ��ʾ�Խ��
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
			pMem[py1 * 1200 + px1 + 1] = BLACK;	// ���Դ渳ֵ�������ص�		
		}
	}
}
int main()
{
	srand((unsigned int)time(NULL));
	StartInit();
	LoadBulletAndFire_StartInit();//��ʼ����������������

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
		Rebullter(t1);//��� ����Ҫ�ڲ���ʼ�� �������ʼ�����������ʱ��
		FlushBatchDraw();

		Sleep(10);//ϵ�����˻���ɿ���
	}
	closegraph();
	return 0;
}
