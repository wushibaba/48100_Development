/*
 * main.c
 *
 *  Created on: 2024年9月23日
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

/* 任务创建函数。    暂定每100us扫描任务一次 */
void Task_Init(void)
{
    Uart_Arry_Init();

//     uint16_T U16Value=0;
//     GetSigVal(H3G_B48_MODE, &U16Value); //获取B48工作模式
//     if ((U16Value & 0x0001) == 0x0001) //如果当前设备是做主设备
//     {
//       if ((U16Value & 0x0002) == 0x0000) //如果是485硬件模式
//       {
 //        (void)SetCycleTask_NoParam(Master_Serial485_Communicat_function, TIME60MS);
//       }
//       else
//       {
//        // (void)CreateScanProg(Can0_DataDeal);
//        // (void)SetCycleTask_NoParam(Can0_ReceiveMsg_timeout, TIME10MS);
//       }

//     }
//     else if ((U16Value & 0x0001) == 0x0000) //如果当前设备是做从设备
//     {
//       if ((U16Value & 0x0002) == 0x0000) //如果是485硬件模式
//       {
//       //  (void)SetCycleTask_NoParam(Slave_Serial485_Communicat_function, TIME40MS);
//       }
//       else
//       {
//       //  (void)CreateScanProg(Can0_DataDeal);
//       //  (void)SetCycleTask_NoParam(Can0_ReceiveMsg_timeout, TIME10MS);
//       }
//     }

//    SetCycleTask_NoParam(DCDC_Contrl_Step,TIME500US);//严格保证100us运行一次
//    SetCycleTask_NoParam(ADCTask, TIME500US);//严格保证100us运行一次

 //     SetCycleTask_NoParam(DCDC_CONDITION,TIME1MS);//1ms运行一次
//       SetCycleTask_NoParam(SCANKeyBUT,TIME10MS);//10ms运行一次

//      SetCycleTask_NoParam(EPWMDriveTask, TIME500US);  //PWM底层驱动任务
 //     SetCycleTask_NoParam(ADCTask, TIME100US);
//    SetCycleTask_NoParam(TempTask, TIME1S);
//    SetCycleTask_NoParam(CurCalcTask, TIME10MS);

//     /*参数配置*/
//     SetCycleTask_NoParam(AutoConfigMission, TIME40MS /*TASK_AUTO_CONFIG_TIME*/ );
//     /*历史数据存储*/
//     SetCycleTask_NoParam(DataStorage_Main, TIME1S /*TIME100MS*/ );
//     /*GPIO任务*/
//     SetCycleTask_NoParam(GPIO_Main, TIME100MS /*TASK_GPIO_TIME*/ );
//     /*Rs485协议*/
//     SetCycleTask_NoParam(Rs485_Manager_Main, TIME40MS /*TIME4MS*/ );
//     /*电流获取*/
//     SetCycleTask_NoParam(CurrentUpdate, TIME2S /*TIME200MS*/ );
//     /*soc管理*/
//     (void)SetCycleTask_NoParam(Soc_Main, TIME10S /*TIME1S*/ );
//     /*367307采样*/
//     (void)SetCycleTask_NoParam(BatInfoTask, TIME100MS /* AFE_TASK_CYCLE */ );
//     /*单体电压，温度*/
//     (void)SetCycleTask_NoParam(Get_Volt_Temp, TIME2S /*TIME200MS*/ );
//     /*RTC任务*/
//     (void)SetCycleTask_NoParam(Task_RTC_Main, TIME2S /*TIME200MS*/ );
//     /*休眠管理*/
// //    SetCycleTask_NoParam(SystemTask, TIME500MS);
//     /*led亮灯任务*/
//     (void)SetCycleTask_NoParam(led_ctrl_step, TIME100MS /*TIME100MS*/ );

//     /*报警任务*/
//     (void)DelayTask_NoParam(Delay_Task_AlarmManager, TIME1_2S,0);  //报警任务延时1.2s执行
//     /*充电管理*/
//     (void)DelayTask_NoParam(Delay_Task_ChgManager, TIME2_6S,1); //充放电控制任务延时2.6s执行

//     /*生产工装电流校准*/
//     (void)SetCycleTask_NoParam(CurCailbTask, TIME4S /*TIME400MS*/ );

// //    SetCycleTask_NoParam(test_PWM, 10);   //only for test
//         SetCycleTask_NoParam(CMPSStest, 10000); //1S 比较器测试
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
    InitCLAPara();  //初始化了ADvalues转换为实际值
  // StartCLATasks();


    UserISRFuncRegster();// register ISR callback function (not necessary)
    Interrupt_enableMaster();// Enables CPU interrupts
    /************ USER CODE BEGIN **************/


    /************ USER CODE END **************/
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM
    /************ USER CODE BEGIN **************/
   // EEP_Check();
    SomeSigValInit();//此函数初始化一定要运行，不然初始化RET层，以及运行GetSigVal()/SetSigVal()函数就有问题。


    Usart_Init();   //实际并无用处，这里是普通COM口

    //  RTCInit();
    //  SoftwareVersion();

    Rs485_Manager_Init();



    dcdc_sp_proct_init();       //DCDCtask内
    initialize_protection_state();  //初始化保护状态
    initialize_protection_parameters(); //初始化白虎参数
    /***** Start Module *****/
    StartADC();
    StartSCI();
    StartEPWMTZFunction();
    StartEPWM();
    StartCLATasks();
  //  StopAllEPWMOutput();
    Relay_Init();//继电器上电初始化 控制继电器部分，测试PWM的时候不开放,单独测试继电器的时候，关闭epwm输出后开启
    DC_DRI_CTL_ON();
    LED_DSP_ON();//DSP_LED指示灯打开
    Task_Init();

    DC_DRI_CTL_ON();    //供电打开 与EPWM信号给出间隔 必须大于6us

    HAL_Delay(1);       //延迟1ms

    test_PWM();    //测试PWM。测试继电器Rel的时候需要注释掉！


    /************ USER CODE END **************/
     while(1)
     {


         if (DCDCTaskCycleCnt4_done == TRUE)    //40us执行一次的定时器执行标志
         {
             DCDCTaskCycleCnt4_done = FALSE;

             EPWMDriveTask();    //8.7
             //DCDC_Contrl_Step(); //15 DCDC闭环控制函数
             ADCTask();
             check_cbc_protection();
         }
         if (DCDCTaskCycleCnt1_done == TRUE)    //40ms执行一次的定时器执行标志
         {
             DCDCTaskCycleCnt1_done = FALSE;
             Rs485_Manager_Main();     //485通讯处理函数，包括了数据的同步，可以从这边看采样后转换的数据
             Syn_Parameters_Mcu_Dsp(); //根据传输过来的数据，进行数据同步，更新

//             if (deviceInfo.isMaster)   //这个部分等待CAN通信&&均流部分完成后再调用
//             {
//                 Send_Heartbeat();
//             }
         }
         if (DCDCTaskCycleCnt2_done == TRUE)        //80us执行一次的定时器标志
         {
             DCDCTaskCycleCnt2_done = FALSE;
             DCDC_CONDITION();      //DCDC部分状态机
             //ADCTask();
            // CurCalcTask();
         }


         //
        // ScanProgExe(); //任务扫描函数

    //     /************ USER CODE BEGIN **************/
    //   COMStateMaintain(); /* 串口异常处理 无异常无动作 */ //这边可以注释掉。放在MODBUS处理函数内

         /************ USER CODE END **************/
     }


}

