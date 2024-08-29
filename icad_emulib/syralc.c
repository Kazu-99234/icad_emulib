#include <stdlib.h>
#include <memory.h>
#include <sys/stat.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

void syralc_(int *mmfno, char mmfnam[], int *leng, int *ircode)
{
	struct	stat	st;
	int		iret;
	char	cDir[256+1];
	
	*ircode = 0;
	err_syosai = 0;

	
	if ( *mmfno < 1  || *mmfno > 17 ) {
		*ircode = 12;
		err_syosai = 1;
		return;
	}
	if ( *leng < 3 || *leng > 256 ) {
		*ircode = 12;
		err_syosai = 3;
		return;
	}
	
	//ディレクトリチェック
	memcpy(cDir, mmfnam, *leng);
	cDir[*leng]=0;
	iret = stat(cDir, &st);
	if (iret != 0 ) {
		*ircode = 12;
		err_syosai = 2;
		return;
	}
	
	if ((st.st_mode & S_IFMT) != S_IFDIR) {
		*ircode = 12;
		err_syosai = 2;
		return;
	}
	
	strcpy(MMF_Dirpath[*mmfno - 1], cDir);
	
	
	return;
}

