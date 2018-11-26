CC = g++

SRCS = find_coins.cpp

TARGET = coin_decter

INCLUDE = -I./include -I.

C_INC = ./preprocess.hpp

CFLAGS = $(shell pkg-config --cflags --libs opencv) 

CFLAGS += $(INCLUDE)

CFLAGS += $(patsubst %,-I%,$(C_INC))

all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)
