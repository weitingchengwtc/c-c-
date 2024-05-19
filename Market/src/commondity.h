#ifndef COMMONDITY_H
#define COMMONDITY_H
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "users.h"
#define MAXCMD 100
typedef struct Commodity
{
	char commodityName[25];
	char commodityid[10];
	char sendtouser[10]; // ˭����ģ�1���ϼܣ�0 �¼ܣ�userid ������
	char CreatDate[12];  // �ϼ�ʱ��
	char ByUserId[10];   // ˭��������Ʒ
	int pricce;

} COMMODITY;
extern COMMODITY cmdarr[MAXCMD];
extern int cmdcount;

void GetRandCmdId(int nums, char* str);
void WriteCmdtodocment(FILE* fp);
void GetCurrenDate(char* ch);
void CreateCommondity(FILE* fp, USER user);
void StartLoadCmd(FILE* fp);
void Printf(COMMODITY cmd);
void DisplyAllCmd(bool flog);
void DisplyTest();
void BuyCmd(USER user);
void RemoveCmd();
void LikeFindCmd(); // ģ������ֻ���δ�۳���Ʒ
int AccurateFindcmd();//��ȷ����
void FindUser();//����ĳ���û���������Ǯ
void CmdMenu();
void DeleteCmd();
void pfmenu();
void pfline();
int RandNums();

#endif // !_COMMONDITY_H

