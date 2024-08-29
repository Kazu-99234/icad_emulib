#include <string.h>
#include "icad_emu.h"
#include "icad_emu_data.h"


void svqvsn_(char vsname[8], int *vsno)
{
	int		i;
	char	cwk[9];

	*vsno = 0;
	memcpy(cwk, vsname, 8);
	cwk[8] = 0;

	for (i = 0; i < 500; i++) {
		if (VsInfodata[i].vsno != 0) {
			if (strcmp(VsInfodata[i].vsname, cwk) == 0) {
				*vsno = VsInfodata[i].vsno;
				break;
			}
		}
	}

	return;

}
