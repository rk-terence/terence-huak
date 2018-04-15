#pragma once

/***********************************************************
引脚的定义
***********************************************************/

//定义四个直流减速电机8个引脚
const unsigned char MOTOR11 = 22, MOTOR12 = 23;
const unsigned char MOTOR21 = 26, MOTOR22 = 27;
const unsigned char MOTOR31 = 24, MOTOR32 = 25;
const unsigned char MOTOR41 = 28, MOTOR42 = 29;

//定义四个中断引脚
const unsigned char INTER1 = 18, INTER2 = 19, INTER3 = 20, INTER4 = 21;

//定义四个电机enable输入引脚
const unsigned char MOTOR1 = 4, MOTOR2 = 6, MOTOR3 = 5, MOTOR4 = 7;

//定义四个中断计数器
short INTER1_CNT, INTER2_CNT, INTER3_CNT, INTER4_CNT;

//光电传感器引脚设置
const short line1_pin1 = 34, line1_pin2 = 35, line1_pin3 = 36, line1_pin4 = 37; 
const short line2_pin1 = 41, line2_pin2 = 40, line2_pin3 = 39, line2_pin4 = 38;
const short line3_pin1 = 33, line3_pin2 = 32, line3_pin3 = 31, line3_pin4 = 30;
const short line4_pin1 = 42, line4_pin2 = 43, line4_pin3 = 44, line4_pin4 = 45;


/***********************************************************
global variables
***********************************************************/

int PWM_MOTOR1, PWM_MOTOR2, PWM_MOTOR3, PWM_MOTOR4;    //定义四个直流减速电机 pwm 控制量

int Position_X, Position_Y;                             //当前位置        

//运动状态相关
char move_Mode;
const char X_increase = 0, X_decrease = 1, Y_increase = 2, Y_decrease = 3, Find_it = 4;

//LOOP函数相关
int flag, crossing_flag, Mode_flag, Node_flag, step_flag;//flags
char init_flag = 1;

char PEread_flag;//设置读取状态标志，0表示读取不记录，1表示读取并记录中，2表示记录完毕
const char OnlyRead = 0, Reading = 1, ReadOver = 2;

//16路传感器真值表  1 BLACK 2 
char val_11, val_12, val_13, val_14;
char val_21, val_22, val_23, val_24;
char val_31, val_32, val_33, val_34;
char val_41, val_42, val_43, val_44;

//光电传感器设置 黑1白0

extern const short queueNumber = 500;//设置队列长度
const short wrongMax = 10;    //设置容错极限
char peRead11, peRead12, peRead13, peRead14;  //存取16路光电（photoelectric）传感器数据
char peRead21, peRead22, peRead23, peRead24;
char peRead31, peRead32, peRead33, peRead34;
char peRead41, peRead42, peRead43, peRead44;
short queue11, queue12, queue13, queue14;//设置16路光电传感器队列
short queue21, queue22, queue23, queue24;
short queue31, queue32, queue33, queue34;
short queue41, queue42, queue43, queue44;

//Oniwheel 相关
int omni_angle, last_angle;
float omni_pwm, last_pwm;

//机器人关键帧相关
char key_flag, crossing, runaway, change_crossing; //十字路口与跑偏状态

char Get_Point;

const char List_Node1 = 10;
char Now_step=0, Now_Node=0;
//运动路径List, 第一行存储移动状态，第二行存储移动步数
char List[][List_Node1] =
{{ X_increase,Y_decrease,7 },{3,3,7}};
//移动步数在双环嵌套PID中作为输入量
