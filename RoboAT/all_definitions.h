#pragma once

/***********************************************************
���ŵĶ���
***********************************************************/

//�����ĸ�ֱ�����ٵ��8������
const unsigned char MOTOR11 = 22, MOTOR12 = 23;
const unsigned char MOTOR21 = 26, MOTOR22 = 27;
const unsigned char MOTOR31 = 24, MOTOR32 = 25;
const unsigned char MOTOR41 = 28, MOTOR42 = 29;

//�����ĸ��ж�����
const unsigned char INTER1 = 18, INTER2 = 19, INTER3 = 20, INTER4 = 21;

//�����ĸ����enable��������
const unsigned char MOTOR1 = 4, MOTOR2 = 6, MOTOR3 = 5, MOTOR4 = 7;

//�����ĸ��жϼ�����
short INTER1_CNT, INTER2_CNT, INTER3_CNT, INTER4_CNT;

//��紫������������
const short line1_pin1 = 34, line1_pin2 = 35, line1_pin3 = 36, line1_pin4 = 37; 
const short line2_pin1 = 41, line2_pin2 = 40, line2_pin3 = 39, line2_pin4 = 38;
const short line3_pin1 = 33, line3_pin2 = 32, line3_pin3 = 31, line3_pin4 = 30;
const short line4_pin1 = 42, line4_pin2 = 43, line4_pin3 = 44, line4_pin4 = 45;


/***********************************************************
global variables
***********************************************************/

int PWM_MOTOR1, PWM_MOTOR2, PWM_MOTOR3, PWM_MOTOR4;    //�����ĸ�ֱ�����ٵ�� pwm ������

int Position_X, Position_Y;                             //��ǰλ��        

//�˶�״̬���
char move_Mode;
const char X_increase = 0, X_decrease = 1, Y_increase = 2, Y_decrease = 3, Find_it = 4;

//LOOP�������
int flag, crossing_flag, Mode_flag, Node_flag, step_flag;//flags
char init_flag = 1;

char PEread_flag;//���ö�ȡ״̬��־��0��ʾ��ȡ����¼��1��ʾ��ȡ����¼�У�2��ʾ��¼���
const char OnlyRead = 0, Reading = 1, ReadOver = 2;

//16·��������ֵ��  1 BLACK 2 
char val_11, val_12, val_13, val_14;
char val_21, val_22, val_23, val_24;
char val_31, val_32, val_33, val_34;
char val_41, val_42, val_43, val_44;

//��紫�������� ��1��0

extern const short queueNumber = 500;//���ö��г���
const short wrongMax = 10;    //�����ݴ���
char peRead11, peRead12, peRead13, peRead14;  //��ȡ16·��磨photoelectric������������
char peRead21, peRead22, peRead23, peRead24;
char peRead31, peRead32, peRead33, peRead34;
char peRead41, peRead42, peRead43, peRead44;
short queue11, queue12, queue13, queue14;//����16·��紫��������
short queue21, queue22, queue23, queue24;
short queue31, queue32, queue33, queue34;
short queue41, queue42, queue43, queue44;

//Oniwheel ���
int omni_angle, last_angle;
float omni_pwm, last_pwm;

//�����˹ؼ�֡���
char key_flag, crossing, runaway, change_crossing; //ʮ��·������ƫ״̬

char Get_Point;

const char List_Node1 = 10;
char Now_step=0, Now_Node=0;
//�˶�·��List, ��һ�д洢�ƶ�״̬���ڶ��д洢�ƶ�����
char List[][List_Node1] =
{{ X_increase,Y_decrease,7 },{3,3,7}};
//�ƶ�������˫��Ƕ��PID����Ϊ������
