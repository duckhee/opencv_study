CC = g++
SRCS = ex2_5.cpp
TARGET = ex2_5

#CFLAGS = -g -Wall '-Wl,-rpath,$$ORIGIN/lib' -I./include -L./lib -lopencv_core

CFLAGS = -g -Wall $(shell pkg-config --cflags --libs opencv)

all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)

#g++ ex2_5.cpp -o ex2_5 `pkg-config --cflags --libs opencv`