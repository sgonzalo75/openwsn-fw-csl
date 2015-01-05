################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow/IEEE802154.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow/IEEE802154E.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow/adaptive_sync.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow/topology.c 

OBJS += \
./openstack/02a-MAClow/IEEE802154.o \
./openstack/02a-MAClow/IEEE802154E.o \
./openstack/02a-MAClow/adaptive_sync.o \
./openstack/02a-MAClow/topology.o 

C_DEPS += \
./openstack/02a-MAClow/IEEE802154.d \
./openstack/02a-MAClow/IEEE802154E.d \
./openstack/02a-MAClow/adaptive_sync.d \
./openstack/02a-MAClow/topology.d 


# Each subdirectory must supply rules for building sources it contributes
openstack/02a-MAClow/IEEE802154.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow/IEEE802154.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

openstack/02a-MAClow/IEEE802154E.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow/IEEE802154E.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

openstack/02a-MAClow/adaptive_sync.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow/adaptive_sync.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

openstack/02a-MAClow/topology.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow/topology.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


