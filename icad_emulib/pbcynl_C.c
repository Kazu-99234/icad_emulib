#include	<stdio.h>
#include	<string.h>
#include	<math.h>
#include	"ComHansub.h"


//**************************************************************************************
//* 関数名　　:pbcynl_C
//* 概要  　　:線分と点の関係を調べる
//* 詳細  　　:
//* 引数　　　:[I] 直線の始点X座標
//* 　　　　　:[I] 直線の始点Y座標
//* 　　　　　:[I] 直線の終点X座標
//* 　　　　　:[I] 直線の終点Y座標
//* 　　　　　:[I] 調べる点のX座標
//* 　　　　　:[I] 調べる点のY座標
//* 　　　　　:[I] 誤差
//* 　　　　　:[O] 判定
//* 　　　　　:[O] 調べる点の始点からの距離
//* 戻り値　　:無し
//* 作成者　　:2022/10/11 FXS 蔡
//* 更新者　　:20xx/xx/xx
//* 更新内容　:
//**************************************************************************************
void pbcynl_C(double d_xs,double d_ys,double d_xe,double d_ye,double d_x,double d_y,double d_gg,int *i_nh,double *d_r)
{
	double d_a = 0.0,
		   d_b = 0.0,
		   d_bct = 0.0,
		   d_length = 0.0,
		   d_d1 = 0.0,
		   d_d2 = 0.0,
		   // ==== R1911.9 = 2019/12/11 Alv.senoo 汎用サブルーチン誤差対応
		   d_gosa = 0.0;

	d_gosa = d_gg;
	if (fabs(d_gg) < D_KIJUN) {
		d_gosa = D_KOYO_GOSA;
	}
	// ============== 2019/12/11 Alv.senoo 汎用サブルーチン誤差対応

	*i_nh = 5;
	d_bct = (d_x - d_xs) * (d_xe - d_xs) + (d_y - d_ys) * (d_ye - d_ys);
	d_a = (d_x - d_xs) * (d_x - d_xs) + (d_y - d_ys) * (d_y - d_ys);
	d_b = (d_xe - d_xs) * (d_xe - d_xs) + (d_ye - d_ys) * (d_ye - d_ys);
	d_length = sqrt(d_a * d_b);
	*d_r = sqrt(d_a);

	d_d1 = sqrt(d_a) - sqrt(d_b);
	d_d1 = fabs(d_d1);

	d_d2 = d_bct - d_length;
	d_d2 = fabs(d_d2);
	//==== R1911.9 = 2019/12/11 Alv.senoo 汎用サブルーチン誤差対応
	if (d_a < d_gosa) {
		*i_nh = 1;
	} else if (d_d1 < d_gosa && d_d2 < d_gosa) {
		*i_nh = 2;
	} else if (d_d2 < d_gosa) {
		if (d_a < d_b) {
			*i_nh = 0;
		} else {
			*i_nh = 3;
		}
	} else {
		d_bct = fabs(d_bct);
		d_d2 = fabs(d_bct - d_length);
		d_d2 = sqrt(d_d2);
		if (d_d2 < d_gosa) {
			*i_nh = 4;
		}
	}
	//============== 2019/12/11 Alv.senoo 汎用サブルーチン誤差対応
	return;
	//DEBUG INIT , SUBTRACE
}