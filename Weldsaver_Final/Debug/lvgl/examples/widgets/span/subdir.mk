################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/examples/widgets/span/lv_example_span_1.c 

OBJS += \
./lvgl/examples/widgets/span/lv_example_span_1.o 

C_DEPS += \
./lvgl/examples/widgets/span/lv_example_span_1.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/examples/widgets/span/%.o lvgl/examples/widgets/span/%.su lvgl/examples/widgets/span/%.cyclo: ../lvgl/examples/widgets/span/%.c lvgl/examples/widgets/span/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"D:/stm32_projects/weld_saver_final/Weldsaver_Final" -I"D:/stm32_projects/weld_saver_final/Weldsaver_Final/hal_stm_lvgl/STM32746G-Discovery" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-examples-2f-widgets-2f-span

clean-lvgl-2f-examples-2f-widgets-2f-span:
	-$(RM) ./lvgl/examples/widgets/span/lv_example_span_1.cyclo ./lvgl/examples/widgets/span/lv_example_span_1.d ./lvgl/examples/widgets/span/lv_example_span_1.o ./lvgl/examples/widgets/span/lv_example_span_1.su

.PHONY: clean-lvgl-2f-examples-2f-widgets-2f-span

