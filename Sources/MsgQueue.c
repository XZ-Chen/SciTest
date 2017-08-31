/*---------------------------------------------------------*/
/************************************************************
����Ƽ�MC9S12XET256���ܳ��๦���ۺϿ���ƽ̨ 
E-mail: 2008f.d@163.com
�Ա��꣺http://fxfreefly.taobao.com
************************************************************/
/*---------------------------------------------------------*/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "MsgQueue.h"
#include "SCI.h"

Queue MsgLine;

/*************************************************************/
/*                     ��ʼ������                            */
/*************************************************************/
void InitializeQueue(void) {
	int i;
  MsgLine.front = MsgLine.rear = NULL;
  MsgLine.items = 0;
	MsgLine.front = MsgLine.rear = 0;
  MsgLine.items = 0;
  MsgLine.Msgdata->len = 5;
	MsgLine.Msgdata->MsgHead = MsgLine.Msgdata->MsgTail = 0;
	for(i=0;i<Queue_Size;i++){
  	MsgLine.Msgdata->data[i] = 0;
	}
	
}
/*************************************************************/
/*                     �ж϶���״̬                          */
/*************************************************************/
Bool QueueIsFull(const Queue *pq)
{    
    return pq->items == Queue_Size;
}
   
Bool QueueIsEmpty(const Queue *pq)
{   
    return pq->items == 0;;
}
int QueueItemCount(const Queue *pq){

    return pq->items;
}
/*************************************************************/
/*                     �����и�����Ŀ                        */
/*************************************************************/
static void CopyToQueue(T_SciMsg Msg, Queue *pn){
   
   int i; 
   for(i=0;i<=2;i++) 
      pn->rear->data[i] = Msg.data[i];
}
static void CopyToMsg(Queue *pn, T_SciMsg *Msg){
   
   int j; 
   for(j=0;j<=2;j++)
      Msg->data[j] = pn->front->data[j];
}
/*************************************************************/
/*                     �����������Ŀ                        */
/*************************************************************/
Bool EnQueue(T_SciMsg Msg,Queue *pq) {

	if(QueueIsFull(pq))
       return FALSE;
	if(QueueIsEmpty(pq))
       pq->rear = &(pq->Msgdata[0]); //���ݰ����ڶ����׶�       	
  else 
     	 pq->rear = &(pq->Msgdata[pq->items]);  //���ӵ�����β��	                               
  CopyToQueue(Msg, pq);  
  pq->items++;                //������Ŀ��������
 	SCI_SendDec16u(pq->items);
 	SCI_send('\n');
  return TRUE;  
}
/*************************************************************/
/*                     �Ӷ��ж�ȡ��Ŀ                        */
/*************************************************************/
Bool DeQueue(T_SciMsg *Msg,Queue *pq) {
    if(QueueIsEmpty(pq))
        return FALSE;
    CopyToMsg(pq, Msg);
    pq->addroffset++;
    SCI_SendDec16u(pq->addroffset);
    SCI_send('\n');
    pq->front = &(pq->Msgdata[pq->addroffset]);
    if(pq->items == pq->addroffset)
    {  
	  	pq->rear = pq->front = &(pq->Msgdata[0]);
	    pq->addroffset = pq->items = 0;
    }	
    return TRUE;
}   

/*************************************************************/
/*                     �����жϽ��պ���                      */
/*************************************************************/
static T_SciMsg NewMsg;
static uint8 Data_receive = 0;
static uint8 DataRec_Count = 0;
uint8  DataSuccess_Flag = 0;

#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt VectorNumber_Vsci4 receivedata(void) 
{
    Data_receive = SCI_receive();
    if(Data_receive == 0xaa && DataRec_Count == 0 && DataSuccess_Flag == 0) {
       DataRec_Count = 1; 
       NewMsg.MsgHead = Data_receive;
    } else if(DataRec_Count == 1) {
       DataRec_Count = 2; 
       NewMsg.data[0] = Data_receive;
    } else if(DataRec_Count == 2) {
       DataRec_Count = 3; 
       NewMsg.data[1] = Data_receive;
    } else if(DataRec_Count == 3){
       DataRec_Count = 4; 
       NewMsg.data[2] = Data_receive;
    } else if(Data_receive == 0x55 && DataRec_Count == 4){
       DataRec_Count = 0; 
       NewMsg.MsgTail = Data_receive;
       DataSuccess_Flag = 1;
    } 
    if(DataSuccess_Flag == 1) {
       DataSuccess_Flag = 0;
       EnQueue(NewMsg,&MsgLine); 
    }   
}
#pragma CODE_SEG DEFAULT                              