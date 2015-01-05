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
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/headers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/cross-layers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/common" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/kernel/openos" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/cc2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03a-IPHC" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03b-IPv6" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/04-TRAN" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cexample" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cinfo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/c6t" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/tohlone" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cleds" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cstorm" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cwellknown" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/techo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/uecho" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

openstack/02a-MAClow/IEEE802154E.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow/IEEE802154E.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/headers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/cross-layers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/common" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/kernel/openos" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/cc2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03a-IPHC" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03b-IPv6" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/04-TRAN" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cexample" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cinfo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/c6t" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/tohlone" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cleds" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cstorm" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cwellknown" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/techo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/uecho" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

openstack/02a-MAClow/adaptive_sync.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow/adaptive_sync.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/headers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/cross-layers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/common" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/kernel/openos" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/cc2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03a-IPHC" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03b-IPv6" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/04-TRAN" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cexample" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cinfo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/c6t" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/tohlone" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cleds" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cstorm" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cwellknown" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/techo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/uecho" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

openstack/02a-MAClow/topology.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow/topology.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/headers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/cross-layers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/common" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/kernel/openos" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/cc2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03a-IPHC" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03b-IPv6" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/04-TRAN" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cexample" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cinfo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/c6t" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/tohlone" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cleds" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cstorm" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cwellknown" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/techo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/uecho" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

