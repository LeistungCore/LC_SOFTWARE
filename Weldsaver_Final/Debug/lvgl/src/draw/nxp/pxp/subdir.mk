################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.c \
../lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.c \
../lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.c 

OBJS += \
./lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.o \
./lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.o \
./lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.o 

C_DEPS += \
./lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.d \
./lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.d \
./lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/draw/nxp/pxp/%.o lvgl/src/draw/nxp/pxp/%.su lvgl/src/draw/nxp/pxp/%.cyclo: ../lvgl/src/draw/nxp/pxp/%.c lvgl/src/draw/nxp/pxp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"D:/stm32_projects/weld_saver_final/Weldsaver_Final" -I"D:/stm32_projects/weld_saver_final/Weldsaver_Final/hal_stm_lvgl/STM32746G-Discovery" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-src-2f-draw-2f-nxp-2f-pxp

clean-lvgl-2f-src-2f-draw-2f-nxp-2f-pxp:
	-$(RM) ./lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.cyclo ./lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.d ./lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.o ./lvgl/src/draw/nxp/pxp/lv_draw_pxp_blend.su ./lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.cyclo ./lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.d ./lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.o ./lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp.su ./lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.cyclo ./lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.d ./lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.o ./lvgl/src/draw/nxp/pxp/lv_gpu_nxp_pxp_osa.su

.PHONY: clean-lvgl-2f-src-2f-draw-2f-nxp-2f-pxp

