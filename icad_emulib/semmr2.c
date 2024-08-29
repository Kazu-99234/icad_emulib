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

	if (itype == 1) {	// 点
		Mirror(dx, dy, dvx, dvy, array->d[1], array->d[2], &dnx, &dny);
		array->d[1] = dnx;
		array->d[2] = dny;
	}
	else if (itype == 2) {	// 線
		Mirror(dx, dy, dvx, dvy, array->d[1], array->d[2], &dnx, &dny);
		array->d[1] = dnx;
		array->d[2] = dny;
		
		Mirror(0.0, 0.0, dvx, dvy, array->d[3], array->d[4], &dwx, &dwy);
		array->d[3] = dwx;
		array->d[4] = dwy;
	}
	else if (itype == 3) {	// 折れ線
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
	else if (itype == 4) {	// 円
//	printf("	C MIRR  %f, %f  %f, %f   %f, %f --> ",dx, dy, dvx, dvy, array->d[1], array->d[2]);
		Mirror(dx, dy, dvx, dvy, array->d[1], array->d[2], &dnx, &dny);
		array->d[1] = dnx;
		array->d[2] = dny;
//	printf("%f, %f\n",array->d[1], array->d[2]);
	}
	else if (itype == 5) {	// 円弧
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
	else if (itype == 9) {	// ハッチング
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
	else if (itype == 10) {	// 矩形
		Mirror(dx, dy, dvx, dvy, array->d[1], array->d[2], &dnx, &dny);
		array->d[1] = dnx;
		array->d[2] = dny;
		
		Mirror(0.0, 0.0, dvx, dvy, array->d[3], array->d[4], &dwx, &dwy);
		array->d[3] = dwx;
		array->d[4] = dwy;
	}
	else if (itype == 32) {	// 文字列
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
	else if (itype == 89) {	// 楕円、楕円弧
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
// 機能		指定された2次元要素をミラー(鏡映)します。
// 引数
// in	entids[]	ミラーする(鏡映元の)要素の要素識別番号を指定します
// in	*nument		ミラーする要素の個数を指定します
// in	*incrmt		要素識別番号の取出し間隔を指定します
// in	*mx			ミラーの鏡映面となる線分上の点のX座標を指定します
// in	*my			ミラーの鏡映面となる線分上の点のY座標を指定します
// in	*mvx		ミラーの鏡映面となる線分の単位方向ベクトルのX成分を指定します
// in	*mvy		ミラーの鏡映面となる線分の単位方向ベクトルのY成分を指定します
// in	*erase		dummy
// out	*ircode		復帰情報

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
