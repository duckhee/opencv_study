CC = g++

SRCS = ex5_4.cpp

TARGET = ex5_4

CFLAGS = $(shell pkg-config --cflags --libs opencv)

all: 
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)