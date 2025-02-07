################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/examples/libs/rlottie/lv_example_rlottie_1.c \
../lvgl/examples/libs/rlottie/lv_example_rlottie_2.c \
../lvgl/examples/libs/rlottie/lv_example_rlottie_approve.c 

OBJS += \
./lvgl/examples/libs/rlottie/lv_example_rlottie_1.o \
./lvgl/examples/libs/rlottie/lv_example_rlottie_2.o \
./lvgl/examples/libs/rlottie/lv_example_rlottie_approve.o 

C_DEPS += \
./lvgl/examples/libs/rlottie/lv_example_rlottie_1.d \
./lvgl/examples/libs/rlottie/lv_example_rlottie_2.d \
./lvgl/examples/libs/rlottie/lv_example_rlottie_approve.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/examples/libs/rlottie/%.o lvgl/examples/libs/rlottie/%.su lvgl/examples/libs/rlottie/%.cyclo: ../lvgl/examples/libs/rlottie/%.c lvgl/examples/libs/rlottie/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"D:/stm32_projects/weld_saver_final/Weldsaver_V0.1" -I"D:/stm32_projects/weld_saver_final/Weldsaver_V0.1/hal_stm_lvgl/STM32746G-Discovery" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-examples-2f-libs-2f-rlottie

clean-lvgl-2f-examples-2f-libs-2f-rlottie:
	-$(RM) ./lvgl/examples/libs/rlottie/lv_example_rlottie_1.cyclo ./lvgl/examples/libs/rlottie/lv_example_rlottie_1.d ./lvgl/examples/libs/rlottie/lv_example_rlottie_1.o ./lvgl/examples/libs/rlottie/lv_example_rlottie_1.su ./lvgl/examples/libs/rlottie/lv_example_rlottie_2.cyclo ./lvgl/examples/libs/rlottie/lv_example_rlottie_2.d ./lvgl/examples/libs/rlottie/lv_example_rlottie_2.o ./lvgl/examples/libs/rlottie/lv_example_rlottie_2.su ./lvgl/examples/libs/rlottie/lv_example_rlottie_approve.cyclo ./lvgl/examples/libs/rlottie/lv_example_rlottie_approve.d ./lvgl/examples/libs/rlottie/lv_example_rlottie_approve.o ./lvgl/examples/libs/rlottie/lv_example_rlottie_approve.su

.PHONY: clean-lvgl-2f-examples-2f-libs-2f-rlottie

