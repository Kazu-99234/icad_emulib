#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

void ssmvis_(int segids[],int *count,int *inc,int *ivs,int *ircode)
{

	*ircode = 0;
	err_syosai = 0;


	if (cur_mode != 0) {
		*ircode = 12;
		err_syosai = 101;
	}
	else {
		if (*count < 1  ) {
			*ircode = 12;
			err_syosai = 2;
		}
		else {
			if (*inc < 1) {
				*ircode = 12;
				err_syosai = 3;
			}
			else {
				int		i, j, ismax, ivsno;
				short	*ichk;
				int		icnt;
				
				icnt=0;
				
				for (ivsno=1;ivsno <= 500;ivsno++) {
					if ( VsInfodata[ivsno - 1].vsno == 0 ) continue;
					
					struct  SegInfo *pSeg = (struct  SegInfo *)	VsInfodata[ivsno - 1].pSeg;
					ismax = VsInfodata[ivsno - 1].iScount;

					for (i = 0; i < *count; i++) {
						
						for (j = 0; j < ismax; j++) {
							if (pSeg[j].isegno == segids[i * (*inc)] || pSeg[j].isysno == segids[i * (*inc)]) {
								pSeg[j].ivisi = *ivs;
								
								break;
							}
						}
					}
				}
						

			}
		}

	}

	return;	
}
