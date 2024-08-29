#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// semdlt_
// 機能		指定された要素を削除します。
// 引数
// in	entids[]	削除する要素の要素識別番号を指定します
// in	*nument		削除する要素の個数を指定します
// in	*incrmt		要素識別番号の取出し間隔を指定します
// in	*mode		dummy
// out	*ircode		復帰情報

void semdlt_(int entids[], int *nument, int *incrmt, int *mode, int *ircode)
{


	*ircode = 0;
	err_syosai = 0;


	if (cur_mode != 0) {
		*ircode = 12;
		err_syosai = 101;
	}
	else {
		if (*nument < 1  ) {
			*ircode = 12;
			err_syosai = 2;
		}
		else {
			if (*incrmt < 1) {
				*ircode = 12;
				err_syosai = 3;
			}
			else {
					if (*mode != 0 && *mode != 1) {
						*ircode = 12;
						err_syosai = 3;
					}
					else {
						int		i, j, ismax, ivsno;
						short	*ichk;
						int		icnt;
						
//						ichk = malloc( sizeof(short) * *nument);
//						memset(ichk, 0, sizeof(short) * *nument);
						icnt=0;
						
						for (ivsno=1;ivsno <= 500;ivsno++) {
							if ( VsInfodata[ivsno - 1].vsno == 0 ) continue;

							struct  SegInfo *pSeg = (struct  SegInfo *)	VsInfodata[ivsno - 1].pSeg;
							ismax = VsInfodata[ivsno - 1].iScount;

							for (i = 0; i < *nument; i++) {
								
//								if ( *(ichk+i) != 0 )  continue;
								
								for (j = 0; j < ismax; j++) {
									if (pSeg[j].isegno == entids[i * (*incrmt)] || pSeg[j].isysno == entids[i * (*incrmt)]) {
//									if (pSeg[j].isysno == entids[i * (*incrmt)]) {
										pSeg[j].ipcount = 0;
										pSeg[j].idel = 1;
	
										pSeg[j].isegno = 0;
										pSeg[j].isysno = 0;
										
//										*(ichk+i) = 1;
//										icnt++;
										break;
									}
//									if (icnt == *nument) break;
								}
//								if (icnt == *nument) break;
							}
//							if (icnt == *nument) break;
						}
						
//						free(ichk);
					}


			}
		}

	}

	return;

}