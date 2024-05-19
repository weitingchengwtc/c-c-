#define _CRT_SECURE_NO_WARNINGS
#include"commondity.h"
#include"users.h"
#include"order.h"
#include <cstdio>
#include <cstring>
#include <time.h>
using namespace std;

USER UserArr[MAXUser];
int UserNumsCnt = 0;
USER CurrentUser;
void MainMenu()
{
	pfline();
	printf("1 登陆,2 注册,3 管理员登陆, 4 退出,5 查看所有, 6 注销\n");
	pfline();
}

int Unregister(USER user)//用户注销
{
	cout << user.UserName << " " << user.UserId << " " << endl;
	// printf("输入用户ID 将对其进行注销");
	for (int i = 0; i < UserNumsCnt; i++)
	{
		if (user.UserId == UserArr[i].UserId)
		{
			strcpy(UserArr[i].UserId, "-1");// 借此标志作为删除操作
			printf("删除成功\n");
			return 1;
		}
	}
	return -1;
}
int GetRandNums()//获得随机数
{
	int nums = rand() % (66666 + 1) + 10000;
	return nums;
}
void GetRandUserID(int nums, char* str)//获得随机用户ID
{
	char ch[12];
	sprintf(ch, "U%d", nums);
	strcpy(str, ch);
}
void RegisterUser(FILE* fp)//用户注册
{
	USER user;
	printf("开始注册 请输入账号 密码 电话 地址\n");
	cin >> user.UserName >> user.PassWorld >> user.Iphone >> user.Address;
	GetRandUserID(GetRandNums(), user.UserId);
	user.flog = user.Money = 0;
	UserArr[UserNumsCnt++] = user;
	printf("注册成功\n");
	fclose(fp);
	return;
}
void WriteUserToDocument(FILE* fp)
{
	for (int i = 0; i < UserNumsCnt; i++)
	{
		if (strcmp(UserArr[i].UserId, "-1") == 0)
			continue;
		fprintf(fp, "%s %s %s %s %d %d %d\n", UserArr[i].UserName, UserArr[i].PassWorld, UserArr[i].UserId,
			UserArr[i].Address, UserArr[i].Iphone, UserArr[i].Money, UserArr[i].flog);
	}
	cout << "OK" << endl;
}
void PrintfUserData()
{
	printf("================================================\n");
	printf("用户名  密码   ID   电话    地址    零钱    权限\n");
	cout << "PrintfData:" << UserNumsCnt << endl;
	for (int i = 0; i < UserNumsCnt; i++)
	{
		if (strcmp(UserArr[i].UserId, "-1") == 0)
		{
			continue;
		}
		printf("%s %s %s %s %d %d %d\n", UserArr[i].UserName, UserArr[i].PassWorld, UserArr[i].UserId,
			UserArr[i].Address, UserArr[i].Iphone, UserArr[i].Money, UserArr[i].flog);
	}
}
void StartLoadData(FILE* fp)
{
	USER user;
	while (fscanf(fp, "%s %s %s %s %d  %d %d", user.UserName, user.PassWorld, user.UserId,
		user.Address, &user.Iphone, &user.Money, &user.flog) != EOF)
	{
		UserArr[UserNumsCnt] = user; // 这个操作，竟然可以直接赋值

		// printf("%s %s %d %s %d %0.d %d\n", UserArr[i].UserName, UserArr[i].PassWorld, UserArr[i].UserId,
		//        UserArr[i].Address, UserArr[i].Iphone, UserArr[i].Money, UserArr[i].flog);

		UserNumsCnt++;
	}
}
bool Login()
{
	printf("输入用户名和密码: ");
	char username[20], passworld[20];
	cin >> username >> passworld;
	for (int i = 0; i < UserNumsCnt; i++)
	{
		if ((strcmp(username, UserArr[i].UserName) == 0) && (strcmp(passworld, UserArr[i].PassWorld) == 0))
		{
			CurrentUser = UserArr[i];
			printf("登陆成功\n");
			/*printf("%s %s %s %s %d %d %d\n", CurrentUser.UserName, CurrentUser.PassWorld, CurrentUser.UserId,
				CurrentUser.Address, CurrentUser.Iphone, CurrentUser.Money, CurrentUser.flog);*/

			return true;
		}
	}
	printf("登陆失败\n");
	return false;
}
void UpdateUser(USER user)//
{
	for (int i = 0; i < UserNumsCnt; i++)
	{
		if ((strcmp(UserArr[i].UserName, user.UserName) == 0) && (strcmp(UserArr[i].UserId, user.UserId) == 0))
		{
			UserArr[i] = user;
			return;
		}
	}
	printf("失败\n");
}
void SetUser(USER user)
{
	printf("重置 账号 密码 电话 地址\n");
	cin >> user.UserName >> user.PassWorld >> user.Iphone >> user.Address;
	UpdateUser(user);
	printf("修改成功\n");
}

