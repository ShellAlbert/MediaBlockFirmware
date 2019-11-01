################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../network/zprotocol.cpp 

OBJS += \
./network/zprotocol.o 

CPP_DEPS += \
./network/zprotocol.d 


# Each subdirectory must supply rules for building sources it contributes
network/%.o: ../network/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/shell.albert/4k-imb-server/imb-server/sm_client/inc" -I"/home/shell.albert/4k-imb-server/imb-server/subtitle" -I"/home/shell.albert/4k-imb-server/imb-server/ip_server/inc" -I/home/shell.albert/4k-imb-server/IMB-SM_SDK_V1.0_0710/include -I"/home/shell.albert/4k-imb-server/imb-server/network" -I"/home/shell.albert/4k-imb-server/imb-server/local/inc" -I"/home/shell.albert/4k-imb-server/imb-server/fpga" -I"/home/shell.albert/4k-imb-server/imb-server/client_affair/inc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


