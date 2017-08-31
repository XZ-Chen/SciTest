//-------------------------------------------------------------------------*
//�ļ���: MSCAN.c 					                             	                 *
//˵  ��: MACAN�����ļ�											                               *
//��ʼʱ�䣺  2012��07��20��              			           			           *
//�޶���¼��     		              			           				                 *
//��ע��      ������MC9S12XS128                         	                 *
//-------------------------------------------------------------------------*
#include "MSCAN.h"

extern SYS_PARA sys_para;
#define AddrSysParaBgn  sys_para.data
//-------------------------------------------------------------------------*
//������: CAN_Init                                                  	     *
//��  ��: ��ʼ��CANģ��                                                    * 
//��  ��: ��															                                 *
//��  ��: ��                                                               *
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*
void MSCANInit(void){
    MODRR_MODRR0 = 0;   //ȷ��CAN0 ��ӦPM0 PM1
    MODRR_MODRR1 = 0;
    CAN0CTL1_CANE = 1; 
    CAN0CTL0_INITRQ = 1;
    while(CAN0CTL1_INITAK == 0);
    CAN0IDAC = 0x20;
    CAN0IDMR0 = 0xff;
    CAN0IDMR1 = 0xff;
    CAN0IDMR2 = 0xff;
    CAN0IDMR3 = 0xff;
    CAN0IDMR4 = 0xff;
    CAN0IDMR5 = 0xff;
    CAN0IDMR6 = 0xff;
    CAN0IDMR7 = 0xff;
    //����ʱ��
    //ͬ����ת���Ϊ1,Ԥ��Ƶ����Ϊ6����λ�������ó� 100kbps
    //bit.7-6=01��ͬ����ת���Ϊ2��bit.5-0=000101,Ԥ��Ƶ����Ϊ6
    //CAN0BTR0 = 0x03;      //6M����Ԥ��Ƶֵ6  4M����Ԥ��Ƶֵ4
    CAN0BTR0 = 0x03;      //1��ͬ����ת��� 6M����Ԥ��Ƶֵ6  4M����Ԥ��Ƶֵ4
    //bit.7=0�����β�����bit.6-4=010,ʱ���2Ϊ3��bit.3-0=0101,
    //ʱ���1Ϊ6��0b00100101����λ����=1M/10=100kbps  625kbps
    CAN0BTR1 = 0x25;
    CAN0CTL1_CLKSRC = 0;  //�����ⲿ����ʱ�� 4M
    //CAN0CTL1_CLKSRC = 1;  //��������ʱ�� 40M
    CAN0CTL1_LISTEN = 0;  //����ģʽ��ֹ
    CAN0CTL1_LOOPB = 0;   //�ر��Ի�����ģʽ

    CAN0CTL0_INITRQ = 0;
    while(CAN0CTL1_INITAK == 1);
    while(!CAN0CTL0_SYNCH);
    CAN0RIER_RXFIE = 0;     //�����ж�     
}

//-------------------------------------------------------------------------*
//������: CAN_TX                                                     	     *
//��  ��: ��ʼ��CAN����ģ��                                                * 
//��  ��: ��															                                 *
//��  ��: ��                                                               *
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*

Bool MSCANSendMsg(can_msg msg)
{
    unsigned char n_tx_buf, i;
    
    // ������ݳ���
    if(msg.len > MAX_LEN)
      return(FALSE);

    // ���ͬ��״̬
    if(!(CAN0CTL0&0x10))
      return(FALSE);

    n_tx_buf = 0;
    do
    {
      // Ѱ�ҿ��з��ͻ�����
      CAN0TBSEL=CAN0TFLG;
      n_tx_buf=CAN0TBSEL;
    }while(!n_tx_buf); 
    
    // дID��
    CAN0TXIDR0 = (unsigned char)(msg.id>>3);
    CAN0TXIDR1 = (unsigned char)(msg.id<<5);     
    // д����
    for(i = 0; i < msg.len; i++)
      *((&CAN0TXDSR0)+i) = msg.data[i];
      
    //д���ݳ���
    CAN0TXDLR = msg.len; 
    
    // ���ȼ�
    CAN0TXTBPR = msg.prty;
    
    //�巢�ͱ�־��׼���÷���
    CAN0TFLG = n_tx_buf;
    
    return(TRUE);
}
/////////////////////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------------------------
// MSCAN ��������
/////////////////////////////////////////////////////////////////////////////////////////
Bool MSCANGetMsg(can_msg *pmsg)
{
  
  unsigned char i;

  // ����Ƿ��յ���Ϣ
  if(!(CAN0RFLG&0x01))
    return(FALSE);
  
  
  if(CAN0RXIDR1&0x08)
 
    return(FALSE);

  // ��ȡID��
  pmsg->id = (unsigned int)(CAN0RXIDR0<<3) | 
            (unsigned char)(CAN0RXIDR1>>5);
  
  if(CAN0RXIDR1&0x10)   //��ȡԶ��֡��־
    pmsg->RTR = TRUE;
  else
    pmsg->RTR = FALSE;
  
  // �����ݳ���
  pmsg->len = CAN0RXDLR;
  
  //  ������
  for(i = 0; i < pmsg->len; i++)
    pmsg->data[i] = *((&CAN0RXDSR0)+i);

  // ����ձ�־��׼���ý���
  CAN0RFLG = 0x01;
  
  return(TRUE);
    
}

/////////////////////////////////////////////////////////////////////////////////////////
// MSCANCheckRcvdMsg
/////////////////////////////////////////////////////////////////////////////////////////
Bool MSCANCheckRcvdMsg(void)
{

  //��ѯ���յ�����
  if(CAN0RFLG&0x01)
    return(TRUE);
  else return(FALSE);
  
}

////////////////////////////////////////////////////////////////////////////////
void MSCANMsgProcess(can_msg msg) {
   if(msg.id != 1)
      return;
   if(msg.len != 5)
      return;
   if(msg.data[0] != 0 && msg.data[0]!= 1)
      return;      
   if(msg.data[0] == 1){
      *(AddrSysParaBgn + msg.data[1]) =  (msg.data[3] << 8) | msg.data[2]; //��8λ 
   }      
   msg.data[2] = *(AddrSysParaBgn + msg.data[1])&0x00ff; //��8λ
   msg.data[3] = *(AddrSysParaBgn + msg.data[1])>>8;     //��8λ
   msg.data[4] = msg.data[0] + msg.data[1] + msg.data[2] + msg.data[3]; 
   MSCANSendMsg(msg); 
}

/////////////////////////////////////////////////////////////////////////////////
can_msg msg;
void MSCANProcess(void){
   if(MSCANCheckRcvdMsg()) {
       if(MSCANGetMsg(&msg)) 
       {
           MSCANMsgProcess(msg);
       }
   }
}