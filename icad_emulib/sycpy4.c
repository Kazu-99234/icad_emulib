#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

void sycpy4_(int *vs2, int *vs1, int *mode, double *x2, double *y2, double *x1, double *y1, double
	*angle, double *scale, int *eidctl, int *offset, int *ircode)
{
	int		i, ismax;
	char	*pseg, *pprm;
	struct	SegInfo *pSeg;

	*ircode = 0;
	err_syosai = 0;

	if (cur_mode != 0) {
		*ircode = 12;
		err_syosai = 101;
		return;
	}
	
	if ( VsInfodata[*vs2 - 1].vsno == 0 || VsInfodata[*vs1 - 1].vsno == 0 ) {
		*ircode = 12;
		err_syosai = 1;
		return;
	}

	
	pseg = malloc(VsInfodata[*vs1 - 1].iSmax);
	if ( pseg == 0 ) {
		fprintf(stderr, " *** sycpy4_ : malloc() エラー ***\n");
		*ircode = 12;
		err_syosai = 999;
		return;
	}
	memcpy(pseg, VsInfodata[*vs1 - 1].pSeg, VsInfodata[*vs1 - 1].iSuse);
	VsInfodata[*vs2 - 1].pSeg = pseg;
	
	pprm = malloc(VsInfodata[*vs1 - 1].iPmax);
	if ( pprm == 0 ) {
		fprintf(stderr, " *** sycpy4_ : malloc() エラー ***\n");
		*ircode = 12;
		err_syosai = 999;
		return;
	}
	memcpy(pprm, VsInfodata[*vs1 - 1].pPrm, VsInfodata[*vs1 - 1].iPuse);
	VsInfodata[*vs2 - 1].pPrm = pprm;
	
	// 実像部品
	char  *pgrp;
	pgrp = malloc(VsInfodata[*vs1 - 1].iGmax);
	if ( pprm == 0 ) {
		fprintf(stderr, " *** sycpy4_ : malloc() エラー ***\n");
		*ircode = 12;
		err_syosai = 999;
		return;
	}
	memcpy(pgrp, VsInfodata[*vs1 - 1].pGrp, VsInfodata[*vs1 - 1].iGuse);
	VsInfodata[*vs2 - 1].pGrp = pgrp;
	
	
	VsInfodata[*vs2 - 1].iclass = VsInfodata[*vs1 - 1].iclass;
	VsInfodata[*vs2 - 1].iseg = VsInfodata[*vs1 - 1].iseg;
	VsInfodata[*vs2 - 1].iScount = VsInfodata[*vs1 - 1].iScount;
	VsInfodata[*vs2 - 1].iSmax = VsInfodata[*vs1 - 1].iSmax;
	VsInfodata[*vs2 - 1].iSuse = VsInfodata[*vs1 - 1].iSuse;
	VsInfodata[*vs2 - 1].iPmax = VsInfodata[*vs1 - 1].iPmax;
	VsInfodata[*vs2 - 1].iPuse = VsInfodata[*vs1 - 1].iPuse;
	// 実像部品
	VsInfodata[*vs2 - 1].iGmax = VsInfodata[*vs1 - 1].iGmax;
	VsInfodata[*vs2 - 1].iGuse = VsInfodata[*vs1 - 1].iGuse;
	
	// 識別ID
	pSeg = (SegInfo *)VsInfodata[*vs2 - 1].pSeg;
	ismax = VsInfodata[*vs2 - 1].iScount;
	iSyscnt[*vs2 - 1] = 0;
	for (i=0; i < ismax; i++) {
//		if (pSeg[i].isysno > 0 ) {
//		if (pSeg[i].isysno > 0 && pSeg[i].idel == 0) {
		if (pSeg[i].isysno != 0 && pSeg[i].idel == 0) {
			pSeg[i].isegno = 0;
//			pSeg[i].isysno =  *vs2 * 1000000 + (++iSyscnt[*vs2 - 1]);
			pSeg[i].isysno =  (*vs2 * 1000000 + (++iSyscnt[*vs2 - 1])) * -1;
		}
		else {
			pSeg[i].isegno = 0;
			pSeg[i].isysno = 0;
		}
		
	}
	
	
	return;
}
