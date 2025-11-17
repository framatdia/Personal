#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"

#pragma CODE_SECTION (E_PI_VSG_comp,"ramfuncs")
// function DQCURRENT_comp
// Input: Active power reference
// Input: Reactive power reference
// Input: Structure--> ADC_conv. DC voltage measurement V_h
// Input: Structure--> PLL_output. omega computation from VSG, voltages and currents in dq
// Input: execution of the FMS
// Output: Structure--> uvsg where the current references are computed

struct uvsg E_PI_VSG_comp(double P_ref, double Q_ref, struct ADC_conv ADC_p, struct PLL_output PLL_Park, double runFSM)
{

// Correspondence between TyphoonSim <---> CCS
// The dq transformation of the voltages and currents are done in the function PLL_dq located in the C-file PLL_Park_transformation. Therefore, we can use the current and voltage in dq just the input PLL_Park
// Kp_p <---> Kp_p
// Ki_p <---> Ki_p
// Kp_q <---> Kp_q
// Ki_q <---> Ki_q
// Xv <---> Xv
// Rv <---> Rv
// x_isd <---> x_isd
// x_isq <---> x_isq
// tau_vsg <---> tau_vsg
// e_o <---> 1.0
// Ts_control <---> Ts
// omega_base <---> omega_ref
// p_m_ref <---> p_pu_ref. Associated to P_ref in W
// q_s_ref <---> q_pu_ref. Associated to Q_ref Var
// is_dq_ref[0] <---> i_d_ref
// is_dq_ref[1] <---> i_q_ref
// omega_vsg <---> u.omega
// theta_vsg <---> u.theta
// e <---> e
// p_s <---> u.p_s
// q_s <---> u.q_s
// vs_d <---> vd_pu. Associated to PLL_Park.V_d in V
// vs_q <---> vq_pu. Associated to PLL_Park.V_q in V
// is_d <---> id_pu. Associated to PLL_Park.I_d in V
// is_q <---> iq_pu. Associated to PLL_Park.I_d in V
// e_p <---> ep
// e_q <---> eq
// is_dq_ref_fil[0] <---> u.i_d_ref
// is_dq_ref_fil[1] <---> u.i_q_ref
// x_p <---> int1
// x_q <---> int3
// theta <---> int2

// 2.0*M_PI*50.0  <---> omega_b
//variable for omega_o, vdq pu, idq pu, electromotive force, integrators, omega base, dq currente references LPF
	static double omega_ref=0, vd_pu=0, vq_pu=0, id_pu=0, iq_pu=0, p_pu_ref=0, q_pu_ref=0, e=0, ep=0, eq=0, int1=0, int2=0, int3=0, int4=omega_b, i_d_ref_ant=0, i_q_ref_ant=0;
    static double i_d_ref = 0, i_q_ref =0, x_isd =0, x_isq =0, x_vsd=0.0, x_vsq=0.0;
    static double u_der = 0.0, x_p_hpf = 0.0, x_p_lpf = 0.0, u_p = 0.0, der_u = 0.0;
// structure of the uvsg
	struct uvsg u;



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	    ///////////PI VSG CONTROLLER///////////////
	//voltage and current in pu. Voltage and currents in V and A: PLL_Park.V_d, PLL_Park.V_q, PLL_Park.I_d, PLL_Park.I_q must be converted to pu.
	    vd_pu=PLL_Park.V_d*0.003061862178479; //Conversion to pu 1/Ubdq U_bdq = 326.5986
	    vq_pu=PLL_Park.V_q*0.003061862178479; //Conversion to pu 1/Ubdq U_bdq = 326.5986
	    id_pu=PLL_Park.I_d*0.02449414855676; //Conversion to pu 1/I_bdq I_bdq = 40.8248
	    iq_pu=PLL_Park.I_q*0.02449414855676; //Conversion to pu 1/I_bdq I_bdq = 40.8248

	//Active and reactive power references in pu. Active and reactive power references: P_ref and Q_ref must be converted to pu
	    p_pu_ref=P_ref*0.00005; //Conversion to pu Sb = 20000
	    q_pu_ref=Q_ref*0.00005; //Conversion to pu Sb = 20000

	//Before starting the state machine, the reference frequency used is that of the PLL. Afterwards it is set to 1 p.u. This is done to avoid a large transition of connection to the grid.
	    if (runFSM>0.5){
	        omega_ref=1; // omega_ref is 1 pu.
	    }
	    else{
	        omega_ref=PLL_Park.omega*0.0031830988618379; //// omega_ref is computed from the PLL p.u 1/(2*pi*50)
	    }

