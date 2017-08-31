//-------------------------------------------------------------------------*
//�ļ���: ATD.h 					                             	                   *
//˵  ��: ģ/��ת��ģ������ͷ�ļ�	  								                       *
//��ʼʱ�䣺  2012��06��30��              			           			           *
//�޶���¼��     		              			           				                 *
//��ע��      ������MC9S12XS128                         	                 *
//-------------------------------------------------------------------------*
#ifndef _SENSORMODULE_H_           //��ֹ�ظ�����
#define _SENSORMODULE_H_ 

//1��ͷ�ļ�    
#include "typedefine.h"           //���ͱ�������
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 
#include "ATD.h"
#include "SPI.h"
#include "PinMap.h"



typedef struct _sensor {
    uint8 status;
    UINT8 pointer;
  	UINT16 value[7];
}sensor;

//-----------------------------------------------------------------------*
//������: SensorModuleInit                                                  	   *
//��  ��: ��ʼ��ATDģ��                                                  * 
//��  ��: ��															                               *
//��  ��: ��                                                             *
//˵  ��: ��                                                             *
//-----------------------------------------------------------------------*

extern sensor stppos_sensor;
extern sensor pedalpos_sensor;
extern sensor stppos_sensor;
extern sensor esttemp_sensor;
extern sensor crankspeed_sensor;

void SensorModuleInit(void);
void SensorScan(uint16 *pSensor);

#define ExhasutTempRead() (SPIReadWord(SPI_MAX6675,0xffff))



        
#endif



