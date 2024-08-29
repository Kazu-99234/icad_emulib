#include	<stdio.h>

#include	"ComHansub.h"


//**************************************************************************************
//* 関数名　　:aasort_C
//* 概要  　　:一次元配列をソートする.
//* 詳細  　　:
//* 引数　　　f_a:[I/O] ソートキー
//* 　　　　　i_no:[O] キーの配列要素
//* 　　　　　i_m:[i] 配列要素数
//* 　　　　　i_kazu:[I] ソート項目数
//* 戻り値　　:無し
//* 作成者　　:2022/09/21 FXS 葛
//* 更新者　　:20xx/xx/xx 
//* 更新内容　:
//**************************************************************************************
void aasort_C( float *f_a, int *i_no, int i_m, int i_kazu )
{
	//*** BINARY CORE SORT
	//    A ; ｿ-ﾄ ｷ-
	//    NO; ｷ - ﾉ ﾊｲﾚﾂ ﾖｳｿ
	//    M; N0 ﾉ ﾊｲﾚﾂ ﾖｳｿ ｽｳ
	// KAZU; ｿ - ﾄ ｺｳﾓｸ ｽｳ
	int   i_i = 0,
		  i_l = 0,
		  i_lg = 0,
		  i_k = 0,
		  i_kk = 0,
		  i_ll = 0,
		  i_was = 0;
	float f_wac = 0.0f;

	for (i_kk = 1; i_kk <= i_m; i_kk++) {
		i_no[i_kk - 1] = i_kk;
	}
	if (i_kazu <= 1) {
		return;
	}
	i_l = i_kazu;
l_10:
	i_lg = i_l / 4;
	i_l = 2 * i_lg + 1;
	i_i = 1;

l_20:
	i_k = i_i;
	i_ll = i_i + i_l;
	f_wac = f_a[i_ll - 1];
	i_was = i_no[i_ll - 1];

l_30:
	if (f_wac < f_a[i_k - 1]) {
		goto l_40;
	}

l_50:
	i_ll = i_k + i_l;
	f_a[i_ll - 1] = f_wac;
	i_no[i_ll - 1] = i_was;
	i_i = i_i + 1;
	if ((i_i + i_l) <= i_kazu) {
		goto l_20;
	} 
	if (i_l == 1) {
		return;
	}
	goto l_10;

l_40:
	i_ll = i_k + i_l;
	f_a[i_ll - 1] = f_a[i_k - 1];
	i_no[i_ll - 1] = i_no[i_k - 1];
	i_k = i_k - i_l;
	if (i_k > 0) {
		goto l_30;
	}
	goto l_50;
}
