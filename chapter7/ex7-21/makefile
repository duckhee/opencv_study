CC = g++

SRCS = ex7_21.cpp

TARGET = ex7_21

CFLAGS = $(shell pkg-config --cflags --libs opencv)

all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)
	

opencv_version:
	 $@ $(shell pkg-config --modversion opencv)