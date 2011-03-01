DEPS=clutter-1.0 libxml-2.0
CXXFLAGS=`pkg-config --cflags $(DEPS)` -Wall -Werror -Wfatal-errors -Wextra -O2
LIBS=`pkg-config --libs $(DEPS)`
OBJS=main.o

all: run

ifeq ($(shell uname -s),Darwin)
  CXXFLAGS += -DDARWIN
endif

%.o : %.cpp %.h
	$(CC) -c $(CXXFLAGS) $< -o $@

run: $(OBJS)
	g++ -g $(LIBS) $^ -o $@

.PHONY: clean

clean:
	rm -f run *.o

