#MakeFile for PA4
#Tyler Longbons

CC=g++
CFLAGS=-c -Wall -I.
OFLAGS=-o

pa4: main.o image.o
				$(CC) main.o image.o $(OFLAGS) pa4

main.o: main.cpp
				$(CC) $(CFLAGS) main.cpp

image.o: image.cpp image.h
				$(CC) $(CFLAGS) image.cpp

clean:
				rm -f *.o pa4

tar:
				tar cf PA4.tar *.cpp *.h Makefile	

valgrind: pa4	
				valgrind --tool=memcheck ./pa4																		
				
