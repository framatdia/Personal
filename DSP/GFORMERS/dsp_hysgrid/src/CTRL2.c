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
		int2+= K_i_i*(i_d_ref - PLL_dq.I_d)*50e-6;
		int3+= K_i_i*(i_q_ref - PLL_dq.I_q)*50e-6;
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

#pragma CODE_SECTION (CTRL2_comp,"ramfuncs")
struct duty_cycle CTRL2_comp(struct ADC_conv ADC_p, struct PLL_output PLL_dq, double theta, double omega, double v_d_ref, double v_q_ref, int flag)
{
	// Static variables
	static double int2 = 0.0, int3=0.0, int4=0.0, int5=0.0, i_d_ref=0.0, i_q_ref=0.0, i_t_d=0.0, i_t_q=0.0;
	static double K_v_p = 0.1, K_v_i = 0.1, K_c_p = 15.1, K_c_i = 0.1;
	//static double y_aux_d2 = 0, y_aux_q2 = 0, y_aux_1_d2 = 0, y_aux_1_q2 = 0, u_aux_1_d2 = 0, u_aux_1_q2 = 0, y_aux_2_d2 = 0, y_aux_2_q2 = 0;
    //static double y_aux_d6 = 0, y_aux_q6 = 0, y_aux_1_d6 = 0, y_aux_1_q6 = 0, u_aux_1_d6 = 0, u_aux_1_q6 = 0, y_aux_2_d6 = 0, y_aux_2_q6 = 0;
	//static double v_d_ref1 = 0.0, v_q_ref1 = 0.0;
    //static double v_d_fil = 0.0, v_q_fil = 0.0,v_d_ant = 0.0, v_q_ant = 0.0;
    //static double r2=1.0;
    //double Yd=0.3;
    #if (DEVICE == 0)
	    double L = 0.4e-3, C = 30e-6;
    #elif (DEVICE == 1 || DEVICE == 2 || DEVICE == 3 || DEVICE == 4)
        double L = 1.25e-3, C = 4e-6;
    #else
        double L = 2.5e-3, C = 1e-6;
    #endif

	//double cwt_2[1]  = {1.999013120731463, 1.991123929206160};
	//double Ts_cwt[1] = {0.00004997532801828658, 0.00004977809823015400};
	if (flag == 0){
		int2 = 0.0;
		int3 = 0.0;
		int4 = 0.0;
		int5 = 0.0;
	}

	// Structures
	struct duty_cycle s, eta;
/*
	// Rate limiter
	if (v_d_ref1 < v_d_ref){
	    v_d_ref1 = v_d_ref1 + 0.00025;
	}
	else if (v_d_ref1 > v_d_ref){
	    v_d_ref1 = v_d_ref1 - 0.00025;
	}
	else{
	    v_d_ref1 = v_d_ref;
	}
    if (v_q_ref1 < v_q_ref){
        v_q_ref1 = v_q_ref1 + 0.00025;
    }
    else if (v_q_ref1 > v_q_ref){
        v_q_ref1 = v_q_ref1 - 0.00025;
    }
    else{
        v_q_ref1 = v_q_ref;
    }
*/
    //harmonics
    // Neg Seq
    /*y_aux_d2 = (- PLL_dq.V_d)*50e-6 - u_aux_1_d2*Ts_cwt[0] + y_aux_1_d2*cwt_2[0] - y_aux_2_d2;
    y_aux_q2 = (- PLL_dq.V_q)*50e-6 - u_aux_1_q2*Ts_cwt[0] + y_aux_1_q2*cwt_2[0] - y_aux_2_q2;
    u_aux_1_d2 = - PLL_dq.V_d; //Delay u_al
    u_aux_1_q2 = - PLL_dq.V_q; //Delay u_be
    y_aux_2_d2 = y_aux_1_d2; //Delay y_aux_1_al
    y_aux_2_q2 = y_aux_1_q2; //Delay y_aux_1_be
    y_aux_1_d2 = y_aux_d2; //Delay y_aux_al
    y_aux_1_q2 = y_aux_q2; //Delay y_aux_be
*/
    //5º 7º
    /*y_aux_d6 = (- PLL_dq.V_d)*50e-6 - u_aux_1_d6*Ts_cwt[1] + y_aux_1_d6*cwt_2[1] - y_aux_2_d6;
    y_aux_q6 = (- PLL_dq.V_q)*50e-6 - u_aux_1_q6*Ts_cwt[1] + y_aux_1_q6*cwt_2[1] - y_aux_2_q6;
    u_aux_1_d6 = - PLL_dq.V_d; //Delay u_al
    u_aux_1_q6 = - PLL_dq.V_q; //Delay u_be
    y_aux_2_d6 = y_aux_1_d6; //Delay y_aux_1_al
    y_aux_2_q6 = y_aux_1_q6; //Delay y_aux_1_be
    y_aux_1_d6 = y_aux_d6; //Delay y_aux_al
    y_aux_1_q6 = y_aux_q6; //Delay y_aux_be*/

	//Compute currents
	i_d_ref=K_v_p*(v_d_ref - PLL_dq.V_d)+ int4 - C*omega*PLL_dq.V_q + PLL_dq.I_d;
	i_q_ref=K_v_p*(v_q_ref - PLL_dq.V_q)+ int5 + C*omega*PLL_dq.V_d + PLL_dq.I_q;

	i_t_d = PLL_dq.I_d - C*omega*PLL_dq.V_q;
	i_t_q = PLL_dq.I_q + C*omega*PLL_dq.V_d;

	// Virtual admittance
	/*v_d_fil=PLL_dq.V_d*0.1+0.9*v_d_ant;
    v_q_fil=PLL_dq.V_q*0.1+0.9*v_q_ant;
    v_d_ant=v_d_fil;
    v_q_ant=v_q_fil;
    i_d_ref = i_d_ref - (PLL_dq.V_d - 0*v_d_fil)*Yd;
    i_q_ref = i_q_ref - (PLL_dq.V_q - 0*v_q_fil)*Yd;*/

	// Compute etas
	s.eta_d = (2.0/ADC_p.V_h)*(-omega*(L)*i_t_q + PLL_dq.V_d + K_c_p*(i_d_ref - i_t_d) + int2);
	s.eta_q = (2.0/ADC_p.V_h)*( omega*(L)*i_t_d + PLL_dq.V_q + K_c_p*(i_q_ref - i_t_q) + int3);

	// Refresh static variables
	if (flag == 1){
		int2 = int2 + K_c_i*(i_d_ref - i_t_d)*50e-6;
		int3 = int3 + K_c_i*(i_q_ref - i_t_q)*50e-6;
		int4 = int4 + K_v_i*(v_d_ref - PLL_dq.V_d)*50e-6;
		int5 = int5 + K_v_i*(v_q_ref - PLL_dq.V_q)*50e-6;
	}

	eta = Park_inverse(PLL_dq, s);
	// Return structure
	return eta;
}

#endif
