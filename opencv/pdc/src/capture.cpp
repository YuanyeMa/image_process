#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/video/background_segm.hpp> //mog
#include <iostream>
#include "image_detect.h"
#include "findContours.h"
#include <stdio.h>
#include <wiringPi.h>

#define VIDEO_SAVE 0

using namespace cv;
using namespace std;

/********************************************************************* 
function : 提取联通域 
param:
	@fgmask : 前景
	@selobj : 标记联通域所需的内存
	@obj_rece : 目标的外接矩形列表
	@noiseSuppressionImg : 经过噪声抑制的前景图片
return:
	目标的个数
**********************************************************************/
int find_blob_rectangle(Mat & fgmask, connectionAreaSelObj & selobj, vector<Rect> & obj_rect, Mat & noiseSuppressionImg)
{
	OnePass(fgmask, selobj, obj_rect, noiseSuppressionImg);

	return obj_rect.size();
}


/********************************************************************* 
function : 显示图片
param : 
	@winName : 显示的窗体名字
	@frame : 原始图像
	@gray : 灰度图
	@fgmask : 前景
	@noise : 经过噪声抑制的图片
	@oVideoWriter : 保存视频句柄
return:
	0
**********************************************************************/
#if VIDEO_SAVE 
int show_image_inwindow(const string & winName , const Mat & frame, const Mat & gray, const Mat & fgmask, const Mat & noise, VideoWriter & oVideoWriter)
#else
int show_image_inwindow(const string & winName , const Mat & frame, const Mat & gray, const Mat & fgmask, const Mat & noise)
#endif
{
	Mat image;
	int w = frame.cols*2 + 80;
	int h = frame.rows + 60;
	image.create(Size(w, h), CV_8UC3);

	Mat imgRoi1 = image(Rect(20,20, frame.cols, frame.rows));
	frame.copyTo(imgRoi1);

	Mat imgRoi2 = image(Rect(frame.cols+40, 20, gray.cols, gray.rows));

	Mat x(Size(gray.cols, gray.rows), CV_8UC3);
	cvtColor(gray, x, CV_GRAY2BGR);
	x.copyTo(imgRoi2);

	Mat imgRoi3 = image(Rect(frame.cols+40+gray.cols+20, 20, fgmask.cols, fgmask.rows));
	Mat y(Size(fgmask.cols, fgmask.rows), CV_8UC3);
	cvtColor(fgmask, y, CV_GRAY2BGR);
	y.copyTo(imgRoi3);

	Mat imgRoi5 = image(Rect(frame.cols+40+gray.cols+20, fgmask.rows+40, noise.cols, noise.rows));
	Mat u(Size(noise.cols, noise.rows), CV_8UC3);
	cvtColor(noise, u, CV_GRAY2BGR);
	u.copyTo(imgRoi5);

#if VIDEO_SAVE 
	if (oVideoWriter.isOpened())	
		oVideoWriter.write(image);
#endif 
	imshow(winName, image);

	return 0;
}


/********************************************************************* 
function : 获取ROI图像
param :
	@rect : 目标矩形区域
	@frame : 原图
	@roi : ROI图像
return :
	@success : 0
	@other : -1
**********************************************************************/
int get_roi_rect(Rect & rect, Mat & frame, Mat & roi)
{	
	Rect rect_roi = rect;

	rect.x = (int)((double)rect.x/320 * 640);
	rect.y = (int)((double)rect.y/240 * 480);
	rect.width = (int)((double)rect.width/320 * 640);
	rect.height = (int)((double)rect.height/240 * 480);

	if (rect.height%2)
		rect_roi.height = rect.height+1;
	else 
		rect_roi.height = rect.height;

	if (rect_roi.width != (rect_roi.height/2)) {
		Point center(rect.x+rect.width/2, rect.y+rect.height/2);
		rect_roi.x = center.x-(rect.height/4);
		rect_roi.y = center.y-(rect.height/2);
		rect_roi.width = rect.height/2;
		rect_roi.height = rect.height;
	}

	if ( 0 <= rect_roi.x && 0 <= rect_roi.width && rect_roi.x+rect_roi.width <= frame.cols &&
	     0 <= rect_roi.y && 0 <= rect_roi.height && rect_roi.y+rect_roi.height <= frame.rows) {
		Mat r = frame(rect_roi);
		resize(r, roi, Size(64, 128));
		return 0;
	} else 
		return -1;
}

