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

void search( IplImage *src , int x , int y , int stamp);

Table **table;		//１画素ごとにラベルを格納
int stamp =0;		//ラベリングの型です。
int first = 10000;	//ラベリングを初期化するためにつかう

void search( IplImage *src , int x , int y ,int stamp)
{
		table[x][y].label = stamp;
		if( PIXEL( src , x+1 , y) == 0 && 0<=x+1 && x+1< src->width && 0<=y && y< src->height ){
			if( table[x+1][y].label == first  ){
				table[x+1][y].label = stamp;
				search( src , x+1 , y , stamp );
			}
		}
		if( PIXEL( src , x-1 , y) == 0 && 0<=x-1 && x-1 <src->width && 0<=y && y< src->height  ){
			if( table[x-1][y].label == first ){
				table[x-1][y].label = stamp;
				search( src , x-1 , y , stamp );
			}
		}
		if( PIXEL( src , x , y+1) == 0 && 0<=x && x< src->width && 0<=y+1 && y+1< src->height  ){
			if( table[x][y+1].label == first ){
				table[x][y+1].label = stamp;
				search( src , x , y+1 , stamp );
			}		
		}
		if( PIXEL( src , x , y-1) == 0 && 0<=x && x< src->width && 0<=y-1 && y-1< src->height  ){
			if( table[x][y-1].label == first ){
				table[x][y-1].label = stamp;
				search( src , x , y-1 , stamp );
			}		
		}
}


void raste_labeling( IplImage *src , IplImage *dst )
{
	//ラベル格納用配列
	table = (Table **)malloc( sizeof( Table) * src ->width );	
	for( int i=0; i<src->width; i++){
		table[i] = (Table *)malloc( sizeof(Table) * src->height );
	}
	//各画素におけるラベルを10000に初期化
	for(int k=0; k < src->height; k++){
		for( int i=0; i < src->width; i++){
			table[i][k].label = first;		
		}
	}

	for ( int y = 0 ; y < src->height ; y++ ){
		for ( int x = 0 ; x < src->width ; x++ ){
			if(  table[x][y].label == first && PIXEL(src,x,y) == 0 ){
				stamp++;
				printf("(%d,%d)=%d\n",x, y, stamp);
			}
			if(  table[x][y].label == first && PIXEL(src,x,y) == 0 ){
				search( src , x , y ,stamp);
			}else if( PIXEL( src , x , y) == 255){
				table[x][y].label = 255;
			}
			
		}
		
	}

	////色変え
	//for ( int y = 0 ; y < src->height ; y ++ ){
	//	for ( int x = 0 ; x < src->width ; x ++ ){
	//		int tmpr = PIXEL(src,x,y)  * table[x][y].label * 20 % 255;
	//		int tmpg = PIXEL(src,x,y)  * table[x][y].label * 40 % 255;
	//		int tmpb = PIXEL(src,x,y)  * table[x][y].label * 60 % 255;
	//		PIXEL_R(dst,x,y)=tmpb;
	//		PIXEL_G(dst,x,y)=tmpr;
	//		PIXEL_B(dst,x,y)=tmpg;
	//	}
	//}

	//白黒濃度変更
	for ( int y = 0 ; y < src->height ; y ++ ){
		for ( int x = 0 ; x < src->width ; x ++ ){
			if( table[x][y].label == 255){
				PIXEL( dst , x , y ) =  255  ;
			}else{
				PIXEL( dst , x , y ) =   table[x][y].label * 30 % 255;
			}
		}
	}


	for( int i=0; i<src->width; i++ ){
		free( table[i] );
	}
	free( table );
	
	cvCopy ( dst , src );

}