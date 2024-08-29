#include <stdlib.h>
#include <memory.h>
#include "icad_emu.h"
#include "icad_emu_data.h"

// sparc2_
// 機能		2次元の円弧プリミティブを作成します。
// in	*x		円弧の中心のX座標を指定します
// in	*y		円弧の中心のY座標を指定します
// in	*r		円弧の半径を正の実数で指定します
// in	*th1	円弧の始角を指定します(単位 : ラジアン)
// in	*th2	円弧の始角から終角までの左回りの相対角度を－2π～2πの範囲で指定します
// 				(*th2≠0、単位：ラジアン)
// 				0＜*th2＜2π 始角から左回りに円弧が作成されます
// 				0＞*th2＞－2π 始角から右回りに円弧が作成されます
// in	*atrid	作成プリミティブに与える属性の定義された図形属性テーブル番号を0～3の整数で指定します
// in	*mode	作成プリミティブの表示・検索属性を以下のいずれかで指定します
// 				1 ： 表示・検索
// 				2 ： 表示・非検索
// 				3 ： 非表示・非検索
// out	*ircode	復帰情報

void sparc2_(double *x, double *y, double *r, double *th1, double *th2, int *atrid, int *mode, int *ircode)
{
	union Udata{
		int	i[1024];
		short	s[248];
		char	c[4096];
		double	d[512];
		float	f[1024];
	} *array;

	double		dgos = 0.000001;
	int	ioff;
	char	*pt;


	*ircode = 0;
	err_syosai = 0;

	if (cur_mode == 0) {
		*ircode = 12;
		err_syosai = 101;
	}
	else {
		if (*r < 0.0) {
			*ircode = 12;
			err_syosai = 3;
		}
		else {
				if (*atrid < 0 || *atrid > 3) {
					*ircode = 12;
					err_syosai = 6;
				}
				else {
					if (*mode < 1 || *mode >3) {
						*ircode = 12;
						err_syosai = 7;
					}
					else {
						if (SegWK.ipcount >= 255) {
							*ircode = 8;
							err_syosai = 1005;
						}
						else {
						//	SegWK.pprm[SegWK.ipcount] = &PrmWkinfo[SegWK.ipcount];
							SegWK.pprm[SegWK.ipcount].iptype = 5;
							SegWK.pprm[SegWK.ipcount].ipsize = 48;
						//	SegWK.pprm[SegWK.ipcount].pdata = &PrmWK[iPWK_use];
						//	array = (union Udata *)&PrmWK[iPWK_use];
							SegWK.pprm[SegWK.ipcount].ioffset = iPWK_use;
							if ((pt = get_PrmWKNext(SegWK.pprm[SegWK.ipcount].ipsize, &ioff)) != NULL) {
								array = (union Udata *)pt;
								array->c[3] = 5;
								array->s[0] = 48;
								array->d[1] = *x;
								array->d[2] = *y;
								array->d[3] = *r;
								array->d[4] = *th1;
								array->d[5] = *th2;
							
								SegWK.pprm[SegWK.ipcount].iwt = GraAttr[*atrid].atrtbl[0];
								SegWK.pprm[SegWK.ipcount].ifnt = GraAttr[*atrid].atrtbl[1];
								SegWK.pprm[SegWK.ipcount].iclr = GraAttr[*atrid].atrtbl[2];
								
								SegWK.pprm[SegWK.ipcount].imode = *mode;


								iPWK_use += 48;
								SegWK.ipcount++;
							}
							else {
								*ircode = 8;
								err_syosai = 1004;
							}

						}

					}

				}

			}

	}

	return;

}