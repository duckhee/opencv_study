CC = g++

SRCS = ex2_25.cpp

TARGET = ex2_25

CFLAGS = $(shell pkg-config --cflags --libs opencv)

all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)


clean:
	rm -f $(TARGET)