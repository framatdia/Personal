#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"
#include "DSP28x_Project.h"

struct duty_cycle Park_inverse(struct PLL_output, struct duty_cycle);

#pragma CODE_SECTION (OL_comp,"ramfuncs")
// function DQCURRENT_comp
// Input: Structure--> ADC_conv. DC voltage measurement V_h
// Input: Structure--> PLL_output. omega computation from PLL, voltages and currents in dq
// Input:d current reference
// Input:q current reference
// Input:flag for resetting integrators
// Output: eta_abc
struct duty_cycle OL_comp(struct ADC_conv ADC_p, struct PLL_output PLL_dq,  double e_q_ref, int flag)

{
// Correspondence between TyphoonSim <---> CCS
// y_d <---> y_d
// y_q <---> y_q
// e_d <---> e_d
// e_q <---> e_q
// L <---> L
// Kp_i <---> Kp_i
// Ki_i <---> Ki_i
// is_dq[0]  <---> PLL_dq.I_d
// is_dq[1]  <---> PLL_dq.I_q
// vs_dq[0] <---> PLL_dq.V_d
// vs_dq[1] <---> PLL_dq.V_q
// omega_pll <---> PLL_dq.omega
// is_dq_ref[0] <--->  i_d_ref
// is_dq_ref[1]  <---> i_q_ref
// v_dc <---> ADC_p.V_h
// Ts_Control <---> Ts
// eta_d <---> s.eta_d
// eta_q <---> s.eta_q

    // Structure duty_cycle assigns to variable s and eta
    struct duty_cycle s={0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, eta={0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    static double v_td = 0, v_tq=0;
    v_td = 0.0;
    v_tq = e_q_ref*325.2691;
    s.eta_d = v_td*(2.0/ADC_p.V_h);
    s.eta_q = v_tq*(2.0/ADC_p.V_h);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7

// eta transformation from dq to abc
	eta = Park_inverse(PLL_dq, s);
// Return structure eta (eta_a,eta_b,eta_c). Output of the function DQCURRENT_comp
	return eta;
}


