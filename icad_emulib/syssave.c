#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

extern int  IcadSave(FILE *,int);

void sysave_(int *msfno, char mname[40], int *prtct, char psword[8], char cdata[80], char vsno[32], char wfno[32], int inform[4], int *ircode)
{
	char	cName[40+1];
	int		i, j, ivsno, iscnt,irc;
	unsigned char	cBase, cBit;
	FILE	*fp;
	char	fname[256+1];
	
	*ircode = 0;
	err_syosai = 0;
	
	cBase = 0x80;

	if ( *msfno < 1  || *msfno > 17 ) {
		*ircode = 12;
		err_syosai = 1;
		return;
	}
	
	//ファイル名チェック
	memcpy(cName, mname, 40);
	cName[40]=0;
	for (i=0;i < 40;i++) {
		if ( mname[i] != ' ' ) {
			cName[i] = mname[i];
		}
		else {
			cName[i] = 0;
			break;
		}
	}
	if (i == 0 ) {
		*ircode = 8;
		err_syosai = 2380;
		return;
	}
	
	// 保存ファイル
	sprintf(fname,"%s\\%s.idat",MMF_Dirpath[*msfno - 1],cName);
	if ( (fp=fopen(fname,"wb")) == NULL ) {
		*ircode = 12;
		err_syosai = 2580;
		return;
	}
	
	iscnt=0;
	for (i=0; i < 32 ;i++) {
		for (j=0;j < 8;j++) {
			cBit = cBase >> j;
			if ( (vsno[i] & cBit) != 0x00 ) {
				ivsno = i * 8 + j + 1;
				irc=IcadSave(fp, ivsno);
				iscnt += irc;
			}
		}
	}
	
	//ファイルクローズ
	fclose(fp);
	
	if (iscnt == 0 ) {
		*ircode = 8;
		err_syosai = 2344;
		remove(fname);
	}
	
	
	return;
}

int  IcadSave(FILE *fp,int ivsno) {
	int		i, j,  icnt, ivs, iscnt;
	struct  SegInfo	*seg;
	union Udata{
		int	i[1024];
		short	s[248];
		char	c[4096];
		double	d[512];
		float	f[1024];
	} *array;

	for (i=0; i < 500 ;i++) {
		if ( VsInfodata[i].vsno == ivsno ) break;
	}
	if (i == 500) return 0;
	
	ivs = i;
	
	iscnt=0;
	seg =  (struct  SegInfo *)VsInfodata[ivs].pSeg;
	for (i=0; i < VsInfodata[ivs].iScount;i++) {
		if( (seg+i)->idel != 0 ) continue;
		
		fwrite("SEG",sizeof(char),3,fp);
		fwrite((seg+i),sizeof(int),8,fp);
		
		for (j=0;j < (seg+i)->ipcount;j++) {
			array = VsInfodata[ivs].pPrm + (seg+i)->pprm[j].ioffset;

			icnt = array->s[0];
			fwrite("PRM",sizeof(char),3,fp);
			fwrite(&(seg+i)->pprm[j],sizeof(short),6,fp);
			fwrite(&(array->c[0]),sizeof(char),icnt,fp);
			
		}
		iscnt++;
	}
	
	return iscnt;
	
}
