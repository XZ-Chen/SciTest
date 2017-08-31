//-------------------------------------------------------------------------*
//�ļ���: MSMQ.c 					                             	                 *
//˵  ��: �������ݴ���											                               *
//��ʼʱ�䣺  2017��08��29��              			           			           *
//�޶���¼��     		              			           				                 *
//��ע��      ������MC9S12XET256                         	                 *
//-------------------------------------------------------------------------*
#include "MSMQ.h"
#include "MsgQueue.h"
#include "SCI.h"

extern SYS_PARA sys_para;
#define G_HVInjWide sys_para.item.InjWide_var.un16HV_InjWide
#define G_LVInjWide sys_para.item.InjWide_var.un16LV_InjWide
#define G_GapInjWide sys_para.item.InjWide_var.un16HLV_GapWide
extern uint8 DataSuccess_Flag;
extern T_SciMsg ReadMsg;

void MSSCIProcess(void){
     
     if(SciMsgReadProcess()){
        switch(ReadMsg.data[0])               //��������
        {
          case 'H':
              G_HVInjWide =  (ReadMsg.data[3] << 8) | ReadMsg.data[2]; //��8λ 
          case 'G':
              G_GapInjWide =  (ReadMsg.data[3] << 8) | ReadMsg.data[2]; //��8λ 
          case 'L':
              G_LVInjWide =  ((ReadMsg.data[3] << 8) | ReadMsg.data[2]); //��8λ         
        }
     }
     
}