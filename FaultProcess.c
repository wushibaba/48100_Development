/*
 * FaultProcess.c
 *
 *  Created on: 2024年9月26日
 *      Author: wushibaba
 */


#include <stdio.h>
#include <stdbool.h>
#include "H3GSignal_QS.h"
#include <FaultProcess.h>



// 保护状态全局变量---到时候外部状态机需要调用
ProtectionState protection_state = {0};
SystemInputs system_inputs = {0};
ProtectionParameters protection_params;

void initialize_protection_parameters() {
        // 初始化B端保护的阈值
    protection_params.level1_b_charge_overcurrent_threshold = 130.0;   // B端充电一级保护阈值 (A)
    protection_params.level2_b_charge_overcurrent_threshold = 200.0;   // B端充电二级保护阈值 (A)
    protection_params.level1_b_discharge_overcurrent_threshold = 130.0; // B端放电一级保护阈值 (A)
    protection_params.level2_b_discharge_overcurrent_threshold = 150.0; // B端放电二级保护阈值 (A)

    // 初始化P端保护的阈值
    protection_params.level1_p_charge_overcurrent_threshold = 130.0;   // P端充电一级保护阈值 (A)
    protection_params.level2_p_charge_overcurrent_threshold = 200.0;   // P端充电二级保护阈值 (A)
    protection_params.level1_p_discharge_overcurrent_threshold = 130.0; // P端放电一级保护阈值 (A)
    protection_params.level2_p_discharge_overcurrent_threshold = 150.0; // P端放电二级保护阈值 (A)

    // 初始化短路保护阈值
    protection_params.p_short_circuit_current_threshold = 250.0; // P端短路电流阈值 (A)

    // 初始化P端过压保护参数
    protection_params.p_over_voltage_threshold = 60.0; // 保护阈值为60V
    protection_params.p_over_voltage_recovery = 58.0;  // 恢复阈值为58V
    protection_params.p_over_voltage_recovery_interval_count = 25000; // 延时1秒 (1秒 = 25000个40微秒的中断计数)

    // 初始化环境温度和MOS开关管的温度保护阈值
    protection_params.environment_over_temperature_threshold = 100.0;  // 环境过温阈值 (摄氏度)
    protection_params.environment_over_temperature_recovery = 90.0;    // 环境过温恢复阈值 (摄氏度)
    protection_params.environment_under_temperature_threshold = -20.0; // 环境欠温阈值 (摄氏度)
    protection_params.environment_under_temperature_recovery = -10.0;  // 环境欠温恢复阈值 (摄氏度)
    protection_params.mos_over_temperature_threshold = 120.0;           // MOS开关管过温阈值 (摄氏度)
    protection_params.mos_over_temperature_recovery = 110.0;            // MOS开关管过温恢复阈值 (摄氏度)

    // 初始化保护恢复的时间间隔
    protection_params.charge_recovery_interval_count = 1500000;       // 充电保护恢复时间间隔 (约1分钟)
    protection_params.discharge_recovery_interval_count = 9000000;   // 放电保护恢复时间间隔 (约10分钟)
    protection_params.p_short_circuit_recovery_interval_count = 9000000; // P端短路重启间隔 (约10分钟，可调)

    // 初始化最大尝试次数
    protection_params.max_b_protection_attempts = 3; // B端最大保护尝试次数
    protection_params.max_p_charge_protection_attempts = 3; // P端充电最大保护尝试次数

}



