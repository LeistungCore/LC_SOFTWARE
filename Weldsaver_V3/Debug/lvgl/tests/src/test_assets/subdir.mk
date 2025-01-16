################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/tests/src/test_assets/font_1.c \
../lvgl/tests/src/test_assets/font_1_bin.c \
../lvgl/tests/src/test_assets/font_2.c \
../lvgl/tests/src/test_assets/font_2_bin.c \
../lvgl/tests/src/test_assets/font_3.c \
../lvgl/tests/src/test_assets/font_3_bin.c \
../lvgl/tests/src/test_assets/kern_one_otf.c \
../lvgl/tests/src/test_assets/test_animimg001.c \
../lvgl/tests/src/test_assets/test_animimg002.c \
../lvgl/tests/src/test_assets/test_animimg003.c \
../lvgl/tests/src/test_assets/test_arc_bg.c \
../lvgl/tests/src/test_assets/test_font_montserrat_ascii_1bpp.c \
../lvgl/tests/src/test_assets/test_font_montserrat_ascii_2bpp.c \
../lvgl/tests/src/test_assets/test_font_montserrat_ascii_4bpp.c \
../lvgl/tests/src/test_assets/test_font_montserrat_ascii_4bpp_compressed.c \
../lvgl/tests/src/test_assets/test_img_caret_down.c \
../lvgl/tests/src/test_assets/test_img_cogwheel_a8.c \
../lvgl/tests/src/test_assets/test_img_cogwheel_argb8888.c \
../lvgl/tests/src/test_assets/test_img_cogwheel_i4.c \
../lvgl/tests/src/test_assets/test_img_cogwheel_rgb565.c \
../lvgl/tests/src/test_assets/test_img_cogwheel_rgb565a8.c \
../lvgl/tests/src/test_assets/test_img_cogwheel_xrgb8888.c \
../lvgl/tests/src/test_assets/test_img_emoji_F617.c \
../lvgl/tests/src/test_assets/test_img_lvgl_logo_jpg.c \
../lvgl/tests/src/test_assets/test_img_lvgl_logo_png.c \
../lvgl/tests/src/test_assets/ubuntu_font.c 

OBJS += \
./lvgl/tests/src/test_assets/font_1.o \
./lvgl/tests/src/test_assets/font_1_bin.o \
./lvgl/tests/src/test_assets/font_2.o \
./lvgl/tests/src/test_assets/font_2_bin.o \
./lvgl/tests/src/test_assets/font_3.o \
./lvgl/tests/src/test_assets/font_3_bin.o \
./lvgl/tests/src/test_assets/kern_one_otf.o \
./lvgl/tests/src/test_assets/test_animimg001.o \
./lvgl/tests/src/test_assets/test_animimg002.o \
./lvgl/tests/src/test_assets/test_animimg003.o \
./lvgl/tests/src/test_assets/test_arc_bg.o \
./lvgl/tests/src/test_assets/test_font_montserrat_ascii_1bpp.o \
./lvgl/tests/src/test_assets/test_font_montserrat_ascii_2bpp.o \
./lvgl/tests/src/test_assets/test_font_montserrat_ascii_4bpp.o \
./lvgl/tests/src/test_assets/test_font_montserrat_ascii_4bpp_compressed.o \
./lvgl/tests/src/test_assets/test_img_caret_down.o \
./lvgl/tests/src/test_assets/test_img_cogwheel_a8.o \
./lvgl/tests/src/test_assets/test_img_cogwheel_argb8888.o \
./lvgl/tests/src/test_assets/test_img_cogwheel_i4.o \
./lvgl/tests/src/test_assets/test_img_cogwheel_rgb565.o \
./lvgl/tests/src/test_assets/test_img_cogwheel_rgb565a8.o \
./lvgl/tests/src/test_assets/test_img_cogwheel_xrgb8888.o \
./lvgl/tests/src/test_assets/test_img_emoji_F617.o \
./lvgl/tests/src/test_assets/test_img_lvgl_logo_jpg.o \
./lvgl/tests/src/test_assets/test_img_lvgl_logo_png.o \
./lvgl/tests/src/test_assets/ubuntu_font.o 

