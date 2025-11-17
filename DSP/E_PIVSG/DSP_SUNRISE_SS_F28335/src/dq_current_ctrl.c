#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"
#include "DSP28x_Project.h"

struct duty_cycle Park_inverse(struct PLL_output, struct duty_cycle);

#pragma CODE_SECTION (DQCURRENT_comp,"ramfuncs")
// function DQCURRENT_comp
// Input: Structure--> ADC_conv. DC voltage measurement V_h
// Input: Structure--> PLL_output. omega computation from PLL, voltages and currents in dq
// Input:d current reference
// Input:q current reference
// Input:flag for resetting integrators
// Output: eta_abc
struct duty_cycle DQCURRENT_comp(struct ADC_conv ADC_p, struct PLL_output PLL_dq, double i_d_ref, double i_q_ref, int flag)

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

// a static variable preserves its previous value in its previous scope and is not initialized again in the new scope
// Static variables for integrator
    static double y_d = 0, y_q=0;
// Static variables for error
	static double e_d = 0, e_q=0;
	static double etad = 0, etaq=0;
	static double x_etad = 0, x_etaq=0;

// notch filter
	static double B_n = 0.499849000000000;
	static double K_n3 = 0.7285; //
	static double A_n3 = 1.999013120731463;
	static double x_etad_1 = 0, x_etaq_1=0;
	static double x_etad_2 = 0, x_etaq_2=0;
	static double etad_1 = 0, etaq_1=0;
	static double etad_2 = 0, etaq_2=0;

	static double y_i_2_d2=0,y_i_1_d2=0,y_i_d2=0,u_i_2_d2=0,u_i_1_d2=0,u_i_d2=0;
    static double y_v_2_d2=0,y_v_1_d2=0,y_v_d2=0,u_v_2_d2=0,u_v_1_d2=0,u_v_d2=0;
    static double y_i_2_q2=0,y_i_1_q2=0,y_i_q2=0,u_i_2_q2=0,u_i_1_q2=0,u_i_q2=0;
    static double y_v_2_q2=0,y_v_1_q2=0,y_v_q2=0,u_v_2_q2=0,u_v_1_q2=0,u_v_q2=0;
    double Ts_cwt = 0.00004997532801828658, cwt_2 = 1.999013120731463;

// Structure duty_cycle assigns to variable s and eta
	struct duty_cycle s={0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, eta={0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7
	    ///////////PI DQ CURRENT CONTROLLER///////////////

// Initialization and reset of integrator. Variable flag is used for reset. If flag is equal to 1, integrator is exectuded. Otherwise is zero
	if (flag == 0){
	    y_d = 0.0;
	    y_q = 0.0;
	}

// error in dq axes
//Typhonsim e_d = is_dq_ref[0] - is_dq[0];
//Typhonsim	e_q = is_dq_ref[1] - is_dq[1];

#if AHF_2nd == 1
	// Resonant (2nd) at current control
    y_i_d2 = (- PLL_dq.I_d)*Ts - u_i_1_d2*Ts_cwt + y_i_1_d2*cwt_2 - y_i_2_d2;
    y_i_q2 = (- PLL_dq.I_q)*Ts - u_i_1_q2*Ts_cwt + y_i_1_q2*cwt_2 - y_i_2_q2;

    y_i_2_d2 = y_i_1_d2;
    y_i_1_d2 = y_i_d2;
    u_i_2_d2 = u_i_1_d2;
    u_i_1_d2 = u_i_d2;
#elif AHF_2nd == 2
    // Resonant (2nd) at voltage control
    y_v_d2 = (- PLL_dq.V_d)*Ts - u_v_1_d2*Ts_cwt + y_v_1_d2*cwt_2 - y_v_2_d2;
    y_v_q2 = (- PLL_dq.V_q)*Ts - u_v_1_q2*Ts_cwt + y_v_1_q2*cwt_2 - y_v_2_q2;

    y_v_2_d2 = y_v_1_d2;
    y_v_1_d2 = y_v_d2;
    u_v_2_d2 = u_v_1_d2;
    u_v_1_d2 = u_v_d2;
#endif

    e_d = i_d_ref - PLL_dq.I_d + y_v_d2;
    e_q = i_q_ref - PLL_dq.I_q + y_v_q2;

//Computation of the eta signals: PI ctrl+cross-coupling-term cancellation+feedforward signals
//Typhonsim //modulating signal computation eta_d = (2/v_dc) * (Kp_i*e_d + y_d -   L*omega*is_dq[1] + vs_dq[0]);
//Typhonsim //modulating signal computation eta_q = (2/v_dc )* (Kp_i*e_q + y_q +  L*oemga*is_dq[0] + vs_dq[1]);
	//s.eta_d = (2.0/ADC_p.V_h)*(Kp_i*e_d + Ki_i*y_d - PLL_dq.omega*(L)*PLL_dq.I_q + PLL_dq.V_d);
	//s.eta_q = (2.0/ADC_p.V_h)*(Kp_i*e_q + Ki_i*y_q + PLL_dq.omega*(L)*PLL_dq.I_d + PLL_dq.V_q);
	etad = (2.0/ADC_p.V_h)*(Kp_i*e_d + Ki_i*y_d - PLL_dq.omega*(L)*PLL_dq.I_q + PLL_dq.V_d + y_i_d2);
	etaq = (2.0/ADC_p.V_h)*(Kp_i*e_q + Ki_i*y_q + PLL_dq.omega*(L)*PLL_dq.I_d + PLL_dq.V_q + y_i_q2);
	//x_etad = x_etad + Ts*2*M_PI*1/(tau_vsg)*(etad - x_etad);
	//x_etaq = x_etaq + Ts*2*M_PI*1/(tau_vsg)*(etaq - x_etaq);
	//s.eta_d = x_etad;
	//s.eta_q = x_etaq;
	x_etad = K_n3*etad - A_n3*(K_n3*etad_1 - 0.707*x_etad_1) + K_n3*etad_2 - B_n*x_etad_2;
	x_etaq = K_n3*etaq - A_n3*(K_n3*etaq_1 - 0.707*x_etaq_1) + K_n3*etaq_2 - B_n*x_etaq_2;
	s.eta_d = x_etad;
	s.eta_q = x_etaq;

	etad_2 = etad_1;
	etad_1 = etad;
	x_etad_2 = x_etad_1;
	x_etad_1 = x_etad;
	etaq_2 = etaq_1;
	etaq_1 = etaq;
	x_etaq_2 = x_etaq_1;
	x_etaq_1 = x_etaq;
	//i_sdq_f.q = i3_sdq.q - A_n3*(i3_sdq1.q - 0.99*i3_sdq1_f.q) + i3_sdq2.q - B_n*i3_sdq2_f.q;

// Reset of the integrator. Variable flag is used for reset. If flag is equal to 1, integrator is exectuded. Otherwise is zero
	if (flag == 1){
	    //TyphoonSim //integrator y_d = y_d + Ki_i*Ts_Control*e_d;
	    //TyphoonSim //integrator y_q = y_q + Ki_i*Ts_Control*e_q;
	    y_d = y_d + e_d*Ts;
	    y_q = y_q + e_q*Ts;
	}
	         ///////////PI DQ CURRENT CONTROLLER///////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////7

// eta transformation from dq to abc
	eta = Park_inverse(PLL_dq, s);
// Return structure eta (eta_a,eta_b,eta_c). Output of the function DQCURRENT_comp
	return eta;
}


