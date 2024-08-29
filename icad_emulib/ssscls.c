#include "icad_emu.h"
#include "icad_emu_data.h"

void ssscls_(int *iclass,int *ircode)
{
	*ircode = 0;
	err_syosai = 0;
	
	if ( *iclass < 0 || *iclass > 255 ) {
		*ircode = 12;
		err_syosai = 1;
	}
	else {
		if (cur_mode != 0 ) {
			*ircode = 12;
			err_syosai = 100;
		}
		else {
			VsInfodata[act_vsno-1].iclass = *iclass;
			cur_class = *iclass;
		}
	}
	
	return;
}
