#define _CRT_SECURE_NO_WARNINGS
#include"commondity.h"
#include"users.h"
#include"order.h"

using namespace std;
COMMODITY cmdarr[MAXCMD];
int cmdcount;
void GetRandCmdId(int nums, char* str)
{
	char ch[20];
	sprintf(ch, "M%d", nums);
	strcpy(str, ch);
	// printf("%s\n", ch);
}
void pfmenu()
{
	printf("  名称    ID     价格   上架时间    状态  发布者\n");
}
void pfline()
{
	printf("***************************************************\n");
}
int RandNums()
{
	int randnum = rand() % (66666 + 1) + 10000;
	return randnum;
}

void BuyCmd(USER user)//需要优化
{
	int i = AccurateFindcmd();
	if (i == -1)return;
	if (CurrentUser.Money < cmdarr[i].pricce)
	{
		printf(" 抱歉 你的余额不足\n");
		return;
	}
	printf(" 确认是否购买？ Y|N   ");
	char ch;
	cin >> ch;
	if (ch == 'Y' || ch == 'y')
	{
		//这里需要加上一个生成订单
		CreateOdrer(cmdarr[i].pricce, cmdarr[i]);
		CurrentUser.Money = CurrentUser.Money - cmdarr[i].pricce;
		strcpy(cmdarr[i].sendtouser, CurrentUser.UserId);
		//给卖家钱 这里涉及到很多查询，需要查商品，创建者
		FindUserAndToMoney(cmdarr[i].ByUserId, cmdarr[i].pricce);//找到卖家 并给他打钱

	}
	else if (ch == 'N' || ch == 'n')
	{
		return;
	}
}
void GetCurrenDate(char* ch)
{
	time_t now = time(NULL);
	// 获取一个结构化的日期表示
	struct tm* timeStruct;
	timeStruct = localtime(&now);
	// 11个字符足够存储 YYYY-MM-DD 格式的日期
	// 使用strftime函数格式化日期
	char formattedDate[12];
	strftime(formattedDate, sizeof(formattedDate), "%Y-%m-%d", timeStruct);
	// 直接用指针进来初始化不得行，只能间接传出去。
	strcpy(ch, formattedDate);
}
void CreateCommondity(FILE* fp, USER user)
{
	printf("填写 名称, 价格 : ");
	COMMODITY commondity;
	cin >> commondity.commodityName >> commondity.pricce;
	GetCurrenDate(commondity.CreatDate);
	GetRandCmdId(RandNums(), commondity.commodityid);
	strcpy(commondity.ByUserId, user.UserId);
	strcpy(commondity.sendtouser, "1");
	//fprintf(fp, "%s %s %d %s %s %s\n", commondity.commodityName, commondity.commodityid,/*
	//	commondity.pricce, commondity.CreatDate, commondity.ByUserId, commondity.sendtouser);*/
	cmdarr[cmdcount++] = commondity;
	printf("上架成功\n");
}
void StartLoadCmd(FILE* fp)
{
	cmdcount = 0;
	COMMODITY commondity;
	while (fscanf(fp, "%s %s %d %s %s %s", commondity.commodityName, commondity.commodityid,
		&commondity.pricce, commondity.CreatDate, commondity.ByUserId, commondity.sendtouser) != EOF)
	{
		// printf("%-10s %7s %4.2d %s\n", commondity.commodityName, commondity.commodityid, commondity.pricce, commondity.CreatDate);
		cmdarr[cmdcount++] = commondity;
	}
}