// 更新的过流保护函数，非中断函数，可在主循环中调用
void check_overcurrent_protection(SystemInputs *inputs, ProtectionParameters *params) {
    // B端充电过流保护逻辑
    if (inputs->battery_current_avg > params-> level1_b_charge_overcurrent_threshold) {
        protection_state.level1_b_charge_protection_triggered = true;
        protection_state.discharging_enabled = true;  // 允许放电解除
        protection_state.charging_enabled = false;    // 禁止充电

        if (protection_state.b_charge_protection_timer_count == 0) {
            protection_state.b_charge_protection_timer_count = 1;  // 开始计时 在40us定时器中断内增加
        }

        //B端一级充电过流保护已触发
    }

    if (inputs->battery_current_avg > params-> level2_b_charge_overcurrent_threshold) {
        protection_state.level2_b_charge_protection_triggered = true;
        protection_state.charging_enabled = false;    // 禁止充电
        protection_state.discharging_enabled = false; // 禁止放电解除

        if (protection_state.b_charge_protection_timer_count == 0) {
            protection_state.b_charge_protection_timer_count = 1;  // 开始计时 在40us定时器中断内增加
        }

       //B端二级充电过流保护已触发
    }

    // B端放电过流保护逻辑
    if (inputs->battery_current_avg > params-> level1_b_discharge_overcurrent_threshold) {
        protection_state.level1_b_discharge_protection_triggered = true;
        protection_state.charging_enabled = true;    // 允许充电解除
        protection_state.discharging_enabled = false; // 禁止放电

        if (protection_state.discharge_protection_timer_count == 0) {
            protection_state.discharge_protection_timer_count = 1;  // 开始计时 在40us定时器中断内增加
        }

       //B端一级放电过流保护已触发
    }

    if (inputs->battery_current_avg > params-> level2_b_discharge_overcurrent_threshold) {
        protection_state.level2_b_discharge_protection_triggered = true;
        protection_state.charging_enabled = true;    // 允许充电解除
        protection_state.discharging_enabled = false; // 禁止放电

        if (protection_state.discharge_protection_timer_count == 0) {
            protection_state.discharge_protection_timer_count = 1;  // 开始计时 在40us定时器中断内增加
        }

        printf("B端二级放电过流保护已触发。\n");
    }

    // P端充电过流保护逻辑
    if (inputs->bus_current_avg > params-> level1_p_charge_overcurrent_threshold) {
        protection_state.level1_p_charge_protection_triggered = true;
        protection_state.discharging_enabled = true;  // 允许放电解除
        protection_state.charging_enabled = false;    // 禁止充电

        if (protection_state.p_charge_protection_timer_count == 0) {
            protection_state.p_charge_protection_timer_count = 1;  // 开始计时 在40us定时器中断内增加
        }

        //P端一级充电过流保护已触发
    }

    if (inputs->bus_current_avg > params-> level2_p_charge_overcurrent_threshold) {
        protection_state.level2_p_charge_protection_triggered = true;
        protection_state.charging_enabled = false;    // 禁止充电
        protection_state.discharging_enabled = true;  // 允许放电解除

        if (protection_state.p_charge_protection_timer_count == 0) {
            protection_state.p_charge_protection_timer_count = 1;  // 开始计时 在40us定时器中断内增加
        }

        //P端二级充电过流保护已触发
    }

    // P端放电过流保护逻辑
    if (inputs->bus_current_avg > params-> level1_p_discharge_overcurrent_threshold) {
        protection_state.level1_p_discharge_protection_triggered = true;
        protection_state.charging_enabled = true;    // 允许充电解除
        protection_state.discharging_enabled = false; // 禁止放电

        if (protection_state.discharge_protection_timer_count == 0) {
            protection_state.discharge_protection_timer_count = 1;  // 开始计时 在40us定时器中断内增加
        }

        //P端一级放电过流保护已触发
    }

    if (inputs->bus_current_avg > params-> level2_p_discharge_overcurrent_threshold) {
        protection_state.level2_p_discharge_protection_triggered = true;
        protection_state.charging_enabled = true;    // 允许充电解除
        protection_state.discharging_enabled = false; // 禁止放电

        if (protection_state.discharge_protection_timer_count == 0) {
            protection_state.discharge_protection_timer_count = 1;  // 开始计时 在40us定时器中断内增加
        }

        //P端二级放电过流保护已触发
    }

    // 检查B端充电恢复条件
    if (protection_state.b_charge_protection_timer_count > 0 &&
        protection_state.b_charge_protection_timer_count >= params-> charge_recovery_interval_count) {

        if (protection_state.b_charge_overcurrent_attempts < params-> max_b_protection_attempts) {
            protection_state.level1_b_charge_protection_triggered = false;
            protection_state.charging_enabled = true;
            protection_state.discharging_enabled = true;

            protection_state.b_charge_overcurrent_attempts++;
            protection_state.b_charge_protection_timer_count = 0;

        } else {
            protection_state.charging_enabled = false;  //B端充电保护已触发三次，禁止充电
        }
    }

    // 检查P端充电恢复条件
    if (protection_state.p_charge_protection_timer_count > 0 &&
        protection_state.p_charge_protection_timer_count >= params-> charge_recovery_interval_count) {

        if (protection_state.p_charge_overcurrent_attempts < params-> max_p_charge_protection_attempts) {
            protection_state.level1_p_charge_protection_triggered = false;
            protection_state.level2_p_charge_protection_triggered = false;
            protection_state.charging_enabled = true;
            protection_state.discharging_enabled = true;

            protection_state.p_charge_overcurrent_attempts++;
            protection_state.p_charge_protection_timer_count = 0;

            //P端充电恢复尝试
        } else {
            protection_state.charging_enabled = false;
            //P端充电保护已触发三次，禁止充电
        }
    }

    // 检查放电恢复条件，无次数限制
    if (protection_state.discharge_protection_timer_count > 0 &&
        protection_state.discharge_protection_timer_count >= params-> discharge_recovery_interval_count) {

        protection_state.level1_b_discharge_protection_triggered = false;
        protection_state.level2_b_discharge_protection_triggered = false;
        protection_state.level1_p_discharge_protection_triggered = false;
        protection_state.level2_p_discharge_protection_triggered = false;
        protection_state.charging_enabled = true;
        protection_state.discharging_enabled = true;
        protection_state.discharge_protection_timer_count = 0;

        //放电恢复成功，继续尝试恢复放电

     }

    // 增加P端短路保护逻辑
      if (inputs->bus_current > params-> p_short_circuit_current_threshold) {
          protection_state.p_short_circuit_protection_triggered = true;
          protection_state.charging_enabled = false;    // 禁止充电
          protection_state.discharging_enabled = false; // 禁止放电

          if (protection_state.p_short_circuit_timer_count == 0) {
              protection_state.p_short_circuit_timer_count = 1;  // 开始计时 在40us定时器中断内增加
          }

          //P端短路保护已触发
      }

      // 检查P端短路保护恢复条件
      if (protection_state.p_short_circuit_timer_count > 0 &&
          protection_state.p_short_circuit_timer_count >= params-> p_short_circuit_recovery_interval_count) {

          protection_state.p_short_circuit_protection_triggered = false;
          protection_state.charging_enabled = true;
          protection_state.discharging_enabled = true;
          protection_state.p_short_circuit_timer_count = 0;

          //P端短路保护恢复成功，重新尝试正常运行
      }


}

