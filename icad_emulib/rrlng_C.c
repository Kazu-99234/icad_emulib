#include	<stdio.h>
#include	<string.h>
#include	"ComHansub.h"
#include	<math.h>

//**************************************************************************************
//* �֐����@�@:rrlng_C
//* �T�v  �@�@:�����̒����𒲂ׂ�
//* �ڍ�  �@�@:
//* �����@�@�@:[I] �����̎n�_X���W
//* �@�@�@�@�@:[I] �����̎n�_Y���W
//* �@�@�@�@�@:[I] �����̏I�_X���W
//* �@�@�@�@�@:[I] �����̏I�_Y���W
//* �߂�l�@�@:�����̒���
//* �쐬�ҁ@�@:2022/09/15 FXS ��
//* �X�V�ҁ@�@:20xx/xx/xx
//* �X�V���e�@:
//**************************************************************************************
float rrlng_C(float f_xs,float f_ys,float f_xe,float f_ye)
{
	float f_rrlng = 0.0f;

	// = R1302.0 sato = 2013/02/26  �V�H�@
	//   R1302.0  �ύX
	f_rrlng = (float)(sqrt((double)(f_xs - f_xe) * (double)(f_xs - f_xe) + (double)(f_ys - f_ye) * (double)(f_ys - f_ye)));
	// ================ 2013/02/26
	return f_rrlng;
	
}