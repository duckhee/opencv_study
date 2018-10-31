CC = g++

SRCS = ex2_7.cpp

TARGET = ex2_7

CFLAGS = $(shell pkg-config --cflags --libs opencv)

all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -rf $(TARGET)
