#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// sgfree_
// 機能		指定されたグループ/実像部品を解除します。
// 引数
// in	*grpid		グループ/実像部品の要素識別番号を指定します
// out	*ircode		復帰情報

void sgfree_(int *grpid, int *ircode)
{
	int	i, igmax, ivsno;
	struct GroupInfo *grp;

	
	*ircode = 0;
	err_syosai = 0;

	for (ivsno=1;ivsno <= 500;ivsno++) {
		if ( VsInfodata[ivsno - 1].vsno == 0 ) continue;
		
		grp = (GroupInfo *)VsInfodata[ivsno - 1].pGrp;
		igmax = VsInfodata[ivsno - 1].iGcount;

		for (i = 0; i < igmax; i++) {
			if (((grp + i)->isegno == *grpid || (grp + i)->isysno == *grpid ) && (grp + i)->idel == 0) {
				(grp + i)->idel = 1;
				break;
			}
		}
		if ( i < igmax )  break;
	}
	
	return;
}

