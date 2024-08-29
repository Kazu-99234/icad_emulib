#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// spdget_
// 機能		2次元の矩形プリミティブを作成します。

void spsget_(char array[4096], int *ircode)
{
	union Udata {
		int	i[1024];
		short	s[248];
		char	c[4096];
		double	d[512];
		float	f[1024];
	} *uarray;

	*ircode = 0;
	err_syosai = 0;

	if (Sread.segno == 0) {
		*ircode = 4;
		err_syosai = 1001;
	}
	else {
		struct  SegInfo *seg = Sread.seg;

		if (Sread.prmno == seg->ipcount) {
			*ircode = 8;
			err_syosai = 401;
		}
		else {
		//	uarray = (union Udata *)seg->pprm[Sread.prmno];
		//	uarray = (union Udata *)seg->pprm[Sread.prmno].pdata;
			uarray = (union Udata *)(VsInfodata[seg->ivsno-1].pPrm + seg->pprm[Sread.prmno].ioffset);
			memcpy(array, uarray, uarray->s[0]);
			Sread.prmno++;
		}
	}

	return;
}