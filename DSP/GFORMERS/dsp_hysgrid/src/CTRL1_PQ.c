#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"

#if MODULATION == 1

struct duty_cycle sector_comp(double v_h, double vref, double phref);

#pragma CODE_SECTION (CTRL1_PQ_comp,"ramfuncs")
struct duty_cycle CTRL1_PQ_comp(struct ADC_conv ADC_p, struct PLL_output PLL_dq, double omega, double p_pu_ref, double q_pu_ref, int flag)
{
	double vd_ref=0, vq_ref=0, i_d_ref=0, i_q_ref=0, P_ref=0, Q_ref=0, vref=0, phref=0;
	struct duty_cycle eta;
	// Static variables
	static double int2 = 0;
	static double int3 = 0;

	// idq setpoint computation
	P_ref=p_pu_ref*20000;
	Q_ref=q_pu_ref*20000;
	i_d_ref=0.66666666666667*((P_ref*PLL_dq.V_d)+(Q_ref*PLL_dq.V_q))/(PLL_dq.V_d*PLL_dq.V_d+PLL_dq.V_q*PLL_dq.V_q);
	i_q_ref=0.66666666666667*((P_ref*PLL_dq.V_q)+(Q_ref*PLL_dq.V_d))/(PLL_dq.V_d*PLL_dq.V_d+PLL_dq.V_q*PLL_dq.V_q);

    vd_ref = -omega*(0.0025)*PLL_dq.I_q + PLL_dq.V_d + 1.5*(i_d_ref - PLL_dq.I_d) + int2;
    vq_ref =  omega*(0.0025)*PLL_dq.I_d + PLL_dq.V_q + 1.5*(i_q_ref - PLL_dq.I_q) + int3;

	vref=sqrt(vd_ref*vd_ref+vq_ref*vq_ref);
	phref=atan(vq_ref/vd_ref);

	if ((vq_ref > 0 && vd_ref < 0) || (vq_ref < 0 && vd_ref < 0)){
	    phref+=M_PI;
	}
	phref+=PLL_dq.theta;


	// Refresh static variables
	if (flag == 1){
		int2+= K_i_i*(i_d_ref - PLL_dq.I_d)*50e-6;
		int3+= K_i_i*(i_q_ref - PLL_dq.I_q)*50e-6;
	}

	else{
        int2 = 0.0;
        int3 = 0.0;
        vref=326.7;
        phref=PLL_dq.theta-M_PI_2;

    }
	  if(phref>6.2831853){phref-=6.2831853;}
	  else if(phref<0){phref+=6.2831853;}

	  eta = sector_comp(ADC_p.V_h, vref, phref);
	return eta;
}

#elif MODULATION == 0

struct duty_cycle Park_inverse(struct PLL_output, struct duty_cycle);		// Park Inverse

#pragma CODE_SECTION (CTRL1_PQ_comp,"ramfuncs")
struct duty_cycle CTRL1_PQ_comp(struct ADC_conv ADC_p, struct PLL_output PLL_dq, double omega, double P_pu_ref, double Q_pu_ref, int flag)
{
	// Static variables
	static double int2 = 0;
	static double int3 = 0;
	static double P_ref=0;
	static double Q_ref=0;
	static double i_d_ref=0;
	static double i_q_ref=0;

	if (flag == 0){
		int2 = 0.0;
		int3 = 0.0;
	}

	// Structures
	struct duty_cycle s, eta;

	P_ref=P_pu_ref*20000;
	Q_ref=Q_pu_ref*20000;
	i_d_ref=0.66666666666667*((P_ref*PLL_dq.V_d)+(Q_ref*PLL_dq.V_q))/(PLL_dq.V_d*PLL_dq.V_d+PLL_dq.V_q*PLL_dq.V_q);
	i_q_ref=0.66666666666667*((P_ref*PLL_dq.V_q)+(Q_ref*PLL_dq.V_d))/(PLL_dq.V_d*PLL_dq.V_d+PLL_dq.V_q*PLL_dq.V_q);

	// Compute variables
	s.eta_d = (2.0/ADC_p.V_h)*(-omega*(0.0025)*PLL_dq.I_q + PLL_dq.V_d + K_i_p*(i_d_ref - PLL_dq.I_d) + int2);
	s.eta_q = (2.0/ADC_p.V_h)*(omega*(0.0025)*PLL_dq.I_d + PLL_dq.V_q + K_i_p*(i_q_ref - PLL_dq.I_q) + int3);

	// Refresh static variables
	if (flag == 1){
		int2 = int2 + K_i_i*(i_d_ref - PLL_dq.I_d)*50e-6;
		int3 = int3 + K_i_i*(i_q_ref - PLL_dq.I_q)*50e-6;
	}

	eta = Park_inverse(PLL_dq, s);

	// Return structure
	return eta;
}

#endif




