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

distclean: clean
	rm -f $(TARGET)

CFLAGS+=-std=c++0x
newtest: newenum.o
	$(CC) -s -o newenum.exe newenum.o
