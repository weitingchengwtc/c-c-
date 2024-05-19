#define _CRT_SECURE_NO_WARNINGS
#include"order.h"
#include"commondity.h"
#include <iostream>

using namespace std;
int ordercount = 0;
ORDER orderarr[MAX_ORDER];
void GetOrderId(int nums, char* str)
{
	char ch[20];
	sprintf(ch, "D%d", nums);
	strcpy(str, ch);
}
void WriterOrderToDmt(FILE* fp)
{
	for (int i = 0; i < ordercount; i++)
	{
		/*if (strcmp(cmdarr[i].ByUserId, "-1") == 0)
		{
			continue;
		}*/

		fprintf(fp, "%s %s %d %s %s %s\n", orderarr[i].cmdname, orderarr[i].orderid, orderarr[i].prince
			, orderarr[i].dreatedate, orderarr[i].buyuserID, orderarr[i].selluserid);
	}
}
void StartLoading(FILE* fp)
{
	ordercount = 0;
	ORDER order;
	while (fscanf(fp, "%s %s %d %s %s %s\n", order.cmdname, order.orderid, &order.prince
		, order.dreatedate, order.buyuserID, order.selluserid) != EOF)
	{
		// printf("%-10s %7s %4.2d %s\n", commondity.commodityName, commondity.commodityid, commondity.pricce, commondity.CreatDate);
		orderarr[ordercount++] = order;
		/*cout << order.cmdname << " " << order.orderid << " " << order.prince<<" "
			<< order.dreatedate << " " << order.buyuserID << " " << order.selluserid << endl;*/
	}
}
//想办法封装成函数方便点
void BuyuserFindOrder()
{
	printf(" 名称    编号  价格   创建日期    买家    卖家   \n");
	for (int i = 0; i < ordercount; i++)
	{
		if (strcmp(CurrentUser.UserId, orderarr[i].buyuserID) == 0)
		{
			pfoder(orderarr[i]);
		}
	}
	printf("====================================================================\n");

}
void SelluserFindOrder()
{
	for (int i = 0; i < ordercount; i++)
	{
		if (strcmp(CurrentUser.UserId, orderarr[i].selluserid) == 0)
		{
			pfoder(orderarr[i]);
		}
	}
}
void pfoder(ORDER order)
{
	cout << order.cmdname << " " << order.orderid << " " << order.prince
		<< order.dreatedate << " " << order.buyuserID << " " << order.selluserid << endl;
}
void CreateOdrer(int monery, COMMODITY currentcmd)
{
	ORDER order;
	strcpy(order.cmdname, currentcmd.commodityName);
	strcpy(order.selluserid, currentcmd.ByUserId);
	strcpy(order.buyuserID, CurrentUser.UserId);
	GetOrderId(RandNums(), order.orderid);
	order.prince = currentcmd.pricce;
	GetCurrenDate(order.dreatedate);
	orderarr[ordercount++] = order;
	
}
