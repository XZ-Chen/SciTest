//-------------------------------------------------------------------------*
//�ļ���: ECT.h                                                        	   *
//˵  ��: ��ǿ�Ͷ�ʱ��ͷ�ļ�                                         		   *
//��ʼʱ�䣺  2012��07��02��              			                           *
//�޶���¼��     		              			                                   *
//��ע��      ������MC9S12XS128               			                       *
//-------------------------------------------------------------------------*
#ifndef _PINMAP_H
#define _PINMAP_H

#define PIN1_24V       1
#define PIN2_GND       2
#define PIN3_GND       3
#define PIN4_5V        4
#define PIN36_24VRLY   36

//�ȵ�ż
#define PIN6_TCN       5 //ThemalCouple T-
#define PIN7_TCP       6 //ThemalCouple T+

//CAN�ӿ�
#define PIN7_CANL     7
#define PIN8_CANH     8




//�������
#define PIN11_B1       11   //�������
#define PIN12_A1       12
#define PIN13_A2       13
#define PIN14_B2       14

//6·ͨ��AD
#define PIN15_AD       3
#define PIN16_AD       4 
#define PIN17_AD       5
#define PIN24_AD       11
#define PIN25_AD       12
#define PIN26_AD       13

//2·ѹ���¶�         
#define PIN30_P        7
#define PIN9_NTC       8  //AD8
#define PIN29_P        9
#define PIN10_NTC      10 //AD10
//1·NTCˮ��
#define PIN27_NTCP     6    //ˮ��
#define PIN28_NTCN     28


//ת�ٴ�����
#define PIN18_SPEEDP   18  //SPEED+
#define PIN19_SPEEDN   19  //SPEED-

//4·��λ�������루24V-->5V) 
#define PIN20_DI       0
#define PIN21_DI       3
#define PIN22_DI       2
#define PIN23_DI       3 

//������������
#define PIN31_UEGO_IP   31
#define PIN32_UEGO_VM   32
#define PIN33_UEGO_HN   33 //H-
#define PIN34_UEGO_HP   34 //H+
#define PIN35_UEGO_IA   35 
#define PIN50_UEGO_UN   50 

//7·1A�Ͷ˿��أ��͵�����
#define PIN43_LDO      3
#define PIN44_LDO      2
#define PIN45_LDO      1
#define PIN46_LDO      0
#define PIN47_LDO      4
#define PIN48_LDO      5
#define PIN49_LDO      6

//12·10A�Ͷ˿��أ��ߵ�����
#define PIN37_HDO      7
#define PIN38_HDO      8
#define PIN39_HDO      9
#define PIN40_HDO      10
#define PIN41_HDO      11
#define PIN42_HDO      12
#define PIN51_HDO      13
#define PIN52_HDO      14
#define PIN53_HDO      15 
#define PIN54_HDO      16
#define PIN55_HDO      17
#define PIN56_HDO      18


#define DI_IGSWITCH_PIN   PIN21_DI   //��𿪹�    0��Ч
#define DI_LNGSWITCH_PIN  PIN20_DI   //��Ȼ������  0��Ч

#define DO_MAINRLY_PIN  PIN54_HDO
#define DO_LNGRLY_PIN   PIN53_HDO   


#define AD_PEDAL_CH    PIN15_AD    //����λ��AN3
#define AD_STEPPER_CH  PIN16_AD    //�������λ��AN4 

#define INJECTOR_PIN1 PIN37_HDO
#define INJECTOR_PIN2 PIN38_HDO
#define INJECTOR_PIN3 PIN39_HDO
#define INJECTOR_PIN4 PIN40_HDO
#define INJECTOR_PIN5 PIN51_HDO
#define INJECTOR_PIN6 PIN52_HDO





//-------------------------------------------------------------------------* 


#endif