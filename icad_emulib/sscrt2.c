#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"


void sscrt2_(int *type, int *visi, int *disp, int *ircode)
{
	int		irc = 0;
	char	*pw;

	*ircode = 0;
	err_syosai = 0;

	if (cur_mode != 0) {
		*ircode = 12;
		err_syosai = 101;
	}
	else {

		if (*type < 0 || *type>255) {
			*ircode = 12;
			err_syosai = 1;
		}
		else {
			if (*visi != 0 && *visi != 1) {
				*ircode = 12;
				err_syosai = 2;
			}
			else {
				if (*disp != 0 && *disp != 1) {
					*ircode = 12;
					err_syosai = 3;
				}
				else {

					if (act_vsno == 0) {
						*ircode = 8;
						err_syosai = 1;
					}
					else {
						if (cur_class == 0) {
							*ircode = 8;
							err_syosai = 1;
						}
						else {
							memset((char *)&SegWK, 0, sizeof(SegWK));
							SegWK.ivsno = act_vsno;
							SegWK.ivisi = *visi;
							SegWK.idisp = *disp;
							SegWK.itype = *type;
							SegWK.iclass = cur_class;
							

//							iPWK_max = 40000;
						//	if ( PrmWK != 0 && iPWK_max > DATA_SIZE*BLK_SIZE) {
						//		free(PrmWK);
						//		PrmWK = 0;
						//	}
							if ( PrmWK == 0 ) {
								pw = malloc(DATA_SIZE*BLK_SIZE);
								if (pw > 0) {
									PrmWK = pw;
								}
								else {
									fprintf(stderr, " *** getPrmNext : malloc() ÉGÉâÅ[ ***\n");
									*ircode = 12;
									err_syosai = 999;
								}
							}
							iPWK_max = DATA_SIZE*BLK_SIZE;
							iPWK_use = 0;
							
							cur_mode = 1;
						}
					}

				}


			}

		}
	}


}
