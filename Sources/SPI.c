//-------------------------------------------------------------------------*
//�ļ���: SPI.c 					                             	                   *
//˵  ��: SPI����ͨѶ�����ļ�  											                       *
//��ʼʱ�䣺  2012��07��12��              			           			           *
//�޶���¼��     		              			           				                 *
//��ע��      ������MC9S12XS128                          	                 *
//-------------------------------------------------------------------------*
#include "SPI.h"
#include "GeneralFun.h"
//-------------------------------------------------------------------------*
//������: SPIInit                                                  	       *
//��  ��: ��ʼ��SPIģ��                                                    * 
//��  ��: ��															                                 *
//��  ��: ��                                                               *
//˵  ��: A39441,A39442,MAX6675---->SPI0    PE5  PE4  PS7
//                     CJ125------->SPI1 
//                L9733,L9935------>SPI2    PE6  PE7
//-------------------------------------------------------------------------*
void SPIInit(void){
    //SPI���ƼĴ���1
    SPI0CR1 = 0b01010110;    //
    SPI1CR1 = 0b01010110; 
    SPI2CR1 = 0b01011110;    //���������ε���֤������Ҫ���ó�11���ҿް�
    //          ||||||||_____LSBFE:   LSB����ʹ��λ
    //          |||||||______SSOE:    ���ѡ�����ʹ��λ
    //          ||||||_______CPHA:    SPIʱ����λѡ��λ  0�������ز���  1��ż���ز���
    //          |||||________CPOL:    SPIʱ�Ӽ���λ 1 ����Ϊ�� 0 ����Ϊ��
    //          ||||_________MSTR:    SPI����ģʽλ Master = 1 Slave = 0
    //          |||__________SPTIE:   SPI���ݴ����ж�ʹ�� 1 ʹ�� 0 ��ֹ 
    //          ||___________SPE:     SPIϵͳʹ��λ 1 ʹ�� 0 ��ֹ
    //          |____________SPIE:    SPI�ж�ʹ��λ 1 ʹ�� 0 ��ֹ
    
    //SPI���ƼĴ���2
    SPI0CR2 = 0b01000000;
    SPI1CR2 = 0b01010000; 
    SPI2CR2 = 0b01000000; 
    //          ||||||||_____SPC0:    �������ſ���λ 1 ˫�� 0 ��ͨģʽ
    //          |||||||______SPISWAI: �ڵȴ�ģʽ��SPIֹͣλ 1 ���� 0 ֹͣ
    //          ||||||_______0
    //          |||||________BIDIROE: ��˫��ģʽ���������ʹ��λ
    //          ||||_________MODFEN:  ģʽ���Ϲ���ʹ��λ 1 ʹ�� 0 ��ֹ
    //          |||__________0
    //          ||___________XFRW:    λ��ѡ�� 1 16λ 0 8λ   
    //          |____________0

    //SPI������ѡ��Ĵ���
    SPI0BR = 0b01000001;     //       F = 2M ��Ƶϵ�� = (SPPR+1)*2^(SPR+1) = 20
    SPI1BR = 0b01000010;     //       F = 1M ��Ƶϵ�� = (SPPR+1)*2^(SPR+1) = 40
    SPI2BR = 0b01000010;     //       F = 1M
    //         ||||||||______SPR0:    SPI������ѡ��λ
    //         |||||||_______SPR1:    bus = 40mhz
    //         ||||||________SPR2:
    //         |||||_________0
    //         ||||__________SPPR0:   SPI������Ԥѡ��λ
    //         |||___________SPPR1: 
    //         ||____________SPPR2: 
    //         |_____________0
    
    //SPI���ݼĴ���
//  SPI_SR = 0b10110000;
    //         ||||||||______0
    //         |||||||_______0
    //         ||||||________0
    //         |||||_________0
    //         ||||__________MODF:    SPIģʽ�����־λ 1 ģʽ������ 0 ģʽ���󲻷���
    //         |||___________SPTEF:   SPI������жϱ�־λ 1 SPI0DRΪ�� 0 SPI0DR����Ϊ��   
    //         ||____________0 
    //         |_____________SPIF:    SPI�ж�����λ 1 �����ݸ��Ƶ�SPI0DR 0 ���ݴ���δ���
    DDRS |= 0xf0;
    DDRH |= 0xff; 
    MODRR_MODRR4 = 0; //SPI0--->PS4 PS5 PS6 PS7
    MODRR_MODRR5 = 1; //SPI1--->PH0 PH1 PH2 PH3
    MODRR_MODRR6 = 1; //SPI2--->PH4 PH5 PH6 PH7
    
    //DDRE |= 0xf0;  //PE4,PE5,PE6,PE7 set as ouput
    SPI_CSN_L9733_DDR = 1;
    SPI_CSN_L9935_DDR = 1;
    SPI_CSN_A39441_DDR = 1;
    SPI_CSN_A39442_DDR = 1;
    SPI_CSN_MAX6675_DDR = 1;
    
    SPI_CSN_MAX6675 = 1;
    SPI_CSN_L9733 = 1;
    SPI_CSN_L9935 = 1;
    SPI_CSN_A39441 = 1;
    SPI_CSN_A39442 = 1;
   
}

