//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <graphics.h>
//#include <conio.h>
//#include <iostream>
//#include <windows.h>
//#include <math.h>
//#include <time.h>
//#include <Mmsystem.h>
//
//struct MyStruct // 记录图片位置，交换用
//{
//    int xx;
//    int yy;
//} hs[4][4];
//
//int map[4][4] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
//
//IMAGE img;
//int flog = 0;
//
//int currentx, currenty, nextcurrentx, nextcurrenty;
//
//void InitGraph()
//{
//    initgraph(800, 800); // 初始化窗口
//    loadimage(&img, "./test.jpg", 800, 800); // 加载图片
//}
//
//void dram()
//{
//    int x, y;
//    int xx, yy;
//    for (int i = 0; i < 4; i++)
//    {
//        for (int j = 0; j < 4; j++)
//        {
//            x = j * 200;
//            y = i * 200;
//            xx = (map[i][j] % 4) * 200;
//            yy = (map[i][j] / 4) * 200;
//            putimage(x, y, 200, 200, &img, xx, yy);
//            hs[i][j].xx = xx;
//            hs[i][j].yy = yy;
//        }
//    }
//}
//
//void drawexchangeimg()
//{
//    if (flog == 0) return;
//
//    int currRow = currenty / 200;
//    int currCol = currentx / 200;
//    int nextRow = nextcurrenty / 200;
//    int nextCol = nextcurrentx / 200;
//
//    if (currRow == nextRow && currCol == nextCol) {
//        flog = 0;
//        return;
//    }
//
//    // 交换 map 数组中的值
//    int temp = map[currRow][currCol];
//    map[currRow][currCol] = map[nextRow][nextCol];
//    map[nextRow][nextCol] = temp;
//
//    // 重新绘制交换后的图像块
//    //没有这部分会出现很多问题，暂时不知道怎么处理
//    int currImageX = (map[currRow][currCol] % 4) * 200;
//    int currImageY = (map[currRow][currCol] / 4) * 200;
//    int nextImageX = (map[nextRow][nextCol] % 4) * 200;
//    int nextImageY = (map[nextRow][nextCol] / 4) * 200;
//
//    putimage(currCol * 200, currRow * 200, 200, 200, &img, currImageX, currImageY);
//    putimage(nextCol * 200, nextRow * 200, 200, 200, &img, nextImageX, nextImageY);
//
//    flog = 0;
//}
//
//void usercheck()
//{
//    ExMessage msg;
//    if (peekmessage(&msg, EM_MOUSE))
//    {
//        if (msg.message == WM_LBUTTONDOWN) // 按下鼠标左键
//        {
//            flog = 1;
//            currentx = msg.x;
//            currenty = msg.y;
//        }
//        if (msg.message == WM_LBUTTONUP) // 鼠标松开左键
//        {
//            nextcurrentx = msg.x;
//            nextcurrenty = msg.y;
//            drawexchangeimg();
//        }
//    }
//}
//
//int main()
//{
//    InitGraph();
//    dram();
//    while (1)
//    {
//        usercheck();
//        //Sleep(20);
//    }
//    closegraph();
//
//    return 0;
//}



#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <Mmsystem.h>
//1 游戏开始界面，更换图片选择
int map[4][4] = {1, 4, 9,6,
				 12,15,5,7,
				  3,8,10,11,
				 13,14,2,0 };

struct MyStruct//记录图片位置，交换用
{
	int xx;
	int yy;

}hs[4][4];
int hss[4][4];
//int map[4][4] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,15,14 };

IMAGE img;
HWND hwnd;

int flog = 0;
int currentx, currenty, nextcurrentx, nextcurrenty;

