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
	printf("1 ��½,2 ע��,3 ����Ա��½, 4 �˳�,5 �鿴����, 6 ע��\n");
	pfline();
}

int Unregister(USER user)//�û�ע��
{
	cout << user.UserName << " " << user.UserId << " " << endl;
	// printf("�����û�ID ���������ע��");
	for (int i = 0; i < UserNumsCnt; i++)
	{
		if (user.UserId == UserArr[i].UserId)
		{
			strcpy(UserArr[i].UserId, "-1");// ��˱�־��Ϊɾ������
			printf("ɾ���ɹ�\n");
			return 1;
		}
	}
	return -1;
}
int GetRandNums()//��������
{
	int nums = rand() % (66666 + 1) + 10000;
	return nums;
}
void GetRandUserID(int nums, char* str)//�������û�ID
{
	char ch[12];
	sprintf(ch, "U%d", nums);
	strcpy(str, ch);
}
void RegisterUser(FILE* fp)//�û�ע��
{
	USER user;
	printf("��ʼע�� �������˺� ���� �绰 ��ַ\n");
	cin >> user.UserName >> user.PassWorld >> user.Iphone >> user.Address;
	GetRandUserID(GetRandNums(), user.UserId);
	user.flog = user.Money = 0;
	UserArr[UserNumsCnt++] = user;
	printf("ע��ɹ�\n");
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
	printf("�û���  ����   ID   �绰    ��ַ    ��Ǯ    Ȩ��\n");
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
		UserArr[UserNumsCnt] = user; // �����������Ȼ����ֱ�Ӹ�ֵ

		// printf("%s %s %d %s %d %0.d %d\n", UserArr[i].UserName, UserArr[i].PassWorld, UserArr[i].UserId,
		//        UserArr[i].Address, UserArr[i].Iphone, UserArr[i].Money, UserArr[i].flog);

		UserNumsCnt++;
	}
}
bool Login()
{
	printf("�����û���������: ");
	char username[20], passworld[20];
	cin >> username >> passworld;
	for (int i = 0; i < UserNumsCnt; i++)
	{
		if ((strcmp(username, UserArr[i].UserName) == 0) && (strcmp(passworld, UserArr[i].PassWorld) == 0))
		{
			CurrentUser = UserArr[i];
			printf("��½�ɹ�\n");
			/*printf("%s %s %s %s %d %d %d\n", CurrentUser.UserName, CurrentUser.PassWorld, CurrentUser.UserId,
				CurrentUser.Address, CurrentUser.Iphone, CurrentUser.Money, CurrentUser.flog);*/

			return true;
		}
	}
	printf("��½ʧ��\n");
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
	printf("ʧ��\n");
}
void SetUser(USER user)
{
	printf("���� �˺� ���� �绰 ��ַ\n");
	cin >> user.UserName >> user.PassWorld >> user.Iphone >> user.Address;
	UpdateUser(user);
	printf("�޸ĳɹ�\n");
}

void BuyUser()
{
	int choice;
	while (1)
	{
		pfline();
		printf("1 �鿴������Ʒ, 2 ������Ʒ, 3 ������Ʒ��4 �ҵĶ���,  5 �˳� \n");
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
		printf("1 ��Ʒ�ϼ�, 2 ��Ʒ�¼ܣ� 3 �鿴��ʷ����, 5 �ҵ���ҳ,  4 �˳��� 6 ������Ʒ ��7 �鿴�ѷ�����Ʒ\n");
		pfline();
		cin >> choice;
		switch (choice)
		{
		case 1:
			fp = fopen("commondity.txt", "a");
			CreateCommondity(fp, CurrentUser);
			fclose(fp);
			//���̼��ؿ�����Ч
			DisplyTest();
			break;
		case 2:
			RemoveCmd();
			break;
		case 3:
			MenuUser();
			break;
		case 4:
			//�����˳�֮���Ȳ�д���ļ�����ʱ�����ݽṹ�������޸ģ�ֻ��Ҫ�����˳�ʱһ��д��ͺ��ˡ�
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
		printf("1 �������, 2 ��������, 3 �ҵ���ҳ,  4 �˳� \n");
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
		printf("1 �ҵ���Ϣ,2 ����,3 ע��, 4 ��ֵ, 5 �˳� \n");
		printf("============================================\n");
		cin >> choice;
		switch (choice)
		{
		case 1:
			printf("================================================\n");
			printf("�û���  ����   ID   �绰    ��ַ    ��Ǯ    Ȩ��\n");
			printf("%s %s %s %s %d %0.d %d\n", CurrentUser.UserName, CurrentUser.PassWorld, CurrentUser.UserId,
				CurrentUser.Address, CurrentUser.Iphone, CurrentUser.Money, CurrentUser.flog);
			printf("================================================\n");
			break;
		case 2:
			SetUser(CurrentUser);
			break;
		case 3:
			Unregister(CurrentUser);
			printf("�޸ĳɹ�\n");
			break;
		case 4:
			printf("�����ֵ���  ");
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
