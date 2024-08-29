#define 	DATA_SIZE	8
#define 	BLK_SIZE	40000
#define 	SEG_BLK_SIZE	5000
#define 	GRP_BLK_SIZE	500

typedef struct  PrmInfo {	// プリミティブ管理
	short	iptype;
	short	ipsize;
	short	imode;
	short	iwt;
	short	ifnt;
	short	iclr;
//	char	*pdata;			// PrmWkinfo用
	int 	ioffset;		// プリミティブ領域先頭からのOFFSET
} PrmInfo;
	
typedef struct  SegInfo {	// セグメント管理
	int 	ivsno;
	int 	isegno;			// ユーザ識別番号
	int 	isysno;			// システム識別番号
	int 	itype;
	int 	iclass;
	int 	ivisi;
	int 	idisp;
	int 	ipcount;
	int 	idel;
//	struct PrmInfo pprm[255];
	struct PrmInfo pprm[511];
} SegInfo;

typedef struct  VsInfo {	// VS管理
	char	vsname[8+1];	// VS名
	int 	vsno;			// VS番号
	int 	iclass;			// アクティブクラス
	int 	iseg;			// アクティブセグメント
	int 	iScount;		// セグメント数
	char*	pSeg;			// セグメントデータ領域ポインタ
	int 	iSmax;			// セグメントデータ領域サイズ
	int 	iSuse;			// セグメントデータ領域利用サイズ
	char*	pPrm;			// プリミティブデータ領域ポインタ
	int 	iPmax;			// プリミティブデータ領域サイズ
	int 	iPuse;			// プリミティブデータ領域利用サイズ
	int 	iGcount;		// グループ数
	char*	pGrp;			// グループデータ領域ポインタ
	int 	iGmax;			// グループデータ領域サイズ
	int 	iGuse;			// グループデータ領域利用サイズ
} VsInfo;

typedef struct GroupInfo {
	int 	ivsno;
	char	grpname[24+1];	// グループ・実像部品名
	int 	isegno;			// ユーザ識別番号
	int 	isysno;			// システム識別番号
	int 	ientcnt;		// 要素数
	int 	igent[512];		// 要素の識別番号
	int		idel;
} GroupInfo;

typedef  struct  GraphicAttribute {	// グラフィック属性
	int 	atrtbl[4];
} GraphicAttribute;

typedef  struct  TextAttribute {	// テキスト属性
	float	atrtb1[6];
	int 	atrtb2[2];
} TextAttribute;



typedef  struct SreadInfo {
	int 	vsno;
	int 	segno;
	int 	prmno;
	struct  SegInfo	*seg;
} SreadInfo;


typedef  struct SrseqInfo {
	int 	vsno;
	char	iclass[32];
	char	type[32];
	int		isno;
} SrseqInfo;



//プリミティブ

typedef  struct  P_point {	// 点
	double	x;
	double	y;
	short	mtype;
} P_point;

typedef  struct  P_line {	// 線分
	double	x;	// 始点
	double	y;
	double	vx;	// 方向ベクトル
	double	vy;
	double	l;	// 長さ
} P_line;

typedef  struct  Vect {	// ベクトル
	double	x;
	double	y;
} Vect;

typedef  struct  P_pline {	// 折れ線
	double	x;	// 始点
	double	y;
	struct Vect vect[254];	// 2点目以降への始点からのベクトル
} P_pline;


typedef  struct  Vlen {
	double	px;	// 開始点への方向ベクトル
	double	py;
	double	l;	// 線の長さ
} Vlen;

typedef  struct  P_hacching {
	double	x;	// 始点
	double	y;
	double	vx;	// 方向ベクトル
	double	vy;
	struct  Vlen hline[168];	// 構成線情報
} P_hacching;

typedef  struct  P_rect {	// 矩形
	double	x;	// 始点
	double	y;
	double	vx;	// 方向ベクトル
	double	vy;
	double	l;	// 横の長さ
	double	m;	// 縦の長さ
} P_rect;


typedef  struct  P_text {
	double	x;	// 始点
	double	y;
	float	h;
	float	w;
	float	d;
	float	ang_t;	// 文字傾き
	float	ang_s;	// 文字列傾き
	int 	idmy1;
	char	flg[4];	// [0]:文字タイプ
	int 	m_su;	// 文字数
	char	mtext[1024];	// 文字列
} p_text;


//void SetBit(char data[32], int pos);
int ChkBit(char data[32], int pos);


float	CNV_SC2Degree(int  isc);
float	CNV_SC2Radian(int  isc);
int 	CNV_Degree2SC(float deg);
int 	CNV_Radian2SC(float rad);


char* get_PrmNext(int  isize, int  *ioff);
char* get_SegNext();
char* get_GrpNext();
char* get_PrmWKNext( int  isize, int  *ioff);

void sbterm_(int  *ircode);
void sbinit_(char param[100], int  *unit, int  *ircode);
void scqerr_(int  *detail);
void serwin_(double window[4], int  *vsno, char actcls[32], char acttyp[32], int  *mode, int  entlst[], int  *size, int  *count, int  *ircode);
void spauxn_(int  *form, char numarry[], int  *n, int  *ircode);
void spsgra_(int  *atrid, int  atrtbl[4], int  *ircode);
void spstxt_(int  *atrid, float atrtb1[6], int  atrtb2[2], int  *font, int  *ircode);
void sscrt2_(int  *type, int  *visi, int  *disp, int  *ircode);
void ssqvs_(int  *vsno);
void ssscls_(int  *iclass, int  *ircode);
void sssvs_(int  *vsno, int  *ircode);
void sversv_(int  *vsno, int  *ircode);
void svopnv_(char vsname[8], int  *vsno, int  *ircode);
void svqopv_(int  vsno[100], int  *cnt);
void svqvsn_(char vsname[8], int  *vsno);
void svqvss_(int  *vsno, char vsname[8], int  status[5], int  *ircode);
void ssqcls_(int  *class);
