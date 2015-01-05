################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03b-IPv6/forwarding.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03b-IPv6/icmpv6.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03b-IPv6/icmpv6echo.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03b-IPv6/icmpv6rpl.c 

OBJS += \
./openstack/03b-IPv6/forwarding.o \
./openstack/03b-IPv6/icmpv6.o \
./openstack/03b-IPv6/icmpv6echo.o \
./openstack/03b-IPv6/icmpv6rpl.o 

C_DEPS += \
./openstack/03b-IPv6/forwarding.d \
./openstack/03b-IPv6/icmpv6.d \
./openstack/03b-IPv6/icmpv6echo.d \
./openstack/03b-IPv6/icmpv6rpl.d 


# Each subdirectory must supply rules for building sources it contributes
openstack/03b-IPv6/forwarding.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03b-IPv6/forwarding.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

openstack/03b-IPv6/icmpv6.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03b-IPv6/icmpv6.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

openstack/03b-IPv6/icmpv6echo.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03b-IPv6/icmpv6echo.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

openstack/03b-IPv6/icmpv6rpl.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03b-IPv6/icmpv6rpl.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


