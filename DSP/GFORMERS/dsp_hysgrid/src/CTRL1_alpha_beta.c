#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"
#include "DSP28x_Project.h"

struct signal power2current(struct ADC_conv ADC, struct CAN_read CAN, unsigned int SCH, struct powers* Pow, struct powers* Pow_f, struct PLL_output PLL_dq);

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
#pragma CODE_SECTION (CTRL1_PQ_comp_albe,"ramfuncs")
struct duty_cycle CTRL1_PQ_comp_albe(struct ADC_conv ADC_p, struct PLL_output PLL_dq, double omega, double p_pu_ref, double q_pu_ref, int flag)
{
	double val_ref=0, vbe_ref=0, i_al_ref=0, i_be_ref=0, P_ref=0, Q_ref=0;
	double vref=0, phref=0;
	double u_al = 0, u_be = 0;
	double Ts = 50e-6;
	double Sb = 20000.0;
	double y_aux_al = 0;
	double y_aux_be = 0;
	double u_aux_1_al = 0;
	double u_aux_1_be = 0;
	double y_aux_1_al = 0;
	double y_aux_1_be = 0;
	double y_aux_2_al = 0;
	double y_aux_2_be = 0;
	double omega_ref = 314.1593;

	struct duty_cycle eta = {0,0,0,0,0,0,0,0,0};
	// ialpbet setpoint computation
	//Power references
    P_ref=p_pu_ref*Sb;
    Q_ref=q_pu_ref*Sb;
	i_al_ref=0.66666666666667*((P_ref*PLL_dq.alfa_V)+(Q_ref*PLL_dq.beta_V))/(PLL_dq.alfa_V*PLL_dq.alfa_V+PLL_dq.V_q*PLL_dq.beta_V);
	i_be_ref=0.66666666666667*((P_ref*PLL_dq.beta_V)+(Q_ref*PLL_dq.alfa_V))/(PLL_dq.alfa_V*PLL_dq.alfa_V+PLL_dq.V_q*PLL_dq.beta_V);



// Resonant controller. Discretization method: Impulse Invariant
	u_al = K_r_i*(i_al_ref - PLL_dq.alfa_I);
	u_be = K_r_i*(i_be_ref - PLL_dq.beta_I);

    if (flag == 0){
        y_aux_al = 0.0;
        y_aux_be = 0.0;
        }
    else{

        y_aux_al = u_al*Ts - u_aux_1_al*Ts*cos(omega_ref*Ts) + 2*y_aux_1_al*cos(omega_ref*Ts) - y_aux_2_al;
        y_aux_be = u_be*Ts - u_aux_1_be*Ts*cos(omega_ref*Ts) + 2*y_aux_1_be*cos(omega_ref*Ts) - y_aux_2_be;
    }
    val_ref =  PLL_dq.alfa_V + K_r_p*(i_al_ref - PLL_dq.alfa_I) + y_aux_al;
    vbe_ref =  PLL_dq.beta_V + K_r_p*(i_be_ref - PLL_dq.beta_I) + y_aux_be;

	vref=sqrt(val_ref*val_ref+vbe_ref*vbe_ref);
	phref=atan(val_ref/vbe_ref);

	if ((val_ref > 0 && vbe_ref < 0) || (vbe_ref < 0 && val_ref < 0)){
	    phref+=M_PI;
	}
	phref+=theta;

    //Delay generation
	u_aux_1_al=u_al; //Delay u_al
	u_aux_1_be=u_be; //Delay u_be

	y_aux_1_al = y_aux_al; //Delay y_aux_al
	y_aux_1_be = y_aux_be; //Delay y_aux_be

	y_aux_2_al = y_aux_1_al; //Delay y_aux_1_al
	y_aux_2_be = y_aux_1_be; //Delay y_aux_1_be


