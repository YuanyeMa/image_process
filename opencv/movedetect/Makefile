CC = g++

CFLAGS += -g -O3 -Wall
INC += -I./ `pkg-config --cflags opencv`
LIBS += `pkg-config --libs opencv`

TARGET = main.exe
OBJS += movedetect.o

all:$(TARGET)
$(TARGET):$(OBJS)
	$(CC) $(INC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)
$(OBJS):%.o:%.cpp
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

.PHONY:clean
clean:
	rm -r *.o $(TARGET)