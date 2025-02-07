################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/others/sysmon/lv_sysmon.c 

OBJS += \
./lvgl/src/others/sysmon/lv_sysmon.o 

C_DEPS += \
./lvgl/src/others/sysmon/lv_sysmon.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/others/sysmon/%.o lvgl/src/others/sysmon/%.su lvgl/src/others/sysmon/%.cyclo: ../lvgl/src/others/sysmon/%.c lvgl/src/others/sysmon/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"D:/2/Projects/003_RGB_Mixer/2_32F746GDISCOVERY" -I"D:/2/Projects/003_RGB_Mixer/2_32F746GDISCOVERY/hal_stm_lvgl/STM32746G-Discovery" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-others-2f-sysmon

clean-lvgl-2f-src-2f-others-2f-sysmon:
	-$(RM) ./lvgl/src/others/sysmon/lv_sysmon.cyclo ./lvgl/src/others/sysmon/lv_sysmon.d ./lvgl/src/others/sysmon/lv_sysmon.o ./lvgl/src/others/sysmon/lv_sysmon.su

.PHONY: clean-lvgl-2f-src-2f-others-2f-sysmon

