CC              := g++
CFLAGS          := -I/usr/local/include/opencv4 -L/usr/local/lib
OBJECTS         := 
LIBRARIES       := -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_highgui -lopencv_objdetect 

.PHONY: all clean

all: test

test: 

	$(CC) $(CFLAGS) -o test test.cpp $(LIBRARIES)
        
clean:

	rm -f *.o
	rm -f test
