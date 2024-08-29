#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// sgcrt_
// 機能		指定された要素群をグループ/実像部品化します
// 引数
// in	*grpid		グループ/実像部品に割り当てるユーザ識別番号を整数で指定します(1以上)
// 					なお、ユーザ識別番号を割り当てない場合は本引数に0を指定します
// in	entids[]	グループ/実像部品化する要素識別番号を指定します
// in	*n			entids[]で指定した要素識別番号の個数を指定します
// in	*dim		グループ/実像部品の次元を指定します
// 					2 ： 2次元
// out	*ientid		作成されたグループ/実像部品のシステム識別番号の返答領域
// out	*ircode		復帰情報

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
