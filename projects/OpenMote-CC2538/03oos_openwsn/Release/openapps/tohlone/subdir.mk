################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/tohlone/tohlone.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/tohlone/tohlone_webpages.c 

OBJS += \
./openapps/tohlone/tohlone.o \
./openapps/tohlone/tohlone_webpages.o 

C_DEPS += \
./openapps/tohlone/tohlone.d \
./openapps/tohlone/tohlone_webpages.d 


# Each subdirectory must supply rules for building sources it contributes
openapps/tohlone/tohlone.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/tohlone/tohlone.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

openapps/tohlone/tohlone_webpages.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/tohlone/tohlone_webpages.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


