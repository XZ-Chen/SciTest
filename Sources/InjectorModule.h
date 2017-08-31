//-------------------------------------------------------------------------*
//�ļ���: InjectorModule.h      					                             	   *
//˵  ��: ���䷧����ͷ�ļ�											                           *
//��ʼʱ�䣺  2012��07��09��              			           			           *
//�޶���¼��     		              			           				                 *
//��ע��      ������MC9S12XS128                          	                 *
//-------------------------------------------------------------------------*
#ifndef _INJECTORMODULE_H_
#define _INJECTORMODULE_H_

//1��ͷ�ļ�   
#include "PIT.h"
#include "typedefine.h"           //���ͱ�������
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 
#include "PinMap.h"
#include "DIOModule.h"
//-------------------------------------------------------------------------*
//������: InjectorModuleInit                                               *
//��  ��: ��ʼ�����䷧ģ��                                                 * 
//��  ��: ��															                                 *
//��  ��: ��                                                               *
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*





void InjectorModuleInit(void);
void InjectorWide(uint16 nCycle,uint16 nWide); 
#define InjectorOff() InjectorWide(0,0) 

#endif