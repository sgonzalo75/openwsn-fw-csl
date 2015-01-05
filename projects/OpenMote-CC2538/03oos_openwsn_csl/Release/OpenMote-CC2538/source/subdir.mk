################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/adc.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/aes.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/ccm.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/cpu.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/debug.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/flash.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/gpio.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/gptimer.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/i2c.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/interrupt.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/ioc.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/pka.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/sha256.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/sleepmode.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/ssi.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/sys_ctrl.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/systick.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/uarthal.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/udma.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/watchdog.c 

OBJS += \
./OpenMote-CC2538/source/adc.o \
./OpenMote-CC2538/source/aes.o \
./OpenMote-CC2538/source/ccm.o \
./OpenMote-CC2538/source/cpu.o \
./OpenMote-CC2538/source/debug.o \
./OpenMote-CC2538/source/flash.o \
./OpenMote-CC2538/source/gpio.o \
./OpenMote-CC2538/source/gptimer.o \
./OpenMote-CC2538/source/i2c.o \
./OpenMote-CC2538/source/interrupt.o \
./OpenMote-CC2538/source/ioc.o \
./OpenMote-CC2538/source/pka.o \
./OpenMote-CC2538/source/sha256.o \
./OpenMote-CC2538/source/sleepmode.o \
./OpenMote-CC2538/source/ssi.o \
./OpenMote-CC2538/source/sys_ctrl.o \
./OpenMote-CC2538/source/systick.o \
./OpenMote-CC2538/source/uarthal.o \
./OpenMote-CC2538/source/udma.o \
./OpenMote-CC2538/source/watchdog.o 

C_DEPS += \
./OpenMote-CC2538/source/adc.d \
./OpenMote-CC2538/source/aes.d \
./OpenMote-CC2538/source/ccm.d \
./OpenMote-CC2538/source/cpu.d \
./OpenMote-CC2538/source/debug.d \
./OpenMote-CC2538/source/flash.d \
./OpenMote-CC2538/source/gpio.d \
./OpenMote-CC2538/source/gptimer.d \
./OpenMote-CC2538/source/i2c.d \
./OpenMote-CC2538/source/interrupt.d \
./OpenMote-CC2538/source/ioc.d \
./OpenMote-CC2538/source/pka.d \
./OpenMote-CC2538/source/sha256.d \
./OpenMote-CC2538/source/sleepmode.d \
./OpenMote-CC2538/source/ssi.d \
./OpenMote-CC2538/source/sys_ctrl.d \
./OpenMote-CC2538/source/systick.d \
./OpenMote-CC2538/source/uarthal.d \
./OpenMote-CC2538/source/udma.d \
./OpenMote-CC2538/source/watchdog.d 


# Each subdirectory must supply rules for building sources it contributes
OpenMote-CC2538/source/adc.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/adc.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/source/aes.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/aes.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/source/ccm.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/ccm.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/source/cpu.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/cpu.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/source/debug.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/debug.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/source/flash.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/flash.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/source/gpio.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/source/gptimer.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/gptimer.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/source/i2c.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/i2c.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/source/interrupt.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/interrupt.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/source/ioc.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/ioc.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/source/pka.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/pka.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/source/sha256.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/sha256.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/source/sleepmode.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/sleepmode.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/source/ssi.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/ssi.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/source/sys_ctrl.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/sys_ctrl.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/source/systick.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/systick.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/source/uarthal.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/uarthal.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/source/udma.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/udma.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

OpenMote-CC2538/source/watchdog.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/bsp/boards/OpenMote-CC2538/source/watchdog.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


