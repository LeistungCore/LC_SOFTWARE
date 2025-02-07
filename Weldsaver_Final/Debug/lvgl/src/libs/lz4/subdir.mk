################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/libs/lz4/lz4.c 

OBJS += \
./lvgl/src/libs/lz4/lz4.o 

C_DEPS += \
./lvgl/src/libs/lz4/lz4.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/libs/lz4/%.o lvgl/src/libs/lz4/%.su lvgl/src/libs/lz4/%.cyclo: ../lvgl/src/libs/lz4/%.c lvgl/src/libs/lz4/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"D:/2/Projects/003_RGB_Mixer/2_32F746GDISCOVERY" -I"D:/2/Projects/003_RGB_Mixer/2_32F746GDISCOVERY/hal_stm_lvgl/STM32746G-Discovery" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-libs-2f-lz4

clean-lvgl-2f-src-2f-libs-2f-lz4:
	-$(RM) ./lvgl/src/libs/lz4/lz4.cyclo ./lvgl/src/libs/lz4/lz4.d ./lvgl/src/libs/lz4/lz4.o ./lvgl/src/libs/lz4/lz4.su

.PHONY: clean-lvgl-2f-src-2f-libs-2f-lz4

