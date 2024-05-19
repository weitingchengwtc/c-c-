#define _CRT_SECURE_NO_WARNINGS
//#include"users.h"
//#include "commondity.h"
//#include"order.h"


//test
#include"interface.h"

using namespace std;

int main()
{

	pmain();
	pcmd();
	puser();
	main_interface();

	// 
	//主测试之后打开
	//srand((unsigned int)time(NULL));
	//
	//FILE* fp = NULL;
	//fp = fopen("User.txt", "r");
	//StartLoadData(fp);
	//fclose(fp);
	//fp = fopen("commondity.txt", "r");
	//if (fp == NULL)
	//{
	//	printf("打开错误\n");
	//	return 0;
	//}
	//StartLoadCmd(fp);
	//fclose(fp);
	//fp = fopen("order.txt", "r");
	//StartLoading(fp);
	//fclose(fp);

	//bool token = false;
	//while (1)
	//{
	//	MainMenu();
	//	//	printf("1 登陆,2 注册,3 管理员登陆, 4 退出,5 查看所有, 6 注销\n");

	//	int iswitch = -1;
	//	cin >> iswitch;
	//	switch (iswitch)
	//	{
	//	case 1:
	//		token = Login();
	//		if (token)
	//		{
	//			//MenuUser();
	//			LoginMain();
	//			strcpy(CurrentUser.UserId, "-1");//表示当前登录的对象为空
	//		}
	//		break;
	//	case 2:
	//		fp = fopen("User.txt", "a");
	//		if (fp == NULL)
	//		{
	//			cout << "文件打开失败" << endl;
	//			break;
	//		}
	//		RegisterUser(fp);
	//		fclose(fp);
	//		break;
	//	case 3:

	//		break;
	//	case 4:
	//		fp = fopen("User.txt", "w");
	//		//结束的时候需要将cmd user order 数据写入文件
	//		WriteUserToDocument(fp);
	//		fclose(fp);

	//		fp = fopen("commondity.txt", "w");
	//		if (fp == NULL)
	//		{
	//			printf("打开错误\n");
	//			return 0;
	//		}
	//		WriteCmdtodocment(fp);
	//		fclose(fp);

	//		fp = fopen("order.txt", "w");
	//		WriterOrderToDmt(fp);
	//		fclose(fp);

	//		exit(0);
	//		break;
	//	case 5:
	//		if (strcmp(CurrentUser.UserId, "-1") != 0)
	//		{
	//			printf("请先登录\n");
	//			break;
	//		}
	//		PrintfUserData();
	//		break;
	//	case 6:
	//		if (strcmp(CurrentUser.UserId, "-1") != 0)
	//		{
	//			printf("请先登录\n");
	//			break;
	//		}
	//		Unregister(CurrentUser);
	//		break;
	//	}
	//}



	//测试comd

	/*FILE* fp = NULL;
	fp = fopen("commondity.txt", "r");
	LoadCmd(fp);
	fclose(fp);
	int choice;
	while (1)
	{
		CmdMenu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			fp = fopen("commondity.txt", "a");
			CreateCommondity(fp,CurrentUser);
			fclose(fp);
			break;
		case 2:
			RemoveCmd();
			break;
		case 3:
			FindCmd();
			break;
		case 4:
			fp = fopen("commondity.txt", "w");
			EndWritetodocment(fp);
			fclose(fp);
			return 0;
			break;
		case 5:
			DisplyTest();
			break;
		case 6:
			DeleteCmd();
			break;
		}
	}*/

	return 0;
}