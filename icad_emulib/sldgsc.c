extern	int	CNV_Degree2SC(float );

// sldgsc_
// �@�\		�w�肳�ꂽ�p�x��SC�p�x�ɕϊ����܂��B
// in	*deg	�ϊ�����p�x���w�肵�܂�(�P�ʁF�x)
// out	*sc		�ϊ����SC�p�x�̕ԓ��̈�in *deg �ϊ�����p�x���w�肵�܂�(�P�ʁF�x)

void sldgsc_(float *deg,int *sc)
{
	
	*sc = CNV_Degree2SC(*deg);
	
}