void check_p_over_voltage_protection(SystemInputs *inputs, ProtectionParameters *params) {
    // 检查是否超过过压阈值
    if (inputs->bus_voltage > params->p_over_voltage_threshold) {
        protection_state.p_over_voltage_protection_triggered = true;
        protection_state.charging_enabled = false;
        protection_state.discharging_enabled = false;

        // 启动过压计数器
        if (protection_state.p_over_voltage_recovery_timer_count == 0) {
            protection_state.p_over_voltage_recovery_timer_count = 1;
        }

        //P端过压保护已触发
    }

    // 检查是否符合恢复条件
    if (protection_state.p_over_voltage_protection_triggered) {
        if (inputs->bus_voltage <= params->p_over_voltage_recovery) {
            // 延时恢复逻辑
            if (protection_state.p_over_voltage_recovery_timer_count >= params->p_over_voltage_recovery_interval_count) {
                protection_state.p_over_voltage_protection_triggered = false;
                protection_state.charging_enabled = true;
                protection_state.discharging_enabled = true;
                protection_state.p_over_voltage_recovery_timer_count = 0;
                //P端过压保护已恢复
            } else {
                // 计数器递增
                protection_state.p_over_voltage_recovery_timer_count++;
            }
        } else {
            // 电压未恢复，重置计数器
            protection_state.p_over_voltage_recovery_timer_count = 0;
        }
    }
}


// 环境温度保护子函数
void check_environment_temperature_protection(SystemInputs *inputs , ProtectionParameters *params) {
    // 环境过温保护
    if (inputs->environment_temperature > params-> environment_over_temperature_threshold) {
        protection_state.over_temperature_protection_triggered = true;
        protection_state.charging_enabled = false;
        protection_state.discharging_enabled = false;
        //环境过温保护已触发
    } else if (protection_state.over_temperature_protection_triggered &&
               inputs->environment_temperature <= params-> mos_over_temperature_recovery) {
        protection_state.over_temperature_protection_triggered = false;
        protection_state.charging_enabled = true;
        protection_state.discharging_enabled = true;
        //环境欠温保护已解除
    }

    // 环境欠温保护
    if (inputs->environment_temperature < params-> environment_under_temperature_threshold) {
        protection_state.under_temperature_protection_triggered = true;
        protection_state.charging_enabled = false;
        protection_state.discharging_enabled = false;
        //环境欠温保护已触发
    } else if (protection_state.under_temperature_protection_triggered &&
               inputs->environment_temperature >= params-> environment_under_temperature_recovery) {
        protection_state.under_temperature_protection_triggered = false;
        protection_state.charging_enabled = true;
        protection_state.discharging_enabled = true;
        //环境欠温保护已解除
    }
}

