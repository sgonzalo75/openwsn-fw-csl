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
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/bsp_timer.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/bsp_timer.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/debugpins.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/debugpins.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/eui64.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/eui64.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/i2c.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/i2c.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/leds.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/leds.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/radio.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/radio.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/radiotimer.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/radiotimer.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/startup_gcc.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/startup_gcc.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/uart.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/uart.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


