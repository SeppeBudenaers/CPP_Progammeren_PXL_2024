CPP = g++
CFLAGS = -Wall -g
LDFLAGS = -g

DEPS =
INCLUDES = -I .
VPATH =

SRC_DIR = .
OBJ_DIR = .

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJ =  $(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(SRCS)))
TARGET = main

$(TARGET): $(OBJ)
	$(CPP) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CPP) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -rf *.o *~ $(TARGET)
