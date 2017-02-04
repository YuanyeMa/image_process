#include"opencv2/objdetect/objdetect.hpp"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

void help(){
	cout << 
		"Usage:" << endl <<
		"./facedetect --cascade=<cascade_path>"
		"--scale=<image scale greater ot equal to 1, try 1.3 for example"
		"filename" << endl << endl <<
		"Example:" << endl << 
		"./facedetect --cascade=\"./data/haarcascades/haarcascade_frontalface_alt.xml\""
		"--scale=1.3 ./photo.jpg" << endl << endl <<
		"Using OpenCV version" << CV_VERSION << endl;
}

void detectFaces(Mat &img, CascadeClassifier &cascade, double scale){

	const static Scalar colors[] =
	{
		Scalar(255, 0, 0),
		Scalar(255, 128, 0),
		Scalar(255, 255, 0),
		Scalar(0, 255, 0),
		Scalar(0, 128, 255),
		Scalar(0, 255, 255),
		Scalar(0, 0, 255),
		Scalar(255, 0, 255)
	};
	double t = 0;
	vector<Rect> faces;
	Mat gray;
	cvtColor(img, gray, CV_BGR2GRAY);

	Mat smallImg(cvRound(img.rows / scale), cvRound(img.cols / scale), CV_8UC1);
	Size smallImgSize = smallImg.size();

	resize(gray, smallImg, smallImgSize, 0, 0, INTER_LINEAR);
	equalizeHist(smallImg, smallImg);

	t = (double)getTickCount();
	cascade.detectMultiScale(smallImg, faces, 1.1, 2, CV_HAAR_SCALE_IMAGE, Size(30, 30));
	t = (double)getTickCount() - t;
	printf("detection time = %g ms\n", t*1000/getTickFrequency());;
	int i = 0;
	for (vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++){
		Scalar color = colors[i%8];
		Rect rect = faces[i];
		printf(
				"face;x=%f&y=%f&width=%f&height=%f\n",
				(float)r->x / smallImgSize.width,
				(float)r->y / smallImgSize.height,
				(float)r->width / smallImgSize.width,
				(float)r->height / smallImgSize.height
				);
		rectangle(img, cvPoint(cvRound(rect.x*scale), cvRound(rect.y*scale)), cvPoint(cvRound((rect.x + rect.width-1)*scale), cvRound((rect.y + rect.height-1)*scale)), color, 3, 8, 0);
	}
	namedWindow("result");
	imshow("result", img);
}

int main(int argc, const char** argv){

	const String scaleOpt = "--scale=";
	size_t scaleOptLen = scaleOpt.length();
	const String cascadeOpt = "--cascade=";
	size_t cascadeOptLen = cascadeOpt.length();

	String cascadeName, inputName;
	double scale = 1;

	for(int i = 1; i < argc; i++){
		if (cascadeOpt.compare(0, cascadeOptLen, argv[i], cascadeOptLen)== 0){
			cascadeName.assign(argv[i] + cascadeOptLen);
		}else if(scaleOpt.compare(0, scaleOptLen, argv[i], scaleOptLen)==0){
			if (!sscanf(argv[i]+scaleOpt.length(), "%lf", &scale)||scale < 1)
				scale = 1;
		}else if (argv[i][0] == '-'){
			cout << "warning; Unknown option" << argv[i] << endl;
		}else 
			inputName.assign(argv[i]);

	}

	if (cascadeName.empty()){
		cout << "error; you must specify the cascade." << endl;
		help();

		return -1;
	}

	CascadeClassifier cascade;
	if (!cascade.load(cascadeName)){
		cout << "error; Could not load classifier.Filename:\"" <<cascadeName << "\"" << endl;

		return -1;
	}

	if (inputName.empty()){
		cout << "error;You must specify the file to process." << endl;
		help();

		return -1;
	}

	Mat image = imread(inputName, 1);
	if(image.empty()){
		cout << "error; Could not load the file to process.Filename:\"" << inputName << "\"" << endl;

		return -1;
	}

	detectFaces(image, cascade, scale);
	char c = (char)waitKey(0)&0xFF;
	if(c == 27 || c == 'q' || c == 'Q')
		destroyAllWindows();
	return 0;
}
