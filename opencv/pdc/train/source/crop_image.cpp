#include <iostream>
#include <iostream>
#include <fstream>
#include <stdlib.h> //srand()和rand()函数
#include <time.h> //time()函数
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/ml/ml.hpp>
#include "dataset.h"

using namespace std;
using namespace cv;

int CropImageCount = 0; //裁剪出来的负样本图片个数

int main()
{
	Mat src;
	string ImgName;

	char saveName[256];//裁剪出来的负样本图片文件名
	ifstream fin(ORI_NegSamListFile);//打开原始负样本图片文件列表

	//一行一行读取文件列表
	while(getline(fin,ImgName))
	{
		cout<<"处理："<<ImgName<<endl;
		ImgName = NEG_SAMPLE_ORIGIN_PATH+ImgName;

		src = imread(ImgName,1);//读取图片
		if (src.empty()) {
			cout<<"打开图片失败，程序退出!"<<endl;
			return -1;
		}

		//src =cvLoadImage(imagename,1);
		cout<<"宽："<<src.cols<<"，高："<<src.rows<<endl;

		//图片大小应该能能至少包含一个64*128的窗口
		if(src.cols > 64 && src.rows > 128)
		{
			srand(time(NULL));//设置随机数种子

			//从每张图片中随机裁剪10个64*128大小的不包含人的负样本
			for(int i=0; i<10; i++)
			{
				int x = (int)( rand() % (src.cols-64) ); //左上角x坐标
				int y = (int)( rand() % (src.rows-128) ); //左上角y坐标
				cout<<x<<","<<y<<endl;
				Mat imgROI = src(Rect(x,y,64,128));
				sprintf(saveName,"./../dataset/neg/noperson%06d.jpg",++CropImageCount);//生成裁剪出的负样本图片的文件名
				imwrite(saveName, imgROI);//保存文件
			}
		} else if (src.cols == 64 && src.rows == 128) {
				sprintf(saveName,"./../dataset/neg/noperson%06d.jpg",++CropImageCount);
				imwrite(saveName, src);//保存文件
		}
	}

  cout<<"总共裁剪出"<<CropImageCount<<"张图片"<<endl;

}
