#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// spqprm_
// 機能		指定されたプリミティブの表示制御情報と表示、検索属性を得ます。

void spqprm_(int *segid, int *primno, int atrary[3], int *mode, int *ircode)
{
	int	i, ismax, ivsno;
	union Udata {
		int	i[1024];
		short	s[248];
		char	c[4096];
		double	d[512];
		float	f[1024];
	} *array;
	struct SegInfo *seg;

	*ircode = 0;
	err_syosai = 0;

	//ivsno = *segid / 1000000;

	for (ivsno=1;ivsno <= 500;ivsno++) {
		if ( VsInfodata[ivsno - 1].vsno == 0 ) continue;
		
		seg = (SegInfo *)VsInfodata[ivsno - 1].pSeg;
		ismax = VsInfodata[ivsno - 1].iScount;

		for (i = 0; i < ismax; i++) {
			if ((seg + i)->idel == 1) continue;
			if ((seg + i)->isegno == *segid || (seg + i)->isysno == *segid) {
				if (*primno > 0 && *primno <= (seg + i)->ipcount) {
					struct PrmInfo *prm = &((seg + i)->pprm[*primno - 1]);
					array = (union Udata *)prm;
				//	if (array->c[7] <= 32) {
						atrary[0] = prm->iwt;
						atrary[1] = prm->ifnt;
						atrary[2] = prm->iclr;
						*mode = prm->imode;
				//	}
				}
				else {
					*ircode = 8;
					err_syosai = 401;
				}
				break;
			}
		}
	}
	if (ivsno == 500) {
		*ircode = 8;
		err_syosai = 311;
	}


	return;

}