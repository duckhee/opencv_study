CC = g++

SRCS = ex7_8.cpp

TARGET = ex7_8

CFLAGS = $(shell pkg-config --cflags --libs opencv)

all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f  $(TARGET)