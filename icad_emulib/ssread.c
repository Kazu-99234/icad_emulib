#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"


void ssread_(int *entid, int infary[16])
{
	int	i, ismax, ivsno;
	int ircode;
	struct SegInfo *seg;

	ircode = 0;
	err_syosai = 0;

	memset(infary, 0, 4 * 16);

	for (ivsno=1;ivsno <= 500;ivsno++) {
		if ( VsInfodata[ivsno - 1].vsno == 0 ) continue;
		
		seg = (SegInfo *)VsInfodata[ivsno - 1].pSeg;
		ismax = VsInfodata[ivsno - 1].iScount;
		for (i = 0; i < ismax; i++) {
			
			if ((seg + i)->idel == 1) continue;
			
			if ((seg + i)->isegno == *entid) {
				if ((seg + i)->idel != 0) infary[0] = 100; // íœÏ
				infary[1] = (seg + i)->isegno;
				infary[2] = 0;
				infary[3] = ivsno;
				infary[4] = (seg + i)->iclass;
				infary[5] = (seg + i)->itype;
				infary[6] = (seg + i)->idisp;
				infary[7] = 0;
				infary[8] = 0;
				infary[9] = 0;
				infary[10] = 0;
				infary[11] = (seg + i)->ipcount;
				infary[12] = 0;
				infary[13] = 0;
				infary[14] = 0;
				infary[15] = 0;

				Sread.vsno = ivsno;
				Sread.segno = (seg + i)->isegno;
				Sread.prmno = 0;
				Sread.seg = (seg + i);
				break;
			}
			else if ((seg + i)->isysno == *entid) {
				if ((seg + i)->idel != 0) infary[0] = 100; // íœÏ
//				infary[1] = 0;
				infary[1] = (seg + i)->isegno;
				infary[2] = 0;
				infary[3] = ivsno;
				infary[4] = (seg + i)->iclass;
				infary[5] = (seg + i)->itype;
				infary[6] = (seg + i)->idisp;
				infary[7] = 0;
				infary[8] = 0;
				infary[9] = 0;
				infary[10] = 0;
				infary[11] = (seg + i)->ipcount;
				infary[12] = 0;
				infary[13] = 0;
				infary[14] = 0;
				infary[15] = 0;

				Sread.vsno = ivsno;
				Sread.segno = (seg + i)->isegno;
				Sread.prmno = 0;
				Sread.seg = (seg + i);
				
				break;
			}
		}
		
		if (i < ismax) break;
	}

	if (ivsno > 500) {
		ircode = 12;
		err_syosai = 321;
	}

	return;

}