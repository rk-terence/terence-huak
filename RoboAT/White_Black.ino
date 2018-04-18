#include "all_definitions.h"
/*2018.4.17增加内容：
	增加函数，判断一列（4个）光电传感器是否值都相等。
	完全改变了逻辑。期待可以奏效。目前只改变了Y_decrease的逻辑。
	Swirl的pwm改为200
*/
/*2018.4.18增加内容：
	把X_increase 的方向调整改为200pwm，角度改为正常。*/


/*********************************************************************************
函数功能：只读取光电传感器返回值
入口参数：无
返回  值：无
***********************************************************************************/
void PEread()
{
	peRead11 = digitalRead(line1_pin1);
	peRead12 = digitalRead(line1_pin2);
	peRead13 = digitalRead(line1_pin3);
	peRead14 = digitalRead(line1_pin4);
	peRead21 = digitalRead(line1_pin1);
	peRead22 = digitalRead(line2_pin2);
	peRead23 = digitalRead(line2_pin3);
	peRead24 = digitalRead(line2_pin4);
	peRead31 = digitalRead(line3_pin1);
	peRead32 = digitalRead(line3_pin2);
	peRead33 = digitalRead(line3_pin3);
	peRead34 = digitalRead(line3_pin4);
	peRead41 = digitalRead(line4_pin1);
	peRead42 = digitalRead(line4_pin2);
	peRead43 = digitalRead(line4_pin3);
	peRead44 = digitalRead(line4_pin4);
	return;
}

/*********************************************************************************
函数功能：判断读取的光电传感器的值是否相等
入口参数：某一个传感器线列
返回  值：布尔
***********************************************************************************/
short IsSensorEqual(short line)
{
	switch (line)
	{
	case 1:
		if (peRead11 == peRead12)
			if (peRead11 == peRead13)
				if (peRead11 == peRead14)
					return 1;
		break;
	case 2:
		if (peRead21 == peRead22)
			if (peRead21 == peRead23)
				if (peRead21 == peRead24)
					return 1;
		break;
	case 3:
		if (peRead31 == peRead32)
			if (peRead31 == peRead33)
				if (peRead31 == peRead34)
					return 1;
		break;
	case 4:
		if (peRead41 == peRead12)
			if (peRead41 == peRead43)
				if (peRead41 == peRead44)
					return 1;
		break;
	}
	return 0;
}

/*********************************************************************************
函数功能：通过光电传感器读数分析机器人目前的运动状态，对小车运动状态进行微调：稍左、稍右、偏转
入口参数：无
返回  值：无
*********************************************************************************/
void PE_to_Modify()
{
	switch (move_Mode)
	{
		case X_increase:
		{
			break;
		}
		case X_decrease:
		{
			break;
		}
		case Y_increase:
		{
			break;
		}
		case Y_decrease:
		{
			break;
		}
	}
	return;
	
}

