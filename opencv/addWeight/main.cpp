#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat srcImg1 = imread("./01.jpg");
	Mat srcImg2 = imread("./02.jpg");

	if (!srcImg1.data || !srcImg2.data) {
		cout << "read image file failed!" << endl;
		return false;
	}

	Size sz(srcImg1.cols, srcImg1.rows);
	Mat srcImg2z;
	resize(srcImg2, srcImg2z, sz);

	double a = 0.5;
	double b;
	Mat x;

	b = 1 - a;
	addWeighted(srcImg1, a, srcImg2z, b, 0, x);

	namedWindow("roi");
	imshow("roi", x);

	imwrite("addWeighted.jpg", x);

	waitKey(0);

	return 0;
}