C_DEPS += \
./lvgl/tests/src/test_assets/font_1.d \
./lvgl/tests/src/test_assets/font_1_bin.d \
./lvgl/tests/src/test_assets/font_2.d \
./lvgl/tests/src/test_assets/font_2_bin.d \
./lvgl/tests/src/test_assets/font_3.d \
./lvgl/tests/src/test_assets/font_3_bin.d \
./lvgl/tests/src/test_assets/kern_one_otf.d \
./lvgl/tests/src/test_assets/test_animimg001.d \
./lvgl/tests/src/test_assets/test_animimg002.d \
./lvgl/tests/src/test_assets/test_animimg003.d \
./lvgl/tests/src/test_assets/test_arc_bg.d \
./lvgl/tests/src/test_assets/test_font_montserrat_ascii_1bpp.d \
./lvgl/tests/src/test_assets/test_font_montserrat_ascii_2bpp.d \
./lvgl/tests/src/test_assets/test_font_montserrat_ascii_4bpp.d \
./lvgl/tests/src/test_assets/test_font_montserrat_ascii_4bpp_compressed.d \
./lvgl/tests/src/test_assets/test_img_caret_down.d \
./lvgl/tests/src/test_assets/test_img_cogwheel_a8.d \
./lvgl/tests/src/test_assets/test_img_cogwheel_argb8888.d \
./lvgl/tests/src/test_assets/test_img_cogwheel_i4.d \
./lvgl/tests/src/test_assets/test_img_cogwheel_rgb565.d \
./lvgl/tests/src/test_assets/test_img_cogwheel_rgb565a8.d \
./lvgl/tests/src/test_assets/test_img_cogwheel_xrgb8888.d \
./lvgl/tests/src/test_assets/test_img_emoji_F617.d \
./lvgl/tests/src/test_assets/test_img_lvgl_logo_jpg.d \
./lvgl/tests/src/test_assets/test_img_lvgl_logo_png.d \
./lvgl/tests/src/test_assets/ubuntu_font.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/tests/src/test_assets/%.o lvgl/tests/src/test_assets/%.su lvgl/tests/src/test_assets/%.cyclo: ../lvgl/tests/src/test_assets/%.c lvgl/tests/src/test_assets/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"D:/2/Projects/003_RGB_Mixer/2_32F746GDISCOVERY" -I"D:/2/Projects/003_RGB_Mixer/2_32F746GDISCOVERY/hal_stm_lvgl/STM32746G-Discovery" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-tests-2f-src-2f-test_assets

