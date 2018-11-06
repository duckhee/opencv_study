CC = g++

SRCS = ex2_45.cpp

TARGET = ex2_45

CFLAGS  = $(shell pkg-config --cflags --libs opencv)

all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)
	