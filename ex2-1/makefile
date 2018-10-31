CC = g++

CFLAGS = '-Wl,-rpath,$$ORIGIN/lib' -I./include -L./lib -lopencv_core 

#CFLAGS += -l/usr/local/include/opencv/
#CFLAGS = $(shell pkg-config --cflags opencv)
#LDFLAGS = $(shell pkg-config --libs opencv)
#CFLAGS += `pkg-config --cflags opencv`
#LDFLAGS += `pkg-config --libs opencv`
#OPENCV = $(shell `pkg-config --cflags --libs opencv`)

#OPENCV = `pkg-config --cflags --libs opencv`



SRCS = ex2_1.cpp
PROG = ex2_1

TEST_FLAG = '-Wl,-rpath,$$ORIGIN/lib' -I./include -L./lib -lopencv_core 

all:
	$(CC)  $(SRC) -o $(PROG) $(CFLAGS)

test:
	$(CC) $(SRCS) -o test $(TEST_FLAG)

clean:
	rm -f $(PROG)
	rm -f test

