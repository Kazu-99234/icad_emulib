#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

void sversv_(int *vsno, int *ircode)
{
	int	i;

	*ircode = 0;
	err_syosai = 0;

	if (cur_mode == 0) {

		if (*vsno > 0 && *vsno <= 500) {
			for (i = 0; i < 500; i++) {
				if (VsInfodata[i].vsno == *vsno) {
					free(VsInfodata[i].pSeg);
					free(VsInfodata[i].pPrm);
					memset((void *)(&VsInfodata[i]), 0, sizeof(struct  VsInfo));
					break;
				}
			}
			if (i == 500) {
				*ircode = 8;
				err_syosai = 603;

			}
		}
		else {
			*ircode = 12;
			err_syosai = 1;
		}
	}
	else {
		*ircode = 12;
		err_syosai = 101;
	}

	return;

}