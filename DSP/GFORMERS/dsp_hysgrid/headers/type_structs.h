#define PWM_TIMER_TBPRD 		3750 	// 20 kHz -> 50 us
#define EPWM_MIN_DB             100  // Dead-band of 1us for ePWM (Table 3.15)
#define EPWM_MIN_DB  			25 	// Dead-band of 1us for ePWM (Table 3.15)
#define Ts						50e-6
#define DEVICE          4	// Device number for ADC calibration parameters
    // DEVICE   0           BESS
    // DEVICE   1           EASY-RES PROTOTYPE 1
    // DEVICE   2           EASY-RES PROTOTYPE 2
    // DEVICE   3           EASY-RES PROTOTYPE 3
    // DEVICE   4           TYPHOON Slot 1, CAN DRES 1
    // DEVICE   5           ALLT 1
    // DEVICE   6           ALLT 2
    // DEVICE   7           ALLT 3
    // DEVICE   8           ALLT 4
    // DEVICE   9           ALLT 5
    // DEVICE   10          ALLT 6
    // DEVICE   11          TYPHOON Slot 3, CAN ALLT 5
    // DEVICE   12          BALANCE ALLT
#define wires           3
#define CTRL            16
        /*CTRL 8*/
        #define REF_TYPE        1 // Powers: 1, Currents: 0
#define CTRL_Z          0
#define CTRL_H          0
        /*CTRL 11*/
#define CTRLVdc_2       0       // Square voltage control
/*  1 -> OPEN LOOP
    2 -> CTRL1 (DQ CURRENT REFERENCE)
    3 -> CTRL1 (PQ in dq CURRENT REFERENCE)
    4 -> PI-CC: CTRL3
    5 -> CTRL1 - DC CTRL1
    6 -> CTRL1 (PQ CURRENT REFERENCE) - DC CTRL3
    7 -> CTRL3 - DC CTRL3
    8 -> CTRL1 (alpha-beta current controller bac3ph3wgfolalbe)eve
    9 -> CTRL1 (alpha-beta current controller PQ references bac3ph3wgfolalbe)
    10-> CTRL2 (DQ VOLTAGE controller and references)
    11-> STATCOM (DC-Bus Controller)
    12-> S-OL: Swing equation, Open-loop
    13-> S-VC: Swing equation, CTRL2-CTRL1
    14-> S-CC: Swing equation, CTRL1
    15-> PI-VC: PI-VSG, CTRL2-CTRL1
    16-> PI-OL: PI-VSG, Open-loop
    */


#define     EXT_SYNC            0       // EXT_SYNC = 0 -> EXTERNAL SYNC OFF (MASTER),      EXT_SYNC = 1 -> EXTERNAL SYNC ON (SLAVE)
#define     MODULATION          0       // MODULATION = 0 -> SPWM,      MODULATION = 1 -> SVPWM
#define     SCHEDULER_ON        0       // Activate scheduler (1) / deactivate scheduler (0)
#define     FSM                 0       // Enable FSM


#if DEVICE==0 // BESS
// I_s
#define     GAIN_IH         1
#define     OFF_IH          0
#define     GAIN_IL         1
#define     OFF_IL          0
#define     GAIN_VL         1
#define     OFF_VL          0
#define     GAIN_VH         0.9091
#define     OFF_VH          0
#define     GAIN_IC         1.131
#define     OFF_IC          -1
#define     GAIN_VC         1.2155
#define     OFF_VC          -1.5
#define     GAIN_IB         1.1359
#define     OFF_IB          -0.14
#define     GAIN_VB         1.2259
#define     OFF_VB          -1.5
#define     GAIN_IA         1.1297
#define     OFF_IA          -2.2
#define     GAIN_VA         1.2188
#define     OFF_VA          -0.8

/*
// I_t
#define     GAIN_IH         1
#define     OFF_IH          0
#define     GAIN_IL         1
#define     OFF_IL          0
#define     GAIN_VL         1
#define     OFF_VL          0
#define     GAIN_VH         0.9091
#define     OFF_VH          0
#define     GAIN_IC         1.0
#define     OFF_IC          0
#define     GAIN_VC         1.2155
#define     OFF_VC          -1.5
#define     GAIN_IB         1.0
#define     OFF_IB          0
#define     GAIN_VB         1.2259
#define     OFF_VB          -1.5
#define     GAIN_IA         1.0
#define     OFF_IA          0
#define     GAIN_VA         1.2188
#define     OFF_VA          -0.8
*/

#elif DEVICE==1 // EASYRES 1

