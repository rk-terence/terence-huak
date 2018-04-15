/*
Name:		Position_Volecity_Control.ino
Created:	2018/3/24 18:15:12
Author:	HUAK
*/
#include"Position_Velocity_Control.h"
//定义四个中断计数函数
void CALL_INTER1() { INTER1_CNT++; }
void CALL_INTER2() { INTER2_CNT++; }
void CALL_INTER3() { INTER3_CNT++; }
void CALL_INTER4() { INTER4_CNT++; }

/*************************************************************************
函数功能：计算当前位置距离目标位置的距离
入口参数：当前位置格数，目标位置格数
返回  值：Target_Position (以脉冲数表示)
计算公式：（目标格点坐标-源格点坐标）* 两白线中点距离 / 轮周长 * 一圈脉冲数 / 1.41
*************************************************************************/
unsigned int Distance(char Grid)
{
	unsigned int Target_Position;
	Target_Position = (int)Grid * 400 / 188 * 390 ;
	//Target_Position = Grid * 295 / 188 * 390;// 测试用，宿舍
}


/*************************************************************************
函数功能：限制PWM赋值
入口参数：Moto
返回  值：void
**************************************************************************/
void Xianfu_Pwm()
{
	int Amplitude = 250;   //PWM满幅255,控制在250左右
	if (PWM_MOTOR1 < 0) PWM_MOTOR1 = 0;
	if (PWM_MOTOR1 > Amplitude)  PWM_MOTOR1 = Amplitude;
	if (PWM_MOTOR2 < 0) PWM_MOTOR2 = 0;
	if (PWM_MOTOR2 > Amplitude)  PWM_MOTOR2 = Amplitude;
	if (PWM_MOTOR3 < 0) PWM_MOTOR3 = 0;
	if (PWM_MOTOR3 > Amplitude)  PWM_MOTOR3 = Amplitude;
	if (PWM_MOTOR4 < 0) PWM_MOTOR4 = 0;
	if (PWM_MOTOR4 > Amplitude)  PWM_MOTOR4 = Amplitude;
}

/**************************************************************
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
***************************************************************/
int myabs(int a)
{
	int temp;
	if (a < 0) temp = -a;
	else temp = a;
	return temp;
}

/****************************************************************
函数功能：速度PID控制器
入口参数：编码器的速度测量值和速度控制的目标值
返回  值：电机PWM
根据速度式离散PID公式
pwm=Kp*e(k)+Ki*∑e(k)+Kd[e（k）-e(k-1)]
e(k)代表本次偏差
e(k-1)代表上一次的偏差
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,,k;
pwm代表输出
*****************************************************************/
int Velocity1_PI(int Encoder, int Target)
{
	static char Last_Mode;
	float Kp = 35, Ki = 3.5, Kd = 0;      //PID参数由电机的种类和负载决定
	static int Bias, Pwm, Last_bias;
	if (Last_Mode != move_Mode)
	{
		Last_bias = 0;
		Pwm = 0;
	}
	Bias = Encoder - Target;               //计算偏差
	Pwm += Kp * (Bias - Last_bias)  + Ki * Bias ;//增量式PI控制器
	Last_bias = Bias;
	Last_Mode = move_Mode;
	return Pwm;
}
int Velocity2_PI(int Encoder, int Target)
{
	static char Last_Mode;
	float Kp = 35, Ki = 3.5, Kd = 0;      //PID参数由电机的种类和负载决定
	static int Bias, Pwm, Last_bias;
	if (Last_Mode != move_Mode)
	{
		Last_bias = 0;
		Pwm = 0;
	}
	Bias = Encoder - Target;               //计算偏差
	Pwm += Kp * (Bias - Last_bias)  + Ki * Bias ;//增量式PI控制器
	Last_bias = Bias;
	Last_Mode = move_Mode;
	return Pwm;
}
int Velocity3_PI(int Encoder, int Target)
{
	static char Last_Mode;
	float Kp = 35, Ki = 3.5, Kd = 0;      //PID参数由电机的种类和负载决定
	static int Bias, Pwm, Last_bias;
	if (Last_Mode != move_Mode)
	{
		Last_bias = 0;
		Pwm = 0;
	}
	Bias = Encoder - Target;               //计算偏差
	Pwm += Kp * (Bias - Last_bias)  + Ki * Bias ;//增量式PI控制器
	Last_bias = Bias;
	Last_Mode = move_Mode;
	return Pwm;
}
int Velocity4_PI(int Encoder, int Target)
{
	static char Last_Mode;
	float Kp = 35, Ki = 3.5, Kd = 0;      //PID参数由电机的种类和负载决定
	static int Bias, Pwm, Last_bias;
	if (Last_Mode != move_Mode)
	{
		Last_bias = 0;
		Pwm = 0;
	}
	Bias = Encoder - Target;               //计算偏差
	Pwm += Kp * (Bias - Last_bias)  + Ki * Bias ;//增量式PI控制器
	Last_bias = Bias;
	Last_Mode = move_Mode;
	return Pwm;
}

