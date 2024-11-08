/*
 * main.c
 *
 *  Created on: 2024��9��23��
 *      Author: PENG LI
 */
#include "CoreOpt.h"
#include "device.h"
#include "user_gpio.h"
#include "user_cla.h"
#include "user_adc.h"
#include "user_epwm.h"
#include "user_cputick.h"
#include "user_cmpss.h"
#include "user_temp.h"
#include "user_cur.h"
#include "user_sci.h"
#include "user_watchdog.h"
#include "user_interface.h"

#include "user_can.h"

#include "Uart_Bsp.h"
#include "DcdcTask.h"

/******* APP include *******/
#include "Gpio_Bsp.h"
#include "TaskManager.h"
#include "H3GSignal_QS.h"
#include "SignalManage.h"
#include "systemtask.h"
#include "com_manager.h"
#include "Rs232_Manager.h"
#include "AlarmManager.h"
/**
 * main.c
 */



uint8_t initializedflag=0;
//static U8 TIMEhuasu[2] = {0,0};
extern TTimeEvent EventTime;
extern DeviceInfo deviceInfo;

/* ���񴴽�������    �ݶ�ÿ100usɨ������һ�� */
void Task_Init(void)
{
    Uart_Arry_Init();

//     uint16_T U16Value=0;
//     GetSigVal(H3G_B48_MODE, &U16Value); //��ȡB48����ģʽ
//     if ((U16Value & 0x0001) == 0x0001) //�����ǰ�豸�������豸
//     {
//       if ((U16Value & 0x0002) == 0x0000) //�����485Ӳ��ģʽ
//       {
 //        (void)SetCycleTask_NoParam(Master_Serial485_Communicat_function, TIME60MS);
//       }
//       else
//       {
//        // (void)CreateScanProg(Can0_DataDeal);
//        // (void)SetCycleTask_NoParam(Can0_ReceiveMsg_timeout, TIME10MS);
//       }

//     }
//     else if ((U16Value & 0x0001) == 0x0000) //�����ǰ�豸�������豸
//     {
//       if ((U16Value & 0x0002) == 0x0000) //�����485Ӳ��ģʽ
//       {
//       //  (void)SetCycleTask_NoParam(Slave_Serial485_Communicat_function, TIME40MS);
//       }
//       else
//       {
//       //  (void)CreateScanProg(Can0_DataDeal);
//       //  (void)SetCycleTask_NoParam(Can0_ReceiveMsg_timeout, TIME10MS);
//       }
//     }

//    SetCycleTask_NoParam(DCDC_Contrl_Step,TIME500US);//�ϸ�֤100us����һ��
//    SetCycleTask_NoParam(ADCTask, TIME500US);//�ϸ�֤100us����һ��

 //     SetCycleTask_NoParam(DCDC_CONDITION,TIME1MS);//1ms����һ��
//       SetCycleTask_NoParam(SCANKeyBUT,TIME10MS);//10ms����һ��

//      SetCycleTask_NoParam(EPWMDriveTask, TIME500US);  //PWM�ײ���������
 //     SetCycleTask_NoParam(ADCTask, TIME100US);
//    SetCycleTask_NoParam(TempTask, TIME1S);
//    SetCycleTask_NoParam(CurCalcTask, TIME10MS);

//     /*��������*/
//     SetCycleTask_NoParam(AutoConfigMission, TIME40MS /*TASK_AUTO_CONFIG_TIME*/ );
//     /*��ʷ���ݴ洢*/
//     SetCycleTask_NoParam(DataStorage_Main, TIME1S /*TIME100MS*/ );
//     /*GPIO����*/
//     SetCycleTask_NoParam(GPIO_Main, TIME100MS /*TASK_GPIO_TIME*/ );
//     /*Rs485Э��*/
//     SetCycleTask_NoParam(Rs485_Manager_Main, TIME40MS /*TIME4MS*/ );
//     /*������ȡ*/
//     SetCycleTask_NoParam(CurrentUpdate, TIME2S /*TIME200MS*/ );
//     /*soc����*/
//     (void)SetCycleTask_NoParam(Soc_Main, TIME10S /*TIME1S*/ );
//     /*367307����*/
//     (void)SetCycleTask_NoParam(BatInfoTask, TIME100MS /* AFE_TASK_CYCLE */ );
//     /*�����ѹ���¶�*/
//     (void)SetCycleTask_NoParam(Get_Volt_Temp, TIME2S /*TIME200MS*/ );
//     /*RTC����*/
//     (void)SetCycleTask_NoParam(Task_RTC_Main, TIME2S /*TIME200MS*/ );
//     /*���߹���*/
// //    SetCycleTask_NoParam(SystemTask, TIME500MS);
//     /*led��������*/
//     (void)SetCycleTask_NoParam(led_ctrl_step, TIME100MS /*TIME100MS*/ );

//     /*��������*/
//     (void)DelayTask_NoParam(Delay_Task_AlarmManager, TIME1_2S,0);  //����������ʱ1.2sִ��
//     /*������*/
//     (void)DelayTask_NoParam(Delay_Task_ChgManager, TIME2_6S,1); //��ŵ����������ʱ2.6sִ��

//     /*������װ����У׼*/
//     (void)SetCycleTask_NoParam(CurCailbTask, TIME4S /*TIME400MS*/ );

// //    SetCycleTask_NoParam(test_PWM, 10);   //only for test
//         SetCycleTask_NoParam(CMPSStest, 10000); //1S �Ƚ�������
// //    SetCycleTask_NoParam(test_sci, 20000);//

    initializedflag=1;
}




