#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"
#include <math.h>

//#pragma CODE_SECTION (CTRL1__PQ_comp,"ramfuncs")



#pragma CODE_SECTION(rms_calculation,"ramfuncs")
struct rms rms_calculation(struct ADC_conv ADC, unsigned int SCH)
{
    static struct rms rms_out;     // RMS output struct

    #if (wires == 3)
        double Vi[6]={0,0,0,0,0,0};            // ADC measurements
        double Vi2[6]={0,0,0,0,0,0};
        static double rms2[6]={0,0,0,0,0,0};           // RMS vector
        static double rms0[7]={0,0,0,0,0,0,0};         // Filtered RMS vector
        static double Sum[6]={0,0,0,0,0,0};    // Summatory of squares
        unsigned int n_meas = 6;            // Length of ADC measurements
        Vi[0]=ADC.V_a;
        Vi[1]=ADC.V_b;
        Vi[2]=ADC.V_c;
        Vi[3]=ADC.I_a;
        Vi[4]=ADC.I_b;
        Vi[5]=ADC.I_c;
    #elif (wires == 4)
        double Vi[7]={0,0,0,0,0,0,0};
        double Vi2[7]={0,0,0,0,0,0,0};
        static double rms2[7]={0,0,0,0,0,0,0};
        #if SCHEDULER_ON == 1
        static double rms0[7]={0,0,0,0,0,0,0};
        #endif
        static double Sum[7]={0,0,0,0,0,0,0};
        unsigned int n_meas = 7;
        Vi[0]=ADC.V_a;
        Vi[1]=ADC.V_b;
        Vi[2]=ADC.V_c;
        Vi[3]=ADC.I_a;
        Vi[4]=ADC.I_b;
        Vi[5]=ADC.I_c;
        Vi[6]=ADC.I_n;
    #endif

  /*unsigned int j=0;
    static unsigned int i=0;
    if (i>=400){    // 400 -> Sample time 50e-6, f=50Hz
        for (j=0;j<n_meas;j++)
        {
                rms2[j] = Sum[j]*0.0025;    // Root mean
                Sum[j] = 0.0;
        }
        i=0;
    }
    i++;
    for (j=0;j<n_meas;j++)
    {
        Vi2[j] = Vi[j]*Vi[j];               // Square of the measurement
        Sum[j] = Vi2[j] + Sum[j];    // Summatory of squares
    }*/
    static unsigned int i=0;