int main(int argc, char ** argv)
{
	
	int frame_count = 0;
	char filename[64]={0};
	bool stop = false;

	bool open_led = false;
	bool led_on = false;
	double tt = 0;


	Mat fgmask;	//前景掩膜
	Mat graimg;	//灰度图
	Mat frame; 	//原始帧
	BackgroundSubtractorMOG2 mog2; //使用默认参数调用混合高斯模型
	

	VideoCapture cap(0);
	if (!cap.isOpened()) {
		std::cout<<"open video1 failed!"<<std::endl;
		return -1;
	}

	cap>>frame;
	if (frame.empty()) {
		cout<<"读取图像失败，程序退出"<<endl;
		return -1;
	}
	connectionAreaSelObj selobj; 

	cvtColor(frame, graimg, CV_BGR2GRAY); //转换为灰度图
	resize(graimg, graimg, Size(320,240)); //缩放

	selobj.init(graimg.cols, graimg.rows);

#if VIDEO_SAVE
	/* 初始化视频保存 */
	double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH)*2+80;
	double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT)+60;
	Size frameSize(static_cast<int>(dWidth), static_cast<int>(dHeight));
	VideoWriter oVideoWriter(argv[1], CV_FOURCC('D', 'I', 'V', 'X'), 10, frameSize, true);
	if (!oVideoWriter.isOpened()) {
		cout<<" oVideoWriter init failed!"<<endl;
		return -1;
	}
	/* end */
#endif 

	dector_init(); //初始化分类器

	while(!stop) {
		double time = (double)getTickCount(); 
		cap>>frame;
		if (frame.empty()) {
			cout<<"读取图像失败，程序退出"<<endl;
			return -1;
		}
		frame_count++;

		cvtColor(frame, graimg, CV_BGR2GRAY); //转换为灰度图
		resize(graimg, graimg, Size(320,240)); //缩放
		mog2(graimg, fgmask, 0.001);	//前景提取

		//Mat bg;
		//mog2.getBackgroundImage(bg); //只有BGR图片能够获取背景
		if (frame_count > 500) {
			medianBlur(fgmask, fgmask, 3); //中值滤波
			threshold(fgmask, fgmask, 50, 255, CV_THRESH_BINARY); //二值化

			Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
			dilate(fgmask, fgmask, element); //膨胀操作
			erode(fgmask, fgmask, element); //腐蚀操作

			/* 找出联通域外接矩形 */
			Mat noseSuppressionImg(graimg.rows, graimg.cols, CV_8UC1);
			vector<Rect> obj_rect_vec;

			int num_obj = find_blob_rectangle(fgmask, selobj, obj_rect_vec, noseSuppressionImg);

			/* 画出外接矩形 */
			vector<Rect>::iterator it;
			for (it=obj_rect_vec.begin(); it!=obj_rect_vec.end(); it++) {
				Mat sRoi;
				if(!get_roi_rect(*it, frame, sRoi)) {
					//sprintf(filename, "./%d.jpg", frame_count);
					//imwrite(filename, sRoi);
					/* 检测人，是人的话标红色，不是人的话标绿色 */
					int ispeople = 0;
					ispeople = dector_win(sRoi);
					if (1 == ispeople) {
						rectangle(frame, it->tl(), it->br(), Scalar(0, 0, 255), 2, 8, 0);
						//cout << "人类出没 ！！！！！！！！！"<<endl;
						tt = getTickCount();
						led_on = true;
						cout<<"开灯！！！！！！"<<endl;
					} else if (-1 == ispeople){
						rectangle(frame, it->tl(), it->br(), Scalar(0, 255, 0), 2, 8, 0);
						//cout<<" just nothing, easy !!!"<<endl;
					} else {
						//cout<<"分类失败！"<<endl;
						continue;
					}
				} else {
					//cout<<"set ROI failed!"<<endl;
					continue;
				}
			}
			
				
			if (led_on) {
				if ((((double)getTickCount()-tt)*1000./getTickFrequency()) > 5000) {
					led_on = false;
					cout<<"关灯 ！！！"<<endl;
				}
			}
			if (led_on) {
				ellipse(frame, Point(600,40), Size(20, 20), 0, 0, 360, Scalar(0, 0, 255), -1);	
			} else { 
				ellipse(frame, Point(600,40), Size(20, 20), 0, 0, 360, Scalar(255, 0, 0), -1);
			}

#if VIDEO_SAVE 
			show_image_inwindow("video0", frame, graimg, fgmask,noseSuppressionImg, oVideoWriter);
#else
			show_image_inwindow("video0", frame, graimg, fgmask,noseSuppressionImg);
#endif
		}
		char k = (char)waitKey(30);
		if(k == 27) 
			stop = true;
		time = (double)getTickCount() - time; 
		//cout<<"one frame cost "<<time*1000./getTickFrequency()<<"ms"<<endl;
	}

	selobj.release();

	return 0;
}

