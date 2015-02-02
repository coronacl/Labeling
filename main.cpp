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

	//src = cvLoadImage ("sampleImage.jpg",CV_LOAD_IMAGE_ANYCOLOR); �J���[��
	src = cvLoadImage ("check3.bmp",CV_LOAD_IMAGE_GRAYSCALE); // �O���[�X�P�[����

	//dst = cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,3); //�J���[��
	dst  = cvCreateImage(cvSize(src->width,src->height),IPL_DEPTH_8U,1); // �O���[�X�P�[����
	
	cvNamedWindow ("Original Image", CV_WINDOW_AUTOSIZE);
	cvShowImage ("Original Image", src);
	cvWaitKey (0);	//�ǂꂩ�̃L�[���������܂Œ�~

	two_values( src ,dst );
	raste_labeling( src , dst );

	cvNamedWindow ("Filtering Image", CV_WINDOW_AUTOSIZE);
	cvShowImage ("Filtering Image", dst);

	cvWaitKey (0);

	//�m�ۂ����摜�̈�̊J���A����уE�B���h�E�����
	//cvDestroyWindow ("Original Image");	//�E�B���h�E�����
	//cvDestroyWindow ("Filtering Image");//�E�B���h�E�����
	cvDestroyAllWindows();					//�����E�B���h�E�����
	cvReleaseImage (&src);	//�摜���������J������
	cvReleaseImage (&dst);	//�摜���������J������
}