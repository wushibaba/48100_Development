/*
 * FaultProcess.h
 *
 *  Created on: 2024��9��26��
 *      Author: PENG LI
 */

#ifndef USER_APP_ALARMMANAGER_FAULTPROCESS_H_
#define USER_APP_ALARMMANAGER_FAULTPROCESS_H_




typedef struct {
    float level1_b_charge_overcurrent_threshold; // B�˳��һ��������ֵ (A)
    float level2_b_charge_overcurrent_threshold; // B�˳�����������ֵ (A)
    float level1_b_discharge_overcurrent_threshold; // B�˷ŵ�һ��������ֵ (A)
    float level2_b_discharge_overcurrent_threshold; // B�˷ŵ����������ֵ (A)

    float level1_p_charge_overcurrent_threshold; // P�˳��һ��������ֵ (A)
    float level2_p_charge_overcurrent_threshold; // P�˳�����������ֵ (A)
    float level1_p_discharge_overcurrent_threshold; // P�˷ŵ�һ��������ֵ (A)
    float level2_p_discharge_overcurrent_threshold; // P�˷ŵ����������ֵ (A)

    float p_short_circuit_current_threshold; // P�˶�·������ֵ (A)

    float p_over_voltage_threshold; // P�˹�ѹ������ֵ (V)
    float p_over_voltage_recovery;  // P�˹�ѹ�ָ���ֵ (V)

    float environment_over_temperature_threshold; // ����������ֵ (���϶�)
    float environment_over_temperature_recovery; // �������»ָ���ֵ (���϶�)
    float environment_under_temperature_threshold; // ����Ƿ����ֵ (���϶�)
    float environment_under_temperature_recovery; // ����Ƿ�»ָ���ֵ (���϶�)

    float mos_over_temperature_threshold; // MOS���عܹ�����ֵ (���϶�)
    float mos_over_temperature_recovery; // MOS���عܹ��»ָ���ֵ (���϶�)

    uint32_t charge_recovery_interval_count; // ��籣���ָ�ʱ���� (�жϼ�������)
    uint32_t discharge_recovery_interval_count; // �ŵ籣���ָ�ʱ���� (�жϼ�������)
    uint32_t p_short_circuit_recovery_interval_count; // P�˶�·������� (�жϼ�������)
    uint32_t p_over_voltage_recovery_interval_count; // P�˹�ѹ�ָ�ʱ���� (�жϼ�������)

    uint32_t max_b_protection_attempts; // B����󱣻����Դ���
    uint32_t max_p_charge_protection_attempts; // P�˳����󱣻����Դ���
} ProtectionParameters;

// ϵͳ����ṹ��
typedef struct {
    float battery_voltage;         // B�˵�ѹ
    float bus_voltage;             // P�˵�ѹ
    float battery_current;         // ��ص���˲ʱֵ
    float battery_current_avg;     // ��ص���ƽ������ֵ
    float bus_current;             // ĸ�ߵ���˲ʱֵ
    float bus_current_avg;         // ĸ�ߵ���ƽ������ֵ
    float environment_temperature; // �����¶�
    float mos_1_temperature;         // MOS1���ع��¶�
    float mos_2_temperature;         // MOS2���ع��¶�
} SystemInputs;

// ����״̬�ṹ��
typedef struct {

    bool level1_b_charge_protection_triggered; // B�˳�����һ�����ϱ���������־
    bool level2_b_charge_protection_triggered; // B�˳�����������ϱ���������־
    bool level1_b_discharge_protection_triggered; // B�˷ŵ���һ�����ϱ���������־
    bool level2_b_discharge_protection_triggered; // B�˷ŵ����������ϱ���������־

    bool level1_p_charge_protection_triggered; // P�˳����һ�����ϱ���������־
    bool level2_p_charge_protection_triggered; // P�˳�����������ϱ���������־
    bool level1_p_discharge_protection_triggered; // P�˷ŵ���һ�����ϱ���������־
    bool level2_p_discharge_protection_triggered; // P�˷ŵ����������ϱ���������־

    bool p_short_circuit_protection_triggered; // P�˶�·����������־

    bool p_over_voltage_protection_triggered; // P�˹�ѹ��������״̬

    bool over_temperature_protection_triggered; // �������±���������־
    bool under_temperature_protection_triggered; // ����Ƿ�±���������־
    bool mos_over_temperature_protection_triggered; // MOS���عܹ��±���������־

    bool charging_enabled;
    bool discharging_enabled;

    uint32_t b_charge_protection_timer_count;
    uint32_t discharge_protection_timer_count;
    uint32_t p_charge_protection_timer_count;
    uint32_t p_over_voltage_recovery_timer_count;  // P�˹�ѹ�����ָ���ʱ����
    uint32_t p_short_circuit_timer_count; // P�˶�·������ʱ��

    uint32_t b_charge_overcurrent_attempts;
    uint32_t p_charge_overcurrent_attempts;

    uint32_t cbc_trigger_count;   // CBC������������
    uint32_t cbc_start_time;      // ��¼CBC������ʱ����ʼʱ��
    bool cbc_interrupt_flag;      // CBC�жϱ�־λ
} ProtectionState;

// ��������
void check_overcurrent_protection(SystemInputs *inputs, ProtectionParameters *params);
void check_environment_temperature_protection(SystemInputs *inputs, ProtectionParameters *params);
void check_environment_temperature_protection(SystemInputs *inputs , ProtectionParameters *params);
void check_mos_temperature_protection(SystemInputs *inputs, ProtectionParameters *params);
void check_all_protections();
void initialize_protection_state();
void initialize_protection_parameters();
void check_cbc_protection();
#endif /* USER_APP_ALARMMANAGER_FAULTPROCESS_H_ */
