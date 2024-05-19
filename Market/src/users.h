#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

#define MAXUser 100

typedef struct USER
{
    char UserName[20];
    char PassWorld[20];
    char Address[40];
    char UserId[12];
    int Iphone;
    int Money;
    int flog;

} USER;
//ȫ�ֱ�����ô����
extern USER UserArr[MAXUser];
extern USER CurrentUser;
extern int UserNumsCnt;
void MainMenu();
bool Login();
void RegisterUser(FILE* fp);
void WriteUserToDocument(FILE* fp);
void PrintfUserData();
void StartLoadData(FILE* fpt);
void UpdateUser(USER user);
void SetUser(USER user);
void MenuUser();
void FindUserAndToMoney(char* userid,int money);//����ĳ���û���������Ǯ
int Unregister(USER user);
int GetRandNums();
void GetRandUserID(int nums, char* str);
void LoginMain();
void BuyUser();
void SellUser();

#endif 