#define 	GAIN_IH			1.0633333
#define		OFF_IH			-0.5
#define		GAIN_IL			1.04664
#define		OFF_IL			-0.95
#define		GAIN_VL			0.942
#define		OFF_VL			0
#define		GAIN_VH			0.889
#define		OFF_VH			0
#define		GAIN_IC			1.0252
#define		OFF_IC			0
#define		GAIN_VC			1.0831
#define		OFF_VC			-1.88
#define		GAIN_IB			1.0244
#define		OFF_IB			-0.39
#define		GAIN_VB			1.0919
#define		OFF_VB			-1.02
#define		GAIN_IA			1.0151
#define		OFF_IA			-0.402
#define		GAIN_VA			1.0853
#define		OFF_VA			-4.97

#elif DEVICE==2 // EASYRES 2

#define 	GAIN_IH			0.98085
#define		OFF_IH			-0.17
#define		GAIN_IL			1.05529
#define		OFF_IL			-0.842
#define		GAIN_VL			0.9423
#define		OFF_VL			0
#define		GAIN_VH			0.8892
#define		OFF_VH			0
#define		GAIN_IC			1.0247
#define		OFF_IC			-0.1
#define		GAIN_VC			1.058
#define		OFF_VC			-2.3
#define		GAIN_IB			1.0061
#define		OFF_IB			-0.33
#define		GAIN_VB			1.0646
#define		OFF_VB			-1.7
#define		GAIN_IA			1.0311
#define		OFF_IA			-0.21
#define		GAIN_VA			1.066
#define		OFF_VA			-1.77167

#elif DEVICE==3 // EASYRES 3

#define 	GAIN_IH			1.267
#define		OFF_IH			1.35
#define		GAIN_IL			1.0528
#define		OFF_IL			-1
#define		GAIN_VL			0.923
#define		OFF_VL			1.7
#define		GAIN_VH			0.8858
#define		OFF_VH			0
#define		GAIN_IC			0.8426
#define		OFF_IC			0.05677
#define		GAIN_VC			1.0873
#define		OFF_VC			-4
#define		GAIN_IB			0.8764
#define		OFF_IB			-0.55
#define		GAIN_VB			1.0957
#define		OFF_VB			-4
#define		GAIN_IA			0.8751
#define		OFF_IA			-0.3
#define		GAIN_VA			1.0807
#define		OFF_VA			-2.818

#elif DEVICE==4  || DEVICE == 11  // TYPHOON

#define     GAIN_IN         1
#define     OFF_IN          0
#define 	GAIN_IH			1
#define		OFF_IH			0
#define		GAIN_IL			1
#define		OFF_IL			0
#define		GAIN_VL			1
#define		OFF_VL			0
#define		GAIN_VH			1
#define		OFF_VH			0
#define		GAIN_IC			1
#define		OFF_IC			0
#define		GAIN_VC			1
#define		OFF_VC			0
#define		GAIN_IB			1
#define		OFF_IB			0
#define		GAIN_VB			1
#define		OFF_VB			0
#define		GAIN_IA			1
#define		OFF_IA			0
#define		GAIN_VA			1
#define		OFF_VA			0

#elif DEVICE==5 // ALLT 1

#define     GAIN_IN         1.0212
#define     OFF_IN          -0.07
#define     GAIN_VH         1.1230
#define     GAIN_IC         1.0233
#define     OFF_IC          -0.05
#define     GAIN_VC         1.0775
#define     OFF_VC          -2.3
#define     GAIN_IB         1.0137
#define     OFF_IB          0
#define     GAIN_VB         1.0917
#define     OFF_VB          -1.1
#define     GAIN_IA         1.0116
#define     OFF_IA          -0.2
#define     GAIN_VA         1.0757
#define     OFF_VA          -1.6

#elif DEVICE==6 // ALLT 2

#define     GAIN_IN         1.0251
#define     OFF_IN          0.26
#define     GAIN_VH         1.1228
#define     GAIN_IC         1.0187
#define     OFF_IC          0.1
#define     GAIN_VC         1.0941
#define     OFF_VC          4.4
#define     GAIN_IB         1.0210
#define     OFF_IB          0.35
#define     GAIN_VB         1.0712
#define     OFF_VB          2
#define     GAIN_IA         1.0207
#define     OFF_IA          0.42
#define     GAIN_VA         1.0829
#define     OFF_VA          1.2

#elif DEVICE==7 // ALLT 3

#define     GAIN_IN         1.0478
#define     OFF_IN          0.1
#define     GAIN_VH         1.1379
#define     GAIN_IC         1.05
#define     OFF_IC          0
#define     GAIN_VC         1.0878
#define     OFF_VC          -1.3
#define     GAIN_IB         1.006
#define     OFF_IB          0
#define     GAIN_VB         1.1023
#define     OFF_VB          -1
#define     GAIN_IA         1.024
#define     OFF_IA          0
#define     GAIN_VA         1.0889
#define     OFF_VA          -0.3

