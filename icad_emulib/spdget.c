#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// spdget_
// �@�\		�w��v�f�̎w��v���~�e�B�u�f�[�^��ǂݍ��݂܂��B
// in	*entid		�v���~�e�B�u�f�[�^�𓾂�v�f�̗v�f���ʔԍ����w�肵�܂�
// in	*prmno		�v���~�e�B�u�ԍ����w�肵�܂�
// out	array[4096]	�v���~�e�B�u�f�[�^�̕ԓ��̈�
// out	*ircode		���A���

void spdget_(int *entid, int *prmno, char array[4096], int *ircode)
{
	int	i, ismax, ivsno;

	struct SegInfo *seg;
	union Udata{
		int	i[1024];
		short	s[248];
		char	c[4096];
		double	d[512];
		float	f[1024];
	} *uarray;

	*ircode = 0;
	err_syosai = 0;
	
	uarray = (union Udata *)array;
	
//	printf("SPDGET ent=%d  prm=%d\n",*entid, *prmno);

	for (ivsno=1;ivsno <= 500;ivsno++) {
		if ( VsInfodata[ivsno - 1].vsno == 0 ) continue;
		
		seg = (SegInfo *)VsInfodata[ivsno - 1].pSeg;
		ismax = VsInfodata[ivsno - 1].iScount;
		
		for (i = 0; i < ismax; i++) {
			if ((seg + i)->isegno == *entid && (seg + i)->idel == 0) {
		//		if ( (seg + i)->idel == 1 ) {
		//			*ircode = 8;
		//			err_syosai = 311;
		//			return;
		//		}
				if (*prmno > 0 && *prmno <= (seg + i)->ipcount) {
					struct PrmInfo *prm = &((seg + i)->pprm[*prmno - 1]);
				//	memcpy(array, prm->pdata, prm->ipsize);
					memcpy(array, VsInfodata[ivsno - 1].pPrm + prm->ioffset, prm->ipsize);
					break;
				}
		//		else {
		//			*ircode = 8;
		//			err_syosai = 401;
		//		}
			}
			else if ((seg + i)->isysno == *entid && (seg + i)->idel == 0) {
				if ( (seg + i)->idel == 1 ) {
					*ircode = 8;
					err_syosai = 311;
					return;
				}
				if (*prmno > 0 && *prmno <= (seg + i)->ipcount) {
					struct PrmInfo *prm = &((seg + i)->pprm[*prmno - 1]);
				//	memcpy(array, prm->pdata, prm->ipsize);
					memcpy(array, VsInfodata[ivsno - 1].pPrm + prm->ioffset, prm->ipsize);
					break;
				}
			}
		}
		if (i < ismax) break;

	}

	if (ivsno > 500) {
		*ircode = 8;
		err_syosai = 311;
	}

	return;

}