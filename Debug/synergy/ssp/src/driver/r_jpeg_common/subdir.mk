################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../synergy/ssp/src/driver/r_jpeg_common/r_jpeg_common.c 

OBJS += \
./synergy/ssp/src/driver/r_jpeg_common/r_jpeg_common.o 

C_DEPS += \
./synergy/ssp/src/driver/r_jpeg_common/r_jpeg_common.d 


# Each subdirectory must supply rules for building sources it contributes
synergy/ssp/src/driver/r_jpeg_common/%.o: ../synergy/ssp/src/driver/r_jpeg_common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	C:\Renesas\e2_studio\Utilities\\/isdebuild arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -D_RENESAS_SYNERGY_ -I"C:\DSE\EQUIPO8\ProyectoIntegrador\src" -I"C:\DSE\EQUIPO8\ProyectoIntegrador\src\synergy_gen" -I"C:\DSE\EQUIPO8\ProyectoIntegrador\synergy_cfg\ssp_cfg\bsp" -I"C:\DSE\EQUIPO8\ProyectoIntegrador\synergy_cfg\ssp_cfg\driver" -I"C:\DSE\EQUIPO8\ProyectoIntegrador\synergy\ssp\inc" -I"C:\DSE\EQUIPO8\ProyectoIntegrador\synergy\ssp\inc\bsp" -I"C:\DSE\EQUIPO8\ProyectoIntegrador\synergy\ssp\inc\bsp\cmsis\Include" -I"C:\DSE\EQUIPO8\ProyectoIntegrador\synergy\ssp\inc\driver\api" -I"C:\DSE\EQUIPO8\ProyectoIntegrador\synergy\ssp\inc\driver\instances" -I"C:\DSE\EQUIPO8\ProyectoIntegrador\synergy_cfg\ssp_cfg\framework" -I"C:\DSE\EQUIPO8\ProyectoIntegrador\synergy\ssp\inc\framework\api" -I"C:\DSE\EQUIPO8\ProyectoIntegrador\synergy\ssp\inc\framework\instances" -I"C:\DSE\EQUIPO8\ProyectoIntegrador\synergy\ssp\inc\framework\tes" -I"C:\DSE\EQUIPO8\ProyectoIntegrador\synergy_cfg\ssp_cfg\framework\el" -I"C:\DSE\EQUIPO8\ProyectoIntegrador\synergy\ssp\inc\framework\el" -I"C:\DSE\EQUIPO8\ProyectoIntegrador\synergy\ssp\src\framework\el\tx" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '

