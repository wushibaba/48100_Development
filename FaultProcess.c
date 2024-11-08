/*
 * FaultProcess.c
 *
 *  Created on: 2024��9��26��
 *      Author: wushibaba
 */


#include <stdio.h>
#include <stdbool.h>
#include "H3GSignal_QS.h"
#include <FaultProcess.h>



// ����״̬ȫ�ֱ���---��ʱ���ⲿ״̬����Ҫ����
ProtectionState protection_state = {0};
SystemInputs system_inputs = {0};
ProtectionParameters protection_params;

void initialize_protection_parameters() {
        // ��ʼ��B�˱�������ֵ
    protection_params.level1_b_charge_overcurrent_threshold = 130.0;   // B�˳��һ��������ֵ (A)
    protection_params.level2_b_charge_overcurrent_threshold = 200.0;   // B�˳�����������ֵ (A)
    protection_params.level1_b_discharge_overcurrent_threshold = 130.0; // B�˷ŵ�һ��������ֵ (A)
    protection_params.level2_b_discharge_overcurrent_threshold = 150.0; // B�˷ŵ����������ֵ (A)

    // ��ʼ��P�˱�������ֵ
    protection_params.level1_p_charge_overcurrent_threshold = 130.0;   // P�˳��һ��������ֵ (A)
    protection_params.level2_p_charge_overcurrent_threshold = 200.0;   // P�˳�����������ֵ (A)
    protection_params.level1_p_discharge_overcurrent_threshold = 130.0; // P�˷ŵ�һ��������ֵ (A)
    protection_params.level2_p_discharge_overcurrent_threshold = 150.0; // P�˷ŵ����������ֵ (A)

    // ��ʼ����·������ֵ
    protection_params.p_short_circuit_current_threshold = 250.0; // P�˶�·������ֵ (A)

    // ��ʼ��P�˹�ѹ��������
    protection_params.p_over_voltage_threshold = 60.0; // ������ֵΪ60V
    protection_params.p_over_voltage_recovery = 58.0;  // �ָ���ֵΪ58V
    protection_params.p_over_voltage_recovery_interval_count = 25000; // ��ʱ1�� (1�� = 25000��40΢����жϼ���)

    // ��ʼ�������¶Ⱥ�MOS���عܵ��¶ȱ�����ֵ
    protection_params.environment_over_temperature_threshold = 100.0;  // ����������ֵ (���϶�)
    protection_params.environment_over_temperature_recovery = 90.0;    // �������»ָ���ֵ (���϶�)
    protection_params.environment_under_temperature_threshold = -20.0; // ����Ƿ����ֵ (���϶�)
    protection_params.environment_under_temperature_recovery = -10.0;  // ����Ƿ�»ָ���ֵ (���϶�)
    protection_params.mos_over_temperature_threshold = 120.0;           // MOS���عܹ�����ֵ (���϶�)
    protection_params.mos_over_temperature_recovery = 110.0;            // MOS���عܹ��»ָ���ֵ (���϶�)

    // ��ʼ�������ָ���ʱ����
    protection_params.charge_recovery_interval_count = 1500000;       // ��籣���ָ�ʱ���� (Լ1����)
    protection_params.discharge_recovery_interval_count = 9000000;   // �ŵ籣���ָ�ʱ���� (Լ10����)
    protection_params.p_short_circuit_recovery_interval_count = 9000000; // P�˶�·������� (Լ10���ӣ��ɵ�)

    // ��ʼ������Դ���
    protection_params.max_b_protection_attempts = 3; // B����󱣻����Դ���
    protection_params.max_p_charge_protection_attempts = 3; // P�˳����󱣻����Դ���

}



