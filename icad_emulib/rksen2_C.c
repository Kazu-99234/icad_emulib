#include	<stdio.h>
#include	<string.h>
#include	<math.h>
#include	<stdlib.h>
#include	"ComHansub.h"

//**************************************************************************************
//* �֐����@�@:rksen2_C
//* �T�v  �@�@:�̈�̍��W����  ������ɂ���_���폜����
//* �����@�@�@:[I/O] ���W��
//* �@�@�@�@�@:[I/O] ���W�e�[�u��
//* �@�@�@�@�@:[I] �덷
//* �߂�l�@�@:����
//* �쐬�ҁ@�@:2022/09/23 FXS ��
//* �X�V�ҁ@�@:20xx/xx/xx
//* �X�V���e�@:
//**************************************************************************************
void rksen2_C(int *i_cnt, float f_pos[][SIZE_2], float f_rgosa)
{
	// ==== R1911.9 = 2019/12/11 Alv.senoo �ėp�T�u���[�`���덷�Ή�
	// ============== 2019/12/11 Alv.senoo �ėp�T�u���[�`���덷�Ή�
	int    i_i = 0,
		   i_i1 = 0,
		   i_kcnt = 0,
		   i_nha = 0,
		   i_icnt1 = 0;
	float  f_r_gosa = 0.0f,
		   (*f_rpos)[SIZE_2];
	double d_dxs = 0.0,
		   d_dys = 0.0,
		   d_dxe = 0.0,
		   d_dye = 0.0,
		   d_dx = 0.0,
		   d_dy = 0.0,
		   d_dr = 0.0;
	double dgosa;

	f_rpos = NULL;
	if ((f_rpos = (float(*)[SIZE_2])malloc(sizeof(float)* (*i_cnt) * 2)) == NULL) {
		goto l_end;
	}

	memset(f_rpos, 0, sizeof(float)* (*i_cnt) * 2);

	// ==== R1911.9 = 2019/12/11 Alv.senoo �ėp�T�u���[�`���덷�Ή�
	f_r_gosa = f_rgosa;
	if (fabsf(f_rgosa) < F_KIJUN) {
		f_r_gosa = F_KOYO_GOSA;
	}
	// ============== 2019/12/11 Alv.senoo �ėp�T�u���[�`���덷�Ή�
	// **********************************************
	// *   �����J�n
	// **********************************************
	//
	for (i_i = 1; i_i <= *i_cnt; i_i++) {
		f_rpos[i_i - 1][0] = f_pos[i_i - 1][0];
		f_rpos[i_i - 1][1] = f_pos[i_i - 1][1];
	}

	i_icnt1 = *i_cnt;
	for (i_i = 2; i_i <= *i_cnt; i_i++) {
		if (i_i > i_icnt1) {
			break;
		}
		if (ireq_C(f_rpos[0][0], f_rpos[i_i - 1][0], 0.1f) == 1
		 && ireq_C(f_rpos[0][1], f_rpos[i_i - 1][1], 0.1f) == 1) {
			i_icnt1 = i_icnt1 - 1;
			for (i_i1 = i_i; i_i1 <= i_icnt1; i_i1++) {
				f_rpos[i_i1 - 1][0] = f_rpos[i_i1][0];
				f_rpos[i_i1 - 1][1] = f_rpos[i_i1][1];
			}
		}
	}

	f_pos[0][0] = f_rpos[0][0];
	f_pos[0][1] = f_rpos[0][1];
	i_kcnt = 1;

	for (i_i1 = 1; i_i1 <= i_icnt1; i_i1++) {
		i_i = i_i1 % i_icnt1 + 1;
		if (i_kcnt == 1) {
			d_dxs = f_rpos[i_icnt1 - 1][0];
			d_dys = f_rpos[i_icnt1 - 1][1];
		} else {
			// = R1307.0 sato = 2013/07/08  �����P
			//   R1307.0  �C��
			d_dxs = f_pos[i_kcnt - 2][0];
			d_dys = f_pos[i_kcnt - 2][1];
			// ================ 2013/07/08
		}
		d_dxe = f_pos[i_kcnt - 1][0];
		d_dye = f_pos[i_kcnt - 1][1];
		d_dx = f_rpos[i_i - 1][0];
		d_dy = f_rpos[i_i - 1][1];
		// ==== R1911.9 = 2019/12/11 Alv.senoo �ėp�T�u���[�`���덷�Ή�
		dgosa = f_r_gosa;
//		pbcynl_C(d_dxs, d_dys, d_dxe, d_dye, d_dx, d_dy, double(f_r_gosa), &i_nha, &d_dr);
		pbcynl_C(d_dxs, d_dys, d_dxe, d_dye, d_dx, d_dy, dgosa, &i_nha, &d_dr);
		// ============== 2019/12/11 Alv.senoo �ėp�T�u���[�`���덷�Ή�
		if (i_i != 1) {
			if (i_nha == 5) {
				i_kcnt = i_kcnt + 1;
				f_pos[i_kcnt - 1][0] = f_rpos[i_i - 1][0];
				f_pos[i_kcnt - 1][1] = f_rpos[i_i - 1][1];
			} else if (i_nha == 3) {
				f_pos[i_kcnt - 1][0] = f_rpos[i_i - 1][0];
				f_pos[i_kcnt - 1][1] = f_rpos[i_i - 1][1];
			}
		} else if (i_i == 1 && i_nha == 3) {
			i_kcnt = i_kcnt - 1;
		}
	}
	*i_cnt = i_kcnt;
	//
	//	 **********************************************
	//	 *   �I��
	//	 **********************************************
	//
l_end:
	if (f_rpos == NULL) {
		free(f_rpos);
	}
	return;
}