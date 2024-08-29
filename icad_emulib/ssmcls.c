#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

void ssmcls_(int entids[], int *nument, int *incrmt, int *iclass, int *mode, int ientid[], int *ircode)
{
	int	i, ivsno;
	int		j, ismax, ipmax;
	struct  SegInfo *pSeg;
	union Udata {
		int	i[1024];
		short	s[248];
		char	c[4096];
		double	d[512];
		float	f[1024];
	} *array;

	char *pt;

	*ircode = 0;
	err_syosai = 0;


	if (cur_mode != 0) {
		*ircode = 12;
		err_syosai = 100;
		goto l_err;
	}
	if (*nument < 1) { 
		*ircode = 12;
		err_syosai = 2;
		goto l_err;
	}
	if (*incrmt < 1) {
		*ircode = 12;
		err_syosai = 3;
		goto l_err;
	}
	if (*iclass < 1 || *iclass > 255) {
		*ircode = 12;
		err_syosai = 4;
		goto l_err;
	}

	for (i = 0; i < *nument;i++){
//		ivsno = entids[i] / 1000000;
		for (ivsno=1;ivsno <= 500;ivsno++) {
			if ( VsInfodata[ivsno - 1].vsno == 0 ) continue;

			pSeg = (struct  SegInfo *)	VsInfodata[ivsno-1].pSeg;
			ismax = VsInfodata[ivsno - 1].iScount;
			
			for (j = 0; j < ismax; j++) {
				if ( entids[i] == (pSeg+j)->isegno || entids[i] == (pSeg+j)->isysno ) {
					(pSeg+j)->iclass = *iclass;
					ientid[i] = (pSeg+j)->isysno;
				}
			}
		}
	}

l_err:

	return;



}