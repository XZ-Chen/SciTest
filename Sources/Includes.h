//-------------------------------------------------------------------------*
//�ļ���: Includes.h                                              	       *
//˵  ��: ��ͷ�ļ�,���ļ�����:                                 		         *
//        ������(main)�ļ����õ���ͷ�ļ����ⲿ�����������йس�������       *
//��ʼʱ�䣺  2012��07��05��              			                           *
//�޶���¼��     		              			                                   *
//��ע��      ������MC9S12XS128                			                       *
//-------------------------------------------------------------------------*
#ifndef INCLUDES_H
#define INCLUDES_H
    //1 ͷ�ļ�
    //1.1 ����ͨ��ͷ�ļ�(����ı�)
    #include "typedefine.h"           //���ͱ�������

    //1.2 ����ͨ��ͷ�ļ�(��Ҫ�ı�)
    #include <hidef.h>      /* common defines and macros */
    #include <MC9S12XET256.h>     /* derivative information */
    //1.2 ��������Ӳ������ͷ�ļ�  
    #include "CrankModule.h"
    #include "SensorModule.h"
    #include "GeneralFun.h" 
    #include "DIOModule.h"
    #include "SysTask.h"
    #include "lookup_table.h"
    #include "InjectorModule.h"
    #include "StepperModule.h"
    
    
    //2 �궨��

    //3 ȫ�ֱ�������
#endif