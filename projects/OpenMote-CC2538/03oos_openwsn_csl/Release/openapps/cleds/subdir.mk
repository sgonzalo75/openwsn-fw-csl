################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cleds/cleds.c 

OBJS += \
./openapps/cleds/cleds.o 

C_DEPS += \
./openapps/cleds/cleds.d 


# Each subdirectory must supply rules for building sources it contributes
openapps/cleds/cleds.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cleds/cleds.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


