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
	char sendtouser[10]; // 谁购买的，1，上架，0 下架，userid 被购买
	char CreatDate[12];  // 上架时间
	char ByUserId[10];   // 谁发布的商品
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
void LikeFindCmd(); // 模糊查找只针对未售出商品
int AccurateFindcmd();//精确查找
void FindUser();//查找某个用户，给他打钱
void CmdMenu();
void DeleteCmd();
void pfmenu();
void pfline();
int RandNums();

#endif // !_COMMONDITY_H

