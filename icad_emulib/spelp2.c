#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

#define	PAI_R	3.141592653589794
#define	PAI_2R	6.28318530717958647

// spelp2_
// 機能		次元の楕円プリミティブを作成します。

void spelp2_(double *x, double *y, double *rad1, double *rad2, double *ang, int *atrid, int *mode, int *ircode)
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
		if (*rad1 < 0.0 || *rad2 < 0.0) {
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
						SegWK.pprm[SegWK.ipcount].iptype = 89;
						SegWK.pprm[SegWK.ipcount].ipsize = 72;
					//	SegWK.pprm[SegWK.ipcount].pdata = &PrmWK[iPWK_use];
						SegWK.pprm[SegWK.ipcount].ioffset = iPWK_use;
					//	array = (union Udata *)&PrmWK[iPWK_use];
						if ((pt = get_PrmWKNext(SegWK.pprm[SegWK.ipcount].ipsize, &ioff)) != NULL) {
							array = (union Udata *)pt;
							array->c[3] = 7;
							array->s[0] = 72;
							array->d[1] = *x;
							array->d[2] = *y;
							array->d[3] = *rad1;
							array->d[4] = *rad2;
							array->d[5] = *ang;
							array->d[6] = 0.0;
							array->d[7] = PAI_2R;

							SegWK.pprm[SegWK.ipcount].iwt = GraAttr[*atrid].atrtbl[0];
							SegWK.pprm[SegWK.ipcount].ifnt = GraAttr[*atrid].atrtbl[1];
							SegWK.pprm[SegWK.ipcount].iclr = GraAttr[*atrid].atrtbl[2];
							
							SegWK.pprm[SegWK.ipcount].imode = *mode;

							iPWK_use += 72;
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