
/*----------------------------------------*/
/*インクルード宣言                        */
/*----------------------------------------*/
#include	<global_debuglog.h>

/*----------------------------------------*/
/*配列サイズ設定                           */
/*----------------------------------------*/
#define SIZE_2 2
#define SIZE_3 3
#define SIZE_4 4
#define SIZE_100 100
#define SIZE_100 100
#define SIZE_200 200
#define SIZE_300 300
#define SIZE_61  61
#define SIZE_201 201
#define SIZE_512 512
#define SIZE_1024 1024
#define SIZE_1000 1000

/*----------------------------------------*/
/*配列インデックス                         */
/*----------------------------------------*/
#define IDX_ST 0
#define DEBUG_TYPE		1
#define DEBUG_LEVEL		0
/* ログを出力させる場合は以下のコメントをはずす */
//#define DEBUGLOG_MODE 1

/*----------------------------------------*/
/*関数プロトタイプ宣言                    */
/*----------------------------------------*/
extern "C" int Hansub();
extern "C" void pbryok(int *,double ,double ,double ,double ,double ,double );
extern "C" void pbcsn2(int [SIZE_2][SIZE_4],int *);
extern "C" void pbcynl(double ,double ,double ,double ,double ,double ,double ,int *,double *);
extern "C" void point(float [SIZE_2][SIZE_100],int ,float ,float ,int *,float );
extern "C" void round2(int ,float [SIZE_2][SIZE_100]);
extern "C" void pbccut(float [][SIZE_100],int ,float [][SIZE_100],int ,int *,int ,float ,float );
extern "C" void pbscut(float [][SIZE_100],int ,float [][SIZE_100],int ,int *,int ,float );
extern "C" void rbscut(float [][SIZE_100],int ,float [][SIZE_100],int ,int *,int ,float );
extern "C" void pbchsn(float ,float ,float ,float ,float ,float ,float *,float *,float *);
extern "C" void kjtcrs(float ,float ,float ,float ,float ,float ,float ,float ,float *,float *,int *,float );
extern "C" void djtcrs(double ,double ,double ,double ,double ,double ,double ,double ,double *,double *,int *,double );
extern "C" void pbccr3(double ,double ,double ,double ,double ,double ,double ,double ,double ,double ,double ,double ,double *,double *,double *,double *,double *,double *,double *,double ,int *);
extern "C" void hbcsn2(float [SIZE_3][SIZE_4],int *);
extern "C" void hbzgku(float ,float ,float ,float ,float ,float *,float *);
extern "C" void pbcstg(float [SIZE_4][SIZE_100],int *,float );
extern "C" int iiang(int ,int ,int ,int );
extern "C" int irang(float ,float ,float ,float );
extern "C" int idang(double ,double ,double ,double );
extern "C" int iikak(int ,int ,int ,int );
extern "C" int irkak(float ,float ,float ,float );
extern "C" int idkak(double ,double ,double ,double );
extern "C" int iilng(int ,int ,int ,int );
extern "C" int irlng(float ,float ,float ,float );
extern "C" int idlng(double ,double ,double ,double );
extern "C" void hbcynl(float ,float ,float ,float ,float ,float ,float ,float ,float ,float ,int *,float *);
extern "C" void dkcari(int [SIZE_2][SIZE_100],int ,int *);
extern "C" void dkcara(float [SIZE_2][SIZE_100],int ,float *);
extern "C" void dblara(double [SIZE_2][SIZE_100],int ,double *);
extern "C" void pbara3(float [SIZE_3][SIZE_100],int ,float *);
extern "C" void ebinou(float [SIZE_3][SIZE_100],int ,int *);
extern "C" void aasort(float *, int *, int ,int );
extern "C" void pbsort(int [SIZE_100][SIZE_100], int, int, int,int, int *, int, int * );
extern "C" void hbbcr3(
	float , float , float , float , float , float , 
	float , float , float , float , float , float , 
	float *, float *, float *, float *, float *, float *,
	float *, float, int * );
extern "C" void pbcst2( float [SIZE_4][SIZE_100],int *, float );
extern "C" void pbcst3( float [SIZE_4][SIZE_1024],int *, float );
extern "C" void rbcst2( float [SIZE_4][SIZE_100],int *, float );
extern "C" void pdkatn(
	float , float , float , 
	float , float , float , 
	float , float , float , 
	float [SIZE_3][SIZE_100], int , 
	float [SIZE_3][SIZE_100], int * );
extern "C" void delta3( int *, float [SIZE_3][SIZE_100], float );
extern "C" void pbcln2( int, float [SIZE_2][SIZE_100], float, float, float,  float [SIZE_2][SIZE_100]);
extern "C" void pbgetm( 
	int [SIZE_2][SIZE_100], int , int [SIZE_2][SIZE_100], int , 
	int [SIZE_100][SIZE_100], int *, int *, int *, int *, int );
extern "C" void pbpg06( float , float , float , float , float[SIZE_2][SIZE_2], float[SIZE_2][SIZE_2], float[SIZE_2][SIZE_4] );
extern "C" void hbmima( float [SIZE_3][SIZE_100], int , float *, float *, float *, float *, float *, float * );
extern "C" void dkb002( float [SIZE_2][SIZE_100], int , float , float [SIZE_2][SIZE_100], int[SIZE_2][SIZE_100] );
extern "C" void mengo2( int , float [SIZE_2][SIZE_100], int , float [SIZE_2][SIZE_100], int *, int *, int *,  float );
extern "C" void mengo3( float [SIZE_2][SIZE_100], int *, int *, int * );
extern "C" void ebeqmn( float [SIZE_2][SIZE_100], int, float [SIZE_2][SIZE_100], int,  int *, float );
extern "C" void hxzmen4(float [][SIZE_100], int, float [][SIZE_61],int *, int *,int);
extern "C" void hxzmen7(float [][SIZE_1024], int, float [][SIZE_201],int *, int *,int);
extern "C" void hxzmengo(float [][SIZE_100], int *, int *, int );
extern "C" void rbcsn4(float [SIZE_3][SIZE_4],float ,int *);
extern "C" void round3(int ,float [SIZE_2][SIZE_100]);
extern "C" void jefcnv(int, char *, int *);
