CC = g++

SRCS = ex4_22.cpp

TARGET = ex4_22

CFLAGS = $(shell pkg-config --cflags --libs opencv)

all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)
	