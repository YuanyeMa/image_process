cc = g++
exe = calcHist.out
obj = calcHist.o

$(exe):$(obj)
	$(cc) -o $(exe) $(obj) -lopencv_core -lopencv_highgui -lopencv_imgproc

calcHist.o:calcHist.c
	$(cc) -c calcHist.c

clean:
	rm -rf *.o $(exe)
