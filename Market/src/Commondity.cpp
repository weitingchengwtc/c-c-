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
	printf("  ����    ID     �۸�   �ϼ�ʱ��    ״̬  ������\n");
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

void BuyCmd(USER user)//��Ҫ�Ż�
{
	int i = AccurateFindcmd();
	if (i == -1)return;
	if (CurrentUser.Money < cmdarr[i].pricce)
	{
		printf(" ��Ǹ �������\n");
		return;
	}
	printf(" ȷ���Ƿ��� Y|N   ");
	char ch;
	cin >> ch;
	if (ch == 'Y' || ch == 'y')
	{
		//������Ҫ����һ�����ɶ���
		CreateOdrer(cmdarr[i].pricce, cmdarr[i]);
		CurrentUser.Money = CurrentUser.Money - cmdarr[i].pricce;
		strcpy(cmdarr[i].sendtouser, CurrentUser.UserId);
		//������Ǯ �����漰���ܶ��ѯ����Ҫ����Ʒ��������
		FindUserAndToMoney(cmdarr[i].ByUserId, cmdarr[i].pricce);//�ҵ����� ��������Ǯ

	}
	else if (ch == 'N' || ch == 'n')
	{
		return;
	}
}
void GetCurrenDate(char* ch)
{
	time_t now = time(NULL);
	// ��ȡһ���ṹ�������ڱ�ʾ
	struct tm* timeStruct;
	timeStruct = localtime(&now);
	// 11���ַ��㹻�洢 YYYY-MM-DD ��ʽ������
	// ʹ��strftime������ʽ������
	char formattedDate[12];
	strftime(formattedDate, sizeof(formattedDate), "%Y-%m-%d", timeStruct);
	// ֱ����ָ�������ʼ�������У�ֻ�ܼ�Ӵ���ȥ��
	strcpy(ch, formattedDate);
}
void CreateCommondity(FILE* fp, USER user)
{
	printf("��д ����, �۸� : ");
	COMMODITY commondity;
	cin >> commondity.commodityName >> commondity.pricce;
	GetCurrenDate(commondity.CreatDate);
	GetRandCmdId(RandNums(), commondity.commodityid);
	strcpy(commondity.ByUserId, user.UserId);
	strcpy(commondity.sendtouser, "1");
	//fprintf(fp, "%s %s %d %s %s %s\n", commondity.commodityName, commondity.commodityid,/*
	//	commondity.pricce, commondity.CreatDate, commondity.ByUserId, commondity.sendtouser);*/
	cmdarr[cmdcount++] = commondity;
	printf("�ϼܳɹ�\n");
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

void Printf(COMMODITY cmd) // �Դ�ӡ���з�װ
{
	printf("%-10s %7s %4.2d %s", cmd.commodityName, cmd.commodityid,
		cmd.pricce, cmd.CreatDate);
	if (strcmp(cmd.sendtouser, "1") == 0)
	{
		printf("   ������\n");
	}
	else if (strcmp(cmd.sendtouser, "0") == 0)
	{
		printf("   ���¼�\n");
	}
	else
	{
		printf("   ���۳�\n");
	}
}
void DisplyAllCmd(bool flog)
{
	printf("=========================================\n");
	printf("  ����    ID     �۸�   �ϼ�ʱ��    ״̬    \n");

	for (int i = 0; i < cmdcount; i++)
	{
		// printf("%-10s %7s %4.2d %s", cmdarr[i].commodityName, cmdarr[i].commodityid,
		//        cmdarr[i].pricce, cmdarr[i].CreatDate);
		// if (strcmp(cmdarr[i].sendtouser, "1") == 0)
		// {
		//     printf("   ������\n");
		// }
		// else if (strcmp(cmdarr[i].sendtouser, "0") == 0)
		// {
		//     printf("   ���¼�\n");
		// }
		// else
		// {
		//     printf("   ���۳�\n");
		// }
		if (flog)//��Ҫ���
		{
			if (strcmp(cmdarr[i].ByUserId, CurrentUser.UserId) == 0)
			{
				Printf(cmdarr[i]);
			}
		}
		else
		{
			Printf(cmdarr[i]); // ��װ�Ա��������ط��������
		}
	}
	printf("=========================================\n");
}
void DisplyTest()//��־λ ���ֲ����л��ǲ鵥��
{
	// printf("=========================================\n");
	// printf("  ����     ID     �۸�   �ϼ�ʱ��    ״̬  ������\n");
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
			printf("   ������ ");
		}
		else if (strcmp(cmdarr[i].sendtouser, "0") == 0)
		{
			printf("   ���¼� ");
		}
		else
		{
			printf("   ���۳� ");
		}
		printf("%-7s\n", cmdarr[i].ByUserId);

		// Printf(cmdarr[i]); // ��װ�Ա��������ط��������
	}
	pfline();
}
void RemoveCmd()
{
	//�����¼���Ʒֻ���¼����Լ��ϼܵ���Ʒ������Ա���¼������˷�����
	printf("������ƷID �¼ܸ���Ʒ  ");
	char str[12];
	cin >> str;
	for (int i = 0; i < cmdcount; i++)
	{
		//�ҵ���ǰ��������������Ʒ
		if ((strcmp(CurrentUser.UserId, cmdarr[i].ByUserId) == 0) &&
			(strcmp(str, cmdarr[i].commodityid) == 0))
		{
			pfline();
			Printf(cmdarr[i]);
			pfline();
			printf("ȷ���¼ܸ���Ʒ�� Y|N   ");
			char ch;
			cin >> ch;
			if (ch == 'Y' || ch == 'y')
			{
				strcpy(cmdarr[i].sendtouser, "0"); // ���¼�
			}
			else if (ch == 'N' || ch == 'n')
			{
				return;
			}
			return;
		}
	}
	printf("δ�ϼ���Ʒ����ȫ���¼�\n");
}
void LikeFindCmd() // ����ֻ���δ�۳���Ʒ
{
	char str[25];
	printf("��������  ");
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
	printf("������  ");
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
	printf("û�и���Ʒ\n");
	pfline();
	return -1;
}
void CmdMenu()
{
	pfline();
	printf("1 �ϼ���Ʒ, 2 �¼���Ʒ, 3 ��ѯ����, 4 �˳���ǰ״̬, 5 �鿴����, 6 ɾ����Ʒ\n");
	pfline();
}
void DeleteCmd()
{
	printf("���붩��ID ��ɾ���ö���   ");
	char str[10];
	cin >> str;
	char currentuser[20] = "U12126"; // ģ�⵱ǰ�û�
	for (int i = 0; i < cmdcount; i++)
	{
		if (strcmp(cmdarr[i].ByUserId, currentuser) == 0 && strcmp(cmdarr[i].commodityid, str) == 0)
		{
			printf("ȷ��ɾ������Ʒ�� Y|N   ");
			char ch;
			cin >> ch;
			if (ch == 'Y' || ch == 'y')
			{
				strcpy(cmdarr[i].ByUserId, "-1"); // ��ɾ��
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