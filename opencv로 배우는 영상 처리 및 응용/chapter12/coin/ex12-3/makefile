CC = g++

SRCS = calc_coins.cpp

TARGET = coin_detect

INCLUDE = -I./include -I.

C_INC = \
./util.hpp \
./preprocess.hpp \
./histogram.hpp \
./classify.hpp \

CFLAGS = $(shell pkg-config --cflags --libs opencv)

CFLAGS += $(INCLUDE)

CFLAGS += $(patsubst %,-I%,$(C_INC))

all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)