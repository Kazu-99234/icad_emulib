/*----------------------------------------*/
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
#define SIZE_61  61
#define SIZE_512 512
#define SIZE_1024 1024
#define SIZE_1000 1000

//ADD
#define SIZE_6 6
#define SIZE_7 7
#define SIZE_9 9
#define SIZE_10 10
#define SIZE_20 20
#define SIZE_30 30
#define SIZE_200 200
#define SIZE_300 300
#define SIZE_101  101
#define SIZE_201  201
#define SIZE_600 600
#define SIZE_2000 2000
#define SIZE_4000 4000

/*----------------------------------------*/
/*円周率                                  */
/*----------------------------------------*/
#define  M_PAI  3.141592654				/* 円周率 */
#define  M_RAD  (3.141592654/180.0)		/* ラジアン値 */

/*----------------------------------------*/
/*誤差          　　　　　　    　       */
/*----------------------------------------*/
#define  F_KIJUN  0.0001f				/* 誤差を設定する基準値(float) */
//#define  D_KIJUN  0.0001d0				/* 誤差を設定する基準値(double) */
#define  D_KIJUN  1.0e-4				/* 誤差を設定する基準値(double) */

/*----------------------------------------*/
/*許容誤差      　　　　　　    　       */
/*----------------------------------------*/
#define  F_KOYO_GOSA  0.8f				/* 許容誤差(float) */
#define  D_KOYO_GOSA  8.0e-1			/* 許容誤差(double) */

/*----------------------------------------*/
/*許容誤差(角度)     　　　　    　       */
/*----------------------------------------*/
#define  F_KOYO_ANG  0.003f				/* 許容誤差（角度）(float) */
#define  D_KOYO_ANG  3.0e-3				/* 許容誤差（角度）(double) */


/*----------------------------------------*/
/*配列インデックス                         */
/*----------------------------------------*/
#define IDX_ST 0
#define DEBUG_TYPE		1
#define DEBUG_LEVEL		0

/*----------------------------------------*/
/*汎用サブルーチン誤差対応                */
/*----------------------------------------*/
#define GI_MAX_HZZMEN		201
#define GI_MAX_HZZMEN_LXY	100
/* ログを出力させる場合は以下のコメントをはずす */
//#define DEBUGLOG_MODE 1

/*----------------------------------------*/
/*関数プロトタイプ宣言                    */
/*----------------------------------------*/
extern "C" int Hansub();
extern "C" void pbryok_C(int *,double ,double ,double ,double ,double ,double );
extern "C" void pbcsn2_C(int[SIZE_4][SIZE_2], int *);
//extern "C" void pbcsn2_C(int[SIZE_2][SIZE_4],int *);
extern "C" void pbcynl_C(double ,double ,double ,double ,double ,double ,double ,int *,double *);
extern "C" void point_C(float [][SIZE_2],int ,float ,float ,int *,float );
extern "C" void round2_C(int ,float [][SIZE_2]);
extern "C" void pbccut_C(float [][SIZE_2],int ,float [][SIZE_4],int ,int *,int ,float ,float );
extern "C" void pbscut_C(float [][SIZE_4],int ,float [][SIZE_4],int ,int *,int ,float );
extern "C" void rbscut_C(float [][SIZE_4],int ,float [][SIZE_4],int ,int *,int ,float );
extern "C" void pbchsn_C(float ,float ,float ,float ,float ,float ,float *,float *,float *);
extern "C" void kjtcrs_C(float ,float ,float ,float ,float ,float ,float ,float ,float *,float *,int *,float );
extern "C" void djtcrs_C(double ,double ,double ,double ,double ,double ,double ,double ,double *,double *,int *,double );
extern "C" void pbccr3_C(double ,double ,double ,double ,double ,double ,double ,double ,double ,double ,double ,double ,double *,double *,double *,double *,double *,double *,double *,double ,int *);
extern "C" void hbcsn2_C(float[SIZE_4][SIZE_3],int *);
extern "C" void hbzgku_C(float ,float ,float ,float ,float ,float *,float *);
extern "C" void pbcstg_C(float [][SIZE_4],int *,float );
extern "C" int iiang_C(int ,int ,int ,int );
extern "C" int irang_C(float ,float ,float ,float );
extern "C" int idang_C(double ,double ,double ,double );
extern "C" int iikak_C(int ,int ,int ,int );
extern "C" int irkak_C(float ,float ,float ,float );
extern "C" int idkak_C(double ,double ,double ,double );
extern "C" int iilng_C(int ,int ,int ,int );
extern "C" int irlng_C(float ,float ,float ,float );
extern "C" int idlng_C(double ,double ,double ,double );
extern "C" void hbcynl_C(float ,float ,float ,float ,float ,float ,float ,float ,float ,float ,int *,float *);
extern "C" void dkcari_C(int [][SIZE_2],int ,int *);
extern "C" void dkcara_C(float [][SIZE_2],int ,float *);
extern "C" void dblara_C(double [][SIZE_2],int ,double *);
extern "C" void pbara3_C(float [][SIZE_3],int ,float *);
extern "C" void ebinou_C(float [][SIZE_2],int ,int *);
extern "C" void aasort_C(float *, int *, int ,int );
extern "C" void pbsort_C(int *, int, int, int,int, int *, int, int *);
extern "C" void hbbcr3_C(
	float , float , float , float , float , float , 
	float , float , float , float , float , float , 
	float *, float *, float *, float *, float *, float *,
	float *, float, int * );
