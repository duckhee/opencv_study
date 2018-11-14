CC = g++

SRCS = ex5_9.cpp

TAREGT = ex5_9

CFLAGS = $(shell pkg-config --cflags --libs opencv)

all:
	$(CC) $(SRCS) -o $(TAREGT) $(CFLAGS)

clean:
	rm -f $(TAREGT)