################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../luaProject/luaInterface.c \
../luaProject/printFreeHeap.c 

OBJS += \
./luaProject/luaInterface.o \
./luaProject/printFreeHeap.o 

C_DEPS += \
./luaProject/luaInterface.d \
./luaProject/printFreeHeap.d 


# Each subdirectory must supply rules for building sources it contributes
luaProject/%.o luaProject/%.su luaProject/%.cyclo: ../luaProject/%.c luaProject/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -DLUA_Float=DLUA_32BITS -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Frimi/STM32CubeIDE/workspace_1.13.2/Lua_Test/Lua/helper" -I"C:/Users/Frimi/STM32CubeIDE/workspace_1.13.2/Lua_Test/Lua" -I"C:/Users/Frimi/STM32CubeIDE/workspace_1.13.2/Lua_Test/luaProject" -I"C:/Users/Frimi/STM32CubeIDE/workspace_1.13.2/Lua_Test/luaProject/Scripts" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-luaProject

clean-luaProject:
	-$(RM) ./luaProject/luaInterface.cyclo ./luaProject/luaInterface.d ./luaProject/luaInterface.o ./luaProject/luaInterface.su ./luaProject/printFreeHeap.cyclo ./luaProject/printFreeHeap.d ./luaProject/printFreeHeap.o ./luaProject/printFreeHeap.su

.PHONY: clean-luaProject

