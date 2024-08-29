#include	<stdio.h>
#include	<string.h>
#include	"ComHansub.h"
#include	<math.h>

//**************************************************************************************
//* �֐����@�@:round3_C
//* �T�v  �@�@:���p�`�̍��W�������ɕϊ�����
//* �ڍ�  �@�@:
//* �����@�@�@:[I] �ʂ��\�����钸�_�̐�
//* �@�@�@�@�@:[I/O] �ʂ̍��W
//* �߂�l�@�@:����
//* �쐬�ҁ@�@:2022/10/08 FXS ��
//* �X�V�ҁ@�@:20xx/xx/xx
//* �X�V���e�@:���݂͂̂̉��������|�C���^��悩��l���ɕύX(4/4)
//**************************************************************************************
 void round3_C(int i_n, float f_xp[][SIZE_2]) {
	//
	//     �� � ����� � з���� � ��
	//     N-- - �߲�� ��
	//     XP-- - �߲�� ���ֳ
	//
	int   i_i = 0,
		  i_a = 0,
		  i_b = 0,
		  i_j = 0,
		  i_l = 0;
	float f_zg = 0.0f,
		  f_zaa = 0.0f,
		  f_zbb = 0.0f,
		  f_az = 0.0f,
		  f_bz = 0.0f,
		  f_cz = 0.0f,
		  f_dz = 0.0f,
		  f_ez = 0.0f,
		  f_so = 0.0f,
		  f_co = 0.0f,
		  f_yo = 0.0f,
		  f_xw = 0.0f,
		  f_yw = 0.0f,
		  f_nn = 0.0f;

	// =====  MENTE 92.03.18 BY A.SUGIMOTO  =====
	if (i_n == 0) {
		goto l_900;
	}
	// ==========================================

	f_zg = f_xp[0][0];
	i_l = 1;
	for (i_i = 2; i_i <= i_n; i_i++) {
		if (f_zg <= f_xp[i_i - 1][0]) {
			goto l_10;
		}
		f_zg = f_xp[i_i - 1][0];
		i_l = i_i;
l_10:
		continue;
	}

	i_a = i_l + 1;
	if (i_l == i_n) {
		i_a = 1;
	}
	i_b = i_l - 1;
	if (i_l == 1) {
		i_b = i_n;
	}
	f_zaa = (f_xp[i_a - 1][0] + f_xp[i_b - 1][0]) / 2;
	f_zbb = (f_xp[i_a - 1][1] + f_xp[i_b - 1][1]) / 2;
	f_az = f_xp[i_a - 1][0];
	f_bz = f_xp[i_a - 1][1];
	f_cz = f_xp[i_l - 1][0];
	f_dz = f_xp[i_l - 1][1];
	f_ez = sqrtf((f_zbb - f_dz) * (f_zbb - f_dz) + (f_zaa - f_cz) * (f_zaa - f_cz));
	f_so = (f_zbb - f_dz) / f_ez;
	f_co = (f_zaa - f_cz) / f_ez;
	f_yo = f_co * (f_bz - f_dz) - f_so * (f_az - f_cz);
	if (f_yo < 0.0f) {
		return;
	}
	f_nn = (i_n + 1) / 2.0f;
	for (i_i = 2; i_i <= f_nn; i_i++) {
		i_j = i_n - i_i + 2;
		f_xw = f_xp[i_i - 1][0];
		f_yw = f_xp[i_i - 1][1];
		f_xp[i_i - 1][0] = f_xp[i_j - 1][0];
		f_xp[i_i - 1][1] = f_xp[i_j - 1][1];
		f_xp[i_j - 1][0] = f_xw;
		f_xp[i_j - 1][1] = f_yw;
	}

	// =====  MENTE 92.03.18 BY A.SUGIMOTO  =====
l_900:
	return;
	// ==========================================
}