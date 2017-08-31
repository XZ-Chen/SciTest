//-------------------------------------------------------------------------*
//�ļ���: DataFlash.h                                                      *
//˵  ��: DataFlashͷ�ļ�                                         		     *
//��ʼʱ�䣺  2012��10��02��              			                           *
//�޶���¼��     		              			                                   *
//��ע��      ������MC9S12XS128               			                       *
//-------------------------------------------------------------------------*
#ifndef _DATAFLASH_H
#define _DATAFLASH_H

//1 ͷ�ļ�
#include "typedefine.h"           //���ͱ�������
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 

#define READword(address)     ((unsigned int)(*(volatile unsigned int *__near)(address)))
                                                                       
#define DFLASH_LOWEST_START_PAGE        0x00        //����data flash����ʼҳ
#define DFLASH_START                    0x00100000  //����data flash����ʼ��ַ
#define DFLASH_PAGE_SIZE                0x0400      //����data flash�Ĵ�СΪ1K.
#define DFLASH_PAGE_WINDOW_START        0x0800      //����data flashҳ�洰�ڵ���ʼ��ַ
#define LEDCPU PORTB_PB0
#define LEDCPU_dir DDRB_DDRB0

void DFlashInit(void);
word DFlashRead (word destination);
void DFlashErase(word ADDR16);

#endif