extern "C" void pbcst2_C( float [][SIZE_4],int *, float );
extern "C" void rbcst2_C( float [][SIZE_4],int *, float );
extern "C" void pdkatn_C(
	float , float , float , 
	float , float , float , 
	float , float , float , 
	float [][SIZE_3], int , 
	float [][SIZE_3], int * );
extern "C" void delta3_C( int *, float [][SIZE_3], float );
extern "C" void pbcln2_C( int, float [][SIZE_2], float, float, float,  float [][SIZE_2]);
extern "C" void pbgetm_C( 	int [][SIZE_2], int , int [][SIZE_2], int , int *, int, int, int *, int *, int );
extern "C" void pbpg06_C( float , float , float , float , float[SIZE_2][SIZE_2], float[SIZE_2][SIZE_2], float[SIZE_4][SIZE_2] );
extern "C" void hbmima_C( float [][SIZE_3], int , float *, float *, float *, float *, float *, float * );
extern "C" void dkb002_C( float [][SIZE_2], int , float , float[][SIZE_2], int[][SIZE_2]);
extern "C" void mengo2_C( int , float[] [SIZE_2], int , float [][SIZE_2], int *, int *, int *,  float );
extern "C" void mengo3_C( float [][SIZE_2], int *, int *, int * );
extern "C" void ebeqmn_C( float [][SIZE_2], int, float [][SIZE_2], int,  int *, float );
extern "C" void hxzmen4_C(float [][SIZE_4], int, float [][SIZE_1000],int *, int *,int);
extern "C" void hxzmengo2_C(float [][SIZE_2], int *, int *, int );
extern "C" void rbcsn4_C(float [SIZE_4][SIZE_2],float ,int *);
extern "C" void round3_C(int ,float [][SIZE_2]);
extern "C" void jefcnv_C(int, char *, int *);
extern "C" void dksenp_C(int *, float[][SIZE_2], float);
extern "C" void hbcsn2n_C(float[SIZE_4][SIZE_3], int *, float );
extern "C" float rrlng_C(float rxs, float rys, float rxe, float rye);
extern "C" void hzzmnst2_C(float [][SIZE_1000], int *, int, int, int *, int *, int *, int);
extern "C" void mennuk_C(int, float[][SIZE_2], int, float[][SIZE_2], int *, int[10], int *, float);
extern "C" void pbctrm_C(int*, int, int, int *, int);
extern "C" void pbenu3_C(float[][SIZE_2], float[][SIZE_2], float[][SIZE_2], int, int, int, int *);
extern "C" void rbcsn2_C(float[SIZE_4][SIZE_2], int *);
extern "C" void rksen2_C(int *, float[][SIZE_2], float);
extern "C" void rbgetm_C(int[][SIZE_2], int, float[][SIZE_2], int, int *, int, int, int *, int *, int);
extern "C" void ebmynt_C(float [SIZE_3][SIZE_3], float *, float *, float *, float , float , int *);
extern "C" void ebmynv_C(float [SIZE_3][SIZE_3], float [SIZE_3][SIZE_3], float );
extern "C" void pbpg05_C(double [2][2], double , double , double , double , double [2][2]);
extern "C"  int irhok_C(float , float );
extern "C"  int idhok_C(double , double );
extern "C"  int iihok_C(int , int );
extern "C" void rbsrt2_C(float *, int , int , int [], int , int[]);
extern "C"  int iadd1_C(int, int);
extern "C" void pbsyok_C(int *, int , int , int , int , int *, int [], int i_nt);
extern "C"  int ireq_C(float , float , float );
extern "C"  int iieq_C(int, int, int);
extern "C"  int ideq_C(double , double , double );
extern "C" void pbcmt1_C(int , int , int [], int , int [], int *, int *, int , int );
extern "C" void hzzmen7_C(float[][SIZE_4], int, float[][SIZE_1000], int *, int *, int);

