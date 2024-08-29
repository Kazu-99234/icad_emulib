#include "icad_emu.h"
#include "icad_emu_data.h"

// spstxt_
// 機能		指定された文字属性テーブルにプリミティブ作成時の文字属性を設定します。

void spstxt_(int *atrid, float atrtb1[6], int atrtb2[2], int *font, int *ircode)
{

	*ircode = 0;
	err_syosai = 0;

	if (*atrid < 0 || *atrid > 3) {
		*ircode = 12;
		err_syosai = 1;
	}
	else {
		if ((atrtb2[0] < 1 || atrtb2[0] > 31) ||
			(atrtb2[1] < 1 || atrtb2[1] > 3) ) {
			*ircode = 12;
			err_syosai = 2;
		}
		else {
			int	i;

			for (i = 0; i < 6; i++) {
				TxtAttr[*atrid].atrtb1[i] = atrtb1[i];
			}

			for (i = 0; i < 2; i++) {
				TxtAttr[*atrid].atrtb2[i] = atrtb2[i];
			}
		}
	}

	return;


}
