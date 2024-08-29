#include "icad_emu.h"
#include "icad_emu_data.h"

// spsgra_
// 機能		指定された図形属性テーブルに、プリミティブ作成時の図形属性を設定します。

void spsgra_(int *atrid,int atrtbl[4],int *ircode)
{
	

	*ircode = 0;
	err_syosai = 0;

	if (*atrid < 0 || *atrid > 3) {
		*ircode = 12;
		err_syosai = 1;
	}
	else {
//		if ((atrtbl[0] < 1 || atrtbl[0] > 3) ||
//			(atrtbl[1] < 1 || atrtbl[1] > 6) ||
//			(atrtbl[2] < 1 || atrtbl[2] > 31)) {
//			*ircode = 12;
//			err_syosai = 2;
//		}
//		else {
			int	i;
			for (i = 0; i < 4; i++) {
				GraAttr[*atrid].atrtbl[i] = atrtbl[i];
			}
			
	
			// 不当な値の修正
			if (GraAttr[*atrid].atrtbl[2] < 1  ) {
				GraAttr[*atrid].atrtbl[2] = 1;
			}
	//		if ( atrtbl[0] == 4 && atrtbl[1] == 1 && atrtbl[2] == 5 ) 
	//		{
	//			i=4;
	//		}
	
	
//		}
	}

	return;
}	

