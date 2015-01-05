################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03a-IPHC/iphc.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03a-IPHC/openbridge.c 

OBJS += \
./openstack/03a-IPHC/iphc.o \
./openstack/03a-IPHC/openbridge.o 

C_DEPS += \
./openstack/03a-IPHC/iphc.d \
./openstack/03a-IPHC/openbridge.d 


# Each subdirectory must supply rules for building sources it contributes
openstack/03a-IPHC/iphc.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03a-IPHC/iphc.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

openstack/03a-IPHC/openbridge.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03a-IPHC/openbridge.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


