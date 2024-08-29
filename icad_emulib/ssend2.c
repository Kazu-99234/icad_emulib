#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

void ssend2_(int *segno, int *mode, int *isegno, int *ircode)
{

	int	ioff;
	
	*ircode = 0;
	err_syosai = 0;
	
	if (cur_mode != 1) {
		*ircode = 12;
		err_syosai = 100;
	}
	else {

		if (*segno < 0) {
			*ircode = 12;
			err_syosai = 1;
		}
		else {
			if (*mode != 0 && *mode != 1) {
				*ircode = 12;
				err_syosai = 2;
			}
			else {
				if (SegWK.ipcount == 0) {
					*ircode = 4;
					err_syosai = 100;
				}
				else {
					char *pt;
					struct  SegInfo *seg;
					int	i;
					if ((pt = get_SegNext()) != NULL) {
						seg = (struct  SegInfo *)pt;
						SegWK.isegno = *segno;
					//	SegWK.isysno = act_vsno*1000000 + (++iSyscnt[act_vsno-1]);
						SegWK.isysno = (act_vsno*1000000 + (++iSyscnt[act_vsno-1])) * -1;
						*isegno = SegWK.isysno;
					//	*seg = SegWK;
						seg->ivsno = SegWK.ivsno;
						seg->isegno = SegWK.isegno;
						seg->isysno = SegWK.isysno;
						seg->itype = SegWK.itype;
						seg->iclass = SegWK.iclass;
						seg->ivisi = SegWK.ivisi;
						seg->idisp = SegWK.idisp;
						seg->idel = SegWK.idel;
						seg->ipcount = SegWK.ipcount;
						
					//	if ( seg->ipcount >= 255 ) {
					//		seg->idel = SegWK.idel;
					//	}
						
						ioff = 0;
						for (i = 0; i < SegWK.ipcount; i++) {
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

							}
							else {
								*ircode = 8;
								err_syosai = 1004;
							}
						}
						cur_mode = 0;
					}
					else {
						*ircode = 8;
						err_syosai = 1004;
					}

				}
			}

		}
	}
	cur_mode = 0;

	return;
}
