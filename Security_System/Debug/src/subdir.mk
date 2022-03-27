################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/AFIO_program.c \
../src/BUZERR_program.c \
../src/EXTI_program.c \
../src/GPIO_program.c \
../src/HESP8266_program.c \
../src/KPD_program.c \
../src/MUSART1_program.c \
../src/NVIC_program.c \
../src/RCC_program.c \
../src/SERVO_program.c \
../src/SPI_program.c \
../src/STK_program.c \
../src/TFT_program.c \
../src/TIM_program.c \
../src/ULTRASONIC_program.c \
../src/main.c 

OBJS += \
./src/AFIO_program.o \
./src/BUZERR_program.o \
./src/EXTI_program.o \
./src/GPIO_program.o \
./src/HESP8266_program.o \
./src/KPD_program.o \
./src/MUSART1_program.o \
./src/NVIC_program.o \
./src/RCC_program.o \
./src/SERVO_program.o \
./src/SPI_program.o \
./src/STK_program.o \
./src/TFT_program.o \
./src/TIM_program.o \
./src/ULTRASONIC_program.o \
./src/main.o 

C_DEPS += \
./src/AFIO_program.d \
./src/BUZERR_program.d \
./src/EXTI_program.d \
./src/GPIO_program.d \
./src/HESP8266_program.d \
./src/KPD_program.d \
./src/MUSART1_program.d \
./src/NVIC_program.d \
./src/RCC_program.d \
./src/SERVO_program.d \
./src/SPI_program.d \
./src/STK_program.d \
./src/TFT_program.d \
./src/TIM_program.d \
./src/ULTRASONIC_program.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


