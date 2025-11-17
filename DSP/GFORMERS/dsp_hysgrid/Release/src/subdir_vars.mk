################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../src/DSP2833x_Headers_nonBIOS.cmd 

ASM_SRCS += \
../src/DSP2833x_ADC_cal.asm \
../src/DSP2833x_CodeStartBranch.asm \
../src/DSP2833x_usDelay.asm 

C_SRCS += \
../src/ADC_configuration.c \
../src/CTRL1.c \
../src/CTRL1_DCDC.c \
../src/CTRL1_PQ.c \
../src/CTRL1_alpha_beta.c \
../src/CTRL2.c \
../src/CTRL2_DCDC.c \
../src/CTRL3.c \
../src/CTRL3_DCDC.c \
../src/DMA_configuration.c \
../src/DSP2833x_Adc.c \
../src/DSP2833x_CpuTimers.c \
../src/DSP2833x_DMA.c \
../src/DSP2833x_DefaultIsr.c \
../src/DSP2833x_ECan.c \
../src/DSP2833x_GlobalVariableDefs.c \
../src/DSP2833x_Gpio.c \
../src/DSP2833x_PieCtrl.c \
../src/DSP2833x_PieVect.c \
../src/DSP2833x_SysCtrl.c \
../src/GPIO_configuration.c \
../src/OPEN_LOOP.c \
../src/PLL_Park_transformations.c \
../src/STATCOM.c \
../src/State_machine.c \
../src/calculations.c \
../src/eCAN_Configuration.c \
../src/ePWM_configuration.c \
../src/main.c \
../src/swing.c 

C_DEPS += \
./src/ADC_configuration.d \
./src/CTRL1.d \
./src/CTRL1_DCDC.d \
./src/CTRL1_PQ.d \
./src/CTRL1_alpha_beta.d \
./src/CTRL2.d \
./src/CTRL2_DCDC.d \
./src/CTRL3.d \
./src/CTRL3_DCDC.d \
./src/DMA_configuration.d \
./src/DSP2833x_Adc.d \
./src/DSP2833x_CpuTimers.d \
./src/DSP2833x_DMA.d \
./src/DSP2833x_DefaultIsr.d \
./src/DSP2833x_ECan.d \
./src/DSP2833x_GlobalVariableDefs.d \
./src/DSP2833x_Gpio.d \
./src/DSP2833x_PieCtrl.d \
./src/DSP2833x_PieVect.d \
./src/DSP2833x_SysCtrl.d \
./src/GPIO_configuration.d \
./src/OPEN_LOOP.d \
./src/PLL_Park_transformations.d \
./src/STATCOM.d \
./src/State_machine.d \
./src/calculations.d \
./src/eCAN_Configuration.d \
./src/ePWM_configuration.d \
./src/main.d \
./src/swing.d 

OBJS += \
./src/ADC_configuration.obj \
./src/CTRL1.obj \
./src/CTRL1_DCDC.obj \
./src/CTRL1_PQ.obj \
./src/CTRL1_alpha_beta.obj \
./src/CTRL2.obj \
./src/CTRL2_DCDC.obj \
./src/CTRL3.obj \
./src/CTRL3_DCDC.obj \
./src/DMA_configuration.obj \
./src/DSP2833x_ADC_cal.obj \
./src/DSP2833x_Adc.obj \
./src/DSP2833x_CodeStartBranch.obj \
./src/DSP2833x_CpuTimers.obj \
./src/DSP2833x_DMA.obj \
./src/DSP2833x_DefaultIsr.obj \
./src/DSP2833x_ECan.obj \
./src/DSP2833x_GlobalVariableDefs.obj \
./src/DSP2833x_Gpio.obj \
./src/DSP2833x_PieCtrl.obj \
./src/DSP2833x_PieVect.obj \
./src/DSP2833x_SysCtrl.obj \
./src/DSP2833x_usDelay.obj \
./src/GPIO_configuration.obj \
./src/OPEN_LOOP.obj \
./src/PLL_Park_transformations.obj \
./src/STATCOM.obj \
./src/State_machine.obj \
./src/calculations.obj \
./src/eCAN_Configuration.obj \
./src/ePWM_configuration.obj \
./src/main.obj \
./src/swing.obj 

ASM_DEPS += \
./src/DSP2833x_ADC_cal.d \
./src/DSP2833x_CodeStartBranch.d \
./src/DSP2833x_usDelay.d 

