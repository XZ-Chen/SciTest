//-------------------------------------------------------------------------*
//�ļ���: SensorModule.c 					                             	                   *
//˵  ��: ģ/��ת��ģ�������ļ�	  								                         *
//��ʼʱ�䣺  2012��06��30��              			           			           *
//�޶���¼��     		              			           				                 *
//��ע��      ������MC9S12XS128                         	                 *
//-------------------------------------------------------------------------*
#include "SensorModule.h"
#include "CrankModule.h"


//-------------------------------------------------------------------------*
//������: SensorModuleInit                                                 	     *
//��  ��: ��ʼ������������ģ��                                                    * 
//��  ��: ��															                                 *
//��  ��: ��                                                               *
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*



sensor stppos_sensor,pedalpos_sensor,esttemp_sensor,crankspeed_sensor;

void ValueAverage(sensor *pSensor,uint16 nNewValue) 
{
    int8 i;
    uint16 sum;
    
    for(i=pSensor->pointer-1;i>=0;i--)  //rise order sort
    {
        if(nNewValue < pSensor->value[i])
        {
            pSensor->value[i+1] = pSensor->value[i];
            if(i==0) pSensor->value[0] = nNewValue;
        }
        else
        {
            pSensor->value[i+1] = nNewValue;
            break;
        }
    }
    pSensor->pointer++;
    if(pSensor->pointer == 6)
    {
        pSensor->pointer = 2;
        sum=0;
        for(i=2;i<=3;i++)
        {
            sum += pSensor->value[i];
            pSensor->value[i-2] = pSensor->value[i];
        }
        pSensor->value[6] = (sum>>1);
    }
}
void SensorVarInit(sensor *pSensor){
  uint8 i;
  pSensor->status = 0;
  pSensor->pointer = 2;
  for(i = 0;i<7;i++)
    pSensor->value[i] = 0;   
}
void SensorModuleInit(void)
{  
    SensorVarInit(&stppos_sensor);            //�������λ��
    SensorVarInit(&pedalpos_sensor);          //����λ��
    SensorVarInit(&esttemp_sensor);           //�����¶�
    SensorVarInit(&crankspeed_sensor);        //ת��
}


void SensorScan(uint16 *pSensor) 
{
    /*uint16 nNewValue = 0;
    nNewValue = CrankSpeedRead();
    ValueAverage(&crankspeed_sensor,nNewValue);
    nNewValue = ATDRead(AD_STEPPER_CH);
    ValueAverage(&stppos_sensor,nNewValue);
    nNewValue = ATDRead(AD_PEDAL_CH);
    ValueAverage(&pedalpos_sensor,nNewValue);
    
    nTicks++;       
    //max6675��ȡʱ��ļ������̫�̣�̫�̵Ļ����ݸ����Ͳ���仯��һ�½��յ���
    //���������ֵ����ȡ����ĳ�200ms���棬��ȡ����
    if(nTicks == 10) {  //200ms
       nTicks = 0;
       esttemp_sensor.nValue = ExhasutTempRead();
    }
    */
    //*(pSensor+0) = crankspeed_sensor.value[6];
    //*(pSensor+1) = pedalpos_sensor.value[6];
    *(pSensor+0) = 2000;
    *(pSensor+1) = pedalpos_sensor.value[6];
    //*(pSensor+2) = stppos_sensor.value[6];
    //*(pSensor+3) = esttemp_sensor.value[6];
}

