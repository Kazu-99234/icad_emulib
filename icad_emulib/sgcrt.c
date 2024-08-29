#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// sgcrt_
// �@�\		�w�肳�ꂽ�v�f�Q���O���[�v/�������i�����܂�
// ����
// in	*grpid		�O���[�v/�������i�Ɋ��蓖�Ă郆�[�U���ʔԍ��𐮐��Ŏw�肵�܂�(1�ȏ�)
// 					�Ȃ��A���[�U���ʔԍ������蓖�ĂȂ��ꍇ�͖{������0���w�肵�܂�
// in	entids[]	�O���[�v/�������i������v�f���ʔԍ����w�肵�܂�
// in	*n			entids[]�Ŏw�肵���v�f���ʔԍ��̌����w�肵�܂�
// in	*dim		�O���[�v/�������i�̎������w�肵�܂�
// 					2 �F 2����
// out	*ientid		�쐬���ꂽ�O���[�v/�������i�̃V�X�e�����ʔԍ��̕ԓ��̈�
// out	*ircode		���A���

void sgcrt_(int *grpid, int entids[], int *n, int *dim, int *ientid, int *ircode)
{
	int		i, icnt;
	
	
	*ircode = 0;
	err_syosai = 0;

	if (cur_mode != 0) {
		*ircode = 12;
		err_syosai = 100;
	}
	else {
		
		if ( *n > 0 ) {
			char *pt;
			struct  GroupInfo *grp;
			
			icnt=0;
			for (i=0; i < *n;i++) {
				if ( entids[i] < 1 ) continue;
				icnt++;
			}
			
			if ( icnt > 0 ) {
				if ((pt = get_GrpNext()) != NULL) {
					grp = (struct  GroupInfo *)pt;
					grp->ivsno = act_vsno;
					grp->isegno = *grpid;
				//	grp->isysno = act_vsno*1000000 + (++iSyscnt[act_vsno-1]);
					grp->isysno = (act_vsno*1000000 + (++iSyscnt[act_vsno-1])) * -1;
					
					for(i=0;i < icnt;i++) {
						grp->igent[i] = entids[i];
					}
					grp->ientcnt = icnt;
					
				}
			}
			else {
				*ircode = 12;
				err_syosai = 2;
			}
		}
		else {
			*ircode = 12;
			err_syosai = 3;
		}
		
	}

	return;
}
