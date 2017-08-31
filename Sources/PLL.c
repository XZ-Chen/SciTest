//-------------------------------------------------------------------------*
//�ļ���: MCUInit.c                                                    	   *
//˵  ��: оƬ��ʼ���ļ�                                         		       *
//��ʼʱ�䣺  2012��07��01��              			                           *
//�޶���¼��     		              			                                   *
//��ע��      ������MC9S12XS128               			                       *
//-------------------------------------------------------------------------*
#include "PLL.h"
#define BUS_CLOCK		   32000000	   //����Ƶ��
#define OSC_CLOCK		   16000000	   //����Ƶ��
//-------------------------------------------------------------------------* 
//������: PLLInit                                                         *
//��  ��: ���໷��ʼ��                                                     *
//��  ������                                                               * 
//��  ��: ��                                                               * 
//˵  ��: Fvco = 2*Fosc*(SYNDIV+1)/(REFDIV+1)                              *                                                               *
//        Fref = Fosc/(REFDIV+1)                                           *
//        Fpll = Fvco/(2*POSTDIV)                                          *
//        Fbus = Fpll/2                                                    *
//-------------------------------------------------------------------------* 
void PLLInit(void){      //��������Ƶ��Ϊ��40M
    CLKSEL = 0x00;       
    SYNR = 0b01010011;
    REFDV = 0b00000001;   
    POSTDIV = 0b00000000;
    while(!(CRGFLG&0x08));  
    CLKSEL = 0x80;        //ѡ�����໷ʱ�� 
}

/*************************************************************/
/*               ���迪�����ʼ�����໷                      */
/*************************************************************/
void FXINIT_PLL(void) 
{
    CLKSEL &= 0x7f;       //set OSCCLK as sysclk
    PLLCTL &= 0x8F;       //Disable PLL circuit
    CRGINT &= 0xDF;
    
    #if(BUS_CLOCK == 40000000) 
      SYNR = 0x44;
    #elif(BUS_CLOCK == 32000000)
      SYNR = 0x43;     
    #elif(BUS_CLOCK == 24000000)
      SYNR = 0x42;
    #endif 

    REFDV = 0x81;         //PLLCLK=2��OSCCLK��(SYNR+1)/(REFDV+1)��64MHz ,fbus=32M
    PLLCTL =PLLCTL|0x70;  //Enable PLL circuit
    asm NOP;
    asm NOP;
    while(!(CRGFLG&0x08)); //PLLCLK is Locked already
    CLKSEL |= 0x80;        //set PLLCLK as sysclk
}
