#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

void ssrstr_(int *dim, int *vswfno, char cclass[32], char type[32], int *ircode)
{
	int	i;

	*ircode = 0;
	err_syosai = 0;

	if (*vswfno < 1 || *vswfno > 500) {
		*ircode = 12;
		err_syosai = 2;
	}
	else {
		for (i = 0; i < 500; i++) {
			if (VsInfodata[i].vsno == *vswfno) {
				Srseq.vsno = *vswfno;
				memcpy(Srseq.iclass, cclass, 32);
				memcpy(Srseq.type, type, 32);
				Srseq.isno = 0;
				break;
			}

			if (i == 500) {
				*ircode = 8;
				err_syosai = 603;
			}
		}
	}

	return;

}