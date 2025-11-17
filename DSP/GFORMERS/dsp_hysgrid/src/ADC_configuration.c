#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"

// ADC Configuration
void Setup_ADC(void)
{
#if (DEVICE==1 || DEVICE==2 || DEVICE==3 || DEVICE==0) // EASY-RES PROTOTYPE
	AdcRegs.ADCTRL3.bit.SMODE_SEL = 0x0; // Setup sequential sampling mode
	AdcRegs.ADCMAXCONV.all = 0x0017; // 10 conversiones en total (8 para el SEQ1, 2 para el SEQ2)
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x9; // Setup conv from ADCINB1
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0xA; // Setup conv from ADCINB2
	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0xB; // Setup conv from ADCINB3
	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0xC; // Setup conv from ADCINB4
	AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0xD; // Setup conv from ADCINB5
	AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0xE; // Setup conv from ADCINB6
	AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0xF; // Setup conv from ADCINB7
	AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x1; // Setup conv from ADCINA1
	AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0x0; // Setup conv from ADCINA0
	AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0x8; // Setup conv from ADCINB0


	AdcRegs.ADCTRL2.all = 0;
	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;
	AdcRegs.ADCTRL2.bit.EPWM_SOCB_SEQ2 = 1;
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ2 = 1;

#elif (DEVICE==5 || DEVICE==6 || DEVICE==7 || DEVICE==8 || DEVICE==9 || DEVICE==10 || DEVICE==12 ) // ALLT

    AdcRegs.ADCTRL3.bit.SMODE_SEL = 0x0; // Setup sequential sampling mode
    AdcRegs.ADCMAXCONV.all = 0x0017; // 10 conversiones en total (8 para el SEQ1, 2 para el SEQ2)

    AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x0; // Setup conv from ADCINA0
    AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0x8; // Setup conv from ADCINB0
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x9; // Setup conv from ADCINB1
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0xA; // Setup conv from ADCINB2
    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0xB; // Setup conv from ADCINB3
    AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0xC; // Setup conv from ADCINB4
    AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0xD; // Setup conv from ADCINB5
    AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0xE; // Setup conv from ADCINB6
    AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0xF; // Setup conv from ADCINB7
    AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0x1; // Setup conv from ADCINA1


    AdcRegs.ADCTRL2.all = 0;
    AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;
    AdcRegs.ADCTRL2.bit.EPWM_SOCB_SEQ2 = 1;
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ2 = 1;

#elif (DEVICE == 4)		// TYPHOON  Slot 1

	AdcRegs.ADCTRL3.bit.SMODE_SEL = 0x0; // Setup sequential sampling mode
	AdcRegs.ADCMAXCONV.all = 0x0037; // 12 conversiones en total (8 para el SEQ1 y 4 para el SEQ2)

	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x2; // Setup conv from ADCINA2
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x8; // Setup conv from ADCINB0
	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x1; // Setup conv from ADCINA1
	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x0; // Setup conv from ADCINA0
	AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0xB; // Setup conv from ADCINB3
	AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0xC; // Setup conv from ADCINB4
	AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0xD; // Setup conv from ADCINB5
	AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0xE; // Setup conv from ADCINB6
	AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0xF; // Setup conv from ADCINB7
	AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0x3; // Setup conv from ADCINA3
	AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 0x4; // Setup conv from ADCINA4
	AdcRegs.ADCCHSELSEQ3.bit.CONV11 = 0x5; // Setup conv from ADCINA5

    AdcRegs.ADCTRL2.all = 0;
    AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;
    AdcRegs.ADCTRL2.bit.EPWM_SOCB_SEQ2 = 1;
    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ2 = 1;

#elif DEVICE == 11           // TYPHOON  Slot 2

    AdcRegs.ADCTRL3.bit.SMODE_SEL = 0x0; // Setup sequential sampling mode
    AdcRegs.ADCMAXCONV.all = 0x0037; // 12 conversiones en total (8 para el SEQ1 y 4 para el SEQ2)

	// For the second DSP that will be connected to typhoon
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x1; // Setup conv from ADCINA1
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x2; // Setup conv from ADCINA2
    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x3; // Setup conv from ADCINA3
    AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x4; // Setup conv from ADCINA4
    AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x5; // Setup conv from ADCINA5
    AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x6; // Setup conv from ADCINA6
    AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x7; // Setup conv from ADCINA7
    AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0xE; // Setup conv from ADCINB6
    AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0xC; // Setup conv from ADCINB4
    AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0x0; // Setup conv from ADCINA0
    AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 0x9; // Setup conv from ADCINB1
    AdcRegs.ADCCHSELSEQ3.bit.CONV11 = 0xA; // Setup conv from ADCINB2



	AdcRegs.ADCTRL2.all = 0;
	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1 = 1;
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;
	AdcRegs.ADCTRL2.bit.EPWM_SOCB_SEQ2 = 1;
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ2 = 1;

#endif

}

