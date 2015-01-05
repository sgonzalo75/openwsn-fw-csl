################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/OpenMote-CC2538/adxl346.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/OpenMote-CC2538/max44009.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/OpenMote-CC2538/sht21.c 

OBJS += \
./drivers/adxl346.o \
./drivers/max44009.o \
./drivers/sht21.o 

C_DEPS += \
./drivers/adxl346.d \
./drivers/max44009.d \
./drivers/sht21.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/adxl346.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/OpenMote-CC2538/adxl346.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/max44009.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/OpenMote-CC2538/max44009.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/sht21.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/drivers/OpenMote-CC2538/sht21.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


