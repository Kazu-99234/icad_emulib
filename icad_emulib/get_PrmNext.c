#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"


char* get_PrmNext( int isize, int *ioff)
{
	char *pw, *pwc;
	char *ptr;

	ptr = NULL;

	if (isize > 0) {

		if (VsInfodata[act_vsno-1].pPrm == NULL) {
			pw = malloc(DATA_SIZE*BLK_SIZE);
			if (pw > 0) {
				VsInfodata[act_vsno-1].pPrm = pw;
				VsInfodata[act_vsno-1].iPmax = DATA_SIZE*BLK_SIZE;
				VsInfodata[act_vsno-1].iPuse = isize;

				ptr = pw;
				*ioff = 0;

			}
			else {
				fprintf(stderr, " *** getPrmNext : malloc() エラー ***\n");
			}
		}
		else {

			// 領域サイズチェック
			if (VsInfodata[act_vsno-1].iPuse + isize < VsInfodata[act_vsno-1].iPmax)
			{
				ptr = VsInfodata[act_vsno-1].pPrm + VsInfodata[act_vsno-1].iPuse;
				*ioff = VsInfodata[act_vsno-1].iPuse;
				VsInfodata[act_vsno-1].iPuse += isize;
			}
			else {
				// 拡張
				pwc = VsInfodata[act_vsno-1].pPrm;
				if ((pw = realloc(pwc, VsInfodata[act_vsno-1].iPmax + DATA_SIZE*BLK_SIZE)) == NULL) {
					fprintf(stderr, " *** get_PrmNext : realloc() エラー ***\n");
				}
				else {
					VsInfodata[act_vsno-1].pPrm = pw;
					VsInfodata[act_vsno-1].iPmax += DATA_SIZE*BLK_SIZE;

					ptr = VsInfodata[act_vsno-1].pPrm + VsInfodata[act_vsno-1].iPuse;
					*ioff = VsInfodata[act_vsno-1].iPuse;
					VsInfodata[act_vsno-1].iPuse += isize;
				}

			}
		}
	}

	return ptr;
}
