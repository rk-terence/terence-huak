#pragma once
/*********************************************************************************
函数功能：只读取光电传感器返回值
入口参数：无
返回  值：无
***********************************************************************************/
void PEread();


/*********************************************************************************
函数功能：通过光电传感器读数分析机器人目前的运动状态，对小车运动状态进行微调：稍左、稍右、偏转
入口参数：无
返回  值：无
*********************************************************************************/
void PE_to_Modify();

/*********************************************************************************
函数功能：通过光电传感器读数分析出机器人目前状态，出现可能特殊状态时引导程序进入case 1, 包括过左、过右、十字
入口参数：无
返回  值：无
************************************************************************************/
void PE_to_Position(char crossing);


/***********************************************************************************
函数功能：读取光电传感器并记录数据队列
入口参数：short queue_pos 表示当前队员的位置,记录完毕后引导程序进入case2
返回  值：无
*************************************************************************************/
void Read_queue(short queue_pos);


/************************************************************************************
函数功能：防光电传感器误读，当 queueNumber 次读取中意外电平不超过 wrongMax 次，则认为读数正确
入口参数  short queue
返回  值：char True_Level
*************************************************************************************/
char Read_Judge(short queue);


/************************************************************************************
函数功能：获得 True_Level,并将队列清空
入口参数：无
返回  值：无
*************************************************************************************/
void GetTruelv();

/**************************************************************************
函数功能：BACK and Find
入口参数：无
返回值  ：无
*************************************************************************/
void Find_Back();