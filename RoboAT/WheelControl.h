

/*Fuction:	to move the car on all directions (especially 4 directions: foward, leftward, rightward, backward).
Parameters: int angle, with a range from 0 degree to 360 degrees.
			int speed, should be a number from 0 to 1(number 1 means full speed).
Return:		NONE
Version:	1.0
Note:		Some of the parameters should be modified according to real situations, for on real situations 
			things are not always in consistency with the theory. The parameters are mainly the PWM part, and 
			I can't guarantee the velocity will definitely be exactly in proportion with the duty cycle of 
			PWM waves. The unsure parameters are indicated in WheelControl.ino.

			THEREFORE, I DO NOT RECOMMEND USING ALL THE DIRECTIONS. 
			
			To secure the performance, please use four directions only, the degrees of which are 0, 90, 180, 
			and 270.
*/
int OmniDirMove(short angle, short pwm);


/*Fuction:	让小车旋转
Parameters: int choice (1 - 逆时针, 2 - 顺时针)
Return:		NONE
Version:	1.0
Note:		
*/
void Swirl(int choice);



void DMotorControl(char status1, unsigned char pwm1, char status2, unsigned char pwm2, char status3, unsigned char pwm3, char status4, unsigned char pwm4);
