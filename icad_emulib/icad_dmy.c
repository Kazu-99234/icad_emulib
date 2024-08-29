#include <stdlib.h>
#include <time.h>

void idate_(int idt[])
{
	time_t	t1;
	
	time(&t1);
	struct tm *local = localtime(&t1);
	
	idt[0] = local->tm_mday;
	idt[1] = local->tm_mon + 1;
	idt[2] = local->tm_year + 1900;
}

void itime_(int itm[])
{
	time_t	t1;
	
	time(&t1);
	struct tm *local = localtime(&t1);
	
	itm[0] = local->tm_hour;
	itm[1] = local->tm_min;
	itm[2] = local->tm_sec;
}


void system_(char *line)
{
	system(line);
}

void sorefs_(int *ircode)
{
	*ircode = 0;

	return;
}

void svport_(int *vpno, int *vsno, int *wfno, int *vwno, int *ircode)
{
	*ircode = 0;

	return;
}

void imsggt_(int *msgno, int *ip1, int *ip2, char msg[], int *iszie, int *size, int *msglvl, int *ircode)
{
	*ircode = 0;

	return;
}

void imsgpt_(int *msgno, char insmsg[], int *n, int *msglvl, int *ircode)
{
	*ircode = 0;

	return;
}
void imwrit_(char wrtdat[], int *lwrtdt, int *color, int *ircode)
{
	*ircode = 0;

return;
}

void dnopvw_(int *view_no, double pos[2], double *scale, int *vsno, int ircode[2])
{
	*ircode = 0;

	return;
}

/*
void syralc_(int *mmfno, char mmfnam[], int *leng, int *ircode)
{
	*ircode = 0;

	return;
}

void sysave_(int *msfno, char mname[40], int *prtct, char psword[8], char cdata[80], char vsno[32], char wfno[32], int inform[4], int *ircode)
{
	*ircode = 0;

	return;
}
*/

void sddgrd_(int *pdno, float *x, float *y, float grdata[7], int *jon, int *ircode)
{
	*ircode = 0;

	return;
}

void sdsgrd_(float grdata[7], int *jon, int *ircode)
{
	*ircode = 0;

	return;
}

void scqapd_(int *pdno)
{
	int ircode;
	ircode = 0;

	return;
}

void sdsegd_(int *pdno, int *grdflg, int *ircode)
{
	*ircode = 0;

	return;
}



void dnstxt_(int *atrid, int linf[10], double dinf[10], int ircode[2])
{
	*ircode = 0;

	return;
}

void dncnot_(double pos[2], char cinf[20][160], int linf[10], int *pesadr, int ircode[2])
{
	*ircode = 0;

	return;
}

void siscls_(char actcls[32])
{
	
	return;
}

void syqmdl_(int *msfno,char mname[40],int *alevel,int *qlevel,char sname[8],int mdlinf[4], char chrinf[88],int *ircode)
{
	*ircode = 0;

	return;
}
