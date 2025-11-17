#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"

#pragma CODE_SECTION (CTRL3_comp,"ramfuncs")

struct uvsg CTRL3_comp(double enable_P_ref, double P_pu_ref, double Q_pu_ref, double sync, struct ADC_conv ADC_p, struct PLL_output PLL_Park, double runFSM)
{
	static double omega_o=0, v_d_pu=0, v_q_pu=0, i_d_pu=0, i_q_pu=0, e_q=0, int1=0, int2=0, int3=0, int4=omega_b, i_d_ref_ant=0, i_q_ref_ant=0;
	struct uvsg u;

	if (enable_P_ref < 0.5){
		P_pu_ref=0;
	}
	v_d_pu=PLL_Park.V_d*0.003061862178479;
	v_q_pu=PLL_Park.V_q*0.003061862178479;
	i_d_pu=PLL_Park.I_d*0.02449414855676;
	i_q_pu=PLL_Park.I_q*0.02449414855676;

	if (runFSM>0.5){
		omega_o=1;
	}
	else{
		omega_o=PLL_Park.omega*0.0031830988618379;
	}

	// Power computation

	u.p_s=i_d_pu*v_d_pu+i_q_pu*v_q_pu;
	u.q_s=i_d_pu*v_q_pu-i_q_pu*v_d_pu;

	// Outputs of the active power control

	u.omega=(omega_o+Kp_p*(P_pu_ref-u.p_s)+int1)*omega_b;
	u.theta=int2;
	u.sin=sin(u.theta);
	u.cos=cos(u.theta);

	// Outputs of the reactive power control

	u.DV=Kp_q*(Q_pu_ref-u.q_s)+int3;
	//if (u.DV>0.1){u.DV=0.1;}
	//if (u.DV<-0.1){u.DV=-0.1;}
	e_q=1.0+u.DV;
	u.e_q = -e_q*E_0;
#if CTRL == 15
    // Tensión de referencia
    u.v_d_ref = (     - Rv*i_d_pu + Xv*i_q_pu)*E_0;
    u.v_q_ref = (-e_q + Rv*i_q_pu - Xv*i_d_pu)*E_0;
#elif CTRL == 4

	// Virtual current computation

	u.i_d_ref=-(Xv*e_q+Rv*v_d_pu+Xv*v_q_pu)/(Rv*Rv+Xv*Xv);
	u.i_q_ref=-(Rv*e_q+Rv*v_q_pu-Xv*v_d_pu)/(Rv*Rv+Xv*Xv);

	//u.i_d_ref=u.i_d_ref*0.0075+i_d_ref_ant*0.9925; // 10 ms
	//u.i_q_ref=u.i_q_ref*0.0075+i_q_ref_ant*0.9925;
    u.i_d_ref=u.i_d_ref*0.02+i_d_ref_ant*0.98; // 2.4 ms
    u.i_q_ref=u.i_q_ref*0.02+i_q_ref_ant*0.98;

	i_d_ref_ant=u.i_d_ref;
	i_q_ref_ant=u.i_q_ref;

	u.i_d_ref=u.i_d_ref*40.824799999999939;
	u.i_q_ref=u.i_q_ref*40.824799999999939;
#endif
	/* Update the states
	 * int1 = incremento de omega pu
	 * int2 = theta rads
	 * int3 = incremento de tension pu
	 * int4 = omega filtrada */

	if (runFSM>0.5){
		int1=int1+Ki_p*(P_pu_ref-u.p_s)*Ts;
		//if (u.DV <= 0.1 && u.DV >= -0.1){
			int3=int3+Ki_q*(Q_pu_ref-u.q_s)*Ts;
		/*}

		else{
			int3=0;
		}*/
	}
	else{
		int1=0;
		int3=0;
	}
		if (int2 > 6.283185307179586){
			int2=int2-6.283185307179586;
			}

		int2=int2+u.omega*Ts;


	u.omega_rads=int4+(-int4+u.omega)*Ts;

	return u;

}
