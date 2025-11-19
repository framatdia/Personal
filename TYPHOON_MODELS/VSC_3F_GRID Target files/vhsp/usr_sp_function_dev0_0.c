// generated using template: cop_main.template---------------------------------------------
/******************************************************************************************
**
**  Module Name: cop_main.c
**  NOTE: Automatically generated file. DO NOT MODIFY!
**  Description:
**            Main file
**
******************************************************************************************/
// generated using template: arm/custom_include.template-----------------------------------


#ifdef __cplusplus
#include <limits>

extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <complex.h>
#include <time.h>
#include <stdarg.h>

// x86 libraries:
#include "../include/sp_functions_dev0.h"


#ifdef __cplusplus
}
#endif


// ----------------------------------------------------------------------------------------                // generated using template:generic_macros.template-----------------------------------------
/*********************** Macros (Inline Functions) Definitions ***************************/

// ----------------------------------------------------------------------------------------

#ifndef MAX
#define MAX(value, limit) (((value) > (limit)) ? (value) : (limit))
#endif
#ifndef MIN
#define MIN(value, limit) (((value) < (limit)) ? (value) : (limit))
#endif

// generated using template: VirtualHIL/custom_defines.template----------------------------

typedef unsigned char X_UnInt8;
typedef char X_Int8;
typedef signed short X_Int16;
typedef unsigned short X_UnInt16;
typedef int X_Int32;
typedef unsigned int X_UnInt32;
typedef unsigned int uint;
typedef double real;

// ----------------------------------------------------------------------------------------
// generated using template: custom_consts.template----------------------------------------

// arithmetic constants
#define C_SQRT_2                    1.4142135623730950488016887242097f
#define C_SQRT_3                    1.7320508075688772935274463415059f
#define C_PI                        3.1415926535897932384626433832795f
#define C_E                         2.7182818284590452353602874713527f
#define C_2PI                       6.283185307179586476925286766559f

//@cmp.def.start
//component defines

























































//@cmp.def.end


//-----------------------------------------------------------------------------------------
// generated using template: common_variables.template-------------------------------------
// true global variables





// const variables

//@cmp.var.start
// variables
double _is_a_ia1__out;
double _is_b_ia1__out;
double _is_c_ia1__out;
double _three_phase_pll1_lpf_lpf__out;
double _three_phase_pll1_lpf_lpf__b_coeff[2] = {2.220446049250313e-16, 0.0002467400073613568};
double _three_phase_pll1_lpf_lpf__a_coeff[3] = {1.0, -1.97778894456, 0.9780356845673617};
double _three_phase_pll1_lpf_lpf__a_sum;
double _three_phase_pll1_lpf_lpf__b_sum;
double _three_phase_pll1_lpf_lpf__delay_line_in;
double _three_phase_pll1_pid_integrator1__out;
double _three_phase_pll1_pid_integrator2__out;
double _three_phase_pll1_unit_delay1__out;
double _three_phase_pll1_abc_to_dq_lpf_d__out;
double _three_phase_pll1_abc_to_dq_lpf_d__previous_filtered_value;
double _three_phase_pll1_abc_to_dq_lpf_q__out;
double _three_phase_pll1_abc_to_dq_lpf_q__previous_filtered_value;
double _vm_a_va1__out;
double _vm_b_va1__out;
double _vm_c_va1__out;
double _vs_a_va1__out;
double _vs_b_va1__out;
double _vs_c_va1__out;
double _three_phase_pll1_to_hz__out;
double _three_phase_pll1_sin__out;
double _three_phase_pll1_normalize__in1;
double _three_phase_pll1_normalize__in2;

double _three_phase_pll1_normalize__in2_pu;
double _three_phase_pll1_normalize__pk;

