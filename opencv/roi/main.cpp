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

	Size sz(srcImg2.cols/5, srcImg2.rows/5);
	Mat srcImg2z;
	resize(srcImg2, srcImg2z,sz);

	Mat imageROI = srcImg1(Rect(1000, 150, srcImg2z.cols, srcImg2z.rows));

	Mat mask;
	cvtColor(srcImg2z, mask, CV_BGR2GRAY);

	srcImg2z.copyTo(imageROI, mask);

	namedWindow("roi");
	imshow("roi", srcImg1);

	waitKey(0);

	return 0;
}
