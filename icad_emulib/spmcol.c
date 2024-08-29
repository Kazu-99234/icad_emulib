#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// spmcol_
// 機能		指定された要素の指定プリミティブの色を変更します。

void spmcol_(int *segid, int *primno, int *color, int *dummy, int *ircode)
{
	*ircode = 0;
	err_syosai = 0;

	if (cur_mode != 0) {
		*ircode = 12;
		err_syosai = 101;
	}
	else {
		if (*color < 1 || *color > 31) {
			*ircode = 12;
			err_syosai = 3;
		}
		else {

			int		j, ismax, ipmax, ivsno;
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
						if (*primno == 0) {
							for (j = 0; j < ipmax; j++) {
								pPrm[j].iclr = *color;
							}
						}
						else {
								pPrm[*primno - 1].iclr = *color;
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
	}

	l_err:
	return;


}