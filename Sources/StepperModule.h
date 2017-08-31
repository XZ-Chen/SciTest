//-------------------------------------------------------------------------*
//�ļ���: StepperModule.h      					                             	     *
//˵  ��: �����������ͷ�ļ�											                         *
//��ʼʱ�䣺  2012��07��09��              			           			           *
//�޶���¼��     		              			           				                 *
//��ע��      ������MC9S12XS128                          	                 *
//-------------------------------------------------------------------------*
#ifndef _STEPPERMODULE_H_
#define _STEPPERMODULE_H_

//1��ͷ�ļ�   
#include "typedefine.h"           //���ͱ�������
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 
#include "GeneralFun.h"
    
#define STEPPER_WAIT     0
#define STEPPER_RUN      1
#define STEPPER_REACH    2
#define STEPPER_POSERR   5

#define STEPPER_EN_L9935      PORTK_PK1
#define STEPPER_EN_L9935_DDR  DDRK_DDRK1

#define STEPPER_PHASE_NUM 4



   
//2  �궨��
//3  ��������
    
//-------------------------------------------------------------------------*
//������: StepperModuleInit                                                *
//��  ��: ��ʼ���������ģ��                                               * 
//��  ��: ��															                                 *
//��  ��: ��                                                               *
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------* 
void StepperModuleInit(void); 
uint8 StepperRun(uint16 nDesPos,uint16 nDesPosAD,uint16 nCurPosAD); 
#endif