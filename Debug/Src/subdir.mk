################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/ax25.c \
../Src/cc112x_spi.c \
../Src/cc_tx_init.c \
../Src/gps.c \
../Src/lfsr.c \
../Src/main.c \
../Src/rasp_manager.c \
../Src/scrambler.c \
../Src/sensors.c \
../Src/stm32f7xx_hal_msp.c \
../Src/stm32f7xx_it.c \
../Src/syscalls.c \
../Src/system_stm32f7xx.c \
../Src/time_manager.c \
../Src/tx_manager.c 

OBJS += \
./Src/ax25.o \
./Src/cc112x_spi.o \
./Src/cc_tx_init.o \
./Src/gps.o \
./Src/lfsr.o \
./Src/main.o \
./Src/rasp_manager.o \
./Src/scrambler.o \
./Src/sensors.o \
./Src/stm32f7xx_hal_msp.o \
./Src/stm32f7xx_it.o \
./Src/syscalls.o \
./Src/system_stm32f7xx.o \
./Src/time_manager.o \
./Src/tx_manager.o 

C_DEPS += \
./Src/ax25.d \
./Src/cc112x_spi.d \
./Src/cc_tx_init.d \
./Src/gps.d \
./Src/lfsr.d \
./Src/main.d \
./Src/rasp_manager.d \
./Src/scrambler.d \
./Src/sensors.d \
./Src/stm32f7xx_hal_msp.d \
./Src/stm32f7xx_it.d \
./Src/syscalls.d \
./Src/system_stm32f7xx.d \
./Src/time_manager.d \
./Src/tx_manager.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-d16 -DUSE_HAL_DRIVER -DSTM32F767xx -I"C:/Users/david/OneDrive/Documents/MSG/Ballooooon/Software1.0/HABv1/Inc" -I"C:/Users/david/OneDrive/Documents/MSG/Ballooooon/Software1.0/HABv1/Drivers/STM32F7xx_HAL_Driver/Inc" -I"C:/Users/david/OneDrive/Documents/MSG/Ballooooon/Software1.0/HABv1/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"C:/Users/david/OneDrive/Documents/MSG/Ballooooon/Software1.0/HABv1/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"C:/Users/david/OneDrive/Documents/MSG/Ballooooon/Software1.0/HABv1/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


