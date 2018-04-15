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


	attachInterrupt(digitalPinToInterrupt(INTER1), CALL_INTER1, FALLING);
	attachInterrupt(digitalPinToInterrupt(INTER2), CALL_INTER2, FALLING);
	attachInterrupt(digitalPinToInterrupt(INTER3), CALL_INTER3, FALLING);
	attachInterrupt(digitalPinToInterrupt(INTER4), CALL_INTER4, FALLING);
	

	//中断处理相关
	//FlexiTimer2::set(10, Flash);  // 中断设置函数，每 10ms 进入一次中断
	//FlexiTimer2::start();
}

// the loop function runs over and over again until power down or reset
void loop()
{
	move_Mode = List[0][Now_Node];
	PEread();

	//调试输出
	flag = peRead31*1000+peRead32*100+peRead33*10+peRead34;
	Serial.println(flag);
		
	crossing_flag = crossing;
	Mode_flag = move_Mode;
	Node_flag = Now_Node;
	step_flag = Now_step;

	//监视器监控调试
	Serial.println(crossing_flag);
	Serial.println(Mode_flag);
	Serial.println(Node_flag);
	Serial.println(step_flag);


	switch (move_Mode)
	{
	case X_increase:
		if (init_flag)
		{
			omni_angle = 180; omni_pwm = 250;//初始化
			OmniDirMove(omni_angle, omni_pwm);
			init_flag = 0;
		}

		//直线循迹
		PE_to_Position();
		if (omni_angle != last_angle || omni_pwm == last_pwm)
			OmniDirMove(omni_angle, omni_pwm);

		//制动急停，与下面的预先停止二选一
		if (Now_step == List[1][Now_Node])
			DMotorControl(-1, 125, -1, 125, -1, 125, -1, 125);

		//预先停止
		if (Now_step == List[1][Now_Node] - 1)
		{
			omni_pwm = 125;
		}

		//进入节点之后的处理——读取下一个指令
		if (crossing  && change_crossing && Now_step >= List[1][Now_Node])
		{
			++Now_Node;
			move_Mode = List[0][Now_Node];
			Now_step = 0;
			init_flag = 1;
			break;
		}
		break;
	case X_decrease:
		if (init_flag)
		{
			omni_angle = 0; omni_pwm = 250;//初始化
			OmniDirMove(omni_angle, omni_pwm);
			init_flag = 0;
		}

		//直线循迹
		PE_to_Position();
		if (omni_angle != last_angle || omni_pwm == last_pwm)
			OmniDirMove(omni_angle, omni_pwm);

		//制动，与下面的预先停止二选一
		if (Now_step == List[1][Now_Node])
			DMotorControl(-1, 125, -1, 125, -1, 125, -1, 125);

		//预先停止
		if (Now_step == List[1][Now_Node] - 1)
		{
			omni_pwm = 125;
		}

		//进入节点之后的处理——读取下一个指令
		if (crossing  && change_crossing && Now_step >= List[1][Now_Node])
		{
			++Now_Node;
			move_Mode = List[0][Now_Node];
			Now_step = 0;
			init_flag = 1;
			break;
		}
		break;
	case Y_increase:
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

		//制动，与下面的预先停止二选一
		if (Now_step == List[1][Now_Node])
			DMotorControl(-1, 125, -1, 125, -1, 125, -1, 125);

		//预先停止
		if (Now_step == List[1][Now_Node] - 1)
		{
			omni_pwm = 125;
		}

		//进入节点之后的处理——读取下一个指令
		if (crossing  && change_crossing && Now_step >= List[1][Now_Node])
		{
			++Now_Node;
			move_Mode = List[0][Now_Node];
			Now_step = 0;
			init_flag = 1;
			break;
		}
		break;
	case Y_decrease:
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

		//制动，与下面的预先停止二选一
		if (Now_step == List[1][Now_Node])
			DMotorControl(-1, 125, -1, 125, -1, 125, -1, 125);

		//预先停止
		if (Now_step == List[1][Now_Node] - 1)
		{
			omni_pwm = 125;
		}

		//进入节点之后的处理——读取下一个指令
		if (crossing  && change_crossing && Now_step >= List[1][Now_Node])
		{
			++Now_Node;
			move_Mode = List[0][Now_Node];
			Now_step = 0;
			init_flag = 1;
			break;
		}
		break;
	default:
		omni_pwm = 0;
		break;
	}
	
	last_angle = omni_angle;
	last_pwm = omni_pwm;
}