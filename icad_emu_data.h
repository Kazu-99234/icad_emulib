
extern	struct VsInfo	VsInfodata[500];
extern	int 	act_vsno;

extern	struct GraphicAttribute  GraAttr[4];
extern	int 	cur_gra_atr;

extern	struct  SegInfo SegWK;
//extern	struct  PrmInfo PrmWkinfo[255];


//extern	char    PrmWK[40000];
extern	char    *PrmWK;

extern	int     iPWK_max;
extern	int	iPWK_use;

extern	struct  TextAttribute  TxtAttr[4];
extern	int 	cur_txt_atr;

extern	int 	cur_mode;	// 編集モード

extern	int 	cur_class;	// 作図クラス

extern	int     err_syosai;	// 詳細エラー
	
extern	int 	iSyscnt[500];	// システム識別番号カウント

extern	struct SreadInfo	Sread;
extern	struct SrseqInfo	Srseq;

extern	int 	Update_ivs;
extern	int 	Update_segno;
extern	int 	Update_sysno;
extern	int 	Update_segidx;
extern	int 	Update_curprm;

extern	char	MMF_Dirpath[17][256+1];
