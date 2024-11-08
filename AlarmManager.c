
#include "AlarmManager.h"
//#include "H3G_GRP01_48V.h"
#include "H3GSignal_QS.h"
#include "SampleManager.h"
//#include "Alarm_Storage.h"

U8 alarm_run_flag = 0;

void AlarmManager_Init(void)
{
   // H3G_GRP01_48V_initialize();
	//  Alarm_Storage_initialize();
}	

//extern uint8_T cell_call;


void AlarmManager_Main(void)
{
//    if(One_Sample_End)
		{	
     //   H3G_GRP01_48V_step();
	//		  Alarm_Storage_step();  //灏嗗憡璀﹀瓨鍌ㄦ斁鍦ㄥ憡璀︿换鍔″悗椹笂鎵ц锛岀‘淇濆巻鍙叉暟鎹兘涓�涓�瀵瑰簲
			  if(alarm_run_flag == 0)
				{
				  alarm_run_flag = 1;
				}	
		}			
}


BOOL Check_Warning_For_Exist(U8 GroupId)
{
//	if ((Get_H3G_Alarm_Single(H3G_GRP01_SUM_ALM_LVL_TWO_STA_HIGH + GroupId)) & //2绾ч珮瀛楄妭
//		(Get_H3G_All_Para(H3G_SET_CUT_OFF_RELY_ALM_LVL_TWO_CONT_HIGH)))
//	{
//		return TRUE;
//	}
//	if ((Get_H3G_Alarm_Single(H3G_GRP01_SUM_ALM_LVL_TWO_STA_LOW + GroupId)) & //2绾т綆瀛楄妭
//		(Get_H3G_All_Para(H3G_SET_CUT_OFF_RELY_ALM_LVL_TWO_CONT_LOW)))
//	{
//		return TRUE;
//	}
//	if ((Get_H3G_Alarm_Single(H3G_GRP01_SUM_ALM_LVL_ONE_STA_HIGH + GroupId)) & //1绾ч珮瀛楄妭
//		(Get_H3G_All_Para(H3G_SET_CUT_OFF_RELY_ALM_LVL_ONE_CONT_HIGH)))
//	{
//		return TRUE;
//	}
//	if ((Get_H3G_Alarm_Single(H3G_GRP01_SUM_ALM_LVL_ONE_STA_LOW + GroupId)) & //1绾т綆瀛楄妭
//		(Get_H3G_All_Para(H3G_SET_CUT_OFF_RELY_ALM_LVL_ONE_CONT_LOW)))
//	{
//		return TRUE;
//	}
	return FALSE;
}









