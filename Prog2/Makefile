CC = gcc
C++ = g++ 
LIBDIRS = -L/usr/lib64
INCDIRS = -I/usr/include

HEADERS  = file.h
OBJS 	   = file.o

all : mtar

mtar: jtar.o $(HEADERS) $(OBJS) 
	$(C++) -o mtar jtar.o $(OBJS) $(INCDIRS) $(LIBDIRS)

file.o : file.cpp $(HEADERS)
	$(C++) -c file.cpp

jtar.o : jtar.cpp $(HEADERS) $(OBJS) 
	$(C++) -c jtar.cpp
 
clean :
	rm *.o

pristine :
	rm *.o
	rm mtar