	else{
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

#pragma CODE_SECTION (CTRL1_PQ_comp_albe,"ramfuncs")
struct duty_cycle CTRL1_PQ_comp_albe(struct ADC_conv ADC_p, struct PLL_output PLL_dq, double omega, double p_pu_ref, double q_pu_ref, struct signal it_ref, int flag, struct CAN_read CAN)
{
	//variables
    static double u_al = 0;
    static double u_be = 0;
    static double u_n = 0;
    double val_ref=0;
    double vbe_ref=0;
    static double y_aux_al = 0;
    static double y_aux_be = 0;
    static double y_aux_al3 = 0;
    static double y_aux_be3 = 0;
    static double y_aux_al5 = 0;
    static double y_aux_be5 = 0;
    static double y_aux_al7 = 0;
    static double y_aux_be7 = 0;
    static double u_aux_1_al = 0;
    static double u_aux_1_be = 0;
    static double u_aux_1_n = 0;
    static double u_aux_1_al3 = 0;
    static double u_aux_1_be3 = 0;
    static double u_aux_1_n3 = 0;
    static double y_aux_1_al = 0;
    static double y_aux_1_be = 0;
    static double y_aux_2_al = 0;
    static double y_aux_2_be = 0;
    static double y_aux_1_al3 = 0;
    static double y_aux_1_be3 = 0;
    static double y_aux_2_al3 = 0;
    static double y_aux_2_be3 = 0;
    static double y_aux_1_al5 = 0;
    static double y_aux_1_be5 = 0;
    static double y_aux_2_al5 = 0;
    static double y_aux_2_be5 = 0;
    static double y_aux_1_al7 = 0;
    static double y_aux_1_be7 = 0;
    static double y_aux_2_al7 = 0;
    static double y_aux_2_be7 = 0;
    static double y_aux_n = 0;
    static double y_aux_n3 = 0;
    static double y_aux_n5 = 0;
    static double y_aux_n7 = 0;
    static double y_aux_1_n = 0;
    static double y_aux_1_n3 = 0;
    static double y_aux_1_n5 = 0;
    static double y_aux_1_n7 = 0;
    static double y_aux_2_n = 0;
    static double y_aux_2_n3 = 0;
    static double y_aux_2_n5 = 0;
    static double y_aux_2_n7 = 0;
    double i_al_ref=0;
    double i_be_ref=0;
    double  P_ref=0;
    double Q_ref=0;
    double Sb = 20000.0;
    double omega_ref = 314.1593;
    double cwt_2[4] = {1.999753264963321, 1.997779749923940, 1.993834667466256, 1.987921910910359};
    double Ts_cwt[4] = {0.0000499938316240830, 0.00004994449374809851, 0.0000498458666866564, 0.00004969804777275899};
    //double cwt_2 = 1.999753215609926, c3wt_2 = 1.997779305889514, Ts_cwt = 0.00004999883027327548, Ts_c3wt = 0.00004994947759499735;
    double den_afbt = 0;
    double mVh = 0;
    //struct signal i_powers={0,0,0,0,0,0,0,0};
    //double D_res = 2.49984579694325e-05, AB_res = -1.99975327510920;


	// Structures
	struct duty_cycle s, eta;

	mVh = 2.0/ADC_p.V_h;
    //Currents
    i_al_ref = it_ref.alfa;
    i_be_ref = it_ref.beta;
    // Resonant controller
	u_al = (i_al_ref - PLL_dq.alfa_I);
    u_be = (i_be_ref - PLL_dq.beta_I);
    if (flag == 0){
          y_aux_al = 0.0;
          y_aux_be = 0.0;
          y_aux_n = 0.0;
          y_aux_n3 = 0.0;
          y_aux_n5 = 0.0;
          y_aux_n7 = 0.0;
          y_aux_al3 = 0.0;
          y_aux_be3 = 0.0;
          y_aux_al5 = 0.0;
          y_aux_be5 = 0.0;
          y_aux_al7 = 0.0;
          y_aux_be7 = 0.0;
          }
      else{
          // Tustin
          //y_aux_al=D_res*(u_al - u_aux_2_al) - AB_res*y_aux_1_al - y_aux_2_al;
          //y_aux_be=D_res*(u_be - u_aux_2_be) - AB_res*y_aux_1_be - y_aux_2_be;
          // Impulse invariant
          //y_aux_al = u_al*Ts - u_aux_1_al*Ts*cos(omega_ref*Ts) + 2*y_aux_1_al*cos(omega_ref*Ts) - y_aux_2_al;
          //y_aux_be = u_be*Ts - u_aux_1_be*Ts*cos(omega_ref*Ts) + 2*y_aux_1_be*cos(omega_ref*Ts) - y_aux_2_be;
          y_aux_al = u_al*Ts - u_aux_1_al*Ts_cwt[0] + y_aux_1_al*cwt_2[0] - y_aux_2_al;
          y_aux_be = u_be*Ts - u_aux_1_be*Ts_cwt[0] + y_aux_1_be*cwt_2[0] - y_aux_2_be;
#if CTRL_H == 1
          y_aux_al3 = (- PLL_dq.alfa_I)*Ts - u_aux_1_al3*Ts_cwt[1] + y_aux_1_al3*cwt_2[1] - y_aux_2_al3;
          y_aux_be3 = (- PLL_dq.beta_I)*Ts - u_aux_1_be3*Ts_cwt[1] + y_aux_1_be3*cwt_2[1] - y_aux_2_be3;
          //y_aux_al5 = (- PLL_dq.alfa_I)*Ts - u_aux_1_al3*Ts_cwt[2] + y_aux_1_al5*cwt_2[2] - y_aux_2_al5;
          //y_aux_be5 = (- PLL_dq.beta_I)*Ts - u_aux_1_be3*Ts_cwt[2] + y_aux_1_be5*cwt_2[2] - y_aux_2_be5;
          //y_aux_al7 = (- PLL_dq.alfa_I)*Ts - u_aux_1_al3*Ts_cwt[3] + y_aux_1_al7*cwt_2[3] - y_aux_2_al7;
          //y_aux_be7 = (- PLL_dq.beta_I)*Ts - u_aux_1_be3*Ts_cwt[3] + y_aux_1_be7*cwt_2[3] - y_aux_2_be7;
#endif
          if (wires == 4)
          {
              u_n = it_ref.n - ADC_p.I_n;
              y_aux_n  = u_n*Ts - u_aux_1_n*Ts_cwt[0] + y_aux_1_n*cwt_2[0] - y_aux_2_n;
#if CTRL_H == 1
              y_aux_n3 = (- ADC_p.I_n)*Ts - u_aux_1_n3*Ts_cwt[1] + y_aux_1_n3*cwt_2[1] - y_aux_2_n3;
              //y_aux_n5 = (- ADC_p.I_n)*Ts - u_aux_1_n3*Ts_cwt[2] + y_aux_1_n5*cwt_2[2] - y_aux_2_n5;
              //y_aux_n7 = (- ADC_p.I_n)*Ts - u_aux_1_n3*Ts_cwt[3] + y_aux_1_n7*cwt_2[3] - y_aux_2_n7;
#endif
              //s.eta_n = (K_r_i*y_aux_n + K_r3_i*(y_aux_n3 + y_aux_n5 + y_aux_n7) + K_r_p*u_n)*mVh;
              s.eta_n = (K_r_i*y_aux_n + K_r3_i*(y_aux_n3 + 0.0*y_aux_n5)+ K_r_p*u_n)*mVh;
              //s.eta_n = 0;
              u_aux_1_n = u_n;
              y_aux_2_n = y_aux_1_n;
              y_aux_1_n = y_aux_n;
#if CTRL_H == 1
              u_aux_1_n3 = - ADC_p.I_n;
              y_aux_2_n3 = y_aux_1_n3;
              //y_aux_2_n5 = y_aux_1_n5;
              //y_aux_2_n7 = y_aux_1_n7;
              y_aux_1_n3 = y_aux_n3;
              //y_aux_1_n5 = y_aux_n5;
              //y_aux_1_n7 = y_aux_n7;
#endif
          }
      }

#if CTRL_H == 1
    val_ref =  PLL_dq.alfa_V + K_r_p*u_al + K_r_i*y_aux_al + K_r3_i*(y_aux_al3);// + y_aux_al5);// + y_aux_al7);// + K_r3_i/10.0*y_aux_al5+y_aux_al7);
    vbe_ref =  PLL_dq.beta_V + K_r_p*u_be + K_r_i*y_aux_be + K_r3_i*(y_aux_be3);// + y_aux_be5);// + y_aux_be7);// + K_r3_i/10.0*y_aux_be5+y_aux_be7);
#else
    val_ref =  PLL_dq.alfa_V + K_r_p*u_al + K_r_i*y_aux_al;
    vbe_ref =  PLL_dq.beta_V + K_r_p*u_be + K_r_i*y_aux_be;
#endif
	//Delay generation
    //u_aux_2_al=u_aux_1_al; //Delay u_al
    //u_aux_2_be=u_aux_1_be; //Delay u_be
    u_aux_1_al = u_al; //Delay u_al
    u_aux_1_be = u_be; //Delay u_be
    y_aux_2_al = y_aux_1_al; //Delay y_aux_1_al
    y_aux_2_be = y_aux_1_be; //Delay y_aux_1_be
    y_aux_1_al = y_aux_al; //Delay y_aux_al
    y_aux_1_be = y_aux_be; //Delay y_aux_be
#if CTRL_H == 1
    u_aux_1_al3 = - PLL_dq.alfa_I; //Delay u_al
    u_aux_1_be3 = - PLL_dq.beta_I; //Delay u_be
    y_aux_2_al3 = y_aux_1_al3; //Delay y_aux_1_al
    y_aux_2_be3 = y_aux_1_be3; //Delay y_aux_1_be
    y_aux_1_al3 = y_aux_al3; //Delay y_aux_al
    y_aux_1_be3 = y_aux_be3; //Delay y_aux_be
    //y_aux_2_al5 = y_aux_1_al5; //Delay y_aux_1_al
    //y_aux_2_be5 = y_aux_1_be5; //Delay y_aux_1_be
    //y_aux_1_al5 = y_aux_al5; //Delay y_aux_al
    //y_aux_1_be5 = y_aux_be5; //Delay y_aux_be
    //y_aux_2_al7 = y_aux_1_al7; //Delay y_aux_1_al
    //y_aux_2_be7 = y_aux_1_be7; //Delay y_aux_1_be
    //y_aux_1_al7 = y_aux_al7; //Delay y_aux_al
    //y_aux_1_be7 = y_aux_be7; //Delay y_aux_be
#endif

    // Compute variables
    s.eta_alfa = mVh*(val_ref);
    s.eta_beta = mVh*(vbe_ref);

	eta = Park_inverse(PLL_dq, s);
	// Return structure
	return eta;
}

#endif

struct signal power2current(struct ADC_conv ADC, struct CAN_read CAN, unsigned int SCH, struct powers* Pow, struct powers* Pow_f, struct PLL_output PLL_dq){
    struct signal s = {0,0,0,0,0,0,0,0};
    struct afbt va={0,0},vb={0,0},vc={0,0}, ia={0,0},ib={0,0},ic={0,0};
    static struct abc u1_v={0,0,0};
    static struct abc y0_v={0,0,0};
    static struct abc y1_v={0,0,0};
    static struct abc y2_v={0,0,0};
    static struct abc u1_i={0,0,0};
    static struct abc y0_i={0,0,0};
    static struct abc y1_i={0,0,0};
    static struct abc y2_i={0,0,0};
    //struct powers pnf = {0,0,0,0,0,0,0,0,0,0,0,0,0};
    static struct powers pnf0 = {0,0,0,0,0,0,0,0,0,0,0,0,0};
    //static struct abc P = {0,0,0}, Q = {0,0,0};

    double wts = 0.015707963267949, wts2_n = -1.984292036732051, wts2_di = 0.496103611347925;
    //double wts = 0.015709534221371, wts2_n = -1.984290465778629, wts2_di = 0.496103224707066;

    /* Alfa-beta per phase */
        // Alfa component
        va.af = ADC.V_a;
        vb.af = ADC.V_b;
        vc.af = ADC.V_c;
        ia.af = ADC.I_a;
        ib.af = ADC.I_b;
        ic.af = ADC.I_c;

        // 1st filter
        y0_v.a = y1_v.a;
        y0_v.b = y1_v.b;
        y0_v.c = y1_v.c;
        y1_v.a = ((ADC.V_a + u1_v.a)*wts - wts2_n*y1_v.a)*wts2_di;
        y1_v.b = ((ADC.V_b + u1_v.b)*wts - wts2_n*y1_v.b)*wts2_di;
        y1_v.c = ((ADC.V_c + u1_v.c)*wts - wts2_n*y1_v.c)*wts2_di;
        y0_i.a = y1_i.a;
        y0_i.b = y1_i.b;
        y0_i.c = y1_i.c;
        y1_i.a = ((ADC.I_a + u1_i.a)*wts - wts2_n*y1_i.a)*wts2_di;
        y1_i.b = ((ADC.I_b + u1_i.b)*wts - wts2_n*y1_i.b)*wts2_di;
        y1_i.c = ((ADC.I_c + u1_i.c)*wts - wts2_n*y1_i.c)*wts2_di;

        // 2nd filter
        y2_v.a = ((y1_v.a + y0_v.a)*wts - wts2_n*y2_v.a)*wts2_di;
        y2_v.b = ((y1_v.b + y0_v.b)*wts - wts2_n*y2_v.b)*wts2_di;
        y2_v.c = ((y1_v.c + y0_v.c)*wts - wts2_n*y2_v.c)*wts2_di;
        y2_i.a = ((y1_i.a + y0_i.a)*wts - wts2_n*y2_i.a)*wts2_di;
        y2_i.b = ((y1_i.b + y0_i.b)*wts - wts2_n*y2_i.b)*wts2_di;
        y2_i.c = ((y1_i.c + y0_i.c)*wts - wts2_n*y2_i.c)*wts2_di;

        // Delayed states
        u1_v.a = ADC.V_a;
        u1_v.b = ADC.V_b;
        u1_v.c = ADC.V_c;
        u1_i.a = ADC.I_a;
        u1_i.b = ADC.I_b;
        u1_i.c = ADC.I_c;

        // Beta component
        va.bt = 2.0*y2_v.a;
        vb.bt = 2.0*y2_v.b;
        vc.bt = 2.0*y2_v.c;
        ia.bt = 2.0*y2_i.a;
        ib.bt = 2.0*y2_i.b;
        ic.bt = 2.0*y2_i.c;

        /* Powers computation */

#if SCHEDULER_ON == 1
        if (SCH==4){
            Pow->Pa = 0.5*(va.af*ia.af + va.bt*ia.bt);
        }
        if (SCH==5){
            Pow->Qa = -0.5*(va.af*ia.bt - va.bt*ia.af);
        }
        if (SCH==6){
            Pow->Pb = 0.5*(vb.af*ib.af + vb.bt*ib.bt);
        }
        if (SCH==7){
            Pow->Qb = -0.5*(vb.af*ib.bt - vb.bt*ib.af);
        }
        if (SCH==8){
            Pow->Pc = 0.5*(vc.af*ic.af + vc.bt*ic.bt);
        }
        if (SCH==9){
            Pow->Qc = -0.5*(vc.af*ic.bt - vc.bt*ic.af);
        }
#else

        pnf0.Pa= ADC.V_a*ADC.I_a*0.00001+0.99999*pnf0.Pa;
        pnf0.Pb= ADC.V_b*ADC.I_b*0.00001+0.99999*pnf0.Pb;
        pnf0.Pc= ADC.V_c*ADC.I_c*0.00001+0.99999*pnf0.Pc;
        pnf0.Qa= (ADC.V_b-ADC.V_c)*ADC.I_a*0.00001+0.99999*pnf0.Qa;
        pnf0.Qb= (ADC.V_c-ADC.V_a)*ADC.I_b*0.00001+0.99999*pnf0.Qb;
        pnf0.Qc= (ADC.V_a-ADC.V_b)*ADC.I_c*0.00001+0.99999*pnf0.Qc;

        Pow_f->Pa  = pnf0.Pa;
        Pow_f->Pb  = pnf0.Pb;
        Pow_f->Pc  = pnf0.Pc;
        Pow_f->Qa  = pnf0.Qa*0.577350269189626;
        Pow_f->Qb  = pnf0.Qb*0.577350269189626;
        Pow_f->Qc  = pnf0.Qc*0.577350269189626;

            Pow->Pa = 0.5*(va.af*ia.af + va.bt*ia.bt);
            Pow->Qa = -0.5*(va.af*ia.bt - va.bt*ia.af);
            Pow->Pb = 0.5*(vb.af*ib.af + vb.bt*ib.bt);
            Pow->Qb = -0.5*(vb.af*ib.bt - vb.bt*ib.af);
            Pow->Pc = 0.5*(vc.af*ic.af + vc.bt*ic.bt);
            Pow->Qc = -0.5*(vc.af*ic.bt - vc.bt*ic.af);
#endif

#if (REF_TYPE == 0)
    /* Raw current references computation */
        // Unbalanced references
        //s.a = CAN.M_a*(PLL_dq.sin*CAN.cos_a + PLL_dq.cos*CAN.sin_a);
        //s.b = CAN.M_b*(PLL_dq.sin*CAN.cos_b + PLL_dq.cos*CAN.sin_b);
        //s.c = CAN.M_c*(PLL_dq.sin*CAN.cos_c + PLL_dq.cos*CAN.sin_c);
        //Balanced current references. Only active power
        s.a = CAN.iqa_ref*(PLL_dq.sin*1.0 + PLL_dq.cos*0.0);
        s.b = CAN.iqa_ref*5.0/10.0*(PLL_dq.sin*(-0.5) + PLL_dq.cos*(-0.866025403784439));
        s.c = CAN.iqa_ref*7.0/10.0*(PLL_dq.sin*(-0.5) + PLL_dq.cos*0.866025403784439);
        if (wires == 3){
            s.c = -s.a -s.b;}
        else{
            s.n = -s.a -s.b -s.c;
        }
#else
    /* Current references computation */
        if(DEVICE ==  1 || DEVICE == 2 || DEVICE == 3 || DEVICE == 4){    //For the current EASYRES prototype setup
        s.a = 2.0*(CAN.P_pu_ref*20000.0*va.af + CAN.Q_pu_ref*20000.0*va.bt)/(va.af*va.af + va.bt*va.bt);
        s.b = 2.0*(CAN.P_pu_ref*20000.0*vb.af + CAN.Q_pu_ref*20000.0*vb.bt)/(vb.af*vb.af + vb.bt*vb.bt);
        }
        else{
        //s.a = 2.0*(CAN.Pa_ref*va.af + CAN.Qa_ref*va.bt)/(va.af*va.af + va.bt*va.bt);
        //s.b = 2.0*(CAN.Pb_ref*vb.af + CAN.Qb_ref*vb.bt)/(vb.af*vb.af + vb.bt*vb.bt);
        s.a = 2.0*(CAN.Pa_ref*va.af + CAN.Qa_ref*va.bt)/(va.af*va.af + va.bt*va.bt);
        s.b = 2.0*(CAN.Pb_ref*vb.af + CAN.Qb_ref*vb.bt)/(vb.af*vb.af + vb.bt*vb.bt);
        }
        if (wires == 3){
            s.c = -s.a -s.b;}
        else{
            //s.c = 2.0*(CAN.Pc_ref*vc.af + CAN.Qc_ref*vc.bt)/(vc.af*vc.af + vc.bt*vc.bt);
            s.c = 2.0*(CAN.Pc_ref*vc.af + CAN.Qc_ref*vc.bt)/(vc.af*vc.af + vc.bt*vc.bt);
            s.n = -s.a -s.b -s.c;
        }
#endif
        s.alfa = 0.666666666667*s.a -0.333333333333*(s.b + s.c);
        s.beta = 0.577350269189915*(s.b - s.c);
    return s;
}



struct duty_cycle ctrl_z3(struct ADC_conv ADC_p){
    struct duty_cycle s={0,0,0,0,0,0,0,0,0,0};
    double u_iz=0;
    double c3wt_2 = 1.997779749923940, Ts_c3wt = 0.00004994449374809851;
    static double u_aux_1_iz = 0;
    static double y_aux_iz = 0;
    static double y_aux_1_iz = 0;
    static double y_aux_2_iz = 0;

    u_iz = -(ADC_p.I_a + ADC_p.I_b + ADC_p.I_c)*0.333333333333; // Z component computation

    y_aux_iz = u_iz*Ts - u_aux_1_iz*Ts_c3wt + y_aux_1_iz*c3wt_2 - y_aux_2_iz;
    s.eta_a = 2.0*(K_r_i*(y_aux_iz + y_aux_iz) + 0.0*K_r_p*u_iz)*0.002739726027397;
    s.eta_b = s.eta_a;
    s.eta_c = s.eta_a;

    u_aux_1_iz = u_iz;
    y_aux_2_iz = y_aux_1_iz;
    y_aux_1_iz = y_aux_iz;

    return s;
}











