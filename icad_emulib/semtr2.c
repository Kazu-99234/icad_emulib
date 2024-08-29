#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

#define	PAI_R	3.141592653589794
#define	PAI_2R	6.28318530717958647

void Rote(double ang, double cx,double cy, double x,double y, double *nx,double *ny)
{
	double	dx, dy;
	
	dx = x - cx;
	dy = y - cy;
	
	*nx = dx * cos(ang) - dy * sin(ang) + cx;
	*ny = dx * sin(ang) + dy * cos(ang) + cy;
}

void PrmMove(PrmInfo *pPrm, char *p, double dx, double dy)
{
	int	itype, i, icnt;
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
		array->d[1] = array->d[1]  + dx;
		array->d[2] = array->d[2]  + dy;
	}
	else if (itype == 2) {	// 線
		array->d[1] = array->d[1]  + dx;
		array->d[2] = array->d[2]  + dy;
	}
	else if (itype == 3) {	// 折れ線
		array->d[1] = array->d[1]  + dx;
		array->d[2] = array->d[2]  + dy;
	}
	else if (itype == 4 || itype == 5) {	// 円, 円弧
		array->d[1] = array->d[1]  + dx;
		array->d[2] = array->d[2]  + dy;
	}
	else if (itype == 9) {	// ハッチング
		icnt = (pPrm->ipsize - 40) / 24;
		array->d[1] = array->d[1]  + dx;
		array->d[2] = array->d[2]  + dy;
		for (i=0; i < icnt ; i++) {
			array->d[i*3 + 5] = array->d[i*3 + 5]  + dx;
			array->d[i*3 + 6] = array->d[i*3 + 6]  + dy;
		}
	}
	else if (itype == 10) {	// 矩形
		array->d[1] = array->d[1]  + dx;
		array->d[2] = array->d[2]  + dy;
	}
	else if (itype == 32) {	// 文字列
		array->d[1] = array->d[1]  + dx;
		array->d[2] = array->d[2]  + dy;
	}
	else if (itype == 89) {	// 楕円、楕円弧
		array->d[1] = array->d[1]  + dx;
		array->d[2] = array->d[2]  + dy;
	}
}
void PrmRote(PrmInfo *pPrm, char *p, double dx, double dy, double ang)
{
	int	itype, i, icnt;
	double	dnx, dny, dwx, dwy, dang;
	int	iang;

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

	}
	else if (itype == 2) {	// 線
		Rote(ang, dx, dy, array->d[1], array->d[2], &dnx, &dny);
		array->d[1] = dnx;
		array->d[2] = dny;
		Rote(ang, 0.0, 0.0, array->d[3], array->d[4], &dwx, &dwy);
		array->d[3] = dwx;
		array->d[4] = dwy;
	}
	else if (itype == 3) {	// 折れ線
		Rote(ang, dx, dy, array->d[1], array->d[2], &dnx, &dny);
		array->d[1] = dnx;
		array->d[2] = dny;
		icnt = (pPrm->ipsize - 24) / 8;
		for (i=0;i < icnt;i++) {
			Rote(ang, 0.0, 0.0, array->d[i*2+3], array->d[i*2+4], &dwx, &dwy);
			array->d[i*2+3] = dwx;
			array->d[i*2+4] = dwy;
		}
	}
	else if (itype == 4) {	// 円
		Rote(ang, dx, dy, array->d[1], array->d[2], &dnx, &dny);
		array->d[1] = dnx;
		array->d[2] = dny;
	}
	else if (itype == 5) {	// 円弧
		Rote(ang, dx, dy, array->d[1], array->d[2], &dnx, &dny);
		array->d[1] = dnx;
		array->d[2] = dny;
		array->d[4] = array->d[4] + ang;
		if (array->d[4] > PAI_2R ) array->d[4] = array->d[4] - PAI_R;
		if (array->d[4] < -PAI_2R ) array->d[4] = array->d[4] + PAI_R;
		array->d[5] = array->d[5] + ang;
		if (array->d[5] > PAI_2R ) array->d[5] = array->d[5] - PAI_R;
		if (array->d[5] < -PAI_2R ) array->d[5] = array->d[5] + PAI_R;

	}
	else if (itype == 9) {	// ハッチング
		Rote(ang, dx, dy, array->d[1], array->d[2], &dnx, &dny);
		array->d[1] = dnx;
		array->d[2] = dny;

		Rote(ang, 0.0, 0.0, array->d[3], array->d[4], &dwx, &dwy);
		array->d[3] = dwx;
		array->d[4] = dwy;
		
		icnt = (pPrm->ipsize - 40) / 24;
		for (i=0; i < icnt ; i++) {
			Rote(ang, dx, dy, array->d[i*3 + 5], array->d[i*3 + 6], &dnx, &dny);
			array->d[i*3 + 5] = dnx;
			array->d[i*3 + 6] = dny;
		}
	}
	else if (itype == 10) {	// 矩形
		Rote(ang, dx, dy, array->d[1], array->d[2], &dnx, &dny);
		array->d[1] = dnx;
		array->d[2] = dny;
		Rote(ang, 0.0, 0.0, array->d[3], array->d[4], &dwx, &dwy);
		array->d[3] = dwx;
		array->d[4] = dwy;
	}
	else if (itype == 32) {	// 文字列
		Rote(ang, dx, dy, array->d[1], array->d[2], &dnx, &dny);
		array->d[1] = dnx;
		array->d[2] = dny;
		iang = CNV_Radian2SC(ang);
		
	//	array->i[9] = array->i[9] + iang;
	//	array->i[10] = array->i[10] + iang;
	//	dang = CNV_SC2Degree(array->i[9] + iang);
	//	dang = CNV_SC2Degree(array->i[10] + iang);
		
		dang = CNV_SC2Radian(array->i[9]);
		iang = CNV_Radian2SC(ang + dang);
		array->i[9] = iang;
		dang = CNV_SC2Radian(array->i[10]);
		iang = CNV_Radian2SC(ang + dang);
		array->i[10] = iang;
	}
	else if (itype == 89) {	// 楕円、楕円弧
		Rote(ang, dx, dy, array->d[1], array->d[2], &dnx, &dny);
		array->d[1] = dnx;
		array->d[2] = dny;
		array->d[5] = array->d[5] + ang;
		if (array->d[5] > PAI_2R ) array->d[5] = array->d[5] - PAI_R;
		if (array->d[5] < -PAI_2R ) array->d[5] = array->d[5] + PAI_R;
		array->d[6] = array->d[6] + ang;
		if (array->d[6] > PAI_2R ) array->d[6] = array->d[6] - PAI_R;
		if (array->d[6] < -PAI_2R ) array->d[6] = array->d[6] + PAI_R;
		array->d[7] = array->d[7] + ang;
		if (array->d[7] > PAI_2R ) array->d[7] = array->d[7] - PAI_R;
		if (array->d[7] < -PAI_2R ) array->d[7] = array->d[7] + PAI_R;
	}
}


