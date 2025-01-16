################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/themes/default/lv_theme_default.c 

OBJS += \
./lvgl/src/themes/default/lv_theme_default.o 

C_DEPS += \
./lvgl/src/themes/default/lv_theme_default.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/themes/default/%.o lvgl/src/themes/default/%.su lvgl/src/themes/default/%.cyclo: ../lvgl/src/themes/default/%.c lvgl/src/themes/default/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"D:/stm32_projects/weld_saver_final/Weldsaver_V3" -I"D:/stm32_projects/weld_saver_final/Weldsaver_V3/hal_stm_lvgl/STM32746G-Discovery" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-themes-2f-default

clean-lvgl-2f-src-2f-themes-2f-default:
	-$(RM) ./lvgl/src/themes/default/lv_theme_default.cyclo ./lvgl/src/themes/default/lv_theme_default.d ./lvgl/src/themes/default/lv_theme_default.o ./lvgl/src/themes/default/lv_theme_default.su

.PHONY: clean-lvgl-2f-src-2f-themes-2f-default

