#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

void sptxt2_(double *x, double *y, char texts[], int *num, int *code, int *atrid, int *mode, int *ircode)
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
		if (*num < 1 ) {
			*ircode = 12;
			err_syosai = 4;
		}
		else {
			if ( *code !=0 && *code != 1) {
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
							int  isize;

							isize = 56 + (*num) * (*code + 1);

						//	SegWK.pprm[SegWK.ipcount] = &PrmWkinfo[SegWK.ipcount];
							SegWK.pprm[SegWK.ipcount].iptype = 32;
							SegWK.pprm[SegWK.ipcount].ipsize = isize;
						//	SegWK.pprm[SegWK.ipcount].pdata = &PrmWK[iPWK_use];
							SegWK.pprm[SegWK.ipcount].ioffset = iPWK_use;

						//	array = (union Udata *)&PrmWK[iPWK_use];
							if ((pt = get_PrmWKNext(SegWK.pprm[SegWK.ipcount].ipsize, &ioff)) != NULL) {
								array = (union Udata *)pt;
								array->c[3] = 32;
								array->s[0] = isize;
								array->d[1] = *x;
								array->d[2] = *y;
								array->f[6] = TxtAttr[*atrid].atrtb1[0];
								array->f[7] = TxtAttr[*atrid].atrtb1[1];
								array->f[8] = TxtAttr[*atrid].atrtb1[2];
								array->i[9] = CNV_Degree2SC(TxtAttr[*atrid].atrtb1[3]);
								array->i[10] = CNV_Degree2SC(TxtAttr[*atrid].atrtb1[4]);

								array->i[11] = 0;
								array->i[12] = 0;
								if (*code == 0) {
									array->c[48] =0x80;
								}
								else {
									array->c[48] = 0x40;
								}

								array->i[13] = *num;

								memcpy(&(array->c[56]), texts, (*num) * (*code + 1));

								SegWK.pprm[SegWK.ipcount].iwt = TxtAttr[*atrid].atrtb2[1];
								SegWK.pprm[SegWK.ipcount].ifnt = 1;
								SegWK.pprm[SegWK.ipcount].iclr = TxtAttr[*atrid].atrtb2[0];
								
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