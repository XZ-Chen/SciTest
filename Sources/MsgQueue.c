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
#define MAXQUEUE 10
extern uint8  DataSuccess_Flag;
extern T_SciMsg NewMsg;
extern Queue MsgLine;
/*************************************************************/
/*                     ��ʼ������                            */
/*************************************************************/
void InitializeQueue(Queue *pq) {

    pq->front = pq->rear = NULL;
    pq->items = 0;
}
/*************************************************************/
/*                     �ж϶���״̬                          */
/*************************************************************/
Bool QueueIsFull(const Queue *pq){
    
    return pq->items == MAXQUEUE;
}

Bool QueueIsEmpty(const Queue *pq){

    return pq->items == 0;
}
int QueueItemCount(const Queue *pq){

    return pq->items;
}
/*************************************************************/
/*                     �����и�����Ŀ                        */
/*************************************************************/
static void CopyToNode(T_SciMsg Msg, Node *pn){
   
   int i;
   pn->SciMsg.MsgHead = Msg.MsgHead;
   pn->SciMsg.MsgTail = Msg.MsgTail; 
   for(i=0;i<=2;i++) 
      pn->SciMsg.data[i] = Msg.data[i];
}
static void CopyToMsg(Node *pn, T_SciMsg *Msg){
   
   int j;
   Msg->MsgHead = pn->SciMsg.MsgHead;
   Msg->MsgTail = pn->SciMsg.MsgTail; 
   for(j=0;j<=2;j++)
      Msg->data[j] = pn->SciMsg.data[j];
}
/*************************************************************/
/*                     �����������Ŀ                        */
/*************************************************************/
Bool EnQueue(T_SciMsg Msg,Queue *pq) {
    Node *pnew;
    if(QueueIsFull(pq))
        return FALSE;
    CopyToNode(Msg, pnew);  
    pnew->next = NULL;
    if(QueueIsEmpty(pq))
        pq->front = pnew; //���ݰ����ڶ����׶�
    else 
        pq->rear->next = pnew;  //���ӵ�����β��
    pq->rear = pnew;            //��¼����β�˵�λ��
    pq->items++;                //������Ŀ��������1
    return TRUE;
    
}
/*************************************************************/
/*                     �Ӷ��ж�ȡ��Ŀ                        */
/*************************************************************/
Bool DeQueue(T_SciMsg *Msg,Queue *pq) {
    //Node *pt;
    if(QueueIsEmpty(pq))
        return FALSE;
    CopyToMsg(pq->front, Msg);
    //pt =pq->front;
    
    pq->front = pq->front->next;
    pq->items--;                //������Ŀ��������1
    if(pq->items == 0)
        pq->rear = NULL;
    return TRUE;
}   
/*************************************************************/
/*                     �Ӷ���ȡ����                          */
/*************************************************************/
T_SciMsg ReadMsg;
Bool SciMsgReadProcess(void){
     return DeQueue(&ReadMsg,&MsgLine);
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