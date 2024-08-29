#include	<stdio.h>
#include	<string.h>
#include	<math.h>
#include	"ComHansub.h"

//**************************************************************************************
//* 関数名　　:mennuk_C
//* 概要  　　:任意の面（主面）を任意の面（従面）でカットする。
//* 詳細  　　:
//* 引数　　　[I] 主面の頂点の数
//* 　　　　　[I/O] 主面の座標及びカット後の面の座標
//* 　　　　　[I] 従面の頂点の数
//* 　　　　　[I] 従面の座標
//* 　　　　　[O] カット後の面の数
//* 　　　　　[O] 各面の頂点の数
//* 　　　　　[O] 主面と従面の関係
//* 　　　　　[I] 誤差
//* 戻り値　　:無し
//* 作成者　　:2022/10/11 FXS 武
//* 更新者　　:20xx/xx/xx
//* 更新内容　:
//**************************************************************************************
 void mennuk_C(int i_n1, float f_rminn[][SIZE_2], int i_n2,
        float f_rsub[][SIZE_2], int *i_loo, int i_idx[SIZE_10], int *i_ilo, float f_gsa)
{
	int    i_i = 0,
		   i_j = 0,
		   i_k = 0,
		   i_n = 0,
		   i_l = 0,
		   i_ii = 0,
		   i_ll = 0,
		   i_i1 = 0,
		   i_j1 = 0,
		   i_l1 = 0,
		   i_i2 = 0,
		   i_j2 = 0,
		   i_j3 = 0,
		   i_ik = 0,
		   i_jk = 0,
		   i_ki = 0,
		   i_kj = 0,
		   i_k1 = 0,
		   i_k2 = 0,
		   i_na = 0,
		   i_nm = 0,
		   i_ns = 0,
		   i_nb = 0,
		   i_nn = 0,
		   i_np = 0,
		   i_ma = 0,
		   i_mb = 0,
		   i_kp = 0,
		   i_kh = 0,
		   i_ia = 0,
		   i_ib = 0,
		   i_l0 = 0,
		   i_l01 = 0,
		   i_ics = 0,
		   i_ih1 = 0,
		   i_ih2 = 0,
		   i_jh1 = 0,
		   i_jh2 = 0,
		   i_ksw = 0,
		   i_lp[SIZE_100],
		   i_indx[SIZE_100],
		   i_lhen[SIZE_200],
		   i_iten[SIZE_100][SIZE_2],
		   i_khen[SIZE_100][SIZE_3],
		   i_ihen[SIZE_200][SIZE_2],
		   i_jhen[SIZE_200][SIZE_2],
		   i_iihen[SIZE_200][SIZE_2],
		   i_jjhen[SIZE_200][SIZE_2];
		   // ==== R1911.9 = 2019/12/10 Alv.hayashi 汎用サブルーチン誤差対応
	float  f_x = 0.0f,
		   f_y = 0.0f,
		   f_x0 = 0.0f,
		   f_y0 = 0.0f,
		   f_x1 = 0.0f,
		   f_y1 = 0.0f,
		   f_x2 = 0.0f,
		   f_y2 = 0.0f,
		   f_x11 = 0.0f,
		   f_y11 = 0.0f,
		   f_x22 = 0.0f,
		   f_y22 = 0.0f,
		   f_gsa2 = 0.0f,
		   f_eps = 0.0f,
		   f_xxx = 0.0f,
		   // ============== 2019/12/10 Alv.hayashi 汎用サブルーチン誤差対応
		   // = R1711.0 sugimoto = 2017 / 11 / 30 Windows移行 ポイント不足
		   f_zppp[SIZE_100],
		   f_zpp[SIZE_100][SIZE_2],
		   f_xp[SIZE_4000][SIZE_2];
	double d_gosa = 0.0;

	// ==================== 2017/11/30 Windows移行 ポイント不足
	// = R1711.0 sugimoto = 2017/11/30 Windows移行 ポイント不足
	// ==================== 2017/11/30 Windows移行 ポイント不足
	memset(i_lp, 0, sizeof(i_lp));
	memset(i_indx, 0, sizeof(i_indx));
	memset(i_lhen, 0, sizeof(i_lhen));
	memset(i_iten, 0, sizeof(i_iten));
	memset(i_khen, 0, sizeof(i_khen));
	memset(i_ihen, 0, sizeof(i_ihen));
	memset(i_jhen, 0, sizeof(i_jhen));
	memset(i_iihen, 0, sizeof(i_iihen));
	memset(i_jjhen, 0, sizeof(i_jjhen));
	memset(f_zppp, 0, sizeof(f_zppp));
	memset(f_zpp, 0, sizeof(f_zpp));
	memset(f_xp, 0, sizeof(f_xp));
	memset(i_idx, 0, sizeof(int) * SIZE_10);

	// ==== System R0402.0 ==== 2004/2(hatanaka)
	*i_loo = 0;
	// == == == == == == == == == == == == 2004 / 2(hatanaka)
	//	= R1809.0 sugimoto = 2018 / 09/19 作図パターン追加
	//	= POINT用誤差精度アップ
	d_gosa = -0.1;
	// ==================== 2018/09/19 作図パターン追加
	f_eps = f_gsa;
	// ==== R1911.9 = 2019/12/10 Alv.hayashi 汎用サブルーチン誤差対応
	f_gsa2 = f_gsa;
	if (fabsf(f_gsa2) < F_KIJUN) {
		f_eps = F_KOYO_GOSA;
		f_gsa2 = F_KOYO_GOSA;
	}
	// ============== 2019/12/10 Alv.hayashi 汎用サブルーチン誤差対応
	f_xxx = 0.1f;
	i_nm = i_n1;
	i_ns = i_n2;
	//  ｼﾕﾒﾝ ﾉ ﾎﾟｲﾝﾄ(ｻﾞﾋﾖｳ) ﾄ ｼﾞﾕｳﾒﾝ ﾉ ﾎﾟｲﾝﾄ ｵ ｱﾜｾﾃ f_xp ﾍ ｾﾂﾄｽﾙ
	for (i_i = 1; i_i <= i_nm; i_i++) {
		f_xp[i_i - 1][0] = f_rminn[i_i - 1][0];
		f_xp[i_i - 1][1] = f_rminn[i_i - 1][1];
	}
	//  ﾄﾞｳｲﾂｾﾝｼﾞﾖｳ ﾉ ﾎﾟｲﾝﾄ ｵ ｹｽ
	// ==== R1911.9 = 2019/12/10 Alv.hayashi 汎用サブルーチン誤差対応
	rksen2_C(&i_nm, (float (*)[SIZE_2])f_xp, f_gsa2);
	// ============== 2019/12/10 Alv.hayashi 汎用サブルーチン誤差対応
	for (i_i = 1; i_i <= i_ns; i_i++) {
		i_i1 = i_nm + i_i;
		f_xp[i_i1 - 1][0] = f_rsub[i_i - 1][0];
		f_xp[i_i1 - 1][1] = f_rsub[i_i - 1][1];
	}
	// ==== R1911.9 = 2019/12/10 Alv.hayashi 汎用サブルーチン誤差対応
	rksen2_C(&i_ns, (float(*)[SIZE_2])f_xp[i_nm], f_gsa2);

	// ============== 2019/12/10 Alv.hayashi 汎用サブルーチン誤差対応
	// ｼﾞﾕｳﾒﾝ ｵ ﾋﾀﾞﾘﾏﾜﾘ ﾆ ｽﾙ
	round3_C(i_ns, (float(*)[SIZE_2])f_xp[i_nm]);
	i_n = i_nm + i_ns;
	//
	//	  ﾄﾞｳｲﾂ ﾎﾟｲﾝﾄ ｵ ｻｶﾞｼ fi_iten(2, 100) ﾉ ﾃ - ﾌﾞﾙ ｵ ﾂｸﾙ
	i_kp = 0;
	for (i_i = 1; i_i <= i_nm; i_i++) {
		f_x1 = f_xp[i_i - 1][0];
		f_y1 = f_xp[i_i - 1][1];
		for (i_j = 1; i_j <= i_ns; i_j++) {
			i_j1 = i_j + i_nm;
			f_x2 = f_xp[i_j1 - 1][0];
			f_y2 = f_xp[i_j1 - 1][1];
			if (sqrtf((f_x1 - f_x2) * (f_x1 - f_x2) + (f_y1 - f_y2) * (f_y1 - f_y2)) < f_eps) {
				goto l_1400;
			}
		}
		goto l_1200;
l_1400:
		i_kp = i_kp + 1;
		i_iten[i_kp - 1][0] = i_i;
		i_iten[i_kp - 1][1] = i_j1;
l_1200:
		continue;
	}
	//
	//  ｼﾕﾒﾝ ﾄ ｼﾞﾕｳﾒﾝ ﾉ ｺｳﾃﾝ ｵ ﾓﾄﾒﾙ
	//
	//   ik-- - ihen ﾃ - ﾌﾞﾙ ﾉ ｺｽｳ
	//   jk-- - jhen ﾃ - ﾌﾞﾙ ﾉ ｺｽｳ
	//   ics-- - ｺｳﾃﾝ ﾉ ｺｽｳ
	//   khen(5, 50)-- - ｺｳﾃﾝ ﾃ - ﾌﾞﾙ
	//   khen(1, i)-- - ｺｳﾃﾝ ﾊﾞﾝｺﾞｳ
	//   khen(2, i)-- - ﾍﾝ 2 ﾉ ｼﾃﾝ    ﾊﾞﾝｺﾞｳ
	//   khen(3, i)-- - ﾍﾝ 2 ﾉ ｼﾕｳﾃﾝ  ﾊﾞﾝｺﾞｳ
	i_ik = 0;
	i_jk = 0;
	i_ics = 0;
	i_k = 0;
	for (i_i = 1; i_i <= i_nm; i_i++) {
		i_na = i_i;
		f_x1 = f_xp[i_i - 1][0];
		f_y1 = f_xp[i_i - 1][1];
		if (i_i == i_nm) {
			goto l_1600;
		}
		i_nb = i_i + 1;
		f_x2 = f_xp[i_i][0];
		f_y2 = f_xp[i_i][1];
		goto l_1700;
l_1600:
		i_nb = 1;
		f_x2 = f_xp[0][0];
		f_y2 = f_xp[0][1];
l_1700:
		i_l = 2;

		//  zpp(2, 50)---- 1ﾍﾟﾝ ﾉ ｳｴﾆｱﾙ  ｻﾞﾋﾖｳ(x, y)
		//  lp(50)---- 1ﾍﾟﾝ ﾉ ｳｴﾆｱﾙ  ﾊﾞﾝｺﾞｳ
		//  l-- - 1ﾍﾟﾝ ﾉ ｳｴﾆｱﾙ  ｺｳﾃﾝﾉ ｶｽﾞ
		f_zpp[0][0] = f_x1;
		f_zpp[1][0] = f_y1;
		f_zpp[1][0] = f_x2;
		f_zpp[1][1] = f_y2;
		i_lp[0] = i_na;
		i_lp[1] = i_nb;
		for (i_j = 1; i_j <= i_ns; i_j++) {
			i_j1 = i_j + i_nm;
			i_ma = i_j1;
			f_x11 = f_xp[i_j1 - 1][0];
			f_y11 = f_xp[i_j1 - 1][1];
			if (i_j == i_ns) {
				goto l_1900;
			}
			i_mb = i_j1 + 1;
			f_x22 = f_xp[i_j1][0];
			f_y22 = f_xp[i_j1][1];
			goto l_2000;
l_1900:
			i_mb = i_nm + 1;
			f_x22 = f_xp[i_mb - 1][0];
			f_y22 = f_xp[i_mb - 1][1];
l_2000:
			kjtcrs_C(f_x1, f_y1, f_x2, f_y2, f_x11, f_y11, f_x22, f_y22, &f_x, &f_y, &i_nn, f_xxx);
			if (i_nn != 1) {
				goto l_1800;
			}
			i_ics = i_ics + 1;
			if (sqrtf((f_x - f_x1) * (f_x - f_x1) + (f_y - f_y1) * (f_y - f_y1)) < f_eps) {
				goto l_2310;
			}
			if (sqrtf((f_x - f_x2) * (f_x - f_x2) + (f_y - f_y2) * (f_y - f_y2)) < f_eps) {
				goto l_2320;
			}
			if (sqrtf((f_x - f_x11) * (f_x - f_x11) + (f_y - f_y11) * (f_y - f_y11)) < f_eps) {
				goto l_2100;
			}
			if (sqrtf((f_x - f_x22) * (f_x - f_x22) + (f_y - f_y22) * (f_y - f_y22)) < f_eps) {
				goto l_2200;
			}
			//  ｼﾝﾎﾟｲﾝﾄ ｵ ﾂｸﾙ
			i_n = i_n + 1;
			f_xp[i_n - 1][0] = f_x;
			f_xp[i_n - 1][1] = f_y;
			i_np = i_n;
			goto l_2300;
l_2100:
			i_np = i_ma;
			goto l_2300;
l_2200:
			i_np = i_mb;
l_2300:
			for (i_ii = 1; i_ii <= i_l; i_ii++) {
				if (i_np == i_lp[i_ii - 1]) {
					goto l_2350;
				}
			}
			i_l = i_l + 1;
			i_lp[i_l - 1] = i_np;
			f_zpp[i_l - 1][0] = f_x;
			f_zpp[i_l - 1][1] = f_y;
			goto l_2350;
l_2310:
			i_np = i_na;
			goto l_2350;
l_2320:
			i_np = i_nb;
l_2350:
			if (sqrtf((f_x - f_x11) * (f_x - f_x11) + (f_y - f_y11) * (f_y - f_y11)) < f_eps) {
				goto l_1800;
			}
			if (sqrtf((f_x - f_x22) * (f_x - f_x22) + (f_y - f_y22) * (f_y - f_y22)) < f_eps) {
				goto l_1800;
			}
			if (i_k == 0) {
				goto l_2360;
			}
			for (i_ii = 1; i_ii <= i_k; i_ii++) {
				if (i_np == i_khen[i_ii - 1][0]) {
					goto l_1800;
				}
			}
l_2360:
			i_k = i_k + 1;
			i_khen[i_k - 1][0] = i_np;
			i_khen[i_k - 1][1] = i_ma;
			i_khen[i_k - 1][2] = i_mb;
l_1800:
		continue;
		}
		//
		//   ｼﾃﾝ ﾄ ｿﾉﾀﾉﾃﾝ ﾄﾉ ｷﾖﾘ ｵﾓﾄﾒﾃ ｿ - ﾄ ｽﾙ
		if (i_l == 2) {
			goto l_2400;
		}
		f_zppp[0] = 0.0f;
		for (i_ii = 2; i_ii <= i_l; i_ii++) {
			f_zppp[i_ii - 1] = sqrtf((f_zpp[i_ii - 1][0] - f_x1) * (f_zpp[i_ii - 1][0] - f_x1)
				+ (f_zpp[i_ii - 1][1] - f_y1) * (f_zpp[i_ii - 1][1] - f_y1));
		}
		aasort_C(f_zppp, i_indx, i_l, i_l);

		//  ihen ﾃ - ﾌﾞﾙ ｵ ﾂｸﾙ
		i_l1 = i_l - 1;
		for (i_ii = 1; i_ii <= i_l1; i_ii++) {
			i_ik = i_ik + 1;
			i_j1 = i_indx[i_ii - 1];
			i_j2 = i_indx[i_ii];
			i_ihen[i_ik - 1][0] = i_lp[i_j1 - 1];
			i_ihen[i_ik - 1][1] = i_lp[i_j2 - 1];
		}
		goto l_1500;
l_2400:
		i_ik = i_ik + 1;
		i_ihen[i_ik - 1][0] = i_lp[0];
		i_ihen[i_ik - 1][1] = i_lp[1];
l_1500:
		continue;
	}
	if (i_ics != 0) {
			goto  l_2700;
	}
	f_x = (f_x11 + f_x22) / 2.;
	f_y = (f_y11 + f_y22) / 2.;
	point_C((float(*)[SIZE_2])f_xp, i_nm, f_x, f_y, &i_kh, d_gosa);
	if (i_kh != 1) {
		goto l_1510;
	}
	*i_ilo = 2;
	return;
l_1510:
	f_x = (f_x1 + f_x2) / 2.;
	f_y = (f_y1 + f_y2) / 2.;
	point_C((float(*)[SIZE_2])f_xp[i_nm], i_ns, f_x, f_y, &i_kh, d_gosa);
	if (i_kh != 1) {
		goto l_1520;
	}
	*i_ilo = 3;
	return;
l_1520:
	*i_ilo = 0;
	return;
l_2700:
	//
	//  ｼﾞﾕｳﾒﾝ ﾆ ﾂｲﾃ i_jhen ﾃ - ﾌﾞﾙ ｵ ﾂｸﾙ
	for (i_i = 1; i_i <= i_ns; i_i++) {
		i_i1 = i_i + i_nm;
		i_ll = 2;
		i_ia = i_i1;
		i_ib = i_i1 + 1;
		if (i_i == i_ns) {
			i_ib = i_nm + 1;
		}
		i_lp[0] = i_ia;
		i_lp[1] = i_ib;
		if (i_k == 0) {
			goto l_3110;
		}
		for (i_j = 1; i_j <= i_k; i_j++) {
			if (i_ia == i_khen[i_j - 1][1] && i_ib == i_khen[i_j - 1][2]) {
				goto l_3200;
			}
			goto l_3100;
l_3200:
			i_ll = i_ll + 1;
			i_lp[i_ll - 1] = i_khen[i_j - 1][0];
l_3100:
			continue;
		}
l_3110:
		f_x0 = f_xp[i_ia - 1][0];
		f_y0 = f_xp[i_ia - 1][1];
		if (i_ll == 2) {
			goto  l_3300;
		}
		f_zppp[0] = 0.;
		for (i_j = 2; i_j <= i_ll; i_j++) {
			i_j1 = i_lp[i_j - 1];
			f_x1 = f_xp[i_j1 - 1][0];
			f_y1 = f_xp[i_j1 - 1][1];
			f_zppp[i_j - 1] = sqrtf((f_x0 - f_x1) * (f_x0 - f_x1) + (f_y0 - f_y1) * (f_y0 - f_y1));
		}
		aasort_C(f_zppp, i_indx, i_ll, i_ll);

		//  jhen ﾃ - ﾌﾞﾙ
		i_l1 = i_ll - 1;
		for (i_j = 1; i_j <= i_l1; i_j++) {
			i_jk = i_jk + 1;
			i_j1 = i_indx[i_j - 1];
			i_j2 = i_indx[i_j];
			i_jhen[i_jk - 1][0] = i_lp[i_j1 - 1];
			i_jhen[i_jk - 1][1] = i_lp[i_j2 - 1];
		}
		goto l_3000;
l_3300:
		i_jk = i_jk + 1;
		i_jhen[i_jk - 1][0] = i_lp[0];
		i_jhen[i_jk - 1][1] = i_lp[1];
l_3000:
		continue;
	}
	//
	//  jhen ﾃ - ﾌﾞﾙ ﾉ ﾎﾟｲﾝﾄﾒｲ ﾃﾞ ｼﾕﾒﾝ ﾉ ﾎﾟｲﾝﾄ ﾆ ｲﾂﾁｽﾙﾓﾉﾊ ｼﾕﾒﾝ ﾉ ﾎﾟｲﾝﾄﾒｲ ﾆ ｽﾙ
	if (i_kp == 0) {
		goto l_3650;
	}
	for (i_i = 1; i_i <= i_jk; i_i++) {
		for (i_j = 1; i_j <= i_kp; i_j++) {
			if (i_jhen[i_i - 1][0] == i_iten[i_j - 1][1]) {
				i_jhen[i_i - 1][0] = i_iten[i_j - 1][0];
			}
			if (i_jhen[ i_i - 1][1] == i_iten[ i_j - 1][1]) {
				i_jhen[i_i - 1][1] = i_iten[i_j - 1][0];
			}
		}
	}

	//  ihen, jhen ｵ ｸﾗﾍﾞﾙ
	//       ﾏﾂﾀｸ ｵﾅｼﾞ
	//                         ｲﾂﾎﾟｳ ｵ ｹｽ(0 ﾄ ｽﾙ)
	//       ｷﾞﾔｸ ﾉ ﾅﾗﾋﾞ ﾉ ﾄｷ
	//                         ﾘﾖｳﾎｳ ﾄﾓ ｹｽ
l_3650:
	for (i_i = 1; i_i <= i_ik; i_i++) {
		i_ih1 = i_ihen[i_i - 1][0];
		i_ih2 = i_ihen[i_i - 1][1];
		for (i_j = 1; i_j <= i_jk; i_j++) {
			i_jh1 = i_jhen[i_j - 1][0];
			i_jh2 = i_jhen[i_j - 1][1];
			if (i_ih1 == i_jh1 && i_ih2 == i_jh2) {
				goto l_4200;
			}
			if (i_ih1 == i_jh2 && i_ih2 == i_jh1) {
				goto l_4300;
			}
		}
		goto l_4000;
l_4200:
		i_jhen[i_j - 1][0] = 0;
		i_jhen[i_j - 1][1] = 0;
		i_ihen[i_i - 1][0] = -i_ih1;
		i_ihen[i_i - 1][1] = -i_ih2;
		goto l_4000;
l_4300:
		i_ihen[i_i - 1][0] = 0;
		i_ihen[i_i - 1][1] = 0;
		i_jhen[i_j - 1][0] = 0;
		i_jhen[i_j - 1][1] = 0;
l_4000:
		continue;
	}
	//
	//  2ﾃﾝ ﾉ ﾁﾕｳﾃﾝ ｶﾞ ｱｲﾃﾉ ﾌﾞﾛﾂｸ ﾆ ﾊｲﾂﾃｲﾙﾊﾞｱｲ ﾊ ﾊﾌﾞｸ
	//
	//  ihen ﾆ ﾂｲﾃ
	for (i_i = 1; i_i <= i_ik; i_i++) {
		i_i1 = i_ihen[i_i - 1][0];
		i_i2 = i_ihen[i_i - 1][1];
		if (i_i1 == 0) {
			goto  l_4400;
		}
		if (i_i1 < 0) {
			goto l_4410;
		}
		f_x = (f_xp[i_i1 - 1][0] + f_xp[i_i2 - 1][0]) / 2.0f;
		f_y = (f_xp[i_i1 - 1][1] + f_xp[i_i2 - 1][1]) / 2.0f;
		point_C((float(*)[SIZE_2])f_xp[i_nm], i_ns, f_x, f_y, &i_kh, d_gosa);
		if (i_kh != 3) {
			goto l_4420;
		}
		f_x = f_xp[i_i1 - 1][0];
		f_y = f_xp[i_i1 - 1][1];
		point_C((float(*)[SIZE_2])f_xp[i_nm], i_ns, f_x, f_y, &i_kh, d_gosa);
		if (i_kh != 3) {
			goto l_4420;
		}
		f_x = f_xp[i_i2 - 1][0];
		f_y = f_xp[i_i2 - 1][1];
		point_C((float(*)[SIZE_2])f_xp[i_nm], i_ns, f_x, f_y, &i_kh, d_gosa);
l_4420:
		if (i_kh != 1) {
			goto l_4400;
		}
		i_ihen[i_i - 1][0] = 0;
		i_ihen[i_i - 1][1] = 0;
		goto l_4400;
l_4410:
		i_ihen[i_i - 1][0] = -i_i1;
		i_ihen[i_i - 1][1] = -i_i2;
l_4400:
		continue;
	}
	//
	//  jhen ﾆ ﾂｲﾃ
	for (i_i = 1; i_i <= i_jk; i_i++) {
		i_i1 = i_jhen[i_i - 1][0];
		i_i2 = i_jhen[i_i - 1][1];
		if (i_i1 == 0) {
			goto l_4500;
		}
		f_x = (f_xp[i_i1 - 1][0] + f_xp[i_i2 - 1][0]) / 2.0;
		f_y = (f_xp[i_i1 - 1][1] + f_xp[i_i2 - 1][1]) / 2.0;
		point_C((float (*)[SIZE_2])f_xp, i_nm, f_x, f_y, &i_kh, d_gosa);
		if (i_kh != 3) {
			goto l_4430;
		}
		f_x = f_xp[i_i1 - 1][0];
		f_y = f_xp[i_i1 - 1][1];
		point_C((float(*)[SIZE_2])f_xp, i_nm, f_x, f_y, &i_kh, d_gosa);
		if (i_kh != 3) {
			goto l_4430;
		}
		f_x = f_xp[i_i2 - 1][0];
		f_y = f_xp[i_i2 - 1][1];
		point_C((float(*)[SIZE_2])f_xp, i_nm, f_x, f_y, &i_kh, d_gosa);
l_4430:
		if (i_kh == 1) {
			goto l_4500;
		}
		i_jhen[i_i - 1][0] = 0;
		i_jhen[i_i - 1][1] = 0;
l_4500:
		continue;
	}
	//
	//  ihen ﾉ ｺｽｳ  ki
	//  jhen ﾉ ｺｽｳ  kj
	//
l_4550:
	i_ki = 0;
	for (i_i = 1; i_i <= i_ik; i_i++) {
		if (i_ihen[i_i - 1][0] == 0) {
			goto l_4600;
		}
		i_ki = i_ki + 1;
		i_ihen[i_ki - 1][0] = i_ihen[i_i - 1][0];
		i_ihen[i_ki - 1][1] = i_ihen[i_i - 1][1];
l_4600:
		continue;
	}
	i_kj = 0;
	for (i_i = 1; i_i <= i_jk; i_i++) {
		if (i_jhen[i_i - 1][0] == 0) {
			goto l_4700;
		}
		i_kj = i_kj + 1;
		i_jhen[i_kj - 1][0] = i_jhen[i_i - 1][0];
		i_jhen[i_kj - 1][1] = i_jhen[i_i - 1][1];
l_4700:
		continue;
	}
	if (i_ki == 0 && i_kj == 0) {
		*i_ilo = 4;
		return;
	}
	for (i_i = 1; i_i <= i_ki; i_i++) {
		i_iihen[i_i - 1][0] = i_ihen[i_i - 1][0];
		i_iihen[i_i - 1][1] = i_ihen[i_i - 1][1];
	}
	for (i_i = 1; i_i <= i_kj; i_i++) {
		i_jjhen[i_i - 1][0] = i_jhen[i_i - 1][0];
		i_jjhen[i_i - 1][1] = i_jhen[i_i - 1][1];
	}
	//
	//  ihen, jhen ｵ ｱﾜｾﾃ ﾒﾝ ｵ ｺﾞｳｾｲ ｽﾙ
	//
	i_l0 = 0;
	*i_loo = 0;
	i_l01 = i_l0;
l_5000:
	i_ksw = 0;
	if (i_l0 == i_ki + i_kj) {
		goto  l_5100;
	}
	for (i_i = 1; i_i <= i_ki; i_i++) {
		i_i1 = i_ihen[i_i - 1][0];
		i_i2 = i_ihen[i_i - 1][1];
		if (i_i1 != 0) {
			goto  l_5300;
		}
	}
	for (i_i = 1; i_i <= i_kj; i_i++) {
		i_i1 = i_jhen[i_i - 1][0];
		i_i2 = i_jhen[i_i - 1][1];
		if (i_i1 != 0) {
			goto l_5500;
		}
	}
	goto l_5100;
l_5300:
	i_j3 = i_i;
	i_j1 = i_i1;
	i_j2 = i_i2;
	i_l0 = i_l0 + 1;
	i_lhen[i_l0 - 1] = i_i1;
	i_l0 = i_l0 + 1;
	i_lhen[i_l0 - 1] = i_i2;
	i_ihen[i_i - 1][0] = 0;
	i_ihen[i_i - 1][1] = 0;
	goto l_5900;
l_5500:
	i_j3 = i_i;
	i_l0 = i_l0 + 1;
	i_lhen[i_l0 - 1] = i_i1;
	i_l0 = i_l0 + 1;
	i_lhen[i_l0 - 1] = i_i2;
	i_jhen[i_i - 1][0] = 0;
	i_jhen[i_i - 1][1] = 0;
	i_ksw = 0;
l_5600:
	for (i_j = 1; i_j <= i_ki; i_j++) {
		i_j1 = i_ihen[i_j - 1][0];
		i_j2 = i_ihen[i_j - 1][1];
		if (i_j1 == 0) {
			goto l_5700;
		}
		if (i_j1 == i_i2) {
			goto l_5800;
		}
l_5700:
		continue;
	}
	if (i_ksw == 1) {
		goto l_6410;
	}
	i_j2 = i_i2;
	i_ksw = i_ksw + 1;
l_5900:
	for (i_k = 1; i_k <= i_kj; i_k++) {
		i_k1 = i_jhen[i_k - 1][0];
		i_k2 = i_jhen[i_k - 1][1];
		if (i_k1 == 0) {
			goto  l_6000;
		}
		if (i_j2 == i_k1) {
			goto l_6100;
		}
l_6000:
		continue;
	}
	i_i2 = i_j2;
	if (i_ksw == 1) {
		goto l_6420;
	}
	i_ksw = i_ksw + 1;
	goto l_5600;
l_6100:
	i_j3 = i_k;
	i_jhen[i_k - 1][0] = 0;
	i_jhen[i_k - 1][1] = 0;
	i_ksw = 0;
	if (i_k2 == i_i1) {
		goto l_6200;
	}
	i_l0 = i_l0 + 1;
	i_lhen[i_l0 - 1] = i_k2;
	i_i2 = i_k2;
	goto  l_5600;
l_5800:
	i_j3 = i_j;
	i_ihen[i_j - 1][0] = 0;
	i_ihen[i_j - 1][1] = 0;
	i_ksw = 0;
	if (i_j2 == i_i1) {
		goto l_6200;
	}
	i_l0 = i_l0 + 1;
	i_lhen[i_l0 - 1] = i_j2;
	goto l_5900;
l_6200:
	*i_loo = *i_loo + 1;
	i_idx[*i_loo - 1] = i_l0 - i_l01;
	i_l01 = i_l0;
	goto l_5000;
l_5100:
	if (i_l0 <= 2) {
		goto l_6400;
	}
	// = R1906.0 sugimoto = 2019/07/01 431802507289 テーブル拡張
	if (i_l0 > 200) {
		i_l0 = 200;
	}
	// ==================== 2019/07/01 431802507289 テーブル拡張
	for (i_i = 1; i_i <= i_l0; i_i++) {
		i_l1 = i_lhen[i_i - 1];
		f_rminn[i_i - 1][0] = f_xp[i_l1 - 1][0];
		f_rminn[i_i - 1][1] = f_xp[i_l1 - 1][1];
	}
	*i_ilo = 1;
	return;
	//  ﾒﾝｺﾞｳｾｲ ﾃﾞｷﾅｶﾂﾀ ﾄｷ ﾂﾅｶﾞﾗﾅｲ ﾍﾝ ｵ ｹｼ ﾓｳｲﾁﾄﾞ ｺﾞｳｾｲ ｼﾅｵｽ
l_6410:
	i_iihen[i_j3 - 1][0] = 0;
	i_iihen[i_j3 - 1][1] = 0;
	goto l_6430;
l_6420:
	i_jjhen[i_j3 - 1][0] = 0;
	i_jjhen[i_j3 - 1][1] = 0;
l_6430:
	if (*i_loo >= 1) {
		goto l_5100;
	}
	for (i_i = 1; i_i <= i_ki; i_i++) {
		i_ihen[0][i_i - 1] = i_iihen[i_i - 1][0];
		i_ihen[1][i_i - 1] = i_iihen[i_i - 1][1];
	}
	for (i_i = 1; i_i <= i_kj; i_i++) {
		i_jhen[0][i_i - 1] = i_jjhen[i_i - 1][0];
		i_jhen[1][i_i - 1] = i_jjhen[i_i - 1][1];
	}
	i_jk = i_kj;
	i_ik = i_ki;
	goto l_4550;
l_6400:
	*i_ilo = 9;
	return;
	//     debug init,subchk
}