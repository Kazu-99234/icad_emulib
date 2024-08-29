#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// sppnt2_
// 機能		次元の点プリミティブを作成します。

void sppnt2_(double *x, double *y, int *mark, int *atrid, int *mode, int *ircode) 
{


	union Udata{
		int	i[1024];
		short	s[248];
		char	c[4096];
		double	d[512];
		float	f[1024];
	} *array;

	int	ioff;
	char	*pt;

	*ircode = 0;
	err_syosai = 0;

	if (cur_mode == 0) {
		*ircode = 12;
		err_syosai = 101;
	}
	else {

		if (*mark < 1 || *mark > 4) {
			*ircode = 12;

			err_syosai = 3;
		}
		else {
			if (*atrid < 0 || *atrid > 3) {
				*ircode = 12;
				err_syosai = 4;
			}
			else {
				if (*mode < 1 || *mode >3) {
					*ircode = 12;
					err_syosai = 5;
				}
				else {
					if (SegWK.ipcount >= 255) {
						*ircode = 8;
						err_syosai = 1005;
					}
					else {
					//	SegWK.pprm[SegWK.ipcount] = &PrmWkinfo[SegWK.ipcount];
						SegWK.pprm[SegWK.ipcount].iptype = 1;
						SegWK.pprm[SegWK.ipcount].ipsize = 32;
					//	SegWK.pprm[SegWK.ipcount].pdata = &PrmWK[iPWK_use];
						SegWK.pprm[SegWK.ipcount].ioffset = iPWK_use;
						
					//	array = (union Udata *)&PrmWK[iPWK_use];
						if ((pt = get_PrmWKNext(SegWK.pprm[SegWK.ipcount].ipsize, &ioff)) != NULL) {
							array = (union Udata *)pt;
							array->c[3] = 1;
							array->s[0] = 32;
							array->d[1] = *x;
							array->d[2] = *y;
							array->s[12] = *mark;

							SegWK.pprm[SegWK.ipcount].iwt = GraAttr[*atrid].atrtbl[0];
							SegWK.pprm[SegWK.ipcount].ifnt = GraAttr[*atrid].atrtbl[1];
							SegWK.pprm[SegWK.ipcount].iclr = GraAttr[*atrid].atrtbl[2];
							
							SegWK.pprm[SegWK.ipcount].imode = *mode;

							iPWK_use += 32;
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