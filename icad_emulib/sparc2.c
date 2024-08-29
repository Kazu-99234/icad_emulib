#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// sparc2_
// �@�\		2�����̉~�ʃv���~�e�B�u���쐬���܂��B
// in	*x		�~�ʂ̒��S��X���W���w�肵�܂�
// in	*y		�~�ʂ̒��S��Y���W���w�肵�܂�
// in	*r		�~�ʂ̔��a�𐳂̎����Ŏw�肵�܂�
// in	*th1	�~�ʂ̎n�p���w�肵�܂�(�P�� : ���W�A��)
// in	*th2	�~�ʂ̎n�p����I�p�܂ł̍����̑��Ίp�x���|2�΁`2�΂͈̔͂Ŏw�肵�܂�
// 				(*th2��0�A�P�ʁF���W�A��)
// 				0��*th2��2�� �n�p���獶���ɉ~�ʂ��쐬����܂�
// 				0��*th2���|2�� �n�p����E���ɉ~�ʂ��쐬����܂�
// in	*atrid	�쐬�v���~�e�B�u�ɗ^���鑮���̒�`���ꂽ�}�`�����e�[�u���ԍ���0�`3�̐����Ŏw�肵�܂�
// in	*mode	�쐬�v���~�e�B�u�̕\���E�����������ȉ��̂����ꂩ�Ŏw�肵�܂�
// 				1 �F �\���E����
// 				2 �F �\���E�񌟍�
// 				3 �F ��\���E�񌟍�
// out	*ircode	���A���

void sparc2_(double *x, double *y, double *r, double *th1, double *th2, int *atrid, int *mode, int *ircode)
{
	union Udata{
		int	i[1024];
		short	s[248];
		char	c[4096];
		double	d[512];
		float	f[1024];
	} *array;

	double		dgos = 0.000001;
	int	ioff;
	char	*pt;


	*ircode = 0;
	err_syosai = 0;

	if (cur_mode == 0) {
		*ircode = 12;
		err_syosai = 101;
	}
	else {
		if (*r < 0.0) {
			*ircode = 12;
			err_syosai = 3;
		}
		else {
				if (*atrid < 0 || *atrid > 3) {
					*ircode = 12;
					err_syosai = 6;
				}
				else {
					if (*mode < 1 || *mode >3) {
						*ircode = 12;
						err_syosai = 7;
					}
					else {
						if (SegWK.ipcount >= 255) {
							*ircode = 8;
							err_syosai = 1005;
						}
						else {
						//	SegWK.pprm[SegWK.ipcount] = &PrmWkinfo[SegWK.ipcount];
							SegWK.pprm[SegWK.ipcount].iptype = 5;
							SegWK.pprm[SegWK.ipcount].ipsize = 48;
						//	SegWK.pprm[SegWK.ipcount].pdata = &PrmWK[iPWK_use];
						//	array = (union Udata *)&PrmWK[iPWK_use];
							SegWK.pprm[SegWK.ipcount].ioffset = iPWK_use;
							if ((pt = get_PrmWKNext(SegWK.pprm[SegWK.ipcount].ipsize, &ioff)) != NULL) {
								array = (union Udata *)pt;
								array->c[3] = 5;
								array->s[0] = 48;
								array->d[1] = *x;
								array->d[2] = *y;
								array->d[3] = *r;
								array->d[4] = *th1;
								array->d[5] = *th2;
							
								SegWK.pprm[SegWK.ipcount].iwt = GraAttr[*atrid].atrtbl[0];
								SegWK.pprm[SegWK.ipcount].ifnt = GraAttr[*atrid].atrtbl[1];
								SegWK.pprm[SegWK.ipcount].iclr = GraAttr[*atrid].atrtbl[2];
								
								SegWK.pprm[SegWK.ipcount].imode = *mode;


								iPWK_use += 48;
								SegWK.ipcount++;
							}
							else {
								*ircode = 8;
								err_syosai = 1004;
							}

						}

					}

				}

			}

	}

	return;

}