#elif DEVICE==8 // ALLT 4

#define     GAIN_IN         1.0267
#define     OFF_IN          -0.04
#define     GAIN_VH         1.1190
#define     GAIN_IC         1.0328
#define     OFF_IC          0.29
#define     GAIN_VC         1.1001
#define     OFF_VC          0.75
#define     GAIN_IB         1.0286
#define     OFF_IB          0.3
#define     GAIN_VB         1.0992
#define     OFF_VB          1.15
#define     GAIN_IA         1.0236
#define     OFF_IA          0.2
#define     GAIN_VA         1.0923
#define     OFF_VA          1.7

#elif DEVICE==9  // ALLT 5

#define     GAIN_IN         1.0225
#define     OFF_IN          0.2
#define     GAIN_VH         1.1020
#define     GAIN_IC         1.0258
#define     OFF_IC          0.26
#define     GAIN_VC         1.0810
#define     OFF_VC          1.2
#define     GAIN_IB         1.0180
#define     OFF_IB          0.05
#define     GAIN_VB         1.0761
#define     OFF_VB          0
#define     GAIN_IA         1.0257
#define     OFF_IA          0.18
#define     GAIN_VA         1.0793
#define     OFF_VA          0.7

#elif DEVICE==10 // ALLT 6

#define     GAIN_IN         1.114
#define     OFF_IN          0.04
#define     GAIN_VH         1.2075
#define     GAIN_IC         1.0869
#define     OFF_IC          1.2
#define     GAIN_VC         1.0982
#define     OFF_VC          0.45
#define     GAIN_IB         1.006
#define     OFF_IB          0
#define     GAIN_VB         1.0971
#define     OFF_VB          0.1
#define     GAIN_IA         1.017
#define     OFF_IA          -0.2
#define     GAIN_VA         1.0777
#define     OFF_VA          0.3



#elif DEVICE==12 // BALANCE ALLT

#define     GAIN_IN         1
#define     OFF_IN          0
#define     GAIN_VH         1.1462
#define     GAIN_IC         1.0245
#define     OFF_IC          0.42
#define     GAIN_VC         1.0449
#define     OFF_VC          -0.8
#define     GAIN_IB         1.0096
#define     OFF_IB          -0.83
#define     GAIN_VB         1.0506
#define     OFF_VB          -0.6
#define     GAIN_IA         0.9918
#define     OFF_IA          -2.22
#define     GAIN_VA         1.0613
#define     OFF_VA          -2.9

#endif
// Generate Test ID for PLC startup routine

#if CTRL == 1 || CTRL == 2 || CTRL == 10 || CTRL == 11
#define testID					1

#elif CTRL == 3 || CTRL == 4  || CTRL == 8
#define testID					3

#elif CTRL == 5
#define testID					7

#elif CTRL == 6 || CTRL == 7
#define testID					13

#else
#define testID 0
#endif

// Limits of operation
#define V_pk_min 		32400       //34000
#if (CTRL == 10)
    #define V_pk_max 		14400       //14400
    #define V_h_min         180         //680
    #define V_h_max         220         //770
#else
    #define V_pk_max        65000       //65000
#if (CTRL == 11)
    #define V_h_min         500         //500
#else
    #define V_h_min         680         //680
#endif
    #define V_h_max         770         //770
#endif
#define V_l_min			100         //100
#define V_l_max			150         //150
#define I_l_max			25          //25
#if DEVICE == 0
    #define I_pk_max 		90          //40
#elif DEVICE == 4
    #define I_pk_max        200          //40
#elif DEVICE == 12
    #define I_pk_max        40          //200
#else
    #define I_pk_max        40          //40
#endif
#define omega_min 		200         //200
#define omega_max 		450         //450

// Transformation parameters
    // Rotation matrix
    #define c120          -0.5
    #define s120          0.866025403784439

// HFPS parameters
#define b_approach		1   			// 0 for linear piecewise approach for RRL boundary computation, 1 for asymptotic approach for RR limitation boundary computation
#define v_w				145 			// UC upper warning voltage
#define v_a				150				// UC upper alert voltage
#define u_aux			5				// v_a-v_w
#define r_n				200				// Rated upper boundary RRL (W/s)
#define r_a				20000			// Alert upper boundary RRL (W/s)
#define r_sm			5.05076e-5		// 1/(r_a-r_n+1)
#define k				1				// When using linear piecewise approach, RRL will increase linearly up to r_n*(k+1) after the warning voltage until it reaches the alert voltage

#if (CTRL == 12 || CTRL == 14)
    // Swing equation
    //#define Xv              0.8
    #define Xv              4.0
    #define Rv              0.0
    #define Kp_q            0.001626345596729
    #define Ki_q            0.016263455967291
    // CTRL 2
    //#define K_v_p           0.1
    //#define K_v_i           0.1
    // CTRL 1
    //#define K_c_p           15.1
    //#define K_c_i           0.1
