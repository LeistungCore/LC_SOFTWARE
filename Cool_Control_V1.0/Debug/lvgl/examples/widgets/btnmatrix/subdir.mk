################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_1.c \
../lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_2.c \
../lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_3.c 

OBJS += \
./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_1.o \
./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_2.o \
./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_3.o 

C_DEPS += \
./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_1.d \
./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_2.d \
./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_3.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/examples/widgets/btnmatrix/%.o lvgl/examples/widgets/btnmatrix/%.su lvgl/examples/widgets/btnmatrix/%.cyclo: ../lvgl/examples/widgets/btnmatrix/%.c lvgl/examples/widgets/btnmatrix/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I"D:/stm32_projects/FINAL_CODE_COOL_CONTROL_2/Cool_Control_V1.0" -I"D:/stm32_projects/FINAL_CODE_COOL_CONTROL_2/Cool_Control_V1.0/hal_stm_lvgl/STM32746G-Discovery" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Core/Inc -I../Middlewares/Third_Party/LwIP/src/apps/httpd -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/BSP/Components/lan8742 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/apps/http -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lvgl-2f-examples-2f-widgets-2f-btnmatrix

clean-lvgl-2f-examples-2f-widgets-2f-btnmatrix:
	-$(RM) ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_1.cyclo ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_1.d ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_1.o ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_1.su ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_2.cyclo ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_2.d ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_2.o ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_2.su ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_3.cyclo ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_3.d ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_3.o ./lvgl/examples/widgets/btnmatrix/lv_example_btnmatrix_3.su

.PHONY: clean-lvgl-2f-examples-2f-widgets-2f-btnmatrix

