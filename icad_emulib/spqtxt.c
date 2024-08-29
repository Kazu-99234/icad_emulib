#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// spqtxt_
// 機能		指定された文字属性テーブルから文字属性を得ます。

void spqtxt_(int *atrid, float atrtb1[6], int atrtb2[2], int *font, int *ircode)
{
	*ircode = 0;
	err_syosai = 0;

	if (*atrid < 0 || *atrid > 3) {
		*ircode = 12;
		err_syosai = 1;
	}
	else {

			int	i;

			for (i = 0; i < 6; i++) {
				atrtb1[i] = TxtAttr[*atrid].atrtb1[i];
			}

			for (i = 0; i < 2; i++) {
				atrtb2[i] = TxtAttr[*atrid].atrtb2[i];
			}
	}

	return;

}