/****************************************************************
函数功能：位置PID控制器
入口参数：编码器的速度测量值和速度控制的目标值
返回  值：电机PWM
根据位置式离散PID公式
pwm=Kp*e(k)+Ki*∑e(k)+Kd[e（k）-e(k-1)]
e(k)代表本次偏差
e(k-1)代表上一次的偏差
∑e(k)代表e(k)以及之前的偏差的累积和;其中k为1,2,,k;
pwm代表输出
*****************************************************************/
int Position1_PI(int Encoder, int Target)
{
	static char Last_Mode;
	float Kp = 5.2, Ki = 0.01, Kd = 0;       //PID参数由电机的种类和负载决定
	static float Bias, Pwm, Integral_bias = 0;
	if (Last_Mode != move_Mode)
	{
		Integral_bias += Bias;//运动状态改变，速度积分（表征位置）清空
		Pwm = 0;              //位置式PI控制器清空
	}
	Bias = Encoder - Target;  //计算偏差
	Integral_bias += Bias;                 //求出偏差的积分，表征位置
	Pwm = Kp * Bias + Ki * Integral_bias;     //位置式PI控制器
	Last_Mode = move_Mode;

	Serial.println("Position_MOTOR1: ");
	Serial.println("Encoder: "); Serial.println(Encoder);
	Serial.println("Bias:"); Serial.println(Bias);
	Serial.println("Integral_bias:"); Serial.println(Integral_bias);
	Serial.println("PWM:"); Serial.println(Pwm);

	return Pwm;
}
int Position2_PI(int Encoder, int Target)
{
	static char Last_Mode;
	float Kp = 5.2, Ki = 0.01, Kd = 0;       //PID参数由电机的种类和负载决定
	static float Bias, Pwm, Integral_bias = 0;
	if (Last_Mode != move_Mode)
	{
		Integral_bias += Bias;//运动状态改变，速度积分（表征位置）清空
		Pwm = 0;              //位置式PI控制器清空
	}
	Bias = Encoder - Target;  //计算偏差
	Integral_bias += Bias;                 //求出偏差的积分，表征位置
	Pwm = Kp * Bias + Ki * Integral_bias;     //位置式PI控制器
	Last_Mode = move_Mode;
	
	Serial.println("Position_MOTOR2: ");
	Serial.println("Encoder: "); Serial.println(Encoder);
	Serial.println("Bias:"); Serial.println(Bias);
	Serial.println("Integral_bias:"); Serial.println(Integral_bias);
	Serial.println("PWM:"); Serial.println(Pwm);
	
	return Pwm;
}
int Position3_PI(int Encoder, int Target)
{
	static char Last_Mode;
	float Kp = 5.2, Ki = 0.01, Kd = 0;       //PID参数由电机的种类和负载决定
	static float Bias, Pwm, Integral_bias = 0;
	if (Last_Mode != move_Mode)
	{
		Integral_bias += Bias;//运动状态改变，速度积分（表征位置）清空
		Pwm = 0;              //位置式PI控制器清空
	}
	Bias = Encoder - Target;  //计算偏差
	Integral_bias += Bias;                 //求出偏差的积分，表征位置
	Pwm = Kp * Bias + Ki * Integral_bias;     //位置式PI控制器

	Last_Mode = move_Mode;

	Serial.println("Position_MOTOR3: ");
	Serial.println("Encoder: "); Serial.println(Encoder);
	Serial.println("Bias:"); Serial.println(Bias);
	Serial.println("Integral_bias:"); Serial.println(Integral_bias);
	Serial.println("PWM:"); Serial.println(Pwm);

	return Pwm;
}
int Position4_PI(int Encoder, int Target)
{
	static char Last_Mode;
	float Kp = 5.2, Ki = 0.01, Kd = 0;       //PID参数由电机的种类和负载决定
	static float Bias, Pwm, Integral_bias = 0;
	if (Last_Mode != move_Mode)
	{
		Integral_bias += Bias;//运动状态改变，速度积分（表征位置）清空
		Pwm = 0;              //位置式PI控制器清空
	}
	Bias = Encoder - Target;  //计算偏差
	Integral_bias += Bias;                 //求出偏差的积分，表征位置
	Pwm = Kp * Bias + Ki * Integral_bias;     //位置式PI控制器
	Last_Mode = move_Mode;

	Serial.println("Position_MOTOR4: ");
	Serial.println("Encoder: "); Serial.println(Encoder);
	Serial.println("Bias:"); Serial.println(Bias);
	Serial.println("Integral_bias:"); Serial.println(Integral_bias);
	Serial.println("PWM:"); Serial.println(Pwm);
	
	return Pwm;
}
char delta_Position(int Position1,int Position2, int Position3, int Position4, int Target_Position)
{
	const int delta = 10;
	if (myabs(Position1 - Target_Position) < delta && myabs(Position4 - Target_Position)<delta && myabs(Position3 - Target_Position) && myabs(Position4-Target_Position)<delta)
		return 1;
	else
		return 0;
}
/******************************************************************
函数功能：速度位置PID控制器双环嵌套
入口参数：实例化电机
外环位置控制PID，内环速度控制PID
注意    ：是否需要设计两两轮子同速？结合case信息
*******************************************************************/
void Double_Loop(unsigned int Target_Position)
{
	static int Position1=0, Position2=0, Position3=0, Position4=0;
	static int Encoder1, Encoder2, Encoder3, Encoder4;
	
	Serial.println("INTER_CNT:");
	Serial.println(INTER1_CNT);
	Serial.println(INTER2_CNT);
	Serial.println(INTER3_CNT);
	Serial.println(INTER4_CNT);
	
	Encoder1 = INTER1_CNT;
	Encoder2 = INTER2_CNT;
	Encoder3 = INTER3_CNT;
	Encoder4 = INTER4_CNT;
	INTER1_CNT = 0;
	INTER2_CNT = 0;
	INTER3_CNT = 0;
	INTER4_CNT = 0;


	Position1 += Encoder1;
	Position2 += Encoder2;
	Position3 += Encoder3;
	Position4 += Encoder4;

	Get_Point = delta_Position(Position1, Position2, Position3,Position4, Target_Position);

//调试监控代码
	Serial.println("Position is:");
	Serial.println(Position1);
	Serial.println(Position2);
	Serial.println(Position3);
	Serial.println(Position4);
	
	Serial.println("Target_Position is:");
	Serial.println(Target_Position);
	Serial.println("PWM_Position is:");

	PWM_MOTOR1 = Position1_PI(Position1, Target_Position);
	PWM_MOTOR1 = Velocity1_PI(Encoder1, -PWM_MOTOR1);
	
	PWM_MOTOR2 = Position2_PI(Position1, Target_Position);
	PWM_MOTOR2 = Velocity2_PI(Encoder1, -PWM_MOTOR2);
	
	PWM_MOTOR3 = Position3_PI(Position1, Target_Position);
	PWM_MOTOR3 = Velocity3_PI(Encoder1, -PWM_MOTOR3);
	
	PWM_MOTOR4 = Position4_PI(Position1, Target_Position);
	PWM_MOTOR4 = Velocity4_PI(Encoder1, -PWM_MOTOR4);

	Serial.println("PWM_Velocity is:");
	Serial.println(PWM_MOTOR1);
	Serial.println(PWM_MOTOR2);
	Serial.println(PWM_MOTOR3);
	Serial.println(PWM_MOTOR4);

	Xianfu_Pwm();
}

