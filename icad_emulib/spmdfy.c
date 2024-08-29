#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// spmdfy_
// 機能		指定された要素の指定プリミティブを他のプリミティブで置き換えます。


void spmdfy_(int *segid, int *primno, char newprm[4096], int *erase, int *ircode)
{
	union Udata{
		int	i[1024];
		short	s[248];
		char	c[4096];
		double	d[512];
		float	f[1024];
	} *array;
	
	int	ioff, iwk;
	
	union {
		int  i;
		char c[4];
	}  icnv;

	char *pt;

	*ircode = 0;
	err_syosai = 0;
	
	array = (union Udata *)newprm;

	if (cur_mode != 0) {
		*ircode = 12;
		err_syosai = 101;
	}
	else {

		int		j, ismax, ipmax, ivsno, isize, ia;
		struct  SegInfo *pSeg;
			
		for (ivsno=1;ivsno <= 500;ivsno++) {
			if ( VsInfodata[ivsno - 1].vsno == 0 ) continue;
		
			pSeg = (struct  SegInfo *)	VsInfodata[ivsno-1].pSeg;
			ismax = VsInfodata[ivsno-1].iScount;

			for (j = 0; j < ismax; j++) {
				if (pSeg[j].isegno == *segid || pSeg[j].isysno == *segid) {
					ipmax = pSeg[j].ipcount;
					struct  PrmInfo *pPrm = (struct  PrmInfo*)pSeg[j].pprm;

					if (*primno > ipmax) {
						*ircode = 12;
						err_syosai = 2;
						goto l_err;
					}
					
					isize = (int)array->s[0];
					if (isize % 8) {
						ia = isize / 8;
						isize = (ia + 1) * 8;
					}
					
					if ( pPrm[*primno - 1].ipsize >= array->s[0] ) {
						pt = VsInfodata[ivsno - 1].pPrm + pPrm[*primno - 1].ioffset;
						memcpy(pt, newprm, array->s[0]);
						pPrm[*primno - 1].ipsize = array->s[0];
						icnv.i = 0;
						icnv.c[0] = array->c[3];
						pPrm[*primno - 1].iptype = icnv.i;
					}
					else {
						ioff = 0;
						if ((pt = get_PrmNext(isize, &ioff)) != NULL) {
						//	pPrm[*primno - 1].pdata = pt;
							pPrm[*primno - 1].ioffset = ioff;
							memcpy(pt, newprm, array->s[0]);
							pPrm[*primno - 1].ipsize = array->s[0];
							icnv.i = 0;
							icnv.c[0] = array->c[3];
							pPrm[*primno - 1].iptype = icnv.i;
							
						//	pPrm[*primno - 1].iwt = GraAttr[cur_gra_atr].atrtbl[0];
						//	pPrm[*primno - 1].ifnt = GraAttr[cur_gra_atr].atrtbl[1];
						//	pPrm[*primno - 1].iclr = GraAttr[cur_gra_atr].atrtbl[2];

						}
					}

					break;
				}
			}

			if ( j < ismax ) break;
		}

		if (ivsno > 500) {
			*ircode = 8;
			err_syosai = 311;
		}
	}
	

l_err:

	return;


}