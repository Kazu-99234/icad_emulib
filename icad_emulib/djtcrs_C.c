#include	<stdio.h>
#include	<string.h>
#include	<math.h>
#include	"ComHansub.h"


//**************************************************************************************
//* �֐����@�@:djtcrs_C
//* �T�v  �@�@:�Q�����̌�_�����߂�
//* �ڍ�  �@�@:
//* �����@�@�@:[I] �������̎n�_X���W
//* �@�@�@�@�@:[I] �������̎n�_Y���W
//* �@�@�@�@�@:[I] �������̏I�_X���W
//* �@�@�@�@�@:[I] �������̏I�_Y���W
//* �@�@�@�@�@:[I] �������̎n�_X���W
//* �@�@�@�@�@:[I] �������̎n�_Y���W
//* �@�@�@�@�@:[I] �������̏I�_X���W
//* �@�@�@�@�@:[I] �������̏I�_Y���W
//* �@�@�@�@�@:[O] ��_��X���W
//* �@�@�@�@�@:[O] ��_��Y���W
//* �@�@�@�@�@:[O] �����̌������
//* �@�@�@�@�@:[I] �덷
//* �߂�l�@�@:����
//* �쐬�ҁ@�@:2022/10/11 FXS ��
//* �X�V�ҁ@�@:20xx/xx/xx
//* �X�V���e�@:
//**************************************************************************************
void djtcrs_C(double d_x1,double d_y1,double d_x2,double d_y2,double d_x3,double d_y3,double d_x4,double d_y4,double *d_x,double *d_y,int *i_n,double d_d)
{
		   //     �޲���� kjtcrs
		   //     x1 - x4    input   x - zahyo
		   //     y1 - y4    input   y - zahyo
		   //     x : output  x - zahyo
		   //     y : output  y - zahyo
		   //     n : (0 or 1 or 2)
		   // ==== R1911.9 = 2019/12/10 Alv.shin �ėp�T�u���[�`���덷�Ή�
	double d_xx = 0.0,
		   // ============== 2019/12/10 Alv.shin �ėp�T�u���[�`���덷�Ή�
		   d_ahen = 0.0,
		   d_bhen = 0.0,
		   d_ramd1 = 0.0,
		   d_ramd2 = 0.0,
		   d_amiu1 = 0.0,
		   d_amiu2 = 0.0,
		   d_csth = 0.0,
		   d_a = 0.0,
		   d_b = 0.0,
		   d_c = 0.0,
		   d_e = 0.0,
		   d_f = 0.0,
		   d_g = 0.0;
	int   l_errno1 = 0,
		   l_estop = 0,
		   l_eprint = 0,
		   l_trace1 = 0,
		   l_usexit = 0,
		   l_errno2 = 0;

	//==== R1911.9 = 2019/12/10 Alv.shin �ėp�T�u���[�`���덷�Ή�
	d_xx = d_d;
	if (fabs(d_xx) < D_KIJUN){
		d_xx = D_KOYO_GOSA;
	}
	// ============== 2019/12/10 Alv.shin �ėp�T�u���[�`���덷�Ή�
	//  error set
	l_trace1 = 0;
	l_usexit = 0;
	l_estop = 1000;
	l_errno1 = 207;
	l_errno2 = 208;
	l_eprint = 1;
	// *** �d�v�r��݊����Ȃ������߂d�q�q�r�d�s���폜���� (h.3.1.9)
	// *** �i�v���O�����őΏ�)
	// ==== R1911.9 = 2019/12/10 Alv.shin �ėp�T�u���[�`���덷�Ή�
	//      xx=gl
	// ============== 2019/12/10 Alv.shin �ėp�T�u���[�`���덷�Ή�
	*i_n = 0;
	if (d_x1 - d_xx <= d_x2 && d_x1 + d_xx >= d_x2 && d_x3 - d_xx <= d_x4 && d_x3 + d_xx >= d_x4) {
		goto l_10;
	}
	if (d_y1 - d_xx <= d_y2 && d_y1 + d_xx >= d_y2 && d_y3 - d_xx <= d_y4 && d_y3 + d_xx >= d_y4) {
		goto l_10;
	}
	goto l_20;

l_10:
		*d_x = 0.0;
		*d_y = 0.0;
		*i_n = 2;
l_999 :
		return;
l_20:
	if (d_x1 - d_xx <= d_x2&&d_x1 + d_xx >= d_x2) {
		goto l_30;
	}
	if (d_x3 - d_xx <= d_x4&&d_x3 + d_xx >= d_x4) {
		goto l_40;
	}
	if (d_y1 - d_xx <= d_y2&&d_y1 + d_xx >= d_y2) {
		goto l_50;
	}
	if (d_y3 - d_xx <= d_y4&&d_y3 + d_xx >= d_y4) {
		goto l_60;
	}
	goto l_70;
l_30:
	*d_x = d_x1;
	goto l_81;
l_40:
	*d_x = d_x3;
	goto l_80;
l_50:
	*d_y = d_y1;
	goto l_100;
l_60:
	*d_y = d_y3;
	goto l_101;
l_100:
	*d_x = (*d_y - d_y3) * (d_x4 - d_x3) / (d_y4 - d_y3) + d_x3;
	goto l_90;
l_101:
	*d_x = (*d_y - d_y1) * (d_x2 - d_x1) / (d_y2 - d_y1) + d_x1;
	goto l_90;
l_70:
	d_ahen = sqrt((d_x1 - d_x2) * (d_x1 - d_x2) + (d_y1 - d_y2) * (d_y1 - d_y2));
	d_bhen = sqrt((d_x3 - d_x4) * (d_x3 - d_x4) + (d_y3 - d_y4) * (d_y3 - d_y4));
	d_ramd1 = (d_x1 - d_x2) / d_ahen;
	d_ramd2 = (d_x3 - d_x4) / d_bhen;
	d_amiu1 = (d_y1 - d_y2) / d_ahen;
	d_amiu2 = (d_y3 - d_y4) / d_bhen;

	d_csth = fabs(d_ramd1 * d_ramd2 + d_amiu1 * d_amiu2);
	if (d_csth >= 1.0 - d_xx / 10.&&d_csth <= 1. + d_xx / 10.0){
		goto l_10;
	}

	d_a = (d_y3 - d_y1) * (d_x2 - d_x1) * (d_x4 - d_x3);
	d_b = d_x1 * (d_y2 - d_y1) * (d_x4 - d_x3);
	d_c = (d_y2 - d_y1) * (d_x4 - d_x3);
	d_g = (d_y4 - d_y3) * (d_x2 - d_x1);
	d_e = d_x3 * (d_y4 - d_y3) * (d_x2 - d_x1);
	d_f = (d_x4 - d_x3) * (d_y2 - d_y1) - (d_y4 - d_y3) * (d_x2 - d_x1);

	if (d_f >= -1.0e-8 && d_f <= 1.0e-8){
		goto l_260;
	}
	*d_x = (d_a + d_b - d_e) / d_f;
	goto l_80;

l_260:
	*d_x = 0.0;
	goto l_80;

l_80:
	*d_y = (*d_x - d_x1) * (d_y2 - d_y1) / (d_x2 - d_x1) + d_y1;
	goto l_90;
l_81:
	*d_y = (*d_x - d_x3) * (d_y4 - d_y3) / (d_x4 - d_x3) + d_y3;
l_90:
	if (((*d_x <= d_x2 + d_xx && *d_x >= d_x1 - d_xx) || (*d_x <= d_x1 + d_xx && *d_x >= d_x2 - d_xx))
		&& ((*d_x <= d_x4 + d_xx && *d_x >= d_x3 - d_xx) || (*d_x <= d_x3 + d_xx && *d_x >= d_x4 - d_xx))) {
		goto l_110;
	}
	goto l_999;
l_110:
	if (((*d_y <= d_y2 + d_xx && *d_y >= d_y1 - d_xx) || (*d_y <= d_y1 + d_xx && *d_y >= d_y2 - d_xx))
		&& ((*d_y <= d_y4 + d_xx && *d_y >= d_y3 - d_xx) || (*d_y <= d_y3 + d_xx && *d_y >= d_y4 - d_xx))){
		*i_n = 1;
	}
	goto l_999;
}