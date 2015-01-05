################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh/neighbors.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh/otf.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh/processIE.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh/schedule.c \
/home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh/sixtop.c 

OBJS += \
./openstack/02b-MAChigh/neighbors.o \
./openstack/02b-MAChigh/otf.o \
./openstack/02b-MAChigh/processIE.o \
./openstack/02b-MAChigh/schedule.o \
./openstack/02b-MAChigh/sixtop.o 

C_DEPS += \
./openstack/02b-MAChigh/neighbors.d \
./openstack/02b-MAChigh/otf.d \
./openstack/02b-MAChigh/processIE.d \
./openstack/02b-MAChigh/schedule.d \
./openstack/02b-MAChigh/sixtop.d 


# Each subdirectory must supply rules for building sources it contributes
openstack/02b-MAChigh/neighbors.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh/neighbors.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

openstack/02b-MAChigh/otf.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh/otf.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

openstack/02b-MAChigh/processIE.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh/processIE.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

openstack/02b-MAChigh/schedule.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh/schedule.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

openstack/02b-MAChigh/sixtop.o: /home/sgonzalos/TFM/openwsn-trunk/openwsn-fw/openstack/02b-MAChigh/sixtop.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