/* Step2 */
extern "C" void bandmt_C(float *,float [],float [], int , int, int, int,int,int);
extern "C" void delta1_C(int [SIZE_2][SIZE_100], float [SIZE_2][SIZE_100], float );
extern "C" void delta2_C(int *, float[][SIZE_2], float);
extern "C" void dkb001_C(float[][SIZE_2], int, float, float[][SIZE_2], int[][SIZE_2]);
extern "C" void dksen2_C(int *, float f_xp[][SIZE_2], float);
extern "C" float dround_C(double, int);
extern "C" void ebpsf0_C(double[SIZE_2][SIZE_2], double, double[SIZE_3], int *);
extern "C" void eefip2_C(double [SIZE_3], double [SIZE_3], double [SIZE_2], int *i_rcode);
extern "C" void hbcsn3_C(float[SIZE_4][SIZE_2], int *);
extern "C" void hbdak1_C(int, float, float, float, float[SIZE_3], float *, float *, float *);
extern "C" void hbdak2_C(int, float, float, float, float[SIZE_3], float *, float *, float *, int *, int);
extern "C" void hfyjik_C(double , double , double , double , double [][SIZE_3],double [][SIZE_3], int );
extern "C" void htdaka_C(float, float, float, float[SIZE_3], float , float , float *);
extern "C" void hvzpbenu2_C(float[][SIZE_2], float[][SIZE_2], float[][SIZE_2], int, int, int, int *, float);
extern "C" int iiketa_C(int );
extern "C" void hvzpbcmn_C(int, float[][SIZE_2], int, float[][SIZE_2], int* , float[][SIZE_2], int *, int *, float, int *, int);
extern "C" void hvzmengo_C(int, float[][SIZE_2], int, float[][SIZE_2], int *, int *, int *, float);
extern "C" void hvzmengo2_C(int, float[][SIZE_2], int, float[][SIZE_2], int *, int *, int *, float);
extern "C" void pbcynl2_C(double , double , double , double , double , double , double , int *, double *);
extern "C" void pbcyn3_C(double, double, double, double, double, double, double, double, double, double, int *, double *);
extern "C" int idcrs_C(double[SIZE_4][SIZE_2]);
extern "C" int iddak_C(double, double, double, double, double, double, double, double);
extern "C" void hvzpbscut_C(float [][SIZE_4], int , float [][SIZE_4], int , int *, int , float );
extern "C" void hzzmnsrt_C(float[SIZE_201][SIZE_1000], int *, int, int, int, int *, int);
extern "C" int iipos_C(float[][SIZE_2], int, int, int);
extern "C" int irpos_C(float[][SIZE_2], int, float, float);
extern "C" int idpos_C(float[][SIZE_2], int, double, double);
extern "C" int iicrs_C(int[SIZE_4][SIZE_2]);
extern "C" int ircrs_C(float[SIZE_4][SIZE_2]);
extern "C" int iidak_C(int, int, int, int, int, int, int, int);
extern "C" int irdak_C(float, float, float, float, float, float, float, float);
extern "C" int iround_C(int, int);
extern "C" void mengo1_C(int[SIZE_2][SIZE_100], int[SIZE_2][SIZE_100], float[SIZE_2][SIZE_100], float[SIZE_2][SIZE_100], float,int *, int *);
extern "C" void pbcad1_C(float, float, float, float, float, float *, float *);
extern "C" void pbcca2_C(int, float, float, float, float, float[][SIZE_2], int, float, float[][SIZE_4], int, int *, int *);
extern "C" void pbccat_C(int, float, float, float, float, float[][SIZE_2], int, float, float[][SIZE_4], int, int *, int *);
extern "C" void pbcct3_C(float[][SIZE_2], int, float[][SIZE_4], int, int *, int, float, float);
extern "C" void pbcmen_C(int, float[][SIZE_2], int, float[][SIZE_2], int , float[][SIZE_2], int *, int *, float);
extern "C" void pbcrln_C(float [SIZE_3], float [SIZE_2][SIZE_2], float [SIZE_2][SIZE_2], int *);
extern "C" void pbcsen_C(int [SIZE_4][SIZE_2], int *);
extern "C" void pbenu2_C(float[][SIZE_2], float[][SIZE_2], float[][SIZE_2], int, int, int, int *);
extern "C" void pbsct3_C(float [][SIZE_6], int , float [][SIZE_6], int , int *, int , float , float );
extern "C" void pdpetr_C(float [][SIZE_3], float [][SIZE_2], int , int , int , int *);
extern "C" void pdpont_C(float [][SIZE_3], int , float [SIZE_3], int *, float );
extern "C" void pdvect_C(float[SIZE_3][SIZE_3], float[SIZE_3], int *, int *);
extern "C" void pdvitr_C(float[][SIZE_3], float, float, float, float, float, float, int , int *);
extern "C" void poin2_C(float[][SIZE_2], int, float, float, int *, float);
extern "C" void point2_C(float[][SIZE_2], int, float, float, int *, float);
extern "C" void rbcsen_C(float [SIZE_4][SIZE_2], int *);
extern "C" void rbcst2b_C(float[][SIZE_4], int *, float);
extern "C" void rebeqmn_C(float[][SIZE_2], int, float[][SIZE_2], int, int *, float);
extern "C" void rmennuk_C(int, float[][SIZE_2], int, float[][SIZE_2], int *, int[10], int *, float);
extern "C" void rmennuk2_C(int, float[][SIZE_2], int, float[][SIZE_2], int *, int[10], int *, float);
extern "C" void round1_C(float [SIZE_2][SIZE_100], int [SIZE_2][SIZE_100]);
extern "C" float rrdak_C(float, float, float, float, float, float, float, float);
extern "C" float rround_C(float , int );

