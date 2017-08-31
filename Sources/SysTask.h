//-------------------------------------------------------------------------*
//文件名: MCUInit.h                                                    	   *
//说  明: 芯片初始化头文件                                         		     *
//作者：      刘晓程						                                           *
//初始时间：  2012年07月01日              			                           *
//修订记录：     		              			                                   *
//备注：      适用于MC9S12XS128               			                       *
//-------------------------------------------------------------------------*
#ifndef _SYSTASK_H_
#define _SYSTASK_H_


//1 头文件
#include "typedefine.h"        //类型别名定义



typedef union _sys_para{
   uint16 data[256];
   struct{
       struct{
          uint16 un16SysMode;       //系统主模式
          uint16 un16DuralMode;     //双燃料模式
          uint16 un16InjWide;       //喷射时间
          uint16 un16StepperPos;    //电机位置    
          uint16 un16LNGState;
          uint16 bSensorScan;      //传感器扫描
          uint16 bIOScan;           //IO口扫描  
          uint16 bModeJudge;        //模式判别
          uint16 bOutput;           //输出
          uint16 un16Pedal;         //油门位置
                       
       }mem_var;                      //9
       struct{
         uint16 un16GearNum;          //齿数
         uint16 un16LNGSpeed;         //
         uint16 un16EstTempMax;
         uint16 un16StpP1;
         uint16 un16HighSpeed;
         uint16 un16HSK1;
         uint16 un16LSK2;
         uint16 un16StpP2;
         uint16 un16StpStart;         //步进电机起始
         uint16 un16StpEnd;           //步进电机终止
       }const_var;                   //10
       uint16 un16Sensor[10];        //预留10个传感器
       uint16 un16DI[8];             //预留8个输入
       uint16 un16DO[8];             //预留8个输出
       
       struct{
       uint16 un16HV_InjWide;        //高压喷射时间
       uint16 un16HLV_GapWide;       //高低压喷射间隔时间
       uint16 un16LV_InjWide;        //低压喷射时间
       }InjWide_var;
       
       uint16 un16Reserved[202];
   }item;
}SYS_PARA;

#define SYS_POWERON  0
#define SYS_SINGLE   1
#define SYS_DURAL    2
#define SYS_ERR      3  //出错
#define SYS_HALT     4  //停止


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






//这是sub mode存储出致命代码


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