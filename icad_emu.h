#define 	DATA_SIZE	8
#define 	BLK_SIZE	40000
#define 	SEG_BLK_SIZE	5000
#define 	GRP_BLK_SIZE	500

typedef struct  PrmInfo {	// �v���~�e�B�u�Ǘ�
	short	iptype;
	short	ipsize;
	short	imode;
	short	iwt;
	short	ifnt;
	short	iclr;
//	char	*pdata;			// PrmWkinfo�p
	int 	ioffset;		// �v���~�e�B�u�̈�擪�����OFFSET
} PrmInfo;
	
typedef struct  SegInfo {	// �Z�O�����g�Ǘ�
	int 	ivsno;
	int 	isegno;			// ���[�U���ʔԍ�
	int 	isysno;			// �V�X�e�����ʔԍ�
	int 	itype;
	int 	iclass;
	int 	ivisi;
	int 	idisp;
	int 	ipcount;
	int 	idel;
//	struct PrmInfo pprm[255];
	struct PrmInfo pprm[511];
} SegInfo;

typedef struct  VsInfo {	// VS�Ǘ�
	char	vsname[8+1];	// VS��
	int 	vsno;			// VS�ԍ�
	int 	iclass;			// �A�N�e�B�u�N���X
	int 	iseg;			// �A�N�e�B�u�Z�O�����g
	int 	iScount;		// �Z�O�����g��
	char*	pSeg;			// �Z�O�����g�f�[�^�̈�|�C���^
	int 	iSmax;			// �Z�O�����g�f�[�^�̈�T�C�Y
	int 	iSuse;			// �Z�O�����g�f�[�^�̈旘�p�T�C�Y
	char*	pPrm;			// �v���~�e�B�u�f�[�^�̈�|�C���^
	int 	iPmax;			// �v���~�e�B�u�f�[�^�̈�T�C�Y
	int 	iPuse;			// �v���~�e�B�u�f�[�^�̈旘�p�T�C�Y
	int 	iGcount;		// �O���[�v��
	char*	pGrp;			// �O���[�v�f�[�^�̈�|�C���^
	int 	iGmax;			// �O���[�v�f�[�^�̈�T�C�Y
	int 	iGuse;			// �O���[�v�f�[�^�̈旘�p�T�C�Y
} VsInfo;

typedef struct GroupInfo {
	int 	ivsno;
	char	grpname[24+1];	// �O���[�v�E�������i��
	int 	isegno;			// ���[�U���ʔԍ�
	int 	isysno;			// �V�X�e�����ʔԍ�
	int 	ientcnt;		// �v�f��
	int 	igent[512];		// �v�f�̎��ʔԍ�
	int		idel;
} GroupInfo;

typedef  struct  GraphicAttribute {	// �O���t�B�b�N����
	int 	atrtbl[4];
} GraphicAttribute;

typedef  struct  TextAttribute {	// �e�L�X�g����
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



//�v���~�e�B�u

typedef  struct  P_point {	// �_
	double	x;
	double	y;
	short	mtype;
} P_point;

typedef  struct  P_line {	// ����
	double	x;	// �n�_
	double	y;
	double	vx;	// �����x�N�g��
	double	vy;
	double	l;	// ����
} P_line;

typedef  struct  Vect {	// �x�N�g��
	double	x;
	double	y;
} Vect;

typedef  struct  P_pline {	// �܂��
	double	x;	// �n�_
	double	y;
	struct Vect vect[254];	// 2�_�ڈȍ~�ւ̎n�_����̃x�N�g��
} P_pline;


typedef  struct  Vlen {
	double	px;	// �J�n�_�ւ̕����x�N�g��
	double	py;
	double	l;	// ���̒���
} Vlen;

typedef  struct  P_hacching {
	double	x;	// �n�_
	double	y;
	double	vx;	// �����x�N�g��
	double	vy;
	struct  Vlen hline[168];	// �\�������
} P_hacching;

typedef  struct  P_rect {	// ��`
	double	x;	// �n�_
	double	y;
	double	vx;	// �����x�N�g��
	double	vy;
	double	l;	// ���̒���
	double	m;	// �c�̒���
} P_rect;


typedef  struct  P_text {
	double	x;	// �n�_
	double	y;
	float	h;
	float	w;
	float	d;
	float	ang_t;	// �����X��
	float	ang_s;	// ������X��
	int 	idmy1;
	char	flg[4];	// [0]:�����^�C�v
	int 	m_su;	// ������
	char	mtext[1024];	// ������
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
