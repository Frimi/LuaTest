################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lua/helper/luaHeap.c \
../Lua/helper/luaHelper.c 

OBJS += \
./Lua/helper/luaHeap.o \
./Lua/helper/luaHelper.o 

C_DEPS += \
./Lua/helper/luaHeap.d \
./Lua/helper/luaHelper.d 


# Each subdirectory must supply rules for building sources it contributes
Lua/helper/%.o Lua/helper/%.su Lua/helper/%.cyclo: ../Lua/helper/%.c Lua/helper/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -DLUA_Float=DLUA_32BITS -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Frimi/STM32CubeIDE/workspace_1.13.2/Lua_Test/Lua/helper" -I"C:/Users/Frimi/STM32CubeIDE/workspace_1.13.2/Lua_Test/Lua" -I"C:/Users/Frimi/STM32CubeIDE/workspace_1.13.2/Lua_Test/luaProject" -I"C:/Users/Frimi/STM32CubeIDE/workspace_1.13.2/Lua_Test/luaProject/Scripts" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Lua-2f-helper

clean-Lua-2f-helper:
	-$(RM) ./Lua/helper/luaHeap.cyclo ./Lua/helper/luaHeap.d ./Lua/helper/luaHeap.o ./Lua/helper/luaHeap.su ./Lua/helper/luaHelper.cyclo ./Lua/helper/luaHelper.d ./Lua/helper/luaHelper.o ./Lua/helper/luaHelper.su

.PHONY: clean-Lua-2f-helper

