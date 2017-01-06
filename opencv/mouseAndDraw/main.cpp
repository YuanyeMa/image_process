#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;
using namespace std;

Mat bgImage(600,800,CV_8UC3);

void on_MouseHandle(int event, int x, int y, int flags, void * param)
{
	Rect rect(x-10, y-10, 20, 20);
	Mat tempImg;
	bgImage.copyTo(tempImg);
	switch (event)
	{
	case EVENT_MOUSEMOVE:
		rectangle(tempImg, rect, Scalar(0, 0, 255), 1);
		line(tempImg, Point(x , 0), Point(x , y-10), Scalar(0, 0, 255), 1);
		line(tempImg, Point(x, y+10), Point(x, bgImage.rows), Scalar(0, 0, 255), 1);
		line(tempImg, Point(0, y), Point(x-10, y), Scalar(0, 0, 255), 1);
		line(tempImg, Point(x+10, y), Point(bgImage.cols,y), Scalar(0, 0, 255), 1);
		imshow("mouse", tempImg);
		break;
	default:
		imshow("mouse", bgImage);
		break;
	}
}

int main()
{

	namedWindow("mouse");
	setMouseCallback("mouse", on_MouseHandle);

	while (char(waitKey(1)) != 'q') {}

	return 0;
}
