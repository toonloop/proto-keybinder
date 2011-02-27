DEPS=clutter-1.0 libxml-2.0
CFLAGS=`pkg-config --cflags $(DEPS)`
LIBS=`pkg-config --libs $(DEPS)`

all: run

main.o: main.cpp
	g++ -Wall -g $(CFLAGS) main.cpp -c -o main.o

run: main.o
	g++ -Wall -g $(LIBS) main.o -o run

.PHONY: clean

clean:
	rm -f run *.o

