#ifndef INCLUDED_SUB
#define INCLUDED_SUB

//マクロ定義
#define PIXEL(p,x,y)	((unsigned char *)p->imageData)[p->widthStep*(y)+(x)]
#define PIXEL_R(p,x,y)	((unsigned char *)p->imageData)[p->widthStep*(y)+(x)*3+2]
#define PIXEL_G(p,x,y)	((unsigned char *)p->imageData)[p->widthStep*(y)+(x)*3+1]
#define PIXEL_B(p,x,y)	((unsigned char *)p->imageData)[p->widthStep*(y)+(x)*3]

struct Table{
	int label;			//ラベル番号を格納する
	int x;				
	int y;	
};

struct Box{

	int t;			//しきい値
	double sigma;	//クラス間分散
};

void swap( Box *x , Box *y);
void b_sort( Box *box , int n );
double var(double m1 , double m2 , double w1 , double w2 );
void two_values( IplImage *src , IplImage *dst );
void raste_labeling( IplImage *src , IplImage *dst );

#endif