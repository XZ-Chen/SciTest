/*---------------------------------------------------------*/
/************************************************************
//函数名: KeyInterrupt                                                  	   *
//功  能: 脉宽选择按键                                                 * 
//参  数: 无															                               *
//返  回: 无                                                             *
//说  明: 无 
************************************************************/
/*---------------------------------------------------------*/
#ifndef _MsgQueue_H_           //防止重复定义
#define _MsgQueue_H_

#include "typedefine.h"           //类型别名定义
#include "SCI.h"



typedef struct node {

    T_SciMsg SciMsg;
    struct node * next;
}Node;

typedef struct queue{

    Node *front;
    Node *rear;
    int items;
}Queue;

static void CopyToNode(T_SciMsg Msg, Node *pn);
static void CopyToMsg(Node *pn, T_SciMsg Msg);
void InitializeQueue(Queue *pq);
Bool QueueIsFull(const Queue *pq);
Bool QueueIsEmpty(const Queue *pq);
int QueueItemCount(const Queue *pq);
Bool EnQueue(T_SciMsg Msg,Queue *pq);
Bool DeQueue(T_SciMsg *pMsg,Queue *pq);

void SciMsgAddProcess(void);


#endif