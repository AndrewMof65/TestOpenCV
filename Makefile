.PHONY: all clean

CC          := clang
CFLAGS      := -c -I/usr/local/include/opencv4
LDFLAGS	    := -L/usr/local/lib
LIBRARIES   := -lstdc++ -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_highgui -lopencv_objdetect 

SOURCES	    := tools.cpp test.cpp
OBJECTS	    := $(SOURCES:.cpp=.o)
EXECUTABLE  := test


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(LIBRARIES) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
        
clean:

	rm -f $(OBJECTS) $(EXECUTABLE)

