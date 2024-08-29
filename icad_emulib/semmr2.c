#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

#define	PAI_R	3.141592653589794
#define	PAI_2R	6.28318530717958647

extern void Rote(double ang, double cx,double cy, double x,double y, double *nx,double *ny);

void Mirror(double dxs, double dys, double dvx, double dvy, double dx, double dy, double *dnx, double *dny)
{
	double	dxe, dye, da , dex, dey, dd, dpx, dpy, dlen;
	
	dxe = dxs + dvx * 100.0;
	dye = dys + dvy * 100.0;
	da = (dxs - dxe) *  (dxs - dxe)  + (dys - dye) *  (dys - dye);
	da = sqrt(da);
	dex = (dxe - dxs) / da;
	dey = (dye - dys) / da;
	dd = ((dx-dxs) * (dxe-dxs) + (dy-dys) * (dye-dys)) / da;
	dpx = dxs + dex * dd;
	dpy = dys + dey * dd;
	dlen = (dpx - dx) * (dpx * dx) + (dpy -dy) * (dpy -dy);
	dlen = sqrt(dlen);
	
	*dnx = dpx + (dpx - dx);
	*dny = dpy + (dpy - dy);

}

void PrmMirr(PrmInfo *pPrm, char *p, double dx, double dy, double dvx, double dvy)
{
	
	int	itype, i, icnt;
	double	dnx, dny, dwx, dwy, dlx, dly, dcx, dcy;

	union Udata {
		int	i[1024];
		short	s[248];
		char	c[4096];
		double	d[512];
		float	f[1024];
	} *array;
	
	itype = pPrm->iptype;
	array = p + pPrm->ioffset;

	if (itype == 1) {	// �_
		Mirror(dx, dy, dvx, dvy, array->d[1], array->d[2], &dnx, &dny);
		array->d[1] = dnx;
		array->d[2] = dny;
	}
	else if (itype == 2) {	// ��
		Mirror(dx, dy, dvx, dvy, array->d[1], array->d[2], &dnx, &dny);
		array->d[1] = dnx;
		array->d[2] = dny;
		
		Mirror(0.0, 0.0, dvx, dvy, array->d[3], array->d[4], &dwx, &dwy);
		array->d[3] = dwx;
		array->d[4] = dwy;
	}
	else if (itype == 3) {	// �܂��
		Mirror(dx, dy, dvx, dvy, array->d[1], array->d[2], &dnx, &dny);
		array->d[1] = dnx;
		array->d[2] = dny;
		icnt = (pPrm->ipsize - 24) / 8;
		for (i=0;i < icnt;i++) {
			Mirror(0.0, 0.0, dvx, dvy, array->d[i*2+3], array->d[i*2+4], &dwx, &dwy);
			array->d[i*2+3] = dwx;
			array->d[i*2+4] = dwy;
		}
	}
	else if (itype == 4) {	// �~
//	printf("	C MIRR  %f, %f  %f, %f   %f, %f --> ",dx, dy, dvx, dvy, array->d[1], array->d[2]);
		Mirror(dx, dy, dvx, dvy, array->d[1], array->d[2], &dnx, &dny);
		array->d[1] = dnx;
		array->d[2] = dny;
//	printf("%f, %f\n",array->d[1], array->d[2]);
	}
	else if (itype == 5) {	// �~��
		dcx = array->d[1];
		dcy = array->d[2];
		
		Mirror(dx, dy, dvx, dvy, array->d[1], array->d[2], &dnx, &dny);
		array->d[1] = dnx;
		array->d[2] = dny;
		
		dlx = dcx + cos(array->d[4]) * array->d[3];
		dly = dcy + sin(array->d[4]) * array->d[3];
		Mirror(dx, dy, dvx, dlx, dly, dvy, &dwx, &dwy);
		array->d[4] = atan((dwy - dcy)/(dwx - dcx));
		
		dlx = dcx + cos(array->d[5]) * array->d[3];
		dly = dcy + sin(array->d[5]) * array->d[3];
		Mirror(dx, dy, dvx, dlx, dly, dvy, &dwx, &dwy);
		array->d[5] = -atan((dwy - dcy)/(dwx - dcx));
		

	}
	else if (itype == 9) {	// �n�b�`���O
		Mirror(dx, dy, dvx, dvy, array->d[1], array->d[2], &dnx, &dny);
		array->d[1] = dnx;
		array->d[2] = dny;
		
		Mirror(0.0, 0.0, dvx, dvy, array->d[3], array->d[4], &dwx, &dwy);
		array->d[3] = dwx;
		array->d[4] = dwy;

		icnt = (pPrm->ipsize - 40) / 24;
		for (i=0; i < icnt ; i++) {
			Mirror(0.0, 0.0, dvx, dvy, array->d[i*3 + 5], array->d[i*3 + 6], &dwx, &dwy);
			array->d[i*3 + 5] = dnx;
			array->d[i*3 + 6] = dny;
		}
	}
	else if (itype == 10) {	// ��`
		Mirror(dx, dy, dvx, dvy, array->d[1], array->d[2], &dnx, &dny);
		array->d[1] = dnx;
		array->d[2] = dny;
		
		Mirror(0.0, 0.0, dvx, dvy, array->d[3], array->d[4], &dwx, &dwy);
		array->d[3] = dwx;
		array->d[4] = dwy;
	}
	else if (itype == 32) {	// ������
		double dang, dwx, dwy;
		dang = CNV_SC2Radian(array->i[9]);
		Rote((PAI_R / 2.0), 0.0, 0.0, cos(dang) * array->f[6], sin(dang) *  array->f[6], &dwx, &dwy);
		Mirror(dx, dy, dvx, dvy,  (array->d[1] + dwx), (array->d[2] + dwy), &dnx, &dny);
		array->d[1] = dnx;
		array->d[2] = dny;

		dang = CNV_SC2Radian(array->i[9]);
		dlx = cos(dang);
		dly = sin(dang);
		Mirror(0.0, 0.0, dvx, dvy, dlx, dly, &dwx, &dwy);
		dang = atan(dwy/dwx);
		array->i[9] = CNV_Radian2SC(dang);
		
		dang = CNV_SC2Radian(array->i[10]);
		dlx = cos(dang);
		dly = sin(dang);
		Mirror(0.0, 0.0, dvx, dvy, dlx, dly, &dwx, &dwy);
		dang = atan(dwy/dwx);
		array->i[10] = CNV_Radian2SC(dang);
	}
	else if (itype == 89) {	// �ȉ~�A�ȉ~��
		Mirror(dx, dy, dvx, dvy, array->d[1], array->d[2], &dnx, &dny);
		array->d[1] = dnx;
		array->d[2] = dny;
		dcx = array->d[1];
		dcy = array->d[2];
		
		if ( !(array->d[6] == 0.0 && array->d[7] == PAI_2R) ) {
			dlx = dcx + cos(array->d[5]) * array->d[3];
			dly = dcy + sin(array->d[5]) * array->d[3];
			Mirror(dx, dy, dvx, dlx, dly, dvy, &dwx, &dwy);
			array->d[5] = atan((dwy - dcy)/(dwx - dcx));
			dlx = dcx + cos(array->d[6]) * array->d[3];
			dly = dcy + sin(array->d[6]) * array->d[3];
			Mirror(dx, dy, dvx, dlx, dly, dvy, &dwx, &dwy);
			array->d[6] = atan((dwy - dcy)/(dwx - dcx));
			dlx = dcx + cos(array->d[7]) * array->d[3];
			dly = dcy + sin(array->d[7]) * array->d[3];
			Mirror(dx, dy, dvx, dlx, dly, dvy, &dwx, &dwy);
			array->d[7] = -atan((dwy - dcy)/(dwx - dcx));
		}
	}
}
	
