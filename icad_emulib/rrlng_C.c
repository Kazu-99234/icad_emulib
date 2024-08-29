#include	<stdio.h>
#include	<string.h>
#include	"ComHansub.h"
#include	<math.h>

//**************************************************************************************
//* 関数名　　:rrlng_C
//* 概要  　　:線分の長さを調べる
//* 詳細  　　:
//* 引数　　　:[I] 線分の始点X座標
//* 　　　　　:[I] 線分の始点Y座標
//* 　　　　　:[I] 線分の終点X座標
//* 　　　　　:[I] 線分の終点Y座標
//* 戻り値　　:線分の長さ
//* 作成者　　:2022/09/15 FXS 武
//* 更新者　　:20xx/xx/xx
//* 更新内容　:
//**************************************************************************************
float rrlng_C(float f_xs,float f_ys,float f_xe,float f_ye)
{
	float f_rrlng = 0.0f;

	// = R1302.0 sato = 2013/02/26  新工法
	//   R1302.0  変更
	f_rrlng = (float)(sqrt((double)(f_xs - f_xe) * (double)(f_xs - f_xe) + (double)(f_ys - f_ye) * (double)(f_ys - f_ye)));
	// ================ 2013/02/26
	return f_rrlng;
	
}