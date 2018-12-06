CC = g++

SRCS = ex10_10.cpp

TARGET = ex10_10

CFLAGS = $(shell pkg-config --cflags --libs opencv)

all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)
	rm -f Keypoints.yml

