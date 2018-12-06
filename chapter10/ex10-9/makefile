CC = g++

SRCS = ex10_9.cpp

TARGET = ex10_9

CFLAGS = $(shell pkg-config --cflags --libs opencv)

all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)
	rm -f Keypoints.yml

