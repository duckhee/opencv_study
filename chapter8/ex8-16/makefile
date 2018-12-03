CC = g++

SRCS = ex8_16.cpp pyrsegmentation.cpp

TARGET = ex8_16

CFLAGS = $(shell pkg-config --cflags --libs opencv)

all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)


