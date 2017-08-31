//-------------------------------------------------------------------------*
//�ļ���: TIM.h      					                             	               *
//˵  ��: TIM��ʱ������ͷ�ļ�											                         *
//��ʼʱ�䣺  2012��07��09��              			           			           *
//�޶���¼��     		              			           				                 *
//��ע��      ������MC9S12XS128                          	                 *
//-------------------------------------------------------------------------*
#ifndef _CRANKMODULE_H_
#define _CRANKMODULE_H_

//1��ͷ�ļ�   
#include "typedefine.h"           //���ͱ�������
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 
#include "ECT.h"

//2  �궨��
#define CRANK_GEAR_NUM        128
#define CRANK_CYLINDER_NUM    6
#define CRANK_RPM_MAX         5000
#define CRANK_RPM_MIN         100

typedef struct{
	UINT16 array[200];
	UINT32 accum;
	UINT16 average;
	UINT8 index;
	UINT8 gearnum;
	UINT16 rpm;
	uint8 stopcnt;
} GROUP_ACCUM;
    


//3  �������� 
//-------------------------------------------------------------------------*
//������: CrankModuleInit                                                  *
//��  ��: ��ʼ����ʱ��ģ��                                                 * 
//��  ��: ��															                                 *
//��  ��: ��                                                               *
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*

void CrankModuleInit(void);
uint16 CrankSpeedRead(void);

#endif