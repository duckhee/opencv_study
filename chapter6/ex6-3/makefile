CC = g++

SRCS = ex6_3.cpp

TARGET = ex6_3

CFLAGS = $(shell pkg-config --cflags --libs opencv)


all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)