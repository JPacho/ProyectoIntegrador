################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../synergy/ssp/src/bsp/cmsis/Device/RENESAS/S7G2/Source/startup_S7G2.c \
../synergy/ssp/src/bsp/cmsis/Device/RENESAS/S7G2/Source/system_S7G2.c 

OBJS += \
./synergy/ssp/src/bsp/cmsis/Device/RENESAS/S7G2/Source/startup_S7G2.o \
./synergy/ssp/src/bsp/cmsis/Device/RENESAS/S7G2/Source/system_S7G2.o 

C_DEPS += \
./synergy/ssp/src/bsp/cmsis/Device/RENESAS/S7G2/Source/startup_S7G2.d \
./synergy/ssp/src/bsp/cmsis/Device/RENESAS/S7G2/Source/system_S7G2.d 


# Each subdirectory must supply rules for building sources it contributes
synergy/ssp/src/bsp/cmsis/Device/RENESAS/S7G2/Source/%.o: ../synergy/ssp/src/bsp/cmsis/Device/RENESAS/S7G2/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	C:\Renesas\e2_studio\Utilities\\/isdebuild arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -D_RENESAS_SYNERGY_ -I"C:\REP16082019\IOs\src" -I"C:\REP16082019\IOs\src\synergy_gen" -I"C:\REP16082019\IOs\synergy_cfg\ssp_cfg\bsp" -I"C:\REP16082019\IOs\synergy_cfg\ssp_cfg\driver" -I"C:\REP16082019\IOs\synergy\ssp\inc" -I"C:\REP16082019\IOs\synergy\ssp\inc\bsp" -I"C:\REP16082019\IOs\synergy\ssp\inc\bsp\cmsis\Include" -I"C:\REP16082019\IOs\synergy\ssp\inc\driver\api" -I"C:\REP16082019\IOs\synergy\ssp\inc\driver\instances" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


