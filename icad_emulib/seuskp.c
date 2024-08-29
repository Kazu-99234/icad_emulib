#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// seuskp_
// 機能		修正対象要素のプリミティブを新要素にコピーせず読み飛ばします。
// 引数
// out	*ircode		復帰情報

void seuskp_(int *ircode)
{
	struct  SegInfo *pSeg;

	*ircode = 0;
	err_syosai = 0;
	
	if ( cur_mode != 2 ) {
		*ircode = 12;
		err_syosai = 100;
		return;
	}
	
	pSeg = (struct  SegInfo *)	VsInfodata[Update_ivs].pSeg;
	
	if (Update_curprm >= pSeg[Update_segidx].ipcount) {
		*ircode = 8;
		err_syosai = 401;
	}
	else {
		Update_curprm++;
	}
}
