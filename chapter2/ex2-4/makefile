CC = g++
SRCS = ex2_4.cpp
TARGET = ex2_4

CFLAGS = -g -Wall '-Wl,-rpath,$$ORIGIN/lib' -I./include -L./lib -lopencv_core

all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)