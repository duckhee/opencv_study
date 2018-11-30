CC = g++

SRCS = ex8_13.cpp

TARGET = ex8_13

CFLAGS = $(shell pkg-config --cflags --libs opencv)

all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)


