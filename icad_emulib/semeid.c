#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// semeid_
// 機能		指定された要素のユーザ識別番号を変更します。
// 引数
// in	entids[]	変更する要素の要素識別番号を指定します
// in	*nument		変更する要素の個数を指定します
// in	*incrmt		entids[]及びnewents[]で指定された要素識別番号の取出し間隔を指定します
// in	newents[]	新しく割り当てる要素の要素識別番号を指定します
// out	*ircode		復帰情報

void semeid_(int entids[], int *nument, int *incrmt, int newents[], int *ircode)
{
	*ircode = 0;
	err_syosai = 0;

	if (cur_mode != 0) {
		*ircode = 12;
		err_syosai = 101;
	}
	else {
		if (*nument < 1) {
			*ircode = 12;
			err_syosai = 2;
		}
		else {
			if (*incrmt < 1) {
				*ircode = 12;
				err_syosai = 3;
			}
			else {

				int		i, j, ipmax, ivsno;
				
				for (ivsno=1;ivsno <= 500;ivsno++) {
					if ( VsInfodata[ivsno - 1].vsno == 0 ) continue;
					
					struct  SegInfo *pSeg = (struct  SegInfo *)	VsInfodata[ivsno-1].pSeg;
					ipmax = VsInfodata[ivsno-1].iScount;

					for (i = 0; i < *nument; i++) {
						for (j = 0; j < ipmax; j++) {
						//	if (pSeg[j].isegno == entids[i * (*incrmt)] || pSeg[j].isysno == entids[i * (*incrmt)]) {
							if ((pSeg[j].isegno == entids[i * (*incrmt)] && pSeg[j].idel == 0)  ||
								(pSeg[j].isysno == entids[i * (*incrmt)] && pSeg[j].idel == 0)) {
								pSeg[j].isegno = newents[i * (*incrmt)];
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