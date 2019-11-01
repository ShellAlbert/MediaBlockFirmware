#This is a makefile of libimbapi.so for x86

INC=-I../include
LIBPATH=-L../libs_x86
LIB= -lsmsdk -ldl

BIN=./libimbapi.so

CC=g++ -DMM_LINUX -DMM_CPP -DMVC2API_DEBUG

FLAGS= -shared -Wall -fPIC

SOURCE = mvc2api_securitymanager.cpp
SOURCE += mvc2api_device.cpp
SOURCE += ./private/BaseClassPrivate.cpp
SOURCE += ./private/SecurityManagerPrivate.cpp

all:
	$(CC) $(FLAGS) -o $(BIN)  $(SOURCE) $(INC) $(LIBPATH) $(LIB)

clean:
	rm -rf *.o libimbapi.so

