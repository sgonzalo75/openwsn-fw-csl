################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/04-TRAN/opencoap.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/04-TRAN/opentcp.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/04-TRAN/openudp.c 

OBJS += \
./openstack/04-TRAN/opencoap.o \
./openstack/04-TRAN/opentcp.o \
./openstack/04-TRAN/openudp.o 

C_DEPS += \
./openstack/04-TRAN/opencoap.d \
./openstack/04-TRAN/opentcp.d \
./openstack/04-TRAN/openudp.d 


# Each subdirectory must supply rules for building sources it contributes
openstack/04-TRAN/opencoap.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/04-TRAN/opencoap.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

openstack/04-TRAN/opentcp.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/04-TRAN/opentcp.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

openstack/04-TRAN/openudp.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/04-TRAN/openudp.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


