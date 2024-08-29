#include	<stdio.h>
#include	<string.h>
#include	<stdlib.h>
#include	<math.h>
#include	"ComHansub.h"

//**************************************************************************************
//* 関数名　　:pbccut_C
//* 概要  　　:枠内外カット（複数線分・複数カット面）
//* 詳細  　　:
//* 引数　　　:[I] ｶｯﾄｴﾘｱの座標ﾃｰﾌﾞﾙ（複数ｾｯﾄ可、中間判定-9999.0　END判定-99999.0）
//* 　　　　　:[I] 上記のテーブルの整合寸法
//* 　　　　　:[I/O] 線分の始点、終点座標
//* 　　　　　:[I] 上記テーブルの整合寸法
//* 　　　　　:[I/O] ＡＡテーブルにセットしてある線分数（ＬＳＵ≦Ｍ）
//* 　　　　　:[I] 処理区分
//* 　　　　　:[I] 線分として認める最小の長さ
//* 　　　　　:[I] 誤差（ＰＢＣＹＮＬで使用）
//* 戻り値　　:無し
//* 作成者　　:2022/09/21 FXS 武
//* 更新者　　:20xx/xx/xx
//* 更新内容　:
//**************************************************************************************
void pbccut_C(float f_pos[][SIZE_2],int i_n,float f_aa[][SIZE_4],int i_m,int *i_lsu,int i_ksw,float f_al,float f_gosa){
	const int i_mpp = 100;

	int    i_i = 0,
		   i_j = 0,
		   i_k = 0,
		   i_l = 0,
		   i_nh = 0,
		   i_msu = 0,
		   i_nsu = 0,
		   i_mpc = 0,
		   i_mrc = 0,
		   i_lpc = 0,
		   i_ixy[SIZE_4][SIZE_2];
	float  f_pp = 0.0f,
		   f_am = 0.0f,
		   f_gosa_al = 0.0f,
		   f_gosa_gsa = 0.0f,
		   (*f_ros)[SIZE_2] = NULL,
		   (*f_pnt)[SIZE_3] = NULL,
		   *f_ipt = NULL,
		   f_x = 0.0f,
		   f_y = 0.0f;
	double d_x = 0.0,
		   d_y = 0.0,
		   d_x1 = 0.0,
		   d_y1 = 0.0,
		   d_x2 = 0.0,
		   d_y2 = 0.0,
		   d_x3 = 0.0,
		   d_y3 = 0.0,
		   d_x4 = 0.0,
		   d_y4 = 0.0,
		   d_xx = 0.0,
		   d_yy = 0.0,
		   d_gg = 0.0,
		   d_rr = 0.0;

	if ((f_ros = (float(*)[SIZE_2])malloc(sizeof(float) * i_mpp * 2)) == NULL) {
		goto l_end;
	}
	if ((f_pnt = (float(*)[SIZE_3])malloc(sizeof(float) * i_mpp * 3)) == NULL) {
		goto l_end;
	}
	if ((f_ipt = (float *)malloc(sizeof(float) * i_mpp)) == NULL) {
		goto l_end;
	}
	memset(i_ixy, 0, sizeof(i_ixy));
	memset(f_ros, 0, sizeof(float) * i_mpp * 2);
	memset(f_pnt, 0, sizeof(float)* i_mpp * 3);
	memset(f_ipt, 0, sizeof(float)* i_mpp);

	if (i_ksw < 1 || i_ksw > 4) {
		goto l_999;
	}
	if (*i_lsu > i_m) {
		goto l_999;
	}
	// ==== R1911.9 = 2019/12/11 Alv.senoo 汎用サブルーチン誤差対応
	f_gosa_al = f_al;
	if (fabsf(f_al) < F_KIJUN) {
		f_gosa_al = F_KOYO_GOSA;
	}
	f_gosa_gsa = f_gosa;
	if (fabsf(f_gosa) < F_KIJUN) {
		f_gosa_gsa = F_KOYO_GOSA;
	}
	d_gg = f_gosa_gsa;
	// ============== 2019/12/11 Alv.senoo 汎用サブルーチン誤差対応
	//
	// *****  f_aa ﾖﾘ ｾﾝﾌﾞﾝ ｵ ﾄﾘﾀﾞｼ ｼﾖﾘ ｵ ｵｺﾅｳ  *****
	//	
	i_msu = *i_lsu;
	i_nsu = *i_lsu;
	*i_lsu = 0;
	for (i_i = 1; i_i <= i_msu; i_i++) {
		d_x1 = f_aa[i_i - 1][0];
		d_y1 = f_aa[i_i - 1][1];
		d_x2 = f_aa[i_i - 1][2];
		d_y2 = f_aa[i_i - 1][3];
		// ==== System R0806.0 ==== 2008/06(hatanaka)
		if (sqrt((d_x1 - d_x2) * (d_x1 - d_x2) + (d_y1 - d_y2) * (d_y1 - d_y2)) == 0.0) {
		// ======================== 2008/06(hatanaka)
			goto l_100;
		}
		i_mpc = 2;
		f_pnt[0][0] = f_aa[i_i - 1][0];
		f_pnt[0][1] = f_aa[i_i - 1][1];
		f_pnt[0][2] = 0.0f;
		f_ipt[0] = 0.0f;
		f_pnt[1][0] = f_aa[i_i - 1][2];
		f_pnt[1][1] = f_aa[i_i - 1][3];
		// = R1310.0 hatanaka = 2013/10/25 運-DEPS_F,伏Z
		//   R1310.0 長さ処理の変更
		f_pnt[1][2] = rrlng_C(f_aa[i_i - 1][0], f_aa[i_i - 1][1], f_aa[i_i - 1][2], f_aa[i_i - 1][3]);
		// ==================== 2013/10/25 運-DEPS_F,伏Z
		f_ipt[1] = 0;

		// *****  f_pos ﾖﾘ ｶﾂﾄﾒﾝｾﾝﾌﾞﾝ ｵ ﾄﾘﾀﾞｼ ｾﾝﾌﾞﾝ ﾄﾉ ｺｳﾃﾝ ｵ ﾓﾄﾒﾙ  *****
		i_mrc = 0;
		for (i_j = 1; i_j <= i_n; i_j++) {
			if (f_pos[i_j - 1][0] == -9999.0f || f_pos[i_j - 1][0] == -99999.0f) {
				if (i_mrc == 0) {
					if (f_pos[i_j - 1][0] == -99999.0f) {
						goto l_210;
					}
					goto l_200;
				} else {
					d_x3 = f_pos[i_j - 2][0];
					d_y3 = f_pos[i_j - 2][1];
					d_x4 = f_pos[i_mrc - 1][0];
					d_y4 = f_pos[i_mrc - 1][1];
					i_mrc = 0;
				}
			} else {
				if (i_mrc == 0) {
					i_mrc = i_j;
					goto l_200;
				} else {
					d_x3 = f_pos[i_j - 2][0];
					d_y3 = f_pos[i_j - 2][1];
					d_x4 = f_pos[i_j - 1][0];
					d_y4 = f_pos[i_j - 1][1];
				}
			}
			djtcrs_C(d_x1, d_y1, d_x2, d_y2, d_x3, d_y3, d_x4, d_y4, &d_xx, &d_yy, &i_nh, d_gg);
			if (i_nh == 1) {
				pbcynl_C(d_x1, d_y1, d_x2, d_y2, d_xx, d_yy, d_gg, &i_nh, &d_rr);
				if (i_nh == 0) {
					for (i_k = 1; i_k <= i_mpc; i_k++) {
						if (f_pnt[i_k - 1][2] == (float)(d_rr)) {
							goto l_230;
						}
					}
					if (i_mpc >= i_mpp) {
						goto l_210;
					}
					i_mpc = i_mpc + 1;
					f_pnt[i_mpc - 1][0] = (float)(d_xx);
					f_pnt[i_mpc - 1][1] = (float)(d_yy);
					f_pnt[i_mpc - 1][2] = (float)(d_rr);
					f_ipt[i_mpc - 1] = 0;
l_230:
					continue;
				}
			}
			if (f_pos[i_j - 1][0] == -99999.0) {
				goto l_210;
			}
l_200:
			continue;
		}
		//
		// *****  ﾌﾞﾝｶﾂﾃﾝ ﾉ ｿ-ﾄ ｵ ｽﾙ  *****
		//
l_210:
		for (i_j = 1; i_j <= (i_mpc - 1); i_j++) {
			for (i_k = i_j + 1; i_k <= i_mpc; i_k++) {
				if (f_pnt[i_j - 1][2] > f_pnt[i_k - 1][2]) {
					for (i_l = 1; i_l <= 3; i_l++) {
						f_pp = f_pnt[i_j - 1][i_l - 1];
						f_pnt[i_j - 1][i_l - 1] = f_pnt[i_k - 1][i_l - 1];
						f_pnt[i_k - 1][i_l - 1] = f_pp;
					}
				}
			}
		}
		//
		// *****  ｶｸﾒﾝ ｵ ﾄﾘﾀﾞｼ ﾌﾞﾝｶﾂｾﾝﾌﾞﾝ ﾉ ﾅｲｶﾞｲﾊﾝﾃｲ ｵ ｵｺﾅｳ  *****
		//
		i_mrc = 0;
		for (i_j = 1; i_j <= i_n; i_j++) {
			if (f_pos[i_j - 1][0] == -9999.0f || f_pos[i_j - 1][0] == -99999.0f) {
				if (i_mrc != 0) {
					for (i_k = 1; i_k <= (i_mpc - 1); i_k++) {
						if (f_ipt[i_k - 1] != 1) {
							f_x = (f_pnt[i_k - 1][0] + f_pnt[i_k][0]) / 2.0f;
							f_y = (f_pnt[i_k - 1][1] + f_pnt[i_k][1]) / 2.0f;
							// ==== R1911.9 = 2019/12/11 Alv.senoo 汎用サブルーチン誤差対応
							point_C(f_ros, i_mrc, f_x, f_y, &i_nh, f_gosa_gsa);
							// ============== 2019/12/11 Alv.senoo 汎用サブルーチン誤差対応
							if (i_nh == 1) {
								f_ipt[i_k - 1] = 1;
							}
							if (i_nh == 3) {
								f_ipt[i_k - 1] = 2;
							}
						}
					}
				}
				i_mrc = 0;
				if (f_pos[i_j - 1][0] == -99999.0) {
					goto l_490;
				}
			} else {
				if (i_mrc >= i_mpp) {
					goto l_400;
				}
				i_mrc = i_mrc + 1;
				f_ros[i_mrc - 1][0] = f_pos[i_j - 1][0];
				f_ros[i_mrc - 1][1] = f_pos[i_j - 1][1];
			}
l_400:
			continue;
		}
l_490:
		//
		// *****  ｶﾞｲﾄｳｽﾙ ｾﾝﾌﾞﾝ ｵ f_aaﾃ - ﾌﾞﾙ ﾍ ﾓﾄﾞｽ  *****
		//
		i_lpc = 0;
		for (i_j = 1; i_j <= i_mpc; i_j++) {
			if (i_j != i_mpc && 
				((i_ksw == 1 && f_ipt[i_j - 1] == 0) ||
				 (i_ksw == 2 && f_ipt[i_j - 1] == 1) ||
				 (i_ksw == 3 && f_ipt[i_j - 1] != 1) ||
				 (i_ksw == 4 && f_ipt[i_j - 1] != 0))) {
				if (i_lpc == 0) {
					i_lpc = i_j;
				}
			} else if (i_lpc != 0) {
				d_x1 = f_pnt[i_lpc - 1][0];
				d_y1 = f_pnt[i_lpc - 1][1];
				d_x2 = f_pnt[i_j - 1][0];
				d_y2 = f_pnt[i_j - 1][1];
				f_am = (float)(sqrt((d_x1 - d_x2) * (d_x1 - d_x2) + (d_y1 - d_y2) * (d_y1 - d_y2)));
				// ==== R1911.9 = 2019/12/11 Alv.senoo 汎用サブルーチン誤差対応
				if (f_am >= f_gosa_al) {
					// ============== 2019/12/11 Alv.senoo 汎用サブルーチン誤差対応
					if (*i_lsu < i_i) {
						*i_lsu = *i_lsu + 1;
						f_aa[*i_lsu - 1][0] = f_pnt[i_lpc - 1][0];
						f_aa[*i_lsu - 1][1] = f_pnt[i_lpc - 1][1];
						f_aa[*i_lsu - 1][2] = f_pnt[i_j - 1][0];
						f_aa[*i_lsu - 1][3] = f_pnt[i_j - 1][1];
					} else {
						if (i_nsu >= i_m) {
							goto l_510;
						}
						i_nsu = i_nsu + 1;
						f_aa[i_nsu - 1][0] = f_pnt[i_lpc - 1][0];
						f_aa[i_nsu - 1][1] = f_pnt[i_lpc - 1][1];
						f_aa[i_nsu - 1][2] = f_pnt[i_j - 1][0];
						f_aa[i_nsu - 1][3] = f_pnt[i_j - 1][1];
					}
				}
				i_lpc = 0;
			}
		}
l_510:
		continue;
l_100:
		continue;
	}
	//
	// *****  f_aaﾃ - ﾌﾞﾙ ﾉ ｻｲﾃｷｶ ｵ ｽﾙ  *****
	//
	for (i_i = i_msu + 1; i_i <= i_nsu; i_i++) {
		*i_lsu = *i_lsu + 1;
		f_aa[*i_lsu - 1][0] = f_aa[i_i - 1][0];
		f_aa[*i_lsu - 1][1] = f_aa[i_i - 1][1];
		f_aa[*i_lsu - 1][2] = f_aa[i_i - 1][2];
		f_aa[*i_lsu - 1][3] = f_aa[i_i - 1][3];
	}
l_999:
l_end:
	if (f_ros != NULL) {
		free(f_ros);
	}
	if (f_pnt != NULL) {
		free(f_pnt);
	}
	if (f_ipt != NULL) {
		free(f_ipt);
	}
	return;
}
