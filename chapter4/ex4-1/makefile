CC = g++

SRCS = ex4_1.cpp

TARFGET = ex4_1

CFLAGS = $(shell pkg-config --cflags --libs opencv)

all:
	$(CC) $(SRCS) -o $(TARFGET) $(CFLAGS)

clean:
	rm -f $(TARFGET)

