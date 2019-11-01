#This is a makefile of imbsdkdemo for x86

INC=-I../include
LIBPATH=-L../libs_x86
LIB= -lssl -lcrypto -limbapi -ldl -lrt
BIN=./imbsdkdemo
CC=g++ -DMM_LINUX -DMM_CPP

SOURCE =  ./main.cpp

FLAGS= -g -Wall

all:
	$(CC) $(FLAGS) -o $(BIN)  $(SOURCE) $(INC) $(LIBPATH) $(LIB)

clean:
	rm -rf *.o imbsdkdemo
