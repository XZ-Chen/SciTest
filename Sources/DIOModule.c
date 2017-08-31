//-------------------------------------------------------------------------*
//�ļ���: DIODodule.c                                                  	   *
//˵  ��: ������������ļ�                                         		     *
//��ʼʱ�䣺  2012��07��02��              			                           *
//�޶���¼��     		              			                                   *
//��ע��      ������MC9S12XS128               			                       *
//-------------------------------------------------------------------------*
#include "DIOModule.h"
#include "GeneralFun.h" 
#include "SPI.h"
#include "SCI.h"




//12·��λ��������ʿ��ؿ�������
static UINT8 *pHDOCtrlPort[12] =    {&PTP,  &PTP,  &PTP,  &PTP,  &PTP,  &PTS, 
                                     &PORTA,&PORTA,&PORTA,&PORTA,&PORTA,&PORTA};
//12·��λ��������ʿ��ؿ������ŷ���ؼĴ���                            
static UINT8 *pHDOCtrlPortDDR[12] = {&DDRP, &DDRP, &DDRP, &DDRP, &DDRP, &DDRS, 
                                     &DDRA, &DDRA, &DDRA, &DDRA, &DDRA, &DDRA};
//A39441   PTP0 PTP1 PTP2 PTP3 PTP4 PA0
//A39442   PA1  PA2  PA3  PA4  PA5  PA6    
static UINT8 HDOCtrlPortMask[12] =  {0x01,  0x02,  0x04,  0x08,  0x10,  0x02,
                                     0x02,  0x04,  0x08,  0x10,  0x20,  0x40};
//4·��λ���ض˿�  PB1 PB2 PB3 PH6                             
static UINT8 *pDIPort[4] =    {&PORTB,&PORTB,&PORTB,&PTIH};
static UINT8 *pDIPortDDR[4] = {&DDRB, &DDRB, &DDRB, &DDRH};
static UINT8 DIPortMask[4] =  {0x02,  0x04,  0x08,   0x40};

//7·С�������ʿ���״̬                                    
static uint8 LDOStatus = 0; 

  
  
                                
//A3944��ʼ��
void A3944Init(void) {
   RESTN_A39441_DDR = 1;
   RESTN_A39442_DDR = 1;
   RESTN_A39441 = 0;
   RESTN_A39442 = 0;
   DelayUs(5);
   RESTN_A39441 = 1;
   RESTN_A39442 = 1;  
}

//L9733��ʼ��
void L9733Init(void){
   LDOStatus = 0;
   RESTN_L9733_DDR = 1;
   RESTN_L9733 = 0;
   DelayUs(5);
   RESTN_L9733 = 1;
}

void DIOModuleInit(void)
{
   UINT8 i;
   A3944Init();
   L9733Init();
   for(i=0;i<12;i++) {                     
     *(pHDOCtrlPortDDR[i]) |= HDOCtrlPortMask[i];//��Ӧ�Ŀ��ƶ˿�����Ϊ���
   }
   for(i=0;i<4;i++) {
     *(pDIPortDDR[i]) &= (~DIPortMask[i]); //��Ӧ�˿�����Ϊ����
   }
   
}
//��λ����ɨ��
uint16 DIRead(uint8 pin){
   uint8 ch;
   if(pin>PIN23_DI)
      return 0xff;
   ch = pin;
   if(*(pDIPort[ch]) & DIPortMask[ch])
      return ON;
   else
      return OFF;     
}
//С�������ʿ������
uint16 LDOOutput(uint8 ch,uint8 val) {
    uint16 cmd;
    if(val == 1)
      LDOStatus = BSET(ch,LDOStatus);
    else
      LDOStatus = BCLR(ch,LDOStatus); 
    cmd = CMD_L9733_OUTPUT | LDOStatus;
    return SPIWriteWord(SPI_L9733,cmd);
}
//��������ʿ������
uint16 HDOOutput(uint8 ch,uint8 val){
   if(val == ON)
      *(pHDOCtrlPort[ch]) |=  HDOCtrlPortMask[ch];
   else
      *(pHDOCtrlPort[ch]) &=  (~HDOCtrlPortMask[ch]);
   return 0;
}
//��λ����ɨ��
void DIScan(uint16 *pDI) 
{
    //*pDI = DIRead(DI_IGSWITCH_PIN);
    *(pDI+1) = DIRead(DI_LNGSWITCH_PIN);
    //*(pDI+1) = OFF;
   
}

void keyScan(uint16 *pDI)
{
    *pDI = DIRead(DI_IGSWITCH_PIN);

}
//����λ����״̬

//���ʿ������
uint16 DOOutput(uint8 pin,uint8 val) {
   if(val != 1 && val != 0)
      return 0;
   if(pin <= PIN49_LDO) {  
      return LDOOutput(pin,val);
   } else if(pin <= PIN56_HDO){
      return HDOOutput(pin - 7,val);
   } 
}


