void BuyUser()
{
	int choice;
	while (1)
	{
		pfline();
		printf("1 查看所有商品, 2 搜索商品, 3 购买商品，4 我的订单,  5 退出 \n");
		pfline();
		cin >> choice;
		switch (choice)
		{
		case 1:
			DisplyTest();
			break;
		case 2:
			LikeFindCmd();
			break;
		case 3:
			BuyCmd(CurrentUser);
			break;
		case 4:
			//fp = fopen("commondity.txt", "w");
			//EndWritetodocment(fp);
			//fclose(fp);
			BuyuserFindOrder();
			break;
		case 6:
			DisplyTest();
			break;
		case 5:
			return;
			break;
		default:
			break;
		}
	}
}
void SellUser()
{

	FILE* fp = NULL;
	int choice;
	while (1)
	{
		pfline();
		printf("1 商品上架, 2 商品下架， 3 查看历史订单, 5 我的主页,  4 退出， 6 所有商品 ，7 查看已发布商品\n");
		pfline();
		cin >> choice;
		switch (choice)
		{
		case 1:
			fp = fopen("commondity.txt", "a");
			CreateCommondity(fp, CurrentUser);
			fclose(fp);
			//立刻加载看看成效
			DisplyTest();
			break;
		case 2:
			RemoveCmd();
			break;
		case 3:
			MenuUser();
			break;
		case 4:
			//这里退出之后先不写入文件，此时在数据结构中已做修改，只需要程序退出时一次写入就好了。
			/*fp = fopen("commondity.txt", "w");
			EndWritetodocment(fp);
			fclose(fp);*/

			SelluserFindOrder();
			break;
		case 6:
			DisplyTest();
			break;
		case 7:
			DisplyAllCmd(true);//
			break;
		default:
			break;
		}
	}
}
void LoginMain()
{
	int choice;
	while (1)
	{
		pfline();
		printf("1 我是买家, 2 我是卖家, 3 我的主页,  4 退出 \n");
		pfline();
		cin >> choice;
		switch (choice)
		{
		case 1:
			BuyUser();
			break;
		case 2:
			SellUser();
			break;
		case 3:
			MenuUser();
			break;
		case 4:
			return;
			break;
		default:
			break;
		}
	}
}
void MenuUser()
{
	int choice;
	while (1)
	{
		printf("============================================\n");
		printf("1 我的信息,2 设置,3 注销, 4 充值, 5 退出 \n");
		printf("============================================\n");
		cin >> choice;
		switch (choice)
		{
		case 1:
			printf("================================================\n");
			printf("用户名  密码   ID   电话    地址    零钱    权限\n");
			printf("%s %s %s %s %d %0.d %d\n", CurrentUser.UserName, CurrentUser.PassWorld, CurrentUser.UserId,
				CurrentUser.Address, CurrentUser.Iphone, CurrentUser.Money, CurrentUser.flog);
			printf("================================================\n");
			break;
		case 2:
			SetUser(CurrentUser);
			break;
		case 3:
			Unregister(CurrentUser);
			printf("修改成功\n");
			break;
		case 4:
			printf("输入充值金额  ");
			int money;
			cin >> money;
			CurrentUser.Money += money;
			UpdateUser(CurrentUser);
			break;
		case 5:
			UpdateUser(CurrentUser);
			return;
			break;
		}
	}
}
void FindUserAndToMoney(char* userid, int money)
{
	for (int i = 0; i < UserNumsCnt; i++)
	{
		if (strcmp(userid, UserArr[i].UserId) == 0)
		{
			UserArr[i].Money = UserArr[i].Money + money;
			return;
		}
	}
	return;
}
