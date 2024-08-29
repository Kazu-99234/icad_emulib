#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// spply2_
// 機能		2次元の折れ線プリミティブを作成します。

void spply2_(double *xstart, double *ystart, double xarray[], double yarray[], int *numpt, int *incrmt, int *atrid, int *mode, int *ircode) 
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
		if (*numpt < 1 || *numpt >254) {
			*ircode = 12;
			err_syosai = 5;
		}
		else {
			if (*incrmt < 1) {
				*ircode = 12;
				err_syosai = 6;
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
							int  isize, i;

							isize = 24 + 16 * (*numpt);
							
						//	SegWK.pprm[SegWK.ipcount] = &PrmWkinfo[SegWK.ipcount];
							SegWK.pprm[SegWK.ipcount].iptype = 3;
							SegWK.pprm[SegWK.ipcount].ipsize = isize;
						//	SegWK.pprm[SegWK.ipcount].pdata = &PrmWK[iPWK_use];
							SegWK.pprm[SegWK.ipcount].ioffset = iPWK_use;
							
						//	array = (union Udata *)&PrmWK[iPWK_use];
							if ((pt = get_PrmWKNext(SegWK.pprm[SegWK.ipcount].ipsize, &ioff)) != NULL) {
								array = (union Udata *)pt;
								array->c[3] = 3;
								array->s[0] = isize;
								array->d[1] = *xstart;
								array->d[2] = *ystart;
								for (i = 0; i < *numpt; i++) {
									array->d[3+i*2] = xarray[i*(*incrmt)];
									array->d[4+i*2] = yarray[i]*(*incrmt);
								}
								SegWK.pprm[SegWK.ipcount].iwt = GraAttr[*atrid].atrtbl[0];
								SegWK.pprm[SegWK.ipcount].ifnt = GraAttr[*atrid].atrtbl[1];
								SegWK.pprm[SegWK.ipcount].iclr = GraAttr[*atrid].atrtbl[2];
								
								SegWK.pprm[SegWK.ipcount].imode = *mode;

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

	return;

}