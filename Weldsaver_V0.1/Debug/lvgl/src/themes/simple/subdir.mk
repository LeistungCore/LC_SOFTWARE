################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/themes/simple/lv_theme_simple.c 

OBJS += \
./lvgl/src/themes/simple/lv_theme_simple.o 

C_DEPS += \
./lvgl/src/themes/simple/lv_theme_simple.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/themes/simple/%.o lvgl/src/themes/simple/%.su lvgl/src/themes/simple/%.cyclo: ../lvgl/src/themes/simple/%.c lvgl/src/themes/simple/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"D:/2/Projects/003_RGB_Mixer/2_32F746GDISCOVERY" -I"D:/2/Projects/003_RGB_Mixer/2_32F746GDISCOVERY/hal_stm_lvgl/STM32746G-Discovery" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-themes-2f-simple

clean-lvgl-2f-src-2f-themes-2f-simple:
	-$(RM) ./lvgl/src/themes/simple/lv_theme_simple.cyclo ./lvgl/src/themes/simple/lv_theme_simple.d ./lvgl/src/themes/simple/lv_theme_simple.o ./lvgl/src/themes/simple/lv_theme_simple.su

.PHONY: clean-lvgl-2f-src-2f-themes-2f-simple

