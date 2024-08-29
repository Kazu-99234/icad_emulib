#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"


char* get_SegNext()
{
	char *pw, *pwc;
	char *ptr;
	int isize;

	ptr = NULL;

	isize = sizeof(struct  SegInfo);

	if (isize > 0) {

		if (VsInfodata[act_vsno-1].pSeg == NULL) {
			pw = malloc(isize*SEG_BLK_SIZE);
			if (pw > 0) {
				VsInfodata[act_vsno-1].pSeg = pw;
				VsInfodata[act_vsno-1].iSmax = isize*SEG_BLK_SIZE;
				VsInfodata[act_vsno-1].iSuse = isize;
				VsInfodata[act_vsno-1].iScount = 1;

				ptr = pw;

			}
			else {
				fprintf(stderr, " *** getSegNext : malloc() エラー ***\n");
			}
		}
		else {

			// 領域サイズチェック
			if (VsInfodata[act_vsno-1].iSuse + isize < VsInfodata[act_vsno-1].iSmax)
			{
				ptr = VsInfodata[act_vsno-1].pSeg + VsInfodata[act_vsno-1].iSuse;
				VsInfodata[act_vsno-1].iSuse += isize;
				VsInfodata[act_vsno-1].iScount++;
			}
			else {
				// 拡張
				pwc = VsInfodata[act_vsno-1].pSeg;
				if ((pw = realloc(pwc, VsInfodata[act_vsno-1].iSmax + isize*SEG_BLK_SIZE)) == NULL) {
					fprintf(stderr, " *** get_SegNext : realloc() エラー ***\n");
				}
				else {
					VsInfodata[act_vsno-1].pSeg = pw;
					VsInfodata[act_vsno-1].iSmax += isize*SEG_BLK_SIZE;

					ptr = VsInfodata[act_vsno-1].pSeg + VsInfodata[act_vsno-1].iSuse;
					VsInfodata[act_vsno-1].iSuse += isize;
					VsInfodata[act_vsno-1].iScount++;
				}

			}
		}
	}

	return ptr;
}
