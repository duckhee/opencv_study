CC = g++

SRCS = ex4_40.cpp

TARGET = ex4_40

CFLAGS = $(shell pkg-config --cflags --libs opencv)

all: 
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)