clean-lvgl-2f-tests-2f-src-2f-test_assets:
	-$(RM) ./lvgl/tests/src/test_assets/font_1.cyclo ./lvgl/tests/src/test_assets/font_1.d ./lvgl/tests/src/test_assets/font_1.o ./lvgl/tests/src/test_assets/font_1.su ./lvgl/tests/src/test_assets/font_1_bin.cyclo ./lvgl/tests/src/test_assets/font_1_bin.d ./lvgl/tests/src/test_assets/font_1_bin.o ./lvgl/tests/src/test_assets/font_1_bin.su ./lvgl/tests/src/test_assets/font_2.cyclo ./lvgl/tests/src/test_assets/font_2.d ./lvgl/tests/src/test_assets/font_2.o ./lvgl/tests/src/test_assets/font_2.su ./lvgl/tests/src/test_assets/font_2_bin.cyclo ./lvgl/tests/src/test_assets/font_2_bin.d ./lvgl/tests/src/test_assets/font_2_bin.o ./lvgl/tests/src/test_assets/font_2_bin.su ./lvgl/tests/src/test_assets/font_3.cyclo ./lvgl/tests/src/test_assets/font_3.d ./lvgl/tests/src/test_assets/font_3.o ./lvgl/tests/src/test_assets/font_3.su ./lvgl/tests/src/test_assets/font_3_bin.cyclo ./lvgl/tests/src/test_assets/font_3_bin.d ./lvgl/tests/src/test_assets/font_3_bin.o ./lvgl/tests/src/test_assets/font_3_bin.su ./lvgl/tests/src/test_assets/kern_one_otf.cyclo ./lvgl/tests/src/test_assets/kern_one_otf.d ./lvgl/tests/src/test_assets/kern_one_otf.o ./lvgl/tests/src/test_assets/kern_one_otf.su ./lvgl/tests/src/test_assets/test_animimg001.cyclo ./lvgl/tests/src/test_assets/test_animimg001.d ./lvgl/tests/src/test_assets/test_animimg001.o ./lvgl/tests/src/test_assets/test_animimg001.su ./lvgl/tests/src/test_assets/test_animimg002.cyclo ./lvgl/tests/src/test_assets/test_animimg002.d ./lvgl/tests/src/test_assets/test_animimg002.o ./lvgl/tests/src/test_assets/test_animimg002.su ./lvgl/tests/src/test_assets/test_animimg003.cyclo ./lvgl/tests/src/test_assets/test_animimg003.d ./lvgl/tests/src/test_assets/test_animimg003.o ./lvgl/tests/src/test_assets/test_animimg003.su ./lvgl/tests/src/test_assets/test_arc_bg.cyclo ./lvgl/tests/src/test_assets/test_arc_bg.d ./lvgl/tests/src/test_assets/test_arc_bg.o ./lvgl/tests/src/test_assets/test_arc_bg.su ./lvgl/tests/src/test_assets/test_font_montserrat_ascii_1bpp.cyclo ./lvgl/tests/src/test_assets/test_font_montserrat_ascii_1bpp.d ./lvgl/tests/src/test_assets/test_font_montserrat_ascii_1bpp.o ./lvgl/tests/src/test_assets/test_font_montserrat_ascii_1bpp.su ./lvgl/tests/src/test_assets/test_font_montserrat_ascii_2bpp.cyclo ./lvgl/tests/src/test_assets/test_font_montserrat_ascii_2bpp.d ./lvgl/tests/src/test_assets/test_font_montserrat_ascii_2bpp.o ./lvgl/tests/src/test_assets/test_font_montserrat_ascii_2bpp.su ./lvgl/tests/src/test_assets/test_font_montserrat_ascii_4bpp.cyclo ./lvgl/tests/src/test_assets/test_font_montserrat_ascii_4bpp.d ./lvgl/tests/src/test_assets/test_font_montserrat_ascii_4bpp.o ./lvgl/tests/src/test_assets/test_font_montserrat_ascii_4bpp.su ./lvgl/tests/src/test_assets/test_font_montserrat_ascii_4bpp_compressed.cyclo ./lvgl/tests/src/test_assets/test_font_montserrat_ascii_4bpp_compressed.d ./lvgl/tests/src/test_assets/test_font_montserrat_ascii_4bpp_compressed.o ./lvgl/tests/src/test_assets/test_font_montserrat_ascii_4bpp_compressed.su ./lvgl/tests/src/test_assets/test_img_caret_down.cyclo ./lvgl/tests/src/test_assets/test_img_caret_down.d ./lvgl/tests/src/test_assets/test_img_caret_down.o ./lvgl/tests/src/test_assets/test_img_caret_down.su ./lvgl/tests/src/test_assets/test_img_cogwheel_a8.cyclo ./lvgl/tests/src/test_assets/test_img_cogwheel_a8.d ./lvgl/tests/src/test_assets/test_img_cogwheel_a8.o ./lvgl/tests/src/test_assets/test_img_cogwheel_a8.su ./lvgl/tests/src/test_assets/test_img_cogwheel_argb8888.cyclo ./lvgl/tests/src/test_assets/test_img_cogwheel_argb8888.d ./lvgl/tests/src/test_assets/test_img_cogwheel_argb8888.o ./lvgl/tests/src/test_assets/test_img_cogwheel_argb8888.su ./lvgl/tests/src/test_assets/test_img_cogwheel_i4.cyclo ./lvgl/tests/src/test_assets/test_img_cogwheel_i4.d ./lvgl/tests/src/test_assets/test_img_cogwheel_i4.o ./lvgl/tests/src/test_assets/test_img_cogwheel_i4.su ./lvgl/tests/src/test_assets/test_img_cogwheel_rgb565.cyclo ./lvgl/tests/src/test_assets/test_img_cogwheel_rgb565.d ./lvgl/tests/src/test_assets/test_img_cogwheel_rgb565.o ./lvgl/tests/src/test_assets/test_img_cogwheel_rgb565.su ./lvgl/tests/src/test_assets/test_img_cogwheel_rgb565a8.cyclo ./lvgl/tests/src/test_assets/test_img_cogwheel_rgb565a8.d ./lvgl/tests/src/test_assets/test_img_cogwheel_rgb565a8.o ./lvgl/tests/src/test_assets/test_img_cogwheel_rgb565a8.su ./lvgl/tests/src/test_assets/test_img_cogwheel_xrgb8888.cyclo ./lvgl/tests/src/test_assets/test_img_cogwheel_xrgb8888.d ./lvgl/tests/src/test_assets/test_img_cogwheel_xrgb8888.o ./lvgl/tests/src/test_assets/test_img_cogwheel_xrgb8888.su ./lvgl/tests/src/test_assets/test_img_emoji_F617.cyclo ./lvgl/tests/src/test_assets/test_img_emoji_F617.d ./lvgl/tests/src/test_assets/test_img_emoji_F617.o ./lvgl/tests/src/test_assets/test_img_emoji_F617.su ./lvgl/tests/src/test_assets/test_img_lvgl_logo_jpg.cyclo ./lvgl/tests/src/test_assets/test_img_lvgl_logo_jpg.d ./lvgl/tests/src/test_assets/test_img_lvgl_logo_jpg.o ./lvgl/tests/src/test_assets/test_img_lvgl_logo_jpg.su ./lvgl/tests/src/test_assets/test_img_lvgl_logo_png.cyclo ./lvgl/tests/src/test_assets/test_img_lvgl_logo_png.d ./lvgl/tests/src/test_assets/test_img_lvgl_logo_png.o ./lvgl/tests/src/test_assets/test_img_lvgl_logo_png.su ./lvgl/tests/src/test_assets/ubuntu_font.cyclo ./lvgl/tests/src/test_assets/ubuntu_font.d ./lvgl/tests/src/test_assets/ubuntu_font.o ./lvgl/tests/src/test_assets/ubuntu_font.su

.PHONY: clean-lvgl-2f-tests-2f-src-2f-test_assets

