#include "all_definitions.h"
/*2018.4.17�������ݣ�
	���Ӻ������ж�һ�У�4������紫�����Ƿ�ֵ����ȡ�
	��ȫ�ı����߼����ڴ�������Ч��Ŀǰֻ�ı���Y_decrease���߼���
	Swirl��pwm��Ϊ200
*/
/*2018.4.18�������ݣ�
	��X_increase �ķ��������Ϊ200pwm���Ƕȸ�Ϊ������*/


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
�������ܣ��ж϶�ȡ�Ĺ�紫������ֵ�Ƿ����
��ڲ�����ĳһ������������
����  ֵ������
***********************************************************************************/
short IsSensorEqual(short line)
{
	switch (line)
	{
	case 1:
		if (peRead11 == peRead12)
			if (peRead11 == peRead13)
				if (peRead11 == peRead14)
					return 1;
		break;
	case 2:
		if (peRead21 == peRead22)
			if (peRead21 == peRead23)
				if (peRead21 == peRead24)
					return 1;
		break;
	case 3:
		if (peRead31 == peRead32)
			if (peRead31 == peRead33)
				if (peRead31 == peRead34)
					return 1;
		break;
	case 4:
		if (peRead41 == peRead12)
			if (peRead41 == peRead43)
				if (peRead41 == peRead44)
					return 1;
		break;
	}
	return 0;
}

/*********************************************************************************
�������ܣ�ͨ����紫������������������Ŀǰ���˶�״̬����С���˶�״̬����΢�����������ҡ�ƫת
��ڲ�������
����  ֵ����
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
��ע:	���������ص�ֵ, ��ɫ����1, ��ɫ����0
�汾:
	2.0: ����line3��line4���߼����ж��Ƿ�ֱ��, �����ǲ��. ����Ч�����۲�, Ӧ�ò����������. Ŀǰ���ڵ�������
		Y_decrease�޷���ֱ��, �Լ�X_increase�ߵò���ֱ.
	2.1: �Ż��˴���(ɾ������). ���������.
	2.2: �ı�X�жϽ���ڵ���߼�, �ı�Y�жϽ���ڵ���߼�.
	2.3: �������µ�Y�����ж��߼�, ʹ�������.
		δ������(2.4): ���ǵ�X����Ѱ��Ҳ����̫��, ����׼����X�����Ѱ���߼�����һ��.׼��ʹ��line3��line4.
	2.4: ��2.3.
************************************************************************************/
void PE_to_Position()
{
	if (!crossing)
	{
		switch (move_Mode)
		{
		case X_increase:
		{
		//����ֱ��(������)
		if (!peRead32 && !peRead42 && !peRead33 && !peRead43 \
			|| !peRead32 && !peRead42 && peRead33 && peRead43|| !peRead33 && !peRead43 && peRead32 &&peRead42)
			//�м�4��ȫ�׻���һ�߰�һ�ߺ�.
		{
			omni_angle = 180;
		}
		else if (peRead32 && peRead42 && peRead33 && peRead43)//���ȫ�ڵĻ�
		{
			if (!peRead41 && !peRead31)
			{
				omni_angle = 225;
				omni_pwm = 200;
			}
			else if (!peRead44 && !peRead34)
			{
				omni_angle = 315;
				omni_pwm = 200;
			}
			//���û�з�����������, �ͼ�����һ��ָ��. ����Ͳ�дelse��
		}
		//��Ҫ���ƫ
		else if (peRead31 + peRead32 + peRead41 + peRead42 > peRead33 + peRead34 + peRead43 + peRead44)
		{
			omni_angle = 225;
			omni_pwm = 200;
		}
		//��Ҫ��ƫ
		else if (peRead31 + peRead32 + peRead41 + peRead42 < peRead33 + peRead34 + peRead43 + peRead44)
		{
			omni_angle = 135;
			omni_pwm = 200;
		}

		//����������ʮ��·��
		if (peRead31 + peRead32 + peRead33 + peRead34 < 2 || peRead41 + peRead42 + peRead43 + peRead44 < 2)//ԭ�ж�����: !peRead31 && !peRead32 && !peRead33 && !peRead34
		{
			crossing = 1;
			Now_step++;
		}
		/*else
		{
			omni_angle = 180;
			omni_pwm = 250;
		}*/

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
		//����ǰ��
		if (peRead31 + peRead32 + peRead33 + peRead34 == 4 && peRead41 + peRead42 + peRead43 + peRead44 == 0 \
			|| peRead31 + peRead32 + peRead33 + peRead34 == 0 && peRead41 + peRead42 + peRead43 + peRead44 == 4)//һ�ߺ�һ�߰�
		{
			omni_angle = 270;
		}
		//�������ȫ�ڣ����������
		else if (peRead31 + peRead32 + peRead33 + peRead34 == 4 && peRead41 + peRead42 + peRead43 + peRead44 == 4)//ȫ��
		{
			if (peRead22 && peRead23)//����ȫ�ڣ���ֱ��
				omni_angle = 270;
			else if (peRead22 && !peRead23)//һ��һ��
			{
				omni_angle = 0;
				omni_pwm = 200;
			}
			else if (!peRead22 && peRead23)//һ��һ�ף��������෴
			{
				omni_angle = 180;
				omni_pwm = 200;
			}
			else//���ȫ�ף��޷��жϣ�����ֱ��
				omni_angle = 270;
		}
		//���С������
		else if (!IsSensorEqual(4) || !IsSensorEqual(3))
		{
			if (peRead44)
				Swirl(2);
			if (peRead34)
				Swirl(1);
		}
		
		//�������ڵ�
		if (!peRead32 && !peRead42 || !peRead33 && !peRead43)//ԭ�ж�����: !peRead32 && !peRead42
		{
			Now_step++;
			crossing = 1;
		}
		/*else
		{
			omni_angle = 270;
			omni_pwm = 250;
		}*/
		break;
		}
		default:
			omni_pwm = 0;
			break;
		}
	}
	else//crossing == 1
	{
		switch (move_Mode)
		{
		case X_increase:
		{
			if (peRead31 + peRead32 + peRead33 + peRead34 >= 2 && peRead41 + peRead42 + peRead43 + peRead44 >= 2)//�����������Ǻڵ�ʱ��������crossing.
			{
				crossing = 0;
			}
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
			if (peRead32 || peRead42)
			{
				crossing = 0;
			}
			break; 
		}
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