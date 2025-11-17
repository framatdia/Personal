#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"

#pragma CODE_SECTION (CTRL2_DC_comp,"ramfuncs")

double CTRL2_DC_comp(struct ADC_conv ADC_p, double vh_ref, int flag){
	double i_l_ref;
	static double int1=0;

	if (flag == 0){int1=0;}
	else{
		int1+=(vh_ref*vh_ref-ADC_p.V_h*ADC_p.V_h)*Ki_v_dc*Ts;
	}

	i_l_ref=(-Kp_v_dc*(vh_ref*vh_ref-ADC_p.V_h*ADC_p.V_h)-int1)/ADC_p.V_l;
	return i_l_ref;

}