// semmr2_
// �@�\		�w�肳�ꂽ2�����v�f���~���[(���f)���܂��B
// ����
// in	entids[]	�~���[����(���f����)�v�f�̗v�f���ʔԍ����w�肵�܂�
// in	*nument		�~���[����v�f�̌����w�肵�܂�
// in	*incrmt		�v�f���ʔԍ��̎�o���Ԋu���w�肵�܂�
// in	*mx			�~���[�̋��f�ʂƂȂ������̓_��X���W���w�肵�܂�
// in	*my			�~���[�̋��f�ʂƂȂ������̓_��Y���W���w�肵�܂�
// in	*mvx		�~���[�̋��f�ʂƂȂ�����̒P�ʕ����x�N�g����X�������w�肵�܂�
// in	*mvy		�~���[�̋��f�ʂƂȂ�����̒P�ʕ����x�N�g����Y�������w�肵�܂�
// in	*erase		dummy
// out	*ircode		���A���

void semmr2_(int entids[],int *nument,int *incrmt,double *mx,double *my,double *mvx,double *mvy,int *erase,int *ircode)
{
	
	int	ipmax;
	int		i, j, k, ismax, ivsno;
	short	*ichk;
	int		icnt;
	
	
	*ircode = 0;
	err_syosai = 0;


	if (cur_mode != 0) {
		*ircode = 12;
		err_syosai = 101;
	}
	else {
		if (*nument < 1  ) {
			*ircode = 12;
			err_syosai = 2;
		}
		else {
			if (*incrmt < 1) {
				*ircode = 12;
				err_syosai = 3;
			}
			else {
					
				icnt=0;
				
				for (ivsno=1;ivsno <= 500;ivsno++) {
					if ( VsInfodata[ivsno - 1].vsno == 0 ) continue;
					struct  SegInfo *pSeg = (struct  SegInfo *)	VsInfodata[ivsno - 1].pSeg;
					ismax = VsInfodata[ivsno - 1].iScount;

					for (i = 0; i < *nument; i++) {
						
						for (j = 0; j < ismax; j++) {
							if (pSeg[j].isegno == entids[i * (*incrmt)] || pSeg[j].isysno == entids[i * (*incrmt)]) {
								ipmax = pSeg[j].ipcount;
								struct  PrmInfo *pPrm = (struct  PrmInfo*)pSeg[j].pprm;
								
								for (k=0;k < ipmax;k++) {
									PrmMirr(&pPrm[k],VsInfodata[ivsno - 1].pPrm, *mx, *my, *mvx, *mvy);
								}
								
								break;
							}
						}
					}
				}

			}
		}

	}

	return;}