// Calibration and conversion
#pragma CODE_SECTION(Conversion_ADC,"ramfuncs")
struct ADC_conv Conversion_ADC(Uint16 *ADC_read)
{
	struct ADC_conv s;
	static double i_l_ant=0, v_l_ant=0,i_h_ant=0,v_h_ant=0;

#if (DEVICE==1 || DEVICE==2 || DEVICE==3) // EASY-RES PROTOTYPE

	static double zero_set=0;

	s.I_h = (double) (((ADC_read[7]*0.000732421875 - 1.5)*25) + OFF_IH)*GAIN_IH;
	s.I_l = (double) (((ADC_read[8]*0.000732421875 - 1.5)*50) + OFF_IL)*GAIN_IL;
	s.V_l = (double) (ADC_read[9]*0.052840825244310 + OFF_VL)*GAIN_VL;
	s.V_h = (double) (ADC_read[0]*0.211363300977241 + OFF_VH)*GAIN_VH;
	s.I_c = (double) (((ADC_read[1]*0.000732421875 - 1.5)*25) + OFF_IC)*GAIN_IC;
	s.V_c = (double) (((ADC_read[2]*0.000732421875 - 1.5)*234) + OFF_VC)*GAIN_VC;
	s.I_b = (double) (((ADC_read[3]*0.000732421875 - 1.5)*25) + OFF_IB)*GAIN_IB;
	s.V_b = (double) (((ADC_read[4]*0.000732421875 - 1.5)*234) + OFF_VB)*GAIN_VB;
	s.I_a = (double) (((ADC_read[5]*0.000732421875 - 1.5)*25) + OFF_IA)*GAIN_IA;
	s.V_a = (double) (((ADC_read[6]*0.000732421875 - 1.5)*234) + OFF_VA)*GAIN_VA;

	// Zero-sequence cancellation

	/*zero_seq=(s.V_a+s.V_b+s.V_c)*0.333333333333333;
	s.V_a=s.V_a-zero_seq;
	s.V_b=s.V_b-zero_seq;
	s.V_c=s.V_c-zero_seq;*/

#elif (DEVICE==0) // EASY-RES PROTOTYPE

    static double zero_set=0;

    s.I_h = (double) (((ADC_read[7]*0.000732421875 - 1.5)*25) + OFF_IH)*GAIN_IH;
    s.I_l = (double) (((ADC_read[8]*0.000732421875 - 1.5)*50) + OFF_IL)*GAIN_IL;
    s.V_l = (double) (ADC_read[9]*0.052840825244310 + OFF_VL)*GAIN_VL;
    s.V_h = (double) (ADC_read[0]*0.211363300977241 + OFF_VH)*GAIN_VH;
    s.I_c = (double) (((ADC_read[1]*0.000732421875 - 1.5)*200) + OFF_IC)*GAIN_IC;//200
    s.V_c = (double) (((ADC_read[2]*0.000732421875 - 1.5)*234) + OFF_VC)*GAIN_VC;
    s.I_b = (double) (((ADC_read[3]*0.000732421875 - 1.5)*200) + OFF_IB)*GAIN_IB;//200
    s.V_b = (double) (((ADC_read[4]*0.000732421875 - 1.5)*234) + OFF_VB)*GAIN_VB;
    s.I_a = (double) (((ADC_read[5]*0.000732421875 - 1.5)*200) + OFF_IA)*GAIN_IA;//200
    s.V_a = (double) (((ADC_read[6]*0.000732421875 - 1.5)*234) + OFF_VA)*GAIN_VA;

#elif (DEVICE==5 || DEVICE==6 || DEVICE==7 || DEVICE==8 || DEVICE==9 || DEVICE==10 || DEVICE==12 ) // ALLT

    static double zero_set=0;

    s.V_h = (double) ((ADC_read[0] + ADC_read[8])*0.09814453125)*GAIN_VH;  // Vh
    s.I_c = (double) (((ADC_read[1]*0.000732421875 - 1.5)*25) + OFF_IC)*GAIN_IC;    // Ic
    s.V_c = (double) (((ADC_read[2]*0.000732421875 - 1.5)*234) + OFF_VC)*GAIN_VC;   // Vc
    s.I_b = (double) (((ADC_read[3]*0.000732421875 - 1.5)*25) + OFF_IB)*GAIN_IB;    // Ib
    s.V_b = (double) (((ADC_read[4]*0.000732421875 - 1.5)*234) + OFF_VB)*GAIN_VB;   // Vb
    s.I_a = (double) (((ADC_read[5]*0.000732421875 - 1.5)*25) + OFF_IA)*GAIN_IA;    // Ia
    s.V_a = (double) (((ADC_read[6]*0.000732421875 - 1.5)*234) + OFF_VA)*GAIN_VA;   // Va
    s.I_n = (double) (((ADC_read[7]*0.000732421875 - 1.5)*25) + OFF_IN)*GAIN_IN;    // In

#elif (DEVICE==4)			// TYPHOON Slot 1

