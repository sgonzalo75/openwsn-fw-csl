################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/board.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/bsp_timer.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/debugpins.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/eui64.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/i2c.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/leds.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/radio.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/radiotimer.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/startup_gcc.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/uart.c 

OBJS += \
./OpenMote-CC2538/board.o \
./OpenMote-CC2538/bsp_timer.o \
./OpenMote-CC2538/debugpins.o \
./OpenMote-CC2538/eui64.o \
./OpenMote-CC2538/i2c.o \
./OpenMote-CC2538/leds.o \
./OpenMote-CC2538/radio.o \
./OpenMote-CC2538/radiotimer.o \
./OpenMote-CC2538/startup_gcc.o \
./OpenMote-CC2538/uart.o 

C_DEPS += \
./OpenMote-CC2538/board.d \
./OpenMote-CC2538/bsp_timer.d \
./OpenMote-CC2538/debugpins.d \
./OpenMote-CC2538/eui64.d \
./OpenMote-CC2538/i2c.d \
./OpenMote-CC2538/leds.d \
./OpenMote-CC2538/radio.d \
./OpenMote-CC2538/radiotimer.d \
./OpenMote-CC2538/startup_gcc.d \
./OpenMote-CC2538/uart.d 


# Each subdirectory must supply rules for building sources it contributes
OpenMote-CC2538/board.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/board.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/headers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/cross-layers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/common" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/kernel/openos" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/cc2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03a-IPHC" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03b-IPv6" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/04-TRAN" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cexample" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cinfo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/c6t" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/tohlone" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cleds" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cstorm" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cwellknown" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/techo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/uecho" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/bsp_timer.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/bsp_timer.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/headers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/cross-layers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/common" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/kernel/openos" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/cc2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03a-IPHC" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03b-IPv6" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/04-TRAN" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cexample" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cinfo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/c6t" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/tohlone" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cleds" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cstorm" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cwellknown" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/techo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/uecho" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/debugpins.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/debugpins.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/headers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/cross-layers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/common" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/kernel/openos" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/cc2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03a-IPHC" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03b-IPv6" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/04-TRAN" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cexample" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cinfo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/c6t" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/tohlone" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cleds" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cstorm" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cwellknown" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/techo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/uecho" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/eui64.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/eui64.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/headers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/cross-layers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/common" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/kernel/openos" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/cc2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03a-IPHC" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03b-IPv6" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/04-TRAN" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cexample" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cinfo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/c6t" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/tohlone" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cleds" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cstorm" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cwellknown" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/techo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/uecho" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/i2c.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/i2c.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/headers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/cross-layers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/common" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/kernel/openos" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/cc2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03a-IPHC" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03b-IPv6" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/04-TRAN" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cexample" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cinfo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/c6t" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/tohlone" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cleds" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cstorm" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cwellknown" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/techo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/uecho" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/leds.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/leds.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/headers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/cross-layers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/common" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/kernel/openos" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/cc2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03a-IPHC" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03b-IPv6" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/04-TRAN" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cexample" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cinfo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/c6t" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/tohlone" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cleds" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cstorm" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cwellknown" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/techo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/uecho" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/radio.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/radio.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/headers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/cross-layers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/common" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/kernel/openos" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/cc2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03a-IPHC" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03b-IPv6" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/04-TRAN" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cexample" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cinfo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/c6t" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/tohlone" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cleds" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cstorm" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cwellknown" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/techo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/uecho" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/radiotimer.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/radiotimer.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/headers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/cross-layers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/common" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/kernel/openos" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/cc2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03a-IPHC" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03b-IPv6" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/04-TRAN" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cexample" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cinfo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/c6t" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/tohlone" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cleds" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cstorm" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cwellknown" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/techo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/uecho" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/startup_gcc.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/startup_gcc.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/headers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/cross-layers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/common" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/kernel/openos" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/cc2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03a-IPHC" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03b-IPv6" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/04-TRAN" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cexample" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cinfo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/c6t" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/tohlone" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cleds" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cstorm" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cwellknown" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/techo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/uecho" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/uart.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/uart.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/headers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/cross-layers" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/common" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/kernel/openos" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/cc2538" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02a-MAClow" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03a-IPHC" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/03b-IPv6" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/04-TRAN" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cexample" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cinfo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/c6t" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/tohlone" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cleds" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cstorm" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/cwellknown" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/techo" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openapps/uecho" -I"/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/inc" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


