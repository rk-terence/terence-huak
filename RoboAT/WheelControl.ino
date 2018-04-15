#include"WheelControl.h"
#include<math.h>

/***************************************************************************************************************
函数功能：机器人底层函数，主要实现机器人八个方向运动及自转
入口参数：机器人运动极坐标角度 int angle, 机器人运动速度与全速运动250之比 float speed
返回  值：机器人运动状态 int status
****************************************************************************************************************/

int OmniDirMove(short angle, short pwm)
{
	//static int oldangle = -1, oldspeed = -1;
	int status = 1;

	/*//this can save time and might avoid unnecessary errors if new instructions are the same as the old ones.
	if (oldangle == angle && oldspeed == speed)
	return;*/

	//to preprocess the input parameters...
	if (angle >= 360 || angle < 0)
	{
		if (angle >= 360)
			while (angle >= 360)
				angle -= 360;
		if (angle < 0)
			while (angle < 0)
				angle += 360;
	}
	if (pwm < 0)
		pwm = 200;
	else if (pwm > 250)
		pwm = 250;

	//to divide the real situation into 8 categories, and each branch corresponds with an specific algorithm.
	if (angle >= 0 && angle < 45)
		status = 1;
	else if (angle >= 45 && angle < 90)
		status = 2;
	else if (angle >= 90 && angle < 135)
		status = 3;
	else if (angle >= 135 && angle < 180)
		status = 4;
	else if (angle >= 180 && angle < 225)
		status = 5;
	else if (angle >= 225 && angle < 270)
		status = 6;
	else if (angle >= 270 && angle < 315)
		status = 7;
	else
		status = 8;

	/*//MOTORable L298N output and set the initial speed
	analogWrite(MOTOR1, 0);
	analogWrite(MOTOR2, 0);
	analogWrite(MOTOR3, 0);
	analogWrite(MOTOR4, 0);*/

	/*Serial.println(status);
	Serial.println(digitalRead(MOTOR31));
	Serial.println(digitalRead(MOTOR32));
	Serial.println(analogRead(MOTOR3));
	Serial.println(digitalRead(MOTOR41));
	Serial.println(digitalRead(MOTOR42));
	Serial.println(analogRead(MOTOR4));*/

	//process the differMOTORt categories.
	//NOTE: to make these codes function and avoid chaos, every MOTOR should be connected in the same way.
	switch (status)
	{
	case 1:
		analogWrite(MOTOR1, pwm); analogWrite(MOTOR2, pwm); analogWrite(MOTOR3, pwm * tan((45 - angle) / 180.0 * PI)); analogWrite(MOTOR4, pwm * tan((45 - angle) / 180.0 * PI));
		digitalWrite(MOTOR11, HIGH); digitalWrite(MOTOR12, LOW); digitalWrite(MOTOR21, LOW); digitalWrite(MOTOR22, HIGH); digitalWrite(MOTOR31, HIGH); digitalWrite(MOTOR32, LOW); digitalWrite(MOTOR41, LOW); digitalWrite(MOTOR42, HIGH);
		break;
	case 2:
		analogWrite(MOTOR1, pwm); analogWrite(MOTOR2, pwm); analogWrite(MOTOR3, pwm * tan((angle - 45) / 180.0 * PI)); analogWrite(MOTOR4, pwm * tan((angle - 45) / 180.0 * PI));
		digitalWrite(MOTOR11, HIGH); digitalWrite(MOTOR12, LOW); digitalWrite(MOTOR21, LOW); digitalWrite(MOTOR22, HIGH); digitalWrite(MOTOR31, LOW); digitalWrite(MOTOR32, HIGH); digitalWrite(MOTOR41, HIGH); digitalWrite(MOTOR42, LOW);
		break;
	case 3:
		analogWrite(MOTOR1, pwm * tan((135 - angle) / 180.0 * PI)); analogWrite(MOTOR2, pwm * tan((135 - angle) / 180.0 * PI)); analogWrite(MOTOR3, pwm); analogWrite(MOTOR4, pwm);
		digitalWrite(MOTOR11, HIGH); digitalWrite(MOTOR12, LOW); digitalWrite(MOTOR21, LOW); digitalWrite(MOTOR22, HIGH); digitalWrite(MOTOR31, LOW); digitalWrite(MOTOR32, HIGH); digitalWrite(MOTOR41, HIGH); digitalWrite(MOTOR42, LOW);
		break;
	case 4:
		analogWrite(MOTOR1, pwm * tan((angle - 135) / 180.0 * PI)); analogWrite(MOTOR2, pwm * tan((angle - 135) / 180.0 * PI)); analogWrite(MOTOR3, pwm); analogWrite(MOTOR4, pwm);
		digitalWrite(MOTOR11, LOW); digitalWrite(MOTOR12, HIGH); digitalWrite(MOTOR21, HIGH); digitalWrite(MOTOR22, LOW); digitalWrite(MOTOR31, LOW); digitalWrite(MOTOR32, HIGH); digitalWrite(MOTOR41, HIGH); digitalWrite(MOTOR42, LOW);
		break;
	case 5:
		analogWrite(MOTOR1, pwm); analogWrite(MOTOR2, pwm); analogWrite(MOTOR3, pwm * tan((225 - angle) / 180.0 * PI)); analogWrite(MOTOR4, pwm * tan((225 - angle) / 180.0 * PI));
		digitalWrite(MOTOR11, LOW); digitalWrite(MOTOR12, HIGH); digitalWrite(MOTOR21, HIGH); digitalWrite(MOTOR22, LOW); digitalWrite(MOTOR31, LOW); digitalWrite(MOTOR32, HIGH); digitalWrite(MOTOR41, HIGH); digitalWrite(MOTOR42, LOW);
		break;
	case 6:
		analogWrite(MOTOR1, pwm); analogWrite(MOTOR2, pwm); analogWrite(MOTOR3, pwm * tan((angle - 225) / 180.0 * PI)); analogWrite(MOTOR4, pwm * tan((angle - 225) / 180.0 * PI));
		digitalWrite(MOTOR11, LOW); digitalWrite(MOTOR12, HIGH); digitalWrite(MOTOR21, HIGH); digitalWrite(MOTOR22, LOW); digitalWrite(MOTOR31, HIGH); digitalWrite(MOTOR32, LOW); digitalWrite(MOTOR41, LOW); digitalWrite(MOTOR42, HIGH);
		break;
	case 7:
		analogWrite(MOTOR1, pwm * tan((315 - angle) / 180.0 * PI)); analogWrite(MOTOR2, pwm * tan((315 - angle) / 180.0 * PI)); analogWrite(MOTOR3, pwm); analogWrite(MOTOR4, pwm);
		digitalWrite(MOTOR11, LOW); digitalWrite(MOTOR12, HIGH); digitalWrite(MOTOR21, HIGH); digitalWrite(MOTOR22, LOW); digitalWrite(MOTOR31, HIGH); digitalWrite(MOTOR32, LOW); digitalWrite(MOTOR41, LOW); digitalWrite(MOTOR42, HIGH);
		break;
	case 8:
		analogWrite(MOTOR1, pwm * tan((angle - 315) / 180.0 * PI)); analogWrite(MOTOR2, pwm * tan((angle - 315) / 180.0 * PI)); analogWrite(MOTOR3, pwm); analogWrite(MOTOR4, pwm);
		digitalWrite(MOTOR11, HIGH); digitalWrite(MOTOR12, LOW); digitalWrite(MOTOR21, LOW); digitalWrite(MOTOR22, HIGH); digitalWrite(MOTOR31, HIGH); digitalWrite(MOTOR32, LOW); digitalWrite(MOTOR41, LOW); digitalWrite(MOTOR42, HIGH);
		break;
	}


	/*//Change the parameters.
	oldspeed = speed;
	oldangle = angle;*/

	//PID控制部分


	return status;
}

