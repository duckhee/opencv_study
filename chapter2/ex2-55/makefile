CC = g++

SRCS = ex2_55.cpp

TARGET = ex2_55

CFLAGS = $(shell pkg-config --cflags --libs opencv)

all: 
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)