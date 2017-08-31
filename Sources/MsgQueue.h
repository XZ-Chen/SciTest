/*---------------------------------------------------------*/
/************************************************************
//������: KeyInterrupt                                                  	   *
//��  ��: ����ѡ�񰴼�                                                 * 
//��  ��: ��															                               *
//��  ��: ��                                                             *
//˵  ��: �� 
************************************************************/
/*---------------------------------------------------------*/
#ifndef _MsgQueue_H_           //��ֹ�ظ�����
#define _MsgQueue_H_

#include "typedefine.h"           //���ͱ�������
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