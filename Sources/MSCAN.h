//-------------------------------------------------------------------------*
//�ļ���: MSCAN.h 					                             	                 *
//˵  ��: CAN��������ͷ�ļ�											                           *
//��ʼʱ�䣺  2012��07��20��              			           			           *
//�޶���¼��     		              			           				                 *
//��ע��      ������MC9S12XS128                         	                 *
//-------------------------------------------------------------------------*
#ifndef _MSCAN_H_
#define _MSCAN_H_
//1 ͷ�ļ� 
#include "typedefine.h"           //���ͱ�������
#include <hidef.h> 
#include <MC9S12XET256.h>     /* derivative information */
#include "SysTask.h"

//2 �궨��

#define   MAX_LEN 8     // Max Data Frame

/////////////////////////////////////////////////////////////////////////////////////////
// Variables
/////////////////////////////////////////////////////////////////////////////////////////
typedef struct _can_msg 
{
    unsigned int id;
    Bool RTR;
    unsigned char data[8];
    unsigned char len;
    unsigned char prty;
}can_msg;



/////////////////////////////////////////////////////////////////////////////////////////
// Functions
/////////////////////////////////////////////////////////////////////////////////////////
void MSCANInit(void);
Bool MSCANSendMsg(can_msg msg);
Bool MSCANGetMsg(can_msg *pmsg);
Bool MSCANCheckRcvdMsg(void);
void MSCANProcess(void); 

#endif