double _three_phase_pll1_abc_to_dq_abc_to_alpha_beta__alpha;
double _three_phase_pll1_abc_to_dq_abc_to_alpha_beta__beta;
double _three_phase_pll1_abc_to_dq_abc_to_alpha_beta__gamma;
double _product2__out;
double _rms_value1__out;
double _product3__out;
double _rms_value2__out;
double _sum7__out;
double _product4__out;
double _rms_value3__out;
double _sum5__out;
double _sum6__out;
double _gain1__out;
double _three_phase_pll1_pid_kd__out;
double _three_phase_pll1_pid_ki__out;
double _three_phase_pll1_pid_kp__out;
double _three_phase_pll1_abc_to_dq_alpha_beta_to_dq__d;
double _three_phase_pll1_abc_to_dq_alpha_beta_to_dq__q;
double _three_phase_pll1_abc_to_dq_alpha_beta_to_dq__k1;
double _three_phase_pll1_abc_to_dq_alpha_beta_to_dq__k2;
double _product7__out;
double _sum3__out;
double _sum8__out;
double _product5__out;
double _product6__out;
double _three_phase_pll1_pid_sum8__out;
double _gain3__out;
double _sum4__out;
double _three_phase_pll1_pid_gain1__out;
double _gain2__out;
double _three_phase_pll1_pid_sum5__out;
double _three_phase_pll1_pid_limit1__out;
double _three_phase_pll1_pid_sum6__out;
double _three_phase_pll1_rate_limiter1__out;

double _three_phase_pll1_rate_limiter1__rising_rate_lim[1];
double _three_phase_pll1_rate_limiter1__falling_rate_lim[1];

double _three_phase_pll1_integrator__in;

double _three_phase_pll1_integrator__out;

double _three_phase_pll1_pid_kb__out;
double _three_phase_pll1_pid_sum7__out;
//@cmp.var.end

//@cmp.svar.start
// state variables
double _three_phase_pll1_lpf_lpf__states[2];
double _three_phase_pll1_pid_integrator1__state;
double _three_phase_pll1_pid_integrator2__state;
double _three_phase_pll1_unit_delay1__state;
double _three_phase_pll1_abc_to_dq_lpf_d__filtered_value;
double _three_phase_pll1_abc_to_dq_lpf_d__previous_in;
double _three_phase_pll1_abc_to_dq_lpf_q__filtered_value;
double _three_phase_pll1_abc_to_dq_lpf_q__previous_in;


double _rms_value1__square_sum;
double _rms_value1__sample_cnt;
double _rms_value1__period_cnt;
double _rms_value1__db_timer;
double _rms_value1__previous_filtered_value;
double _rms_value1__previous_correction;
double _rms_value1__previous_value;
double _rms_value1__correction;
double _rms_value1__out_state;
double _rms_value2__square_sum;
double _rms_value2__sample_cnt;
double _rms_value2__period_cnt;
double _rms_value2__db_timer;
double _rms_value2__previous_filtered_value;
double _rms_value2__previous_correction;
double _rms_value2__previous_value;
double _rms_value2__correction;
double _rms_value2__out_state;
double _rms_value3__square_sum;
double _rms_value3__sample_cnt;
double _rms_value3__period_cnt;
double _rms_value3__db_timer;
double _rms_value3__previous_filtered_value;
double _rms_value3__previous_correction;
double _rms_value3__previous_value;
double _rms_value3__correction;
double _rms_value3__out_state;
double _three_phase_pll1_rate_limiter1__state;
X_Int32 _three_phase_pll1_rate_limiter1__first_step;
double _three_phase_pll1_integrator__state;




//@cmp.svar.end

//
// Tunable parameters
//
static struct Tunable_params {
} __attribute__((__packed__)) tunable_params;

void *tunable_params_dev0_cpu0_ptr = &tunable_params;

// Dll function pointers
#if defined(_WIN64)
#else
// Define handles for loading dlls
#endif





// generated using template: \templates\virtual_hil\fmi_custom_logger_fncs.template---------------------------------




