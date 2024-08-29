#include "icad_emu.h"
#include "icad_emu_data.h"

void sssvs_(int *vsno, int *ircode)
{
//	if (cur_mode == 0) {
		if (*vsno > 0 && *vsno <= 500) {
			if (VsInfodata[*vsno - 1].vsno != 0)
			{
				act_vsno = *vsno;
				*ircode = 0;
				err_syosai = 0;
				
				cur_mode = 0; //ƒGƒ‰[‘Î‰ž
			}
			else {
				*ircode = 12;
				err_syosai = 1;
			}

		}
		else {
			*ircode = 12;
			err_syosai = 1;
		}
//	}
//	else {
//		*ircode = 12;
//		err_syosai = 100;
//	}

	return;
}