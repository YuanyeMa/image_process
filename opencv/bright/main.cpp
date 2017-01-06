#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>

using namespace cv;
using namespace std;

Mat srcImg1;
Mat dstImg;
int g_nContrastValue = 80;
int g_nBrightValue = 80;
static void on_ContarstAndBright(int, void *);

int main()
{
	srcImg1 = imread("./01.jpg");
	dstImg = imread("./01.jpg");
	if (!srcImg1.data || !dstImg.data) {
		cout << "读取文件失败！" << endl;
		exit(-1);
	}

	namedWindow("效果图", 1);

	createTrackbar("对比度", "效果图", &g_nContrastValue, 300, on_ContarstAndBright);
	createTrackbar("亮 度", "效果图", &g_nBrightValue, 300, on_ContarstAndBright);

	//on_ContarstAndBright(g_nContrastValue, 0);
	//on_ContarstAndBright(g_nBrightValue, 0);

	while (char(waitKey(1)) != 'q') {}

	return 0;
}

static void on_ContarstAndBright(int a, void * x)
{
	namedWindow("原图", 1);

	for (int y = 0; y<srcImg1.rows; y++) 
	{
		for (int x=0; x<srcImg1.cols; x++)
		{
			for (int c=0; c<3;c++)
			{
				dstImg.at<Vec3b>(y, x)[c] = g_nContrastValue*0.01*(srcImg1.at<Vec3b>(y, x)[c] + g_nBrightValue);
				if (dstImg.at<Vec3b>(y, x)[c] > 255) dstImg.at<Vec3b>(y, x)[c] = 255;
				if (dstImg.at<Vec3b>(y, x)[c] < 0)  dstImg.at<Vec3b>(y, x)[c] = 0;
			}
		}
	}



	imshow("效果图", dstImg);
	imshow("原图", srcImg1);
}
