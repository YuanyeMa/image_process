cc = g++
exe = facedetect.out
obj = facedetect.o

$(exe):$(obj)
	$(cc) -o $(exe) $(obj) -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect

facedetect.o:facedetect.cpp
	$(cc) -c facedetect.cpp

clean:
	rm -rf *.o $(exe)
