################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/character_functions/jatayu.c \
../Core/Src/character_functions/rahwana_sita.c 

C_DEPS += \
./Core/Src/character_functions/jatayu.d \
./Core/Src/character_functions/rahwana_sita.d 

OBJS += \
./Core/Src/character_functions/jatayu.o \
./Core/Src/character_functions/rahwana_sita.o 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/character_functions/%.o Core/Src/character_functions/%.su Core/Src/character_functions/%.cyclo: ../Core/Src/character_functions/%.c Core/Src/character_functions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/touchgfx/framework/include -I../TouchGFX/generated/fonts/include -I../TouchGFX/generated/gui_generated/include -I../TouchGFX/generated/images/include -I../TouchGFX/generated/texts/include -I../TouchGFX/generated/videos/include -I../TouchGFX/gui/include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-character_functions

clean-Core-2f-Src-2f-character_functions:
	-$(RM) ./Core/Src/character_functions/jatayu.cyclo ./Core/Src/character_functions/jatayu.d ./Core/Src/character_functions/jatayu.o ./Core/Src/character_functions/jatayu.su ./Core/Src/character_functions/rahwana_sita.cyclo ./Core/Src/character_functions/rahwana_sita.d ./Core/Src/character_functions/rahwana_sita.o ./Core/Src/character_functions/rahwana_sita.su

.PHONY: clean-Core-2f-Src-2f-character_functions

