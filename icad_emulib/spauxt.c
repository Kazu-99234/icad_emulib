#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// spauxn_
// 機能		任意文字プリミティブを作成します。
// in	*form		form番号を1～255(任意情報を識別するため利用者が任意に指定)の整数で指定します
// in	xtarry[]	任意文字データ(余りは空白を詰めること)
// in	*n			xtarry[]の大きさを指定します(8≦*n≦4080、単位：バイト、8の倍数)
// out	*ircode		復帰情報

void spauxt_(int *form, char txtarry[], int *n, int *ircode)
{

	union Udata {
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
			if (*n < 8 || *n > 4080) {
				*ircode = 12;
				err_syosai = 3;
			}

			int isize, ia;
			isize = *n + 8;
			if (isize % 8) {
				ia = isize / 8;
				isize = (ia + 1) * 8;
			}
			
			if (SegWK.ipcount >= 255) {
				*ircode = 8;
				err_syosai = 1005;
			}
			else {
			//	SegWK.pprm[SegWK.ipcount] = &PrmWkinfo[SegWK.ipcount];
				SegWK.pprm[SegWK.ipcount].iptype = 254;
				SegWK.pprm[SegWK.ipcount].ipsize = isize;
			//	SegWK.pprm[SegWK.ipcount].pdata = &PrmWK[iPWK_use];
				SegWK.pprm[SegWK.ipcount].ioffset = iPWK_use;
			//	array = (union Udata *)&PrmWK[iPWK_use];
				if ((pt = get_PrmWKNext(SegWK.pprm[SegWK.ipcount].ipsize, &ioff)) != NULL) {
					array = (union Udata *)pt;
					array->c[3] = 254;
					array->s[0] = isize;
				//	array->c[7] = *form;
					cCnv.i = *form;
					array->c[7] = cCnv.c[0];
					memcpy(&(array->c[8]), txtarry, *n);

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

	}

	return;
}