// MOS开关管温度保护子函数
void check_mos_temperature_protection(SystemInputs *inputs, ProtectionParameters *params) {
    //MOS1温度保护
    if (inputs->mos_1_temperature > params-> mos_over_temperature_threshold) {
        protection_state.mos_over_temperature_protection_triggered = true;
        protection_state.charging_enabled = false;
        protection_state.discharging_enabled = false;
        //MOS1开关管过温保护已触发，温度**
    } else if (protection_state.mos_over_temperature_protection_triggered &&
               inputs->mos_1_temperature <= params-> mos_over_temperature_recovery) {
        protection_state.mos_over_temperature_protection_triggered = false;
        protection_state.charging_enabled = true;
        protection_state.discharging_enabled = true;}
        //MOS1开关管过温保护已解除

        //MOS2温度保护
        if (inputs->mos_2_temperature > params-> mos_over_temperature_threshold) {
            protection_state.mos_over_temperature_protection_triggered = true;
            protection_state.charging_enabled = false;
            protection_state.discharging_enabled = false;
            //MOS2开关管过温保护已触发
        } else if (protection_state.mos_over_temperature_protection_triggered &&
                   inputs->mos_2_temperature <= params-> mos_over_temperature_recovery) {
            protection_state.mos_over_temperature_protection_triggered = false;
            protection_state.charging_enabled = true;
            protection_state.discharging_enabled = true;}
            //MOS2开关管过温保护已解除
}

// 次数触发 CBC 保护逻辑
void check_cbc_protection() {
    uint32_t current_time = HAL_GetSysTick(); // 获取当前时间，假设单位是微秒

    // 检查CBC中断标志位
    if (protection_state.cbc_interrupt_flag) {
        protection_state.cbc_interrupt_flag = false; // 清除标志位

        // 如果这是第一次触发，初始化计时
        if (protection_state.cbc_trigger_count == 0) {
            protection_state.cbc_start_time = current_time;
            protection_state.cbc_trigger_count = 1;
        } else {
            // 检查时间间隔 这个地方待修改 防止误触发
            if ((current_time - protection_state.cbc_start_time) <= 10) {
                protection_state.cbc_trigger_count++;

                // 如果1000微秒内超过15次触发
                if (protection_state.cbc_trigger_count > 15) {
                    StopAllEPWMOutput(); // 关断所有PWM

                    // 重置CBC计数
                    protection_state.cbc_trigger_count = 0;
                }
            } else {
                // 超过800微秒，重置计数和时间
                protection_state.cbc_start_time = current_time;
                protection_state.cbc_trigger_count = 1;
            }
        }
    }
}

void check_all_protections() {
    check_overcurrent_protection(&system_inputs, &protection_params);
    check_environment_temperature_protection(&system_inputs, &protection_params);
    check_environment_temperature_protection(&system_inputs, &protection_params);
    check_mos_temperature_protection(&system_inputs, &protection_params);
}

void initialize_protection_state() {

    // 初始化CBC保护计数
    protection_state.cbc_trigger_count = 0;
    protection_state.cbc_start_time = 0;
    protection_state.cbc_interrupt_flag = false;

    protection_state.level1_b_charge_protection_triggered = false;
    protection_state.level2_b_charge_protection_triggered = false;
    protection_state.level1_b_discharge_protection_triggered = false;
    protection_state.level2_b_discharge_protection_triggered = false;

    protection_state.level1_p_charge_protection_triggered = false;
    protection_state.level2_p_charge_protection_triggered = false;
    protection_state.level1_p_discharge_protection_triggered = false;
    protection_state.level2_p_discharge_protection_triggered = false;

    protection_state.p_short_circuit_protection_triggered = false;

    protection_state.over_temperature_protection_triggered = false;
    protection_state.under_temperature_protection_triggered = false;
    protection_state.mos_over_temperature_protection_triggered = false;

    protection_state.charging_enabled = true;
    protection_state.discharging_enabled = true;

    protection_state.b_charge_protection_timer_count = 0;
    protection_state.discharge_protection_timer_count = 0;
    protection_state.p_charge_protection_timer_count = 0;
    protection_state.p_short_circuit_timer_count = 0;

    protection_state.b_charge_overcurrent_attempts = 0;
    protection_state.p_charge_overcurrent_attempts = 0;
}
