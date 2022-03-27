################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../userLib/MFRC522.c \
../userLib/i2c-lcd.c 

OBJS += \
./userLib/MFRC522.o \
./userLib/i2c-lcd.o 

C_DEPS += \
./userLib/MFRC522.d \
./userLib/i2c-lcd.d 


# Each subdirectory must supply rules for building sources it contributes
userLib/%.o userLib/%.su: ../userLib/%.c userLib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I"C:/Users/pcx/STM32CubeIDE/workspace_1.9.0/STM32RC522_DAT/userLib" -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-userLib

clean-userLib:
	-$(RM) ./userLib/MFRC522.d ./userLib/MFRC522.o ./userLib/MFRC522.su ./userLib/i2c-lcd.d ./userLib/i2c-lcd.o ./userLib/i2c-lcd.su

.PHONY: clean-userLib

