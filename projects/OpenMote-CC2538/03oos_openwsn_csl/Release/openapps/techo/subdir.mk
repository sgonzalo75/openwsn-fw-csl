################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/techo/techo.c 

OBJS += \
./openapps/techo/techo.o 

C_DEPS += \
./openapps/techo/techo.d 


# Each subdirectory must supply rules for building sources it contributes
openapps/techo/techo.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/techo/techo.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


