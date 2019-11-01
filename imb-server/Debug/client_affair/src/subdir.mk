################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../client_affair/src/zclient_affair.cpp \
../client_affair/src/zcmd_parse.cpp \
../client_affair/src/zdevice_interface.cpp \
../client_affair/src/zsignal.cpp \
../client_affair/src/zthread_async_recv.cpp \
../client_affair/src/zthread_parse_packet.cpp 

OBJS += \
./client_affair/src/zclient_affair.o \
./client_affair/src/zcmd_parse.o \
./client_affair/src/zdevice_interface.o \
./client_affair/src/zsignal.o \
./client_affair/src/zthread_async_recv.o \
./client_affair/src/zthread_parse_packet.o 

CPP_DEPS += \
./client_affair/src/zclient_affair.d \
./client_affair/src/zcmd_parse.d \
./client_affair/src/zdevice_interface.d \
./client_affair/src/zsignal.d \
./client_affair/src/zthread_async_recv.d \
./client_affair/src/zthread_parse_packet.d 


# Each subdirectory must supply rules for building sources it contributes
client_affair/src/%.o: ../client_affair/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/shell.albert/4k-imb-server/imb-server/sm_client/inc" -I"/home/shell.albert/4k-imb-server/imb-server/subtitle" -I"/home/shell.albert/4k-imb-server/imb-server/ip_server/inc" -I/home/shell.albert/4k-imb-server/IMB-SM_SDK_V1.0_0710/include -I"/home/shell.albert/4k-imb-server/imb-server/network" -I"/home/shell.albert/4k-imb-server/imb-server/local/inc" -I"/home/shell.albert/4k-imb-server/imb-server/fpga" -I"/home/shell.albert/4k-imb-server/imb-server/client_affair/inc" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