// ���µĹ����������������жϺ�����������ѭ���е���
void check_overcurrent_protection(SystemInputs *inputs, ProtectionParameters *params) {
    // B�˳����������߼�
    if (inputs->battery_current_avg > params-> level1_b_charge_overcurrent_threshold) {
        protection_state.level1_b_charge_protection_triggered = true;
        protection_state.discharging_enabled = true;  // ����ŵ���
        protection_state.charging_enabled = false;    // ��ֹ���

        if (protection_state.b_charge_protection_timer_count == 0) {
            protection_state.b_charge_protection_timer_count = 1;  // ��ʼ��ʱ ��40us��ʱ���ж�������
        }

        //B��һ�������������Ѵ���
    }

    if (inputs->battery_current_avg > params-> level2_b_charge_overcurrent_threshold) {
        protection_state.level2_b_charge_protection_triggered = true;
        protection_state.charging_enabled = false;    // ��ֹ���
        protection_state.discharging_enabled = false; // ��ֹ�ŵ���

        if (protection_state.b_charge_protection_timer_count == 0) {
            protection_state.b_charge_protection_timer_count = 1;  // ��ʼ��ʱ ��40us��ʱ���ж�������
        }

       //B�˶��������������Ѵ���
    }

    // B�˷ŵ���������߼�
    if (inputs->battery_current_avg > params-> level1_b_discharge_overcurrent_threshold) {
        protection_state.level1_b_discharge_protection_triggered = true;
        protection_state.charging_enabled = true;    // ��������
        protection_state.discharging_enabled = false; // ��ֹ�ŵ�

        if (protection_state.discharge_protection_timer_count == 0) {
            protection_state.discharge_protection_timer_count = 1;  // ��ʼ��ʱ ��40us��ʱ���ж�������
        }

       //B��һ���ŵ���������Ѵ���
    }

    if (inputs->battery_current_avg > params-> level2_b_discharge_overcurrent_threshold) {
        protection_state.level2_b_discharge_protection_triggered = true;
        protection_state.charging_enabled = true;    // ��������
        protection_state.discharging_enabled = false; // ��ֹ�ŵ�

        if (protection_state.discharge_protection_timer_count == 0) {
            protection_state.discharge_protection_timer_count = 1;  // ��ʼ��ʱ ��40us��ʱ���ж�������
        }

        printf("B�˶����ŵ���������Ѵ�����\n");
    }

    // P�˳����������߼�
    if (inputs->bus_current_avg > params-> level1_p_charge_overcurrent_threshold) {
        protection_state.level1_p_charge_protection_triggered = true;
        protection_state.discharging_enabled = true;  // ����ŵ���
        protection_state.charging_enabled = false;    // ��ֹ���

        if (protection_state.p_charge_protection_timer_count == 0) {
            protection_state.p_charge_protection_timer_count = 1;  // ��ʼ��ʱ ��40us��ʱ���ж�������
        }

        //P��һ�������������Ѵ���
    }

    if (inputs->bus_current_avg > params-> level2_p_charge_overcurrent_threshold) {
        protection_state.level2_p_charge_protection_triggered = true;
        protection_state.charging_enabled = false;    // ��ֹ���
        protection_state.discharging_enabled = true;  // ����ŵ���

        if (protection_state.p_charge_protection_timer_count == 0) {
            protection_state.p_charge_protection_timer_count = 1;  // ��ʼ��ʱ ��40us��ʱ���ж�������
        }

        //P�˶��������������Ѵ���
    }

    // P�˷ŵ���������߼�
    if (inputs->bus_current_avg > params-> level1_p_discharge_overcurrent_threshold) {
        protection_state.level1_p_discharge_protection_triggered = true;
        protection_state.charging_enabled = true;    // ��������
        protection_state.discharging_enabled = false; // ��ֹ�ŵ�

        if (protection_state.discharge_protection_timer_count == 0) {
            protection_state.discharge_protection_timer_count = 1;  // ��ʼ��ʱ ��40us��ʱ���ж�������
        }

        //P��һ���ŵ���������Ѵ���
    }

    if (inputs->bus_current_avg > params-> level2_p_discharge_overcurrent_threshold) {
        protection_state.level2_p_discharge_protection_triggered = true;
        protection_state.charging_enabled = true;    // ��������
        protection_state.discharging_enabled = false; // ��ֹ�ŵ�

        if (protection_state.discharge_protection_timer_count == 0) {
            protection_state.discharge_protection_timer_count = 1;  // ��ʼ��ʱ ��40us��ʱ���ж�������
        }

        //P�˶����ŵ���������Ѵ���
    }

    // ���B�˳��ָ�����
    if (protection_state.b_charge_protection_timer_count > 0 &&
        protection_state.b_charge_protection_timer_count >= params-> charge_recovery_interval_count) {

        if (protection_state.b_charge_overcurrent_attempts < params-> max_b_protection_attempts) {
            protection_state.level1_b_charge_protection_triggered = false;
            protection_state.charging_enabled = true;
            protection_state.discharging_enabled = true;

            protection_state.b_charge_overcurrent_attempts++;
            protection_state.b_charge_protection_timer_count = 0;

        } else {
            protection_state.charging_enabled = false;  //B�˳�籣���Ѵ������Σ���ֹ���
        }
    }

    // ���P�˳��ָ�����
    if (protection_state.p_charge_protection_timer_count > 0 &&
        protection_state.p_charge_protection_timer_count >= params-> charge_recovery_interval_count) {

        if (protection_state.p_charge_overcurrent_attempts < params-> max_p_charge_protection_attempts) {
            protection_state.level1_p_charge_protection_triggered = false;
            protection_state.level2_p_charge_protection_triggered = false;
            protection_state.charging_enabled = true;
            protection_state.discharging_enabled = true;

            protection_state.p_charge_overcurrent_attempts++;
            protection_state.p_charge_protection_timer_count = 0;

            //P�˳��ָ�����
        } else {
            protection_state.charging_enabled = false;
            //P�˳�籣���Ѵ������Σ���ֹ���
        }
    }

    // ���ŵ�ָ��������޴�������
    if (protection_state.discharge_protection_timer_count > 0 &&
        protection_state.discharge_protection_timer_count >= params-> discharge_recovery_interval_count) {

        protection_state.level1_b_discharge_protection_triggered = false;
        protection_state.level2_b_discharge_protection_triggered = false;
        protection_state.level1_p_discharge_protection_triggered = false;
        protection_state.level2_p_discharge_protection_triggered = false;
        protection_state.charging_enabled = true;
        protection_state.discharging_enabled = true;
        protection_state.discharge_protection_timer_count = 0;

        //�ŵ�ָ��ɹ����������Իָ��ŵ�

     }

    // ����P�˶�·�����߼�
      if (inputs->bus_current > params-> p_short_circuit_current_threshold) {
          protection_state.p_short_circuit_protection_triggered = true;
          protection_state.charging_enabled = false;    // ��ֹ���
          protection_state.discharging_enabled = false; // ��ֹ�ŵ�

          if (protection_state.p_short_circuit_timer_count == 0) {
              protection_state.p_short_circuit_timer_count = 1;  // ��ʼ��ʱ ��40us��ʱ���ж�������
          }

          //P�˶�·�����Ѵ���
      }

      // ���P�˶�·�����ָ�����
      if (protection_state.p_short_circuit_timer_count > 0 &&
          protection_state.p_short_circuit_timer_count >= params-> p_short_circuit_recovery_interval_count) {

          protection_state.p_short_circuit_protection_triggered = false;
          protection_state.charging_enabled = true;
          protection_state.discharging_enabled = true;
          protection_state.p_short_circuit_timer_count = 0;

          //P�˶�·�����ָ��ɹ������³�����������
      }


}

