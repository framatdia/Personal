#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"
#include "DSP28x_Project.h"


#if MODULATION == 1

#pragma CODE_SECTION (sector_comp,"ramfuncs")
struct duty_cycle sector_comp(double v_h, double vref, double phref){
	double eta1=0, eta2=0, eta3=0, a=0, b=0;
	struct duty_cycle eta;
	int sector=0;

	if (phref< M_PI){

		if (phref>=0 && phref<1.047197551){
			a=phref;
			sector=1;
		}
		else if (phref>=1.047197551 && phref<2.0943951){
			a=phref-1.047197551;
			sector=2;
		}
		else {
			a=phref-2.0943951;
			sector=3;
		}
	}
	else {
		if (phref>=M_PI && phref<4.1887902){
			a=phref-M_PI;
			sector=4;
		}
		else if (phref>=4.1887902 && phref<5.23598775598){
			a=phref-4.1887902;
			sector=5;
		}
		else {
			a=phref-5.23598775598;
			sector=6;
		}
	}
	b=1.7320508*vref/v_h;
	eta1=b*(sin(1.047197551-a));
	eta2=b*(sin(a));
	eta3=(1-eta1-eta2)*0.5;

	if (sector==1){
		eta.eta_a=eta1+eta2+eta3;
		eta.eta_b=eta2+eta3;
		eta.eta_c=eta3;
	}

	else if (sector==2){
		eta.eta_a=eta1+eta3;
		eta.eta_b=eta1+eta2+eta3;
		eta.eta_c=eta3;
	}

	else if (sector==3){
		eta.eta_a=eta3;
		eta.eta_b=eta1+eta2+eta3;
		eta.eta_c=eta2+eta3;
	}

	else if (sector==4){
		eta.eta_a=eta3;
		eta.eta_b=eta1+eta3;
		eta.eta_c=eta1+eta2+eta3;
	}

	else if (sector==5){
		eta.eta_a=eta2+eta3;
		eta.eta_b=eta3;
		eta.eta_c=eta1+eta2+eta3;
	}

	else {
		eta.eta_a=eta1+eta2+eta3;
		eta.eta_b=eta3;
		eta.eta_c=eta1+eta3;
	}

	return eta;

}
#pragma CODE_SECTION (CTRL1_comp,"ramfuncs")
struct duty_cycle CTRL1_comp(struct ADC_conv ADC_p, struct PLL_output PLL_dq, double theta, double omega, double i_d_ref, double i_q_ref, int flag)
{
	double vd_ref=0, vq_ref=0;
	double vref=0, phref=0;
	struct duty_cycle eta = {0,0,0,0,0,0,0,0,0};
	static double int2 = 0;
	static double int3 = 0;
    vd_ref = -omega*(0.0025)*PLL_dq.I_q + PLL_dq.V_d + K_i_p*(i_d_ref - PLL_dq.I_d) + int2;
    vq_ref =  omega*(0.0025)*PLL_dq.I_d + PLL_dq.V_q + K_i_p*(i_q_ref - PLL_dq.I_q) + int3;

	vref=sqrt(vd_ref*vd_ref+vq_ref*vq_ref);
	phref=atan(vq_ref/vd_ref);

	if ((vq_ref > 0 && vd_ref < 0) || (vq_ref < 0 && vd_ref < 0)){
	    phref+=M_PI;
	}
	phref+=theta;


	// Refresh static variables
	if (flag == 1){
		int2+= K_i_i*(i_d_ref - PLL_dq.I_d)*Ts;
		int3+= K_i_i*(i_q_ref - PLL_dq.I_q)*Ts;
	}

	else{
        int2 = 0.0;
        int3 = 0.0;
        vref=326.7;
        phref=theta-M_PI_2;

    }
	  if(phref>6.2831853){phref-=6.2831853;}
	  else if(phref<0){phref+=6.2831853;}

	  eta = sector_comp(ADC_p.V_h, vref, phref);
	return eta;
}

#elif MODULATION == 0

struct duty_cycle Park_inverse(struct PLL_output, struct duty_cycle);		// Park Inverse

#pragma CODE_SECTION (STATCOM_comp,"ramfuncs")
struct duty_cycle STATCOM_comp(struct ADC_conv ADC_p, struct PLL_output PLL_dq, double theta, double omega, double i_d_ref, double vh_ref, int flag)
{
	// Static variables
	static double int2 = 0, int3=0, int4 = 0, i_q_ref = 0;
#if CTRLVdc_2 != 0    //square of the voltages
    static double vh_2 = 0.0, p_ref = 0.0, vh_ref1 = 0;
#endif

	if (flag == 0){
		int2 = 0.0;
		int3 = 0.0;
		int4 = 0.0;
	}

	// Structures
	struct duty_cycle s, eta;

	// Compute variables

#if CTRLVdc_2 == 0          //square of the voltages
  i_q_ref = ((vh_ref-ADC_p.V_h)*Kp_dc + int4);
  s.eta_d = (2.0/ADC_p.V_h)*(-omega*(0.005)*PLL_dq.I_q + PLL_dq.V_d + K_i_p*(i_d_ref - PLL_dq.I_d) + int2);
  s.eta_q = (2.0/ADC_p.V_h)*( omega*(0.005)*PLL_dq.I_d + PLL_dq.V_q + K_i_p*(i_q_ref - PLL_dq.I_q) + int3);
#else
  vh_ref1 = vh_ref*vh_ref;
  vh_2 = ADC_p.V_h*ADC_p.V_h;
  p_ref = -((vh_ref1-vh_2)*Kp_dc + int4);
  i_q_ref=0.66666666666667*((p_ref*PLL_dq.V_q))/(PLL_dq.V_d*PLL_dq.V_d+PLL_dq.V_q*PLL_dq.V_q);
  s.eta_d = (2.0/ADC_p.V_h)*(-omega*(0.005)*PLL_dq.I_q + PLL_dq.V_d + K_i_p*(i_d_ref - PLL_dq.I_d) + int2);
  s.eta_q = (2.0/ADC_p.V_h)*( omega*(0.005)*PLL_dq.I_d + PLL_dq.V_q + K_i_p*(i_q_ref - PLL_dq.I_q) + int3);

#endif

    // Refresh static variables
    if (flag == 1){
//      int2 = int2 + K_i_i*(i_d_ref - PLL_dq.I_d)*Ts;
//      int3 = int3 + K_i_i*(i_q_ref - PLL_dq.I_q)*Ts;
//      int4 = int4 + Ki_dc * (vh_ref - ADC_p.V_h)*Ts;
  int2 = int2 + K_i_i*(i_d_ref - PLL_dq.I_d)*Ts;
  int3 = int3 + K_i_i*(i_q_ref - PLL_dq.I_q)*Ts;
#if CTRLVdc_2 == 0
  int4 = int4 + Ki_dc * (vh_ref - ADC_p.V_h)*Ts;
#else
  int4 = int4 + Ki_dc * (vh_ref1 - vh_2)*Ts;
#endif
    }

	eta = Park_inverse(PLL_dq, s);
	// Return structure
	return eta;
}

#endif
