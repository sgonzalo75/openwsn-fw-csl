################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include openstack/cross-layers/subdir.mk
-include openstack/04-TRAN/subdir.mk
-include openstack/03b-IPv6/subdir.mk
-include openstack/03a-IPHC/subdir.mk
-include openstack/02b-MAChigh/subdir.mk
-include openstack/02a-MAClow/subdir.mk
-include openstack/subdir.mk
-include openos/subdir.mk
-include openapps/uecho/subdir.mk
-include openapps/tohlone/subdir.mk
-include openapps/techo/subdir.mk
-include openapps/cwellknown/subdir.mk
-include openapps/cstorm/subdir.mk
-include openapps/cleds/subdir.mk
-include openapps/cinfo/subdir.mk
-include openapps/cexample/subdir.mk
-include openapps/c6t/subdir.mk
-include openapps/subdir.mk
-include common/subdir.mk
-include OpenMote-CC2538/source/subdir.mk
-include OpenMote-CC2538/subdir.mk
-include 03oos_openwsn/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
03oos_openwsn.hex \

SECONDARY_SIZE += \
03oos_openwsn.siz \


# All Target
all: 03oos_openwsn.elf secondary-outputs

# Tool invocations
03oos_openwsn.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross ARM C Linker'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g -Xlinker --gc-sections -Wl,-Map,"03oos_openwsn.map" -o "03oos_openwsn.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

03oos_openwsn.hex: 03oos_openwsn.elf
	@echo 'Invoking: Cross ARM GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex "03oos_openwsn.elf"  "03oos_openwsn.hex"
	@echo 'Finished building: $@'
	@echo ' '

03oos_openwsn.siz: 03oos_openwsn.elf
	@echo 'Invoking: Cross ARM GNU Print Size'
	arm-none-eabi-size --format=berkeley "03oos_openwsn.elf"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(S_UPPER_DEPS) 03oos_openwsn.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
