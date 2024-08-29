#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// spauxn_
// �@�\		�C�Ӑ��l�v���~�e�B�u���쐬���܂��B
// in	*form		form�ԍ���1�`255(�C�ӏ������ʂ��邽�ߗ��p�҂��C�ӂɎw��)�̐����Ŏw�肵�܂�
// in	numarry[]	�C�ӏ��f�[�^(�]���0���l�߂邱��)
// in	*n			numarry[]�̑傫�����w�肵�܂�(8��*n��4080�A�P�ʁF�o�C�g�A8�̔{��)
// out	*ircode		���A���

void spauxn_(int *form, char numarry[], int *n, int *ircode)
{

	union Udata{
		int	i[1024];
		short	s[248];
		char	c[4096];
		double	d[512];
		float	f[1024];
	} *array;

	union {
		int	i;
		float	f;
		char	c[4];
	} cCnv;
	
	int	ioff;
	char	*pt;

	*ircode = 0;
	err_syosai = 0;

	if (cur_mode == 0) {
		*ircode = 12;
		err_syosai = 101;
	}
	else {

		if (*form < 1 || *form > 255) {
			*ircode = 12;
			err_syosai = 1;
		}
		else {
		//	if (*n < 8 || *n > 4080) {
			if (*n < 8 ) { // 4080�̃`�F�b�N�͊O��
				*ircode = 12;
				err_syosai = 3;
			}
			
			if ( *n > 4080 ) {
				*ircode = 0;
			}

			int isize, ia;
			isize = *n + 8;
			if (isize % 8) {
				ia = isize / 8;
				isize = (ia + 1) * 8;
			}

			if (SegWK.ipcount >= 255) {
		//		*ircode = 8;
		//		err_syosai = 1005;
				*ircode = 0;
			}

		//	SegWK.pprm[SegWK.ipcount] = &PrmWkinfo[SegWK.ipcount];
			SegWK.pprm[SegWK.ipcount].iptype = 253;
			SegWK.pprm[SegWK.ipcount].ipsize = isize;
		//	SegWK.pprm[SegWK.ipcount].pdata = &PrmWK[iPWK_use];
			SegWK.pprm[SegWK.ipcount].ioffset = iPWK_use;
		//	array = (union Udata *)&PrmWK[iPWK_use];
			if ((pt = get_PrmWKNext(SegWK.pprm[SegWK.ipcount].ipsize, &ioff)) != NULL) {
				array = (union Udata *)pt;
				array->i[0] = array->i[1] = 0;
				array->c[3] = 253;
				array->s[0] = isize;
			//	array->c[7] = *form;
				cCnv.i = *form;
				array->c[7] = cCnv.c[0];
				memcpy(&(array->c[8]), numarry, *n);

				SegWK.pprm[SegWK.ipcount].iwt = 0;
				SegWK.pprm[SegWK.ipcount].ifnt = 0;
				SegWK.pprm[SegWK.ipcount].iclr = 0;

				iPWK_use += isize;
				SegWK.ipcount++;
			}
			else {
				*ircode = 8;
				err_syosai = 1004;
			}
		}

	}

	return;
}