//-----------------------------------------------------------------------//
//
//------------------------------------------------------------------------//
//MAX6675�������
UINT16 SPIReadWord(UINT8 id,UINT16 cmd) {
   UINT16 ret = 0;
   DisableInterrupts;
   switch(id) {
      case SPI_MAX6675:
        SPI_CSN_MAX6675 = 0;
        while(!SPI0SR_SPTEF);
        SPI0DR = cmd;
        while(SPI0SR_SPTEF); 
        while(!SPI0SR_SPIF);
        ret = SPI0DR;
        SPI_CSN_MAX6675 = 1;
      break; 
           
      case SPI_A39441:
        SPI_CSN_A39441 = 0;
        while(!SPI0SR_SPTEF);
        SPI0DR = cmd;
        while(SPI0SR_SPTEF);
        while(!SPI0SR_SPIF);
        ret = SPI0DR; 
        SPI_CSN_A39441 = 1;
      break;
      
      case SPI_A39442:
        SPI_CSN_A39442 = 0;
        while(!SPI0SR_SPTEF);
        SPI0DR = cmd;
        while(SPI0SR_SPTEF); 
        while(!SPI0SR_SPIF);
        ret = SPI0DR; 
        SPI_CSN_A39442 = 1;
      break;
      
      case SPI_CJ125:
        while(!SPI1SR_SPTEF);
        SPI1DR = cmd;    
        while(SPI1SR_SPTEF); 
        while(!SPI1SR_SPIF);
        ret = SPI1DR;
      break;
      
      case SPI_L9733:
        SPI2CR1_LSBFE = 1;
        SPI2CR2_XFRW = 1;  //ת����8λ�ֿ�
        SPI_CSN_L9733 = 0;   //оƬѡ��
        while(!SPI2SR_SPTEF);//�ȴ�����
        SPI2DRL = cmd;       //������
        while(SPI2SR_SPTEF);   //�ȴ��������
        while(SPI2SR_SPIF != 1);  //�ȴ����յ�����
        ret = SPI2DR;          //��������
        SPI_CSN_L9733 = 1;     //оƬ�ͷ� 
      break;
      
      case SPI_L9935:
        SPI2CR1_LSBFE = 0;
        SPI2CR2_XFRW = 0;  //ת����8λ�ֿ�
        SPI_CSN_L9935 = 0;   //оƬѡ��
        while(!SPI2SR_SPTEF);//�ȴ�����
        SPI2DRL = cmd & 0x00ff; //������
        while(SPI2SR_SPTEF);   //�ȴ��������
        while(SPI2SR_SPIF != 1);  //�ȴ����յ�����
        ret = SPI2DRL;          //��������   ret = 0xff
        SPI_CSN_L9935 = 1;     //оƬ�ͷ�
      break;

   }
   EnableInterrupts;
   return ret;
}


 


    
   