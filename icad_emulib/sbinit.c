#include <memory.h>
#include "icad_emu.h"

struct VsInfo	VsInfodata[500];
int	act_vsno;

struct GraphicAttribute  GraAttr[4];
int	cur_gra_atr;

struct  SegInfo SegWK;
//struct  PrmInfo PrmWkinfo[255];

//char    PrmWK[40000];
char    *PrmWK;
int     iPWK_max;
int		iPWK_use;

struct  TextAttribute  TxtAttr[4];
int	cur_txt_atr;

int	cur_mode;	// 編集モード

int	cur_class;	// 作図クラス

int    err_syosai;	// 詳細エラー
	
int	iSyscnt[500];	// システム識別番号カウント

struct SreadInfo	Sread;
struct SrseqInfo	Srseq;

char	MMF_Dirpath[17][256+1];

int	Update_ivs;		// 編集セグメント
int	Update_segno;		// 編集セグメント
int	Update_sysno;		// 編集セグメント
int	Update_segidx;		// 編集セグメントindex
int	Update_curprm;

void sbinit_(char param[100],int *unit,int *ircode)
{
	// 初期化

	memset(VsInfodata, 0, sizeof(VsInfodata));
	act_vsno=0;
	
	VsInfodata[0].vsno = 1;
	strcpy(VsInfodata[0].vsname, "!!GLOBAL");
	
	VsInfodata[1].vsno = 2;
	strcpy(VsInfodata[1].vsname, "!XY     ");

	memset(GraAttr, 0, sizeof(GraAttr));
	cur_gra_atr=0;

	memset(TxtAttr, 0, sizeof(TxtAttr));
	cur_txt_atr = 0;

	cur_mode = 0;

	memset(iSyscnt, 0, sizeof(iSyscnt));
	
	PrmWK=0;
	
	memset(MMF_Dirpath, 0, sizeof(MMF_Dirpath));
	
	Update_ivs = 0;
	Update_segno = 0;
	Update_sysno = 0;
	Update_segidx = -1;
	Update_curprm = 0;
	
	*ircode = 0;

	return;
}
