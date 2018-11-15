CC = g++

SRCS = ex5_14.cpp

TARGET = ex5_14

CFLAGS = $(shell pkg-config --cflags --libs opencv)

all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)
	rm -f $(TARGET).jpg
	