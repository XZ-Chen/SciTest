//-------------------------------------------------------------------------*
//�ļ���: SPI.h 					                             	                   *
//˵  ��: SPI����ͨѶ����ͷ�ļ�											                       *
//��ʼʱ�䣺  2012��07��12��              			           			           *
//�޶���¼��     		              			           				                 *
//��ע��      ������MC9S12XS128                          	                 *
//-------------------------------------------------------------------------*
#ifndef _SPI_H_           //��ֹ�ظ�����
#define _SPI_H_

//1��ͷ�ļ�   
#include "typedefine.h"           //���ͱ�������
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 

#define SPI_MAX6675    1
#define SPI_A39441     2
#define SPI_A39442     3
#define SPI_CJ125      4
#define SPI_L9935      5
#define SPI_L9733      6


#define SPI_CSN_L9935      PORTE_PE7
#define SPI_CSN_L9733      PORTE_PE6
#define SPI_CSN_MAX6675    PORTE_PE5    //   SPI_CSN_A39441
#define SPI_CSN_A39442     PTS_PTS0
#define SPI_CSN_A39441     PTS_PTS7

#define SPI_CSN_L9935_DDR    DDRE_DDRE7
#define SPI_CSN_L9733_DDR    DDRE_DDRE6
#define SPI_CSN_MAX6675_DDR  DDRE_DDRE5  //  SPI_CSN_A39441_DDR
#define SPI_CSN_A39442_DDR   DDRS_DDRS0
#define SPI_CSN_A39441_DDR   DDRS_DDRS7



//2  �궨��


//-------------------------------------------------------------------------*
//������: SPIInit                                                  	       *
//��  ��: ��ʼ��SPIģ��                                                    * 
//��  ��: ��															                                 *
//��  ��: ��                                                               *
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*
void SPIInit(void);
    
//-----------------------------------------------------------------------*
//������: SPIReadWord                                                    *
 //��  ��: ��SPI����һ���ֽڵ�����                                       *
//��  ��: ��                                                             *
//��  ��: ���յ�����(������ʧ��,����0xff)                                *
//˵  ��: ��                                                             *
//-----------------------------------------------------------------------* 
UINT16 SPIReadWord(UINT8 id,UINT16 cmd);
#define SPIWriteWord(id,cmd) (SPIReadWord(id,cmd))
        
   

#endif



