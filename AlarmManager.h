
#ifndef __ALARMMANAGER_H__
#define __ALARMMANAGER_H__

#include "CommTypes.h"

extern U8 One_Alarm_End;


//�����ѹ�ߣ�0���������ѹ�ͣ�1��������¶ȸߣ�2��������¶ȵͣ�3�����ŵ��¶ȸߣ�4�����ŵ��¶ȵͣ�5����
//��ѹ����(6)�������¶Ȳ���(7)������ͨѶ����(8)����ѹ��(9)����ѹ��(10)����������(11)���ŵ������(12)��
//�����¶ȸ�(13)�������¶ȵ�(14)��SOC��(15)��SOH��(16) MOS�¶ȸ�(17)

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

/* �澯ģ������ģʽ����  TRUE ����Ǧ�ᵥ��澯   FALSE ������Ǧ�ᵥ��澯 */
void AlarmRunModeSet(BOOL Mode);

/* ��������澯����־ */
void AlarmRunLoad(void);
/* ��ʱ��������澯��� */
void AlarmTimerRunLoad(void);

BOOL Check_Warning_For_Exist(U8 GroupId);

extern U8 alarm_run_flag;

#endif







