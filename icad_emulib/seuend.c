#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// seuend_
// 機能		要素の修正終了を宣言します。
// 引数
// out	*isegno		修正した要素のシステム識別番号の返答領域
// out	*ircode		復帰情報

void seuend_(int *isegno,int *ircode)
{
	int	ioff, i, icnt;
	char	*pt;
	struct  SegInfo *seg, *sego;

	*ircode = 0;
	err_syosai = 0;
	
	if (cur_mode != 2) {
		*ircode = 12;
		err_syosai = 101;
	}
	else {
		
		sego = (struct  SegInfo *)	VsInfodata[Update_ivs-1].pSeg;

		if ((pt = get_SegNext()) != NULL) {
			seg = (struct  SegInfo *)pt;
			seg->isegno = SegWK.isegno;
		//	seg->isysno = act_vsno*1000000 + (++iSyscnt[act_vsno-1]);
			seg->isysno = (act_vsno*1000000 + (++iSyscnt[act_vsno-1])) * -1;
			*isegno = seg->isysno;
			seg->ivsno = SegWK.ivsno;
			seg->itype = SegWK.itype;
			seg->iclass = SegWK.iclass;
			seg->ivisi = SegWK.ivisi;
			seg->idisp = SegWK.idisp;
			seg->idel = 0;
			seg->ipcount = SegWK.ipcount;
						
			icnt = 0;
			ioff = 0;
			for (i = 0; i < SegWK.ipcount;  i++) {
				if ((pt = get_PrmNext(SegWK.pprm[i].ipsize, &ioff)) != NULL) {
					seg->pprm[i].ipsize = SegWK.pprm[i].ipsize;
					seg->pprm[i].iptype = SegWK.pprm[i].iptype;
				//	seg->pprm[i].pdata = 0;
					seg->pprm[i].ioffset = ioff;
					seg->pprm[i].imode = SegWK.pprm[i].imode;
					seg->pprm[i].iwt = SegWK.pprm[i].iwt;
					seg->pprm[i].ifnt = SegWK.pprm[i].ifnt;
					seg->pprm[i].iclr = SegWK.pprm[i].iclr;
				//	memcpy(pt, SegWK.pprm[i].pdata, SegWK.pprm[i].ipsize);
					memcpy(pt, PrmWK + SegWK.pprm[i].ioffset, SegWK.pprm[i].ipsize);
					icnt++;

				}
				else {
					*ircode = 8;
					err_syosai = 1004;
				}
			}
			for (i = Update_curprm ; i < (sego + Update_segidx)->ipcount;  i++) {
				if ((pt = get_PrmNext((sego + Update_segidx)->pprm[i].ipsize, &ioff)) != NULL) {
					seg->pprm[icnt].ipsize = (sego + Update_segidx)->pprm[i].ipsize;
					seg->pprm[icnt].iptype = (sego + Update_segidx)->pprm[i].iptype;
					seg->pprm[icnt].ioffset = ioff;
					seg->pprm[icnt].imode = (sego + Update_segidx)->pprm[i].imode;
					seg->pprm[icnt].iwt = (sego + Update_segidx)->pprm[i].iwt;
					seg->pprm[icnt].ifnt = (sego + Update_segidx)->pprm[i].ifnt;
					seg->pprm[icnt].iclr = (sego + Update_segidx)->pprm[i].iclr;
					memcpy(pt, VsInfodata[Update_ivs-1].pPrm + (sego + Update_segidx)->pprm[i].ioffset, (sego + Update_segidx)->pprm[i].ipsize);
					icnt++;

				}
				else {
					*ircode = 8;
					err_syosai = 1004;
				}
			}
			
			seg->ipcount = icnt;

		}
		

		(sego + Update_segidx)->idel = 1;

		cur_mode = 0;		
		Update_ivs = 0;
		Update_segno = 0;
		Update_sysno = 0;
		Update_segidx = -1;
		Update_curprm = 0;
	}

}
