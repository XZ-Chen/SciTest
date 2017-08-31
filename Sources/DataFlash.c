//-------------------------------------------------------------------------*
//�ļ���: DataFlash.c                                                      *
//˵  ��: DataFlash�����ļ�                                         		     *
//��ʼʱ�䣺  2012��10��02��              			                           *
//�޶���¼��     		              			                                   *
//��ע��      ������MC9S12XS128               			                       *
//-------------------------------------------------------------------------*

#include "DataFlash.h"

//-------------------------------------------------------------------------* 
//������: DFlashInit                                                         *
//��  ��: DFlash��ʼ��                                                        *
//��  ������                                                               * 
//��  ��: ��                                                               * 
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*  
//���ģ�龭�����ԣ�����ûʲô����

uint16  Buffer[]={0x1111,0x2222,0x3333,0x4444};//���ݻ�������ֻ��һ��д���ĸ�����
uint16  data_Address=0x0000;
uint16  date_read[4];


          
/*************************************************************/
/*                      ��ʼ��DFLASH                         */
/*************************************************************/
void DFlashInit(void)
{
   while(FSTAT_CCIF==0);            //�ȴ����ڴ����FLASH�������
  // FCLKDIV=0x0F;                    //�ⲿ����Ϊ16M.FLASHʱ�Ӳ�����1M����������ֲ�
  // FCLKDIV=0x05;                    //�ⲿ����Ϊ6M.FLASHʱ�Ӳ�����1M����������ֲ�
   FCLKDIV=0x03;                    //�ⲿ����Ϊ4M.FLASHʱ�Ӳ�����1M����������ֲ�
   FCNFG=0x00;                      //��ֹ�ж�
   while(FCLKDIV_FDIVLD==0);        //�ȴ�ʱ�����óɹ�
}

/*************************************************************/
/*                     ��DFLASHд������                      */
/*************************************************************/
//ÿ������4��word����8���ֽ�һ����д��
void DFlashWrite(word ADDR16)
{
    while(FSTAT_CCIF==0); 
    if(FSTAT_ACCERR)           //�жϲ������־λ��
        FSTAT_ACCERR=1;
    if(FSTAT_FPVIOL)           //�жϲ������־λ��
        FSTAT_FPVIOL=1;
    FCCOBIX_CCOBIX=0x00; 
    FCCOB=0x1110;         //д������͸�λ��ַ
    FCCOBIX_CCOBIX=0x01;  //��ַ��16λ
    FCCOB=ADDR16;         //д���16λ��ַ
    FCCOBIX_CCOBIX=0x02;  //д���һ������
    FCCOB=Buffer[0];
    FCCOBIX_CCOBIX=0x03;  //д��ڶ�������
    FCCOB=Buffer[1];
    FCCOBIX_CCOBIX=0x04;  //д�����������
    FCCOB=Buffer[2];
    FCCOBIX_CCOBIX=0x05;  //д����ĸ�����
    FCCOB=Buffer[3];  
      
    FSTAT_CCIF=1;         //д��ִ������
    while(FSTAT_CCIF==0); //�ȴ�ִ�����
}

/*************************************************************/
/*                     ��DFLASH��ȡ����                      */
/*************************************************************/
word DFlashRead (word destination)
{
    byte   lastepage;          //���ڴ洢EPAGE��ֵ
    byte   epage;              //���ڼ���EPAGE��ֵ
    unsigned int data;         //��ȡ��������

    lastepage = EPAGE;   //����EPAGE��ֵ

    epage = (byte)((DFLASH_LOWEST_START_PAGE)+(destination >>10));   //����EPAGE
    EPAGE=epage;                                                     //��EPAGE��ֵ
 
    data = READword((destination & (DFLASH_PAGE_SIZE - 1)) + DFLASH_PAGE_WINDOW_START);  //��ȡҳ�洰���е�����

    EPAGE= lastepage;       //�ָ�EPAGE��ֵ

    return(data);
}

/*************************************************************/
/*                    ����DFLASH��һ������                   */
/*************************************************************/
void DFlashErase(word ADDR16)
{   
  while(FSTAT_CCIF==0);
  if(FSTAT_ACCERR)           //�жϲ������־λ��
      FSTAT_ACCERR=1;
  if(FSTAT_FPVIOL)           //�жϲ������־λ��
      FSTAT_FPVIOL=1;
  
  FCCOBIX_CCOBIX=0x00;
  FCCOB=0x1210;           //д���������͸�λ��ַ
  FCCOBIX_CCOBIX=0x01;   
  FCCOB=ADDR16;           //д���16λ�ĵ�ַ
  FSTAT_CCIF=1;           //����ִ������
  while(FSTAT_CCIF==0);   //�ȴ�ִ�����
}


