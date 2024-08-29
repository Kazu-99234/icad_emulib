#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

#define	PAI_R	3.141592653589794
#define	PAI_2R	6.28318530717958647

// spcir2_
// 機能		次元の円プリミティブを作成します
// in	*form		form番号を1～255(任意情報を識別するため利用者が任意に指定)の整数で指定します
// in	xtarry[]	任意文字データ(余りは空白を詰めること)
// in	*n			xtarry[]の大きさを指定します(8≦*n≦4080、単位：バイト、8の倍数)
// out	*ircode		復帰情報

void spcir2_(double *x, double *y, double *rad, int *atrid, int *mode, int *ircode)
{
	union Udata {
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
		if (*rad < 0.0) {
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
						SegWK.pprm[SegWK.ipcount].iptype = 4;
						SegWK.pprm[SegWK.ipcount].ipsize = 48;
					//	SegWK.pprm[SegWK.ipcount].pdata = &PrmWK[iPWK_use];							
						SegWK.pprm[SegWK.ipcount].ioffset = iPWK_use;
					//	array = (union Udata *)&PrmWK[iPWK_use];
						if ((pt = get_PrmWKNext(SegWK.pprm[SegWK.ipcount].ipsize, &ioff)) != NULL) {
							array = (union Udata *)pt;
							array->c[3] = 4;
							array->s[0] = 48;
							array->d[1] = *x;
							array->d[2] = *y;
							array->d[3] = *rad;
							array->d[4] = 0.0;
							array->d[5] = PAI_2R;

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