// generated using template: virtual_hil/custom_functions.template---------------------------------
void ReInit_user_sp_cpu0_dev0() {
#if DEBUG_MODE
    printf("\n\rReInitTimer");
#endif
    //@cmp.init.block.start
    X_UnInt32 _three_phase_pll1_lpf_lpf__i;
    for (_three_phase_pll1_lpf_lpf__i = 0; _three_phase_pll1_lpf_lpf__i < 2; _three_phase_pll1_lpf_lpf__i++) {
        _three_phase_pll1_lpf_lpf__states[_three_phase_pll1_lpf_lpf__i] = 0;
    }
    _three_phase_pll1_pid_integrator1__state = 376.99111843;
    _three_phase_pll1_pid_integrator2__state = 0.0;
    _three_phase_pll1_unit_delay1__state = 0.0;
    _three_phase_pll1_abc_to_dq_lpf_d__filtered_value = 0.0 / (1 - 1.0 * 62.83185307 * 0.0001 );
    _three_phase_pll1_abc_to_dq_lpf_d__previous_in = 0x0;
    _three_phase_pll1_abc_to_dq_lpf_q__filtered_value = 0.0 / (1 - 1.0 * 62.83185307 * 0.0001 );
    _three_phase_pll1_abc_to_dq_lpf_q__previous_in = 0x0;
    {
    }
    _rms_value1__square_sum = 0x0;
    _rms_value1__sample_cnt = 0x0;
    _rms_value1__period_cnt = 0x0;
    _rms_value1__db_timer = 0x0;
    _rms_value1__previous_filtered_value = 0x0;
    _rms_value1__previous_correction = 0x0;
    _rms_value1__correction = 0x0;
    _rms_value1__previous_value = 0x0;
    _rms_value1__out_state = 0x0;
    _rms_value2__square_sum = 0x0;
    _rms_value2__sample_cnt = 0x0;
    _rms_value2__period_cnt = 0x0;
    _rms_value2__db_timer = 0x0;
    _rms_value2__previous_filtered_value = 0x0;
    _rms_value2__previous_correction = 0x0;
    _rms_value2__correction = 0x0;
    _rms_value2__previous_value = 0x0;
    _rms_value2__out_state = 0x0;
    _rms_value3__square_sum = 0x0;
    _rms_value3__sample_cnt = 0x0;
    _rms_value3__period_cnt = 0x0;
    _rms_value3__db_timer = 0x0;
    _rms_value3__previous_filtered_value = 0x0;
    _rms_value3__previous_correction = 0x0;
    _rms_value3__correction = 0x0;
    _rms_value3__previous_value = 0x0;
    _rms_value3__out_state = 0x0;
    HIL_OutAO(0x4001, 0.0f);
    HIL_OutAO(0x4002, 0.0f);
    HIL_OutAO(0x4000, 0.0f);
    HIL_OutAO(0x4003, 0.0f);
    _three_phase_pll1_rate_limiter1__state = 0;
    _three_phase_pll1_rate_limiter1__first_step = 1;
    {
        _three_phase_pll1_integrator__state = 0 ;
    }
    //@cmp.init.block.end
}


// Dll function pointers and dll reload function
#if defined(_WIN64)
// Define method for reloading dll functions
void ReloadDllFunctions_user_sp_cpu0_dev0(void) {
    // Load each library and setup function pointers
}

void FreeDllFunctions_user_sp_cpu0_dev0(void) {
}

#else
// Define method for reloading dll functions
void ReloadDllFunctions_user_sp_cpu0_dev0(void) {
    // Load each library and setup function pointers
}

void FreeDllFunctions_user_sp_cpu0_dev0(void) {
}
#endif

void load_fmi_libraries_user_sp_cpu0_dev0(void) {
#if defined(_WIN64)
#else
#endif
}


void ReInit_sp_scope_user_sp_cpu0_dev0() {
    // initialise SP Scope buffer pointer
}


// generated using template: virtual_hil/common_timer_counter_handler.template-------------------------

/*****************************************************************************************/
/**
* This function is the handler which performs processing for the timer counter.
* It is called from an interrupt context such that the amount of processing
* performed should be minimized.  It is called when the timer counter expires
* if interrupts are enabled.
*
*
* @param    None
*
* @return   None
*
* @note     None
*
*****************************************************************************************/

