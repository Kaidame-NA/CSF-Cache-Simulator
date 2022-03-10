CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

csim: Cache.o main.o
	g++ -o csim Cache.o main.o

Cache.o: Cache.cpp Cache.h
	g++ -c Cache.cpp $(CFLAGS)

main.o: main.cpp
	g++ -c main.cpp $(CFLAGS)

solution.zip :
	rm -f solution.zip
	zip -9r $@ Makefile README.txt *.h *.cpp 

.PHONY: clean
clean:
	rm -f *.o main?  *~
	rm -f solution.zip