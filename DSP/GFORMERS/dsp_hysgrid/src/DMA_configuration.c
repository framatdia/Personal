#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "type_structs.h"

// DMA Configuration
void Setup_DMA(Uint16 *ADC_read, Uint16 *duties){
#if (DEVICE == 0 || DEVICE == 1 || DEVICE == 2 || DEVICE == 3 || DEVICE == 5 || DEVICE == 6 || DEVICE == 7 || DEVICE == 8 || DEVICE == 9 || DEVICE == 10 || DEVICE==11 || DEVICE==12)
	DMACH1AddrConfig(&ADC_read[0],&AdcMirror.ADCRESULT0);
	DMACH1BurstConfig(9,1,1);
	DMACH1TransferConfig(0,0,0);
	DMACH1WrapConfig(0,0,0,0);
	DMACH1ModeConfig(DMA_SEQ1INT,PERINT_ENABLE,ONESHOT_DISABLE,CONT_ENABLE,SYNC_DISABLE,SYNC_SRC,
	                 OVRFLOW_DISABLE,SIXTEEN_BIT,CHINT_END,CHINT_ENABLE);
#elif DEVICE == 4
	DMACH1AddrConfig(&ADC_read[0],&AdcMirror.ADCRESULT0);
	DMACH1BurstConfig(11,1,1);
	DMACH1TransferConfig(0,0,0);
	DMACH1WrapConfig(11,0,11,0);
	DMACH1ModeConfig(DMA_SEQ1INT,PERINT_ENABLE,ONESHOT_DISABLE,CONT_ENABLE,SYNC_DISABLE,SYNC_SRC,
	                 OVRFLOW_DISABLE,SIXTEEN_BIT,CHINT_END,CHINT_ENABLE);
#endif
	StartDMACH1();

	DMACH2AddrConfig(&EPwm1Regs.CMPA.half.CMPA,&duties[0]);
	DMACH2BurstConfig(3,1,64);
	DMACH2TransferConfig(0,0,0);
	DMACH2WrapConfig(3,0,3,0);
	DMACH2ModeConfig(DMA_SEQ2INT,PERINT_ENABLE,ONESHOT_DISABLE,CONT_ENABLE,SYNC_DISABLE,SYNC_SRC,
	                 OVRFLOW_DISABLE,SIXTEEN_BIT,CHINT_END,CHINT_ENABLE);
	StartDMACH2();
}
