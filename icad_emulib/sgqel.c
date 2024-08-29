#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// sgqel_
// 機能		指定されたグループ/実像部品の構成要素の要素識別番号を得ます。
// 引数
// in	*grpid		グループ/実像部品の要素識別番号を指定します
// out	entids[]	構成要素の要素識別番号返答領域
// 					ユーザ識別番号が割り当てられている場合はユーザ識別番号、割り当てられていない場合はシステム識別番号が返されます
// in	*size		得たい要素識別番号の数を指定します
// in	*start		要素識別番号を返す開始要素のグループ/実像部品内の相対番号を指定します
// 					本引数で指定された要素から*sizeで指定された数だけの要素識別番号が返されます
// out	*out		実際にentids[]に返された要素識別番号の個数の返答領域
// out	*ircode		復帰情報

void sgqel_(int *grpid, int entids[], int *size, int *start, int *out, int *ircode)
{
	int	i, j, igmax, ivsno, icnt;
	struct GroupInfo *grp;

	
	*ircode = 0;
	err_syosai = 0;
	
	*out=0;
	icnt=0;

	for (ivsno=1;ivsno <= 500;ivsno++) {
		if ( VsInfodata[ivsno - 1].vsno == 0 ) continue;
		
		grp = (GroupInfo *)VsInfodata[ivsno - 1].pGrp;
		igmax = VsInfodata[ivsno - 1].iGcount;

		for (i = 0; i < igmax; i++) {
			if (((grp + i)->isegno == *grpid || (grp + i)->isysno == *grpid ) && (grp + i)->idel == 0) {
				break;
			}
		}
		if (i < igmax) {
			for (j= *start; j < (grp + i)->ientcnt; j++) {
				entids[icnt] = grp->igent[j];
				icnt++;
				if (icnt == *size)  break;
				
			}
			break;
		}
	}
	
	*out = icnt;
				
	return;
}

