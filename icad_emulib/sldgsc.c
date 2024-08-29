extern	int	CNV_Degree2SC(float );

// sldgsc_
// 機能		指定された角度をSC角度に変換します。
// in	*deg	変換する角度を指定します(単位：度)
// out	*sc		変換後のSC角度の返答領域in *deg 変換する角度を指定します(単位：度)

void sldgsc_(float *deg,int *sc)
{
	
	*sc = CNV_Degree2SC(*deg);
	
}