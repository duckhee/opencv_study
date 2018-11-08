CC = g++

SRCS = ex3_9.cpp

TARGET = ex3_9

CFLAGS = $(shell pkg-config --cflags --libs opencv) 

all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)

