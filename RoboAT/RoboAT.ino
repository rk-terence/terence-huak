/*
 Name:		RoboAT.ino
 Created:	2018/3/30 18:29:07
 Author:	Terence, Huak
*/
#include "all_definitions.h"
#include "Position_Velocity_Control.h"
#include "WheelControl.h"
#include "Move_Location.h"
#include "White_Black.h"

#include <FlexiTimer2.h>


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	// 设置16路光电传感器pinMode 
	pinMode(line1_pin1, INPUT);
	pinMode(line1_pin2, INPUT);
	pinMode(line1_pin3, INPUT);
	pinMode(line1_pin4, INPUT);
	pinMode(line2_pin1, INPUT);
	pinMode(line2_pin2, INPUT);
	pinMode(line2_pin3, INPUT);
	pinMode(line2_pin4, INPUT);
	pinMode(line3_pin1, INPUT);
	pinMode(line3_pin2, INPUT);
	pinMode(line3_pin3, INPUT);
	pinMode(line3_pin4, INPUT);
	pinMode(line4_pin1, INPUT);
	pinMode(line4_pin2, INPUT);
	pinMode(line4_pin3, INPUT);
	pinMode(line4_pin4, INPUT);

	/* 设置直流减速电机 */
	pinMode(MOTOR11, OUTPUT);
	pinMode(MOTOR12, OUTPUT);
	pinMode(MOTOR22, OUTPUT);
	pinMode(MOTOR22, OUTPUT);
	pinMode(MOTOR31, OUTPUT);
	pinMode(MOTOR32, OUTPUT);
	pinMode(MOTOR41, OUTPUT);
	pinMode(MOTOR42, OUTPUT);

	pinMode(MOTOR1, OUTPUT);
	pinMode(MOTOR2, OUTPUT);
	pinMode(MOTOR3, OUTPUT);
	pinMode(MOTOR4, OUTPUT);


	//attachInterrupt(digitalPinToInterrupt(INTER1), CALL_INTER1, FALLING);
	//attachInterrupt(digitalPinToInterrupt(INTER2), CALL_INTER2, FALLING);
	//attachInterrupt(digitalPinToInterrupt(INTER3), CALL_INTER3, FALLING);
	//attachInterrupt(digitalPinToInterrupt(INTER4), CALL_INTER4, FALLING);
	
	//FlexiTimer2::set(10, Flash);  // 中断设置函数，每 10ms 进入一次中断
	//FlexiTimer2::start();

	move_Mode = List[0][Now_Node];	//中断处理相关
}

// the loop function runs over and over again until power down or reset
void loop()
{
	/*
	//底层函数功能调试
	OmniDirMove(90, 250);
	delay(1000);
	DMotorControl(-1, 250, -1, 250, -1, 250, -1, 250);
	delay(1000);*/


	PEread();//读取光电传感器的值

	//监控器调试输出
	flag = peRead21*1000+peRead22*100+peRead23*10+peRead24;
	Serial.println(flag);
	//Serial.println((int)crossing);
	//Serial.println((int)move_Mode);
	//Serial.println((int)Now_Node);
	//Serial.println((int)Now_step);


	switch (move_Mode)
	{
	case X_increase:
	{
		if (init_flag)
		{
			omni_angle = 180; omni_pwm = 200;//初始化
			OmniDirMove(omni_angle, omni_pwm);
			init_flag = 0;
		}

		//直线循迹
		PE_to_Position();
		if (omni_angle != last_angle || omni_pwm == last_pwm)
			OmniDirMove(omni_angle, omni_pwm);

		//制动急停，与下面的预先停止二选一
		if (Now_step == List[1][Now_Node])
		{
			DMotorControl(-1, 250, -1, 250, -1, 250, -1, 250);
			delay(500);
		}
		////预先停止
		//if (Now_step == List[1][Now_Node] - 1)
		//{
		//	omni_pwm = 125;
		//}

		//进入节点之后的处理——读取下一个指令
		if (crossing && Now_step >= List[1][Now_Node])
		{
			Find_Back();
			++Now_Node;
			move_Mode = List[0][Now_Node];
			Now_step = 0;
			init_flag = 1;
		}
		break;
	}
	case X_decrease:
	{
		if (init_flag)
		{
			omni_angle = 0; omni_pwm = 200;//初始化
			OmniDirMove(omni_angle, omni_pwm);
			init_flag = 0;
		}

		//直线循迹
		PE_to_Position();
		if (omni_angle != last_angle || omni_pwm == last_pwm)
			OmniDirMove(omni_angle, omni_pwm);

		//制动急停，与下面的预先停止二选一
		if (Now_step == List[1][Now_Node])
		{
			DMotorControl(-1, 250, -1, 250, -1, 250, -1, 250);
			delay(500);
		}
		//预先停止
		/*if (Now_step == List[1][Now_Node] - 1)
		{
		omni_pwm = 125;
		}*/

		//进入节点之后的处理——读取下一个指令
		if (crossing && Now_step >= List[1][Now_Node])
		{
			Find_Back();
			++Now_Node;
			move_Mode = List[0][Now_Node];
			Now_step = 0;
			init_flag = 1;
		}
		break;
	}
	case Y_increase:
	{
		if (init_flag)
		{
			omni_angle = 90; omni_pwm = 250;//初始化
			OmniDirMove(omni_angle, omni_pwm);
			init_flag = 0;
		}

		//直线循迹
		PE_to_Position();
		if (omni_angle != last_angle || omni_pwm == last_pwm)
			OmniDirMove(omni_angle, omni_pwm);

		//制动急停，与下面的预先停止二选一
		if (Now_step == List[1][Now_Node])
		{
			OmniDirMove(90, 200);
			delay(500);
			DMotorControl(-1, 250, -1, 250, -1, 250, -1, 250);
			delay(500);
		}
		//预先停止
		/*if (Now_step == List[1][Now_Node] - 1)
		{
		omni_pwm = 125;
		}*/

		//进入节点之后的处理——读取下一个指令
		if (crossing && Now_step >= List[1][Now_Node])
		{
			//Find_Back();
			++Now_Node;
			move_Mode = List[0][Now_Node];
			Now_step = 0;
			init_flag = 1;

		}
		break;
	}
	case Y_decrease:
	{
		if (init_flag)
		{
			omni_angle = 270; omni_pwm = 250;//初始化
			OmniDirMove(omni_angle, omni_pwm);
			init_flag = 0;
		}
		//直线循迹
		PE_to_Position();
		if (omni_angle != last_angle || omni_pwm == last_pwm)
			OmniDirMove(omni_angle, omni_pwm);

		//制动急停，与下面的预先停止二选一
		if (Now_step == List[1][Now_Node])
		{
			OmniDirMove(270, 200);
			delay(500);
			DMotorControl(-1, 250, -1, 250, -1, 250, -1, 250);
			delay(500);
		}
		//预先停止
		/*if (Now_step == List[1][Now_Node] - 1)
		{
		omni_pwm = 125;
		}*/

		//进入节点之后的处理——读取下一个指令
		if (crossing && Now_step >= List[1][Now_Node])
		{
			//Find_Back();
			++Now_Node;
			move_Mode = List[0][Now_Node];
			Now_step = 0;
			init_flag = 1;
		}
		break;
	}
	default:
		omni_pwm = 0;
		break;
	}
	
	last_angle = omni_angle;
	last_pwm = omni_pwm;
	delay(50);
}