################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Lua/lapi.c \
../Lua/lauxlib.c \
../Lua/lbaselib.c \
../Lua/lcode.c \
../Lua/lctype.c \
../Lua/ldebug.c \
../Lua/ldo.c \
../Lua/lfunc.c \
../Lua/lgc.c \
../Lua/linit.c \
../Lua/llex.c \
../Lua/lmathlib.c \
../Lua/lmem.c \
../Lua/lobject.c \
../Lua/lopcodes.c \
../Lua/lparser.c \
../Lua/lstate.c \
../Lua/lstring.c \
../Lua/lstrlib.c \
../Lua/ltable.c \
../Lua/ltablib.c \
../Lua/ltm.c \
../Lua/lundump.c \
../Lua/lvm.c \
../Lua/lzio.c 

OBJS += \
./Lua/lapi.o \
./Lua/lauxlib.o \
./Lua/lbaselib.o \
./Lua/lcode.o \
./Lua/lctype.o \
./Lua/ldebug.o \
./Lua/ldo.o \
./Lua/lfunc.o \
./Lua/lgc.o \
./Lua/linit.o \
./Lua/llex.o \
./Lua/lmathlib.o \
./Lua/lmem.o \
./Lua/lobject.o \
./Lua/lopcodes.o \
./Lua/lparser.o \
./Lua/lstate.o \
./Lua/lstring.o \
./Lua/lstrlib.o \
./Lua/ltable.o \
./Lua/ltablib.o \
./Lua/ltm.o \
./Lua/lundump.o \
./Lua/lvm.o \
./Lua/lzio.o 

C_DEPS += \
./Lua/lapi.d \
./Lua/lauxlib.d \
./Lua/lbaselib.d \
./Lua/lcode.d \
./Lua/lctype.d \
./Lua/ldebug.d \
./Lua/ldo.d \
./Lua/lfunc.d \
./Lua/lgc.d \
./Lua/linit.d \
./Lua/llex.d \
./Lua/lmathlib.d \
./Lua/lmem.d \
./Lua/lobject.d \
./Lua/lopcodes.d \
./Lua/lparser.d \
./Lua/lstate.d \
./Lua/lstring.d \
./Lua/lstrlib.d \
./Lua/ltable.d \
./Lua/ltablib.d \
./Lua/ltm.d \
./Lua/lundump.d \
./Lua/lvm.d \
./Lua/lzio.d 


# Each subdirectory must supply rules for building sources it contributes
Lua/%.o Lua/%.su Lua/%.cyclo: ../Lua/%.c Lua/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -DLUA_Float=DLUA_32BITS -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/Frimi/STM32CubeIDE/workspace_1.13.2/Lua_Test/Lua/helper" -I"C:/Users/Frimi/STM32CubeIDE/workspace_1.13.2/Lua_Test/Lua" -I"C:/Users/Frimi/STM32CubeIDE/workspace_1.13.2/Lua_Test/luaProject" -I"C:/Users/Frimi/STM32CubeIDE/workspace_1.13.2/Lua_Test/luaProject/Scripts" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Lua

clean-Lua:
	-$(RM) ./Lua/lapi.cyclo ./Lua/lapi.d ./Lua/lapi.o ./Lua/lapi.su ./Lua/lauxlib.cyclo ./Lua/lauxlib.d ./Lua/lauxlib.o ./Lua/lauxlib.su ./Lua/lbaselib.cyclo ./Lua/lbaselib.d ./Lua/lbaselib.o ./Lua/lbaselib.su ./Lua/lcode.cyclo ./Lua/lcode.d ./Lua/lcode.o ./Lua/lcode.su ./Lua/lctype.cyclo ./Lua/lctype.d ./Lua/lctype.o ./Lua/lctype.su ./Lua/ldebug.cyclo ./Lua/ldebug.d ./Lua/ldebug.o ./Lua/ldebug.su ./Lua/ldo.cyclo ./Lua/ldo.d ./Lua/ldo.o ./Lua/ldo.su ./Lua/lfunc.cyclo ./Lua/lfunc.d ./Lua/lfunc.o ./Lua/lfunc.su ./Lua/lgc.cyclo ./Lua/lgc.d ./Lua/lgc.o ./Lua/lgc.su ./Lua/linit.cyclo ./Lua/linit.d ./Lua/linit.o ./Lua/linit.su ./Lua/llex.cyclo ./Lua/llex.d ./Lua/llex.o ./Lua/llex.su ./Lua/lmathlib.cyclo ./Lua/lmathlib.d ./Lua/lmathlib.o ./Lua/lmathlib.su ./Lua/lmem.cyclo ./Lua/lmem.d ./Lua/lmem.o ./Lua/lmem.su ./Lua/lobject.cyclo ./Lua/lobject.d ./Lua/lobject.o ./Lua/lobject.su ./Lua/lopcodes.cyclo ./Lua/lopcodes.d ./Lua/lopcodes.o ./Lua/lopcodes.su ./Lua/lparser.cyclo ./Lua/lparser.d ./Lua/lparser.o ./Lua/lparser.su ./Lua/lstate.cyclo ./Lua/lstate.d ./Lua/lstate.o ./Lua/lstate.su ./Lua/lstring.cyclo ./Lua/lstring.d ./Lua/lstring.o ./Lua/lstring.su ./Lua/lstrlib.cyclo ./Lua/lstrlib.d ./Lua/lstrlib.o ./Lua/lstrlib.su ./Lua/ltable.cyclo ./Lua/ltable.d ./Lua/ltable.o ./Lua/ltable.su ./Lua/ltablib.cyclo ./Lua/ltablib.d ./Lua/ltablib.o ./Lua/ltablib.su ./Lua/ltm.cyclo ./Lua/ltm.d ./Lua/ltm.o ./Lua/ltm.su ./Lua/lundump.cyclo ./Lua/lundump.d ./Lua/lundump.o ./Lua/lundump.su ./Lua/lvm.cyclo ./Lua/lvm.d ./Lua/lvm.o ./Lua/lvm.su ./Lua/lzio.cyclo ./Lua/lzio.d ./Lua/lzio.o ./Lua/lzio.su

.PHONY: clean-Lua

