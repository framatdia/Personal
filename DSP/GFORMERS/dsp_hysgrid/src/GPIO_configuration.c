#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"

// GPIO Configuration
void Setup_GPIO(void)
{

#if (DEVICE == 1 || DEVICE == 2 || DEVICE == 3 || DEVICE==0) // EASY-RES PROTOTYPE

	EALLOW;
	// Phase a: ePWM3
	GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;
	// Phase b: ePWM4
	GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;
	// Phase c: ePWM1
	GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;
	// DC/DC:   ePWM2
	GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;
	// Enable/disable
	GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 0; // Se establece como GPIO
	GpioCtrlRegs.GPADIR.bit.GPIO29 = 1; // Se establece la GPIO como salida
	GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO19 = 1;
	GpioCtrlRegs.GPBMUX2.bit.GPIO63 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO63 = 1;
	GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO61 = 1;
	// Driver Faults
	GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO11 = 0;
	GpioCtrlRegs.GPBMUX2.bit.GPIO59 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO59 = 0;
	// Driver Reset
	GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;
	//Sync in/Sync out
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 2; // EPWMSYNCI (I)
    GpioCtrlRegs.GPBPUD.bit.GPIO32 = 1;
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 2; // EPWMSYNCO (O)
    GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;
	// Señal auxiliar para comprobar tiempo de ejecucion
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;
	EDIS;

#elif (DEVICE == 5 || DEVICE == 6 || DEVICE == 7 || DEVICE == 8 || DEVICE == 9 || DEVICE == 10 || DEVICE == 12) // ALLT

    EALLOW;
    // Phase a: ePWM3
    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;
    // Phase b: ePWM4
    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;
    // Phase c: ePWM1
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;
    // DC/DC:   ePWM2
    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;
    // Enable/disable
    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0; // Se establece como GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO27 = 1; // Se establece la GPIO como salida
    // Driver Faults
    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO20 = 0;
    // Driver Reset
    GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO23 = 1;
    //Sync in/Sync out
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 2; // EPWMSYNCI (I)
    GpioCtrlRegs.GPBPUD.bit.GPIO32 = 1;
    GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 2; // EPWMSYNCO (O)
    GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;
    EDIS;

#elif (DEVICE == 4 || DEVICE == 11 )		// TYPHOON

	EALLOW;
	// Phase a: ePWM3
	GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;
	// Phase b: ePWM4
	GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;
	// Phase c: ePWM1
	GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;
	// DC/DC:   ePWM2
	GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;
	GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;
	// Enable/disable
	GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 0;
	GpioCtrlRegs.GPADIR.bit.GPIO12 = 1;
	GpioCtrlRegs.GPBMUX2.bit.GPIO61 = 0;
	GpioCtrlRegs.GPBDIR.bit.GPIO61 = 1;
	EDIS;
	// Tiempo de ejecución
    GpioCtrlRegs.GPAMUX1.bit.GPIO14 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO14 = 1;

#endif
}

#pragma CODE_SECTION (enable_ePWM,"ramfuncs")
void enable_ePWM(int enableAC, int enableDC)
{

#if (DEVICE == 1 || DEVICE == 2 || DEVICE == 3 || DEVICE==0) // EASY-RES PROTOTYPE

	if (enableAC == 1)	{
		GpioDataRegs.GPASET.bit.GPIO29 = 1; // Enable fase A ON
		GpioDataRegs.GPASET.bit.GPIO19 = 1; // Enable fase B ON
		GpioDataRegs.GPBSET.bit.GPIO63 = 1; // Enable fase C ON
	}else{
		GpioDataRegs.GPACLEAR.bit.GPIO29 = 1; // Enable fase A OFF
		GpioDataRegs.GPACLEAR.bit.GPIO19 = 1; // Enable fase B OFF
		GpioDataRegs.GPBCLEAR.bit.GPIO63 = 1; // Enable fase C OFF
	}

	if (enableDC == 1)	{
		GpioDataRegs.GPBSET.bit.GPIO61 = 1; // Enable DC/DC ON
	}
	else{
		GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1; // Enable DC/DC OFF
	}

#elif (DEVICE == 4 || DEVICE == 11)		// TYPHOON

	if (enableAC == 1)	{
		GpioDataRegs.GPASET.bit.GPIO11 = 1;

		//GpioDataRegs.GPBSET.bit.GPIO61 = 1;
	}else{
		GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;
		//GpioDataRegs.GPBCLEAR.bit.GPIO61 = 1;
	}

	if (enableDC == 1)	{
		GpioDataRegs.GPASET.bit.GPIO10 = 1;
	}
	else{
		GpioDataRegs.GPACLEAR.bit.GPIO10 = 1;
	}

#elif (DEVICE == 5 || DEVICE == 6 || DEVICE == 7 || DEVICE == 8 || DEVICE == 9 || DEVICE == 10 || DEVICE == 12) // ALLT

    if (enableAC == 1)  {
        GpioDataRegs.GPASET.bit.GPIO27 = 1;
    }else{
        GpioDataRegs.GPACLEAR.bit.GPIO27 = 1;
    }

#endif
}

#pragma CODE_SECTION (reset_drivers,"ramfuncs")
void reset_drivers(int reset)


{
#if (DEVICE == 1 || DEVICE == 2 || DEVICE == 3 || DEVICE==0) // EASY-RES PROTOTYPE

	if (reset == 1){
		GpioDataRegs.GPASET.bit.GPIO10 = 1;
	}
	else{
		GpioDataRegs.GPACLEAR.bit.GPIO10 = 1;
	}

#elif (DEVICE == 5 || DEVICE == 6 || DEVICE == 7 || DEVICE == 8 || DEVICE == 9 || DEVICE == 10 || DEVICE == 12) // ALLT
	if (reset == 1){
	        GpioDataRegs.GPASET.bit.GPIO23 = 1;
	    }
	    else{
	        GpioDataRegs.GPACLEAR.bit.GPIO23 = 1;
	    }
#endif

}