	s.I_h = (double) ((ADC_read[9]*0.000244140625 - 0.5)*10*10 + OFF_IH)*GAIN_IH;	// I_h
    s.I_n = (double) ((ADC_read[10]*0.000244140625 - 0.5)*10*20 + OFF_IN)*GAIN_IN;  // I_n
	s.I_l = (double) ((ADC_read[0]*0.000244140625 - 0.5)*10*10 + OFF_IL)*GAIN_IL;	// I_l
	s.V_l = (double) ((ADC_read[2]*0.000244140625 - 0.5)*10*50 + OFF_VL)*GAIN_VL;	// V_l
	s.V_h = (double) ((ADC_read[1]*0.000244140625 - 0.5)*10*200 + OFF_VH)*GAIN_VH;	// V_h
	s.I_c = (double) ((ADC_read[3]*0.000244140625 - 0.5)*10*20 + OFF_IC)*GAIN_IC;	// I_c
	s.V_c = (double) ((ADC_read[4]*0.000244140625 - 0.5)*10*100 + OFF_VC)*GAIN_VC;	// V_c
	s.I_b = (double) ((ADC_read[5]*0.000244140625 - 0.5)*10*20 + OFF_IB)*GAIN_IB;	// I_b
	s.V_b = (double) ((ADC_read[6]*0.000244140625 - 0.5)*10*100 + OFF_VB)*GAIN_VB;	// V_b
	s.I_a = (double) ((ADC_read[7]*0.000244140625 - 0.5)*10*20 + OFF_IA)*GAIN_IA;	// I_a
	s.V_a = (double) ((ADC_read[8]*0.000244140625 - 0.5)*10*100 + OFF_VA)*GAIN_VA;	// V_a
/*
    s.I_h = (double) ((ADC_read[9]*0.0244140625 - 50) + OFF_IH)*GAIN_IH;   // I_h
    s.I_n = (double) ((ADC_read[10]*0.048828125 - 100) + OFF_IN)*GAIN_IN;  // I_n
    s.I_l = (double) ((ADC_read[0]*0.0244140625 - 50) + OFF_IL)*GAIN_IL;   // I_l
    s.V_l = (double) ((ADC_read[2]*0.1220703125 - 250) + OFF_VL)*GAIN_VL;   // V_l
    s.V_h = (double) ((ADC_read[1]*0.48828125 - 1000) + OFF_VH)*GAIN_VH;  // V_h
    s.I_c = (double) ((ADC_read[3]*0.048828125 - 100) + OFF_IC)*GAIN_IC;   // I_c
    s.V_c = (double) ((ADC_read[4]*0.244140625 - 500) + OFF_VC)*GAIN_VC;  // V_c
    s.I_b = (double) ((ADC_read[5]*0.048828125 - 100) + OFF_IB)*GAIN_IB;   // I_b
    s.V_b = (double) ((ADC_read[6]*0.244140625 - 500) + OFF_VB)*GAIN_VB;  // V_b
    s.I_a = (double) ((ADC_read[7]*0.048828125 - 100) + OFF_IA)*GAIN_IA;   // I_a
    s.V_a = (double) ((ADC_read[8]*0.244140625 - 500) + OFF_VA)*GAIN_VA;  // V_a
*/

#elif (DEVICE==11)           // TYPHOON Slot 2
    // For a second DSP that will be connected to typhoon
    s.I_h = (double) ((ADC_read[10]*0.0244140625 - 50) + OFF_IH)*GAIN_IH;   // I_h
    s.I_n = (double) ((ADC_read[9]*0.048828125 - 100) + OFF_IN)*GAIN_IN;  // I_n
    s.I_l = (double) ((ADC_read[8]*0.0244140625 - 50) + OFF_IL)*GAIN_IL;   // I_l
    s.V_l = (double) ((ADC_read[7]*0.1220703125 - 250) + OFF_VL)*GAIN_VL;   // V_l
    s.V_h = (double) ((ADC_read[6]*0.48828125 - 1000) + OFF_VH)*GAIN_VH;  // V_h
    s.I_c = (double) ((ADC_read[5]*0.048828125 - 100) + OFF_IC)*GAIN_IC;   // I_c
    s.V_c = (double) ((ADC_read[4]*0.244140625 - 500) + OFF_VC)*GAIN_VC;  // V_c
    s.I_b = (double) ((ADC_read[3]*0.048828125 - 100) + OFF_IB)*GAIN_IB;   // I_b
    s.V_b = (double) ((ADC_read[2]*0.244140625 - 500) + OFF_VB)*GAIN_VB;  // V_b
    s.I_a = (double) ((ADC_read[1]*0.048828125 - 100) + OFF_IA)*GAIN_IA;   // I_a
    s.V_a = (double) ((ADC_read[0]*0.244140625 - 500) + OFF_VA)*GAIN_VA;  // V_a

#endif

	/*s.I_l=s.I_l*0.025+0.975*i_l_ant;
	s.V_l=s.V_l*0.025+0.975*v_l_ant;
	s.I_h=s.I_h*0.025+0.975*i_h_ant;
	s.V_h=s.V_h*0.025+0.975*v_h_ant;

	i_l_ant=s.I_l;
	v_l_ant=s.V_l;
	i_h_ant=s.I_h;
	v_h_ant=s.V_h;*/

	return s;


}


