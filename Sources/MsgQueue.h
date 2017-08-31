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

#define Queue_Size 50
/*
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
Bool DeQueue(T_SciMsg *pMsg,Queue *pq);  */
typedef struct queue{

    T_SciMsg *front;
    T_SciMsg *rear;
    uint16 items;
    uint16 addroffset;
    T_SciMsg  Msgdata[Queue_Size];
}Queue;

static void CopyToQueue(T_SciMsg Msg, Queue *pn);
static void CopyToMsg(Queue *pn, T_SciMsg Msg);
void InitializeQueue(void);
//void SciMsgAddProcess(void);
Bool QueueIsFull(const Queue *pq);
Bool QueueIsEmpty(const Queue *pq);
int QueueItemCount(const Queue *pq);
Bool EnQueue(T_SciMsg Msg,Queue *pq);
Bool DeQueue(T_SciMsg *Msg,Queue *pq);
#endif