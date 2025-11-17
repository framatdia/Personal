#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"


#pragma CODE_SECTION(PLL_dq,"ramfuncs")
struct PLL_output PLL_dq(struct ADC_conv ADC_p, struct uvsg u, double sync, int startAC)
{
    // Static variables
    static double int0 = 0;

    // Structures
    static struct PLL_output s;


#if (CTRL == 4 || CTRL == 7 || CTRL == 12 || CTRL == 13 || CTRL == 14 || CTRL == 15 || CTRL == 16)
    // Compute variables
    s.alfa_V = 0.666666666667*ADC_p.V_a -0.333333333333*ADC_p.V_b -0.333333333333*ADC_p.V_c;
    s.beta_V = 0.577350269189915*ADC_p.V_b - 0.577350269189915*ADC_p.V_c;

    s.alfa_I = 0.666666666667*ADC_p.I_a -0.333333333333*ADC_p.I_b -0.333333333333*ADC_p.I_c;
    s.beta_I = 0.577350269189915*ADC_p.I_b - 0.577350269189915*ADC_p.I_c;

    s.sin = u.sin;
    s.cos = u.cos;

    s.V_d =  (s.alfa_V*s.cos + s.beta_V*s.sin);
    s.V_q = (-s.alfa_V*s.sin + s.beta_V*s.cos);
    s.I_d =  (s.alfa_I*s.cos + s.beta_I*s.sin);
    s.I_q = (-s.alfa_I*s.sin + s.beta_I*s.cos);

    s.omega = 1.8*s.V_d + int0;

//   Refresh static variables
    if (startAC > 0.5)
    {
        int0=0;
    }
    else{
        int0 = int0 + s.V_d*717.1314741*Ts;
    }
    // Return structure
    return s;


#else
    static double int1 = 0, omega = 0.0, omega_f = 0.0;
    // Compute variables
    s.alfa_V = 0.666666666667*ADC_p.V_a -0.333333333333*(ADC_p.V_b +ADC_p.V_c);
    s.beta_V = 0.577350269189915*(ADC_p.V_b - ADC_p.V_c);

    s.alfa_I = 0.666666666667*ADC_p.I_a -0.333333333333*(ADC_p.I_b +ADC_p.I_c);
    s.beta_I = 0.577350269189915*(ADC_p.I_b - ADC_p.I_c);

    s.sin = sin(int1);
    s.cos = cos(int1);

    s.V_d =  (s.alfa_V*s.cos + s.beta_V*s.sin);
#if (CTRL != 8)
    s.V_q = (-s.alfa_V*s.sin + s.beta_V*s.cos);
    s.I_d =  (s.alfa_I*s.cos + s.beta_I*s.sin);
    s.I_q = (-s.alfa_I*s.sin + s.beta_I*s.cos);
#endif
    s.theta = int1;
#if (CTRL == 10)
    omega = 314.159265;
#else
    omega = 1.8*s.V_d + int0;
#endif
    omega_f=omega*0.01+0.99*omega_f;  // 200Hz LPF
    s.omega = omega_f;



    /*s.sin = sin(int1);
    s.cos = cos(int1);*/

    // Refresh static variables
    int0 = int0 + s.V_d*717.1314741*Ts;
    if (int1 >= 6.283185307179586)
    {
        int1 = int1 - 6.283185307179586;
    }
    int1 = int1 + omega*Ts;

    // Return structure
    return s;
#endif
}


/*#pragma CODE_SECTION (DQF_transform,"ramfuncs")
struct dq_abc PQabc_to_DQabc(struct PLL_output PLL, struct CAN_read CAN)
{
    struct dq_abc Idq_abc = {0,0,0,0,0,0};
    double den = 0;

    den = PLL.V_d*PLL.V_d+PLL.V_q*PLL.V_q;
    i_d_ref=0.66666666666667*((CAN.Pa_ref*PLL.V_d)+(CAN.Qa_ref*PLL.V_q))/(PLL.V_d*PLL.V_d+PLL.V_q*PLL.V_q);
    i_q_ref=0.66666666666667*((P_ref*PLL.V_q)+(Q_ref*PLL.V_d))/(PLL.V_d*PLL.V_d+PLL.V_q*PLL.V_q);

    return Idq_abc;
}*/

