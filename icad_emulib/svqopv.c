
#include "icad_emu.h"
#include "icad_emu_data.h"


void svqopv_(int vsno[100], int *cnt)
{
	int	i, icnt;

	*cnt = 0;
	icnt = 0;

	for (i = 0; i < 500; i++) {
		if (VsInfodata[i].vsno != 0) {
			vsno[icnt] = VsInfodata[i].vsno;
			icnt++;
			if (icnt >= 100) {
				icnt = 0;
				break; 
			}
		}
	}

	*cnt = icnt;

	return;

}