void Printf(COMMODITY cmd) // 对打印进行封装
{
	printf("%-10s %7s %4.2d %s", cmd.commodityName, cmd.commodityid,
		cmd.pricce, cmd.CreatDate);
	if (strcmp(cmd.sendtouser, "1") == 0)
	{
		printf("   在售中\n");
	}
	else if (strcmp(cmd.sendtouser, "0") == 0)
	{
		printf("   已下架\n");
	}
	else
	{
		printf("   已售出\n");
	}
}
void DisplyAllCmd(bool flog)
{
	printf("=========================================\n");
	printf("  名称    ID     价格   上架时间    状态    \n");

	for (int i = 0; i < cmdcount; i++)
	{
		// printf("%-10s %7s %4.2d %s", cmdarr[i].commodityName, cmdarr[i].commodityid,
		//        cmdarr[i].pricce, cmdarr[i].CreatDate);
		// if (strcmp(cmdarr[i].sendtouser, "1") == 0)
		// {
		//     printf("   在售中\n");
		// }
		// else if (strcmp(cmdarr[i].sendtouser, "0") == 0)
		// {
		//     printf("   已下架\n");
		// }
		// else
		// {
		//     printf("   已售出\n");
		// }
		if (flog)//需要检测
		{
			if (strcmp(cmdarr[i].ByUserId, CurrentUser.UserId) == 0)
			{
				Printf(cmdarr[i]);
			}
		}
		else
		{
			Printf(cmdarr[i]); // 封装以便后边其他地方方便调用
		}
	}
	printf("=========================================\n");
}
void DisplyTest()//标志位 区分查所有还是查单个
{
	// printf("=========================================\n");
	// printf("  名称     ID     价格   上架时间    状态  发布者\n");
	pfline();
	pfmenu();
	for (int i = 0; i < cmdcount; i++)
	{
		if (strcmp(cmdarr[i].ByUserId, "-1") == 0)
		{
			continue;
		}
		//if (!flog)return;//false 
		printf("%-10s %7s %4.2d %s", cmdarr[i].commodityName, cmdarr[i].commodityid,
			cmdarr[i].pricce, cmdarr[i].CreatDate);
		if (strcmp(cmdarr[i].sendtouser, "1") == 0)
		{
			printf("   在售中 ");
		}
		else if (strcmp(cmdarr[i].sendtouser, "0") == 0)
		{
			printf("   已下架 ");
		}
		else
		{
			printf("   已售出 ");
		}
		printf("%-7s\n", cmdarr[i].ByUserId);

		// Printf(cmdarr[i]); // 封装以便后边其他地方方便调用
	}
	pfline();
}
void RemoveCmd()
{
	//卖家下架商品只能下架他自己上架的商品，管理员可下架所有人发布的
	printf("输入商品ID 下架该商品  ");
	char str[12];
	cin >> str;
	for (int i = 0; i < cmdcount; i++)
	{
		//找到当前对象所发布的商品
		if ((strcmp(CurrentUser.UserId, cmdarr[i].ByUserId) == 0) &&
			(strcmp(str, cmdarr[i].commodityid) == 0))
		{
			pfline();
			Printf(cmdarr[i]);
			pfline();
			printf("确认下架该商品？ Y|N   ");
			char ch;
			cin >> ch;
			if (ch == 'Y' || ch == 'y')
			{
				strcpy(cmdarr[i].sendtouser, "0"); // 已下架
			}
			else if (ch == 'N' || ch == 'n')
			{
				return;
			}
			return;
		}
	}
	printf("未上架商品或已全部下架\n");
}
void LikeFindCmd() // 查找只针对未售出商品
{
	char str[25];
	printf("输入名称  ");
	cin >> str;
	pfline();
	pfmenu();
	for (int i = 0; i < cmdcount; i++)
	{
		if (strcmp(cmdarr[i].sendtouser, "1") == 0)
		{
			if (strstr(cmdarr[i].commodityName, str) != NULL)
			{
				Printf(cmdarr[i]);
			}
		}
	}
	pfline();
}
int AccurateFindcmd()
{
	char str[25];
	printf("输入编号  ");
	cin >> str;
	//cout << str << endl;
	pfline();
	pfmenu();
	for (int i = 0; i < cmdcount; i++)
	{
		if (strcmp(cmdarr[i].sendtouser, "1") == 0)
		{
			if (strcmp(cmdarr[i].commodityid, str) == 0)
			{
				Printf(cmdarr[i]);
				pfline();
				return i;
			}
		}
	}
	printf("没有该商品\n");
	pfline();
	return -1;
}
void CmdMenu()
{
	pfline();
	printf("1 上架商品, 2 下架商品, 3 查询订单, 4 退出当前状态, 5 查看所有, 6 删除商品\n");
	pfline();
}
void DeleteCmd()
{
	printf("输入订单ID 以删除该订单   ");
	char str[10];
	cin >> str;
	char currentuser[20] = "U12126"; // 模拟当前用户
	for (int i = 0; i < cmdcount; i++)
	{
		if (strcmp(cmdarr[i].ByUserId, currentuser) == 0 && strcmp(cmdarr[i].commodityid, str) == 0)
		{
			printf("确认删除该商品？ Y|N   ");
			char ch;
			cin >> ch;
			if (ch == 'Y' || ch == 'y')
			{
				strcpy(cmdarr[i].ByUserId, "-1"); // 已删除
			}
			else if (ch == 'N' || ch == 'n')
			{
				return;
			}
			return;
		}
	}
}
void WriteCmdtodocment(FILE* fp)
{
	for (int i = 0; i < cmdcount; i++)
	{
		if (strcmp(cmdarr[i].ByUserId, "-1") == 0)
		{
			continue;
		}
		fprintf(fp, "%s %s %d %s %s %s\n", cmdarr[i].commodityName, cmdarr[i].commodityid,
			cmdarr[i].pricce, cmdarr[i].CreatDate, cmdarr[i].ByUserId, cmdarr[i].sendtouser);
	}
}