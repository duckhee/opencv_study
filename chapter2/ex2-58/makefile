CC = g++

SRCS = ex2_58.cpp

TARGET = ex2_58

CFLAGS = $(shell pkg-config --cflags --libs opencv)

all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)
	rm -f $(TARGET).xml
	