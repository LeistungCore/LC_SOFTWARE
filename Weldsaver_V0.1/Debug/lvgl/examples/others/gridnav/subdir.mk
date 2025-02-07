################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/examples/others/gridnav/lv_example_gridnav_1.c \
../lvgl/examples/others/gridnav/lv_example_gridnav_2.c \
../lvgl/examples/others/gridnav/lv_example_gridnav_3.c \
../lvgl/examples/others/gridnav/lv_example_gridnav_4.c 

OBJS += \
./lvgl/examples/others/gridnav/lv_example_gridnav_1.o \
./lvgl/examples/others/gridnav/lv_example_gridnav_2.o \
./lvgl/examples/others/gridnav/lv_example_gridnav_3.o \
./lvgl/examples/others/gridnav/lv_example_gridnav_4.o 

C_DEPS += \
./lvgl/examples/others/gridnav/lv_example_gridnav_1.d \
./lvgl/examples/others/gridnav/lv_example_gridnav_2.d \
./lvgl/examples/others/gridnav/lv_example_gridnav_3.d \
./lvgl/examples/others/gridnav/lv_example_gridnav_4.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/examples/others/gridnav/%.o lvgl/examples/others/gridnav/%.su lvgl/examples/others/gridnav/%.cyclo: ../lvgl/examples/others/gridnav/%.c lvgl/examples/others/gridnav/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"D:/stm32_projects/weld_saver_final/Weldsaver_V0.1" -I"D:/stm32_projects/weld_saver_final/Weldsaver_V0.1/hal_stm_lvgl/STM32746G-Discovery" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-examples-2f-others-2f-gridnav

clean-lvgl-2f-examples-2f-others-2f-gridnav:
	-$(RM) ./lvgl/examples/others/gridnav/lv_example_gridnav_1.cyclo ./lvgl/examples/others/gridnav/lv_example_gridnav_1.d ./lvgl/examples/others/gridnav/lv_example_gridnav_1.o ./lvgl/examples/others/gridnav/lv_example_gridnav_1.su ./lvgl/examples/others/gridnav/lv_example_gridnav_2.cyclo ./lvgl/examples/others/gridnav/lv_example_gridnav_2.d ./lvgl/examples/others/gridnav/lv_example_gridnav_2.o ./lvgl/examples/others/gridnav/lv_example_gridnav_2.su ./lvgl/examples/others/gridnav/lv_example_gridnav_3.cyclo ./lvgl/examples/others/gridnav/lv_example_gridnav_3.d ./lvgl/examples/others/gridnav/lv_example_gridnav_3.o ./lvgl/examples/others/gridnav/lv_example_gridnav_3.su ./lvgl/examples/others/gridnav/lv_example_gridnav_4.cyclo ./lvgl/examples/others/gridnav/lv_example_gridnav_4.d ./lvgl/examples/others/gridnav/lv_example_gridnav_4.o ./lvgl/examples/others/gridnav/lv_example_gridnav_4.su

.PHONY: clean-lvgl-2f-examples-2f-others-2f-gridnav

