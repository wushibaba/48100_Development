/*
 * FaultProcess.h
 *
 *  Created on: 2024年9月26日
 *      Author: PENG LI
 */

#ifndef USER_APP_ALARMMANAGER_FAULTPROCESS_H_
#define USER_APP_ALARMMANAGER_FAULTPROCESS_H_




typedef struct {
    float level1_b_charge_overcurrent_threshold; // B端充电一级保护阈值 (A)
    float level2_b_charge_overcurrent_threshold; // B端充电二级保护阈值 (A)
    float level1_b_discharge_overcurrent_threshold; // B端放电一级保护阈值 (A)
    float level2_b_discharge_overcurrent_threshold; // B端放电二级保护阈值 (A)

    float level1_p_charge_overcurrent_threshold; // P端充电一级保护阈值 (A)
    float level2_p_charge_overcurrent_threshold; // P端充电二级保护阈值 (A)
    float level1_p_discharge_overcurrent_threshold; // P端放电一级保护阈值 (A)
    float level2_p_discharge_overcurrent_threshold; // P端放电二级保护阈值 (A)

    float p_short_circuit_current_threshold; // P端短路电流阈值 (A)

    float p_over_voltage_threshold; // P端过压保护阈值 (V)
    float p_over_voltage_recovery;  // P端过压恢复阈值 (V)

    float environment_over_temperature_threshold; // 环境过温阈值 (摄氏度)
    float environment_over_temperature_recovery; // 环境过温恢复阈值 (摄氏度)
    float environment_under_temperature_threshold; // 环境欠温阈值 (摄氏度)
    float environment_under_temperature_recovery; // 环境欠温恢复阈值 (摄氏度)

    float mos_over_temperature_threshold; // MOS开关管过温阈值 (摄氏度)
    float mos_over_temperature_recovery; // MOS开关管过温恢复阈值 (摄氏度)

    uint32_t charge_recovery_interval_count; // 充电保护恢复时间间隔 (中断计数次数)
    uint32_t discharge_recovery_interval_count; // 放电保护恢复时间间隔 (中断计数次数)
    uint32_t p_short_circuit_recovery_interval_count; // P端短路重启间隔 (中断计数次数)
    uint32_t p_over_voltage_recovery_interval_count; // P端过压恢复时间间隔 (中断计数次数)

    uint32_t max_b_protection_attempts; // B端最大保护尝试次数
    uint32_t max_p_charge_protection_attempts; // P端充电最大保护尝试次数
} ProtectionParameters;

// 系统输入结构体
typedef struct {
    float battery_voltage;         // B端电压
    float bus_voltage;             // P端电压
    float battery_current;         // 电池电流瞬时值
    float battery_current_avg;     // 电池电流平均采样值
    float bus_current;             // 母线电流瞬时值
    float bus_current_avg;         // 母线电流平均采样值
    float environment_temperature; // 环境温度
    float mos_1_temperature;         // MOS1开关管温度
    float mos_2_temperature;         // MOS2开关管温度
} SystemInputs;

// 保护状态结构体
typedef struct {

    bool level1_b_charge_protection_triggered; // B端充电过流一级故障保护触发标志
    bool level2_b_charge_protection_triggered; // B端充过流二级故障保护触发标志
    bool level1_b_discharge_protection_triggered; // B端放电流一级故障保护触发标志
    bool level2_b_discharge_protection_triggered; // B端放电流二级故障保护触发标志

    bool level1_p_charge_protection_triggered; // P端充电流一级故障保护触发标志
    bool level2_p_charge_protection_triggered; // P端充电流二级故障保护触发标志
    bool level1_p_discharge_protection_triggered; // P端放电流一级故障保护触发标志
    bool level2_p_discharge_protection_triggered; // P端放电流二级故障保护触发标志

    bool p_short_circuit_protection_triggered; // P端短路保护触发标志

    bool p_over_voltage_protection_triggered; // P端过压保护触发状态

    bool over_temperature_protection_triggered; // 环境过温保护触发标志
    bool under_temperature_protection_triggered; // 环境欠温保护触发标志
    bool mos_over_temperature_protection_triggered; // MOS开关管过温保护触发标志

    bool charging_enabled;
    bool discharging_enabled;

    uint32_t b_charge_protection_timer_count;
    uint32_t discharge_protection_timer_count;
    uint32_t p_charge_protection_timer_count;
    uint32_t p_over_voltage_recovery_timer_count;  // P端过压保护恢复延时计数
    uint32_t p_short_circuit_timer_count; // P端短路保护计时器

    uint32_t b_charge_overcurrent_attempts;
    uint32_t p_charge_overcurrent_attempts;

    uint32_t cbc_trigger_count;   // CBC保护触发计数
    uint32_t cbc_start_time;      // 记录CBC保护计时的起始时间
    bool cbc_interrupt_flag;      // CBC中断标志位
} ProtectionState;

// 函数声明
void check_overcurrent_protection(SystemInputs *inputs, ProtectionParameters *params);
void check_environment_temperature_protection(SystemInputs *inputs, ProtectionParameters *params);
void check_environment_temperature_protection(SystemInputs *inputs , ProtectionParameters *params);
void check_mos_temperature_protection(SystemInputs *inputs, ProtectionParameters *params);
void check_all_protections();
void initialize_protection_state();
void initialize_protection_parameters();
void check_cbc_protection();
#endif /* USER_APP_ALARMMANAGER_FAULTPROCESS_H_ */
