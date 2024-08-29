#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// seupdt_
// �@�\		�w�肳�ꂽ�v�f�̏C���J�n��錾���܂��B
// ����
// in	*segid		�C������v�f�̗v�f���ʔԍ����w�肵�܂�
// in	*type		�v�f�^�C�v�ԍ���ύX����ꍇ�A�V�v�f�^�C�v�ԍ����w�肵�܂�(1��*type��255)
// 					�Ȃ��A�v�f�^�C�v�ԍ���ύX���Ȃ��ꍇ��0���w�肵�܂�
// in	*erase		dummy
// out	*ircode		���A���

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