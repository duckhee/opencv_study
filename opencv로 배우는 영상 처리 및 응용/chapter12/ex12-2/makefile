CC = g++

SRCS = draw_coin_histo.cpp

TARGET = coin_detect

INCLUDE = -I./inlcude -I.

C_INC = \
./histogram.hpp \
./histogram0.hpp \
./detect.hpp \
./classify.hpp \
#./preprocess.hpp \


CFLAGS = $(shell pkg-config --cflags --libs opencv)

CFLAGS += $(INCLUDE)

CFLAGS += $(patsubst %,-I%,$(C_INC))

all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)