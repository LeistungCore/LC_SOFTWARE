################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_1.c \
../lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_2.c \
../lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_3.c 

OBJS += \
./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_1.o \
./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_2.o \
./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_3.o 

C_DEPS += \
./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_1.d \
./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_2.d \
./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_3.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/examples/widgets/btnmatrix/%.o lvgl/examples/widgets/btnmatrix/%.su lvgl/examples/widgets/btnmatrix/%.cyclo: ../lvgl/examples/widgets/btnmatrix/%.c lvgl/examples/widgets/btnmatrix/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"D:/stm32_projects/weld_saver_final/Weldsaver_V0.1" -I"D:/stm32_projects/weld_saver_final/Weldsaver_V0.1/hal_stm_lvgl/STM32746G-Discovery" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-examples-2f-widgets-2f-btnmatrix

clean-lvgl-2f-examples-2f-widgets-2f-btnmatrix:
	-$(RM) ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_1.cyclo ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_1.d ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_1.o ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_1.su ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_2.cyclo ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_2.d ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_2.o ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_2.su ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_3.cyclo ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_3.d ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_3.o ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_3.su

.PHONY: clean-lvgl-2f-examples-2f-widgets-2f-btnmatrix

