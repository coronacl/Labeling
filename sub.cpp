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



void swap( Box *x , Box *y)
{
	Box temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void b_sort( Box *box , int n )
{
	int k = n - 1;
	while( k >= 0 ){
		int i , j;
		for( i = 1 , j = -1; i <= k; i++ ){
			if( box[i-1].sigma > box[i].sigma ){
				j = i - 1;
				swap( &box[i] , &box[j] );
			}
		}
		k = j;
	}
}

//クラス間分散
double var(double m1 , double m2 , double w1 , double w2 )		//平均１、平均２、分散１、分散２
{
	double sigma2;		//ただし、二乗してるよ
		
	sigma2 = w1 * w2 * (m1 - m2) * (m1 - m2) / (w1 + w2) / (w1 + w2);

	return( sigma2 );
}

void two_values( IplImage *src , IplImage *dst )
{
	int *histogram = (int *)malloc( sizeof(int) * 256 );	//ヒストグラム作成用配列
	for(int i=0; i<=255; i++){
		histogram[i] = 0;
	}

	for ( int y = 0 ; y < src->height ; y++ ){
		for ( int x = 0 ; x < src->width ; x++ ){

			//ヒストグラム上において、各値に振り分けるため
			for(int i = 0 ; i <= 255 ; i++){
				if( PIXEL( src , x , y ) == i ){
					histogram[i] = histogram[i]+1; 
				}
			}

		}
	}
	//しきい値を求める
	int threshold=0;		//しきい値を適当に仮定する(0～255)
	Box box[256];		//しきい値とクラス間分散を入れる
	for( int threshold = 0; threshold <= 255 ; threshold++ ){

		double w1=0.0 , w2=0.0 , m1=0.0 , m2=0.0 ;

		for( int i =0; i <= threshold-1 ; i++){
			w1 += (double)histogram[i];
		}
		for( int i = threshold+1; i <= 255 ; i++){
			w2 += (double)histogram[i];
		}
		
		int sum1 = 0;
		for( int i = 0 ; i <= threshold-1; i++){
			sum1 += i * histogram[i];
		}
		if( w1 != 0){
			m1 = sum1 / w1;
		}

		int sum2 = 0;
		for( int i = threshold+1 ; i <= 255; i++){
			sum2 +=  i * histogram[i];
		}
		if( w2 != 0){
			m2 = sum2 / w2;
		}
			
		
		box[threshold].t = threshold;
		box[threshold].sigma = var( m1 , m2 , w1 , w2 );
	}

	b_sort( box , 256 );
	threshold = box[255].t ;

	//画素値、しきい値、そのときのクラス間分散を表示します
	//for( int i = 0 ; i <= 255; i++){
	//	printf("histogram[%d] =%d\n",i,histogram[i]);
	//	printf("box[%d] = %d , %lf\n",i,box[i].t,box[i].sigma);
	//}
	//printf("threthhold = %d " , threshold );

	for ( int y = 0 ; y < src->height ; y++ ){
		for ( int x = 0 ; x < src->width ; x++ ){
			if( 0 <= PIXEL( src , x , y ) && PIXEL( src , x , y ) < threshold ){
				PIXEL( dst , x , y ) = 0;
			}else if( threshold < PIXEL( src , x , y ) && PIXEL( src , x , y ) <= 255 ){
				PIXEL( dst , x , y ) = 255;
			}

		}
	}
	free( histogram );
	cvCopy ( dst , src );

}