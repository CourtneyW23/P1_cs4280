GCC = g++
CFLAGS = -g -Wall -Wshadow

scanner: main.o scanner.o
	$(GCC) $(CFLAGS) main.o scanner.o  -o scanner

scanner.o: scanner.cpp scanner.h
	$(GCC) $(CFLAGS) -c scanner.cpp scanner.h

main.o: main.cpp
	$(GCC) $(CFLAGS) -c main.cpp

clean: 
	rm *.o scanner 
