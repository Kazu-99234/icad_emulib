#include	<stdio.h>
#include	<string.h>
#include	<math.h>
#include	"ComHansub.h"

//**************************************************************************************
//* �֐����@�@:kjtcrs_C
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
//* �쐬�ҁ@�@:2022/09/21 FXS ��
//* �X�V�ҁ@�@:20xx/xx/xx
//* �X�V���e�@:
//**************************************************************************************
void kjtcrs_C(float f_x1,float f_y1,float f_x2,float f_y2,float f_x3,float f_y3,float f_x4,
	float f_y4,float *f_x,float *f_y,int *i_n,float f_gl) {
	int   i_errno1 = 0,
		  i_estop = 0,
		  i_eprint = 0,
		  i_trace1 = 0,
		  i_usexit = 0,
		  i_errno2 = 0;
	float f_a = 0.0f,
		  f_b = 0.0f,
		  f_c = 0.0f,
		  f_e = 0.0f,
		  f_f = 0.0f,
		  f_d = 0.0f,
		  f_xx = 0.0f,
		  f_ahen = 0.0f,
		  f_bhen = 0.0f,
		  f_ramd1 = 0.0f,
		  f_ramd2 = 0.0f,
		  f_amiu1 = 0.0f,
		  f_amiu2 = 0.0f,
		  f_csth = 0.0f;

	//  ERROR SET
	i_trace1 = 0;
	i_usexit = 0;
	i_estop = 1000;
	i_errno1 = 207;
	i_errno2 = 208;
	i_eprint = 1;
	// *** �d�v�r��݊����Ȃ������߂d�q�q�r�d�s���폜���� (H.3.1.9)
	// *** �i�v���O�����őΏ��j�@
	f_xx = f_gl;
	// ==== R1911.9 = 2019/12/10 Alv.hayashi �ėp�T�u���[�`���덷�Ή�
	if (fabsf(f_xx) < 0.001f) {
		f_xx = 0.001f;
	}
	//============== 2019/12/10 Alv.hayashi �ėp�T�u���[�`���덷�Ή�
	*i_n = 0;
	if (f_x1 - f_xx <= f_x2 && f_x1 + f_xx >= f_x2 && f_x3 - f_xx <= f_x4 && f_x3 + f_xx >= f_x4) {
		goto l_10;
	}
	if (f_y1 - f_xx <= f_y2 && f_y1 + f_xx >= f_y2 && f_y3 - f_xx <= f_y4 && f_y3 + f_xx >= f_y4) {
		goto l_10;
	}
	goto l_20;
l_10:
	*f_x = 0.0f;
	*f_y = 0.0f;
	*i_n = 2;
l_999:
	return;
l_20:
	if (f_x1 - f_xx <= f_x2 && f_x1 + f_xx >= f_x2) {
		goto l_30;
	}
	if (f_x3 - f_xx <= f_x4 && f_x3 + f_xx >= f_x4) {
		goto l_40;
	}
	if (f_y1 - f_xx <= f_y2 && f_y1 + f_xx >= f_y2) {
		goto l_50;
	}
	if (f_y3 - f_xx <= f_y4 && f_y3 + f_xx >= f_y4) {
		goto l_60;
	}
	goto l_70;
l_30:
	*f_x = f_x1;
	goto l_81;
l_40:
	*f_x = f_x3;
	goto l_80;
l_50:
	*f_y = f_y1;
	goto l_100;
l_60:
	*f_y = f_y3;
	goto l_101;
l_100:
	*f_x = (*f_y - f_y3) * (f_x4 - f_x3) / (f_y4 - f_y3) + f_x3;
	goto l_90;
l_101:
	*f_x = (*f_y - f_y1) * (f_x2 - f_x1) / (f_y2 - f_y1) + f_x1;
	goto l_90;
l_70:
	f_ahen = sqrtf((f_x1 - f_x2) * (f_x1 - f_x2) + (f_y1 - f_y2) * (f_y1 - f_y2));
	f_bhen = sqrtf((f_x3 - f_x4) * (f_x3 - f_x4) + (f_y3 - f_y4) * (f_y3 - f_y4));
	f_ramd1 = (f_x1 - f_x2) / f_ahen;
	f_ramd2 = (f_x3 - f_x4) / f_bhen;
	f_amiu1 = (f_y1 - f_y2) / f_ahen;
	f_amiu2 = (f_y3 - f_y4) / f_bhen;
	f_csth = fabsf(f_ramd1 * f_ramd2 + f_amiu1 * f_amiu2);
	if ((f_csth >= 1.0f - f_xx / 10.0f) && (f_csth <= 1.0f + f_xx / 10.0f)) {
		goto l_10;
	}
	f_a = (f_y3 - f_y1) * (f_x2 - f_x1) * (f_x4 - f_x3);
	f_b = f_x1 * (f_y2 - f_y1) * (f_x4 - f_x3);
	f_c = (f_y2 - f_y1) * (f_x4 - f_x3);
	f_d = (f_y4 - f_y3) * (f_x2 - f_x1);
	f_e = f_x3 * (f_y4 - f_y3) * (f_x2 - f_x1);
	f_f = (f_x4 - f_x3) * (f_y2 - f_y1) - (f_y4 - f_y3) * (f_x2 - f_x1);
	if (f_f >= -1.0E-8 && f_f <= 1.0E-8) {
		goto l_260;
	}
	*f_x = (f_a + f_b - f_e) / f_f;
	goto l_80;
l_260:
	*f_x = 0.;
	goto l_80;
l_80:
	*f_y = (*f_x - f_x1) * (f_y2 - f_y1) / (f_x2 - f_x1) + f_y1;
	goto l_90;
l_81:
	*f_y = (*f_x - f_x3) * (f_y4 - f_y3) / (f_x4 - f_x3) + f_y3;
l_90:
	if (((*f_x <= f_x2 + f_xx && *f_x >= f_x1 - f_xx) || (*f_x <= f_x1 + f_xx && *f_x >= f_x2 - f_xx)) && ((*f_x <= f_x4 + f_xx && *f_x >= f_x3 - f_xx) || (*f_x <= f_x3 + f_xx && *f_x >= f_x4 - f_xx))) {
		goto l_110;
	}
	goto l_999;
l_110:
	if (((*f_y <= f_y2 + f_xx && *f_y >= f_y1 - f_xx) || (*f_y <= f_y1 + f_xx && *f_y >= f_y2 - f_xx)) && ((*f_y <= f_y4 + f_xx && *f_y >= f_y3 - f_xx) || (*f_y <= f_y3 + f_xx && *f_y >= f_y4 - f_xx))) {
		*i_n = 1;
	}
	goto l_999;
}