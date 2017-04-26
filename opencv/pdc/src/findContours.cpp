#include <opencv2/opencv.hpp>      
#include "opencv2/highgui/highgui.hpp"       
#include <opencv2/core/core.hpp>    
#include <vector>//容器头文件 
#include "findContours.h"

vector<connectionAreaCollection> mConAreaColVec;//连通域对象合集容器

void OnePass(Mat & fgmask, connectionAreaSelObj &selobj, vector<Rect> & obj_rect, Mat & noiseSuppressionImg)
{
	memset(selobj.imgDataInt, 0, fgmask.step*fgmask.rows * sizeof(int));//设置初始值为0
	uchar* imgDataChar = fgmask.data;
	int contourmark = 1; //连通域标志

	int rowPoint;//图像行指针偏移
	int lastRowPoint;//图像上一行行指针偏移
	int colPoint;//图像列指针偏移
	int lastColPoint;//图像上一列列指针偏移
	int lastRowColPoint;//图像上一行列指针偏移
	for (size_t row = 1; row < fgmask.rows; row++)//遍历图像行
	{
		rowPoint = row*fgmask.step; //图像行指针偏移计算
		lastRowPoint = (row - 1) *fgmask.step;
		for (size_t col = 1; col < fgmask.cols; col++)
		{
			colPoint = rowPoint + col; //像素点本身
			lastColPoint = rowPoint + col - 1;//像素点左邻接
			lastRowColPoint = lastRowPoint + col;//像素点上邻接

			if (imgDataChar[colPoint] == 255)//判断是不是连通域内的像素点
			{
				//如果不属于任何一个连通域
				if (selobj.imgDataInt[lastRowColPoint] == 0 && selobj.imgDataInt[lastColPoint] == 0)//该点邻接未被标值
				{
					selobj.valuearray[contourmark] = contourmark;//标记该点
					selobj.imgDataInt[colPoint] = contourmark;
					contourmark++;
				}
				else//该点邻接已被标值，则将邻接点中最小值标记值赋给他
				{
					if (selobj.imgDataInt[lastRowColPoint] != 0)//其上面的值只有可能为0或者已被标定为其他，if成立则表明其被标定为其他
					{
						if (selobj.imgDataInt[lastColPoint] != 0)//其左面的值只有可能为0或者已被标定为其他，if成立则表明其被标定为其他
						{
							if (selobj.valuearray[selobj.imgDataInt[lastColPoint]] > selobj.valuearray[selobj.imgDataInt[lastRowColPoint]])//左边大则用上边
																											   //if (imgDataInt[lastColPoint] > imgDataInt[lastRowColPoint])//左边大则用上边
							{
								selobj.imgDataInt[colPoint] = selobj.valuearray[selobj.imgDataInt[lastRowColPoint]];
								selobj.valuearray[selobj.imgDataInt[lastColPoint]] = selobj.valuearray[selobj.imgDataInt[colPoint]]; //标记该点
							}
							else
							{
								selobj.imgDataInt[colPoint] = selobj.valuearray[selobj.imgDataInt[lastColPoint]];
								selobj.valuearray[selobj.imgDataInt[lastRowColPoint]] = selobj.valuearray[selobj.imgDataInt[colPoint]];//标记该点
							}
						}
						else
						{
							selobj.imgDataInt[colPoint] = selobj.imgDataInt[lastRowColPoint];
						}
					}
					else//上面没有被标定，则为非连通域，则本值等于左值
					{
						selobj.imgDataInt[colPoint] = selobj.imgDataInt[lastColPoint];
					}
				}
			}
		}
	}
	for (size_t i = 1; i < contourmark; i++)//将同一个连通域的对象映射表调整好，做完这一步映射表制作完成
	{
		selobj.valuearray[i] = selobj.valuearray[selobj.valuearray[i]];
	}
	for (int row = 0; row < fgmask.rows; row++)//根据映射表对图像像素进行重新赋值
	{
		rowPoint = row*fgmask.step; //图像行指针偏移计算
		for (int col = 0; col <fgmask.cols; col++)
		{
			colPoint = rowPoint + col;
			if (selobj.imgDataInt[colPoint] != 0)
			{
				selobj.imgDataInt[colPoint] = selobj.valuearray[selobj.imgDataInt[colPoint]];
			}
		}
	}
	//对各连通域进行归类，并放入容器中
	for (int row = 0; row < fgmask.rows; row++)//根据映射表对图像像素进行重新赋值
	{
		rowPoint = row*fgmask.step; //图像行指针偏移计算
		for (int col = 0; col <fgmask.cols; col++)
		{
			colPoint = rowPoint + col;
			if (selobj.imgDataInt[colPoint] != 0)
			{		  
				selobj.itor = mConAreaColVec.begin();
				bool creatnew = true;
				while (selobj.itor != mConAreaColVec.end())//查看是否已经保存相应连通域
				{
					if (selobj.imgDataInt[colPoint] == selobj.itor->value)
					{
						connectionArea connectionAreapoint;
						connectionAreapoint.x = col;
						connectionAreapoint.y = row;
						selobj.itor->mConnectionArea.push_back(connectionAreapoint);
						selobj.itor->selboundary(col,row);
						creatnew = false;
						break;
					}
					selobj.itor++;
				}
				if (creatnew)
				{
					connectionAreaCollection newconnectionAreaCollection;
					newconnectionAreaCollection.value = selobj.imgDataInt[colPoint];
					connectionArea connectionAreapoint;
					connectionAreapoint.x = col;
					connectionAreapoint.y = row;
					newconnectionAreaCollection.mConnectionArea.push_back(connectionAreapoint);
					newconnectionAreaCollection.mBoundary.left = col;
					newconnectionAreaCollection.mBoundary.right = col;
					newconnectionAreaCollection.mBoundary.top = row;
					newconnectionAreaCollection.mBoundary.botton = row;
					newconnectionAreaCollection.mBoundary.isBoundary = true;
					mConAreaColVec.push_back(newconnectionAreaCollection);
				}
			}
		}
	}

	vector<connectionAreaBoundary> mConBoVec;//连通域边界容器

	memset(noiseSuppressionImg.data, 0, noiseSuppressionImg.step*noiseSuppressionImg.rows);
	selobj.itor = mConAreaColVec.begin();
	while (selobj.itor != mConAreaColVec.end())//查看是否已经保存相应连通域
	{
		if (selobj.itor->mConnectionArea.size()>500)
		{
			connectionAreaBoundary mBoundary;
			mBoundary=selobj.itor->mBoundary;
			mConBoVec.push_back(mBoundary);
			for (size_t i = 0; i < selobj.itor->mConnectionArea.size(); i++)
			{
				noiseSuppressionImg.at<unsigned char>(selobj.itor->mConnectionArea[i].y, selobj.itor->mConnectionArea[i].x) = 255;
			}
		}
		selobj.itor->mConnectionArea.clear();//资源回收
		selobj.itor++;
	}
	//合并重合边界
	for (size_t i = 0; i < mConBoVec.size(); i++)
	{
		if (mConBoVec[i].isBoundary == true)
		{
			for (size_t j = i+1; j < mConBoVec.size(); j++)//查找边界重叠对象，合并
			{	
				if (mConBoVec[i].right>mConBoVec[j].left
					&& (mConBoVec[i].botton>mConBoVec[j].top
					|| mConBoVec[i].top<mConBoVec[j].botton))
				{
					mConBoVec[j].isBoundary = false;
					mConBoVec[i].right=mConBoVec[i].right < mConBoVec[j].right?
						mConBoVec[j].right: mConBoVec[i].right;
					mConBoVec[i].top = mConBoVec[i].top > mConBoVec[j].top ?
						mConBoVec[j].top : mConBoVec[i].top;
					mConBoVec[i].botton = mConBoVec[i].botton < mConBoVec[j].botton ?
						mConBoVec[j].botton : mConBoVec[i].botton;
				}
				else if (mConBoVec[j].right>mConBoVec[i].left
					&& (mConBoVec[j].botton>mConBoVec[i].top
						|| mConBoVec[j].top<mConBoVec[i].botton))
				{
					mConBoVec[j].isBoundary = false;
					mConBoVec[i].left = mConBoVec[i].left > mConBoVec[j].left ?
						mConBoVec[j].left : mConBoVec[i].left;
					mConBoVec[i].top = mConBoVec[i].top > mConBoVec[j].top ?
						mConBoVec[j].top : mConBoVec[i].top;
					mConBoVec[i].botton = mConBoVec[i].botton < mConBoVec[j].botton ?
						mConBoVec[j].botton : mConBoVec[i].botton;
				}
			}
			//savecount++;
			//sprintf(path, "前景保存//%3d.jpg", savecount);
			mConBoVec[i].set(fgmask.cols, fgmask.rows);
			//Rect rect(mConBoVec[i].left, mConBoVec[i].top, mConBoVec[i].right- mConBoVec[i].left, mConBoVec[i].botton- mConBoVec[i].top);
			//Mat image_roi = srcimg(rect);
			//imwrite(path, image_roi);
			/* 画框 */
			//line(srcimg, cvPoint(mConBoVec[i].left, mConBoVec[i].top), cvPoint(mConBoVec[i].left, mConBoVec[i].botton), Scalar(0, 0, 255), 3);
			//line(srcimg, cvPoint(mConBoVec[i].left, mConBoVec[i].top), cvPoint(mConBoVec[i].right, mConBoVec[i].top), Scalar(0, 0, 255), 3);
			//line(srcimg, cvPoint(mConBoVec[i].right, mConBoVec[i].top), cvPoint(mConBoVec[i].right, mConBoVec[i].botton), Scalar(0, 0, 255), 3);
			//line(srcimg, cvPoint(mConBoVec[i].right, mConBoVec[i].botton), cvPoint(mConBoVec[i].left, mConBoVec[i].botton), Scalar(0, 0, 255), 3);

			obj_rect.push_back(Rect(mConBoVec[i].left, mConBoVec[i].top, (mConBoVec[i].right-mConBoVec[i].left), (mConBoVec[i].botton-mConBoVec[i].top)));
		}
		
	}
	mConBoVec.clear();
	mConAreaColVec.clear();
	//imshow("噪声抑制图像", noiseSuppressionImg);//这里显示他最后程序便会报错，先不管
	//noiseSuppressionImg.release();
}

