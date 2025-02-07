################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/others/gridnav/lv_gridnav.c 

OBJS += \
./lvgl/src/others/gridnav/lv_gridnav.o 

C_DEPS += \
./lvgl/src/others/gridnav/lv_gridnav.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/others/gridnav/%.o lvgl/src/others/gridnav/%.su lvgl/src/others/gridnav/%.cyclo: ../lvgl/src/others/gridnav/%.c lvgl/src/others/gridnav/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"D:/stm32_projects/weld_saver_final/Weldsaver_Final" -I"D:/stm32_projects/weld_saver_final/Weldsaver_Final/hal_stm_lvgl/STM32746G-Discovery" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-others-2f-gridnav

clean-lvgl-2f-src-2f-others-2f-gridnav:
	-$(RM) ./lvgl/src/others/gridnav/lv_gridnav.cyclo ./lvgl/src/others/gridnav/lv_gridnav.d ./lvgl/src/others/gridnav/lv_gridnav.o ./lvgl/src/others/gridnav/lv_gridnav.su

.PHONY: clean-lvgl-2f-src-2f-others-2f-gridnav

