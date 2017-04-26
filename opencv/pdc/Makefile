TARGET=person_dector

CXX:=g++

SRC:=$(wildcard src/*.cpp)
OBJS:=$(SRC:.cpp=.o)
LIB:=
INC:=./inc
INCLUDE:=$(wildcard inc/*.h)

CXXFLAGS:=$(shell pkg-config --cflags --libs opencv) -I$(INC) -lwiringPi

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CXX) $^ -o $@ $(CXXFLAGS)
%.o:%.c
	$(CXX) -c  $^ -o $@ $(CXXFLAGS)
clean:
	rm -rf $(TARGET) $(OBJS)

