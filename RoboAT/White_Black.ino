#include "all_definitions.h"

/*********************************************************************************
�������ܣ�ֻ��ȡ��紫��������ֵ
��ڲ�������
����  ֵ����
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
�������ܣ�ͨ����紫������������������Ŀǰ���˶�״̬����С���˶�״̬����΢�����������ҡ�ƫת
��ڲ�������
����  ֵ����
��    ����0
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
�������ܣ�ͨ����紫��������������������Ŀǰ״̬�����ֿ�������״̬ʱ�����������case 1, �������󡢹��ҡ�ʮ��
��ڲ�������
����  ֵ����
��    ����1.0
************************************************************************************/
void PE_to_Position()
{
	if (!crossing)
	{
		switch (move_Mode)
		{
		case X_increase:
		{
			//����ֱ��
			if ((!peRead32 && !peRead33) || (!peRead42 && !peRead43))
			{
				omni_angle = 180;
				omni_pwm = 212;
			}

			//��Ҫ��ƫ
			if (!peRead34 && peRead32 && peRead31)
			{
				omni_angle = 200;
				omni_pwm = 250;
			}
			//��Ҫ��ƫ
			if (!peRead31 && peRead33 && peRead34)
			{
				omni_angle = 160;
				omni_pwm = 250;
			}

			if (!peRead31 && !peRead32 && !peRead33 && !peRead34)
			{
				++Now_step;
				crossing = 1;
			}
			break;
		}
		case X_decrease:
		{
			//����ֱ��
			if ((!peRead32 && !peRead33) || (!peRead42 && !peRead43))
			{
				omni_angle = 0;
				omni_pwm = 212;
			}

			//��Ҫ��ƫ
			if (!peRead41 && peRead43 && peRead44)
			{
				omni_angle = 20;
				omni_pwm = 250;
			}
			//��Ҫ��ƫ
			if (!peRead44 && peRead41 && peRead42)
			{
				omni_angle = 340;
				omni_pwm = 250;
			}

			if (!peRead41 && !peRead42 && !peRead43 && !peRead44)
			{
				++Now_step;
				crossing = 1;
			}
			break;
		}
		case Y_increase:
		{
			//����ֱ��
			if ((!peRead31 && !peRead32 && !peRead33 && !peRead34) || (!peRead41 && !peRead42 && !peRead43 && !peRead44))
			{
				omni_angle = 90;
				omni_pwm = 212;
			}

			//��Ҫ��ƫ
			if (!peRead11 || !peRead12)
			{
				omni_angle = 135;
				omni_pwm = 250;
			}
			//��Ҫ��ƫ
			if (!peRead13 || !peRead14)
			{
				omni_angle = 45;
				omni_pwm = 250;
			}

			if (!peRead12 && !peRead13)
			{
				Now_step++;
				crossing = 1;
			}
			break;
		}
		case Y_decrease:
		{
			//����ֱ��
			if ((!peRead31 && !peRead32 && !peRead33 && !peRead34) || (!peRead41 && !peRead42 && !peRead43 && !peRead44))
			{
				omni_angle = 270;
				omni_pwm = 212;
			}

			//��Ҫ��ƫ
			if (!peRead23 || !peRead24)
			{
				omni_angle = 315;
				omni_pwm = 250;
			}
			//��Ҫ��ƫ
			if (!peRead21 || !peRead22)
			{
				omni_angle = 225;
				omni_pwm = 250;
			}

			if (!peRead22 && !peRead23)
			{
				++Now_step;
				crossing = 1;
			}
			break;
		}
		default:
			OmniDirMove(0,0);
			break;
		}
	}
	else
	{
		switch (move_Mode)
		{
		case X_increase:
			if ((peRead31 + peRead32 + peRead33 + peRead34) >= 2)
			{
				crossing = 0;
			}
			break;
		case X_decrease:
			if ((peRead41 + peRead42 + peRead43 + peRead44) >= 2)
			{
				crossing = 0;
			}
			break;
		case Y_increase:
			if ((peRead11 + peRead12 + peRead13 + peRead14) >= 2)
			{
				crossing = 0;
			}
			break;
		case Y_decrease:
			if ((peRead21 + peRead22 + peRead23 + peRead24) >= 2)
			{
				crossing = 0;
			}
			break;
		default:
			omni_pwm = 0;
			break;
		}
	}
}

/***********************************************************************************
�������ܣ���ȡ��紫��������¼���ݶ���
��ڲ�����short queue_pos ��ʾ��ǰ��Ա��λ��,��¼��Ϻ������������case2
����  ֵ����
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
�������ܣ�����紫����������� queueNumber �ζ�ȡ�������ƽ������ wrongMax �Σ�����Ϊ������ȷ
��ڲ���  short queue
����  ֵ��char True_Level
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
�������ܣ���� True_Level,�����������
��ڲ�������
����  ֵ����
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

/**************************************************************************
�������ܣ�BACK and Find
		�ߵ��ڵ�֮��������ֱ���������������������������ٴ�ȫ�ף�
��ڲ�������
����ֵ  ����
*************************************************************************/
void Find_Back()
{
	omni_pwm = 200;
	switch (move_Mode)
	{
		case X_increase:
		{
			omni_angle = 0;
			OmniDirMove(omni_angle, omni_pwm);
			PEread();
			while (peRead31 || peRead32 || peRead33 || peRead34) 
			{
				PEread();
			}
			break;
		}
		case Y_increase:
		{
			omni_angle = 90;
			OmniDirMove(omni_angle, omni_pwm);
			PEread();
			while (peRead33 || peRead43) 
			{ 
				PEread();
			}
			break;
		}
		case X_decrease:
		{
			omni_angle = 180;
			OmniDirMove(omni_angle, omni_pwm);
			PEread();
			while (peRead41 || peRead42 || peRead43 || peRead44) 
			{
				PEread();
			}
			break;
		}
		case Y_decrease:
		{
			omni_angle = 270;
			OmniDirMove(omni_angle, omni_pwm);
			PEread();
			while (peRead32 || peRead42) 
			{
				PEread();
			}
			break;
		}

	}
	return;
}