/* 指定ビットをON/OFFする */
//void SetBit(char data[32], int pos)
//{
//	int	idx, bit;
//	int	cBits[] = {	0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };
//	idx = pos / 8;
//	bit = pos % 8;
//	if( (0<=bit) && (bit<=7) ){
//		data[idx] = data[idx] | cBits[bit];
//	}
//}

/* 指定ビットをチェックする */

int ChkBit(char data[32], int pos)
{
	int	idx, bit;
	char cWk;
	int  irc;
	int	cBits[] = {	0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };
	
	irc=0;
	cWk = 0x00;
	idx = pos / 8;
	bit = pos % 8;
	if( (0<=bit) && (bit<=7) ){
		cWk = data[idx] & cBits[bit];
		if (cWk == 0x00)
			irc=0;
		else
			irc=1;
	}
	
	return irc;
}
