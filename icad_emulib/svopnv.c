#define _CRT_SECURE_NO_WARNINGS
#include <memory.h>
#include <string.h>
#include "icad_emu.h"
#include "icad_emu_data.h"



void svopnv_(char vsname[8], int *vsno, int *ircode)
{
	char	cwk[9];
	int		i, ino;

	*ircode = 0;
	ino = -1;

	memcpy(cwk, vsname, 8);
	cwk[8] = 0;

	if (strlen(cwk)) {
		for (i = 0; i < 500; i++) {
			if (VsInfodata[i].vsno > 0) {
				if (strcmp(cwk, VsInfodata[i].vsname) == 0) {
					*ircode = 8;
					err_syosai = 601;
					break;
				}
			}
			else {
				if (ino == -1)  ino = i;
			}
		}

		if ( ino >= 0 ) { 
			VsInfodata[ino].vsno = ino + 1;
			strcpy(VsInfodata[ino].vsname, cwk);
			*vsno = ino + 1;
		}
		else {
			*ircode = 8;
			err_syosai = 1001;
		}

	}
	else {
		*ircode = 8;
		err_syosai = 999;
	}

	return;

}