// semtr2_
// 機能		指定された2 次元要素を平行移動・回転移動します。
// 引数
// in	entids[]	移動する要素の要素識別番号を指定します
// in	*nument		移動する要素の個数を指定します
// in	*incrmt		要素識別番号の取出し間隔を指定します
// in	*mode		移動方法を以下のいずれかで指定します
// 					1 ： 平行移動
// 					2 ： 回転移動
// 					3 ： 平行移動して回転移動
// 					4 ： 回転移動して平行移動
// in	*dx			*mode が1、3 あるいは4 のとき有効で、平行移動時のX 方向の移動量を指定します
// in	*dy			mode が1、3 あるいは4 のとき有効で、平行移動時のY 方向の移動量を指定します
// in	*ang		*mode が2、3 あるいは4 のとき有効で、回転移動時の左回りにおける回転角度を指定します(単位：ラジアン)
// in	*cx			*mode が2、3 あるいは4 のとき有効で、回転移動時の中心X 座標を指定します
// in	*cy			*mode が2、3 あるいは4 のとき有効で、回転移動時の中心Y 座標を指定します
// in	*erase		dummy
// out	*ircode		復帰情報

void semtr2_(int entids[],int *nument,int *incrmt,int *mode,double *dx,double *dy,
	double *ang,double *cx,double *cy,int *erase,int *ircode)
{
	int	ipmax;
	int		i, j, k, ismax, ivsno;
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
					if (*mode < 1 && *mode > 4) {
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
											if ( *mode == 1 ) {
												PrmMove(&pPrm[k],VsInfodata[ivsno - 1].pPrm, *dx, *dy);
											}
											else if ( *mode == 2 ) {
												PrmRote(&pPrm[k],VsInfodata[ivsno - 1].pPrm, *cx, *cy, *ang);
											}
											else if ( *mode == 3 ) {
												PrmMove(&pPrm[k],VsInfodata[ivsno - 1].pPrm, *dx, *dy);
												PrmRote(&pPrm[k],VsInfodata[ivsno - 1].pPrm, *cx, *cy, *ang);
											}
											else if ( *mode == 4 ) {
												PrmRote(&pPrm[k],VsInfodata[ivsno - 1].pPrm, *cx, *cy, *ang);
												PrmMove(&pPrm[k],VsInfodata[ivsno - 1].pPrm, *dx, *dy);
											}
										}
										
										break;
									}
								}
							}
						}
						
					}


			}
		}

	}

	return;
	
}