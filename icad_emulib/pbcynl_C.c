#include	<stdio.h>
#include	<string.h>
#include	<math.h>
#include	"ComHansub.h"


//**************************************************************************************
//* �֐����@�@:pbcynl_C
//* �T�v  �@�@:�����Ɠ_�̊֌W�𒲂ׂ�
//* �ڍ�  �@�@:
//* �����@�@�@:[I] �����̎n�_X���W
//* �@�@�@�@�@:[I] �����̎n�_Y���W
//* �@�@�@�@�@:[I] �����̏I�_X���W
//* �@�@�@�@�@:[I] �����̏I�_Y���W
//* �@�@�@�@�@:[I] ���ׂ�_��X���W
//* �@�@�@�@�@:[I] ���ׂ�_��Y���W
//* �@�@�@�@�@:[I] �덷
//* �@�@�@�@�@:[O] ����
//* �@�@�@�@�@:[O] ���ׂ�_�̎n�_����̋���
//* �߂�l�@�@:����
//* �쐬�ҁ@�@:2022/10/11 FXS ��
//* �X�V�ҁ@�@:20xx/xx/xx
//* �X�V���e�@:
//**************************************************************************************
void pbcynl_C(double d_xs,double d_ys,double d_xe,double d_ye,double d_x,double d_y,double d_gg,int *i_nh,double *d_r)
{
	double d_a = 0.0,
		   d_b = 0.0,
		   d_bct = 0.0,
		   d_length = 0.0,
		   d_d1 = 0.0,
		   d_d2 = 0.0,
		   // ==== R1911.9 = 2019/12/11 Alv.senoo �ėp�T�u���[�`���덷�Ή�
		   d_gosa = 0.0;

	d_gosa = d_gg;
	if (fabs(d_gg) < D_KIJUN) {
		d_gosa = D_KOYO_GOSA;
	}
	// ============== 2019/12/11 Alv.senoo �ėp�T�u���[�`���덷�Ή�

	*i_nh = 5;
	d_bct = (d_x - d_xs) * (d_xe - d_xs) + (d_y - d_ys) * (d_ye - d_ys);
	d_a = (d_x - d_xs) * (d_x - d_xs) + (d_y - d_ys) * (d_y - d_ys);
	d_b = (d_xe - d_xs) * (d_xe - d_xs) + (d_ye - d_ys) * (d_ye - d_ys);
	d_length = sqrt(d_a * d_b);
	*d_r = sqrt(d_a);

	d_d1 = sqrt(d_a) - sqrt(d_b);
	d_d1 = fabs(d_d1);

	d_d2 = d_bct - d_length;
	d_d2 = fabs(d_d2);
	//==== R1911.9 = 2019/12/11 Alv.senoo �ėp�T�u���[�`���덷�Ή�
	if (d_a < d_gosa) {
		*i_nh = 1;
	} else if (d_d1 < d_gosa && d_d2 < d_gosa) {
		*i_nh = 2;
	} else if (d_d2 < d_gosa) {
		if (d_a < d_b) {
			*i_nh = 0;
		} else {
			*i_nh = 3;
		}
	} else {
		d_bct = fabs(d_bct);
		d_d2 = fabs(d_bct - d_length);
		d_d2 = sqrt(d_d2);
		if (d_d2 < d_gosa) {
			*i_nh = 4;
		}
	}
	//============== 2019/12/11 Alv.senoo �ėp�T�u���[�`���덷�Ή�
	return;
	//DEBUG INIT , SUBTRACE
}