/*#pragma CODE_SECTION (DQF_transform,"ramfuncs")
struct signal DQF_transform(struct PLL_output PLL, struct CAN_read CAN, struct dq_abc PQabc_out)
{
    struct dq dqf_b={0,0}, dqf_c={0,0};
    struct signal s = {0, 0, 0, 0, 0, 0, 0, 0};

    //Traslación a dq común (dq_a)
    dqf_b.d =  CAN.idb_ref*c120 + CAN.iqb_ref*s120;
    dqf_b.q = -CAN.idb_ref*s120 + CAN.iqb_ref*c120;

    //Cálculo de abcn
    s.a = CAN.ida_ref*PLL.cos - CAN.iqa_ref*PLL.sin;
    s.b =     dqf_b.d*PLL.cos -     dqf_b.q*PLL.sin;

    if (wires==3){
        s.c = -s.a -s.b;
    }
    else{
        dqf_c.d =  CAN.idc_ref*c120 - CAN.iqc_ref*s120;
        dqf_c.q =  CAN.idc_ref*s120 + CAN.iqc_ref*c120;
        s.c = dqf_c.d*PLL.cos - dqf_c.q*PLL.sin;
        s.n = -s.a -s.b -s.c;
    }

    //Cálculo de alfa-beta
    s.alfa = 0.666666666667*s.a -0.333333333333*(s.b - s.c);
    s.beta = 0.577350269189915*(s.b - s.c);

    return s;
}*/

#pragma CODE_SECTION(Park_inverse,"ramfuncs")
struct duty_cycle Park_inverse(struct PLL_output PLL_dq, struct duty_cycle eta_dq)
{
    // Structures
    struct duty_cycle eta_abc;

#if (CTRL==8)
    // eta computadas en alpha-beta.
        eta_abc.eta_a = eta_dq.eta_alfa;
        eta_abc.eta_b = -0.5*eta_dq.eta_alfa + 0.866025403784439*eta_dq.eta_beta;
        eta_abc.eta_c = eta_abc.eta_b - 1.732050807568878*eta_dq.eta_beta;
        eta_abc.eta_n = eta_dq.eta_n;
#else
        // Compute variables
        eta_abc.eta_d = eta_dq.eta_d;
        eta_abc.eta_q = eta_dq.eta_q;

        eta_abc.eta_alfa = eta_dq.eta_d*PLL_dq.cos - eta_dq.eta_q*PLL_dq.sin;
        eta_abc.eta_beta = eta_dq.eta_d*PLL_dq.sin + eta_dq.eta_q*PLL_dq.cos;

        eta_abc.eta_a = eta_abc.eta_alfa;
        eta_abc.eta_b = -0.5*eta_abc.eta_alfa + 0.866025403784439*eta_abc.eta_beta;
        eta_abc.eta_c = -0.5*eta_abc.eta_alfa - 0.866025403784439*eta_abc.eta_beta;
#endif
    // Saturation
    if (eta_abc.eta_a > 0.99) {eta_abc.eta_a = 0.99;}
    if (eta_abc.eta_a < -0.99) {eta_abc.eta_a = -0.99;}
    if (eta_abc.eta_b > 0.99) {eta_abc.eta_b = 0.99;}
    if (eta_abc.eta_b < -0.99) {eta_abc.eta_b = -0.99;}
    if (eta_abc.eta_c > 0.99) {eta_abc.eta_c = 0.99;}
    if (eta_abc.eta_c < -0.99) {eta_abc.eta_c = -0.99;}

    // Return structure
    return eta_abc;
}