int main(void)
{
    CoreInit();
    Interrupt_initModule();// Initializes PIE and clear PIE registers. Disables CPU interrupts. and clear all CPU interrupt flags.
    Interrupt_initVectorTable();// Initialize the PIE vector table with pointers to the shell interrupt     Service Routines (ISR).
    /************ USER CODE BEGIN **************/
    InitTaskVariable();

    /************ USER CODE END **************/
    UserInitFuncRegster();// register user initialize handle (not necessary)
    /* Initialize gpio */
    InitGPIO();
    //ReadDeviceAddr();
    /* Initialize adc */
    InitADCPara();
    InitADC();
    /* Initialize timer2 */
    InitCPUTimer2();
    EnableCPUTimer2();
    /* Initialize timer1 */
    InitCPUTimer1();
    EnableCPUTimer1();
    /* Initialize timer0 */
    InitCPUTimer0();
    EnableCPUTimer0();
    /* Initialize sci */
    InitSCI();
    /* Initialize cmpss */
    InitCMPSS();
    /* Initialize epwm */
    InitEPWMPara();
    InitEPWM();
    /* Initialize epwm trip-zone function */
    InitEPWMTZFunction();
    /* Initialize current calc */
    InitCurCalc();
    /* Initialize watchdog */
    InitWatchdog();
    /* Initialize cla */
    InitCLA();
    InitCLAPara();  //��ʼ����ADvaluesת��Ϊʵ��ֵ
  // StartCLATasks();


    UserISRFuncRegster();// register ISR callback function (not necessary)
    Interrupt_enableMaster();// Enables CPU interrupts
    /************ USER CODE BEGIN **************/


    /************ USER CODE END **************/
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM
    /************ USER CODE BEGIN **************/
   // EEP_Check();
    SomeSigValInit();//�˺�����ʼ��һ��Ҫ���У���Ȼ��ʼ��RET�㣬�Լ�����GetSigVal()/SetSigVal()�����������⡣


    Usart_Init();   //ʵ�ʲ����ô�����������ͨCOM��

    //  RTCInit();
    //  SoftwareVersion();

    Rs485_Manager_Init();



    dcdc_sp_proct_init();       //DCDCtask��
    initialize_protection_state();  //��ʼ������״̬
    initialize_protection_parameters(); //��ʼ���׻�����
    /***** Start Module *****/
    StartADC();
    StartSCI();
    StartEPWMTZFunction();
    StartEPWM();
    StartCLATasks();
  //  StopAllEPWMOutput();
    Relay_Init();//�̵����ϵ��ʼ�� ���Ƽ̵������֣�����PWM��ʱ�򲻿���,�������Լ̵�����ʱ�򣬹ر�epwm�������
    DC_DRI_CTL_ON();
    LED_DSP_ON();//DSP_LEDָʾ�ƴ�
    Task_Init();

    DC_DRI_CTL_ON();    //����� ��EPWM�źŸ������ �������6us

    HAL_Delay(1);       //�ӳ�1ms

    test_PWM();    //����PWM�����Լ̵���Rel��ʱ����Ҫע�͵���


    /************ USER CODE END **************/
     while(1)
     {


         if (DCDCTaskCycleCnt4_done == TRUE)    //40usִ��һ�εĶ�ʱ��ִ�б�־
         {
             DCDCTaskCycleCnt4_done = FALSE;

             EPWMDriveTask();    //8.7
             //DCDC_Contrl_Step(); //15 DCDC�ջ����ƺ���
             ADCTask();
             check_cbc_protection();
         }
         if (DCDCTaskCycleCnt1_done == TRUE)    //40msִ��һ�εĶ�ʱ��ִ�б�־
         {
             DCDCTaskCycleCnt1_done = FALSE;
             Rs485_Manager_Main();     //485ͨѶ�����������������ݵ�ͬ�������Դ���߿�������ת��������
             Syn_Parameters_Mcu_Dsp(); //���ݴ�����������ݣ���������ͬ��������

//             if (deviceInfo.isMaster)   //������ֵȴ�CANͨ��&&����������ɺ��ٵ���
//             {
//                 Send_Heartbeat();
//             }
         }
         if (DCDCTaskCycleCnt2_done == TRUE)        //80usִ��һ�εĶ�ʱ����־
         {
             DCDCTaskCycleCnt2_done = FALSE;
             DCDC_CONDITION();      //DCDC����״̬��
             //ADCTask();
            // CurCalcTask();
         }


         //
        // ScanProgExe(); //����ɨ�躯��

    //     /************ USER CODE BEGIN **************/
    //   COMStateMaintain(); /* �����쳣���� ���쳣�޶��� */ //��߿���ע�͵�������MODBUS��������

         /************ USER CODE END **************/
     }


}

