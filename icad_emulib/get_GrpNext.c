#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"


char* get_GrpNext()
{
	char *pw, *pwc;
	char *ptr;
	int isize;

	ptr = NULL;

	isize = sizeof(struct  GroupInfo);

	if (isize > 0) {

		if (VsInfodata[act_vsno-1].pGrp == NULL) {
			pw = malloc(isize*GRP_BLK_SIZE);
			if (pw > 0) {
				VsInfodata[act_vsno-1].pGrp = pw;
				VsInfodata[act_vsno-1].iGmax = isize*GRP_BLK_SIZE;
				VsInfodata[act_vsno-1].iGuse = isize;
				VsInfodata[act_vsno-1].iGcount = 1;

				ptr = pw;

			}
			else {
				fprintf(stderr, " *** getGrpNext : malloc() エラー ***\n");
			}
		}
		else {

			// 領域サイズチェック
			if (VsInfodata[act_vsno-1].iGuse + isize < VsInfodata[act_vsno-1].iGmax)
			{
				ptr = VsInfodata[act_vsno-1].pGrp + VsInfodata[act_vsno-1].iGuse;
				VsInfodata[act_vsno-1].iGuse += isize;
				VsInfodata[act_vsno-1].iGcount++;
			}
			else {
				// 拡張
				pwc = VsInfodata[act_vsno-1].pGrp;
				if ((pw = realloc(pwc, VsInfodata[act_vsno-1].iGmax + isize*GRP_BLK_SIZE)) == NULL) {
					fprintf(stderr, " *** get_GrpNext : realloc() エラー ***\n");
				}
				else {
					VsInfodata[act_vsno-1].pGrp = pw;
					VsInfodata[act_vsno-1].iGmax += isize*GRP_BLK_SIZE;

					ptr = VsInfodata[act_vsno-1].pGrp + VsInfodata[act_vsno-1].iGuse;
					VsInfodata[act_vsno-1].iGuse += isize;
					VsInfodata[act_vsno-1].iGcount++;
				}

			}
		}
	}

	return ptr;
}
