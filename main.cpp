#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include <cv.h>
#include <highgui.h>
#include <ctype.h>
#include "task.h"
#pragma comment(lib,"cv210.lib")
#pragma comment(lib,"cxcore210.lib")
#pragma comment(lib,"cvaux210.lib")
#pragma comment(lib,"highgui210.lib")

void main()
{

	IplImage *src , *dst ;

	//src = cvLoadImage ("sampleImage.jpg",CV_LOAD_IMAGE_ANYCOLOR); カラー版
	src = cvLoadImage ("check3.bmp",CV_LOAD_IMAGE_GRAYSCALE); // グレースケール版

	//dst = cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,3); //カラー版
	dst  = cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1); // グレースケール版
	
	cvNamedWindow ("Original Image", CV_WINDOW_AUTOSIZE);
	cvShowImage ("Original Image", src);
	cvWaitKey (0);	//どれかのキーが押されるまで停止

	two_values( src ,dst );
	raste_labeling( src , dst );

	cvNamedWindow ("Filtering Image", CV_WINDOW_AUTOSIZE);
	cvShowImage ("Filtering Image", dst);

	cvWaitKey (0);

	//確保した画像領域の開放、およびウィンドウを閉じる
	//cvDestroyWindow ("Original Image");	//ウィンドウを閉じる
	//cvDestroyWindow ("Filtering Image");//ウィンドウを閉じる
	cvDestroyAllWindows();					//両方ウィンドウを閉じる
	cvReleaseImage (&src);	//画像メモリを開放する
	cvReleaseImage (&dst);	//画像メモリを開放する
}