/*********************************************************************************
函数功能：通过光电传感器读数分析出机器人目前状态，出现可能特殊状态时引导程序进入case 1, 包括过左、过右、十字
入口参数：无
返回  值：无
备注:	传感器返回的值, 黑色返回1, 白色返回0
版本:
	2.0: 利用line3和line4的逻辑来判断是否直走, 具体是差分. 具体效果待观察, 应该不会出现问题. 目前存在的问题是
		Y_decrease无法走直线, 以及X_increase走得不够直.
	2.1: 优化了代码(删除冗余). 方便读代码.
	2.2: 改变X判断进入节点的逻辑, 改变Y判断进入节点的逻辑.
	2.3: 待加入新的Y方向判断逻辑, 使其更完善.
		未来方向(2.4): 考虑到X方向寻线也不是太好, 所以准备把X方向的寻线逻辑升级一下.准备使用line3和line4.
	2.4: 见2.3.
************************************************************************************/
void PE_to_Position()
{
	if (!crossing)
	{
		switch (move_Mode)
		{
		case X_increase:
		{
		//继续直走(车身正)
		if (!peRead32 && !peRead42 && !peRead33 && !peRead43 \
			|| !peRead32 && !peRead42 && peRead33 && peRead43|| !peRead33 && !peRead43 && peRead32 &&peRead42)
			//中间4个全白或者一边白一边黑.
		{
			omni_angle = 180;
		}
		else if (peRead32 && peRead42 && peRead33 && peRead43)//如果全黑的话
		{
			if (!peRead41 && !peRead31)
			{
				omni_angle = 225;
				omni_pwm = 200;
			}
			else if (!peRead44 && !peRead34)
			{
				omni_angle = 315;
				omni_pwm = 200;
			}
			//如果没有发生上述情形, 就继续上一个指令. 这里就不写else了
		}
		//需要左纠偏
		else if (peRead31 + peRead32 + peRead41 + peRead42 > peRead33 + peRead34 + peRead43 + peRead44)
		{
			omni_angle = 225;
			omni_pwm = 200;
		}
		//需要右偏
		else if (peRead31 + peRead32 + peRead41 + peRead42 < peRead33 + peRead34 + peRead43 + peRead44)
		{
			omni_angle = 135;
			omni_pwm = 200;
		}

		//假如遇到了十字路口
		if (peRead31 + peRead32 + peRead33 + peRead34 < 2 || peRead41 + peRead42 + peRead43 + peRead44 < 2)//原判断条件: !peRead31 && !peRead32 && !peRead33 && !peRead34
		{
			crossing = 1;
			Now_step++;
		}
		/*else
		{
			omni_angle = 180;
			omni_pwm = 250;
		}*/

		break;
		}
		case X_decrease:
		{
			break;
		}
		case Y_increase:
		{
			break;
		}
		case Y_decrease:
		{
		//继续前进
		if (peRead31 + peRead32 + peRead33 + peRead34 == 4 && peRead41 + peRead42 + peRead43 + peRead44 == 0 \
			|| peRead31 + peRead32 + peRead33 + peRead34 == 0 && peRead41 + peRead42 + peRead43 + peRead44 == 4)//一边黑一边白
		{
			omni_angle = 270;
		}
		//如果出现全黑，分情况讨论
		else if (peRead31 + peRead32 + peRead33 + peRead34 == 4 && peRead41 + peRead42 + peRead43 + peRead44 == 4)//全黑
		{
			if (peRead22 && peRead23)//两个全黑，则直走
				omni_angle = 270;
			else if (peRead22 && !peRead23)//一黑一白
			{
				omni_angle = 0;
				omni_pwm = 200;
			}
			else if (!peRead22 && peRead23)//一黑一白，与上面相反
			{
				omni_angle = 180;
				omni_pwm = 200;
			}
			else//如果全白，无法判断，继续直走
				omni_angle = 270;
		}
		//如果小车不正
		else if (!IsSensorEqual(4) || !IsSensorEqual(3))
		{
			if (peRead44)
				Swirl(2);
			if (peRead34)
				Swirl(1);
		}
		
		//如果进入节点
		if (!peRead32 && !peRead42 || !peRead33 && !peRead43)//原判断条件: !peRead32 && !peRead42
		{
			Now_step++;
			crossing = 1;
		}
		/*else
		{
			omni_angle = 270;
			omni_pwm = 250;
		}*/
		break;
		}
		default:
			omni_pwm = 0;
			break;
		}
	}
	else//crossing == 1
	{
		switch (move_Mode)
		{
		case X_increase:
		{
			if (peRead31 + peRead32 + peRead33 + peRead34 >= 2 && peRead41 + peRead42 + peRead43 + peRead44 >= 2)//当大于两个是黑的时候代表出了crossing.
			{
				crossing = 0;
			}
			break;
		}
		case X_decrease:
		{
			break;
		}
		case Y_increase:
		{
			break;
		}
		case Y_decrease:
		{
			if (peRead32 || peRead42)
			{
				crossing = 0;
			}
			break; 
		}
		default:
			omni_pwm = 0;
			break;
		}
	}
}

/***********************************************************************************
函数功能：读取光电传感器并记录数据队列
入口参数：short queue_pos 表示当前队员的位置,记录完毕后引导程序进入case2
返回  值：无
*************************************************************************************/
void Read_queue(short queue_pos)
{
	if (queue_pos < queueNumber)
	{
		queue11 += peRead11;
		queue12 += peRead12;
		queue13 += peRead13;
		queue14 += peRead14;
		queue21 += peRead21;
		queue22 += peRead22;
		queue23 += peRead23;
		queue24 += peRead24;
		queue31 += peRead31;
		queue32 += peRead32;
		queue33 += peRead33;
		queue34 += peRead34;
		queue41 += peRead41;
		queue42 += peRead42;
		queue43 += peRead43;
		queue44 += peRead44;
	}
	return;

}

/************************************************************************************
函数功能：防光电传感器误读，当 queueNumber 次读取中意外电平不超过 wrongMax 次，则认为读数正确
入口参数  short queue
返回  值：char True_Level
*************************************************************************************/
char Read_Judge(short queue)
{
	if (queue > queueNumber / 2)
	{
		if (queueNumber - queue <= wrongMax) return 1;
		else return 0;
	}
	else
	{
		if (queue <= wrongMax) return 0;
		else return 1;
	}
}

/************************************************************************************
函数功能：获得 True_Level,并将队列清空
入口参数：无
返回  值：无
*************************************************************************************/
void GetTruelv()
{
	val_11 = Read_Judge(queue11);
	val_12 = Read_Judge(queue12);
	val_13 = Read_Judge(queue13);
	val_14 = Read_Judge(queue14);
	val_21 = Read_Judge(queue21);
	val_22 = Read_Judge(queue22);
	val_23 = Read_Judge(queue23);
	val_24 = Read_Judge(queue24);
	val_31 = Read_Judge(queue31);
	val_32 = Read_Judge(queue32);
	val_33 = Read_Judge(queue33);
	val_34 = Read_Judge(queue34);
	val_41 = Read_Judge(queue41);
	val_42 = Read_Judge(queue42);
	val_43 = Read_Judge(queue43);
	val_44 = Read_Judge(queue44);
	queue11 = 0;
	queue12 = 0;
	queue13 = 0;
	queue14 = 0;
	queue21 = 0;
	queue22 = 0;
	queue23 = 0;
	queue24 = 0;
	queue31 = 0;
	queue32 = 0;
	queue33 = 0;
	queue34 = 0;
	queue41 = 0;
	queue42 = 0;
	queue43 = 0;
	queue44 = 0;

	return;

}