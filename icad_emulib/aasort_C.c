#include	<stdio.h>

#include	"ComHansub.h"


//**************************************************************************************
//* �֐����@�@:aasort_C
//* �T�v  �@�@:�ꎟ���z����\�[�g����.
//* �ڍ�  �@�@:
//* �����@�@�@f_a:[I/O] �\�[�g�L�[
//* �@�@�@�@�@i_no:[O] �L�[�̔z��v�f
//* �@�@�@�@�@i_m:[i] �z��v�f��
//* �@�@�@�@�@i_kazu:[I] �\�[�g���ڐ�
//* �߂�l�@�@:����
//* �쐬�ҁ@�@:2022/09/21 FXS ��
//* �X�V�ҁ@�@:20xx/xx/xx 
//* �X�V���e�@:
//**************************************************************************************
void aasort_C( float *f_a, int *i_no, int i_m, int i_kazu )
{
	//*** BINARY CORE SORT
	//    A ; �-� �-
	//    NO; � - � ʲ�� ֳ�
	//    M; N0 � ʲ�� ֳ� ��
	// KAZU; � - � ��Ӹ ��
	int   i_i = 0,
		  i_l = 0,
		  i_lg = 0,
		  i_k = 0,
		  i_kk = 0,
		  i_ll = 0,
		  i_was = 0;
	float f_wac = 0.0f;

	for (i_kk = 1; i_kk <= i_m; i_kk++) {
		i_no[i_kk - 1] = i_kk;
	}
	if (i_kazu <= 1) {
		return;
	}
	i_l = i_kazu;
l_10:
	i_lg = i_l / 4;
	i_l = 2 * i_lg + 1;
	i_i = 1;

l_20:
	i_k = i_i;
	i_ll = i_i + i_l;
	f_wac = f_a[i_ll - 1];
	i_was = i_no[i_ll - 1];

l_30:
	if (f_wac < f_a[i_k - 1]) {
		goto l_40;
	}

l_50:
	i_ll = i_k + i_l;
	f_a[i_ll - 1] = f_wac;
	i_no[i_ll - 1] = i_was;
	i_i = i_i + 1;
	if ((i_i + i_l) <= i_kazu) {
		goto l_20;
	} 
	if (i_l == 1) {
		return;
	}
	goto l_10;

l_40:
	i_ll = i_k + i_l;
	f_a[i_ll - 1] = f_a[i_k - 1];
	i_no[i_ll - 1] = i_no[i_k - 1];
	i_k = i_k - i_l;
	if (i_k > 0) {
		goto l_30;
	}
	goto l_50;
}
