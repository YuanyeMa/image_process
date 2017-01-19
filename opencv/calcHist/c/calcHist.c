//#include "stdafx.h"
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

IplImage* DrawHistogram(CvHistogram* hist, float scaleX =2, float scaleY =2){
	float histMax =0;
	cvGetMinMaxHistValue(hist, 0, &histMax, 0);

	IplImage*imghist = cvCreateImage(cvSize(256*scaleX, 64*scaleY), 8, 1);
	cvZero(imghist);

	for( int i=0; i<255; i++){
		float histValue = cvQueryHistValue_1D(hist, i);
		float nextValue = cvQueryHistValue_1D(hist, i+1);

		CvPoint pt1 = cvPoint(i*scaleX, 64*scaleY);
		CvPoint pt2 = cvPoint((i+1)*scaleX, 64*scaleY);
		CvPoint pt3 = cvPoint((i+1)*scaleX, 64*scaleY-(nextValue/histMax)*64*scaleY);
		CvPoint pt4 = cvPoint(i*scaleX, 64*scaleY-(histValue/histMax)*64*scaleY);

		int numPts =5;
		CvPoint pts[5];
		pts[0] = pt1;
		pts[1] = pt2;
		pts[2] = pt3;
		pts[3] = pt4;
		pts[4] = pt1;

		cvFillConvexPoly(imghist,pts,numPts,cvScalar(255, 250, 0, 0));

	}
	return imghist;
}

int main(int argc, char* argv[])
{
	IplImage*src = cvLoadImage("/home/rechie/Pictures/6.jpg");

	cvNamedWindow("Src");
	cvShowImage("Src", src);

	int bins =1;
	int dims =1;
	int size = 256/bins;

	float range[] ={0, 255};
	float* ranges[] ={range};
	CvHistogram * hist = cvCreateHist(dims, &size, CV_HIST_ARRAY, ranges, 1);
	cvClearHist(hist);

	IplImage *imgRed = cvCreateImage(cvGetSize(src), 8, 1);
	IplImage *imgGreen = cvCreateImage(cvGetSize(src), 8, 1);
	IplImage *imgBlue = cvCreateImage(cvGetSize(src), 8, 1);

	cvSplit(src,imgBlue,imgGreen,imgRed,NULL);

	cvCalcHist(&imgBlue, hist, 0, 0);
	IplImage*histBlue = DrawHistogram(hist);
	cvClearHist(hist);
	cvNamedWindow("Blue");
	cvShowImage("Blue", histBlue);

	cvCalcHist(&imgGreen, hist, 0, 0);
	IplImage* histGreen = DrawHistogram(hist);
	cvClearHist(hist);
	cvNamedWindow("Green");
	cvShowImage("Green", histGreen);

	cvCalcHist(&imgRed, hist, 0, 0);
	IplImage* histRed = DrawHistogram(hist);
	cvClearHist(hist);
	cvNamedWindow("Red");
	cvShowImage("Red", histRed);

	cvWaitKey(0);
	cvDestroyAllWindows();
	return 0;
}
