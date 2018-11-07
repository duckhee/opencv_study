CC = g++

SRCS = ex2_3.cpp

TARGET = ex2_3

CFLAGS = '-Wl,-rpath,$$ORIGIN/lib' -I./include -L./lib -lopencv_core 

all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)