################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/draw/renesas/dave2d/lv_draw_dave2d.c \
../lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_arc.c \
../lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_border.c \
../lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_fill.c \
../lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_image.c \
../lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_label.c \
../lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_line.c \
../lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_mask_rectangle.c \
../lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_triangle.c \
../lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_utils.c 

OBJS += \
./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d.o \
./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_arc.o \
./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_border.o \
./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_fill.o \
./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_image.o \
./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_label.o \
./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_line.o \
./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_mask_rectangle.o \
./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_triangle.o \
./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_utils.o 

C_DEPS += \
./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d.d \
./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_arc.d \
./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_border.d \
./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_fill.d \
./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_image.d \
./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_label.d \
./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_line.d \
./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_mask_rectangle.d \
./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_triangle.d \
./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_utils.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/draw/renesas/dave2d/%.o lvgl/src/draw/renesas/dave2d/%.su lvgl/src/draw/renesas/dave2d/%.cyclo: ../lvgl/src/draw/renesas/dave2d/%.c lvgl/src/draw/renesas/dave2d/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"D:/2/Projects/003_RGB_Mixer/2_32F746GDISCOVERY" -I"D:/2/Projects/003_RGB_Mixer/2_32F746GDISCOVERY/hal_stm_lvgl/STM32746G-Discovery" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-draw-2f-renesas-2f-dave2d

clean-lvgl-2f-src-2f-draw-2f-renesas-2f-dave2d:
	-$(RM) ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d.cyclo ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d.d ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d.o ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d.su ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_arc.cyclo ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_arc.d ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_arc.o ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_arc.su ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_border.cyclo ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_border.d ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_border.o ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_border.su ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_fill.cyclo ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_fill.d ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_fill.o ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_fill.su ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_image.cyclo ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_image.d ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_image.o ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_image.su ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_label.cyclo ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_label.d ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_label.o ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_label.su ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_line.cyclo ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_line.d ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_line.o ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_line.su ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_mask_rectangle.cyclo ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_mask_rectangle.d ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_mask_rectangle.o ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_mask_rectangle.su ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_triangle.cyclo ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_triangle.d ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_triangle.o ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_triangle.su ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_utils.cyclo ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_utils.d ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_utils.o ./lvgl/src/draw/renesas/dave2d/lv_draw_dave2d_utils.su

.PHONY: clean-lvgl-2f-src-2f-draw-2f-renesas-2f-dave2d