extern "C" void hbcktn_C(float , float , float , float , float , float ,
            float , float , float , float , float , float ,
            float *, float *,float *,float , int *, int *, int *);
extern "C" void hbvec1_C(float [][SIZE_3], int , float [SIZE_3], int *, int *);
extern "C" void htmgo1_C(int , float [][SIZE_3], int , float [][SIZE_3], int *, int [10], int *, float );
extern "C" void htmnu1_C(float [][SIZE_3], float [][SIZE_3], float [][SIZE_3],int , int , int  , int *);
extern "C" void mencut_C(float [][SIZE_2], float [][SIZE_2], float [][SIZE_2],int , int , int , int *);
extern "C" void pbcca3_C(int , float , float , float , float , float [][SIZE_2], int , float , float [][SIZE_4], int , int *, int *);
extern "C" void pbcct2_C(float [][SIZE_2], int , float [][SIZE_4], int ,int *, int ,  float  );
extern "C" void pbcct4_C(float [][SIZE_2], int , float [][SIZE_4], int,int *, int ,  float , float , float );
extern "C" void pbcct5_C(float [][SIZE_2], int , float [][SIZE_4],int ,int *, int ,  float , float , float );
extern "C" void pbcct6_C(int , float , float , float , float , float [][SIZE_2], int , float , float [][SIZE_4],
          int , int *, float , float ,int *);
extern "C" void pdcu11_C(float [][SIZE_3], int , float [3], float [3], float [][SIZE_3],int *, int *, float );
extern "C" void pdcu21_C(float [][SIZE_3], int , float [3], float [3], float [][SIZE_3],int *, int *, float );
extern "C" void pdcu31_C(float [][SIZE_3], int , float [][SIZE_3], int , float [][SIZE_3],int *, int *, float );
extern "C" void pdmg01_C(int , float [][SIZE_3], int , float [][SIZE_3], int *, int *, int *, float );
extern "C" void rbcsn3_C(float [SIZE_4][SIZE_3], int *);
extern "C" void rbcst3_C(float [][SIZE_6], int *, float );
extern "C" void htmgo3_C(float [][SIZE_2], int , int [10]);
extern "C" void eeccat_C(int , float , float , float , float ,	float [][SIZE_2], int , float , float [][SIZE_4], int , int *, int *);
extern "C" void eefip1_C(double [SIZE_2][SIZE_2], double [SIZE_2][SIZE_2], int ,	float , int *);
extern "C" void pdcut1_C(float[][SIZE_3], int, float[3], float[3], float[][SIZE_3], int *, int *);
extern "C" void pdcut2_C(float[][SIZE_3], int, float[3], float[3], float[][SIZE_3], int *, int *);
extern "C" void pdcut3_C(float[][SIZE_3], int, float[][SIZE_3], int, float[][SIZE_3], int *, int *);
extern "C" int isub1_C(int , int );
extern "C" int  irle_C(float , float , float );
extern "C" int  irgt_C(float, float, float);

