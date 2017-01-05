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

	Size sz(srcImg1.cols/5, srcImg1.rows/5);
	Mat srcImg2z;
	resize(srcImg2, srcImg2z, sz);

	Mat imageROI = srcImg1(Rect(1000, 150, srcImg2z.cols, srcImg2z.rows));

	double a = 0.5;
	double b;
	Mat x;

	b = 1 - a;
	addWeighted(imageROI, a, srcImg2z, b, 0, imageROI);

	namedWindow("roi");
	imshow("roi", srcImg1);

	imwrite("addWeighted-part.jpg", srcImg1);

	waitKey(0);

	return 0;
}
