#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"

#pragma CODE_SECTION (CTRL3_DC_comp,"ramfuncs")

double CTRL3_DC_comp(struct ADC_conv ADC_p, double v_uc_ref, int flag){
	double p_uc_ref;
	static int flag_min=0, flag_max=0;
	static double int1=0;

	if (flag==0){int1=0;}
	else{
		int1+=(v_uc_ref*v_uc_ref-ADC_p.V_l*ADC_p.V_l)*Ki_uc*Ts;
	}

	p_uc_ref=(v_uc_ref*v_uc_ref-ADC_p.V_l*ADC_p.V_l)*Kp_uc+int1;

	if (ADC_p.V_l > v_uc_ref*1.1538 || flag_max == 1){ // Saturacion por arriba
		p_uc_ref=1000;
		flag_max=1;
		if (ADC_p.V_l < v_uc_ref*1.0769){
			p_uc_ref=(v_uc_ref*v_uc_ref-ADC_p.V_l*ADC_p.V_l)*Kp_uc+int1;
			flag_max=0;
		}
	}

	if (ADC_p.V_l < v_uc_ref*0.8077 || flag_min == 1){ // Saturacion por abajo
		p_uc_ref=-1000;
		flag_min=1;
		if (ADC_p.V_l > v_uc_ref*0.8846){
			p_uc_ref=(v_uc_ref*v_uc_ref-ADC_p.V_l*ADC_p.V_l)*Kp_uc+int1;
			flag_min=0;
		}

	}
	return p_uc_ref;
}
