// Libraries
#include "DSP28x_Project.h"
#include "type_structs.h"
#include <string.h>

// Constants
#define SEQ1_ADC_INT_ENABLE     1
#define SEQ2_ADC_INT_ENABLE     1


// Prototypes
interrupt void adc_SEQ1_isr(void);
interrupt void adc_SEQ2_isr(void);                                                                          // ADC Interrupt
void Setup_ePWM(void);                                                                                      // ePWM Configuration
void Setup_DMA(Uint16 *ADC_read, Uint16 *duty);                                                                         // DMA Configuration
void Setup_ADC(void);                                                                                       // ADC Configuration
void Setup_eCAN(void);                                                                                      // eCAN Configuration
struct ADC_conv Conversion_ADC(Uint16 *ADC_read);                                                           // ADC Conversion
void Setup_GPIO(void);                                                                                      // GPIO Configuration
//struct PLL_output PLL_dq(struct ADC_conv, struct uvsg u, double sync);                                      // PLL and Park transformation
struct PLL_output PLL_dq(struct ADC_conv, struct uvsg u, double sync, int startAC);
//struct signal DQF_transform(struct PLL_output PLL, struct CAN_read CAN);
struct uvsg CTRL3_comp(double enable_P_ref, double P_pu_ref, double Q_pu_ref, double sync, struct ADC_conv, struct PLL_output, double runFSM);      // i_sdq_ref computation
struct uvsg SWING(double p_ref, double q_ref, double sync, struct PLL_output Park, double runFSM);
struct duty_cycle CTRL1_PQ_comp_albe(struct ADC_conv ADC_p, struct PLL_output PLL_dq, double omega, double p_pu_ref, double q_pu_ref, struct signal it_ref, int flag, struct CAN_read CAN);
struct duty_cycle ctrl_z3(struct ADC_conv ADC_p);
struct duty_cycle CTRL1_comp(struct ADC_conv ADC_p, struct PLL_output PLL_dq, double theta, double omega, double i_d_ref, double i_q_ref, int flag);
struct duty_cycle CTRL1_PQ_comp(struct ADC_conv ADC_p, struct PLL_output PLL_dq, double omega, double p_pu_ref, double q_pu_ref, int flag);
struct duty_cycle CTRL2_comp(struct ADC_conv ADC_p, struct PLL_output PLL_dq, double theta, double omega, double i_d_ref, double i_q_ref, int flag);
struct duty_cycle OPEN_LOOP(double eta);
struct duty_cycle sector_comp(double v_h, double vref, double phref);
struct duty_cycle STATCOM_comp(struct ADC_conv ADC_p, struct PLL_output PLL_dq, double theta, double omega, double i_d_ref, double vh_ref, int flag);
double CTRL3_DC_comp(struct ADC_conv ADC_p, double v_uc_ref, int flag);                                     // p_uc_ref computation
double CTRL2_DC_comp(struct ADC_conv ADC_p, double vh_ref, int flag);                                       // i_l_ref computation
double CTRL1_DC_comp(struct ADC_conv, double i_l_ref, int flag);                                            // eta_dc computation
struct duty_cycle Park_inverse(struct PLL_output, struct duty_cycle);                                       // Park Inverse
void enable_ePWM(int enableAC, int enableDC);                                                                               // Enable/Disable ePWM
struct state_m state_mach(struct ADC_conv ADC_p, struct rms rms_v, double runFSM, double driver_fault, double V_q, double omega, struct CAN_read limites);          // State machine
void MBXwrA(void);                                                                                          // This function initializes all 32 MBOXes of CAN-A
long long mailbox_read(int16);                                                                              // Reads the message in a specified mailbox
struct CAN_read eCAN_RW(struct ADC_conv, struct rms rms_calc, struct powers power, struct PLL_output, struct uvsg uvsg_out, struct state_m);
double ramp_rate_limit(double in, double ramped_in, double ramp_rate);                                      // Ramp rate function
double rrl_boundary_comp(double v_l, double v_uc_ref);                                                      // RRL boundary computation
struct powers power_calc_ctrl3(struct ADC_conv ADC_p, struct powers p_calc, double p_pu_ref, int enable_P_ref, int enable_HFPS, double v_uc_ref);  // Powers calculation function
struct powers power_computation (struct ADC_conv ADC, unsigned int SCH);
struct rms rms_calculation(struct ADC_conv, unsigned int SCH);                                                              // RMS Calculation
void reset_drivers(int reset);
struct signal power2current(struct ADC_conv ADC, struct CAN_read CAN, unsigned int SCH, struct powers* Pow, struct powers* Pow_f, struct PLL_output PLL_dq);