    // RMS output struct assignment
#if SCHEDULER_ON == 1
    if (SCH==0){
        if (i>=40){     // 40 -> Sample time 50e-6, f=50Hz, SCHEDULER=10
            rms2[0] = Sum[0]*0.025;    // Root mean
            Sum[0] = 0.0;
            rms2[3] = Sum[3]*0.025;    // Root mean
            Sum[3] = 0.0;
            rms0[0] = rms2[0]*0.1+rms0[0]*0.9;     //LPF RMS (0.5 = 40ms)
            rms0[3] = rms2[3]*0.1+rms0[3]*0.9;     //LPF RMS (0.5 = 40ms)
        }
        Vi2[0] = Vi[0]*Vi[0];        // Square of the measurement
        Sum[0] = Vi2[0] + Sum[0];    // Summatory of squares
        Vi2[3] = Vi[3]*Vi[3];        // Square of the measurement
        Sum[3] = Vi2[3] + Sum[3];    // Summatory of squares
        rms_out.va_rms = rms0[0];
        rms_out.ia_rms = rms0[3];}
    if (SCH==1){
        if (i>=40){     // 40 -> Sample time 50e-6, f=50Hz, SCHEDULER=10
            rms2[1] = Sum[1]*0.025;    // Root mean
            Sum[1] = 0.0;
            rms2[4] = Sum[4]*0.025;    // Root mean
            Sum[4] = 0.0;
            rms0[1] = rms2[1]*0.1+rms0[1]*0.9;     //LPF RMS (0.5 = 40ms)
            rms0[4] = rms2[4]*0.1+rms0[4]*0.9;     //LPF RMS (0.5 = 40ms)
        }
        Vi2[1] = Vi[1]*Vi[1];        // Square of the measurement
        Sum[1] = Vi2[1] + Sum[1];    // Summatory of squares
        Vi2[4] = Vi[4]*Vi[4];        // Square of the measurement
        Sum[4] = Vi2[4] + Sum[4];    // Summatory of squares
        rms_out.vb_rms = rms0[1];
        rms_out.ib_rms = rms0[4];}
    if (SCH==2){
        if (i>=40){     // 40 -> Sample time 50e-6, f=50Hz, SCHEDULER=10
            rms2[2] = Sum[2]*0.025;    // Root mean
            Sum[2] = 0.0;
            rms2[5] = Sum[5]*0.025;    // Root mean
            Sum[5] = 0.0;
            rms0[2] = rms2[2]*0.1+rms0[2]*0.9;     //LPF RMS (0.5 = 40ms)
            rms0[5] = rms2[5]*0.1+rms0[5]*0.9;     //LPF RMS (0.5 = 40ms)
        }
        Vi2[2] = Vi[2]*Vi[2];        // Square of the measurement
        Sum[2] = Vi2[2] + Sum[2];    // Summatory of squares
        Vi2[5] = Vi[5]*Vi[5];        // Square of the measurement
        Sum[5] = Vi2[5] + Sum[5];    // Summatory of squares
        rms_out.vc_rms = rms0[2];
        rms_out.ic_rms = rms0[5];}
    #if (wires == 3)
        if (i>=40){i=0;}     // 40 -> Sample time 50e-6, f=50Hz, SCHEDULER=10
        if (SCH==3){
        rms_out.in_rms = 0;
        i++;}
    #elif (wires == 4)
        if (SCH==3){
            if (i>=40){     // 40 -> Sample time 50e-6, f=50Hz, SCHEDULER=10
                rms2[6] = Sum[6]*0.025;    // Root mean
                Sum[6] = 0.0;
                rms0[6] = rms2[6]*0.1+rms0[6]*0.9; //LPF RMS (0.5 = 40ms)
                i=0;
            }
            Vi2[6] = Vi[6]*Vi[6];        // Square of the measurement
            Sum[6] = Vi2[6] + Sum[6];    // Summatory of squares
            rms_out.in_rms = rms0[6];
            i++;}
    #endif
#else
        unsigned int j=0;
        for(j=0;j<6;j++){
            if (i>=400){     // 400 -> Sample time 50e-6, f=50Hz, SCHEDULER_OFF
                rms2[j] = Sum[j]*0.0025;    // Root mean
                Sum[j] = 0.0;
            }
            Vi2[j] = Vi[j]*Vi[j];        // Square of the measurement
            Sum[j] = Vi2[j] + Sum[j];}   // Summatory of squares
            rms_out.va_rms = rms2[0];
            rms_out.vb_rms = rms2[1];
            rms_out.vc_rms = rms2[2];
            rms_out.ia_rms = rms2[3];
            rms_out.ib_rms = rms2[4];
            rms_out.ic_rms = rms2[5];

        #if (wires == 3)
            if (i>=400){i=0;}     // 40 -> Sample time 50e-6, f=50Hz, SCHEDULER=10
            //if (SCH==3){
            rms_out.in_rms = 0;
            i++;//}
        #elif (wires == 4)

                if (i>=400){     // 400 -> Sample time 50e-6, f=50Hz, SCHEDULER_OFF
                    rms2[6] = Sum[6]*0.0025;    // Root mean
                    Sum[6] = 0.0;
                    i=0;
                }
                Vi2[6] = Vi[6]*Vi[6];        // Square of the measurement
                Sum[6] = Vi2[6] + Sum[6];    // Summatory of squares
                rms_out.in_rms = rms2[6];
                i++;
        #endif
#endif
	return rms_out;
}


#pragma CODE_SECTION(ramp_rate_limit,"ramfuncs")
double ramp_rate_limit(double in, double ramped_in, double ramp_rate)
{
	double u_sat, y_sat;
	u_sat=(in-ramped_in)*20; // La constante que multiplica es 1/Ts

	if (u_sat < -ramp_rate)
	{
		y_sat = -ramp_rate;

	}
	else if (u_sat > ramp_rate)
	{
		y_sat = ramp_rate;
	}
	else
	{
		y_sat=u_sat;
	}
	ramped_in+=y_sat*Ts;
	return ramped_in;
}

