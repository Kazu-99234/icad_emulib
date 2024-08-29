#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// sgfree_
// �@�\		�w�肳�ꂽ�O���[�v/�������i���������܂��B
// ����
// in	*grpid		�O���[�v/�������i�̗v�f���ʔԍ����w�肵�܂�
// out	*ircode		���A���

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

