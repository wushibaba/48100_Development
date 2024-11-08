
#ifndef __ALARMMANAGER_H__
#define __ALARMMANAGER_H__

#include "CommTypes.h"

extern U8 One_Alarm_End;


//单体电压高（0）、单体电压低（1）、充电温度高（2）、充电温度低（3）、放电温度高（4）、放电温度低（5）、
//电压不均(6)、单体温度不均(7)、采样通讯故障(8)、组压高(9)、组压低(10)、充电电流大(11)、放电电流大(12)、
//环境温度高(13)、环境温度低(14)、SOC低(15)、SOH低(16) MOS温度高(17)

#define ALARM_VOLT_HIGH          0x0001
#define ALARM_VOLT_LOW           0x0002
#define ALARM_CHG_TEMP_HIGH      0x0004
#define ALARM_CHG_TEMP_LOW       0x0008
#define ALARM_DIS_TEMP_HIGH      0x0010
#define ALARM_DIS_TEMP_LOW       0x0020
#define ALARM_VOLT_DIFF          0x0040
#define ALARM_TEMP_DIFF          0x0080
#define ALARM_SAMPLE_FLAUT       0x0100
#define ALARM_TOTAL_HIGH         0x0200
#define ALARM_TOTAL_LOW          0x0400
#define ALARM_CHG_CUR_HIGH       0x0800
#define ALARM_DIS_CUR_HIGH       0x1000
#define ALARM_EVIR_TEMP_HIHG     0x2000
#define ALARM_EVIR_TEMP_LOW      0x4000
#define ALARM_SOC_LOW            0x8000


#define ALARM_SOH_LOW            0x0001
#define ALARM_MOS_TEMP_HIGH      0x0002  
#define ALARM_SHORT_CIRCUIT      0x0004  
#define ALARM_REVERSE_CONNECTION      0x0008 
#define ALARM_SHORT_TERM         0x0010 
#define ALARM_HARDWARE           0x0020
#define ALARM_CHG_MOS            0x0040 
#define ALARM_DISCHG_MOS         0x0080 
#define ALARM_DISCHG_2_PROTECT   0x0100
#define ALARM_CHG_2_PROTECT      0x0200
#define ALARM_FIRE_EQU_STARTUP   0x0400


extern void AlarmManager_Init(void);
extern void AlarmManager_Main(void);

/* 告警模块运行模式设置  TRUE 运行铅酸单体告警   FALSE 不运行铅酸单体告警 */
void AlarmRunModeSet(BOOL Mode);

/* 设置内阻告警检测标志 */
void AlarmRunLoad(void);
/* 定时启动内阻告警检测 */
void AlarmTimerRunLoad(void);

BOOL Check_Warning_For_Exist(U8 GroupId);

extern U8 alarm_run_flag;

#endif







