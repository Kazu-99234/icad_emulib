#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"
#include "comhansub.h"

void ssrseq_(int *entid, int *ircode)
{
	int	i, j, ismax, ivsno;
	int	actcls, acttyp, irc1, irc2;
	struct SegInfo *pSeg;
	*ircode = 0;
	err_syosai = 0;

	*entid = 0;
	
	if (Srseq.vsno == 0) {
		*ircode = 8;
		err_syosai = 700;
	}
	else {
		ivsno = Srseq.vsno;
		pSeg = (SegInfo *)VsInfodata[ivsno - 1].pSeg;
		ismax = VsInfodata[ivsno - 1].iScount;
		for (j = Srseq.isno; j < ismax; j++) {
//			if (pSeg[j].isysno > 0) {
//			if (pSeg[j].isysno > 0 && pSeg[j].idel == 0) {
			if (pSeg[j].isysno != 0 && pSeg[j].idel == 0) {

				actcls = pSeg[j].iclass;
				acttyp = pSeg[j].itype;
				irc1 = ChkBit(Srseq.iclass, actcls);
				irc2 = ChkBit(Srseq.type, acttyp);
				if (irc1 == 1 && irc2 == 1) {
					if( pSeg[j].isegno > 0 ) {
						*entid = pSeg[j].isegno;
					}
					else {
						*entid = pSeg[j].isysno;
					}
					Srseq.isno = j + 1;
					break;
				}
			}
		}
	}
}