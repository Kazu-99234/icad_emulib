#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// secpy2_
// 機能		指定された2 次元要素を要素作成VS へ複写します。
// 引数
// in	*entid	複写元の要素の要素識別番号を指定します
// in	*entno	複写先の要素のユーザ識別番号を指定します(1 以上)
// 				なお、ユーザ識別番号を割当てない場合は、本引数に0 を指定します
// out	*pesadr	複写後の要素に付与されたシステム識別番号返答領域
// out	*ircode	復帰情報

void secpy2_(int *entid,int *entno,int *pesadr,int *ircode)
{
	int		i, j, ismax, ipmax, ivsno, isize, ia, ioff;
	struct  SegInfo *pSeg;
	char	*pt, *pPrm;
	struct  SegInfo *seg;

	*ircode = 0;
	err_syosai = 0;
	
	
	if (cur_mode != 0) {
		*ircode = 12;
		err_syosai = 101;
	}
	else {
	
		for (ivsno=1;ivsno <= 500;ivsno++) {
			if ( VsInfodata[ivsno - 1].vsno == 0 ) continue;
		
			pSeg = (struct  SegInfo *)	VsInfodata[ivsno-1].pSeg;
			ismax = VsInfodata[ivsno-1].iScount;
			pPrm = VsInfodata[ivsno-1].pPrm;

			for (j = 0; j < ismax; j++) {
				if (pSeg[j].idel == 1 ) continue;
				if (pSeg[j].isegno == *entid || pSeg[j].isysno == *entid) {
					break;
				}
			}

			if ( j < ismax ) {
				if ((pt = get_SegNext()) != NULL) {
					seg = (struct  SegInfo *)pt;
					seg->ivsno = act_vsno;
					seg->isegno = 0;
					if ( *entno > 0 ) seg->isegno = *entno;
				//	seg->isysno = act_vsno*1000000 + (++iSyscnt[act_vsno-1]);
					seg->isysno = (act_vsno*1000000 + (++iSyscnt[act_vsno-1])) * -1;
					seg->itype = pSeg[j].itype;
					seg->iclass = pSeg[j].iclass;
					seg->ivisi = pSeg[j].ivisi;
					seg->idisp = pSeg[j].idisp;
					seg->idel = pSeg[j].idel;
					seg->ipcount = pSeg[j].ipcount;
			
					ioff = 0;
					for (i = 0; i < pSeg[j].ipcount; i++) {
						if ((pt = get_PrmNext(pSeg[j].pprm[i].ipsize, &ioff)) != NULL) {
							seg->pprm[i].ipsize = pSeg[j].pprm[i].ipsize;
							seg->pprm[i].iptype = pSeg[j].pprm[i].iptype;
							seg->pprm[i].ioffset = ioff;
							seg->pprm[i].imode = pSeg[j].pprm[i].imode;
							seg->pprm[i].iwt = pSeg[j].pprm[i].iwt;
							seg->pprm[i].ifnt = pSeg[j].pprm[i].ifnt;
							seg->pprm[i].iclr = pSeg[j].pprm[i].iclr;
							memcpy(pt, pPrm + pSeg[j].pprm[i].ioffset,pSeg[j].pprm[i].ipsize);
						}
						else {
							*ircode = 8;
							err_syosai = 1004;
						}
					}
					break;
				}
			}
		}

		if (ivsno > 500) {
			*ircode = 8;
			err_syosai = 311;
		}
	}
	


}