void InitGraph()
{
	hwnd=initgraph(800, 800); // 初始化窗口 并获得句柄
	//settextcolor(YELLOW);
	//settextstyle(25, 0, "楷体");
	//outtextxy(400, 200, "拼图小游戏");
	loadimage(&img, "./test.jpg", 800, 800);//得测试一下是否可行
	//putimage(0, 0, &img);
	//putimage(0, 0, 200, 200, &img, 200, 200);
}
int check()
{
	int c = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (hss[i][j] != c)//map[i][j]不行 因为没交换
				return 0;
			c++;
		}
	}
	return 1;
}
void dram()
{
	//printf("Jjjj\n");
	int x, y;
	int xx, yy;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			x = j * 200, y = i * 200;
			xx = (map[i][j] % 4) * 200;
			yy = (map[i][j] / 4) * 200;
			putimage(x, y, 200, 200, &img, xx, yy);
			/*hs[i][j].xx = xx;不存位置，而是存块
			hs[i][j].yy = yy;*/
			hs[i][j].xx = (map[i][j] % 4);
			hs[i][j].yy = (map[i][j] / 4);

			hss[i][j] = map[i][j];
		}
	}

	//putimage(0, 0, 200, 200, &img, 200, 200);
}
void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
void drawexchingeimg()
{
	//交换数值
	//if (flog == false) return;
	////int temp1=0,temp2=0;
	////需要转换，下x->y,,y->x才对的上所在的位置
	//currentx = currenty / 200;
	//currenty = currentx / 200;
	//nextcurrentx = nextcurrenty / 200;
	//nextcurrenty = nextcurrentx / 200;
	//
	//printf("h %d %d  %d  %d\n", currentx, currenty, nextcurrentx, nextcurrenty);
	//printf("h %d %d  %d  %d\n",hs[currentx][currenty].xx, hs[currentx][currenty].yy ,
	//	     hs[nextcurrentx][nextcurrenty].xx, hs[nextcurrentx][nextcurrenty].yy);

	//putimage(currentx, currenty,200,200, &img,
	//	hs[nextcurrentx][nextcurrenty].xx, hs[nextcurrentx][nextcurrenty].yy);

	//putimage(nextcurrentx, nextcurrenty, 200, 200, &img,
	//	hs[currentx][currenty].xx, hs[currentx][currenty].yy);

	//printf("hhh\n");

	if (flog == 0) return;

	// 需要转换，下x->y,,y->x才对的上所在的位置


	currentx /= 200;
	currenty /= 200;
	nextcurrentx /= 200;
	nextcurrenty /= 200;

	//printf("h %d %d  %d  %d\n", currentx, currenty, nextcurrentx, nextcurrenty);
	//printf("h %d %d  %d  %d\n", hs[currRow][currCol].xx, hs[currRow][currCol].xx,
								//hs[nextRow][nextCol].xx, hs[nextRow][nextCol].yy);

	int cy = currenty;
	int cx = currentx;
	int ncy = nextcurrenty ;
	int ncx = nextcurrentx;

	swap(&currentx, &currenty);
	swap(&nextcurrentx, &nextcurrenty);
	// 交换 map 数组中的值
	//printf("jianhuanhou\n");
	//int temp = map[currentx][currenty];
	//map[currentx][currenty] = map[nextcurrentx][nextcurrenty];
	//map[nextcurrentx][nextcurrenty] = temp;hss得到第几块，
	printf("current: %d %d  nextcurrent:%d  %d\n", currentx, currenty, nextcurrentx, nextcurrenty);
	
	printf("cxy: %d %d  ncxy:%d  %d\n", cx, cy, ncx, ncy);
	printf("hss[currentx][currenty]: %d hss[nextcurrent]: %d \n", hss[currentx][currenty], hss[nextcurrentx][nextcurrenty]);

	/*printf("curt hsq:%d %d\n", (hs[currentx][currenty].xx), (hs[currentx][currenty].yy));
	printf("curt hsh:%d %d\n", (hs[currentx][currenty].xx) * 200, (hs[currentx][currenty].yy) * 200);

	printf("ncurt hsq:%d %d\n", (hs[nextcurrentx][nextcurrenty].xx), (hs[nextcurrentx][nextcurrenty].yy));
	printf("ncurt hsh:%d %d\n", (hs[nextcurrentx][nextcurrenty].xx) * 200, (hs[nextcurrentx][nextcurrenty].yy) * 200);
	*/// 重新绘制交换后的图像块
	//putimage(currentx * 200, currenty * 200, 200, 200, &img,
		//(hs[nextcurrentx][nextcurrenty].xx) * 200, (hs[nextcurrentx][nextcurrenty].yy)*200);

	//putimage(nextcurrentx * 200, nextcurrentx * 200, 200, 200, &img,
		//hs[currentx][currenty].xx, hs[currentx][currenty].xx);

	//终于写好了
	putimage(cx * 200, cy * 200, 200, 200, &img,
		(hss[nextcurrentx][nextcurrenty]%4) * 200, (hss[nextcurrentx][nextcurrenty]/4) * 200);

	putimage(ncx * 200, ncy * 200, 200, 200, &img,
		(hss[currentx][currenty] % 4) * 200, (hss[currentx][currenty]/4)*200);
	
	swap(&hss[currentx][currenty], &hss[nextcurrentx][nextcurrenty]);

	flog = 0;

}
void userchock()
{

	ExMessage msg;
	peekmessage(&msg, EM_MOUSE);
	if (msg.message == WM_LBUTTONDOWN)//按下鼠标左键
	{
		flog = 1;
		currentx = msg.x;
		currenty = msg.y;
		//printf("h %d %d  \n", currentx/200, currenty/200);
	}
	if (msg.message == WM_MOUSEMOVE)//鼠标移动
	{

	}
	if (msg.message == WM_LBUTTONUP)//鼠标松开左键
	{
		nextcurrentx = msg.x;
		nextcurrenty = msg.y;

		//需要交换这两个图片
		//
		//printf("q:%d %d  %d  %d\n", currentx, currenty, nextcurrentx, nextcurrenty);

		drawexchingeimg();
		//Sleep(1000);
		//flog = 0;
	}
}
void PrintfWin()
{
	MessageBox(hwnd, " Congratulations on you win", "WIN", MB_OK);
	return;
}
int main()
{

	InitGraph();
	dram();
	/*for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%d  %d , kuai:%d; ", hs[i][j].xx, hs[i][j].yy, hss[i][j]);
		}
		printf("\n");
	}*/
	while (1)
	{
		if (check()==1) {
			printf("111\n");
			PrintfWin();
			return 0;
		}
		userchock();
		//Sleep(20);
	}
	closegraph();

	return 0;
}