void check_p_over_voltage_protection(SystemInputs *inputs, ProtectionParameters *params) {
    // ����Ƿ񳬹���ѹ��ֵ
    if (inputs->bus_voltage > params->p_over_voltage_threshold) {
        protection_state.p_over_voltage_protection_triggered = true;
        protection_state.charging_enabled = false;
        protection_state.discharging_enabled = false;

        // ������ѹ������
        if (protection_state.p_over_voltage_recovery_timer_count == 0) {
            protection_state.p_over_voltage_recovery_timer_count = 1;
        }

        //P�˹�ѹ�����Ѵ���
    }

    // ����Ƿ���ϻָ�����
    if (protection_state.p_over_voltage_protection_triggered) {
        if (inputs->bus_voltage <= params->p_over_voltage_recovery) {
            // ��ʱ�ָ��߼�
            if (protection_state.p_over_voltage_recovery_timer_count >= params->p_over_voltage_recovery_interval_count) {
                protection_state.p_over_voltage_protection_triggered = false;
                protection_state.charging_enabled = true;
                protection_state.discharging_enabled = true;
                protection_state.p_over_voltage_recovery_timer_count = 0;
                //P�˹�ѹ�����ѻָ�
            } else {
                // ����������
                protection_state.p_over_voltage_recovery_timer_count++;
            }
        } else {
            // ��ѹδ�ָ������ü�����
            protection_state.p_over_voltage_recovery_timer_count = 0;
        }
    }
}