OBJS__QUOTED += \
"src\ADC_configuration.obj" \
"src\CTRL1.obj" \
"src\CTRL1_DCDC.obj" \
"src\CTRL1_PQ.obj" \
"src\CTRL1_alpha_beta.obj" \
"src\CTRL2.obj" \
"src\CTRL2_DCDC.obj" \
"src\CTRL3.obj" \
"src\CTRL3_DCDC.obj" \
"src\DMA_configuration.obj" \
"src\DSP2833x_ADC_cal.obj" \
"src\DSP2833x_Adc.obj" \
"src\DSP2833x_CodeStartBranch.obj" \
"src\DSP2833x_CpuTimers.obj" \
"src\DSP2833x_DMA.obj" \
"src\DSP2833x_DefaultIsr.obj" \
"src\DSP2833x_ECan.obj" \
"src\DSP2833x_GlobalVariableDefs.obj" \
"src\DSP2833x_Gpio.obj" \
"src\DSP2833x_PieCtrl.obj" \
"src\DSP2833x_PieVect.obj" \
"src\DSP2833x_SysCtrl.obj" \
"src\DSP2833x_usDelay.obj" \
"src\GPIO_configuration.obj" \
"src\OPEN_LOOP.obj" \
"src\PLL_Park_transformations.obj" \
"src\STATCOM.obj" \
"src\State_machine.obj" \
"src\calculations.obj" \
"src\eCAN_Configuration.obj" \
"src\ePWM_configuration.obj" \
"src\main.obj" \
"src\swing.obj" 

C_DEPS__QUOTED += \
"src\ADC_configuration.d" \
"src\CTRL1.d" \
"src\CTRL1_DCDC.d" \
"src\CTRL1_PQ.d" \
"src\CTRL1_alpha_beta.d" \
"src\CTRL2.d" \
"src\CTRL2_DCDC.d" \
"src\CTRL3.d" \
"src\CTRL3_DCDC.d" \
"src\DMA_configuration.d" \
"src\DSP2833x_Adc.d" \
"src\DSP2833x_CpuTimers.d" \
"src\DSP2833x_DMA.d" \
"src\DSP2833x_DefaultIsr.d" \
"src\DSP2833x_ECan.d" \
"src\DSP2833x_GlobalVariableDefs.d" \
"src\DSP2833x_Gpio.d" \
"src\DSP2833x_PieCtrl.d" \
"src\DSP2833x_PieVect.d" \
"src\DSP2833x_SysCtrl.d" \
"src\GPIO_configuration.d" \
"src\OPEN_LOOP.d" \
"src\PLL_Park_transformations.d" \
"src\STATCOM.d" \
"src\State_machine.d" \
"src\calculations.d" \
"src\eCAN_Configuration.d" \
"src\ePWM_configuration.d" \
"src\main.d" \
"src\swing.d" 

ASM_DEPS__QUOTED += \
"src\DSP2833x_ADC_cal.d" \
"src\DSP2833x_CodeStartBranch.d" \
"src\DSP2833x_usDelay.d" 

C_SRCS__QUOTED += \
"../src/ADC_configuration.c" \
"../src/CTRL1.c" \
"../src/CTRL1_DCDC.c" \
"../src/CTRL1_PQ.c" \
"../src/CTRL1_alpha_beta.c" \
"../src/CTRL2.c" \
"../src/CTRL2_DCDC.c" \
"../src/CTRL3.c" \
"../src/CTRL3_DCDC.c" \
"../src/DMA_configuration.c" \
"../src/DSP2833x_Adc.c" \
"../src/DSP2833x_CpuTimers.c" \
"../src/DSP2833x_DMA.c" \
"../src/DSP2833x_DefaultIsr.c" \
"../src/DSP2833x_ECan.c" \
"../src/DSP2833x_GlobalVariableDefs.c" \
"../src/DSP2833x_Gpio.c" \
"../src/DSP2833x_PieCtrl.c" \
"../src/DSP2833x_PieVect.c" \
"../src/DSP2833x_SysCtrl.c" \
"../src/GPIO_configuration.c" \
"../src/OPEN_LOOP.c" \
"../src/PLL_Park_transformations.c" \
"../src/STATCOM.c" \
"../src/State_machine.c" \
"../src/calculations.c" \
"../src/eCAN_Configuration.c" \
"../src/ePWM_configuration.c" \
"../src/main.c" \
"../src/swing.c" 

ASM_SRCS__QUOTED += \
"../src/DSP2833x_ADC_cal.asm" \
"../src/DSP2833x_CodeStartBranch.asm" \
"../src/DSP2833x_usDelay.asm" 


