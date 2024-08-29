#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// spewl2_
// 機能		次元のハッチングプリミティブを作成します。

void spewl2_(double *x0, double *y0, double *a, double *b, double xarray[], double yarray[], double lnglst[], int *n, int *inc, int *atrid, int *mode, int *ircode)
{
	union Udata {
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
		dtani = sqrt((*a)*(*a) + (*b)*(*b));
		if (dtani < 1.0 - dgos || dtani > 1.0 + dgos) {
			*ircode = 12;
			err_syosai = 3;
		}
		else {
			if (*n < 1 || *n >168) {
				*ircode = 12;
				err_syosai = 8;
			}
			else {
				if (*inc < 1) {
					*ircode = 12;
					err_syosai = 9;
				}
				else {
					if (*atrid < 0 || *atrid > 3) {
						*ircode = 12;
						err_syosai = 10;
					}
					else {
						if (*mode < 1 || *mode >3) {
							*ircode = 12;
							err_syosai = 11;
						}
						else {
							if (SegWK.ipcount >= 255) {
								*ircode = 8;
								err_syosai = 1005;
							}
							else {
								int  isize, i;

								isize = 40 + 24 * (*n);

							//	SegWK.pprm[SegWK.ipcount] = &PrmWkinfo[SegWK.ipcount];
								SegWK.pprm[SegWK.ipcount].iptype = 9;
								SegWK.pprm[SegWK.ipcount].ipsize = isize;
							//	SegWK.pprm[SegWK.ipcount].pdata = &PrmWK[iPWK_use];
								SegWK.pprm[SegWK.ipcount].ioffset = iPWK_use;
							//	array = (union Udata *)&PrmWK[iPWK_use];
								if ((pt = get_PrmWKNext(SegWK.pprm[SegWK.ipcount].ipsize, &ioff)) != NULL) {
									array = (union Udata *)pt;
									array->c[3] = 9;
									array->s[0] = isize;
									array->d[1] = *x0;
									array->d[2] = *y0;
									array->d[3] = *a;
									array->d[4] = *b;
									for (i = 0; i < *n; i++) {
										array->d[5 + i * 3] = xarray[i*(*inc)] ;
										array->d[6 + i * 3] = yarray[i*(*inc)] ;
										array->d[7 + i * 3] = lnglst[i* (*inc)];
									}
									SegWK.pprm[SegWK.ipcount].iwt = GraAttr[*atrid].atrtbl[0];
									SegWK.pprm[SegWK.ipcount].ifnt = GraAttr[*atrid].atrtbl[1];
									
									SegWK.pprm[SegWK.ipcount].imode = *mode;

									SegWK.pprm[SegWK.ipcount].iclr = GraAttr[*atrid].atrtbl[2];

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

				}
			}
		}

	}

	return;


}