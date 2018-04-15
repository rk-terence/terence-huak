/*
Name:		Position_Volecity_Control.ino
Created:	2018/3/24 18:15:12
Author:	HUAK
*/
#include"Position_Velocity_Control.h"
//�����ĸ��жϼ�������
void CALL_INTER1() { INTER1_CNT++; }
void CALL_INTER2() { INTER2_CNT++; }
void CALL_INTER3() { INTER3_CNT++; }
void CALL_INTER4() { INTER4_CNT++; }

/*************************************************************************
�������ܣ����㵱ǰλ�þ���Ŀ��λ�õľ���
��ڲ�������ǰλ�ø�����Ŀ��λ�ø���
����  ֵ��Target_Position (����������ʾ)
���㹫ʽ����Ŀ��������-Դ������꣩* �������е���� / ���ܳ� * һȦ������ / 1.41
*************************************************************************/
unsigned int Distance(char Grid)
{
	unsigned int Target_Position;
	Target_Position = (int)Grid * 400 / 188 * 390 ;
	//Target_Position = Grid * 295 / 188 * 390;// �����ã�����
}


/*************************************************************************
�������ܣ�����PWM��ֵ
��ڲ�����Moto
����  ֵ��void
**************************************************************************/
void Xianfu_Pwm()
{
	int Amplitude = 250;   //PWM����255,������250����
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
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
***************************************************************/
int myabs(int a)
{
	int temp;
	if (a < 0) temp = -a;
	else temp = a;
	return temp;
}

/****************************************************************
�������ܣ��ٶ�PID������
��ڲ��������������ٶȲ���ֵ���ٶȿ��Ƶ�Ŀ��ֵ
����  ֵ�����PWM
�����ٶ�ʽ��ɢPID��ʽ
pwm=Kp*e(k)+Ki*��e(k)+Kd[e��k��-e(k-1)]
e(k)������ƫ��
e(k-1)������һ�ε�ƫ��
��e(k)����e(k)�Լ�֮ǰ��ƫ����ۻ���;����kΪ1,2,,k;
pwm�������
*****************************************************************/
int Velocity1_PI(int Encoder, int Target)
{
	static char Last_Mode;
	float Kp = 35, Ki = 3.5, Kd = 0;      //PID�����ɵ��������͸��ؾ���
	static int Bias, Pwm, Last_bias;
	if (Last_Mode != move_Mode)
	{
		Last_bias = 0;
		Pwm = 0;
	}
	Bias = Encoder - Target;               //����ƫ��
	Pwm += Kp * (Bias - Last_bias)  + Ki * Bias ;//����ʽPI������
	Last_bias = Bias;
	Last_Mode = move_Mode;
	return Pwm;
}
int Velocity2_PI(int Encoder, int Target)
{
	static char Last_Mode;
	float Kp = 35, Ki = 3.5, Kd = 0;      //PID�����ɵ��������͸��ؾ���
	static int Bias, Pwm, Last_bias;
	if (Last_Mode != move_Mode)
	{
		Last_bias = 0;
		Pwm = 0;
	}
	Bias = Encoder - Target;               //����ƫ��
	Pwm += Kp * (Bias - Last_bias)  + Ki * Bias ;//����ʽPI������
	Last_bias = Bias;
	Last_Mode = move_Mode;
	return Pwm;
}
int Velocity3_PI(int Encoder, int Target)
{
	static char Last_Mode;
	float Kp = 35, Ki = 3.5, Kd = 0;      //PID�����ɵ��������͸��ؾ���
	static int Bias, Pwm, Last_bias;
	if (Last_Mode != move_Mode)
	{
		Last_bias = 0;
		Pwm = 0;
	}
	Bias = Encoder - Target;               //����ƫ��
	Pwm += Kp * (Bias - Last_bias)  + Ki * Bias ;//����ʽPI������
	Last_bias = Bias;
	Last_Mode = move_Mode;
	return Pwm;
}
int Velocity4_PI(int Encoder, int Target)
{
	static char Last_Mode;
	float Kp = 35, Ki = 3.5, Kd = 0;      //PID�����ɵ��������͸��ؾ���
	static int Bias, Pwm, Last_bias;
	if (Last_Mode != move_Mode)
	{
		Last_bias = 0;
		Pwm = 0;
	}
	Bias = Encoder - Target;               //����ƫ��
	Pwm += Kp * (Bias - Last_bias)  + Ki * Bias ;//����ʽPI������
	Last_bias = Bias;
	Last_Mode = move_Mode;
	return Pwm;
}

/****************************************************************
�������ܣ�λ��PID������
��ڲ��������������ٶȲ���ֵ���ٶȿ��Ƶ�Ŀ��ֵ
����  ֵ�����PWM
����λ��ʽ��ɢPID��ʽ
pwm=Kp*e(k)+Ki*��e(k)+Kd[e��k��-e(k-1)]
e(k)������ƫ��
e(k-1)������һ�ε�ƫ��
��e(k)����e(k)�Լ�֮ǰ��ƫ����ۻ���;����kΪ1,2,,k;
pwm�������
*****************************************************************/
int Position1_PI(int Encoder, int Target)
{
	static char Last_Mode;
	float Kp = 5.2, Ki = 0.01, Kd = 0;       //PID�����ɵ��������͸��ؾ���
	static float Bias, Pwm, Integral_bias = 0;
	if (Last_Mode != move_Mode)
	{
		Integral_bias += Bias;//�˶�״̬�ı䣬�ٶȻ��֣�����λ�ã����
		Pwm = 0;              //λ��ʽPI���������
	}
	Bias = Encoder - Target;  //����ƫ��
	Integral_bias += Bias;                 //���ƫ��Ļ��֣�����λ��
	Pwm = Kp * Bias + Ki * Integral_bias;     //λ��ʽPI������
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
	float Kp = 5.2, Ki = 0.01, Kd = 0;       //PID�����ɵ��������͸��ؾ���
	static float Bias, Pwm, Integral_bias = 0;
	if (Last_Mode != move_Mode)
	{
		Integral_bias += Bias;//�˶�״̬�ı䣬�ٶȻ��֣�����λ�ã����
		Pwm = 0;              //λ��ʽPI���������
	}
	Bias = Encoder - Target;  //����ƫ��
	Integral_bias += Bias;                 //���ƫ��Ļ��֣�����λ��
	Pwm = Kp * Bias + Ki * Integral_bias;     //λ��ʽPI������
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
	float Kp = 5.2, Ki = 0.01, Kd = 0;       //PID�����ɵ��������͸��ؾ���
	static float Bias, Pwm, Integral_bias = 0;
	if (Last_Mode != move_Mode)
	{
		Integral_bias += Bias;//�˶�״̬�ı䣬�ٶȻ��֣�����λ�ã����
		Pwm = 0;              //λ��ʽPI���������
	}
	Bias = Encoder - Target;  //����ƫ��
	Integral_bias += Bias;                 //���ƫ��Ļ��֣�����λ��
	Pwm = Kp * Bias + Ki * Integral_bias;     //λ��ʽPI������

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
	float Kp = 5.2, Ki = 0.01, Kd = 0;       //PID�����ɵ��������͸��ؾ���
	static float Bias, Pwm, Integral_bias = 0;
	if (Last_Mode != move_Mode)
	{
		Integral_bias += Bias;//�˶�״̬�ı䣬�ٶȻ��֣�����λ�ã����
		Pwm = 0;              //λ��ʽPI���������
	}
	Bias = Encoder - Target;  //����ƫ��
	Integral_bias += Bias;                 //���ƫ��Ļ��֣�����λ��
	Pwm = Kp * Bias + Ki * Integral_bias;     //λ��ʽPI������
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
�������ܣ��ٶ�λ��PID������˫��Ƕ��
��ڲ�����ʵ�������
�⻷λ�ÿ���PID���ڻ��ٶȿ���PID
ע��    ���Ƿ���Ҫ�����������ͬ�٣����case��Ϣ
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

//���Լ�ش���
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
�������ܣ�ֱ�����ٵ�����ƴ���
��ڲ������ޣ�֮����ܸ���ʮ��·������״̬����������
����  ֵ����
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
�������ܣ�10ms���ƺ������Ĵ���
��ڲ�������
����  ֵ����
***************************************************************************************************************/
void mycontrol_PID()
{
	
	static char OnList_PID = 0; //��¼������Ŀǰ�����˶�·��(�ٶ�λ��˫���ջ�PIDʽ)
	static int stop = 0;   //��������״̬����
	int Grid;             //Ŀ�������
	unsigned int Target_Position; //Ŀ����롪�������ֱ�����ٵ��������
	switch (stop)
	{
	case 0:
		move_Mode = List[0][OnList_PID]; //�˶�ģʽ
		Grid = (int)List[1][OnList_PID];      //��ȡĿ�������
		Serial.println("Grid is:");
		Serial.println(Grid);
		Target_Position = (int)Grid * 400 / 188 * 390; //��ȡĿ�����
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



/*Fuction:	��ʱ���жϵĴ���Ŀǰ�Ĺ����ǻ��ת�٣���λ����ʵ�λ��ͬ���Զ���λ��������⣬����ת�������£���
Parameters: ��
Return:		��
Version:	1.0
Note:		�õ���ҵ�һȦ���ٸ�������֮�󣬿��Ը���ʵʱ�ٶȡ�
*/
void Flash()
{
	OmniDirMove(omni_angle, omni_pwm);
}
