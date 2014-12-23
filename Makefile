TARGET=testenum

SRCS=\
	enumstr.cpp \
	testenum.cpp

OBJS=$(SRCS:.cpp=.o)

CC=gcc
CFLAGS=-g -Wall -O2
CFLAGS+=-save-temps

CPP=g++
CPPFLAGS=-g -Wall -O2
CPPFLAGS+=-save-temps

ALL-TARGET=$(TARGET) cnamedenum newenum
all: $(ALL-TARGET)

$(OBJS): days.h numbers.h fruits.h enumstr.h Makefile

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c $< -o $@

.cpp.o: $(SRCS)
	$(CPP) $(CPPFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) -s -o $@ $^

clean:
	rm -f $(OBJS) $(SRCS:.cpp=.ii) $(SRCS:.cpp=.s)
	rm -f newenum.[^c]*
	rm -f cnamedenum.[^c]

distclean: clean
	rm -f $(ALL-TARGET:=.exe)

cnamedenum: cnamedenum.o
	$(CC) -g -o $@ $^

# c++0x option can support <enum type>::<enum elem>
# to use this option, g++ version should above 4.3
newenum: CPPFLAGS+=-std=c++0x
newenum: newenum.o
	$(CPP) -g -o $@ $^
