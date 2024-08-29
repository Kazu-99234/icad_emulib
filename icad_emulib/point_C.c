#include	<stdio.h>
#include	<string.h>
#include	<math.h>
#include	"ComHansub.h"

//**************************************************************************************
//* 関数名　　:point_C
//* 概要  　　:面と点の関係を調べる
//* 詳細  　　:
//* 引数　　　:[I] 面の座標(まわり方は左／右どちらでも可能)
//* 　　　　　:[I] 面の頂点の数
//* 　　　　　:[I] 点のX座標
//* 　　　　　:[I] 点のY座標 
//* 　　　　　:[O] 判定
//* 　　　　　:[I] ダミー
//* 戻り値　　:無し
//* 作成者　　:2022/09/20 FXS 葛
//* 更新者　　:20xx/xx/xx
//* 更新内容　:
//**************************************************************************************
void point_C(float f_a[][SIZE_2], int i_n, float f_x, float f_y, int *i_ih, float f_gsa)
{
	int    i_i = 0,
		   i_ip = 0;
	double d_del = 0.0,
		   d_pai = 0.0,
		   d_sumt = 0.0,
		   d_x1 = 0.0,
		   d_y1 = 0.0,
		   d_x2 = 0.0,
		   d_y2 = 0.0,
		   d_aa = 0.0,
		   d_bb = 0.0,
		   d_cc = 0.0,
		   d_c = 0.0,
		   d_d = 0.0,
		   d_cd = 0.0,
		   d_cod = 0.0,
		   d_theta = 0.0,
		   d_xx = 0.0,
		   d_xa = 0.0,
		   d_ya = 0.0,
		   d_xb = 0.0,
		   d_yb = 0.0,
		   d_xc = 0.0,
		   d_yc = 0.0,
		   d_zmx = 0.0,
		   d_zmy = 0.0,
		   d_zl = 0.0,
		   d_co = 0.0,
		   d_so = 0.0,
		   d_yo = 0.0;
	//    DEL=0.005D0
	d_del = 0.003;
	//R1808.0 sugimoto = 2018/08/31 細長い面だと誤差で誤動作するので調整
	//= GOS に マイナス値が設定されている場合、誤差変更（座標値0.001精度相当）
	if (f_gsa < 0.0f) {
		d_del = 0.00000005;
	}
	//==================== 2018/08/31 細長い面だと誤差で誤動作するので調整
	d_pai = M_PAI;
	d_sumt = 0.0;
	for (i_i = 1; i_i <= i_n; i_i++) {
		d_x1 = f_a[i_i - 1][0];
		d_y1 = f_a[i_i - 1][1];
		if (i_i == i_n) {
			goto l_100;
		}
		d_x2 = f_a[i_i][0];
		d_y2 = f_a[i_i][1];
		goto l_110;
l_100:
		d_x2 = f_a[0][0];
		d_y2 = f_a[0][1];
l_110:
		d_bb = (d_x1 - d_x2) * (d_x1 - d_x2) + (d_y1 - d_y2) * (d_y1 - d_y2);
		d_cc = (f_x - d_x2) * (f_x - d_x2) + (f_y - d_y2) * (f_y - d_y2);
		d_aa = (f_x - d_x1) * (f_x - d_x1) + (f_y - d_y1) * (f_y - d_y1);
		d_d = sqrt(d_aa);
		d_c = sqrt(d_cc);
		d_cd = d_c * d_d;
		if (d_cd <= d_del && d_cd >= (-d_del)) {
			goto l_120;
		}
		d_cod = (d_bb - d_cc - d_aa) / (-2.0 * d_c * d_d);
		if (d_cod > 1.0) {
			d_cod = 1.;
		}
		if (d_cod < (-1.)) {
			d_cod = -1.;
		}
		d_theta = acos(d_cod);
		if (d_theta <= (d_pai + d_del) && d_theta >= (d_pai - d_del)) {
			goto l_120;
		}
		i_ip = 0;
		d_xx = f_x;
		if (d_x2 < d_xx) {
			i_ip = 2;
		}
		if (d_x1 < d_xx) {
			i_ip = 1;
		}
		if (i_ip != 0) {
			goto l_200;
		}
		d_xa = f_x;
		d_ya = f_y;
		d_xb = d_x1;
		d_yb = d_y1;
		d_xc = d_x2;
		d_yc = d_y2;
		goto l_220;
l_200:
		if (i_ip != 2) {
			goto l_201;
		}
		d_xa = d_x2;
		d_ya = d_y2;
		d_xb = f_x;
		d_yb = f_y;
		d_xc = d_x1;
		d_yc = d_y1;
		goto l_220;
l_201:
		d_xa = d_x1;
		d_ya = d_y1;
		d_xb = d_x2;
		d_yb = d_y2;
		d_xc = f_x;
		d_yc = f_y;
l_220:
		d_zmx = (d_xb + d_xc) / 2;
		d_zmy = (d_yb + d_yc) / 2;
		d_zl = sqrt((d_zmx - d_xa) * (d_zmx - d_xa) + (d_zmy - d_ya) * (d_zmy - d_ya));
		if (d_zl == 0.) {
			goto l_330;
		}
		d_co = (d_zmx - d_xa) / d_zl;
		d_so = (d_zmy - d_ya) / d_zl;
		goto l_340;
l_330:
		d_co = 0.;
		d_so = 0.;
l_340:
		d_yo = d_co * (d_yb - d_ya) - d_so * (d_xb - d_xa);
		if (d_yo < 0.) {
			d_theta = (-d_theta);
		}
		d_sumt = d_sumt + d_theta;
	}
	*i_ih = 0;
	if (d_sumt <= d_del && d_sumt >= (-d_del)) {
		*i_ih = 0;
	}
	d_sumt = fabs(d_sumt);
	if (d_sumt <= (d_pai + d_del) && d_sumt >= (d_pai - d_del)) {
		*i_ih = 3;
	}
	if (d_sumt <= (d_pai * 2 + d_del) && d_sumt >= (d_pai * 2 - d_del)) {
		*i_ih = 1;
	}
	return;
l_120:
	*i_ih = 3;
	return;
	//DEBUG INIT
}