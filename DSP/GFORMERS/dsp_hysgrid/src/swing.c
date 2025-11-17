#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"

#pragma CODE_SECTION (SWING_comp,"ramfuncs")

struct uvsg SWING(double p_ref, double q_ref, double sync, struct PLL_output Park, double runFSM)
{
    double T = 0.0, omega_ref = 314.1592653589793;

    static double int1 = 314.1592653589793, int2 = 0.0, int3 = 0.0, int4 = 314.1592653589793, i_d_ref_ant=0, i_q_ref_ant=0;
    static struct uvsg u = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    // Potencias instantáneas
    u.p_s = 1.5*(Park.V_d*Park.I_d + Park.V_q*Park.I_q);
    u.q_s = 1.5*(Park.V_q*Park.I_d - Park.V_d*Park.I_q);

    // Sync
    omega_ref=omega_base;

//#if CTRL == 12
    if (runFSM>0.5){
//#else
//        if (sync>0.5){
//#endif
        omega_ref=omega_base;
    }
    else{
        omega_ref=Park.omega;
    }

    // Error en par
    T = (p_ref-u.p_s)*omega_base_inv;
    // Error en potencia reactiva
    u.DV=Kp_q*(q_ref-u.q_s)+int3;

    /* Estados
     * int1 = omega
     * int2 = theta
     * int3 = incremento de tension */

    if (runFSM>0.5){
        // Omega
        int1 = int1 + J_inv*(T + D_p*(omega_ref-int1))*Ts;
        // Reactiva
        //if (u.DV <= 32.52691193458119 && u.DV >= -32.52691193458119){
            int3=int3+Ki_q*(q_ref-u.q_s)*Ts;
        //}

        //else{
        //    int3=0.0;
        //}
    }
    else{
        int1=314.1592653589793;
        int3=0.0;
    }
        if (int2 > 6.283185307179586){
            int2=int2-6.283185307179586;
            }





//#if CTRL == 12
    if (runFSM>0.5){
//#else
//        if (sync>0.5){
//#endif
        u.omega = int1;
    }
    else{
        u.omega = Park.omega;
    }
    u.theta = int2;
    u.sin=sin(u.theta);
    u.cos=cos(u.theta);
    int2=int2+u.omega*Ts;

    // Fuerza electromotriz
    u.e_q = - E_0 - u.DV;

    // Tensión de referencia

#if CTRL == 13
    // Tensión de referencia
    u.v_d_ref = (     - Rv*Park.I_d + Xv*Park.I_q);
    u.v_q_ref = u.e_q + (Rv*Park.I_q - Xv*Park.I_d);
#elif CTRL == 14

    // Virtual current computation

    u.i_d_ref=-(-Xv*u.e_q+Rv*Park.V_d+Xv*Park.V_q)/(Rv*Rv+Xv*Xv);
    u.i_q_ref=-(-Rv*u.e_q+Rv*Park.V_q-Xv*Park.V_d)/(Rv*Rv+Xv*Xv);

    //u.i_d_ref=u.i_d_ref*0.0075+i_d_ref_ant*0.9925; // 10 ms
    //u.i_q_ref=u.i_q_ref*0.0075+i_q_ref_ant*0.9925;
    u.i_d_ref=u.i_d_ref*0.02+i_d_ref_ant*0.98; // 2.4 ms
    u.i_q_ref=u.i_q_ref*0.02+i_q_ref_ant*0.98;

    i_d_ref_ant=u.i_d_ref;
    i_q_ref_ant=u.i_q_ref;

#endif
    u.omega_rads=int4+(-int4+u.omega)*Ts;
    return u;
}
