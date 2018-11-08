CC = g++

SRCS = ex3_13.cpp

TARGET = ex3_13

CFLAGS = $(shell pkg-config --cflags --libs opencv)

all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)
	rm -f $(TARGET).bmp
	rm -f $(TARGET).jpg
	rm -f $(TARGET).png
