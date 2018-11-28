CC = g++

SRCS = main.cpp

A_SRCS = apple_test.cpp

B_SRCS = blue_ballone.cpp

G_SRCS = green_ballone.cpp

TARGET = test

INCLUDE = -I./include -I.

CFLAGS = $(shell pkg-config --cflags --libs opencv)

all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

test:
	$(CC) $(G_SRCS) -o $(TARGET) $(CFLAGS)

apple_test1:
	$(CC) $(A_SRCS) -o $(TARGET) $(CFLAGS)

ballone_test:
	$(CC) $(B_SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)