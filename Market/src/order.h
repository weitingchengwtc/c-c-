#ifndef ORDER_H
#define ORDER_H
#include "commondity.h"
#include "users.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ORDER 200

typedef struct Order
{
    char cmdname[10]; //==cmd名字
    char orderid[10];
    char selluserid[10]; // 卖家ID 买家自己查看自己购买的商品
    char buyuserID[10];  // 买家ID 用以区分订单所属
    char dreatedate[10];
    int prince;

} ORDER;
extern int ordercount;
extern ORDER orderarr[MAX_ORDER];

//直接用comd的日期生成器就行了
//void GetCurrenDate(char* ch);
//int CreateRandNums();

void CreateOdrer(int monery, COMMODITY currentcmd);
void GetOrderId(int nums, char* str);
void WriterOrderToDmt(FILE*fp);
void StartLoading(FILE* fp);
void BuyuserFindOrder();
void SelluserFindOrder();
void pfoder(ORDER order);
#endif // !ORDER_H

