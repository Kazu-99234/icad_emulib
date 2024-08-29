#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// seuskp_
// �@�\		�C���Ώۗv�f�̃v���~�e�B�u��V�v�f�ɃR�s�[�����ǂݔ�΂��܂��B
// ����
// out	*ircode		���A���

void seuskp_(int *ircode)
{
	struct  SegInfo *pSeg;

	*ircode = 0;
	err_syosai = 0;
	
	if ( cur_mode != 2 ) {
		*ircode = 12;
		err_syosai = 100;
		return;
	}
	
	pSeg = (struct  SegInfo *)	VsInfodata[Update_ivs].pSeg;
	
	if (Update_curprm >= pSeg[Update_segidx].ipcount) {
		*ircode = 8;
		err_syosai = 401;
	}
	else {
		Update_curprm++;
	}
}