// SCHEDULER
unsigned int T_SCH = 0; /*0-10 -> Ts_sch = 5e-4 -> 40 samples/cicle*/
/* 1: RMS Va Ia
 * 2: RMS Vb Ib
 * 3: RMS Vc Ic
 * 4: RMS In
 * 5: Pa
 * 6: Qa
 * 7: Pb
 * 8: Qb
 * 9: Pc
 * 10: Qc
 */
// Global variables
#pragma DATA_SECTION(ADC_read,"DMARAML4");
Uint16 ADC_read[12];                // ADC Registers
#pragma DATA_SECTION(duty,"DMARAML4");
Uint16 duty[4];
struct powers p={0,0,0,0,0,0,0,0,0,0,0,0,0};
struct powers p_f={0,0,0,0,0,0,0,0,0,0,0,0,0};
double vh_ref_ramp=0; // Variables calculo de potencia
float buffer[400];
int buffer_counter=0, selector;
double eta_dc, i_l_ref, etas=0;
struct CAN_read consignas = {0,0,0,0,0,0,0,0,0,
                             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                             0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                             //4,800,280,90,180,580,30,30,200,
                             //280,380,30};
struct uvsg uvsg_out= {0,0,0,0,0,0,0,0,1,0,0,0,0,0};
long long read_register;
struct svpwm_ref svref = {0,0};
int ADC_counter=0;
struct rms rms_values;
struct signal it_ref = {0,0,0,0,0,0,0,0};


// Interrupt variables: provisionally here
struct ADC_conv ADC_processed;
struct PLL_output PLL_Park= (const struct PLL_output){0};
struct duty_cycle eta, eta_park, y_aux_al, y_aux_be;
struct duty_cycle eta_z = {0,0,0,0,0,0,0,0,0,0};
struct state_m state;


// Memory addresses needed to copy code from Flash to RAM

extern unsigned int RamfuncsLoadStart;
extern unsigned int RamfuncsLoadEnd;
extern unsigned int RamfuncsLoadEnd;
extern unsigned int RamfuncsRunStart;

// Main function
void main(void)
{
    // DSP Initialization
    InitSysCtrl();

    EALLOW;
    SysCtrlRegs.MAPCNF.bit.MAPEPWM = 1; // Enables ePWM remap to Peripheral Frame 3 (accessible by DMA)
    EDIS;

    //location of the memory from the flash to the RAM
    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, &RamfuncsLoadEnd - &RamfuncsLoadStart);

    //Initialization of the flash memory
    InitFlash();

    // Define ADCCLK clock frequency to 25 MHz
    EALLOW;
    SysCtrlRegs.HISPCP.all = 0x3; // 25 MHz
    EDIS;

    // GPIOs Initialization and Configuration
    InitGpio();
    Setup_GPIO();

    // Disable Interrupts
    DINT;

    // PIE Initialization
    InitPieCtrl();

    // Disable interrupts flags
    IER = 0x0000;
    IFR = 0x0000;

    // PIE Initializations with ISR
    InitPieVectTable();

    // Mapping interrupts to ISR
    EALLOW;
    PieVectTable.SEQ1INT = &adc_SEQ1_isr;
    PieVectTable.SEQ2INT = &adc_SEQ2_isr;
    EDIS;

