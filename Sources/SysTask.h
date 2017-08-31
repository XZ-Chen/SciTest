//-------------------------------------------------------------------------*
//�ļ���: MCUInit.h                                                    	   *
//˵  ��: оƬ��ʼ��ͷ�ļ�                                         		     *
//���ߣ�      ������						                                           *
//��ʼʱ�䣺  2012��07��01��              			                           *
//�޶���¼��     		              			                                   *
//��ע��      ������MC9S12XS128               			                       *
//-------------------------------------------------------------------------*
#ifndef _SYSTASK_H_
#define _SYSTASK_H_


//1 ͷ�ļ�
#include "typedefine.h"        //���ͱ�������



typedef union _sys_para{
   uint16 data[256];
   struct{
       struct{
          uint16 un16SysMode;       //ϵͳ��ģʽ
          uint16 un16DuralMode;     //˫ȼ��ģʽ
          uint16 un16InjWide;       //����ʱ��
          uint16 un16StepperPos;    //���λ��    
          uint16 un16LNGState;
          uint16 bSensorScan;      //������ɨ��
          uint16 bIOScan;           //IO��ɨ��  
          uint16 bModeJudge;        //ģʽ�б�
          uint16 bOutput;           //���
          uint16 un16Pedal;         //����λ��
                       
       }mem_var;                      //9
       struct{
         uint16 un16GearNum;          //����
         uint16 un16LNGSpeed;         //
         uint16 un16EstTempMax;
         uint16 un16StpP1;
         uint16 un16HighSpeed;
         uint16 un16HSK1;
         uint16 un16LSK2;
         uint16 un16StpP2;
         uint16 un16StpStart;         //���������ʼ
         uint16 un16StpEnd;           //���������ֹ
       }const_var;                   //10
       uint16 un16Sensor[10];        //Ԥ��10��������
       uint16 un16DI[8];             //Ԥ��8������
       uint16 un16DO[8];             //Ԥ��8�����
       
       struct{
       uint16 un16HV_InjWide;        //��ѹ����ʱ��
       uint16 un16HLV_GapWide;       //�ߵ�ѹ������ʱ��
       uint16 un16LV_InjWide;        //��ѹ����ʱ��
       }InjWide_var;
       
       uint16 un16Reserved[202];
   }item;
}SYS_PARA;

#define SYS_POWERON  0
#define SYS_SINGLE   1
#define SYS_DURAL    2
#define SYS_ERR      3  //����
#define SYS_HALT     4  //ֹͣ


#define DURAL_MODE_STOP        0   
#define DURAL_MODE_START       1
#define DURAL_MODE_IDLE        2
#define DURAL_MODE_NORMAL      3

#define DURAL_MODE_OVERACC     4
#define DURAL_MODE_OVERDEC     5
#define DURAL_MODE_SPEEDLIMIT  6
#define DURAL_MODE_OVERSPEED   7

#define PEDAL_AD_MIN    25
#define PEDAL_AD_MAX    470
#define PEDAL_RATIO_MAX  1200
#define PEDAL_RATIO_MIN  900

#define STEPPER_AD_MIN  135
#define STEPPER_AD_MAX  605
#define STEPPER_P1      0
#define STEPPER_P2      100

#define LNG_HSK1        100
#define LNG_LSK2        100
#define LNG_HIGHSPEED   1600 






//����sub mode�洢����������


void SysVarInit(void);
void SysSingleProcess(void);
void SysDuralProcess();
void SysTaskProcess(void);
void SysDigProcess(void);
void SysOutputProcess(void);

void DuralModeJudge(void);
void DuralAppExcute(void);

void EngineStopCtrl(void);
void NormalCtrl(void);
void OverAccCtrl(void);
void OverDecCtrl(void);
void SpeedLimitCtrl(void);

void EngineTestCtrl();


#endif