#include <stdlib.h>
#include <memory.h>
#include <math.h>

#include "icad_emu.h"
#include "icad_emu_data.h"
#include "comhansub.h"

extern int CheckWin(double window[4], int vsno, struct  SegInfo *pSeg);

// serwin_
// �@�\		�w�肳�ꂽ2�����v�f�ɂ��ăE�C���h�E�������s���܂��B
// ����
// in	window[4]	�����ΏۂƂ���E�C���h�E��z��Ŏw�肵�܂�
// 					[ 0 ] �F �E�C���h�E�̍����_��X���W
// 					[ 1 ] �F �E�C���h�E�̍����_��Y���W
// 					[ 2 ] �F �E�C���h�E�̉E��_��X���W
// 					[ 3 ] �F �E�C���h�E�̉E��_��Y���W
// in	*vsno		��������VS�ԍ����w�肵�܂�
// in	actcls[32]	�����ΏۂƂ��郌�C�����ȉ��̌`���Ŏw�肵�܂�
// 					�����ΏۂƂ��郌�C���̃��C���ԍ��ɑΉ�����r�b�g��ON�ɂ��܂�
// in	acttyp[32]	�����ΏۂƂ���v�f�^�C�v���ȉ��̌`���Ŏw�肵�܂�
// 					�����ΏۂƂ���v�f�^�C�v�ԍ��ɑΉ�����r�b�g��ON�ɂ��܂�
// 					�^�C�v0�͎w�肳��Ă���������܂�
// in	*mode		�������[�h���w�肵�܂�
// 					0 �F �ȈՌ���
// 					1 �F �ڍ׌��� �����Ή�
// out	entlst[]	�������ꂽ�v�f�̃V�X�e�����ʔԍ��̕ԓ��̈�
// in	*size		entlst[]�̑傫�����w�肵�܂�
// out	*count		�������ꂽ�v�f�̌��̕ԓ��̈�
// out	*ircode		���A���

void serwin_(double window[4],int *vsno,char actcls[32],char acttyp[32],int *mode,int entlst[],int *size,int *count,int *ircode)
{
	int	i, j, ismax, icls, ityp, irc1, irc2, icnt;

	// �ȈՌ����̂�

	*ircode = 0;
	err_syosai = 0;


	*count = 0;
	icnt = 0;

	if (cur_mode != 0) {
		*ircode = 12;
		err_syosai = 100;
	}
	else {
		icls = ityp = 0;
		for (i = 0; i < 32; i++) {
			if (actcls[i] != 0x00) icls = 1;
			if (acttyp[i] != 0x00) ityp = 1;
		}
		if (icls == 0 || ityp == 0) {
			*ircode = 12;
			if (icls == 0)
				err_syosai = 3;
			else
				err_syosai = 4;
		}
		else {
			if (window[0] < window[2] && window[1] < window[3]) {

				for (i = 0; i < 500; i++) {
					if (VsInfodata[i].vsno == *vsno) break;
				}
				if (i == 500) {
					*ircode = 12;
					err_syosai = 2;
				}
				else {
					struct  SegInfo *pSeg = (struct  SegInfo *)	VsInfodata[i].pSeg;
					ismax = VsInfodata[i].iScount;

					for (j = 0; j < ismax; j++) {
					//	if (pSeg[j].isysno > 0 && pSeg[j].idel == 0) {
						if (pSeg[j].isysno != 0 && pSeg[j].idel == 0) {
							irc1 = ChkBit(actcls, pSeg[j].iclass);
							irc2 = ChkBit(acttyp, pSeg[j].itype);
							if (irc1 == 1 && irc2 == 1) {
								if (CheckWin(window, i, &pSeg[j]) == 1) {
									entlst[icnt] = pSeg[j].isysno;
									if ( pSeg[j].isegno > 0 ) entlst[icnt] = pSeg[j].isegno;
									icnt++;
								}
							}
						}
					}

				}
			}
			else {
				*ircode = 12;
				err_syosai = 1;
			}
		}

	}

	*count = icnt;

l_err:

	return;
	
}

