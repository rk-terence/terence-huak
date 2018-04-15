#include "all_definitions.h"
#include"Move_Location.h"
/**********************************************************************************
函数功能：判断目前处于的步数(节点)，转弯/继续前进
入口参数：无
返回  值：无
***********************************************************************************/
void Change_Step()
{
	++Now_step;
	if (Now_step >= List[1][Now_Node])
	{
		Now_step = 0;
		++Now_Node;
		move_Mode = List[0][Now_Node];
	}
	if (Now_Node >= List_Node1)
	{
		move_Mode = 9; //default stop
	}
	PEread_flag = OnlyRead;
	return;
}

char On_the_List(char crossing)
{

	/************************************************************************************
	函数功能：根据16路传感器信息确定机器人所处路线信息
	入口参数：无
	返回  值：无
	key_flag作为初步检测结果，crossing储存最终结果
	*************************************************************************************/
	if (!crossing)
	{
		switch (move_Mode)
		{
		case X_increase:
		{
			if (!val_31 && !val_32 && !val_33 && !val_34)
			{
				crossing = 1;
				Change_Step();
			}
		}
		break;
		case X_decrease:
		{
			if (!val_41 && !val_42 && !val_43 && !val_44)
			{
				crossing = 1;
				Change_Step();
				key_flag = 0;
			}
			break;
		}

		case Y_increase:
			break;
		case Y_decrease:
		{
			//crossing
			if (key_flag == 0 && (!val_11 && !val_12 && !val_13 && !val_14))
			{
				break;
			}
			if (key_flag && (!val_32 && !val_42))
			{
				Change_Step();
			}
			//runaway
			break;
		}
		}
	}

	/*************************************************************************************
	函数功能：机器人移出十字，清除标志位crossing
	入口参数：无
	返回  值：无
	***************************************************************************************/
	else
	{
		switch (move_Mode)
		{
		case X_increase:
		{
			if (val_31 || val_34)
			{
				crossing = 0;
			}
			break;
		}
		case X_decrease:
		{
			if (val_41 || val_44)
			{
				crossing = 0;
			}
			break;
		}
		case Y_increase:
		{
			if (val_32 || val_42)
			{
				crossing = 0;
			}
			break;
		}
		case Y_decrease:
		{
			if (val_32 || val_42)
			{
				crossing = 0;
			}
			break;
		}
		}
		
	}
	return crossing;
}

