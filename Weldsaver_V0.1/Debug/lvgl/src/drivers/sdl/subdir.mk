################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/drivers/sdl/lv_sdl_keyboard.c \
../lvgl/src/drivers/sdl/lv_sdl_mouse.c \
../lvgl/src/drivers/sdl/lv_sdl_mousewheel.c \
../lvgl/src/drivers/sdl/lv_sdl_window.c 

OBJS += \
./lvgl/src/drivers/sdl/lv_sdl_keyboard.o \
./lvgl/src/drivers/sdl/lv_sdl_mouse.o \
./lvgl/src/drivers/sdl/lv_sdl_mousewheel.o \
./lvgl/src/drivers/sdl/lv_sdl_window.o 

C_DEPS += \
./lvgl/src/drivers/sdl/lv_sdl_keyboard.d \
./lvgl/src/drivers/sdl/lv_sdl_mouse.d \
./lvgl/src/drivers/sdl/lv_sdl_mousewheel.d \
./lvgl/src/drivers/sdl/lv_sdl_window.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/drivers/sdl/%.o lvgl/src/drivers/sdl/%.su lvgl/src/drivers/sdl/%.cyclo: ../lvgl/src/drivers/sdl/%.c lvgl/src/drivers/sdl/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"D:/2/Projects/003_RGB_Mixer/2_32F746GDISCOVERY" -I"D:/2/Projects/003_RGB_Mixer/2_32F746GDISCOVERY/hal_stm_lvgl/STM32746G-Discovery" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-drivers-2f-sdl

clean-lvgl-2f-src-2f-drivers-2f-sdl:
	-$(RM) ./lvgl/src/drivers/sdl/lv_sdl_keyboard.cyclo ./lvgl/src/drivers/sdl/lv_sdl_keyboard.d ./lvgl/src/drivers/sdl/lv_sdl_keyboard.o ./lvgl/src/drivers/sdl/lv_sdl_keyboard.su ./lvgl/src/drivers/sdl/lv_sdl_mouse.cyclo ./lvgl/src/drivers/sdl/lv_sdl_mouse.d ./lvgl/src/drivers/sdl/lv_sdl_mouse.o ./lvgl/src/drivers/sdl/lv_sdl_mouse.su ./lvgl/src/drivers/sdl/lv_sdl_mousewheel.cyclo ./lvgl/src/drivers/sdl/lv_sdl_mousewheel.d ./lvgl/src/drivers/sdl/lv_sdl_mousewheel.o ./lvgl/src/drivers/sdl/lv_sdl_mousewheel.su ./lvgl/src/drivers/sdl/lv_sdl_window.cyclo ./lvgl/src/drivers/sdl/lv_sdl_window.d ./lvgl/src/drivers/sdl/lv_sdl_window.o ./lvgl/src/drivers/sdl/lv_sdl_window.su

.PHONY: clean-lvgl-2f-src-2f-drivers-2f-sdl

