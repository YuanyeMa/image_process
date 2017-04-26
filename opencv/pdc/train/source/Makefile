
all:
	g++ ./train.cpp -o train  `pkg-config --cflags --libs  opencv`
	g++ ./find_save_HardExample.cpp -o ./creat_hard_example `pkg-config --cflags --libs opencv`
	g++ ./crop_image.cpp -o ./crop_image `pkg-config --cflags --libs opencv`
clean:
	rm -rf ./train ./creat_hard_example *.txt ./crop_image
