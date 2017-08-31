 //-------------------------------------------------------------------------*
//�ļ���: DIOModule.h                                                       *
//˵  ��: IO����ͷ�ļ�                                         		          *
//��ʼʱ�䣺  2012��07��02��              			                            *
//�޶���¼��     		              			                                    *
//��ע��      ������MC9S12XS128               			                        *
//--------------------------------------------------------------------------*
#ifndef _DIOMODULE_H
#define _DIOMODULE_H

//1 ͷ�ļ�
#include "typedefine.h"           //���ͱ�������
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 
#include "PinMap.h"




#define RESTN_A39441  PORTK_PK3
#define RESTN_A39442  PORTK_PK4
#define RESTN_L9733   PORTK_PK2

#define RESTN_A39441_DDR  DDRK_DDRK3
#define RESTN_A39442_DDR  DDRK_DDRK4
#define RESTN_L9733_DDR   DDRK_DDRK2

#define CMD_L9733_OUTPUT  0xac00
#define CMD_L9733_DIAG    0xa300
#define CMD_L9733_PROTECT 0xaa00







//-------------------------------------------------------------------------* 
//������: DIOModuleInit                                                    *
//��  ��: PWM��ʼ��                                                        *
//��  ��: ��                                                               *
//��  ��: ��                                                               * 
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*  
void DIOModuleInit(void);
void DIScan(uint16 *pDI);
void keyScan(uint16 *pDI);
uint16 DOOutput(uint8 pin,uint8 val);
uint16 DIRead(uint8 pin);

#define MainRelayOn()   (DOOutput(DO_MAINRLY_PIN,ON))
#define MainRelayOff()  (DOOutput(DO_MAINRLY_PIN,OFF))
#define LNGRVRelayOn()  (DOOutput(DO_LNGRLY_PIN,ON))
#define LNGRVRelayOff() (DOOutput(DO_LNGRLY_PIN,OFF))

#endif