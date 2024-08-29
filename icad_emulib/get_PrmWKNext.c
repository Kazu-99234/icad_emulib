#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"


char* get_PrmWKNext( int isize, int *ioff)
{
	char *pw, *pwc;
	char *ptr;

	ptr = NULL;

	if (isize > 0) {

		if (PrmWK == NULL) {
			pw = malloc(DATA_SIZE*BLK_SIZE);
			if (pw > 0) {
				PrmWK = pw;
				iPWK_max = DATA_SIZE*BLK_SIZE;
				iPWK_use = 0;

				ptr = pw;
				*ioff = 0;

			}
			else {
				fprintf(stderr, " *** getPrmWKNext : malloc() エラー ***\n");
			}
		}
		else {

			// 領域サイズチェック
			if (iPWK_use + isize < iPWK_max)
			{
				ptr = PrmWK + iPWK_use;
				*ioff = iPWK_use;
				iPWK_use += isize;
			}
			else {
				// 拡張
				pwc = PrmWK;
				if ((pw = realloc(pwc, iPWK_max + DATA_SIZE*BLK_SIZE)) == NULL) {
					fprintf(stderr, " *** get_PrmWKNext : realloc() エラー ***\n");
				}
				else {
					PrmWK = pw;
					iPWK_max += DATA_SIZE*BLK_SIZE;

					ptr = PrmWK + iPWK_use;
					*ioff = iPWK_use;
					iPWK_use += isize;
				}

			}
		}
	}

	return ptr;
}
