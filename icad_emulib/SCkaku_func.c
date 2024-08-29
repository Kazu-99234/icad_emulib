#include <math.h>

#define	PAI_D	180.0
#define	PAI_2D	360.0
#define	PAI_R	3.141592653589794
#define	PAI_2R	6.28318530717958647
//#define	EPS		1.0e-3
#define	EPS		1.0e-5


/*********************************************************************
関数名
	float	CNV_SC2Degree
関数概要
	SC角度を度(DEGREE)へ変換する(slscdg_)
引数説明
	int	isc		(i)	SC角度
戻り値
	度(DEGREE)
注意事項
	なし
*********************************************************************/
float	CNV_SC2Degree(int isc)
{
	return (float)(((PAI_D / 2.0) / (256.0 * pow(2.0, 21))) * (float)(isc));
}
/*********************************************************************
関数名
	float	CNV_SC2Radian
関数概要
	SC角度を度(ラジアン)へ変換する(slscrd_)
引数説明
	int	isc		(i)	SC角度
戻り値
	度(ラジアン)
注意事項
	なし
*********************************************************************/
float	CNV_SC2Radian(int isc)
{
	return (float)(((PAI_R / 2.0) / (256.0 * pow(2.0, 21))) *(float)(isc));
}
/*********************************************************************
関数名
	int	CNV_Degree2SC
関数概要
	度(DEGREE)をSC角度へ変換する(sldgsc_)
引数説明
	float	deg		(i)	度(DEGREE)
戻り値
	SC角度
注意事項
	なし
*********************************************************************/
int	CNV_Degree2SC(float deg)
{
	double degwk = fmod( deg, PAI_2D );
	if( fabs( degwk ) <= EPS )	degwk = 0.0;
	if( degwk < 0.0 )			degwk = degwk + PAI_2D;
	return (int)(((256.0 * 2.0 / PAI_D) * pow(2.0, 21)) * degwk);
}
/*********************************************************************
関数名
	int	CNV_Radian2SC
関数概要
	度(ラジアン)をSC角度へ変換する(slrdsc_)
引数説明
	float	rad		(i)	度(ラジアン)
戻り値
	SC角度
注意事項
	なし
*********************************************************************/
int	CNV_Radian2SC(float rad)
{
	double	radwk = fmod( rad, PAI_2R );
	if( fabs( radwk ) <= EPS )	radwk = 0.0;
	if( radwk < 0.0 )			radwk = radwk + PAI_2R;
	return (int)(((256.0 * 2.0 / PAI_R) * pow(2.0, 21)) * radwk);
}