/******************************************************************************************************
函数功能：直流减速电机控制代码
入口参数：无，之后可能根据十六路传感器状态引入修正量
返回  值：无
********************************************************************************************************/
void Control_MOTOR(void)
{
	switch (move_Mode)
	{
	case X_increase:
		analogWrite(MOTOR1, PWM_MOTOR1);
		analogWrite(MOTOR2, PWM_MOTOR2);
		analogWrite(MOTOR3, PWM_MOTOR3);
		analogWrite(MOTOR4, PWM_MOTOR4);
		digitalWrite(MOTOR11, LOW);
		digitalWrite(MOTOR12, HIGH);
		digitalWrite(MOTOR21, HIGH);
		digitalWrite(MOTOR22, LOW);
		digitalWrite(MOTOR31, LOW);
		digitalWrite(MOTOR32, HIGH);
		digitalWrite(MOTOR41, HIGH);
		digitalWrite(MOTOR42, LOW);
		break;
	case X_decrease:
		analogWrite(MOTOR1, PWM_MOTOR1);
		analogWrite(MOTOR2, PWM_MOTOR2);
		analogWrite(MOTOR3, PWM_MOTOR3);
		analogWrite(MOTOR4, PWM_MOTOR4);
		digitalWrite(MOTOR11, HIGH);
		digitalWrite(MOTOR12, LOW);
		digitalWrite(MOTOR21, LOW);
		digitalWrite(MOTOR22, HIGH);
		digitalWrite(MOTOR31, HIGH);
		digitalWrite(MOTOR32, LOW);
		digitalWrite(MOTOR41, LOW);
		digitalWrite(MOTOR42, HIGH);
		break;
	case Y_increase:
		analogWrite(MOTOR1, PWM_MOTOR1);
		analogWrite(MOTOR2, PWM_MOTOR1);
		analogWrite(MOTOR3, PWM_MOTOR3);
		analogWrite(MOTOR4, PWM_MOTOR4);
		digitalWrite(MOTOR11, LOW); digitalWrite(MOTOR12, HIGH); 
		digitalWrite(MOTOR21, HIGH); digitalWrite(MOTOR22, LOW);
		digitalWrite(MOTOR31, LOW); digitalWrite(MOTOR32, HIGH);
		digitalWrite(MOTOR41, HIGH); digitalWrite(MOTOR42, LOW);
		break;
	case Y_decrease:
		analogWrite(MOTOR1, PWM_MOTOR1);
		analogWrite(MOTOR2, PWM_MOTOR2);
		analogWrite(MOTOR3, PWM_MOTOR3);
		analogWrite(MOTOR4, PWM_MOTOR3);
		digitalWrite(MOTOR11, LOW);
		digitalWrite(MOTOR12, HIGH);
		digitalWrite(MOTOR21, HIGH);
		digitalWrite(MOTOR22, LOW);
		digitalWrite(MOTOR31, HIGH);
		digitalWrite(MOTOR32, LOW);
		digitalWrite(MOTOR41, LOW);
		digitalWrite(MOTOR42, HIGH);
		break;
	case Find_it: break;
	}
}

