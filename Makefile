

CC = g++
LDFLAGS = -ldl
CFLAGS  = -o
OBJ = CRT_603_CZX_Test
INC = -I/usr/local/include/libusb-1.0
LIB = -L/usr/local/lib
SRC = CRT_603_CZX_Test.cpp LoadMyLibrary.cpp LoadMyLibrary.h



ALL:
	$(CC) $(CFLAGS) $(OBJ)  $(SRC) $(INC) $(LDFLAGS) 



