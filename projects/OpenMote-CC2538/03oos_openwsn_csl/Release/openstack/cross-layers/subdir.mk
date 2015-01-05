################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/cross-layers/idmanager.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/cross-layers/openqueue.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/cross-layers/openrandom.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/cross-layers/packetfunctions.c 

OBJS += \
./openstack/cross-layers/idmanager.o \
./openstack/cross-layers/openqueue.o \
./openstack/cross-layers/openrandom.o \
./openstack/cross-layers/packetfunctions.o 

C_DEPS += \
./openstack/cross-layers/idmanager.d \
./openstack/cross-layers/openqueue.d \
./openstack/cross-layers/openrandom.d \
./openstack/cross-layers/packetfunctions.d 


# Each subdirectory must supply rules for building sources it contributes
openstack/cross-layers/idmanager.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/cross-layers/idmanager.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

openstack/cross-layers/openqueue.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/cross-layers/openqueue.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

openstack/cross-layers/openrandom.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/cross-layers/openrandom.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

openstack/cross-layers/packetfunctions.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/cross-layers/packetfunctions.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


