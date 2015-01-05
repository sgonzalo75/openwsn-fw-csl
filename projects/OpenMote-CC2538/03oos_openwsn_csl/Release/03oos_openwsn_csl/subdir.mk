################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/projects/common/03oos_openwsn_csl/03oos_openwsn_csl.c 

OBJS += \
./03oos_openwsn_csl/03oos_openwsn_csl.o 

C_DEPS += \
./03oos_openwsn_csl/03oos_openwsn_csl.d 


# Each subdirectory must supply rules for building sources it contributes
03oos_openwsn_csl/03oos_openwsn_csl.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/projects/common/03oos_openwsn_csl/03oos_openwsn_csl.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


