################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../daemon/zsdk_daemon.cpp 

OBJS += \
./daemon/zsdk_daemon.o 

CPP_DEPS += \
./daemon/zsdk_daemon.d 


# Each subdirectory must supply rules for building sources it contributes
daemon/%.o: ../daemon/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/shell.albert/4k-imb-server/imb-server/sm_client/inc" -I"/home/shell.albert/4k-imb-server/imb-server/subtitle" -I"/home/shell.albert/4k-imb-server/imb-server/ip_server/inc" -I/home/shell.albert/4k-imb-server/IMB-SM_SDK_V1.0_0710/include -I"/home/shell.albert/4k-imb-server/imb-server/network" -I"/home/shell.albert/4k-imb-server/imb-server/local/inc" -I"/home/shell.albert/4k-imb-server/imb-server/fpga" -I"/home/shell.albert/4k-imb-server/imb-server/client_affair/inc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


