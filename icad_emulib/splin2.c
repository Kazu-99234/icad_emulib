#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// splin2_
// 機能		次元の線プリミティブを作成します

void splin2_(double *xstart, double *ystart, double *xdir, double *ydir, double *length, int *atrid, int *mode, int *ircode)
{

	union Udata{
		int	i[1024];
		short	s[248];
		char	c[4096];
		double	d[512];
		float	f[1024];
	} *array;

	double		dtani;
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
		dtani = sqrt((*xdir)*(*xdir) + (*ydir)*(*ydir));
//		if (dtani < 1.0 - dgos || dtani > 1.0 + dgos) {
//			*ircode = 12;
//			err_syosai = 3;
//		}
//		else {
			if (*length < 0.0) {
				*ircode = 12;
				err_syosai = 5;
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
							SegWK.pprm[SegWK.ipcount].iptype = 2;
							SegWK.pprm[SegWK.ipcount].ipsize = 48;
						//	SegWK.pprm[SegWK.ipcount].pdata = &PrmWK[iPWK_use];
							SegWK.pprm[SegWK.ipcount].ioffset = iPWK_use;
							
						//	array = (union Udata*)&PrmWK[iPWK_use];
							if ((pt = get_PrmWKNext(SegWK.pprm[SegWK.ipcount].ipsize, &ioff)) != NULL) {
								array = (union Udata *)pt;
								array->c[3] = 2;
								array->s[0] = 48;
								array->d[1] = *xstart;
								array->d[2] = *ystart;
								array->d[3] = *xdir;
								array->d[4] = *ydir;
								array->d[5] = *length;

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
//		}

	}

	return;


}