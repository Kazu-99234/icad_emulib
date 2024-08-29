#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"


void sbterm_(int *ircode)
{
	int		i;

	//@I—¹ˆ—
	for (i = 0; i < 500; i++)
	{
		if (VsInfodata[i].pSeg != NULL) {
			free(VsInfodata[i].pSeg);
			VsInfodata[i].pSeg = NULL;
		}

		if (VsInfodata[i].pPrm != NULL) {
			free(VsInfodata[i].pPrm);
			VsInfodata[i].pPrm = NULL;
		}

		if (VsInfodata[i].pGrp != NULL) {
			free(VsInfodata[i].pGrp);
			VsInfodata[i].pGrp = NULL;
		}

	}
	act_vsno = 0;

	memset(GraAttr, 0, sizeof(GraAttr));
	cur_gra_atr = 0;

	memset(TxtAttr, 0, sizeof(TxtAttr));
	cur_txt_atr = 0;

	*ircode = 0;

	return;

}