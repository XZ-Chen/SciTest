//-------------------------------------------------------------------------*
//�ļ���:CrankModule.c      					                     	               *
//˵  ��:TIM��ʱ�������ļ�����������ת�ٲ���  	                           *
//��ʼʱ�䣺  2012��07��09��              			           			           *
//�޶���¼��     		              			           				                 *
//��ע��      ������MC9S12XS128                          	                 *
//-------------------------------------------------------------------------*
#include "CrankModule.h"

//-------------------------------------------------------------------------*
//������: CrankModuleInit                                                   	     *
//��  ��: ��ʼ����ʱ��ģ��                                                 * 
//��  ��: ��															                                 *
//��  ��: ��                                                               *
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*
//���䷧��ת�ٻ���ͬ����ϵ
//��OC�в�ͨ����Ϊ�����ڲ��ܵ�����TCNT��������
//ת�ٸ�ʱ��û�������źŽ�����û����
//��·������               
//����NCV1124ת�ٲ���оƬ���Ѿ��������
static GROUP_ACCUM A_crank;

void CrankModuleInit(void){
//-------------------------------------------------------------------------*
//    ���벶׽������Ƚ�PT  	                             	               *
//-------------------------------------------------------------------------* 
    uint8 i;
    A_crank.gearnum = CRANK_GEAR_NUM;//for test
    A_crank.rpm = 0;
    A_crank.average = 0;
    A_crank.index = 0;
    A_crank.accum = 0;
    A_crank.stopcnt = 0;
    for(i=0;i<200;i++)
        A_crank.array[i] = 0;      
    ECT_TSCR1 = 0x80;              //1000   ����ECT����ʱ������
}
uint16 CrankSpeedRead(void) { 
  if(A_crank.stopcnt < 25)   //25*20ms = 500ms��ת���ź�
     A_crank.stopcnt++;
  else if(A_crank.stopcnt == 25) 
     return 0;
  if(A_crank.rpm > CRANK_RPM_MAX || A_crank.rpm < CRANK_RPM_MIN)
     return (30);  
  return (A_crank.rpm); 
}
//��ʱ��ͨ��0���벶׽�ж�    ����Ƶ��Ϊ2.5M  ÿ������0.4us

#pragma CODE_SEG __NEAR_SEG NON_BANKED        
void interrupt VectorNumber_Vectch0 ECT_IC0(void) 
{ 
    //EnableInterrupts; 
    static uint16 u16TCrank = 0;   //��ǰʱ�����ֵ
    static uint16 u16TCrank0 = 0;  //ǰ��ʱ�����ֵ
    uint16 u16DTCrank;             //����ʱ��������ֵ
    ECT_TFLG1_C0F = 1;                 //���жϱ�־λ
    A_crank.stopcnt = 0;
    A_crank.index++;
    if(A_crank.index >= A_crank.gearnum)
    {
        A_crank.index = 0;
        //get the average distance between two gear
        A_crank.average = A_crank.accum/A_crank.gearnum;
    }   
    //get the distance between two gear
  	u16TCrank = ECT_TC0;
  	if(u16TCrank < u16TCrank0) 
  	{
  	    u16DTCrank = 65535 - u16TCrank0 + u16TCrank + 1;
  	}
		else {
		  u16DTCrank = u16TCrank - u16TCrank0;
		}
   	A_crank.accum = A_crank.accum - A_crank.array[A_crank.index] + u16DTCrank;
  	A_crank.array[A_crank.index] = u16DTCrank;
   	u16TCrank0 = u16TCrank;
    if(A_crank.average>0) {
      A_crank.rpm = 185000000/A_crank.average/A_crank.gearnum;
    }
}
#pragma CODE_SEG DEFAULT
   	    


