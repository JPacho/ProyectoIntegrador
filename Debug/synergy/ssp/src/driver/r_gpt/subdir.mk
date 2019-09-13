################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../synergy/ssp/src/driver/r_gpt/r_gpt.c 

OBJS += \
./synergy/ssp/src/driver/r_gpt/r_gpt.o 

C_DEPS += \
./synergy/ssp/src/driver/r_gpt/r_gpt.d 


# Each subdirectory must supply rules for building sources it contributes
synergy/ssp/src/driver/r_gpt/%.o: ../synergy/ssp/src/driver/r_gpt/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	C:\Renesas\e2_studio\Utilities\\/isdebuild arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -D_RENESAS_SYNERGY_ -I"C:\REP16082019\Proyecto_Integrador\src" -I"C:\REP16082019\Proyecto_Integrador\src\synergy_gen" -I"C:\REP16082019\Proyecto_Integrador\synergy_cfg\ssp_cfg\bsp" -I"C:\REP16082019\Proyecto_Integrador\synergy_cfg\ssp_cfg\driver" -I"C:\REP16082019\Proyecto_Integrador\synergy\ssp\inc" -I"C:\REP16082019\Proyecto_Integrador\synergy\ssp\inc\bsp" -I"C:\REP16082019\Proyecto_Integrador\synergy\ssp\inc\bsp\cmsis\Include" -I"C:\REP16082019\Proyecto_Integrador\synergy\ssp\inc\driver\api" -I"C:\REP16082019\Proyecto_Integrador\synergy\ssp\inc\driver\instances" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


