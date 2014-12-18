TARGET=testenum

SRCS=\
	enumstr.cpp \
	testenum.cpp

OBJS=$(SRCS:.cpp=.o)

CC=g++
CFLAGS=-g -Wall -O2

CFLAGS+=-save-temps

all: $(TARGET)

$(OBJS): days.h numbers.h fruits.h enumstr.h Makefile

.cpp.o: $(SRCS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) -s -o $@ $^

clean:
	rm -f $(OBJS) $(SRCS:.cpp=.ii) $(SRCS:.cpp=.s)
	rm -f newenum.[^c]*

distclean: clean
	rm -f $(TARGET)

# c++0x option can support <enum type>::<enum elem>
# to use this option, g++ version should above 4.3
CFLAGS+=-std=c++0x
newenum: newenum.o
	$(CC) -g -o newenum.exe newenum.o
