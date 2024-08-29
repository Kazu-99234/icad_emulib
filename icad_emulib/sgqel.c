#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// sgqel_
// �@�\		�w�肳�ꂽ�O���[�v/�������i�̍\���v�f�̗v�f���ʔԍ��𓾂܂��B
// ����
// in	*grpid		�O���[�v/�������i�̗v�f���ʔԍ����w�肵�܂�
// out	entids[]	�\���v�f�̗v�f���ʔԍ��ԓ��̈�
// 					���[�U���ʔԍ������蓖�Ă��Ă���ꍇ�̓��[�U���ʔԍ��A���蓖�Ă��Ă��Ȃ��ꍇ�̓V�X�e�����ʔԍ����Ԃ���܂�
// in	*size		�������v�f���ʔԍ��̐����w�肵�܂�
// in	*start		�v�f���ʔԍ���Ԃ��J�n�v�f�̃O���[�v/�������i���̑��Δԍ����w�肵�܂�
// 					�{�����Ŏw�肳�ꂽ�v�f����*size�Ŏw�肳�ꂽ�������̗v�f���ʔԍ����Ԃ���܂�
// out	*out		���ۂ�entids[]�ɕԂ��ꂽ�v�f���ʔԍ��̌��̕ԓ��̈�
// out	*ircode		���A���

void sgqel_(int *grpid, int entids[], int *size, int *start, int *out, int *ircode)
{
	int	i, j, igmax, ivsno, icnt;
	struct GroupInfo *grp;

	
	*ircode = 0;
	err_syosai = 0;
	
	*out=0;
	icnt=0;

	for (ivsno=1;ivsno <= 500;ivsno++) {
		if ( VsInfodata[ivsno - 1].vsno == 0 ) continue;
		
		grp = (GroupInfo *)VsInfodata[ivsno - 1].pGrp;
		igmax = VsInfodata[ivsno - 1].iGcount;

		for (i = 0; i < igmax; i++) {
			if (((grp + i)->isegno == *grpid || (grp + i)->isysno == *grpid ) && (grp + i)->idel == 0) {
				break;
			}
		}
		if (i < igmax) {
			for (j= *start; j < (grp + i)->ientcnt; j++) {
				entids[icnt] = grp->igent[j];
				icnt++;
				if (icnt == *size)  break;
				
			}
			break;
		}
	}
	
	*out = icnt;
				
	return;
}

