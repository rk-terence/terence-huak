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
	FlexiTimer2::set(10, Flash);  // 中断设置函数，每 10ms 进入一次中断
	FlexiTimer2::start();
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

		//监视器监控
		Serial.println(crossing_flag);
		Serial.println(Mode_flag);
		Serial.println(Node_flag);
		Serial.println(step_flag);


		switch (move_Mode)
		{
		case X_increase:
			Oni_angle = 180; Oni_speed = 250;
			PE_to_Position();
			if (Now_step == List[1][Now_Node] - 1)
			{
				Oni_speed = 125;
			}
			if (crossing  && change_crossing && Now_step >= List[1][Now_Node])
			{
				++Now_Node;
				move_Mode = List[0][Now_Node];
				Now_step = 0;
				break;
			}
			break;
		case X_decrease:
			Oni_angle = 0; Oni_speed = 250;
			break;
		case Y_increase:
			Oni_angle = 90; Oni_speed = 250;
			break;
		case Y_decrease:
			Oni_angle = 270; Oni_speed = 250;
			break;
		default:
			Oni_speed = 0;
			break;
		}

}
