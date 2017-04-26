#ifndef __FINDCONTOURS_H
#define __FINDCONTOURS_H

#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;
class connectionArea  //连通域对象
{
public:
        int x;
        int y;
};

class connectionAreaBoundary  //连通域外框
{
public:
	int left;
	int right;
	int top;
	int botton;
	bool isBoundary;//确实是边界标志位	
	void set(int width, int height)//使边界值扩大10pix
	{
		left = left - 10 > 0 ? left - 10 : 0;
		right = right + 10 < width-1 ? right + 10 : width - 1;
		top = top - 10 > 0 ? top - 10 : 0;
		botton = botton + 10 < height - 1 ? botton + 10 : height - 1;
	}
};

class connectionAreaCollection  //连通域对象合集
{
public:
	vector<connectionArea> mConnectionArea;
	int value;
	//边界值
	connectionAreaBoundary mBoundary;
	void selboundary(int x, int y)//边界查找
	{
		if (mBoundary.left>x)
		{
			mBoundary.left = x;
		}
		if (mBoundary.right<x)
		{
			mBoundary.right = x;
		}
		if (mBoundary.top>y)
		{
			mBoundary.top = y;
		}
		if (mBoundary.botton<y)
		{
			mBoundary.botton = y;
		}
	}
};

class connectionAreaSelObj  //连通域搜索过程对象
{
public:
	int *valuearray;
	int *imgDataInt;
	vector<connectionAreaCollection> ::iterator itor;//容器迭代器
public:
        void init(int width, int height)
	{
		valuearray = new int[height * width / 2];//设置标记数组最大可能找值为数组长度
		imgDataInt = new int[width *height];//创建跟图像大小一样的int类型的内存对象
	}
	void release()
	{
		delete[]valuearray;
		delete[]imgDataInt;
	}
};


void OnePass(Mat &fgmask, connectionAreaSelObj & selobj, vector<Rect> & obg_rect, Mat & noiseSuppressionImg);

#endif

