#ifndef __ULN2003_H_
#define __ULN2003_H_


typedef enum
{
	STOP_IT1	=	0	,	//ֹͣ
	BRAKE1		,	//ɲ��
	FORWARD1			,	//��ת
	REVERSE1				//��ת
}RotationSTATE_1;


typedef enum
{
	STOP_IT2	=	0	,	//ֹͣ
	BRAKE2			,	//ɲ��
	FORWARD2			,	//��ת
	REVERSE2				//��ת
}RotationSTATE_2;



//���Ƶ��ֹͣ��ɲ������ת����ת
//ͨ�� RotationSTATE ö�ٱ�����ֵ
//ע�������������Ҫ�ŵ�ѭ������ģ�������ѯ����
void uln2003_MotorRotation_1(RotationSTATE_1 rotationControl);
void uln2003_MotorRotation_2(RotationSTATE_2 rotationControl);

/*	ʹ��ʾ�� 

	uln2003_MotorRotation(STOP_IT);	//ֹͣ

*/

#endif /*__ULN2003_H_*/

