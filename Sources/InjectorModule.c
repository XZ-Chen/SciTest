//-------------------------------------------------------------------------*
//�ļ���:InjectorModule.c      					                             	     *
//˵  ��:���䷧�����ļ�											                               *
//��ʼʱ�䣺  2012��07��09��              			           			           *
//�޶���¼��     		              			           				                 *
//��ע��      ������MC9S12XS128                          	                 *
//-------------------------------------------------------------------------*
#include "InjectorModule.h"
#include "CrankModule.h"
static uint16 InjectorIndex = 0;
//static uint16 InjectorPIN[CRANK_CYLINDER_NUM] = {INJECTOR_PIN1,INJECTOR_PIN2,INJECTOR_PIN3,
                      //          INJECTOR_PIN4,INJECTOR_PIN5,INJECTOR_PIN6};
  static uint16 InjectorPIN[CRANK_CYLINDER_NUM] = {INJECTOR_PIN1,INJECTOR_PIN2,INJECTOR_PIN3,
                               INJECTOR_PIN4};
//-------------------------------------------------------------------------*
//������: InjectorModuleInit                                                   	     *
//��  ��: ��ʼ�����䷧                                                 * 
//��  ��: ��															                                 *
//��  ��: ��                                                               *
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*
//A3944 1-6 ��PP0~PP4��PA0
//      7-12��PA1~PA6

void InjectorModuleInit(void)
{
   DOOutput(INJECTOR_PIN1,OFF);
   DOOutput(INJECTOR_PIN2,OFF);
   DOOutput(INJECTOR_PIN3,OFF);
   DOOutput(INJECTOR_PIN4,OFF);
   DOOutput(INJECTOR_PIN5,OFF);
   DOOutput(INJECTOR_PIN6,OFF);
   PITCE_PCE1 = 0;  //PITͨ������ 
   PITCE_PCE2 = 0; //ֹͣ���䷧
          
}
void InjectorWide(uint16 nCycle,uint16 nWide) //����ʱ��
{
    if(nCycle == 0 || nWide == 0) { 
       DOOutput(INJECTOR_PIN1,OFF);
       DOOutput(INJECTOR_PIN2,OFF);
       DOOutput(INJECTOR_PIN3,OFF);
       DOOutput(INJECTOR_PIN4,OFF);
       DOOutput(INJECTOR_PIN5,OFF);
       DOOutput(INJECTOR_PIN6,OFF);
       PITCE_PCE1 = 0;
       PITCE_PCE2 = 0; //ֹͣ���䷧ 
       InjectorIndex = 0;
       return;      
    }
    PITSetCycle(1,nCycle);     //ʱ�� (����)
    PITSetCycle(2,nWide);      //����
    PITCE_PCE1 = 1;             //enable timer channel 1  
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED 
void interrupt VectorNumber_Vpit1 PIT1_ISR(void)                        
{ 
    PITTF = 0x02;    //CLEAR FLAG
    DOOutput(INJECTOR_PIN1,ON);
    DOOutput(INJECTOR_PIN2,ON);
    DOOutput(INJECTOR_PIN3,ON);
    DOOutput(INJECTOR_PIN4,ON);
    DOOutput(INJECTOR_PIN5,ON);
    DOOutput(INJECTOR_PIN6,ON);
    PITCE_PCE2 = 1;             //enable timer channel 2
                                                                               
}
#pragma CODE_SEG DEFAULT

#pragma CODE_SEG __NEAR_SEG NON_BANKED 
void interrupt VectorNumber_Vpit2 PIT2_ISR(void)                        
{  
    PITTF = 0x04;;    //CLEAR FLAG 
    PITCE_PCE2 = 0;             //disable timer channel 2 
    DOOutput(INJECTOR_PIN1,OFF);
    DOOutput(INJECTOR_PIN2,OFF);     
    DOOutput(INJECTOR_PIN3,OFF);
    DOOutput(INJECTOR_PIN4,OFF); 
    DOOutput(INJECTOR_PIN5,OFF);
    DOOutput(INJECTOR_PIN6,OFF);
    //InjectorIndex ++;
    //if(InjectorIndex == CRANK_CYLINDER_NUM)
       //InjectorIndex = 0;                                                                          
}
#pragma CODE_SEG DEFAULT