/************************************************************************************************************
函数功能：10ms控制函数核心代码
入口参数：无
返回  值：无
***************************************************************************************************************/
void mycontrol_PID()
{
	
	static char OnList_PID = 0; //记录机器人目前处于运动路线(速度位置双环闭环PID式)
	static int stop = 0;   //　机器人状态参数
	int Grid;             //目标格子数
	unsigned int Target_Position; //目标距离——换算成直流减速电机脉冲数
	switch (stop)
	{
	case 0:
		move_Mode = List[0][OnList_PID]; //运动模式
		Grid = (int)List[1][OnList_PID];      //获取目标格子数
		Serial.println("Grid is:");
		Serial.println(Grid);
		Target_Position = (int)Grid * 400 / 188 * 390; //获取目标距离
		Double_Loop(Target_Position);
		Control_MOTOR();
		if (Get_Point)
		{
			++OnList_PID;
			if (OnList_PID >= List_Node1)
			{
				stop = 1;
			}
		}
		break;

	default:
		break;
	}		
	return;
}



/*Fuction:	定时器中断的处理，目前的功能是获得转速（单位与国际单位不同，自定单位，便于理解，具体转化待更新）。
Parameters: 无
Return:		无
Version:	1.0
Note:		得到店家的一圈多少个上升沿之后，可以更新实时速度。
*/
void Flash()
{
	OmniDirMove(omni_angle, omni_pwm);
}
