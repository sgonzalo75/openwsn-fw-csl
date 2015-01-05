################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/common/openhdlc.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/common/openserial.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/common/opentimers.c 

OBJS += \
./common/openhdlc.o \
./common/openserial.o \
./common/opentimers.o 

C_DEPS += \
./common/openhdlc.d \
./common/openserial.d \
./common/opentimers.d 


# Each subdirectory must supply rules for building sources it contributes
common/openhdlc.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/common/openhdlc.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

common/openserial.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/common/openserial.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

common/opentimers.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/common/opentimers.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