#elif CTRL == 13
    #define Xv              0.2
    #define Rv              0.0
    #define Kp_q            0.001626345596729
    #define Ki_q            0.016263455967291
#elif CTRL == 15
    #define Xv              0.025
    #define Rv              0
    #define Kp_q            0.1
    #define Ki_q            1
#else
    // CTRL3 parameters
    //#define Xv				0.1
    #define Xv              0.5
    #define Rv				0
    #define Kp_q			0.1
    #define Ki_q			1
    //voltage loop
    //#define K_v_p           0.1
    //#define K_v_i           16
    //#define K_v_i           0.1
    //current
    //#define K_c_p           15.1
    //#define K_c_i           0.1
#endif
    #define omega_b         314.1592653589793
    //#define Kp_p            0.075 // KP1
    #define Kp_p            0.0159 // KP2
    #define Ki_p            0.1
    #define J_inv           2.03
    #define D_p             47.36
    #define omega_base_inv  0.003183098861838
    #define omega_base      314.1592653589793
    #define E_0             325.2691193458119

// CTRL1 parameters dq

#define K_i_p			3
#define K_i_i			320

// CTRL1 parameters alpha-beta

//#define K_r_p			5
//#define K_r_i			160
#define K_r_p           7.5      //7.5
#define K_r_i           640      //640
#define K_r3_i          160      //160

// DC/DC CTRL3 parameters
#define Kp_uc			-0.075
#define Ki_uc			-0.00013124

// DC/DC CTRL2 parameters
#define Kp_v_dc			0.0878
#define Ki_v_dc			0.73185

// DC/DC CTRL1 parameters
#define Kp_i_dc			3
#define Ki_i_dc			94.7

// CTRL 10 parameters dq FILTRO ALLT
//voltage loop
/*#define K_v_p           0.1
#define K_v_i           0.4
//current
#define K_c_p           4.1
#define K_c_i           10.0*/

// CTRL 11 parameters DC-Control
// CTRL1 AC current controller parameters used
//DC voltage loop
#define Kp_dc           0.15
#define Ki_dc           1.5

// import math.h
#define __BSD_VISIBLE
#include "math.h"

struct PLL_output{
	double theta, omega, V_d, V_q, I_d, I_q, sin, cos, alfa_I, beta_I, alfa_V, beta_V;
};


struct powers{
	double P3f, Q3f, p_losses, p_HFPS, p_pri_fil, p_uc_ref, p_ref;
	double Pa, Qa, Pb, Qb, Pc, Qc;
};

struct dcdc_refs{
	double P_uc_ref, eta_dc;
};

struct ADC_conv{
    double I_h, I_l, V_l, V_h, I_c, V_c, I_b, V_b, I_a, V_a, I_n;
};

struct dq_abc{
    double da, qa, db, qb, dc, qc;
};
struct duty_cycle{
	double eta_d, eta_q, eta_a, eta_b, eta_c, eta_alfa, eta_beta, eta_pk, eta_dc, eta_n;
};

struct state_m{
	double PWM_enabled, Fault_Type, Reset_Drivers;
};

struct CAN_read{
    int start_FSM, start_AC, start_DC, start_Primary, sync, enable_P_ref, enable_HFPS, enable_AHF, enable_n;
	double  i_d_ref, i_q_ref, ida_ref, iqa_ref, idb_ref, iqb_ref, idc_ref, iqc_ref, P_pu_ref, Q_pu_ref, V_h_ref, V_uc_ref, I_l_ref, etas, eta_dc, H;
    double Pa_ref, Qa_ref, Pb_ref, Qb_ref, Pc_ref, Qc_ref;
    double M_a, sin_a, cos_a, M_b, sin_b, cos_b, M_c, sin_c, cos_c;
    double p_ref, q_ref;
    //int wires,  V_h_max,  V_pk_max, V_l_min, V_l_max, V_h_min, I_pk_max, I_l_max, V_pk_min;
    //int omega_min, omega_max, I_h_max;

};

struct dq{
    double d, q;
};

struct afbt{
    double af, bt;
};

struct abc{
    double a, b, c;
};

struct signal{
    double a, b, c, n, alfa, beta, d, q;
};

struct rms{
	double ia_rms, ib_rms, ic_rms, in_rms, va_rms, vb_rms, vc_rms;
};

struct uvsg{
	double omega, theta, e_d, e_q, omega_rads, DV, p_s, q_s, sin, cos, i_d_ref, i_q_ref, v_d_ref, v_q_ref;
};

struct svpwm_ref{
  double vref, phref;
};

