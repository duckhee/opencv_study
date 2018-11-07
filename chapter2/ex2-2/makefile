CC = g++
CFLAGS = '-Wl,-rpath,$$ORIGIN/lib' -I./include -L./lib -lopencv_core 

TARGET = ex2_2.cpp

PROG = ex2_2


all:
	$(CC) $(TARGET) -o $(PROG) $(CFLAGS)

clean:
	rm -f $(PROG)