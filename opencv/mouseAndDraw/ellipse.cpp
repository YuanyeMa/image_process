#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;
using namespace std;

Mat bgImage(600,800,CV_8UC3);


int main()
{

	namedWindow("mouse");

	putText(bgImage, "1", Point(100,100), CV_FONT_BLACK, 1, Scalar(255,0,0));
	ellipse(bgImage, Point(150, 150), Size(50, 50), 0, 0, 360, Scalar(0, 255, 0), -1);

	putText(bgImage, "2", Point(350, 100), CV_FONT_BLACK, 1, Scalar(255, 0, 0));
	ellipse(bgImage, Point(400, 150), Size(100, 50), 0, 0, 360, Scalar(0, 255, 0), -1);

	putText(bgImage, "3", Point(70, 350), CV_FONT_BLACK, 1, Scalar(255, 0, 0));
	ellipse(bgImage, Point(150, 400), Size(50, 100), 0, 0, 360, Scalar(0, 255, 0), -1);

	putText(bgImage, "4", Point(350, 350), CV_FONT_BLACK, 1, Scalar(255, 0, 0));
	ellipse(bgImage, Point(400, 400), Size(50, 100), 30, 0, 360, Scalar(0, 255, 0), 1);

	imshow("mouse", bgImage);

	while (char(waitKey(1)) != 'q') {}

	return 0;
}