void TimerCounterHandler_0_user_sp_cpu0_dev0() {
#if DEBUG_MODE
    printf("\n\rTimerCounterHandler_0");
#endif
    //////////////////////////////////////////////////////////////////////////
    // Set tunable parameters
    //////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
    // Output block
    //////////////////////////////////////////////////////////////////////////
    //@cmp.out.block.start
    // Generated from the component: Is_a.Ia1
    _is_a_ia1__out = (HIL_InFloat(0xc80000 + 0x20e));
    // Generated from the component: Is_b.Ia1
    _is_b_ia1__out = (HIL_InFloat(0xc80000 + 0x20f));
    // Generated from the component: Is_c.Ia1
    _is_c_ia1__out = (HIL_InFloat(0xc80000 + 0x210));
    // Generated from the component: Vs_a.Va1
    _vs_a_va1__out = (HIL_InFloat(0xc80000 + 0x20b));
    // Generated from the component: Vs_b.Va1
    _vs_b_va1__out = (HIL_InFloat(0xc80000 + 0x20c));
    // Generated from the component: Vs_c.Va1
    _vs_c_va1__out = (HIL_InFloat(0xc80000 + 0x20d));
    // Generated from the component: Product2
    _product2__out = (_vs_a_va1__out * _is_a_ia1__out);
    // Generated from the component: RMS value1
    if (_rms_value1__period_cnt >= 2 * M_PI) {
        _rms_value1__out_state = sqrt(_rms_value1__square_sum / (2 * M_PI));
        _rms_value1__square_sum = 0.0f;
        _rms_value1__period_cnt = fmod(_rms_value1__period_cnt, 2 * M_PI);
    }
    _rms_value1__out = _rms_value1__out_state;
    // Generated from the component: Product3
    _product3__out = (_vs_b_va1__out * _is_b_ia1__out);
    // Generated from the component: RMS value2
    if (_rms_value2__period_cnt >= 2 * M_PI) {
        _rms_value2__out_state = sqrt(_rms_value2__square_sum / (2 * M_PI));
        _rms_value2__square_sum = 0.0f;
        _rms_value2__period_cnt = fmod(_rms_value2__period_cnt, 2 * M_PI);
    }
    _rms_value2__out = _rms_value2__out_state;
    // Generated from the component: Sum7
    _sum7__out = _vs_a_va1__out - _vs_b_va1__out;
    // Generated from the component: Product4
    _product4__out = (_vs_c_va1__out * _is_c_ia1__out);
    // Generated from the component: RMS value3
    if (_rms_value3__period_cnt >= 2 * M_PI) {
        _rms_value3__out_state = sqrt(_rms_value3__square_sum / (2 * M_PI));
        _rms_value3__square_sum = 0.0f;
        _rms_value3__period_cnt = fmod(_rms_value3__period_cnt, 2 * M_PI);
    }
    _rms_value3__out = _rms_value3__out_state;
    // Generated from the component: Sum5
    _sum5__out = _vs_b_va1__out - _vs_c_va1__out;
    // Generated from the component: Sum6
    _sum6__out = _vs_c_va1__out - _vs_a_va1__out;
    // Generated from the component: Product7
    _product7__out = (_sum7__out * _is_c_ia1__out);
    // Generated from the component: Sum3
    _sum3__out = _product2__out + _product3__out + _product4__out;
    // Generated from the component: Sum8
    _sum8__out = _rms_value1__out + _rms_value2__out + _rms_value3__out;
    // Generated from the component: Product5
    _product5__out = (_sum5__out * _is_a_ia1__out);
    // Generated from the component: Product6
    _product6__out = (_sum6__out * _is_b_ia1__out);
    // Generated from the component: p
    HIL_OutAO(0x4002, (float)_sum3__out);
    // Generated from the component: Gain3
    _gain3__out = 0.3333333333333333 * _sum8__out;
    // Generated from the component: Sum4
    _sum4__out = _product5__out + _product6__out + _product7__out;
    // Generated from the component: Vrms
    HIL_OutAO(0x4000, (float)_gain3__out);
    // Generated from the component: Gain2
    _gain2__out = 0.577350269189626 * _sum4__out;
    // Generated from the component: q1
    HIL_OutAO(0x4003, (float)_gain2__out);
//@cmp.out.block.end
    //////////////////////////////////////////////////////////////////////////
    // Update block
    //////////////////////////////////////////////////////////////////////////
    //@cmp.update.block.start
    // Generated from the component: RMS value1
    if (_rms_value1__period_cnt >= 2 * M_PI) {
        _rms_value1__period_cnt = fmod(_rms_value1__period_cnt, 2 * M_PI);
    }
    _rms_value1__period_cnt += 0.015707963267948967;
    _rms_value1__square_sum += _vs_a_va1__out * _vs_a_va1__out * 0.015707963267948967;
    // Generated from the component: RMS value2
    if (_rms_value2__period_cnt >= 2 * M_PI) {
        _rms_value2__period_cnt = fmod(_rms_value2__period_cnt, 2 * M_PI);
    }
    _rms_value2__period_cnt += 0.015707963267948967;
    _rms_value2__square_sum += _vs_b_va1__out * _vs_b_va1__out * 0.015707963267948967;
    // Generated from the component: RMS value3
    if (_rms_value3__period_cnt >= 2 * M_PI) {
        _rms_value3__period_cnt = fmod(_rms_value3__period_cnt, 2 * M_PI);
    }
    _rms_value3__period_cnt += 0.015707963267948967;
    _rms_value3__square_sum += _vs_c_va1__out * _vs_c_va1__out * 0.015707963267948967;
    //@cmp.update.block.end
}
void TimerCounterHandler_1_user_sp_cpu0_dev0() {
#if DEBUG_MODE
    printf("\n\rTimerCounterHandler_1");
#endif
    //////////////////////////////////////////////////////////////////////////
    // Set tunable parameters
    //////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
    // Output block
    //////////////////////////////////////////////////////////////////////////
    //@cmp.out.block.start
    // Generated from the component: Three phase PLL1.LPF.LPF
    X_UnInt32 _three_phase_pll1_lpf_lpf__i;
    _three_phase_pll1_lpf_lpf__a_sum = 0.0f;
    _three_phase_pll1_lpf_lpf__b_sum = 0.0f;
    _three_phase_pll1_lpf_lpf__delay_line_in = 0.0f;
    for (_three_phase_pll1_lpf_lpf__i = 0; _three_phase_pll1_lpf_lpf__i < 2; _three_phase_pll1_lpf_lpf__i++) {
        _three_phase_pll1_lpf_lpf__b_sum += _three_phase_pll1_lpf_lpf__b_coeff[_three_phase_pll1_lpf_lpf__i] * _three_phase_pll1_lpf_lpf__states[_three_phase_pll1_lpf_lpf__i + 0];
    }
    _three_phase_pll1_lpf_lpf__out = _three_phase_pll1_lpf_lpf__b_sum;
    // Generated from the component: Three phase PLL1.PID.Integrator1
    _three_phase_pll1_pid_integrator1__out = _three_phase_pll1_pid_integrator1__state;
    // Generated from the component: Three phase PLL1.PID.Integrator2
    _three_phase_pll1_pid_integrator2__out = _three_phase_pll1_pid_integrator2__state;
    // Generated from the component: Three phase PLL1.Unit Delay1
    _three_phase_pll1_unit_delay1__out = _three_phase_pll1_unit_delay1__state;
    // Generated from the component: Three phase PLL1.abc to dq.LPF_d
    _three_phase_pll1_abc_to_dq_lpf_d__previous_filtered_value = _three_phase_pll1_abc_to_dq_lpf_d__filtered_value;
    _three_phase_pll1_abc_to_dq_lpf_d__filtered_value = _three_phase_pll1_abc_to_dq_lpf_d__previous_in * (1 * 62.83185307 * 0.0001) + _three_phase_pll1_abc_to_dq_lpf_d__previous_filtered_value * (1 - 1 * 62.83185307 * 0.0001 );
    _three_phase_pll1_abc_to_dq_lpf_d__out = _three_phase_pll1_abc_to_dq_lpf_d__filtered_value;
    // Generated from the component: Three phase PLL1.abc to dq.LPF_q
    _three_phase_pll1_abc_to_dq_lpf_q__previous_filtered_value = _three_phase_pll1_abc_to_dq_lpf_q__filtered_value;
    _three_phase_pll1_abc_to_dq_lpf_q__filtered_value = _three_phase_pll1_abc_to_dq_lpf_q__previous_in * (1 * 62.83185307 * 0.0001) + _three_phase_pll1_abc_to_dq_lpf_q__previous_filtered_value * (1 - 1 * 62.83185307 * 0.0001 );
    _three_phase_pll1_abc_to_dq_lpf_q__out = _three_phase_pll1_abc_to_dq_lpf_q__filtered_value;
    // Generated from the component: Vm_a.Va1
    _vm_a_va1__out = (HIL_InFloat(0xc80000 + 0x208));
    // Generated from the component: Vm_b.Va1
    _vm_b_va1__out = (HIL_InFloat(0xc80000 + 0x209));
    // Generated from the component: Vm_c.Va1
    _vm_c_va1__out = (HIL_InFloat(0xc80000 + 0x20a));
    // Generated from the component: Three phase PLL1.to_Hz
    _three_phase_pll1_to_hz__out = 0.15915494309189535 * _three_phase_pll1_lpf_lpf__out;
    // Generated from the component: Three phase PLL1.sin
    _three_phase_pll1_sin__out = sin(_three_phase_pll1_unit_delay1__out);
    // Generated from the component: Three phase PLL1.normalize
    _three_phase_pll1_normalize__in1 = _three_phase_pll1_abc_to_dq_lpf_d__out;
    _three_phase_pll1_normalize__in2 = _three_phase_pll1_abc_to_dq_lpf_q__out;
    {
        _three_phase_pll1_normalize__pk = ( powf ( _three_phase_pll1_normalize__in1 , 2.0 ) + powf ( _three_phase_pll1_normalize__in2 , 2.0 ) ) ;
        _three_phase_pll1_normalize__pk = sqrt ( _three_phase_pll1_normalize__pk ) ;
        if ( _three_phase_pll1_normalize__pk < 0.1 )     {
            _three_phase_pll1_normalize__in2_pu = _three_phase_pll1_normalize__in2 / 0.1 ;
        }
        else     {
            _three_phase_pll1_normalize__in2_pu = _three_phase_pll1_normalize__in2 / _three_phase_pll1_normalize__pk ;
        }
    }
    // Generated from the component: Three phase PLL1.abc to dq.abc to alpha beta
    _three_phase_pll1_abc_to_dq_abc_to_alpha_beta__alpha = (2.0 * _vm_a_va1__out - _vm_b_va1__out - _vm_c_va1__out) * 0.3333333333333333;
    _three_phase_pll1_abc_to_dq_abc_to_alpha_beta__beta = (_vm_b_va1__out - _vm_c_va1__out) * 0.5773502691896258;
    _three_phase_pll1_abc_to_dq_abc_to_alpha_beta__gamma = (_vm_a_va1__out + _vm_b_va1__out + _vm_c_va1__out) * 0.3333333333333333;
    // Generated from the component: Gain1
    _gain1__out = 6.283185307179586 * _three_phase_pll1_to_hz__out;
    // Generated from the component: Three phase PLL1.PID.Kd
    _three_phase_pll1_pid_kd__out = 1.0 * _three_phase_pll1_normalize__in2_pu;
    // Generated from the component: Three phase PLL1.PID.Ki
    _three_phase_pll1_pid_ki__out = 3200.0 * _three_phase_pll1_normalize__in2_pu;
    // Generated from the component: Three phase PLL1.PID.Kp
    _three_phase_pll1_pid_kp__out = 100.0 * _three_phase_pll1_normalize__in2_pu;
    // Generated from the component: Three phase PLL1.term_pk
    // Generated from the component: Three phase PLL1.abc to dq.alpha beta to dq
    _three_phase_pll1_abc_to_dq_alpha_beta_to_dq__k1 = cos(_three_phase_pll1_unit_delay1__out);
    _three_phase_pll1_abc_to_dq_alpha_beta_to_dq__k2 = sin(_three_phase_pll1_unit_delay1__out);
    _three_phase_pll1_abc_to_dq_alpha_beta_to_dq__d = _three_phase_pll1_abc_to_dq_alpha_beta_to_dq__k2 * _three_phase_pll1_abc_to_dq_abc_to_alpha_beta__alpha - _three_phase_pll1_abc_to_dq_alpha_beta_to_dq__k1 * _three_phase_pll1_abc_to_dq_abc_to_alpha_beta__beta;
    _three_phase_pll1_abc_to_dq_alpha_beta_to_dq__q = _three_phase_pll1_abc_to_dq_alpha_beta_to_dq__k1 * _three_phase_pll1_abc_to_dq_abc_to_alpha_beta__alpha + _three_phase_pll1_abc_to_dq_alpha_beta_to_dq__k2 * _three_phase_pll1_abc_to_dq_abc_to_alpha_beta__beta;
    // Generated from the component: f1
    HIL_OutAO(0x4001, (float)_gain1__out);
    // Generated from the component: Three phase PLL1.PID.Sum8
    _three_phase_pll1_pid_sum8__out = _three_phase_pll1_pid_kd__out - _three_phase_pll1_pid_integrator2__out;
    // Generated from the component: Three phase PLL1.PID.Gain1
    _three_phase_pll1_pid_gain1__out = 714.2857 * _three_phase_pll1_pid_sum8__out;
    // Generated from the component: Three phase PLL1.PID.Sum5
    _three_phase_pll1_pid_sum5__out = _three_phase_pll1_pid_kp__out + _three_phase_pll1_pid_gain1__out + _three_phase_pll1_pid_integrator1__out;
    // Generated from the component: Three phase PLL1.PID.Limit1
    _three_phase_pll1_pid_limit1__out = MIN(MAX(_three_phase_pll1_pid_sum5__out, -10000.0), 10000.0);
    // Generated from the component: Three phase PLL1.PID.Sum6
    _three_phase_pll1_pid_sum6__out =  - _three_phase_pll1_pid_sum5__out + _three_phase_pll1_pid_limit1__out;
    // Generated from the component: Three phase PLL1.Rate Limiter1
    _three_phase_pll1_rate_limiter1__rising_rate_lim[0] = 75.39822368615503 * 0.0001;
    _three_phase_pll1_rate_limiter1__falling_rate_lim[0] = -75.39822368615503 * 0.0001;
    if (_three_phase_pll1_rate_limiter1__first_step) {
        _three_phase_pll1_rate_limiter1__out = _three_phase_pll1_pid_limit1__out;
        _three_phase_pll1_rate_limiter1__state = _three_phase_pll1_pid_limit1__out;
    } else {
        _three_phase_pll1_rate_limiter1__out = _three_phase_pll1_pid_limit1__out;
        if (_three_phase_pll1_pid_limit1__out - _three_phase_pll1_rate_limiter1__state > _three_phase_pll1_rate_limiter1__rising_rate_lim[0])
            _three_phase_pll1_rate_limiter1__out = _three_phase_pll1_rate_limiter1__state + (_three_phase_pll1_rate_limiter1__rising_rate_lim[0]);
        if (_three_phase_pll1_pid_limit1__out - _three_phase_pll1_rate_limiter1__state < _three_phase_pll1_rate_limiter1__falling_rate_lim[0])
            _three_phase_pll1_rate_limiter1__out = _three_phase_pll1_rate_limiter1__state + (_three_phase_pll1_rate_limiter1__falling_rate_lim[0]);
    }
    // Generated from the component: Three phase PLL1.integrator
    _three_phase_pll1_integrator__in = _three_phase_pll1_pid_limit1__out;
    {
        _three_phase_pll1_integrator__state += 0.0001 * _three_phase_pll1_integrator__in ;
        if ( _three_phase_pll1_integrator__in >= 0.0 )     {
            if ( _three_phase_pll1_integrator__state >= 6.283185307179586 )         {
                _three_phase_pll1_integrator__state -= 6.283185307179586 ;
            }
        }
        else     {
            if ( _three_phase_pll1_integrator__state <= - 6.283185307179586 )         {
                _three_phase_pll1_integrator__state += 6.283185307179586 ;
            }
        }
        _three_phase_pll1_integrator__out = _three_phase_pll1_integrator__state ;
    }
    // Generated from the component: Three phase PLL1.PID.Kb
    _three_phase_pll1_pid_kb__out = 1.0 * _three_phase_pll1_pid_sum6__out;
    // Generated from the component: Three phase PLL1.PID.Sum7
    _three_phase_pll1_pid_sum7__out = _three_phase_pll1_pid_ki__out + _three_phase_pll1_pid_kb__out;
//@cmp.out.block.end
    //////////////////////////////////////////////////////////////////////////
    // Update block
    //////////////////////////////////////////////////////////////////////////
    //@cmp.update.block.start
    // Generated from the component: Three phase PLL1.LPF.LPF
    for (_three_phase_pll1_lpf_lpf__i = 1; _three_phase_pll1_lpf_lpf__i > 0; _three_phase_pll1_lpf_lpf__i--) {
        _three_phase_pll1_lpf_lpf__a_sum += _three_phase_pll1_lpf_lpf__a_coeff[_three_phase_pll1_lpf_lpf__i + 1] * _three_phase_pll1_lpf_lpf__states[_three_phase_pll1_lpf_lpf__i];
    }
    _three_phase_pll1_lpf_lpf__a_sum += _three_phase_pll1_lpf_lpf__states[0] * _three_phase_pll1_lpf_lpf__a_coeff[1];
    _three_phase_pll1_lpf_lpf__delay_line_in = _three_phase_pll1_rate_limiter1__out - _three_phase_pll1_lpf_lpf__a_sum;
    for (_three_phase_pll1_lpf_lpf__i = 1; _three_phase_pll1_lpf_lpf__i > 0; _three_phase_pll1_lpf_lpf__i--) {
        _three_phase_pll1_lpf_lpf__states[_three_phase_pll1_lpf_lpf__i] = _three_phase_pll1_lpf_lpf__states[_three_phase_pll1_lpf_lpf__i - 1];
    }
    _three_phase_pll1_lpf_lpf__states[0] = _three_phase_pll1_lpf_lpf__delay_line_in;
    // Generated from the component: Three phase PLL1.PID.Integrator1
    _three_phase_pll1_pid_integrator1__state += _three_phase_pll1_pid_sum7__out * 0.0001;
    // Generated from the component: Three phase PLL1.PID.Integrator2
    _three_phase_pll1_pid_integrator2__state += _three_phase_pll1_pid_gain1__out * 0.0001;
    // Generated from the component: Three phase PLL1.Unit Delay1
    _three_phase_pll1_unit_delay1__state = _three_phase_pll1_integrator__out;
    // Generated from the component: Three phase PLL1.abc to dq.LPF_d
    _three_phase_pll1_abc_to_dq_lpf_d__previous_in = _three_phase_pll1_abc_to_dq_alpha_beta_to_dq__d;
    // Generated from the component: Three phase PLL1.abc to dq.LPF_q
    _three_phase_pll1_abc_to_dq_lpf_q__previous_in = _three_phase_pll1_abc_to_dq_alpha_beta_to_dq__q;
    // Generated from the component: Three phase PLL1.normalize
    {
    }
    // Generated from the component: Three phase PLL1.Rate Limiter1
    _three_phase_pll1_rate_limiter1__rising_rate_lim[0] = 75.39822368615503 * 0.0001;
    _three_phase_pll1_rate_limiter1__falling_rate_lim[0] = -75.39822368615503 * 0.0001;
    if (_three_phase_pll1_pid_limit1__out - _three_phase_pll1_rate_limiter1__state > _three_phase_pll1_rate_limiter1__rising_rate_lim[0])
        _three_phase_pll1_rate_limiter1__state += _three_phase_pll1_rate_limiter1__rising_rate_lim[0];
    else  if (_three_phase_pll1_pid_limit1__out - _three_phase_pll1_rate_limiter1__state < _three_phase_pll1_rate_limiter1__falling_rate_lim[0])
        _three_phase_pll1_rate_limiter1__state += (_three_phase_pll1_rate_limiter1__falling_rate_lim[0]);
    else
        _three_phase_pll1_rate_limiter1__state = _three_phase_pll1_pid_limit1__out;
    _three_phase_pll1_rate_limiter1__first_step = 0;
    // Generated from the component: Three phase PLL1.integrator
    {
    }
    //@cmp.update.block.end
}
// ----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------