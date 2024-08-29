#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// seupdt_
// 機能		指定された要素の修正開始を宣言します。
// 引数
// in	*segid		修正する要素の要素識別番号を指定します
// in	*type		要素タイプ番号を変更する場合、新要素タイプ番号を指定します(1≦*type≦255)
// 					なお、要素タイプ番号を変更しない場合は0を指定します
// in	*erase		dummy
// out	*ircode		復帰情報

void seupdt_(int *segid,int *type,int *erase,int *ircode)
{
	
	*ircode = 0;
	err_syosai = 0;


	if (cur_mode != 0) {
		*ircode = 12;
		err_syosai = 101;
	}
	else {
		int		j, ismax, ipmax, ivsno;
		struct  SegInfo *pSeg;
		
		for (ivsno=1;ivsno <= 500;ivsno++) {
			if ( VsInfodata[ivsno - 1].vsno == 0 ) continue;
	
			pSeg = (struct  SegInfo *)	VsInfodata[ivsno-1].pSeg;
			ismax = VsInfodata[ivsno-1].iScount;
			
			for (j = 0; j < ismax; j++) {
				
				if ( pSeg[j].idel == 1 )  continue;
				
				if (pSeg[j].isegno == *segid || pSeg[j].isysno == *segid) {
					
					memset((char *)&SegWK, 0, sizeof(SegWK));
					SegWK.ivsno = pSeg[j].ivsno;
					SegWK.ivisi = pSeg[j].ivisi;
					SegWK.idisp = pSeg[j].idisp;
					SegWK.itype = pSeg[j].itype;
					if ( *type != 0 ) SegWK.itype = *type;
					SegWK.iclass = pSeg[j].iclass;
					SegWK.isegno = pSeg[j].isegno;
					
					cur_mode = 2;
					Update_ivs = ivsno;
					Update_segno = pSeg[j].isegno;
					Update_sysno = pSeg[j].isysno;
					Update_segidx = j;
					Update_curprm = 0;
				//	if ( *type > 0 ) {
				//		pSeg[j].itype = *type;
				//	}
					break;
				}
			}
			if ( j < ismax ) break;
		}
		if (ivsno > 500) {
			*ircode = 8;
			err_syosai = 311;
		}
	
	}
}