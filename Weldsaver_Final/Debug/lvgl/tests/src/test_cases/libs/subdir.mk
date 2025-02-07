################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/tests/src/test_cases/libs/test_barcode.c \
../lvgl/tests/src/test_cases/libs/test_freetype.c \
../lvgl/tests/src/test_cases/libs/test_libjpeg_turbo.c \
../lvgl/tests/src/test_cases/libs/test_libpng.c \
../lvgl/tests/src/test_cases/libs/test_lodepng.c \
../lvgl/tests/src/test_cases/libs/test_memmove.c \
../lvgl/tests/src/test_cases/libs/test_qrcode.c \
../lvgl/tests/src/test_cases/libs/test_tiny_ttf.c \
../lvgl/tests/src/test_cases/libs/test_tjpgd.c 

OBJS += \
./lvgl/tests/src/test_cases/libs/test_barcode.o \
./lvgl/tests/src/test_cases/libs/test_freetype.o \
./lvgl/tests/src/test_cases/libs/test_libjpeg_turbo.o \
./lvgl/tests/src/test_cases/libs/test_libpng.o \
./lvgl/tests/src/test_cases/libs/test_lodepng.o \
./lvgl/tests/src/test_cases/libs/test_memmove.o \
./lvgl/tests/src/test_cases/libs/test_qrcode.o \
./lvgl/tests/src/test_cases/libs/test_tiny_ttf.o \
./lvgl/tests/src/test_cases/libs/test_tjpgd.o 

C_DEPS += \
./lvgl/tests/src/test_cases/libs/test_barcode.d \
./lvgl/tests/src/test_cases/libs/test_freetype.d \
./lvgl/tests/src/test_cases/libs/test_libjpeg_turbo.d \
./lvgl/tests/src/test_cases/libs/test_libpng.d \
./lvgl/tests/src/test_cases/libs/test_lodepng.d \
./lvgl/tests/src/test_cases/libs/test_memmove.d \
./lvgl/tests/src/test_cases/libs/test_qrcode.d \
./lvgl/tests/src/test_cases/libs/test_tiny_ttf.d \
./lvgl/tests/src/test_cases/libs/test_tjpgd.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/tests/src/test_cases/libs/%.o lvgl/tests/src/test_cases/libs/%.su lvgl/tests/src/test_cases/libs/%.cyclo: ../lvgl/tests/src/test_cases/libs/%.c lvgl/tests/src/test_cases/libs/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"D:/2/Projects/003_RGB_Mixer/2_32F746GDISCOVERY" -I"D:/2/Projects/003_RGB_Mixer/2_32F746GDISCOVERY/hal_stm_lvgl/STM32746G-Discovery" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-tests-2f-src-2f-test_cases-2f-libs

clean-lvgl-2f-tests-2f-src-2f-test_cases-2f-libs:
	-$(RM) ./lvgl/tests/src/test_cases/libs/test_barcode.cyclo ./lvgl/tests/src/test_cases/libs/test_barcode.d ./lvgl/tests/src/test_cases/libs/test_barcode.o ./lvgl/tests/src/test_cases/libs/test_barcode.su ./lvgl/tests/src/test_cases/libs/test_freetype.cyclo ./lvgl/tests/src/test_cases/libs/test_freetype.d ./lvgl/tests/src/test_cases/libs/test_freetype.o ./lvgl/tests/src/test_cases/libs/test_freetype.su ./lvgl/tests/src/test_cases/libs/test_libjpeg_turbo.cyclo ./lvgl/tests/src/test_cases/libs/test_libjpeg_turbo.d ./lvgl/tests/src/test_cases/libs/test_libjpeg_turbo.o ./lvgl/tests/src/test_cases/libs/test_libjpeg_turbo.su ./lvgl/tests/src/test_cases/libs/test_libpng.cyclo ./lvgl/tests/src/test_cases/libs/test_libpng.d ./lvgl/tests/src/test_cases/libs/test_libpng.o ./lvgl/tests/src/test_cases/libs/test_libpng.su ./lvgl/tests/src/test_cases/libs/test_lodepng.cyclo ./lvgl/tests/src/test_cases/libs/test_lodepng.d ./lvgl/tests/src/test_cases/libs/test_lodepng.o ./lvgl/tests/src/test_cases/libs/test_lodepng.su ./lvgl/tests/src/test_cases/libs/test_memmove.cyclo ./lvgl/tests/src/test_cases/libs/test_memmove.d ./lvgl/tests/src/test_cases/libs/test_memmove.o ./lvgl/tests/src/test_cases/libs/test_memmove.su ./lvgl/tests/src/test_cases/libs/test_qrcode.cyclo ./lvgl/tests/src/test_cases/libs/test_qrcode.d ./lvgl/tests/src/test_cases/libs/test_qrcode.o ./lvgl/tests/src/test_cases/libs/test_qrcode.su ./lvgl/tests/src/test_cases/libs/test_tiny_ttf.cyclo ./lvgl/tests/src/test_cases/libs/test_tiny_ttf.d ./lvgl/tests/src/test_cases/libs/test_tiny_ttf.o ./lvgl/tests/src/test_cases/libs/test_tiny_ttf.su ./lvgl/tests/src/test_cases/libs/test_tjpgd.cyclo ./lvgl/tests/src/test_cases/libs/test_tjpgd.d ./lvgl/tests/src/test_cases/libs/test_tjpgd.o ./lvgl/tests/src/test_cases/libs/test_tjpgd.su

.PHONY: clean-lvgl-2f-tests-2f-src-2f-test_cases-2f-libs