// �����¶ȱ����Ӻ���
void check_environment_temperature_protection(SystemInputs *inputs , ProtectionParameters *params) {
    // �������±���
    if (inputs->environment_temperature > params-> environment_over_temperature_threshold) {
        protection_state.over_temperature_protection_triggered = true;
        protection_state.charging_enabled = false;
        protection_state.discharging_enabled = false;
        //�������±����Ѵ���
    } else if (protection_state.over_temperature_protection_triggered &&
               inputs->environment_temperature <= params-> mos_over_temperature_recovery) {
        protection_state.over_temperature_protection_triggered = false;
        protection_state.charging_enabled = true;
        protection_state.discharging_enabled = true;
        //����Ƿ�±����ѽ��
    }

    // ����Ƿ�±���
    if (inputs->environment_temperature < params-> environment_under_temperature_threshold) {
        protection_state.under_temperature_protection_triggered = true;
        protection_state.charging_enabled = false;
        protection_state.discharging_enabled = false;
        //����Ƿ�±����Ѵ���
    } else if (protection_state.under_temperature_protection_triggered &&
               inputs->environment_temperature >= params-> environment_under_temperature_recovery) {
        protection_state.under_temperature_protection_triggered = false;
        protection_state.charging_enabled = true;
        protection_state.discharging_enabled = true;
        //����Ƿ�±����ѽ��
    }
}

// MOS���ع��¶ȱ����Ӻ���
void check_mos_temperature_protection(SystemInputs *inputs, ProtectionParameters *params) {
    //MOS1�¶ȱ���
    if (inputs->mos_1_temperature > params-> mos_over_temperature_threshold) {
        protection_state.mos_over_temperature_protection_triggered = true;
        protection_state.charging_enabled = false;
        protection_state.discharging_enabled = false;
        //MOS1���عܹ��±����Ѵ������¶�**
    } else if (protection_state.mos_over_temperature_protection_triggered &&
               inputs->mos_1_temperature <= params-> mos_over_temperature_recovery) {
        protection_state.mos_over_temperature_protection_triggered = false;
        protection_state.charging_enabled = true;
        protection_state.discharging_enabled = true;}
        //MOS1���عܹ��±����ѽ��

        //MOS2�¶ȱ���
        if (inputs->mos_2_temperature > params-> mos_over_temperature_threshold) {
            protection_state.mos_over_temperature_protection_triggered = true;
            protection_state.charging_enabled = false;
            protection_state.discharging_enabled = false;
            //MOS2���عܹ��±����Ѵ���
        } else if (protection_state.mos_over_temperature_protection_triggered &&
                   inputs->mos_2_temperature <= params-> mos_over_temperature_recovery) {
            protection_state.mos_over_temperature_protection_triggered = false;
            protection_state.charging_enabled = true;
            protection_state.discharging_enabled = true;}
            //MOS2���عܹ��±����ѽ��
}

// �������� CBC �����߼�
void check_cbc_protection() {
    uint32_t current_time = HAL_GetSysTick(); // ��ȡ��ǰʱ�䣬���赥λ��΢��

    // ���CBC�жϱ�־λ
    if (protection_state.cbc_interrupt_flag) {
        protection_state.cbc_interrupt_flag = false; // �����־λ

        // ������ǵ�һ�δ�������ʼ����ʱ
        if (protection_state.cbc_trigger_count == 0) {
            protection_state.cbc_start_time = current_time;
            protection_state.cbc_trigger_count = 1;
        } else {
            // ���ʱ���� ����ط����޸� ��ֹ�󴥷�
            if ((current_time - protection_state.cbc_start_time) <= 10) {
                protection_state.cbc_trigger_count++;

                // ���1000΢���ڳ���15�δ���
                if (protection_state.cbc_trigger_count > 15) {
                    StopAllEPWMOutput(); // �ض�����PWM

                    // ����CBC����
                    protection_state.cbc_trigger_count = 0;
                }
            } else {
                // ����800΢�룬���ü�����ʱ��
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

    // ��ʼ��CBC��������
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
