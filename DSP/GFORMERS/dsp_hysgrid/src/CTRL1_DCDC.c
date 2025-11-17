#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"

#pragma CODE_SECTION (CTRL1_DC_comp,"ramfuncs")

double CTRL1_DC_comp(struct ADC_conv ADC_p, double i_l_ref, int flag){

	static double int1=0;
	double eta_dc;

	if (flag == 0){
		int1=0;
	}
	else{
		int1+=(i_l_ref-ADC_p.I_l)*Ki_i_dc*Ts;
	}

	eta_dc=(Kp_i_dc*(i_l_ref-ADC_p.I_l)+int1+ADC_p.V_l)/ADC_p.V_h;

	if (eta_dc > 1){
		eta_dc = 1;
	}
	if (eta_dc < -1){
		eta_dc = -1;
	}

	return eta_dc;
}
