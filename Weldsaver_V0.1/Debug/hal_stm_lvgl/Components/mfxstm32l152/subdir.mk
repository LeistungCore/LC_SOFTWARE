################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../hal_stm_lvgl/Components/mfxstm32l152/mfxstm32l152.c 

OBJS += \
./hal_stm_lvgl/Components/mfxstm32l152/mfxstm32l152.o 

C_DEPS += \
./hal_stm_lvgl/Components/mfxstm32l152/mfxstm32l152.d 


# Each subdirectory must supply rules for building sources it contributes
hal_stm_lvgl/Components/mfxstm32l152/%.o hal_stm_lvgl/Components/mfxstm32l152/%.su hal_stm_lvgl/Components/mfxstm32l152/%.cyclo: ../hal_stm_lvgl/Components/mfxstm32l152/%.c hal_stm_lvgl/Components/mfxstm32l152/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"D:/stm32_projects/weld_saver_final/Weldsaver_V0.1" -I"D:/stm32_projects/weld_saver_final/Weldsaver_V0.1/hal_stm_lvgl/STM32746G-Discovery" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-hal_stm_lvgl-2f-Components-2f-mfxstm32l152

clean-hal_stm_lvgl-2f-Components-2f-mfxstm32l152:
	-$(RM) ./hal_stm_lvgl/Components/mfxstm32l152/mfxstm32l152.cyclo ./hal_stm_lvgl/Components/mfxstm32l152/mfxstm32l152.d ./hal_stm_lvgl/Components/mfxstm32l152/mfxstm32l152.o ./hal_stm_lvgl/Components/mfxstm32l152/mfxstm32l152.su

.PHONY: clean-hal_stm_lvgl-2f-Components-2f-mfxstm32l152

