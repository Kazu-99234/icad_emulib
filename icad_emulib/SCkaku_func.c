#include <math.h>

#define	PAI_D	180.0
#define	PAI_2D	360.0
#define	PAI_R	3.141592653589794
#define	PAI_2R	6.28318530717958647
//#define	EPS		1.0e-3
#define	EPS		1.0e-5


/*********************************************************************
�֐���
	float	CNV_SC2Degree
�֐��T�v
	SC�p�x��x(DEGREE)�֕ϊ�����(slscdg_)
��������
	int	isc		(i)	SC�p�x
�߂�l
	�x(DEGREE)
���ӎ���
	�Ȃ�
*********************************************************************/
float	CNV_SC2Degree(int isc)
{
	return (float)(((PAI_D / 2.0) / (256.0 * pow(2.0, 21))) * (float)(isc));
}
/*********************************************************************
�֐���
	float	CNV_SC2Radian
�֐��T�v
	SC�p�x��x(���W�A��)�֕ϊ�����(slscrd_)
��������
	int	isc		(i)	SC�p�x
�߂�l
	�x(���W�A��)
���ӎ���
	�Ȃ�
*********************************************************************/
float	CNV_SC2Radian(int isc)
{
	return (float)(((PAI_R / 2.0) / (256.0 * pow(2.0, 21))) *(float)(isc));
}
/*********************************************************************
�֐���
	int	CNV_Degree2SC
�֐��T�v
	�x(DEGREE)��SC�p�x�֕ϊ�����(sldgsc_)
��������
	float	deg		(i)	�x(DEGREE)
�߂�l
	SC�p�x
���ӎ���
	�Ȃ�
*********************************************************************/
int	CNV_Degree2SC(float deg)
{
	double degwk = fmod( deg, PAI_2D );
	if( fabs( degwk ) <= EPS )	degwk = 0.0;
	if( degwk < 0.0 )			degwk = degwk + PAI_2D;
	return (int)(((256.0 * 2.0 / PAI_D) * pow(2.0, 21)) * degwk);
}
/*********************************************************************
�֐���
	int	CNV_Radian2SC
�֐��T�v
	�x(���W�A��)��SC�p�x�֕ϊ�����(slrdsc_)
��������
	float	rad		(i)	�x(���W�A��)
�߂�l
	SC�p�x
���ӎ���
	�Ȃ�
*********************************************************************/
int	CNV_Radian2SC(float rad)
{
	double	radwk = fmod( rad, PAI_2R );
	if( fabs( radwk ) <= EPS )	radwk = 0.0;
	if( radwk < 0.0 )			radwk = radwk + PAI_2R;
	return (int)(((256.0 * 2.0 / PAI_R) * pow(2.0, 21)) * radwk);
}