//Counter clockwise: 1,  Clockwise: 2
void Swirl(int choice)
{
	switch (choice)
	{
	case 1:
		analogWrite(MOTOR1, 250); analogWrite(MOTOR2, 250); analogWrite(MOTOR3, 250); analogWrite(MOTOR4, 250);
		digitalWrite(MOTOR11, LOW); digitalWrite(MOTOR12, HIGH); digitalWrite(MOTOR21, LOW); digitalWrite(MOTOR22, HIGH); digitalWrite(MOTOR31, LOW); digitalWrite(MOTOR32, HIGH); digitalWrite(MOTOR41, LOW); digitalWrite(MOTOR42, HIGH);
		break;
	case 2:
		analogWrite(MOTOR1, 250); analogWrite(MOTOR2, 250); analogWrite(MOTOR3, 250); analogWrite(MOTOR4, 250);
		digitalWrite(MOTOR11, HIGH); digitalWrite(MOTOR12, LOW); digitalWrite(MOTOR21, HIGH); digitalWrite(MOTOR22, LOW); digitalWrite(MOTOR31, HIGH); digitalWrite(MOTOR32, LOW); digitalWrite(MOTOR41, HIGH); digitalWrite(MOTOR42, LOW);
		break;
	default: break;
	}
}


void DMotorControl(char status1, unsigned char pwm1, char status2, unsigned char pwm2, char status3, unsigned char pwm3, char status4, unsigned char pwm4)
{
	analogWrite(MOTOR1, pwm1);
	analogWrite(MOTOR2, pwm2);
	analogWrite(MOTOR3, pwm3);
	analogWrite(MOTOR4, pwm4);

	digitalWrite(MOTOR11, status1); digitalWrite(MOTOR12, status1 - 1);
	digitalWrite(MOTOR21, status2 - 1); digitalWrite(MOTOR12, status2);
	digitalWrite(MOTOR31, status3 - 1); digitalWrite(MOTOR12, status3);
	digitalWrite(MOTOR41, status4); digitalWrite(MOTOR12, status4 - 1);
}