	// Actual power computation in pu
	//TyphoonSim: p_s = (is_d* vs_d + is_q*vs_q);
	//TyphoonSim: q_s = (is_d* vs_q - is_q*vs_d);
	    //u.p_s=id_pu*vd_pu+iq_pu*vq_pu;
	    //u.q_s=id_pu*vq_pu-iq_pu*vd_pu;
	    u.p_s = (ADC_p.V_a*ADC_p.I_a + ADC_p.V_b*ADC_p.I_b + ADC_p.V_c*ADC_p.I_c)*0.00005;
	    u.q_s = ((ADC_p.V_b - ADC_p.V_c)*ADC_p.I_a  + (ADC_p.V_c - ADC_p.V_a)*ADC_p.I_b + (ADC_p.V_a - ADC_p.V_b)*ADC_p.I_c)*0.00005*0.577350269189626;

	// Outputs of the active power control
	// TyphoonSim: e_p = p_m_ref - p_s;
	// TyphoonSim: omega_vsg = (Kp_p*e_p + x_p + omega_base)*2.0*M_PI*50.0;
	    ep = (p_pu_ref-u.p_s);
	    //u.omega=(Kp_p*ep+int1+omega_ref)*omega_b;
	    u.omega = ((F*ep + int1)*1/K + omega_ref)*omega_b;
	//TyphoonSim: theta_vsg= theta;
	    u.theta=int2;
	//compute sin and cos from theta for the dq transformation.
	    u.sin=sin(u.theta);
	    u.cos=cos(u.theta);

	// Outputs of the reactive power control
	// TyphoonSim: e_q = q_s_ref - q_s;;
	// TyphoonSim: e = e_o + Kp_q*e_q + x_q;
	    eq = (q_pu_ref-u.q_s);
	    //e=1.0+Kp_q*eq+int3;
	    u.e_q=-(1.0+Kp_q*eq+int3);

	// Virtual  current reference computation in pu I_bdq: 40.824799999999939
	// TyphoonSim: is_dq_ref[0] = -I_bdq*(Xv*e + Rv*vs_d + Xv*vs_q)/(pow(Rv,2)+pow(Xv,2));
	// TyphoonSim: is_dq_ref[1] = -I_bdq*(Rv*e + Rv*vs_q - Xv*vs_d)/(pow(Rv,2)+pow(Xv,2));
	    i_d_ref=-40.824799999999939*(-(Xv*u.e_q)+Rv*vd_pu+Xv*vq_pu)/(Rv*Rv+Xv*Xv);
	    i_q_ref=-40.824799999999939*(-(Rv*u.e_q)+Rv*vq_pu-Xv*vd_pu)/(Rv*Rv+Xv*Xv);

	    //x_vsd = x_vsd + Ts*2*M_PI*1/(tau_vsg)*(vd_pu - x_vsd);
	    //x_vsq = x_vsq + Ts*2*M_PI*1/(tau_vsg)*(vq_pu - x_vsq);
	    //i_d_ref=-40.824799999999939*(-(u.e_q)+x_vsq)/(Xv);
	    //i_q_ref=-40.824799999999939*(-x_vsd)/(Xv);
	// LPF filter implementation for current references // 2.4 ms
	// TyphoonSim:  x_isd = x_isd + Ts_Control*2*M_PI*1/(tau_vsg)*(is_dq_ref[0] - x_isd);
	// TyphoonSim:  x_isq = x_isq + Ts_Control*2*M_PI*1/(tau_vsg)*(is_dq_ref[1] - x_isq);
	    //x_isd = x_isd + Ts*2*M_PI*1/(tau_vsg)*(i_d_ref - x_isd);
	    //x_isq = x_isq + Ts*2*M_PI*1/(tau_vsg)*(i_q_ref - x_isq);
	    //u.i_d_ref = x_isd;
	    //u.i_q_ref = x_isq;
	    u.i_d_ref = i_d_ref;
	    u.i_q_ref = i_q_ref;

	//Integrator of the APCL and RPCL
	//TyphoonSim integrator PI active and reactive power if runFSM is > 0.5. Otherwise 0
	    if (runFSM>0.5){
	//TyphoonSim: x_p = x_p + Ki_p*Ts_Control*e_p;
	//TyphoonSim: x_q = x_q + Ki_q*Ts_Control*e_q;
	        x_p_lpf = (x_p_lpf +  Ts/T_filter*(ep*Gain_lpf - x_p_lpf));
	        der_u = (ep*Gain_hpf - u_der)/Ts;
	        u_der = ep*Gain_hpf;
	        x_p_hpf = (x_p_hpf +  Ts/T_filter*(T_filter*der_u - x_p_hpf));
	        u_p = x_p_lpf + x_p_hpf;
	        int1=int1+Ki_p*u_p*Ts;
	        int3=int3+Ki_q*eq*Ts;
	    }
	    else{
	        int1=0;
	        int3=0;
	    }

	//TyphoonSim: theta = theta + omega_vsg*Ts_Control;
	    int2=int2+u.omega*Ts;
	//TyphoonSim: reset of theta every 2*pi;
	    if (int2 > 6.283185307179586){
	        int2=int2-6.283185307179586;
	     }
	//  u.omega_rads=int4+(-int4+u.omega)*Ts;

	     ///////////PI VSG CONTROLLER///////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////

// Return the structure u_vsg-->u which contains the current references for the current controller.
	return u;

}
