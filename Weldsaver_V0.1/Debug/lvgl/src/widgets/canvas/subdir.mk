################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/widgets/canvas/lv_canvas.c 

OBJS += \
./lvgl/src/widgets/canvas/lv_canvas.o 

C_DEPS += \
./lvgl/src/widgets/canvas/lv_canvas.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/widgets/canvas/%.o lvgl/src/widgets/canvas/%.su lvgl/src/widgets/canvas/%.cyclo: ../lvgl/src/widgets/canvas/%.c lvgl/src/widgets/canvas/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"D:/stm32_projects/weld_saver_final/Weldsaver_V0.1" -I"D:/stm32_projects/weld_saver_final/Weldsaver_V0.1/hal_stm_lvgl/STM32746G-Discovery" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-widgets-2f-canvas

clean-lvgl-2f-src-2f-widgets-2f-canvas:
	-$(RM) ./lvgl/src/widgets/canvas/lv_canvas.cyclo ./lvgl/src/widgets/canvas/lv_canvas.d ./lvgl/src/widgets/canvas/lv_canvas.o ./lvgl/src/widgets/canvas/lv_canvas.su

.PHONY: clean-lvgl-2f-src-2f-widgets-2f-canvas

