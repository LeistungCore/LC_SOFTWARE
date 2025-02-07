################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/examples/assets/emoji/img_emoji_F617.c 

OBJS += \
./lvgl/examples/assets/emoji/img_emoji_F617.o 

C_DEPS += \
./lvgl/examples/assets/emoji/img_emoji_F617.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/examples/assets/emoji/%.o lvgl/examples/assets/emoji/%.su lvgl/examples/assets/emoji/%.cyclo: ../lvgl/examples/assets/emoji/%.c lvgl/examples/assets/emoji/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"D:/stm32_projects/weld_saver_final/Weldsaver_Final" -I"D:/stm32_projects/weld_saver_final/Weldsaver_Final/hal_stm_lvgl/STM32746G-Discovery" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-examples-2f-assets-2f-emoji

clean-lvgl-2f-examples-2f-assets-2f-emoji:
	-$(RM) ./lvgl/examples/assets/emoji/img_emoji_F617.cyclo ./lvgl/examples/assets/emoji/img_emoji_F617.d ./lvgl/examples/assets/emoji/img_emoji_F617.o ./lvgl/examples/assets/emoji/img_emoji_F617.su

.PHONY: clean-lvgl-2f-examples-2f-assets-2f-emoji