int CheckWin(double window[4], int vsno, struct  SegInfo *pSeg)
{
	union pdata {
		int	i[1024];
		short	s[248];
		char	c[4096];
		double	d[512];
		float	f[1024];
	} *array;

	float farea[5][2], fline[10][4], fprm[5][2];

	int irc, i , ipmax;
	int	num;
	struct  PrmInfo *prm;


	irc = 0;

	farea[0][0] = window[0];
	farea[0][1] = window[1];
	farea[1][0] = window[0];
	farea[1][1] = window[3];
	farea[2][0] = window[2];
	farea[2][1] = window[3];
	farea[3][0] = window[2];
	farea[3][1] = window[1];
	farea[4][0] = -99999.0;
	farea[4][1] = -99999.0;

	ipmax = pSeg->ipcount;

	for (i = 0; i < ipmax; i++) {
		prm = &(pSeg->pprm[i]);
//		array = (union pdata *)(prm->pdata);
		array = VsInfodata[vsno].pPrm + prm->ioffset;

		if (prm->iptype == 1) {			// �_
			if (array->d[1] >= window[0] && array->d[1] <= window[2] &&
				array->d[2] >= window[1] && array->d[2] <= window[3]) {
				irc = 1;
				break;
			}
		}
		else if (prm->iptype == 2 ) {	// ��
			fline[0][0] = array->d[1];
			fline[0][1] = array->d[2];
			fline[0][2] = array->d[1] + array->d[5] * array->d[3];
			fline[0][3] = array->d[2] + array->d[5] * array->d[4];
			num = 1;
			pbccut_C(farea, 5, fline, 10, &num, 4, 0.001, F_KIJUN);
			if (num > 0) {
				irc = 1;
				break;
			}

		}
		else if (prm->iptype == 3) {	// �܂��
			int lcnt;
			float fx, fy;
			lcnt = (array->s[0] - 24) / 16;

			fx = array->d[1];
			fy = array->d[2];

			for (i = 0; i < lcnt; i++) {
				fline[0][0] = fx;
				fline[0][1] = fy;
				fx = fline[0][2] = array->d[1] + array->d[3 + i * 2];
				fy = fline[0][3] = array->d[2] + array->d[4 + i * 2];
				num = 1;
				
				pbccut_C(farea, 5, fline, 10, &num, 4, 0.001, F_KIJUN);
				if (num > 0) {
					irc = 1;
					break;
				}
			}
			if (irc == 1) break;

		}
		else if (prm->iptype == 4) {	// �~
			int	in1, in2;
			float fmin[50][2];
			int i_loo, i_idx[10], i_ilo;

			in1 = 4;
			memcpy(fmin, farea, 4 * 8);
			in2 = 4;
			fprm[0][0] = array->d[1] - array->d[3];
			fprm[0][1] = array->d[2] - array->d[3];
			fprm[1][0] = array->d[1] - array->d[3];
			fprm[1][1] = array->d[2] + array->d[3];
			fprm[2][0] = array->d[1] + array->d[3];
			fprm[2][1] = array->d[2] + array->d[3];
			fprm[3][0] = array->d[1] + array->d[3];
			fprm[3][1] = array->d[2] - array->d[3];

			mennuk_C(in1, fmin, in2, fprm, &i_loo, i_idx, &i_ilo, F_KIJUN);
			if (i_ilo >= 1 && i_ilo < 4) {
				irc = 1;
				break;
			}
		}
		else if (prm->iptype == 5) {	// �~��
			double  dpt[2][2];
			float fmin[50][2];
			int i_loo, i_idx[10], i_ilo;
			int	in1, in2;

			in1 = in2 = 4;
			memcpy(fmin, farea, 4 * 8);

			fprm[0][0] = array->d[1] - array->d[3];
			fprm[0][1] = array->d[2] - array->d[3];
			fprm[1][0] = array->d[1] - array->d[3];
			fprm[1][1] = array->d[2] + array->d[3];
			fprm[2][0] = array->d[1] + array->d[3];
			fprm[2][1] = array->d[2] + array->d[3];
			fprm[3][0] = array->d[1] + array->d[3];
			fprm[3][1] = array->d[2] - array->d[3];

			dpt[0][0] = array->d[1] + cos(array->d[4]);
			dpt[0][1] = array->d[2] + sin(array->d[4]);
			dpt[1][0] = array->d[1] + cos(array->d[4] + array->d[5]);
			dpt[1][1] = array->d[2] + sin(array->d[4] + array->d[5]);

			if (array->d[4] > 0.0) { // �����
				if (dpt[0][0] >= array->d[1] && dpt[0][1] >= array->d[2]) {
					if (dpt[1][0] >= array->d[1] && dpt[1][1] >= array->d[2]) {
						if (fabs(array->d[5]) < M_PAI / 2.0) {
							fprm[0][0] = array->d[1];
							fprm[0][1] = array->d[2];
							fprm[1][0] = array->d[1];
							fprm[1][1] = array->d[2] + array->d[3];
							fprm[2][0] = array->d[1] + array->d[3];
							fprm[2][1] = array->d[2] + array->d[3];
							fprm[3][0] = array->d[1] + array->d[3];
							fprm[3][1] = array->d[2];
						}
					}
					else if (dpt[1][0] <= array->d[1] && dpt[1][1] >= array->d[2]) {
						fprm[0][0] = array->d[1] - array->d[3];
						fprm[0][1] = array->d[2];
						fprm[1][0] = array->d[1] - array->d[3];
						fprm[1][1] = array->d[2] + array->d[3];
						fprm[2][0] = array->d[1] + array->d[3];
						fprm[2][1] = array->d[2] + array->d[3];
						fprm[3][0] = array->d[1] + array->d[3];
						fprm[3][1] = array->d[2];
					}
				}
				if (dpt[0][0] <= array->d[1] && dpt[0][1] >= array->d[2]) {
					if (dpt[1][0] <= array->d[1] && dpt[1][1] >= array->d[2]) {
						if (fabs(array->d[5]) < M_PAI / 2.0) {
							fprm[0][0] = array->d[1] - array->d[3];
							fprm[0][1] = array->d[2];
							fprm[1][0] = array->d[1] - array->d[3];
							fprm[1][1] = array->d[2] + array->d[3];
							fprm[2][0] = array->d[1];
							fprm[2][1] = array->d[2] + array->d[3];
							fprm[3][0] = array->d[1];
							fprm[3][1] = array->d[2];
						}
					}
					else if (dpt[1][0] <= array->d[1] && dpt[1][1] <= array->d[2]) {
						fprm[0][0] = array->d[1] - array->d[3];
						fprm[0][1] = array->d[2] - array->d[3];
						fprm[1][0] = array->d[1] - array->d[3];
						fprm[1][1] = array->d[2] + array->d[3];
						fprm[2][0] = array->d[1];
						fprm[2][1] = array->d[2] + array->d[3];
						fprm[3][0] = array->d[1];
						fprm[3][1] = array->d[2] - array->d[3];
					}
				}
				if (dpt[0][0] <= array->d[1] && dpt[0][1] <= array->d[2]) {
					if (dpt[1][0] <= array->d[1] && dpt[1][1] <= array->d[2]) {
						if (fabs(array->d[5]) < M_PAI / 2.0) {
							fprm[0][0] = array->d[1] - array->d[3];
							fprm[0][1] = array->d[2] - array->d[3];
							fprm[1][0] = array->d[1] - array->d[3];
							fprm[1][1] = array->d[2];
							fprm[2][0] = array->d[1];
							fprm[2][1] = array->d[2];
							fprm[3][0] = array->d[1];
							fprm[3][1] = array->d[2] - array->d[3];
						}
					}
					else if (dpt[1][0] >= array->d[1] && dpt[1][1] <= array->d[2]) {
						fprm[0][0] = array->d[1] - array->d[3];
						fprm[0][1] = array->d[2] - array->d[3];
						fprm[1][0] = array->d[1] - array->d[3];
						fprm[1][1] = array->d[2];
						fprm[2][0] = array->d[1] + array->d[3];
						fprm[2][1] = array->d[2];
						fprm[3][0] = array->d[1] + array->d[3];
						fprm[3][1] = array->d[2] - array->d[3];
					}
				}
				if (dpt[0][0] >= array->d[1] && dpt[0][1] <= array->d[2]) {
					if (dpt[1][0] >= array->d[1] && dpt[1][1] <= array->d[2]) {
						if (fabs(array->d[5]) < M_PAI / 2.0) {
							fprm[0][0] = array->d[1];
							fprm[0][1] = array->d[2] - array->d[3];
							fprm[1][0] = array->d[1];
							fprm[1][1] = array->d[2];
							fprm[2][0] = array->d[1] + array->d[3];
							fprm[2][1] = array->d[2];
							fprm[3][0] = array->d[1] + array->d[3];
							fprm[3][1] = array->d[2] - array->d[3];
						}
					}
					else if (dpt[1][0] >= array->d[1] && dpt[1][1] >= array->d[2]) {
						fprm[0][0] = array->d[1];
						fprm[0][1] = array->d[2] - array->d[3];
						fprm[1][0] = array->d[1];
						fprm[1][1] = array->d[2] + array->d[3];
						fprm[2][0] = array->d[1] + array->d[3];
						fprm[2][1] = array->d[2] + array->d[3];
						fprm[3][0] = array->d[1] + array->d[3];
						fprm[3][1] = array->d[2] - array->d[3];
					}
				}

			}
			else { // �E���
				if (dpt[0][0] >= array->d[1] && dpt[0][1] >= array->d[2]) {
					if (dpt[1][0] >= array->d[1] && dpt[1][1] >= array->d[2]) {
						if (fabs(array->d[5]) < M_PAI / 2.0) {
							fprm[0][0] = array->d[1];
							fprm[0][1] = array->d[2];
							fprm[1][0] = array->d[1];
							fprm[1][1] = array->d[2] + array->d[3];
							fprm[2][0] = array->d[1] + array->d[3];
							fprm[2][1] = array->d[2] + array->d[3];
							fprm[3][0] = array->d[1] + array->d[3];
							fprm[3][1] = array->d[2];
						}
					}
					else if (dpt[1][0] >= array->d[1] && dpt[1][1] <= array->d[2]) {
						fprm[0][0] = array->d[1];
						fprm[0][1] = array->d[2] - array->d[3];
						fprm[1][0] = array->d[1];
						fprm[1][1] = array->d[2] + array->d[3];
						fprm[2][0] = array->d[1] + array->d[3];
						fprm[2][1] = array->d[2] + array->d[3];
						fprm[3][0] = array->d[1] + array->d[3];
						fprm[3][1] = array->d[2] - array->d[3];
					}
				}
				if (dpt[0][0] <= array->d[1] && dpt[0][1] >= array->d[2]) {
					if (dpt[1][0] <= array->d[1] && dpt[1][1] >= array->d[2]) {
						if (fabs(array->d[5]) < M_PAI / 2.0) {
							fprm[0][0] = array->d[1] - array->d[3];
							fprm[0][1] = array->d[2];
							fprm[1][0] = array->d[1] - array->d[3];
							fprm[1][1] = array->d[2] + array->d[3];
							fprm[2][0] = array->d[1];
							fprm[2][1] = array->d[2] + array->d[3];
							fprm[3][0] = array->d[1];
							fprm[3][1] = array->d[2];
						}
					}
					else if (dpt[1][0] >= array->d[1] && dpt[1][1] >= array->d[2]) {
						fprm[0][0] = array->d[1] - array->d[3];
						fprm[0][1] = array->d[2];
						fprm[1][0] = array->d[1] - array->d[3];
						fprm[1][1] = array->d[2] + array->d[3];
						fprm[2][0] = array->d[1] + array->d[3];
						fprm[2][1] = array->d[2] + array->d[3];
						fprm[3][0] = array->d[1] + array->d[3];
						fprm[3][1] = array->d[2];
					}
				}
				if (dpt[0][0] <= array->d[1] && dpt[0][1] <= array->d[2]) {
					if (dpt[1][0] <= array->d[1] && dpt[1][1] <= array->d[2]) {
						if (fabs(array->d[5]) < M_PAI / 2.0) {
							fprm[0][0] = array->d[1] - array->d[3];
							fprm[0][1] = array->d[2] - array->d[3];
							fprm[1][0] = array->d[1] - array->d[3];
							fprm[1][1] = array->d[2];
							fprm[2][0] = array->d[1];
							fprm[2][1] = array->d[2];
							fprm[3][0] = array->d[1];
							fprm[3][1] = array->d[2] - array->d[3];
						}
					}
					else if (dpt[1][0] <= array->d[1] && dpt[1][1] > array->d[2]) {
						fprm[0][0] = array->d[1] - array->d[3];
						fprm[0][1] = array->d[2] - array->d[3];
						fprm[1][0] = array->d[1] - array->d[3];
						fprm[1][1] = array->d[2] + array->d[3];
						fprm[2][0] = array->d[1];
						fprm[2][1] = array->d[2] + array->d[3];
						fprm[3][0] = array->d[1];
						fprm[3][1] = array->d[2] - array->d[3];
					}
				}
				if (dpt[0][0] >= array->d[1] && dpt[0][1] <= array->d[2]) {
					if (dpt[1][0] >= array->d[1] && dpt[1][1] <= array->d[2]) {
						if (fabs(array->d[5]) < M_PAI / 2.0) {
							fprm[0][0] = array->d[1];
							fprm[0][1] = array->d[2] - array->d[3];
							fprm[1][0] = array->d[1];
							fprm[1][1] = array->d[2];
							fprm[2][0] = array->d[1] + array->d[3];
							fprm[2][1] = array->d[2];
							fprm[3][0] = array->d[1] + array->d[3];
							fprm[3][1] = array->d[2] - array->d[3];
						}
					}
					else if (dpt[1][0] <= array->d[1] && dpt[1][1] <= array->d[2]) {
						fprm[0][0] = array->d[1] - array->d[3];
						fprm[0][1] = array->d[2] - array->d[3];
						fprm[1][0] = array->d[1] - array->d[3];
						fprm[1][1] = array->d[2];
						fprm[2][0] = array->d[1] + array->d[3];
						fprm[2][1] = array->d[2];
						fprm[3][0] = array->d[1] + array->d[3];
						fprm[3][1] = array->d[2] - array->d[3];
					}
				}
			}

			mennuk_C(in1, fmin, in2, fprm, &i_loo, i_idx, &i_ilo, F_KIJUN);
			if (i_ilo >= 1 && i_ilo < 4) {
				irc = 1;
				break;
			}

		}
		else if (prm->iptype == 9) {	// �n�b�`���O
			int	i, lcnt;

			lcnt = (array->s[0] - 8 * 5) / 24;
			for (i = 0; i < 3; i++) {
				fline[0][0] = array->d[1] + array->d[5 + i * 3];
				fline[0][1] = array->d[2] + array->d[6 + i * 3];
				fline[0][2] = fline[0][0] + array->d[7 + i * 3] * array->d[3];
				fline[0][3] = fline[0][1] + array->d[7 + i * 3] * array->d[4];
				pbccut_C(farea, 5, fline, 10, &num, 4, 0.001, F_KIJUN);
				if (num > 0) {
					irc = 1;
					break;
				}
			}
			if (irc == 1) break;

		}
		else if (prm->iptype == 10) {	// ��`
			int	in1, in2, i;
			float fmin[50][2];
			float fwk[4][2];
			int i_loo, i_idx[10], i_ilo;
			float fmax_x, fmax_y, fmin_x, fmin_y;

			in1 = 4;
			memcpy(fmin, farea, 4 * 8);
			in2 = 4;

			fmax_x = fmax_y = -9999999.0;
			fmin_x = fmin_y = 9999999.0;

			fwk[0][0] = array->d[1];
			fwk[0][1] = array->d[2];
			fwk[1][0] = array->d[1] + array->d[5] * array->d[3];
			fwk[1][1] = array->d[2] + array->d[5] * array->d[4];
			fwk[2][0] = array->d[1] - array->d[6] * array->d[4];
			fwk[2][1] = array->d[2] + array->d[6] * array->d[3];
			fwk[3][0] = fwk[1][0] - array->d[6] * array->d[4];
			fwk[3][1] = fwk[1][1] + array->d[6] * array->d[3];
			for (i = 0; i < 4; i++) {
				if (fwk[i][0] < fmin_x) fmin_x = fwk[i][0];
				if (fwk[i][0] > fmax_x) fmax_x = fwk[i][0];
				if (fwk[i][1] < fmin_y) fmin_y = fwk[i][1];
				if (fwk[i][1] > fmax_y) fmax_y = fwk[i][1];
			}
			fprm[0][0] = fmin_x;
			fprm[0][1] = fmin_y;
			fprm[1][0] = fmin_x;
			fprm[1][1] = fmax_y;
			fprm[2][0] = fmax_x;
			fprm[2][1] = fmax_y;
			fprm[3][0] = fmin_x;
			fprm[3][1] = fmax_y;

			mennuk_C(in1, fmin, in2, fprm, &i_loo, i_idx, &i_ilo, F_KIJUN);
			if (i_ilo >= 1 && i_ilo < 4) {
				irc = 1;
				break;
			}

		}
		else if (prm->iptype == 32) {	// ������
			int	in1, in2, i;
			float fmin[50][2];
			float fwk[4][2];
			int i_loo, i_idx[10], i_ilo;
			float fmax_x, fmax_y, fmin_x, fmin_y;
			int ikaku, isu;
			float fch, fcw, fang, leng;

			in1 = 4;
			memcpy(fmin, farea, 4 * 8);
			in2 = 4;

			fmax_x = fmax_y = -9999999.0;
			fmin_x = fmin_y = 9999999.0;

			fch = array->f[6];
			fcw = array->f[8];
			isu = array->i[13];
			ikaku = array->i[10];
			fang = CNV_SC2Radian(ikaku);

			leng = fcw * isu;

			fwk[0][0] = array->d[1];
			fwk[0][1] = array->d[2];
			fwk[1][0] = array->d[1] + leng * array->d[3];
			fwk[1][1] = array->d[2] + leng * array->d[4];
			fwk[2][0] = array->d[1] - fch * array->d[4];
			fwk[2][1] = array->d[2] + fch * array->d[3];
			fwk[3][0] = fwk[1][0] - fch * array->d[4];
			fwk[3][1] = fwk[1][1] + fch * array->d[3];
			for (i = 0; i < 4; i++) {
				if (fwk[i][0] < fmin_x) fmin_x = fwk[i][0];
				if (fwk[i][0] > fmax_x) fmax_x = fwk[i][0];
				if (fwk[i][1] < fmin_y) fmin_y = fwk[i][1];
				if (fwk[i][1] > fmax_y) fmax_y = fwk[i][1];
			}
			fprm[0][0] = fmin_x;
			fprm[0][1] = fmin_y;
			fprm[1][0] = fmin_x;
			fprm[1][1] = fmax_y;
			fprm[2][0] = fmax_x;
			fprm[2][1] = fmax_y;
			fprm[3][0] = fmin_x;
			fprm[3][1] = fmax_y;

			mennuk_C(in1, fmin, in2, fprm, &i_loo, i_idx, &i_ilo, F_KIJUN);
			if (i_ilo >= 1 && i_ilo < 4) {
				irc = 1;
				break;
			}
		}

	}

	return irc;

}