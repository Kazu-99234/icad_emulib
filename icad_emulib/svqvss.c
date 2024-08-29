#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

void svqvss_(int *vsno, char vsname[8], int status[5], int *ircode)
{
	int		i;

	*ircode = 0;
	err_syosai = 0;


	if (*vsno > 0 && *vsno <= 500) {

		for (i = 0; i < 500; i++) {
			if (VsInfodata[i].vsno == *vsno) {
				memcpy(vsname, VsInfodata[i].vsname, 8);
				status[0] = VsInfodata[i].iScount;
				status[1] = 0;
				status[2] = 0;
				status[3] = 0;
				status[4] = 0;

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


	return;

}