    //DMA Init
    DMAInitialize();
    Setup_DMA(ADC_read, duty);

    // ADC Initialization
    InitAdc();
    Setup_ADC();

    // PIE Interrupts
    PieCtrlRegs.PIEIER1.bit.INTx1 = SEQ1_ADC_INT_ENABLE;
    PieCtrlRegs.PIEIER1.bit.INTx2 = SEQ2_ADC_INT_ENABLE;

    // ePWM Initialization
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
    EDIS;

    Setup_ePWM();

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;
    EDIS;

    // eCAN Initialization

    InitECana(); // Initialize eCAN-A module
    InitECanGpio();
    Setup_eCAN();


    // Enable Interrupt groups 1/3 that corresponds to ePWM and ADC
    IER |= M_INT3;
    IER |= M_INT1;

    // Enable Interrupts
    EINT;
    ERTM;

    // Loop forever
    while(1)    {
        if (ADC_counter >2000){
            ADC_counter=0;

//Uncomment if CAN parameters are wanted in debug for TYPHOON
#if DEVICE != 4 //|| DEVICE =! 11
            consignas=eCAN_RW(ADC_processed, rms_values, p, PLL_Park, uvsg_out, state);
#endif

        }

    }

}


// ADC Interrupt 1
#pragma CODE_SECTION(adc_SEQ1_isr,"ramfuncs")
interrupt void adc_SEQ1_isr(void)
{
    // Reinitialize for next ADC sequence
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


// ADC Interrupt 2
#pragma CODE_SECTION(adc_SEQ2_isr,"ramfuncs")
interrupt void adc_SEQ2_isr(void)
{
    ADC_counter++;


#if SCHEDULER_ON == 1
    if (T_SCH < 10){T_SCH++;}
    else{T_SCH=0;}
#endif

#if (DEVICE == 4 || DEVICE == 11 )
    if(GpioDataRegs.GPADAT.bit.GPIO12==0){GpioDataRegs.GPASET.bit.GPIO12=1;}
            else{GpioDataRegs.GPACLEAR.bit.GPIO12=1;}
#endif
    // Calibration
    ADC_processed = Conversion_ADC(ADC_read);
    rms_values = rms_calculation(ADC_processed, T_SCH);
    #if (CTRL == 2 || CTRL == 3 || CTRL == 5 || CTRL == 6 || CTRL == 8)
        p = power_computation(ADC_processed,T_SCH);
    #endif
    // PLL and Park transformation
    PLL_Park = PLL_dq(ADC_processed, uvsg_out, consignas.sync, state.PWM_enabled && consignas.start_AC);

    // State machine
    #if (CTRL == 4 || CTRL == 7 || CTRL == 12 || CTRL == 13 || CTRL == 14 || CTRL == 15 || CTRL == 16)    // CTRL3
        state = state_mach(ADC_processed, rms_values, consignas.start_FSM, 0, PLL_Park.V_q, uvsg_out.omega_rads, consignas);
    #elif (CTRL == 2 || CTRL == 3 || CTRL == 5 || CTRL == 6 || CTRL == 8|| CTRL == 10 || CTRL == 11)   // NOT CTRL3
        state = state_mach(ADC_processed, rms_values, consignas.start_FSM, 0, PLL_Park.V_q, PLL_Park.omega, consignas);
    #else
        state.PWM_enabled=1;
    #endif
    #if (FSM == 0)
            state.PWM_enabled=1;
    #endif
    // enable/disable ePWM
    enable_ePWM(state.PWM_enabled && consignas.start_AC, state.PWM_enabled && consignas.start_DC);

    // Driver reset
    reset_drivers(state.Reset_Drivers);

   #if (CTRL_Z == 1)
    eta_z = ctrl_z3(ADC_processed);
    #endif

    #if (CTRL == 6 || CTRL == 7) // CTRL3 DCDC
        // DC/DC: CTRL3
        p.p_uc_ref=CTRL3_DC_comp(ADC_processed, consignas.V_uc_ref, consignas.enable_P_ref);

        // DC/DC: CTRL2
        vh_ref_ramp=ramp_rate_limit(consignas.V_h_ref,vh_ref_ramp,50); // RRL de 50 V/s para la consigna de Vh
        i_l_ref=CTRL2_DC_comp(ADC_processed, vh_ref_ramp, state.PWM_enabled && consignas.start_DC);
        eta_dc=CTRL1_DC_comp(ADC_processed, i_l_ref, state.PWM_enabled && consignas.start_DC);
    #endif

    #if (CTRL == 5) // CTRL1 DCDC
        // DC/DC: CTRL1
        eta_dc=CTRL1_DC_comp(ADC_processed, consignas.I_l_ref, state.PWM_enabled && consignas.start_DC);
    #endif

    #if (CTRL == 7)     // CTRL3 WHEN OPERATING WITH DC/DC
        p=power_calc_ctrl3(ADC_processed, p, consignas.P_pu_ref, consignas.enable_P_ref, consignas.enable_HFPS, consignas.V_uc_ref);
        uvsg_out = CTRL3_comp(consignas.enable_P_ref, p.p_ref, consignas.Q_pu_ref, consignas.sync, ADC_processed, PLL_Park, state.PWM_enabled && consignas.start_AC);
        p.P3f=uvsg_out.p_s*20000;
        p.Q3f=uvsg_out.q_s*20000;

    #elif (CTRL == 4)   // PI-CC: CTRL3 WHEN NOT OPERATING WITH DC/DC
        uvsg_out = CTRL3_comp(consignas.enable_P_ref, consignas.P_pu_ref, consignas.Q_pu_ref, consignas.sync, ADC_processed, PLL_Park, state.PWM_enabled && consignas.start_AC);
        p.P3f=uvsg_out.p_s*20000;
        p.Q3f=uvsg_out.q_s*20000;

    #endif

    #if (CTRL == 16) // PI-OL
        uvsg_out = CTRL3_comp(consignas.enable_P_ref, consignas.P_pu_ref, consignas.Q_pu_ref, consignas.sync, ADC_processed, PLL_Park, state.PWM_enabled && consignas.start_AC);
        p.P3f=uvsg_out.p_s*20000.0;
        p.Q3f=uvsg_out.q_s*20000.0;
        eta.eta_d = 2.0*uvsg_out.e_d/ADC_processed.V_h;
        eta.eta_q = 2.0*uvsg_out.e_q/ADC_processed.V_h;

        eta.eta_alfa = eta.eta_d*PLL_Park.cos - eta.eta_q*PLL_Park.sin;
        eta.eta_beta = eta.eta_d*PLL_Park.sin + eta.eta_q*PLL_Park.cos;

        eta.eta_a = eta.eta_alfa;
        eta.eta_b = -0.5*eta.eta_alfa + 0.866025403784439*eta.eta_beta;
        eta.eta_c = -0.5*eta.eta_alfa - 0.866025403784439*eta.eta_beta;
    #endif

    #if (CTRL == 15) // PI-VC
        uvsg_out = CTRL3_comp(consignas.enable_P_ref, consignas.P_pu_ref, consignas.Q_pu_ref, consignas.sync, ADC_processed, PLL_Park, state.PWM_enabled && consignas.start_AC);
        p.P3f=uvsg_out.p_s*20000.0;
        p.Q3f=uvsg_out.q_s*20000.0;
        eta=CTRL2_comp(ADC_processed, PLL_Park, uvsg_out.theta, uvsg_out.omega, uvsg_out.v_d_ref, uvsg_out.v_q_ref, state.PWM_enabled && consignas.start_AC);
    #endif

    #if (CTRL == 12) // S-OL
        uvsg_out = SWING(consignas.P_pu_ref*20000.0, consignas.Q_pu_ref*20000.0, consignas.sync, PLL_Park, state.PWM_enabled && consignas.start_AC);
        p.P3f=uvsg_out.p_s;
        p.Q3f=uvsg_out.q_s;
        eta.eta_d = 2.0*uvsg_out.e_d/ADC_processed.V_h;
        eta.eta_q = 2.0*uvsg_out.e_q/ADC_processed.V_h;

        eta.eta_alfa = eta.eta_d*PLL_Park.cos - eta.eta_q*PLL_Park.sin;
        eta.eta_beta = eta.eta_d*PLL_Park.sin + eta.eta_q*PLL_Park.cos;

        eta.eta_a = eta.eta_alfa;
        eta.eta_b = -0.5*eta.eta_alfa + 0.866025403784439*eta.eta_beta;
        eta.eta_c = -0.5*eta.eta_alfa - 0.866025403784439*eta.eta_beta;
    #endif

    #if (CTRL == 13) // S-VC
        uvsg_out = SWING(consignas.P_pu_ref*20000.0, consignas.Q_pu_ref*20000.0, consignas.sync, PLL_Park, state.PWM_enabled && consignas.start_AC);
        p.P3f=uvsg_out.p_s;
        p.Q3f=uvsg_out.q_s;
        eta=CTRL2_comp(ADC_processed, PLL_Park, uvsg_out.theta, uvsg_out.omega, uvsg_out.v_d_ref, uvsg_out.v_q_ref, state.PWM_enabled && consignas.start_AC);
    #endif

    #if (CTRL == 14)   // S-CC
        uvsg_out = SWING(consignas.P_pu_ref*20000.0, consignas.Q_pu_ref*20000.0, consignas.sync, PLL_Park, state.PWM_enabled && consignas.start_AC);
        p.P3f=uvsg_out.p_s;
        p.Q3f=uvsg_out.q_s;
        eta=CTRL1_comp(ADC_processed, PLL_Park, uvsg_out.theta, uvsg_out.omega, uvsg_out.i_d_ref, uvsg_out.i_q_ref, state.PWM_enabled && consignas.start_AC);
    #endif

    #if (CTRL == 4 || CTRL == 7)    // CTRL1 WHEN OPERATING WITH CTRL3
        eta=CTRL1_comp(ADC_processed, PLL_Park, uvsg_out.theta, uvsg_out.omega, uvsg_out.i_d_ref, uvsg_out.i_q_ref, state.PWM_enabled && consignas.start_AC);

    #elif (CTRL == 3)   // CTRL1 WHEN NOT OPERATING WITH CTRL3 OR DC/DC, WITH PQ REFERENCES
        eta=CTRL1_PQ_comp(ADC_processed, PLL_Park, PLL_Park.omega, consignas.P_pu_ref, consignas.Q_pu_ref, state.PWM_enabled && consignas.start_AC);

    #elif (CTRL == 8)   // CTRL1 (alpha-beta current controller bac3ph3wgfolalbe)
        //it_ref = DQF_transform(PLL_Park, consignas);
        it_ref = power2current(ADC_processed, consignas, T_SCH, &p, &p_f, PLL_Park);
        eta=CTRL1_PQ_comp_albe(ADC_processed, PLL_Park, PLL_Park.omega, consignas.P_pu_ref, consignas.Q_pu_ref, it_ref, state.PWM_enabled && consignas.start_AC, consignas);

    #elif (CTRL == 6)   // CTRL1 WHEN NOT OPERATING WITH CTRL3 AND OPERATING WITH DC/DC, WITH PQ REFERENCES
        p=power_calc(ADC_processed, p, consignas.P_pu_ref, consignas.enable_P_ref, consignas.enable_HFPS, consignas.V_uc_ref);
        eta=CTRL1_PQ_comp(ADC_processed, PLL_Park, PLL_Park.omega, p.p_ref, consignas.Q_pu_ref, state.PWM_enabled && consignas.start_AC);

    #elif (CTRL == 2 || CTRL == 5)  // CTRL1 WHEN NOT OPERATING WITH CTRL 3, WITH CURRENT REFERENCES
        //eta=CTRL1_comp(ADC_processed, PLL_Park, PLL_Park.theta, PLL_Park.omega, consignas.etas, consignas.i_q_ref, state.PWM_enabled && consignas.start_AC);
        eta=CTRL1_comp(ADC_processed, PLL_Park, PLL_Park.theta, PLL_Park.omega, consignas.ida_ref, consignas.iqa_ref, state.PWM_enabled && consignas.start_AC);
    #elif (CTRL == 10)
        eta=CTRL2_comp(ADC_processed, PLL_Park, PLL_Park.theta, PLL_Park.omega, consignas.i_d_ref, consignas.i_q_ref, state.PWM_enabled && consignas.start_AC);
    #elif (CTRL == 11)
        vh_ref_ramp=ramp_rate_limit(consignas.V_h_ref,vh_ref_ramp,50);
        eta = STATCOM_comp(ADC_processed, PLL_Park, PLL_Park.theta, PLL_Park.omega, consignas.i_d_ref, vh_ref_ramp, state.PWM_enabled && consignas.start_AC);
    #endif

    #if (CTRL == 1)  // OPEN LOOP
      eta = OPEN_LOOP(consignas.etas);
    //    eta = OPEN_LOOP(ADC_processed, PLL_Park, consignas.etas);
    #endif

    // Establishing the comparison values
        duty[1]=0;
#if MODULATION == 0 && CTRL != 1 && CTRL != 10  && CTRL != 8   // SPWM
        // carrier based PWM
        duty[0]=(int) PWM_TIMER_TBPRD*((eta.eta_c+1)*0.5);
        duty[2]=(int) PWM_TIMER_TBPRD*((eta.eta_a+1)*0.5);
        duty[3]=(int) PWM_TIMER_TBPRD*((eta.eta_b+1)*0.5);
        duty[1]=(int) PWM_TIMER_TBPRD*((eta.eta_n+1)*0.5);
//        duty[0]=(int) PWM_TIMER_TBPRD*(eta.eta_c + eta_z.eta_c + 0.5);
//        duty[2]=(int) PWM_TIMER_TBPRD*(eta.eta_a + eta_z.eta_a + 0.5);
//        duty[3]=(int) PWM_TIMER_TBPRD*(eta.eta_b + eta_z.eta_b + 0.5);
//        duty[1]=(int) PWM_TIMER_TBPRD*(eta.eta_n + 0.5);

#elif MODULATION == 1 || CTRL == 1 || CTRL == 10 || CTRL == 8   // SVPWM
        // NOT SVPWM, carrier based PWM
        duty[0]=(int) PWM_TIMER_TBPRD*((eta.eta_c+1)*0.5);
        duty[2]=(int) PWM_TIMER_TBPRD*((eta.eta_a+1)*0.5);
        duty[3]=(int) PWM_TIMER_TBPRD*((eta.eta_b+1)*0.5);
        duty[1]=(int) PWM_TIMER_TBPRD*((eta.eta_n+1)*0.5);
/*
        // original SVPWM
        duty[0]=(int) PWM_TIMER_TBPRD*(eta.eta_c);
        duty[2]=(int) PWM_TIMER_TBPRD*(eta.eta_a);
        duty[3]=(int) PWM_TIMER_TBPRD*(eta.eta_b);
*/
#endif

#if (CTRL == 5 || CTRL == 6 || CTRL == 7) // DCDC
    duty[1]=(int) PWM_TIMER_TBPRD*(eta_dc);
#endif
    // Reinitialize for next ADC sequence
    AdcRegs.ADCTRL2.bit.RST_SEQ2 = 1;
    AdcRegs.ADCST.bit.INT_SEQ2_CLR = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}




