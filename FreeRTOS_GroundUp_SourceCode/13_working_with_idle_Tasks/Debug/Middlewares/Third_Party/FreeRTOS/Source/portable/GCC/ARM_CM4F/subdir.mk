################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c 

OBJS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o 

C_DEPS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.o: ../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.c Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I"/Users/hussamaldean/STM32CubeIDE/RTOS_Course/4_task_priorities/Core/Inc" -I"/Users/hussamaldean/STM32CubeIDE/RTOS_Course/4_task_priorities/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/hussamaldean/STM32CubeIDE/RTOS_Course/4_task_priorities/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/hussamaldean/STM32CubeIDE/RTOS_Course/4_task_priorities/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/hussamaldean/STM32CubeIDE/RTOS_Course/4_task_priorities/Drivers/CMSIS/Include" -I"/Users/hussamaldean/STM32CubeIDE/RTOS_Course/4_task_priorities/Middlewares/Third_Party/FreeRTOS/Source/include" -I"/Users/hussamaldean/STM32CubeIDE/RTOS_Course/4_task_priorities/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2" -I"/Users/hussamaldean/STM32CubeIDE/RTOS_Course/4_task_priorities/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F

clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F:
	-$(RM) ./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.d ./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o

.PHONY: clean-Middlewares-2f-Third_Party-2f-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F

