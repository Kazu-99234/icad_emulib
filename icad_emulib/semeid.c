#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// semeid_
// �@�\		�w�肳�ꂽ�v�f�̃��[�U���ʔԍ���ύX���܂��B
// ����
// in	entids[]	�ύX����v�f�̗v�f���ʔԍ����w�肵�܂�
// in	*nument		�ύX����v�f�̌����w�肵�܂�
// in	*incrmt		entids[]�y��newents[]�Ŏw�肳�ꂽ�v�f���ʔԍ��̎�o���Ԋu���w�肵�܂�
// in	newents[]	�V�������蓖�Ă�v�f�̗v�f���ʔԍ����w�肵�܂�
// out	*ircode		���A���

void semeid_(int entids[], int *nument, int *incrmt, int newents[], int *ircode)
{
	*ircode = 0;
	err_syosai = 0;

	if (cur_mode != 0) {
		*ircode = 12;
		err_syosai = 101;
	}
	else {
		if (*nument < 1) {
			*ircode = 12;
			err_syosai = 2;
		}
		else {
			if (*incrmt < 1) {
				*ircode = 12;
				err_syosai = 3;
			}
			else {

				int		i, j, ipmax, ivsno;
				
				for (ivsno=1;ivsno <= 500;ivsno++) {
					if ( VsInfodata[ivsno - 1].vsno == 0 ) continue;
					
					struct  SegInfo *pSeg = (struct  SegInfo *)	VsInfodata[ivsno-1].pSeg;
					ipmax = VsInfodata[ivsno-1].iScount;

					for (i = 0; i < *nument; i++) {
						for (j = 0; j < ipmax; j++) {
						//	if (pSeg[j].isegno == entids[i * (*incrmt)] || pSeg[j].isysno == entids[i * (*incrmt)]) {
							if ((pSeg[j].isegno == entids[i * (*incrmt)] && pSeg[j].idel == 0)  ||
								(pSeg[j].isysno == entids[i * (*incrmt)] && pSeg[j].idel == 0)) {
								pSeg[j].isegno = newents[i * (*incrmt)];
								break;
							}
						}
					}

				}

			}
		}

	}

	return;

}