#pragma CODE_SECTION(rrl_boundary_comp,"ramfuncs")
double rrl_boundary_comp(double v_l, double v_uc_ref)
{
	static double u, u_w, u_a, u_qa;
	double r_l;
	u_w=fabs(v_w-v_uc_ref);
	u_a=fabs(v_a-v_uc_ref);
	u=fabs(v_l-v_uc_ref);

	if (b_approach){				// Asymptotic approach
		u_qa=u_a-(u_aux)*(r_sm);

		if (u<=u_w){ 					// Full service
			r_l=r_n;
		}
		else if (u>u_w && u<u_qa){ 		// Partial service
			r_l=(u_aux)/(u_a-u)+r_n-1;
		}
		else{ 							// Service disabled
			r_l=r_a;
		}

	}
	else{							// Linear piecewise approach
		if (u<=u_w){
			r_l=r_n;
		}
		else if(u>u_w && u<u_qa){
			r_l=r_n*k/(u_aux)*u+r_n*(1-u_w*k/(u_aux));
		}
		else{
			r_l=r_a;
		}

	}

	return r_l;
}

#pragma CODE_SECTION(power_calc,"ramfuncs")
#if (CTRL == 7)
struct powers power_calc_ctrl3(struct ADC_conv ADC_p, struct powers p_calc, double p_pu_ref, int enable_P_ref, int enable_HFPS, double v_uc_ref)
{
	static double p_pri_fil_ant=0, p_losses_ant=0, rrl_HFPS=r_n;

	p_calc.p_pri_fil=(ADC_p.V_h*ADC_p.I_h)*5e-4+0.9995*p_pri_fil_ant; // LPF 0.1 s
	p_pri_fil_ant=p_calc.p_pri_fil;

	p_calc.p_losses=-(ADC_p.V_l*(-ADC_p.I_l)+p_calc.p_pri_fil-p_calc.P3f)*1.7e-6+0.9999983*p_losses_ant; // LPF 30 s
	p_losses_ant=p_calc.p_losses;

	if (enable_P_ref){
		if(enable_HFPS==0){
			p_calc.p_HFPS=p_calc.p_pri_fil;
			p_calc.p_ref=(p_calc.p_losses+p_calc.p_uc_ref+p_calc.p_pri_fil)*0.00005; // in p.u.
		}
		else{
			rrl_HFPS=rrl_boundary_comp(ADC_p.V_l, v_uc_ref);
			p_calc.p_HFPS=ramp_rate_limit(p_calc.p_pri_fil,p_calc.p_HFPS,rrl_HFPS);
			p_calc.p_ref=(p_calc.p_losses+p_calc.p_uc_ref+p_calc.p_HFPS)*0.00005; // in p.u.
		}
	}
	else{
		p_calc.p_ref=p_pu_ref;
	}

	return p_calc;
}
#else
struct powers power_computation (struct ADC_conv ADC, unsigned int SCH){
    struct powers p = {0,0,0,0,0,0,0,0,0,0,0,0,0};
    static double Pa_ant = 0, Pb_ant = 0, Pc_ant = 0, Qa_ant = 0, Qb_ant = 0, Qc_ant = 0;
#if (CTRL == 2 || CTRL == 3 || CTRL == 5 || CTRL == 6)
    p.P3f = (ADC.V_a*ADC.I_a + ADC.V_b*ADC.I_b + ADC.V_c*ADC.I_c);
    p.Q3f = ((ADC.V_a-ADC.V_b)*ADC.I_c + (ADC.V_b-ADC.V_c)*ADC.I_a + (ADC.V_c-ADC.V_a)*ADC.I_b);
#else
    p.Pa = ADC.V_a*ADC.I_a;     p.Qa = 0.577350269189626*(ADC.V_b-ADC.V_c)*ADC.I_a;
    p.Pb = ADC.V_b*ADC.I_b;     p.Qb = 0.577350269189626*(ADC.V_c-ADC.V_a)*ADC.I_b;
    p.Pc = ADC.V_c*ADC.I_c;     p.Qc = 0.577350269189626*(ADC.V_a-ADC.V_b)*ADC.I_c;

    p.Pa = p.Pa*0.0005+0.9995*Pa_ant; p.Qa = p.Qa*0.0005+0.9995*Qa_ant;
    p.Pb = p.Pb*0.0005+0.9995*Pb_ant; p.Qb = p.Qb*0.0005+0.9995*Qb_ant;
    p.Pc = p.Pc*0.0005+0.9995*Pc_ant; p.Qc = p.Qc*0.0005+0.9995*Qc_ant;

    Pa_ant = p.Pa; Qa_ant = p.Qa;
    Pb_ant = p.Pb; Qb_ant = p.Qb;
    Pc_ant = p.Pc; Qc_ant = p.Qc;
#endif
    return p;
}
#endif
