extern	float	CNV_SC2Degree(int );

// slscrd_
// �@�\		�w�肳�ꂽSC�p�x�����W�A���p�x�ɕϊ����܂��B
// in	*sc		�ϊ�����SC�p�x���w�肵�܂�
// out	*rad	�ϊ���̃��W�A���p�x�̕ԓ��̈�

void slscdg_(int *sc, float *deg)
{

	*deg = CNV_SC2Degree(*sc);
}