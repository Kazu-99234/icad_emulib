extern	float	CNV_SC2Degree(int );

// slscrd_
// 機能		指定されたSC角度をラジアン角度に変換します。
// in	*sc		変換するSC角度を指定します
// out	*rad	変換後のラジアン角度の返答領域

void slscdg_(int *sc, float *deg)
{

	*deg = CNV_SC2Degree(*sc);
}