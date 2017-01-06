#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;
using namespace std;


int main()
{
	Mat bgImage(600, 800, CV_8UC3);

	namedWindow("mouse");
	Point pt[1][4];

	pt[0][0] = Point(20,20);
	pt[0][1] = Point(500, 175);
	pt[0][2] = Point(400, 300);
	pt[0][3] = Point(240, 330);
	

	const Point * ppt[1] = { pt[0] };
	int npt[] = { 4 };

	fillPoly(bgImage, ppt, npt, 1, Scalar(0, 255, 0), 8);

	imshow("mouse", bgImage);

	while (char(waitKey(1)) != 'q') {}

	return 0;
}
