CC = g++

SRCS = ex3_14.cpp

TARGET = ex3_14

CFLAGS = $(shell pkg-config --cflags --libs opencv)

all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)
	rm -f test.bmp
	rm -f test.jpg
	rm -f test.png


