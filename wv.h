#ifndef MSWORDVIEW_HEADER
#define MSWORDVIEW_HEADER
#ifdef __cplusplus
extern "C" {
#endif

/* redefs of things that are either in glibc or we have to imclude them ourselves*/
int strcasecmp(const char *s1, const char *s2);
int getopt(int argc, char * const argv[], const char *optstring);
/* end redefs */

#include <time.h>

#ifndef PATH_MAX
#define PATH_MAX 255 /*seems a reasonable figure*/
#endif

#ifndef U32
#define U32 unsigned int
#endif

#ifndef S32
#define S32 int
#endif

#ifndef U16
#define U16 unsigned short
#endif

#ifndef S16
#define S16 short
#endif

#ifndef U8
#define U8 unsigned char
#endif

#ifndef S8
#define S8 char
#endif


#define DEFAULTINDENT 1800
#define TWIRPS_PER_BQ 1440
#define TWIRPS_PER_H_PIXEL 20
#define TWIRPS_PER_V_PIXEL 20

#define SPACEPIXELS 6

#ifndef isletter
#define isletter(c) (((c) >= 'A' && (c) <= 'Z') || ((c) >= 'a' && (c) <= 'z'))
#endif

#ifndef digit
#define digit(c)  ((c) >= '0' && (c) <= '9')
#endif

#define legal_variable_char(c)  (isletter (c) || digit (c) || c == '_')

#ifndef HAVE_WMF
typedef struct tagRECT
    {
    S32 left;
    S32 right;
    S32 top;
    S32 bottom;
    }RECT;

typedef struct tagPOINT
    {
    S32 x;
    S32 y;
    }POINT;
#else
#	include <wmfapi.h>
#endif



/*Wine Portions Begin*/

typedef struct tagPANOSE
	{
    U8 bFamilyType;
    U8 bSerifStyle;
    U8 bWeight;
    U8 bProportion;
    U8 bContrast;
    U8 bStrokeVariation;
    U8 bArmStyle;
    U8 bLetterform;
    U8 bMidline;
    U8 bXHeight;
	} PANOSE;

void wvGetPANOSE(PANOSE *panose,FILE *fd);

/*
 * The FONTSIGNATURE tells which Unicode ranges and which code pages
 * have glyphs in a font.
 *
 * fsUsb  128-bit bitmap. The most significant bits are 10 (magic number).
 *        The remaining 126 bits map the Unicode ISO 10646 subranges
 *        for which the font provides glyphs.
 *
 * fsCsb  64-bit bitmap. The low 32 bits map the Windows codepages for
 *        which the font provides glyphs. The high 32 bits are for
 *        non Windows codepages.
 */
typedef struct
	{
	U32 fsUsb[4];
	U32 fsCsb[2];
	} FONTSIGNATURE;

void wvGetFONTSIGNATURE(FONTSIGNATURE *fs,FILE *fd);

#ifndef _FILETIME_
#define _FILETIME_
/* 64 bit number of 100 nanoseconds intervals since January 1, 1601 */
typedef struct
	{
	U32  dwLowDateTime;
	U32  dwHighDateTime;
	} FILETIME;
#endif /* _FILETIME_ */

void wvGetFILETIME(FILETIME *ft,FILE *fd);
void wvInitFILETIME(FILETIME *ft);

time_t wvDOSFS_FileTimeToUnixTime( const FILETIME *filetime, U32 *remainder );
int wvFileTimeToDosDateTime(const FILETIME *ft, U16 *fatdate, U16 *fattime );
/*Wine Portions End*/

/** beginning of clean interface **/
void wvRealError(char *file, int line,char *fmt, ...);
#define wvError(fmt, args...) wvRealError(__FILE__,__LINE__,fmt, ## args)
void wvWarning(char *fmt, ...);
void wvFree(void *ptr);

char *wvWideStrToMB(U16 *str);
char *wvWideCharToMB(U16 char16);



typedef struct _FIB
	{
	U16 wIdent ;				/* 0x0000 */
	U16 nFib ;				/* 0x0002 */
	U16 nProduct ;				/* 0x0004 */
	U16 lid ;				/* 0x0006 */
	S16 pnNext ;				/* 0x0008 */

	U32 fDot:1 ;				/* Bitfield 0x0001 0x000A */
	U32 fGlsy:1 ;			/* Bitfield 0x0002 */
	U32 fComplex:1 ;			/* Bitfield 0x0004 */
	U32 fHasPic:1 ;			/* Bitfield 0x0008 */
	U32 cQuickSaves:4 ;			/* Bitfield 0x00F0 */
	U32 fEncrypted:1 ;			/* Bitfield 0x0100 */
	U32 fWhichTblStm:1 ;			/* Bitfield 0x0200 */
	U32 fReadOnlyRecommended:1 ;			/* Bitfield 0x0400 */
	U32 fWriteReservation:1 ;			/* Bitfield 0x0800 */
	U32 fExtChar:1 ;			/* Bitfield 0x1000 */
	U32 fLoadOverride:1 ;			/* Bitfield 0x2000 */
	U32 fFarEast:1 ;			/* Bitfield 0x4000 */
	U32 fCrypto:1 ;			/* Bitfield 0x8000 */
	U32 nFibBack:16 ;				/* 0x000C */
	U32 lKey ;				/* 0x000E */
	U32 envr:8 ;				/* 0x0012 */
	U32 fMac:1 ;				/* Bitfield 0x01 0x0013 */
	U32 fEmptySpecial:1 ;			/* Bitfield 0x02 */
	U32 fLoadOverridePage:1 ;			/* Bitfield 0x04 */
	U32 fFutureSavedUndo:1 ;			/* Bitfield 0x08 */
	U32 fWord97Saved:1 ;			/* Bitfield 0x10 */
	U32 fSpare0:3 ;			/* Bitfield 0xFE */
	U32 chse:16 ;				/* 0x0014 */	/*was chs*/
	U16 chsTables ;				/* 0x0016 */
	S32 fcMin ;				/* 0x0018 */
	S32 fcMac ;				/* 0x001C */
	U16 csw ;				/* 0x0020 */
	U16 wMagicCreated ;				/* 0x0022 */
	U16 wMagicRevised ;				/* 0x0024 */
	U16 wMagicCreatedPrivate ;				/* 0x0026 */
	U16 wMagicRevisedPrivate ;				/* 0x0028 */
	S16 pnFbpChpFirst_W6 ;				/* 0x002A */
	S16 pnChpFirst_W6 ;				/* 0x002C */
	S16 cpnBteChp_W6 ;				/* 0x002E */
	S16 pnFbpPapFirst_W6 ;				/* 0x0030 */
	S16 pnPapFirst_W6 ;				/* 0x0032 */
	S16 cpnBtePap_W6 ;				/* 0x0034 */
	S16 pnFbpLvcFirst_W6 ;				/* 0x0036 */
	S16 pnLvcFirst_W6 ;				/* 0x0038 */
	S16 cpnBteLvc_W6 ;				/* 0x003A */
	S16 lidFE ;				/* 0x003C */
	U16 clw ;				/* 0x003E */
	S32 cbMac ;				/* 0x0040 */
	U32 lProductCreated ;				/* 0x0044 */
	U32 lProductRevised ;				/* 0x0048 */
	S32 ccpText ;				/* 0x004C */
	S32 ccpFtn ;				/* 0x0050 */
	S32 ccpHdd ;				/* 0x0054 */
	S32 ccpMcr ;				/* 0x0058 */
	S32 ccpAtn ;				/* 0x005C */
	S32 ccpEdn ;				/* 0x0060 */
	S32 ccpTxbx ;				/* 0x0064 */
	S32 ccpHdrTxbx ;				/* 0x0068 */
	S32 pnFbpChpFirst ;				/* 0x006C */
	S32 pnChpFirst ;				/* 0x0070 */
	S32 cpnBteChp ;				/* 0x0074 */
	S32 pnFbpPapFirst ;				/* 0x0078 */
	S32 pnPapFirst ;				/* 0x007C */
	S32 cpnBtePap ;				/* 0x0080 */
	S32 pnFbpLvcFirst ;				/* 0x0084 */
	S32 pnLvcFirst ;				/* 0x0088 */
	S32 cpnBteLvc ;				/* 0x008C */
	S32 fcIslandFirst ;				/* 0x0090 */
	S32 fcIslandLim ;				/* 0x0094 */
	U16 cfclcb ;				/* 0x0098 */
	S32 fcStshfOrig ;				/* 0x009A */
	U32 lcbStshfOrig ;				/* 0x009E */
	S32 fcStshf ;				/* 0x00A2 */
	U32 lcbStshf ;				/* 0x00A6 */
	S32 fcPlcffndRef ;				/* 0x00AA */
	U32 lcbPlcffndRef ;				/* 0x00AE */
	S32 fcPlcffndTxt ;				/* 0x00B2 */
	U32 lcbPlcffndTxt ;				/* 0x00B6 */
	S32 fcPlcfandRef ;				/* 0x00BA */
	U32 lcbPlcfandRef ;				/* 0x00BE */
	S32 fcPlcfandTxt ;				/* 0x00C2 */
	U32 lcbPlcfandTxt ;				/* 0x00C6 */
	S32 fcPlcfsed ;				/* 0x00CA */
	U32 lcbPlcfsed ;				/* 0x00CE */
	S32 fcPlcpad ;				/* 0x00D2 */
	U32 lcbPlcpad ;				/* 0x00D6 */
	S32 fcPlcfphe ;				/* 0x00DA */
	U32 lcbPlcfphe ;				/* 0x00DE */
	S32 fcSttbfglsy ;				/* 0x00E2 */
	U32 lcbSttbfglsy ;				/* 0x00E6 */
	S32 fcPlcfglsy ;				/* 0x00EA */
	U32 lcbPlcfglsy ;				/* 0x00EE */
	S32 fcPlcfhdd ;				/* 0x00F2 */
	U32 lcbPlcfhdd ;				/* 0x00F6 */
	S32 fcPlcfbteChpx ;				/* 0x00FA */
	U32 lcbPlcfbteChpx ;				/* 0x00FE */
	S32 fcPlcfbtePapx ;				/* 0x0102 */
	U32 lcbPlcfbtePapx ;				/* 0x0106 */
	S32 fcPlcfsea ;				/* 0x010A */
	U32 lcbPlcfsea ;				/* 0x010E */
	S32 fcSttbfffn ;				/* 0x0112 */
	U32 lcbSttbfffn ;				/* 0x0116 */
	S32 fcPlcffldMom ;				/* 0x011A */
	U32 lcbPlcffldMom ;				/* 0x011E */
	S32 fcPlcffldHdr ;				/* 0x0122 */
	U32 lcbPlcffldHdr ;				/* 0x0126 */
	S32 fcPlcffldFtn ;				/* 0x012A */
	U32 lcbPlcffldFtn ;				/* 0x012E */
	S32 fcPlcffldAtn ;				/* 0x0132 */
	U32 lcbPlcffldAtn ;				/* 0x0136 */
	S32 fcPlcffldMcr ;				/* 0x013A */
	U32 lcbPlcffldMcr ;				/* 0x013E */
	S32 fcSttbfbkmk ;				/* 0x0142 */
	U32 lcbSttbfbkmk ;				/* 0x0146 */
	S32 fcPlcfbkf ;				/* 0x014A */
	U32 lcbPlcfbkf ;				/* 0x014E */
	S32 fcPlcfbkl ;				/* 0x0152 */
	U32 lcbPlcfbkl ;				/* 0x0156 */
	S32 fcCmds ;				/* 0x015A */
	U32 lcbCmds ;				/* 0x015E */
	S32 fcPlcmcr ;				/* 0x0162 */
	U32 lcbPlcmcr ;				/* 0x0166 */
	S32 fcSttbfmcr ;				/* 0x016A */
	U32 lcbSttbfmcr ;				/* 0x016E */
	S32 fcPrDrvr ;				/* 0x0172 */
	U32 lcbPrDrvr ;				/* 0x0176 */
	S32 fcPrEnvPort ;				/* 0x017A */
	U32 lcbPrEnvPort ;				/* 0x017E */
	S32 fcPrEnvLand ;				/* 0x0182 */
	U32 lcbPrEnvLand ;				/* 0x0186 */
	S32 fcWss ;				/* 0x018A */
	U32 lcbWss ;				/* 0x018E */
	S32 fcDop ;				/* 0x0192 */
	U32 lcbDop ;				/* 0x0196 */
	S32 fcSttbfAssoc ;				/* 0x019A */
	U32 lcbSttbfAssoc ;				/* 0x019E */
	S32 fcClx ;				/* 0x01A2 */
	U32 lcbClx ;				/* 0x01A6 */
	S32 fcPlcfpgdFtn ;				/* 0x01AA */
	U32 lcbPlcfpgdFtn ;				/* 0x01AE */
	S32 fcAutosaveSource ;				/* 0x01B2 */
	U32 lcbAutosaveSource ;				/* 0x01B6 */
	S32 fcGrpXstAtnOwners ;				/* 0x01BA */
	U32 lcbGrpXstAtnOwners ;				/* 0x01BE */
	S32 fcSttbfAtnbkmk ;				/* 0x01C2 */
	U32 lcbSttbfAtnbkmk ;				/* 0x01C6 */
	S32 fcPlcdoaMom ;				/* 0x01CA */
	U32 lcbPlcdoaMom ;				/* 0x01CE */
	S32 fcPlcdoaHdr ;				/* 0x01D2 */
	U32 lcbPlcdoaHdr ;				/* 0x01D6 */
	S32 fcPlcspaMom ;				/* 0x01DA */
	U32 lcbPlcspaMom ;				/* 0x01DE */
	S32 fcPlcspaHdr ;				/* 0x01E2 */
	U32 lcbPlcspaHdr ;				/* 0x01E6 */
	S32 fcPlcfAtnbkf ;				/* 0x01EA */
	U32 lcbPlcfAtnbkf ;				/* 0x01EE */
	S32 fcPlcfAtnbkl ;				/* 0x01F2 */
	U32 lcbPlcfAtnbkl ;				/* 0x01F6 */
	S32 fcPms ;				/* 0x01FA */
	U32 lcbPms ;				/* 0x01FE */
	S32 fcFormFldSttbs ;				/* 0x0202 */
	U32 lcbFormFldSttbs ;				/* 0x0206 */
	S32 fcPlcfendRef ;				/* 0x020A */
	U32 lcbPlcfendRef ;				/* 0x020E */
	S32 fcPlcfendTxt ;				/* 0x0212 */
	U32 lcbPlcfendTxt ;				/* 0x0216 */
	S32 fcPlcffldEdn ;				/* 0x021A */
	U32 lcbPlcffldEdn ;				/* 0x021E */
	S32 fcPlcfpgdEdn ;				/* 0x0222 */
	U32 lcbPlcfpgdEdn ;				/* 0x0226 */
	S32 fcDggInfo ;				/* 0x022A */
	U32 lcbDggInfo ;				/* 0x022E */
	S32 fcSttbfRMark ;				/* 0x0232 */
	U32 lcbSttbfRMark ;				/* 0x0236 */
	S32 fcSttbCaption ;				/* 0x023A */
	U32 lcbSttbCaption ;				/* 0x023E */
	S32 fcSttbAutoCaption ;				/* 0x0242 */
	U32 lcbSttbAutoCaption ;				/* 0x0246 */
	S32 fcPlcfwkb ;				/* 0x024A */
	U32 lcbPlcfwkb ;				/* 0x024E */
	S32 fcPlcfspl ;				/* 0x0252 */
	U32 lcbPlcfspl ;				/* 0x0256 */
	S32 fcPlcftxbxTxt ;				/* 0x025A */
	U32 lcbPlcftxbxTxt ;				/* 0x025E */
	S32 fcPlcffldTxbx ;				/* 0x0262 */
	U32 lcbPlcffldTxbx ;				/* 0x0266 */
	S32 fcPlcfhdrtxbxTxt ;				/* 0x026A */
	U32 lcbPlcfhdrtxbxTxt ;				/* 0x026E */
	S32 fcPlcffldHdrTxbx ;				/* 0x0272 */
	U32 lcbPlcffldHdrTxbx ;				/* 0x0276 */
	S32 fcStwUser ;				/* 0x027A */
	U32 lcbStwUser ;				/* 0x027E */
	S32 fcSttbttmbd ;				/* 0x0282 */
	U32 cbSttbttmbd ;				/* 0x0286 */
	S32 fcUnused ;				/* 0x028A */
	U32 lcbUnused ;				/* 0x028E */
	S32 fcPgdMother ;				/* 0x0292 */
	U32 lcbPgdMother ;				/* 0x0296 */
	S32 fcBkdMother ;				/* 0x029A */
	U32 lcbBkdMother ;				/* 0x029E */
	S32 fcPgdFtn ;				/* 0x02A2 */
	U32 lcbPgdFtn ;				/* 0x02A6 */
	S32 fcBkdFtn ;				/* 0x02AA */
	U32 lcbBkdFtn ;				/* 0x02AE */
	S32 fcPgdEdn ;				/* 0x02B2 */
	U32 lcbPgdEdn ;				/* 0x02B6 */
	S32 fcBkdEdn ;				/* 0x02BA */
	U32 lcbBkdEdn ;				/* 0x02BE */
	S32 fcSttbfIntlFld ;				/* 0x02C2 */
	U32 lcbSttbfIntlFld ;				/* 0x02C6 */
	S32 fcRouteSlip ;				/* 0x02CA */
	U32 lcbRouteSlip ;				/* 0x02CE */
	S32 fcSttbSavedBy ;				/* 0x02D2 */
	U32 lcbSttbSavedBy ;				/* 0x02D6 */
	S32 fcSttbFnm ;				/* 0x02DA */
	U32 lcbSttbFnm ;				/* 0x02DE */
	S32 fcPlcfLst ;				/* 0x02E2 */
	U32 lcbPlcfLst ;				/* 0x02E6 */
	S32 fcPlfLfo ;				/* 0x02EA */
	U32 lcbPlfLfo ;				/* 0x02EE */
	S32 fcPlcftxbxBkd ;				/* 0x02F2 */
	U32 lcbPlcftxbxBkd ;				/* 0x02F6 */
	S32 fcPlcftxbxHdrBkd ;				/* 0x02FA */
	U32 lcbPlcftxbxHdrBkd ;				/* 0x02FE */
	S32 fcDocUndo ;				/* 0x0302 */
	U32 lcbDocUndo ;				/* 0x0306 */
	S32 fcRgbuse ;				/* 0x030A */
	U32 lcbRgbuse ;				/* 0x030E */
	S32 fcUsp ;				/* 0x0312 */
	U32 lcbUsp ;				/* 0x0316 */
	S32 fcUskf ;				/* 0x031A */
	U32 lcbUskf ;				/* 0x031E */
	S32 fcPlcupcRgbuse ;				/* 0x0322 */
	U32 lcbPlcupcRgbuse ;				/* 0x0326 */
	S32 fcPlcupcUsp ;				/* 0x032A */
	U32 lcbPlcupcUsp ;				/* 0x032E */
	S32 fcSttbGlsyStyle ;				/* 0x0332 */
	U32 lcbSttbGlsyStyle ;				/* 0x0336 */
	S32 fcPlgosl ;				/* 0x033A */
	U32 lcbPlgosl ;				/* 0x033E */
	S32 fcPlcocx ;				/* 0x0342 */
	U32 lcbPlcocx ;				/* 0x0346 */
	S32 fcPlcfbteLvc ;				/* 0x034A */
	U32 lcbPlcfbteLvc ;				/* 0x034E */
	FILETIME ftModified ;				/* 0x0352 */
	S32 fcPlcflvc ;				/* 0x035A */
	U32 lcbPlcflvc ;				/* 0x035E */
	S32 fcPlcasumy ;				/* 0x0362 */
	U32 lcbPlcasumy ;				/* 0x0366 */
	S32 fcPlcfgram ;				/* 0x036A */
	U32 lcbPlcfgram ;				/* 0x036E */
	S32 fcSttbListNames ;				/* 0x0372 */
	U32 lcbSttbListNames ;				/* 0x0376 */
	S32 fcSttbfUssr ;				/* 0x037A */
	U32 lcbSttbfUssr ;				/* 0x037E */
	} FIB;

void wvGetFIB(FIB *item,FILE *fd);
void wvGetFIB6(FIB *item,FILE *fd);
void wvInitFIB(FIB *item);


int wvGetEmpty_PLCF(U32 **cp,U32 *nocps,U32 offset,U32 len,FILE *fd);

int wvDecrypt(FILE *mainfd,char *,U32 lKey);

typedef struct _FRD
	{
	S16 frd;
	} FRD;

void wvGetFRD(FRD *item,FILE *fd);
int wvGetFRD_PLCF(FRD **frd,U32 **pos,U32 *nofrd,U32 offset,U32 len,FILE *fd);

typedef U16 XCHAR;

typedef struct _ATRD
    {
    XCHAR xstUsrInitl[10];
    S16 ibst;
    U16 ak;			/*unused*/
    U16 grfbmc;		/*unused*/
    S32 lTagBkmk;
    } ATRD;

void wvGetATRD(ATRD *item,FILE *fd);
int wvGetATRD_PLCF(ATRD **atrd,U32 **pos,U32 *noatrd,U32 offset,U32 len,FILE *fd);

typedef struct _SED
    {
    S16 fn;     
    U32 fcSepx;
    S16 fnMpr;  
    U32 fcMpr;
    } SED;

void wvGetSED(SED *item,FILE *fd);
int wvGetSED_PLCF(SED **item,U32 **pos,U32 *noitem,U32 offset,U32 len,FILE *fd);

typedef struct _FFN
    {
    U32 cbFfnM1:8;
    U32 prq:2;
    U32 fTrueType:1;
    U32 reserved1:1;
    U32 ff:3;
    U32 reserved2:1;
    S32 wWeight:16;

    U8 chs;
    U8 ixchSzAlt;
    PANOSE panose;
    FONTSIGNATURE fs;
    XCHAR xszFfn[65];   /*max size*/
    } FFN;

void wvGetFFN(FFN *item,FILE *fd);

typedef struct _FFN_STTBF
    {
    U16 extendedflag;
    U16 nostrings;
    U16 extradatalen;
    FFN *ffn;
    } FFN_STTBF;

void wvGetFFN_STTBF(FFN_STTBF *item,U32 offset,U32 len,FILE *fd);
void wvReleaseFFN_STTBF(FFN_STTBF *item);
char *wvGetFontnameFromCode(FFN_STTBF *item,int fontcode);


typedef struct _STTBF
	{
	U16 extendedflag;
	U16 nostrings;
	U16 extradatalen;
	S8 **s8strings;
	U16 **u16strings;
	U8 **extradata;
	} STTBF;

void wvGetSTTBF(STTBF *anS,U32 offset,U32 len,FILE *fd);
void wvGetSTTBF6(STTBF *anS,U32 offset,U32 len,FILE *fd);
void wvListSTTBF(STTBF *item);
void wvReleaseSTTBF(STTBF *item);
char *wvGetTitle(STTBF *item);

typedef enum
    {
    ibstAssocFileNext = 0,
    ibstAssocDot = 1,
    ibstAssocTitle = 2,
    ibstAssocSubject = 3,
    ibstAssocKeyWords = 4,
    ibstAssocComments = 5,
    ibstAssocAuthor = 6,
    ibstAssocLastRevBy = 7,
    ibstAssocDataDoc = 8,
    ibstAssocHeaderDoc = 9,
    ibstAssocCriteria1 = 10,
    ibstAssocCriteria2 = 11,
    ibstAssocCriteria3 = 12,
    ibstAssocCriteria4 = 13,
    ibstAssocCriteria5 = 14,
    ibstAssocCriteria6 = 15,
    ibstAssocCriteria7 = 16,
    ibstAssocMax = 17,
    ibstAssocMaxWord6 = 17 		/* just in case */
    } ibst;


typedef struct _wv_var1
    {
	/* 16 bits for bitfields */
    U32 ch:5;
    U32 reserved:3;
    U32 flt:8;
    } wv_var1;

typedef struct _wv_var2
    {
	/* 16 bits for bitfields */
    U32 ch:5;
    U32 reserved:3;
    U32 fDiffer:1;
    U32 fZombieEmbed:1;
    U32 fResultDirty:1;
    U32 fResultEdited:1;
    U32 fLocked:1;
    U32 fPrivateResult:1;
    U32 fNested:1;
    U32 fHasSep:1;
    } wv_var2;



typedef union _FLD
    {
    wv_var1 var1;
    wv_var2 var2;
    } FLD;

void wvGetFLD(FLD *item,FILE *fd);
int wvGetFLD_PLCF(FLD **fld,U32 **pos,U32 *nofld,U32 offset,U32 len,FILE *fd);

typedef struct _COPTS
	{
	/* 16 bits for bitfields */
	U32 fNoTabForInd1:1;
	U32 fNoSpaceRaiseLower:1;
	U32 fSuppressSpbfAfterPageBreak:1;
	U32 fWrapTrailSpaces:1;
	U32 fMapPrintTextColor:1;
	U32 fNoColumnBalance:1;
	U32 fConvMailMergeEsc:1;
	U32 fSupressTopSpacing:1;
	U32 fOrigWordTableRules:1;
	U32 fTransparentMetafiles:1;
	U32 fShowBreaksInFrames:1;
	U32 fSwapBordersFacingPgs:1;
	U32 reserved:4;
	} COPTS;

void wvGetCOPTS(COPTS *copts,FILE *fd);

typedef struct _DTTM
	{
	U32 mint:6;
	U32 hr:5;
	U32 dom:5;
	U32 mon:4;
	U32 yr:9;
	U32 wdy:3;
	} DTTM;

void wvGetDTTM(DTTM *item,FILE *fd);
void wvGetDTTMFromBucket(DTTM *item,U8 *pointer);
void wvCreateDTTM(DTTM *dttm,U16 one,U16 two);
void wvCopyDTTM(DTTM *dest,DTTM *src);
void wvInitDTTM(DTTM *dttm);

typedef struct _DOPTYPOGRAPHY
	{
	U32 fKerningPunct:1;
	U32 iJustification:2;
	U32 iLevelOfKinsoku:2;
	U32 f2on1:1;
	U32 reserved:10;
	U32 cchFollowingPunct:16;

	U16 cchLeadingPunct;
	U16 rgxchFPunct[101];
	U16 rgxchLPunct[51];
	} DOPTYPOGRAPHY;

void wvGetDOPTYPOGRAPHY(DOPTYPOGRAPHY *dopt,FILE *fd);


typedef struct _DOGRID
	{
	U16 xaGrid;
	U16 yaGrid;
	U16 dxaGrid;
	U32 dyaGrid:16;
	U32 dyGridDisplay:7;
	U32 fTurnItOff:1;
	U32 dxGridDisplay:7;
	U32 fFollowMargins:1;
	} DOGRID;

void wvGetDOGRID(DOGRID *dogrid,FILE *fd);

typedef struct _ASUMYI
	{
	U32 fValid:1;
	U32 fView:1;
	U32 iViewBy:2;
	U32 fUpdateProps:1;
	U32 reserved:11;
	U32 wDlgLevel:16;

	U32 lHighestLevel;
	U32 lCurrentLevel;
	} ASUMYI;

void wvGetASUMYI(ASUMYI *asumyi,FILE *fd);

typedef struct _DOP
	{
	U32 fFacingPages:1;	
	U32 fWidowControl:1;	
	U32 fPMHMainDoc:1;	
	U32 grfSuppression:2;	
	U32 fpc:2;			/*where footnotes are put*/	
	U32 reserved1:1;
	U32 grpfIhdt:8;
	U32 rncFtn:2;	/*how to restart footnotes*/
	U32	nFtn:14;	/*first footnote no*/

	U32 fOutlineDirtySave:1;
	U32 reserved2:7;
	U32 fOnlyMacPics:1;
	U32 fOnlyWinPics:1;
	U32 fLabelDoc:1;
	U32 fHyphCapitals:1;
	U32 fAutoHyphen:1;
	U32 fFormNoFields:1;
	U32 fLinkStyles:1;
	U32 fRevMarking:1;
	U32 fBackup:1;
	U32 fExactCWords:1;
	U32 fPagHidden:1;
	U32 fPagResults:1;
	U32 fLockAtn:1;
	U32 fMirrorMargins:1;
	U32 reserved3:1;
	U32 fDfltTrueType:1;
	U32 fPagSuppressTopSpacing:1;
	U32 fProtEnabled:1;
	U32 fDispFormFldSel:1;
	U32 fRMView:1;
	U32 fRMPrint:1;
	U32 reserved4:1;
	U32 fLockRev:1;
	U32 fEmbedFonts:1;

	COPTS copts;

	U16 dxaTab;
	U16 wSpare;
	U16 dxaHotZ;
	U16 cConsecHypLim;
	U16 wSpare2;

	DTTM dttmCreated;
	DTTM dttmRevised;
	DTTM dttmLastPrint;

	U16 nRevision;
	U32 tmEdited;
	U32 cWords;
	U32 cCh;
	U16 cPg;
	U32 cParas;

	U32 rncEdn:2;		/*how endnotes are restarted*/
	U32 nEdn:14;		/*beginning endnote no*/
	U32 epc:2;		/*where endnotes go*/
	U32 nfcFtnRef:4; /*number format code for auto footnotes, i think use the new_* instead*/
	U32 nfcEdnRef:4; /*number format code for auto endnotes, i thing use the new_* instead*/
	U32 fPrintFormData:1;
	U32 fSaveFormData:1;
	U32 fShadeFormData:1;
	U32 reserved6:2;
	U32 fWCFtnEdn:1;

	U32 cLines;
	U32 cWordsFtnEnd;
	U32 cChFtnEdn;
	U16 cPgFtnEdn;
	U32 cParasFtnEdn;
	U32 cLinesFtnEdn;
	U32 lKeyProtDoc;	/*password protection key (! ?)*/

	U32 wvkSaved:3;
	U32 wScaleSaved:9;
	U32 zkSaved:2;
	U32 fRotateFontW6:1;
	U32 iGutterPos:1;
	U32 fNoTabForInd:1;
	U32 fNoSpaceRaiseLower:1;
	U32 fSupressSpbfAfterPageBreak:1;
	U32 fWrapTrailSpaces:1;
	U32 fMapPrintTextColor:1;
	U32 fNoColumnBalance:1;
	U32 fConvMailMergeEsc:1;
	U32 fSupressTopSpacing:1;
	U32 fOrigWordTableRules:1;
	U32 fTransparentMetafiles:1;
	U32 fShowBreaksInFrames:1;
	U32 fSwapBordersFacingPgs:1;
	U32 reserved7:4;

	U32 fSuppressTopSpacingMac5:1;
	U32 fTruncDxaExpand:1;
	U32 fPrintBodyBeforeHdr:1;
	U32 fNoLeading:1;
	U32 reserved8:1;
	U32 fMWSmallCaps:1;
	U32 reserved9:10;
	U32 adt:16;

	DOPTYPOGRAPHY doptypography;
	DOGRID dogrid;
	
	U32 reserver11:1;
	U32 lvl:4;
	U32 fGramAllDone:1;
	U32 fGramAllClean:1;
	U32 fSubsetFonts:1;
	U32 fHideLastVersion:1;
	U32 fHtmlDoc:1;
	U32 reserved10:1;
	U32 fSnapBorder:1;
	U32 fIncludeHeader:1;
	U32 fIncludeFooter:1;
	U32 fForcePageSizePag:1;
	U32 fMinFontSizePag:1;
	U32 fHaveVersions:1;
	U32 fAutoVersion:1;
	U32 reserved11:14;

	ASUMYI asumyi;

	U32 cChWS;
	U32 cChWSFtnEdn;
	U32 grfDocEvents;
	U32 fVirusPrompted:1;
	U32 fVirusLoadSafe:1;
	U32 KeyVirusSession30:30;

	U8 Spare[30];
	U32 reserved12;
	U32 reserved13;

	U32 cDBC;
	U32 cDBCFtnEdn;
	U32 reserved14;
	U16 new_nfcFtnRef; /*number format code for auto footnote references*/
	U16 new_nfcEdnRef; /*number format code for auto endnote references*/
	U16 hpsZoonFontPag;
	U16 dywDispPag;
	} DOP;

void wvGetDOP(DOP *dop,U32 fcDop,U32 lcbDop,FILE *tablefd);

typedef struct _BKF
    {
    S32 ibkl:16;
    U32 itcFirst:7;  
    U32 fPub:1;  
    U32 itcLim:7;  
    U32 fCol:1;  
    } BKF;

void wvGetBKF(BKF *item,FILE *fd);
int wvGetBKF_PLCF(BKF **bkf,U32 **pos,U32 *nobkf,U32 offset,U32 len,FILE *fd);


typedef struct _Xst
	{
	U16 *u16string;
	struct _Xst *next;
	U32 noofstrings;
	} Xst;

void wvGetXst(Xst **xst,U32 offset,U32 len,FILE *fd);
void wvFreeXst(Xst **xst);

typedef struct _FSPA
    {
    U32 spid;
    S32 xaLeft;
    S32 yaTop;
    S32 xaRight;
    S32 yaBottom;
	/* 16 bits for bitfields*/
    U32 fHdr:1;
    U32 bx:2;
    U32 by:2;
    U32 wr:4;
    U32 wrk:4;
    U32 fRcaSimple:1;
    U32 fBelowText:1;
    U32 fAnchorLock:1;
    S32 cTxbx;
    } FSPA;

void wvGetFSPA(FSPA *item,FILE *fd);
int wvGetFSPA_PLCF(FSPA **fspa,U32 **pos,U32 *nofspa,U32 offset,U32 len,FILE *fd);


typedef struct _LSTF
    {
    U32 lsid;
    U32 tplc;
    U16 rgistd[9];
	/* 16 bits for bitfields */
    U32 fSimpleList:1;
    U32 fRestartHdn:1;
    U32 reserved1:6;
    U32 reserved2:8;
    } LSTF;

void wvGetLSTF(LSTF *item,FILE *fd);
int wvGetLSTF_PLCF(LSTF **lstf,U32 **pos,U32 *nolst,U32 offset,U32 len,FILE *fd);

typedef struct _LVLF
    {
    U32 iStartAt;
	/* 16 bits for bitfield */
    U32 nfc:8;
    U32 jc:2;
    U32 fLegal:1;  
    U32 fNoRestart:1;
    U32 fPrev:1;  
    U32 fPrevSpace:1;  
    U32 fWord6:1;  
    U32 reserved1:1;
    U8 rgbxchNums[9];
    U8 ixchFollow;
    U32 dxaSpace;      
    U32 dxaIndent;     
    U8 cbGrpprlChpx;  
    U8 cbGrpprlPapx;  
    U16 reserved2;     
    }LVLF;

void wvGetLVLF(LVLF *item,FILE *fd);
void wvCopyLVLF(LVLF *dest,LVLF *src);


/*
A LVL structure contains two parts to it:

(1) an LVLF, which stores all static data such as the start-at value for the
list level, the numbering type (arabic or roman), the alignment (left, right or
centered) of the number, and several Word 6.0 compatibility options; and

(2) a set of pointers to variable length data:

(a) a grpprlChpx, which gives character formatting to the paragraph number text
itself

(b) a grpprlPapx, which gives paragraph formatting to the paragraph containing
the number, such as indenting and tab information, and

(c) the number text itself.
*/
typedef struct _LVL
    {
    LVLF lvlf;
    U8 *grpprlPapx;
    U8 *grpprlChpx;
    XCHAR *numbertext;
    } LVL;

void wvGetLVL(LVL *lvl,FILE *fd);
void wvCopyLVL(LVL *dest,LVL *src);
void wvReleaseLVL(LVL *lvl);


/*
An LST consists of two main parts:

(1) an LSTF, which is stored on disk and contains formatting properties which
apply to the entire list, such as whether the list is simple or multilevel,
the list's unique list index and template code, the istd's of the styles (if
any) that each level in the list is linked to, and a number of Word 6
compatilibity option;

(2) an array of LVL structures, which describe the appearance of each
individual level in the LST.
*/

/*
(3) I have added a list of values which i will use to determine what
number to use for each list entry, Caolan
*/

typedef struct _LST
    {
    LSTF lstf;
    LVL *lvl;
	U32 *current_no;
    }LST;

int wvGetLST(LST **lst,U16 *noofLST,U32 offset,U32 len,FILE *fd);
void wvReleaseLST(LST **lst,U16 noofLST);
LST *wvSearchLST(U32 id,LST *lst,U16 noofLST);

typedef struct _LFO
    {
    U32 lsid;
    U32 reserved1;
    U32 reserved2;
    U8 clfolvl;
    U8 reserved3[3];
    } LFO;

void wvGetLFO(LFO *item,FILE *fd);
int wvGetLFO_PLF(LFO **lfo,U32 *nolfo,U32 offset,U32 len,FILE *fd);

typedef struct _LFOLVL
    {
    U32 iStartAt;
    U32 ilvl:4;
    U32 fStartAt:1;
    U32 fFormatting:1;
    U32 reserved1:2;
    U32 reserved2:8;
    U32 reserved3:8;
    U32 reserved4:8;
    } LFOLVL;

void wvGetLFOLVL(LFOLVL *item,FILE *fd);
int wvInvalidLFOLVL(LFOLVL *item);

int wvGetLFO_records(LFO **lfo,LFOLVL **lfolvl,LVL **lvl,U32 *nolfo,U32 *nooflvl,U32 offset,U32 len,FILE *fd);
int wvReleaseLFO_records(LFO **lfo,LFOLVL **lfolvl,LVL **lvl,U32 nooflvl);

char *wvGenerateNFC(int value,int no_type);
char *wvOrdinal(U32 x);
U16 *wvListString(int ilfo,int ilvl,LST *alst);

typedef U16 LID;

typedef struct _SHD
    {
	/*16 bits in total*/
    U32 icoFore:5;
    U32 icoBack:5;
    U32 ipat:6;
    } SHD;

void wvGetSHD(SHD *item,FILE *fd);
void wvGetSHDFromBucket(SHD *item,U8 *pointer);
void wvInitSHD(SHD *item);
void wvCopySHD(SHD *dest,SHD *src);


typedef struct _DCS
    {
	/* 16 bits for bitfields */
    U32 fdct:3;
    U32 count:5;
    U32 reserved:8;
    } DCS;

void wvGetDCS(DCS *item,FILE *fd);
void wvGetDCSFromBucket(DCS *item,U8 *pointer);
void wvInitDCS(DCS *item);
void wvCopyDCS(DCS *dest,DCS *src);

typedef struct _BRC
	{
	U32 dptLineWidth:8;
	U32 brcType:8;
	U32 ico:8;
	U32 dptSpace:5;
	U32 fShadow:1;
	U32 fFrame:1;
	U32 reserved:1;
	} BRC;

void wvGetBRC(BRC *abrc,FILE *infd);
void wvGetBRCFromBucket(BRC *abrc,U8 *pointer);
void wvInitBRC(BRC *abrc);
void wvCopyBRC(BRC *dest, BRC *src);

typedef struct _BRC10
	{
	/* 16 bits in total */
	U32 dxpLine2Width:3;
	U32 dxpSpaceBetween:3;
	U32 dxpLine1Width:3;
	U32 dxpSpace:5;
	U32 fShadow:1;
	U32 fSpare:1;
	} BRC10;

void wvGetBRC10FromBucket(BRC10 *item,U8 *pointer);
void wvInitBRC10(BRC10 *item);
void wvConvertBRC10ToBRC(BRC *item,BRC10 *in);


/*
The seven types of border lines that Windows Word 1.0 supports are coded
with different sets of values for dxpLine1Width, dxpSpaceBetween, and
dxpLine2 Width.

The border lines and their brc10 settings follow:

 line type        dxpLine1Width               dxpSpaceBetween dxpLine2Width
 no border        0                           0               0

 single line      1                           0               0
 border

 two single line  1                           1               1
 border

 fat solid border 4                           0               0

 thick solid      2                           0               0
 border

 dotted border    6 (special value meaning    0               0
                  dotted line)

 hairline border  7(special value meaning     0               0
                  hairline)

When the no border settings are stored in the BRC, brc.fShadow and
brc.dxpSpace should be set to 0.
*/

typedef struct _LSPD
	{
	S16 dyaLine;
	S16 fMultLinespace;
	} LSPD;

void wvCopyLSPD(LSPD *dest,LSPD *src);
void wvInitLSPD(LSPD *item);
void wvGetLSPDFromBucket(LSPD *item, U8 *pointer);

typedef union _PHE
    {
    struct
        {
		U32 fSpare:1;
		U32 fUnk:1;
		U32 fDiffLines:1;
		U32 reserved1:5;
		U32 clMac:8;
		U32 reserved2:16;
		S32 dxaCol;
		S32 dymHeight; /*also known as dymLine and dymTableHeight in docs*/
        } var1;
    struct
        {
		U32 fSpare:1;
		U32 fUnk:1;
		U32 dcpTtpNext:30;
		S32 dxaCol;
		S32 dymHeight; /*also known as dymLine and dymTableHeight in docs*/
        } var2;
    } PHE;

void wvCopyPHE(PHE *dest,PHE *src,int which);
void wvInitPHE(PHE *item,int which);
void wvGetPHE(PHE *dest,int which,FILE *fd);
void wvGetPHE6(PHE *dest,FILE *fd);

typedef struct _NUMRM
    {
    U8 fNumRM;
    U8 Spare1;
    S16 ibstNumRM;
    DTTM dttmNumRM;
    U8 rgbxchNums[9];   
    U8 rgnfc[9];
    S16 Spare2;
    S32 PNBR[9];       
    XCHAR xst[32];  
    }NUMRM;

void wvGetNUMRM(NUMRM *item,FILE *fd);
void wvGetNUMRMFromBucket(NUMRM *item,U8 *pointer);
void wvCopyNUMRM(NUMRM *dest,NUMRM *src);
void wvInitNUMRM(NUMRM *item);

typedef struct _ANLD
    {
    U8 nfc;
    U8 cxchTextBefore;

    U32 cxchTextAfter:8;
    U32 jc:2;
    U32 fPrev:1;
    U32 fHang:1;
    U32 fSetBold:1;
    U32 fSetItalic:1;
    U32 fSetSmallCaps:1;
    U32 fSetCaps:1;
    U32 fSetStrike:1;
    U32 fSetKul:1;
    U32 fPrevSpace:1;
    U32 fBold:1;
    U32 fItalic:1;
    U32 fSmallCaps:1;
    U32 fCaps:1;
    U32 fStrike:1;
    U32 kul:3;
    U32 ico:5;

    S16 ftc;
    U16 hps;
    U16 iStartAt;
    S16 dxaIndent;
    U16 dxaSpace;
    U8 fNumber1;
    U8 fNumberAcross;
    U8 fRestartHdn;
    U8 fSpareX;
    XCHAR rgxch[32];
    } ANLD;

void wvGetANL(int version,ANLD *item,FILE *fd);
void wvGetANLD_FromBucket(int version,ANLD *item,U8 *pointer8);
void wvCopyANLD(ANLD *dest, ANLD *src);
void wvInitANLD(ANLD *item);

#define istdNormalChar 10

typedef struct _CHP
	{
	U32 fBold:1;
	U32 fItalic:1;
	U32 fRMarkDel:1;
	U32 fOutline:1;
	U32 fFldVanish:1;
	U32 fSmallCaps:1;
	U32 fCaps:1;
	U32 fVanish:1;
	U32 fRMark:1;
	U32 fSpec:1;
	U32 fStrike:1;
	U32 fObj:1;
	U32 fShadow:1;
	U32 fLowerCase:1;
	U32 fData:1;
	U32 fOle2:1;

	U32 fEmboss:1;
	U32 fImprint:1;
	U32 fDStrike:1;
	S32 fUsePgsuSettings:1;		/*?*/
	U32 reserved1:12;
	U32 reserved2;

	U16 reserved11;
	U16 ftc;
	U16 ftcAscii;
	U16 ftcFE;
	U16 ftcOther;
	U16 hps;
	S32 dxaSpace;

	U32 iss:3;
	U32 kul:4;
	U32 fSpecSymbol:1;
	U32 ico:5;
	U32 reserved3:1;
	U32 fSysVanish:1;
	U32 hpsPos:1;
	S32 super_sub:16;

	LID lid;
	LID lidDefault;
	LID lidFE;
	U8 idct;
	U8 idctHint;
	U8 wCharScale;
	S32 fcPic_fcObj_lTagObj;
	S16 ibstRMark;
	S16 ibstRMarkDel;
	DTTM dttmRMark;
	DTTM dttmRMarkDel;
	S16 reserved4;
	U16 istd;
	S16 ftcSym;
	XCHAR xchSym;
	S16 idslRMReason;
	S16 idslReasonDel;
	U8 ysr;
	U8 chYsr;
	U16 cpg;
	U16 hpsKern;

	U32 icoHighlight:5;
	U32 fHighlight:1;
	U32 kcd:3;
	U32 fNavHighlight:1;
	U32 fChsDiff:1;
	U32 fMacChs:1;
	U32 fFtcAsciSym:1;
	U32 reserved5:3;
	U32 fPropRMark:16;			/*was typo of fPropMark in documentation*/

	S16 ibstPropRMark;
	DTTM dttmPropRMark;
	U8 sfxtText;
	U8 reserved6;
	U8 reserved7;
	U16 reserved8;
	U16 reserved9;
	DTTM reserved10;
	U8 fDispFldRMark;
	S16 ibstDispFldRMark;
	DTTM dttmDispFldRMark;
	XCHAR xstDispFldRMark[16];
	SHD shd;
	BRC brc;
	} CHP;

void wvInitCHP(CHP *item);
void wvCopyCHP(CHP *dest,CHP *src);

#define itcMax 64

typedef struct _TC
    {
    S32 rgf:16;
    U32 fFirstMerged:1;
    U32 fMerged:1;
    U32 fVertical:1;
    U32 fBackward:1;
    U32 fRotateFont:1;
    U32 fVertMerge:1;
    U32 fVertRestart:1;
    U32 vertAlign:2;
    U32 fUnused:7;
    U8 wUnused;
    BRC brcTop;
    BRC brcLeft;
    BRC brcBottom;
    BRC brcRight;
    } TC;

void wvCopyTC(TC *dest,TC *src);
void wvInitTC(TC *item);

typedef struct _TLP
    {
    S32 itl:16;
    U32 fBorders:1;
    U32 fShading:1;
    U32 fFont:1;
    U32 fColor:1;
    U32 fBestFit:1;
    U32 fHdrRows:1;
    U32 fLastRow:1;
    U32 fHdrCols:1;
    U32 fLastCol:1;
	U32 unused:7;
    } TLP;

void wvCopyTLP(TLP *dest,TLP *src);
void wvInitTLP(TLP *item);


typedef struct _TAP
    {
    S16 jc;
    S32 dxaGapHalf;
    S32 dyaRowHeight;
    U8 fCantSplit;
    U8 fTableHeader;
    TLP tlp;
    S32 lwHTMLProps;

    U32 fCaFull:1;
    U32 fFirstRow:1;
    U32 fLastRow:1;
    U32 fOutline:1;
    U32 reserved:12;
    S32 itcMac:16;

    S32 dxaAdjust;
    S32 dxaScale;
    S32 dxsInch;
    S16 rgdxaCenter[itcMax+1];
    S16 rgdxaCenterPrint[itcMax+1];
    TC rgtc[itcMax];
    SHD rgshd[itcMax];
    BRC rgbrcTable[6];
    } TAP;

#define itbdMax 64

void wvCopyTAP(TAP *dest,TAP *src);
void wvInitTAP(TAP *item);

typedef struct _PAP
	{
	U16 istd ;		
	U8 jc ;		
	U8 fKeep ;	
	U8 fKeepFollow ;

	U32 fPageBreakBefore:8 ;
	U32 fBrLnAbove:1 ;	
	U32 fBrLnBelow:1 ;
	U32 fUnused:2 ;	
	U32 pcVert:2 ;
	U32 pcHorz:2 ;
	U32 brcp:8 ;
	U32 brcl:8 ;

	U8 reserved1 ;				
	U8 ilvl ;				
	U8 fNoLnn ;			
	S16 ilfo ;		
	U8 nLvlAnm ;
	U8 reserved2 ;			
	U8 fSideBySide ;	
	U8 reserved3 ;	
	U8 fNoAutoHyph ;				
	U8 fWidowControl ;			
	S32 dxaRight ;			
	S32 dxaLeft ;		
	S32 dxaLeft1 ;	
	LSPD lspd ;	
	U32 dyaBefore ;				
	U32 dyaAfter ;			
	PHE phe ;			
	U8 fCrLf ;		
	U8 fUsePgsuSettings ;			
	U8 fAdjustRight ;			
	U8 reserved4 ;			
	U8 fKinsoku ;		
	U8 fWordWrap ;	
	U8 fOverflowPunct ;			
	U8 fTopLinePunct ;		
	U8 fAutoSpaceDE ;	
	U8 fAtuoSpaceDN ;
	U16 wAlignFont ;				

	U32 fVertical:1 ;			
	U32 fBackward:1 ;		
	U32 fRotateFont:1 ;		
	U32 reserved5:13;		
	U32 reserved6:16 ;		

	S8 fInTable ;	
	S8 fTtp ;	
	U8 wr ;	
	U8 fLocked ;		
	TAP ptap ;
	S32 dxaAbs ;
	S32 dyaAbs ;			
	S32 dxaWidth ;			
	BRC brcTop ;			
	BRC brcLeft ;				
	BRC brcBottom ;			
	BRC brcRight ;		
	BRC brcBetween ;
	BRC brcBar ;
	S32 dxaFromText ;	
	S32 dyaFromText ;	
	/*16 bits for the next two entries*/
	S32 dyaHeight:15 ;	
	S32 fMinHeight:1 ;	
	SHD shd ;		
	DCS dcs ;		
	S8 lvl ;		
	S8 fNumRMIns ;	
	ANLD anld ;		
	S16 fPropRMark ;
	S16 ibstPropRMark ;				
	DTTM dttmPropRMark ;		
	NUMRM numrm ;		
	S16 itbdMac ;		
	S16 rgdxaTab[itbdMax] ;	
	S8 rgtbd[itbdMax] ;		
	} PAP;

#define istdNil 4095

void wvCopyPAP(PAP *dest,PAP *src);
void wvInitPAP(PAP *item);


typedef U16 BF;
typedef U16 FTC;

/*
  STSHI: STyleSHeet Information, as stored in a file
  Note that new fields can be added to the STSHI without invalidating
  the file format, because it is stored preceded by it's length.
  When reading a STSHI from an older version, new fields will be zero.
*/
typedef struct _STSHI
    {
    U16  cstd;                          /* Count of styles in stylesheet */
    U16  cbSTDBaseInFile;               /* Length of STD Base as stored in a file */
    U32  fStdStylenamesWritten:1;       /* Are built-in stylenames stored? */
    U32  reserved:15;                   /* Spare flags */
    U32  stiMaxWhenSaved:16;            /* Max sti known when this file was written */
    U16  istdMaxFixedWhenSaved;         /* How many fixed-index istds are there? */
    U16  nVerBuiltInNamesWhenSaved;     /* Current version of built-in stylenames */
    FTC  rgftcStandardChpStsh[3];       /* ftc used by StandardChpStsh for this document */
    } STSHI;

void wvGetSTSHI(STSHI *item,U16 cbSTSHI,FILE *fd);
void wvInitSTSHI(STSHI *item);


typedef union _UPX
    {
    struct
        {
        U8 *grpprl;
        } chpx;
    struct
        {
        U16 istd;
        U8 *grpprl;
        } papx;
    U8 *rgb;
    } UPX;

typedef struct _UPXF
    {
	U16 cbUPX;
	UPX upx;
    } UPXF;


typedef struct _CHPX
	{
	U16 istd;
	U8 cbGrpprl;
	U8 *grpprl;
	} CHPX;

void wvInitCHPX(CHPX *item);
void wvCopyCHPX(CHPX *dest,CHPX *src);
void wvReleaseCHPX(CHPX *item);


typedef union _UPD
    {
    PAP apap;
    CHP achp;
    CHPX chpx;
    } UPD;

/*
The UPE structure is the non-zero prefix of a UPD structure

For my purposes we'll call them the same, and when we get around
to writing word files, when we'll make a distinction.
*/
typedef UPD UPE;



/*
   STD: STyle Definition
   The STD contains the entire definition of a style.
   It has two parts, a fixed-length base (cbSTDBase bytes long)
   and a variable length remainder holding the name, and the upx and upe
   arrays (a upx and upe for each type stored in the style, std.cupx)
   Note that new fields can be added to the BASE of the STD without
   invalidating the file format, because the STSHI contains the length
   that is stored in the file.  When reading STDs from an older version,
   new fields will be zero.
*/
typedef struct _STD
    {
    /* Base part of STD: */
    U32 sti:12;          /* invariant style identifier */
    U32 fScratch:1;      /* spare field for any temporary use,
                            always reset back to zero! */
    U32 fInvalHeight:1;  /* PHEs of all text with this style are wrong */
    U32 fHasUpe:1;       /* UPEs have been generated */
    U32 fMassCopy:1;     /* std has been mass-copied; if unused at
                            save time, style should be deleted */
    U32 sgc:4;           /* style type code */
    U32 istdBase:12;     /* base style */

    U32 cupx:4;          /* # of UPXs (and UPEs) */
    U32 istdNext:12;     /* next style */
    U32 bchUpe:16;          /* offset to end of upx's, start of upe's */

	/* 16 bits in the following bitfields*/
    U32 fAutoRedef:1;    /* auto redefine style when appropriate */
    U32 fHidden:1;       /* hidden from UI? */
    U32 reserved:14;        /* unused bits */

    /* Variable length part of STD: */
    XCHAR    *xstzName;        /* sub-names are separated by chDelimStyle */
    UPXF *grupxf;		/*was UPX *grupx in the spec, but for my 
					     purposes its different*/

    /* the UPEs are not stored on the file; they are a cache of the based-on
       chain */
    UPE *grupe; 
    } STD;

#define sgcPara 1
#define sgcChp  2

int wvGetSTD(STD *item,U16 baselen,FILE *fd);
void wvInitSTD(STD *item);
void wvReleaseSTD(STD *item);


/*
The style sheet (STSH) is stored in the file in two parts, a STSHI and then
an array of STDs. The STSHI contains general information about the following
stylesheet, including how many styles are in it. After the STSHI, each style
is written as an STD. Both the STSHI and each STD are preceded by a U16
that indicates their length.

 Field     Size        Comment
 cbStshi   2 bytes     size of the following STSHI structure
 STSHI     (cbStshi)   Stylesheet Information
 Then for each style in the stylesheet (stshi.cstd), the following is
 stored:
 cbStd     2 bytes     size of the following STD structure
 STD       (cbStd)     the style description
*/

typedef struct _STSH
    {
    STSHI Stshi;
    STD *std;
    }STSH;

void wvGetSTSH(STSH *item,U32 offset,U32 len,FILE *fd);
void wvReleaseSTSH(STSH *item);


void wvInitPAPFromIstd(PAP *apap,U16 istdBase,STSH *stsh);
void wvAddPAPXFromBucket(PAP *apap,UPXF *upxf,STSH *stsh);

void wvInitCHPFromIstd(CHP *achp,U16 istdBase,STSH *stsh);
void wvAddCHPXFromBucket(CHP *achp,UPXF *upxf,STSH *stsh);
void wvAddCHPXFromBucket6(CHP *achp,UPXF *upxf,STSH *stsh);

void wvInitCHPXFromIstd(CHPX *chpx,U16 istdBase,STSH *stsh);
void wvMergeCHPXFromBucket(CHPX *dest,UPXF *upxf);
void wvUpdateCHPXBucket(UPXF *src);

typedef S32 ASUMY;

typedef struct _ANLV
	{
	U8 nfc;
 	U8 cxchTextBefore;

	U32 cxchTextAfter:8;
 	U32 jc:2;
	U32 fPrev:1;
	U32 fHang:1;
	U32 fSetBold:1;
	U32 fSetItalic:1;
	U32 fSetSmallCaps:1;
	U32 fSetCaps:1;
 	U32 fSetStrike:1;
	U32 fSetKul:1;
	U32 fPrevSpace:1;
	U32 fBold:1;
	U32 FItalic:1;
	U32 fSmallCaps:1;
	U32 fCaps:1;
	U32 fStrike:1;
	U32 kul:3;
	U32 ico:5;

	S16 ftc;
	U16 hps;
	U16 iStartAt;
	U16 dxaIndent;
	U16 dxaSpace;
	} ANLV;

typedef struct _OLST
	{
 	ANLV rganlv[9];
 	U8 fRestartHdr;
 	U8 fSpareOlst2;
 	U8 fSpareOlst3;
 	U8 fSpareOlst4;
 	XCHAR rgxch[32];
	} OLST;

typedef struct _SEP
	{
 	U8 bkc;
 	U8 fTitlePage;
	S8 fAutoPgn;
 	U8 nfcPgn;
 	U8 fUnlocked;
	U8 cnsPgn;
 	U8 fPgnRestart;
 	U8 fEndNote;
 	U8 lnc;
 	S8 grpfIhdt;
 	U16 nLnnMod;
 	S32 dxaLnn;
 	S16 dxaPgn;
 	S16 dyaPgn;
 	S8 fLBetween;
 	S8 vjc;
 	U16 dmBinFirst;
 	U16 dmBinOther;
 	U16 dmPaperReq;
 	BRC brcTop;
 	BRC brcLeft;
 	BRC brcBottom;
 	BRC brcRight;
 	S16 fPropRMark;
	S16 ibstPropRMark;
 	DTTM dttmPropRMark;
 	S32 dxtCharSpace;
 	S32 dyaLinePitch;
 	U16 clm;
    S16 reserved1;
 	U8 dmOrientPage;
 	U8 iHeadingPgn;
 	U16 pgnStart;
	S16 lnnMin;
 	S16 wTextFlow;
 	S16 reserved2;

 	S32 pgbProp:16;
 	U32 pgbApplyTo:3;
	U32 pgbPageDepth:2;
	U32 pgbOffsetFrom:3;
	U32 reserved:8;

 	U32 xaPage;
 	U32 yaPage;
 	U32 xaPageNUp;
 	U32 yaPageNUp;
 	U32 dxaLeft;
 	U32 dxaRight;
 	S32 dyaTop;
 	S32 dyaBottom;
 	U32 dzaGutter;
 	U32 dyaHdrTop;
 	U32 dyaHdrBottom;
 	S32 ccolM1;
 	S8 fEvenlySpaced;
 	S8 reserved3;
 	S32 dxaColumns;
 	S32 rgdxaColumnWidthSpacing[89];
 	S32 dxaColumnWidth;
 	U8 dmOrientFirst;
 	U8 fLayout;
 	S16 reserved4;
 	OLST olstAnm;
	} SEP;

void wvApplySprmFromBucket(int version,U16 sprm,PAP *apap,CHP *achp,SEP *asep,STSH *stsh, U8 *pointer, U16 *pos);

typedef struct _Sprm
    {
	/*16 bits in total*/
    U32 ispmd:9;      /*ispmd unique identifier within sgc group*/
    U32 fSpec:1;      /*fSpec sprm requires special handling*/
    U32 sgc:3;        /*sgc   sprm group; type of sprm (PAP, CHP, etc)*/
    U32 spra:3;       /*spra  size of sprm argument*/
    } Sprm;

typedef enum
    {
    sgcPAP = 1,
    sgcCHP,
    sgcPIC,
    sgcSEP,
    sgcTAP
    }sgcval;

int wvSprmLen(int spra);
void wvGetSprmFromU16(Sprm *Sprm,U16 sprm);
int wvEatSprm(U16 sprm,U8 *pointer, U16 *pos);

typedef enum _SprmName
	{
	/* 
	these ones showed up in rgsprmPrm and are mostly 
	out of date i reckon
	*/
	sprmNoop			  = 0x0000 ,	/* this makes sense */
	sprmPPnbrRMarkNot	  = 0x0000 ,	/* never seen this one */

	/*
	this subset were not listed in word 8, but i recreated them
	from the word 8 guidelines and the original word 6, so 
	basically they will blow things up when ms decides to reuse them
	in word 2000 or later versions, but what the hell...
	*/
	sprmCFStrikeRM		  = 0x0841 ,
	sprmPNLvlAnm		  = 0x240D ,
	sprmCFtc			  = 0x483D ,
	/*end subset*/

	/*
	one of the sprm's that shows up in word 6 docs is "0", which
	appears to be either the pap.istd or just an index, seeing
	as the word 6 people didn't list it, lets just ignore it.
	as it only happens in word 6 docs, our code happens to 
	function fine in the current setup, but at some stage 
	im sure it will bite me hard
	*/

	sprmPIstd             = 0x4600 ,
	sprmPIstdPermute      = 0xC601 ,
	sprmPIncLvl           = 0x2602 ,
	sprmPJc               = 0x2403 ,
	sprmPFSideBySide      = 0x2404 ,
	sprmPFKeep            = 0x2405 ,
	sprmPFKeepFollow      = 0x2406 ,
	sprmPFPageBreakBefore = 0x2407 ,
	sprmPBrcl             = 0x2408 ,
	sprmPBrcp             = 0x2409 ,
	sprmPIlvl             = 0x260A ,
	sprmPIlfo             = 0x460B ,
	sprmPFNoLineNumb      = 0x240C ,
	sprmPChgTabsPapx      = 0xC60D ,
	sprmPDxaRight         = 0x840E ,
	sprmPDxaLeft          = 0x840F ,
	sprmPNest             = 0x4610 ,
	sprmPDxaLeft1         = 0x8411 ,
	sprmPDyaLine          = 0x6412 ,
	sprmPDyaBefore        = 0xA413 ,
	sprmPDyaAfter         = 0xA414 ,
	sprmPChgTabs          = 0xC615 ,
	sprmPFInTable         = 0x2416 ,
	sprmPFTtp             = 0x2417 ,
	sprmPDxaAbs           = 0x8418 ,
	sprmPDyaAbs           = 0x8419 ,
	sprmPDxaWidth         = 0x841A ,
	sprmPPc               = 0x261B ,
	sprmPBrcTop10         = 0x461C ,
	sprmPBrcLeft10        = 0x461D ,
	sprmPBrcBottom10      = 0x461E ,
	sprmPBrcRight10       = 0x461F ,
	sprmPBrcBetween10     = 0x4620 ,
	sprmPBrcBar10         = 0x4621 ,
	sprmPDxaFromText10    = 0x4622 ,
	sprmPWr               = 0x2423 ,
	sprmPBrcTop           = 0x6424 ,
	sprmPBrcLeft          = 0x6425 ,
	sprmPBrcBottom        = 0x6426 ,
	sprmPBrcRight         = 0x6427 ,
	sprmPBrcBetween       = 0x6428 ,
	sprmPBrcBar           = 0x6629 ,
	sprmPFNoAutoHyph      = 0x242A ,
	sprmPWHeightAbs       = 0x442B ,
	sprmPDcs              = 0x442C ,
	sprmPShd              = 0x442D ,
	sprmPDyaFromText      = 0x842E ,
	sprmPDxaFromText      = 0x842F ,
	sprmPFLocked          = 0x2430 ,
	sprmPFWidowControl    = 0x2431 ,
	sprmPRuler            = 0xC632 ,
	sprmPFKinsoku         = 0x2433 ,
	sprmPFWordWrap        = 0x2434 ,
	sprmPFOverflowPunct   = 0x2435 ,
	sprmPFTopLinePunct    = 0x2436 ,
	sprmPFAutoSpaceDE     = 0x2437 ,
	sprmPFAutoSpaceDN     = 0x2438 ,
	sprmPWAlignFont       = 0x4439 ,
	sprmPFrameTextFlow    = 0x443A ,
	sprmPISnapBaseLine    = 0x243B ,
	sprmPAnld             = 0xC63E ,
	sprmPPropRMark        = 0xC63F ,
	sprmPOutLvl           = 0x2640 ,
	sprmPFBiDi            = 0x2441 ,
	sprmPFNumRMIns        = 0x2443 ,
	sprmPCrLf             = 0x2444 ,
	sprmPNumRM            = 0xC645 ,
	sprmPHugePapx         = 0x6645 ,
	sprmPFUsePgsuSettings = 0x2447 ,
	sprmPFAdjustRight     = 0x2448 ,

	sprmCFRMarkDel        = 0x0800 ,
	sprmCFRMark           = 0x0801 ,
	sprmCFFldVanish       = 0x0802 ,
	sprmCPicLocation      = 0x6A03 ,
	sprmCIbstRMark        = 0x4804 ,
	sprmCDttmRMark        = 0x6805 ,
	sprmCFData            = 0x0806 ,
	sprmCIdslRMark        = 0x4807 ,
	sprmCChs              = 0xEA08 ,
	sprmCSymbol           = 0x6A09 ,
	sprmCFOle2            = 0x080A ,
	sprmCIdCharType       = 0x480B ,
	sprmCHighlight        = 0x2A0C ,
	sprmCObjLocation      = 0x680E ,
	sprmCFFtcAsciSymb     = 0x2A10 ,
	sprmCIstd             = 0x4A30 ,
	sprmCIstdPermute      = 0xCA31 ,
	sprmCDefault          = 0x2A32 ,
	sprmCPlain            = 0x2A33 ,
	sprmCKcd              = 0x2A34 ,
	sprmCFBold            = 0x0835 ,
	sprmCFItalic          = 0x0836 ,
	sprmCFStrike          = 0x0837 ,
	sprmCFOutline         = 0x0838 ,
	sprmCFShadow          = 0x0839 ,
	sprmCFSmallCaps       = 0x083A ,
	sprmCFCaps            = 0x083B ,
	sprmCFVanish          = 0x083C ,
	sprmCFtcDefault       = 0x4A3D ,
	sprmCKul              = 0x2A3E ,
	sprmCSizePos          = 0xEA3F ,
	sprmCDxaSpace         = 0x8840 ,
	sprmCLid              = 0x4A41 ,
	sprmCIco              = 0x2A42 ,
	sprmCHps              = 0x4A43 ,
	sprmCHpsInc           = 0x2A44 ,
	sprmCHpsPos           = 0x4845 ,
	sprmCHpsPosAdj        = 0x2A46 ,
	sprmCMajority         = 0xCA47 ,
	sprmCIss              = 0x2A48 ,
	sprmCHpsNew50         = 0xCA49 ,
	sprmCHpsInc1          = 0xCA4A ,
	sprmCHpsKern          = 0x484B ,
	sprmCMajority50       = 0xCA4C ,
	sprmCHpsMul           = 0x4A4D ,
	sprmCYsri             = 0x484E ,
	sprmCRgFtc0           = 0x4A4F ,
	sprmCRgFtc1           = 0x4A50 ,
	sprmCRgFtc2           = 0x4A51 ,
	sprmCCharScale        = 0x4852 ,
	sprmCFDStrike         = 0x2A53 ,
	sprmCFImprint         = 0x0854 ,
	sprmCFSpec            = 0x0855 ,
	sprmCFObj             = 0x0856 ,
	sprmCPropRMark        = 0xCA57 ,
	sprmCFEmboss          = 0x0858 ,
	sprmCSfxText          = 0x2859 ,
	sprmCFBiDi            = 0x085A ,
	sprmCFDiacColor       = 0x085B ,
	sprmCFBoldBi          = 0x085C ,
	sprmCFItalicBi        = 0x085D ,
	sprmCFtcBi            = 0x4A5E ,
	sprmCLidBi            = 0x485F ,
	sprmCIcoBi            = 0x4A60 ,
	sprmCHpsBi            = 0x4A61 ,
	sprmCDispFldRMark     = 0xCA62 ,
	sprmCIbstRMarkDel     = 0x4863 ,
	sprmCDttmRMarkDel     = 0x6864 ,
	sprmCBrc              = 0x6865 ,
	sprmCShd              = 0x4866 ,
	sprmCIdslRMarkDel     = 0x4867 ,
	sprmCFUsePgsuSettings = 0x0868 ,
	sprmCCpg              = 0x486B ,
	sprmCRgLid0           = 0x486D ,
	sprmCRgLid1           = 0x486E ,
	sprmCIdctHint         = 0x286F ,

	sprmPicBrcl           = 0x2E00 ,
	sprmPicScale          = 0xCE01 ,
	sprmPicBrcTop         = 0x6C02 ,
	sprmPicBrcLeft        = 0x6C03 ,
	sprmPicBrcBottom      = 0x6C04 ,
	sprmPicBrcRight       = 0x6C05 ,

	sprmScnsPgn           = 0x3000 ,
	sprmSiHeadingPgn      = 0x3001 ,
	sprmSOlstAnm          = 0xD202 ,
	sprmSDxaColWidth      = 0xF203 ,
	sprmSDxaColSpacing    = 0xF204 ,
	sprmSFEvenlySpaced    = 0x3005 ,
	sprmSFProtected       = 0x3006 ,
	sprmSDmBinFirst       = 0x5007 ,
	sprmSDmBinOther       = 0x5008 ,
	sprmSBkc              = 0x3009 ,
	sprmSFTitlePage       = 0x300A ,
	sprmSCcolumns         = 0x500B ,
	sprmSDxaColumns       = 0x900C ,
	sprmSFAutoPgn         = 0x300D ,
	sprmSNfcPgn           = 0x300E ,
	sprmSDyaPgn           = 0xB00F ,
	sprmSDxaPgn           = 0xB010 ,
	sprmSFPgnRestart      = 0x3011 ,
	sprmSFEndnote         = 0x3012 ,
	sprmSLnc              = 0x3013 ,
	sprmSGprfIhdt         = 0x3014 ,
	sprmSNLnnMod          = 0x5015 ,
	sprmSDxaLnn           = 0x9016 ,
	sprmSDyaHdrTop        = 0xB017 ,
	sprmSDyaHdrBottom     = 0xB018 ,
	sprmSLBetween         = 0x3019 ,
	sprmSVjc              = 0x301A ,
	sprmSLnnMin           = 0x501B ,
	sprmSPgnStart         = 0x501C ,
	sprmSBOrientation     = 0x301D ,
	sprmSBCustomize       = 0x301E ,
	sprmSXaPage           = 0xB01F ,
	sprmSYaPage           = 0xB020 ,
	sprmSDxaLeft          = 0xB021 ,
	sprmSDxaRight         = 0xB022 ,
	sprmSDyaTop           = 0x9023 ,
	sprmSDyaBottom        = 0x9024 ,
	sprmSDzaGutter        = 0xB025 ,
	sprmSDmPaperReq       = 0x5026 ,
	sprmSPropRMark        = 0xD227 ,
	sprmSFBiDi            = 0x3228 ,
	sprmSFFacingCol       = 0x3229 ,
	sprmSFRTLGutter       = 0x322A ,
	sprmSBrcTop           = 0x702B ,
	sprmSBrcLeft          = 0x702C ,
	sprmSBrcBottom        = 0x702D ,
	sprmSBrcRight         = 0x702E ,
	sprmSPgbProp          = 0x522F ,
	sprmSDxtCharSpace     = 0x7030 ,
	sprmSDyaLinePitch     = 0x9031 ,
	sprmSClm              = 0x5032 ,
	sprmSTextFlow         = 0x5033 ,

	sprmTJc               = 0x5400 ,
	sprmTDxaLeft          = 0x9601 ,
	sprmTDxaGapHalf       = 0x9602 ,
	sprmTFCantSplit       = 0x3403 ,
	sprmTTableHeader      = 0x3404 ,
	sprmTTableBorders     = 0xD605 ,
	sprmTDefTable10       = 0xD606 ,
	sprmTDyaRowHeight     = 0x9407 ,
	sprmTDefTable         = 0xD608 ,
	sprmTDefTableShd      = 0xD609 ,
	sprmTTlp              = 0x740A ,
	sprmTFBiDi            = 0x560B ,
	sprmTHTMLProps        = 0x740C ,
	sprmTSetBrc           = 0xD620 ,
	sprmTInsert           = 0x7621 ,
	sprmTDelete           = 0x5622 ,
	sprmTDxaCol           = 0x7623 ,
	sprmTMerge            = 0x5624 ,
	sprmTSplit            = 0x5625 ,
	sprmTSetBrc10         = 0xD626 ,
	sprmTSetShd           = 0x7627 ,
	sprmTSetShdOdd        = 0x7628 ,
	sprmTTextFlow         = 0x7629 ,
	sprmTDiagLine         = 0xD62A ,
	sprmTVertMerge        = 0xD62B ,
	sprmTVertAlign        = 0xD62C 
	} SprmName;

SprmName wvGetrgsprmWord6(U8 in);

void wvApplysprmPIstdPermute(PAP *apap,U8 *pointer,U16 *pos);
void wvApplysprmPIncLvl(PAP *apap,U8 *pointer,U16 *pos);
void wvApplysprmPChgTabsPapx(PAP *apap,U8 *pointer,U16 *pos);
int wvApplysprmPChgTabs(PAP *apap,U8 *pointer,U16 *len);
void wvApplysprmPPc(PAP *apap,U8 *pointer,U16 *len);
void wvApplysprmPFrameTextFlow(PAP *apap,U8 *pointer,U16 *pos);
void wvApplysprmPAnld(int version,PAP *apap,U8 *pointer, U16 *pos);
void wvApplysprmPPropRMark(PAP *apap,U8 *pointer,U16 *pos);
void wvApplysprmPNumRM(PAP *apap,U8 *pointer, U16 *pos);
void wvApplysprmPHugePapx(PAP *apap, U8 *pointer, U16 *pos);		/*unfinished*/

void wvApplysprmCChs(CHP *achp,U8 *pointer,U16 *pos);	/*unfinished*/
void wvApplysprmCSymbol(CHP *achp,U8 *pointer,U16 *pos);
void wvApplysprmCIstdPermute(CHP *achp,U8 *pointer,U16 *pos);	/*unfinished*/
void wvApplysprmCDefault(CHP *achp,U8 *pointer,U16 *pos);
void wvApplysprmCPlain(CHP *achp,STSH *stsh,U8 *pointer,U16 *pos);
void wvApplysprmCHpsInc(CHP *achp,U8 *pointer,U16 *pos);	/*unfinished*/
void wvApplysprmCSizePos(CHP *achp,U8 *pointer,U16 *pos);	/*unfinished*/
void wvApplysprmCHpsPosAdj(CHP *achp,U8 *pointer,U16 *pos);	/*unfinished*/
void wvApplysprmCMajority(CHP *achp,STSH *stsh,U8 *pointer,U16 *pos);	/*possibly wrong*/
void wvApplysprmCMajority50(CHP *achp,STSH *stsh,U8 *pointer,U16 *pos);	/*possibly wrong*/
void wvApplysprmCHpsInc1(CHP *achp,U8 *pointer,U16 *pos);
void wvApplysprmCPropRMark(CHP *achp,U8 *pointer,U16 *pos);
void wvApplysprmCDispFldRMark(CHP *achp,U8 *pointer,U16 *pos);

U8 wvToggle(U8 in,U8 toggle);

typedef enum
	{
	UTF8,
	ISO_5589_15,
	CP1252
	/*add your own charset here*/
	} wvCharset;



#define TT_OTHER        	0
#define TT_DOCUMENT     	1       
#define TT_BEGIN			2       
#define TT_END				3  	     
#define TT_TITLE			4
#define TT_PARA				5
#define TT_CHARSET			6	
#define TT_VERSION			7	
#define TT_JUSTIFICATION 	8
#define TT_JUST				9
#define TT_LEFT				10	
#define TT_RIGHT			11
#define TT_CENTER			12
#define TT_BLOCK			13
#define TT_ASIAN			14

#define TokenTableSize 15

typedef struct _TokenTable
	{
    const char *    m_name;
    int             m_type;
	} TokenTable,CharsetTable,ReasonTable;

typedef struct _wvEle
	{
	int nostr;
	char **str;
	} wvEle;

#define CharsetTableSize 3

const char *wvGetCharset(U16 charset);

typedef struct _state_data
	{
	wvEle elements[TokenTableSize];
	U32 state;
	wvEle *currentele;
	char **current;
	U32 currentlen;
	FILE *fp;
	} state_data;

typedef struct _expand_data
	{
	STTBF *anSttbfAssoc;
	PAP *apap;
	U16 charset;
	
	char *retstring;
	U32 currentlen;
	state_data *sd;
	} expand_data;

void wvInitExpandData(expand_data *data);

typedef struct _PRM
	{
	/*full total of bits should be 16*/
	U32 fComplex:1;
	union
		{
		struct 
			{
			U32 isprm:7;
			U32 val:8;
			} var1;
		struct
			{
			U32 igrpprl:15;
			} var2;
		} para;
	} PRM; 

void wvGetPRM(PRM *item,FILE *fd);
void wvInitPRM(PRM *item);

typedef struct _PCD
	{
	/*this should be 16 bits for bitfields*/
 	U32 fNoParaLast:1;
	U32 fPaphNil:1;
	U32 fCopied:1;
	U32 reserved:5;
	U32 fn:8;
 	U32 fc;
 	PRM prm;
	} PCD;

void wvGetPCD(PCD *item,FILE *fd);
void wvInitPCD(PCD *item);
int wvGetPCD_PLCF(PCD **pcd,U32 **pos,U32 *nopcd,U32 offset,U32 len,FILE *fd);
int wvReleasePCD_PLCF(PCD *pcd,U32 *pos);

typedef struct _CLX
    {
    PCD *pcd;
    U32 *pos;
    U32 nopcd;

    U16 grpprl_count;
    U16 *cbGrpprl;
    U8 **grpprl;
    }CLX;


U16 wvAutoCharset(CLX *clx);

void wvInitCLX(CLX *item);
void wvGetCLX(int version,CLX *clx,U32 offset,U32 len,FILE *fd);
void wvReleaseCLX(CLX *clx);
void wvBuildCLXForSimple6(CLX *clx,FIB *fib);


typedef struct _wvParseStruct
	{
	/*public*/
	void *userData;

	/*protected*/
	FILE *mainfd;
	FILE *tablefd;
	FILE *data;
	FILE *summary;
	FIB fib;
	STTBF anSttbfAssoc;
	CLX clx;

	/*private*/
	FILE *tablefd0;
	FILE *tablefd1;
	}wvParseStruct;


FILE *wvWhichTableStream(FIB *fib,wvParseStruct *ps);

/* 
returns the same as wvOLEDecode with the addition that
4 means that it isnt a word document
*/
int wvInitParser(wvParseStruct *ps,FILE *fp);

void wvDecodeSimple(wvParseStruct *ps);

typedef enum
	{
	cbATRD = 30,
	cbANLD = 84,
	cbANLV = 16,
	cbASUMY = 4,
	cbASUMYI = 12,
	cbBTE = 4,
	cbBKD = 6,
	cbBKF = 4,
	cbBKL = 2,
	cbBRC = 4,
	cbBRC10 = 2,
	cbCHP = 136, 
	cbDTTM = 4,
	cbDCS = 2,
	cbDOGRID = 10, 
	cbDOPTYPOGRAPHY = 310, 
	cbFSPA = 26, 
	cbFIB = 898, 
	cbLSPD = 4,
	cbOLST = 212,
	cbNUMRM = 128, 
	cbPGD = 10,
	cbPHE = 12,
	cbPAP = 610, 
	cbPCD = 8,
	/*
	cbPLC 
	*/
	cbPRM = 2,
	cbRS = 16,
	cbRR = 4,
	cbSED = 12, 
	cbSEP = 704,
	cbSHD = 2,
	cbTBD = 1,
	cbTC = 20,
	cbTLP = 4,
	cbTAP = 1728, 
	cbWKB = 12,
	cbLSTF = 28
	} cbStruct;

typedef enum
	{
	cb6BTE = 2, 
	cb6FIB = 682, 
	cb6PHE = 6,
	cb6ANLD = 52
	} cb6Struct;

U32 wvNormFC(U32 fc,int *flag);
int wvGetPieceBoundsFC(U32 *begin,U32 *end,CLX *clx,U32 piececount);
int wvGetPieceBoundsCP(U32 *begin,U32 *end,CLX *clx,U32 piececount);
U16 wvGetChar(FILE *fd,int chartype);


typedef struct _BTE
    {
    U32 pn:22;      
    U32 unused:10;      
    } BTE;

void wvGetBTE(BTE *bte,FILE *fd);
void wvInitBTE(BTE *bte);
int wvGetBTE_PLCF(BTE **bte,U32 **pos,U32 *nobte,U32 offset,U32 len,FILE *fd);
int wvGetBTE_PLCF6(BTE **bte,U32 **pos,U32 *nobte,U32 offset,U32 len,FILE *fd);
void wvCopyBTE(BTE *dest,BTE *src);
int wvGetBTE_FromFC(BTE *bte, U32 currentfc, BTE *list,U32 *fcs, int nobte);
void wvListBTE_PLCF(BTE **bte,U32 **pos,U32 *nobte);

#define PAGESIZE 512

typedef struct _BX
	{
	U8 offset;
	PHE phe;
	} BX;

void wvGetBX(BX *item, FILE *fd);
void wvGetBX6(BX *item, FILE *fd);

typedef struct _PAPX
	{
	U8  cb;
 	U16 istd;
 	U8 *grpprl;
	} PAPX;

void wvGetPAPX(int version,PAPX *item,U32 offset,FILE *fd);
void wvReleasePAPX(PAPX *item);
void wvInitPAPX(PAPX *item);

typedef struct _PAPX_FKP
	{
	U32 *rgfc;
	BX *rgbx;
	PAPX *grppapx;
	U8 crun;
	} PAPX_FKP;

void wvGetPAPX_FKP(int version,PAPX_FKP *fkp,U32 pn,FILE *fd);
void wvReleasePAPX_FKP(PAPX_FKP *fkp);
void wvInitPAPX_FKP(PAPX_FKP *fkp);

int wvGetIntervalBounds(U32 *fcFirst, U32 *fcLim, U32 currentfc, U32 *pos, U32 nopos);
int wvIncFC(int chartype);

int wvGetSimpleParaBounds(int version,PAPX_FKP *fkp,U32 *fcFirst, U32 *fcLim, U32 currentcp,CLX *clx, BTE *bte, U32 *pos,int nobte, FILE *fd);

int wvOutputTextChar(U16 eachchar,U8 chartype,U8 outputtype,U8 *state,wvParseStruct *ps);
void wvOutputFromCP1252(U16 eachchar,U8 outputtype);
void wvOutputFromUnicode(U16 eachchar,U8 outputtype);

U16 wvConvert1252ToUnicode(U8 char8);
U16 wvConvert1252Toiso8859_15(U8 char8);

U16 wvConvertUnicodeToiso8859_15(U16 char16);



int wvConvert1252ToHtml(U8 char8);

void wvDecodeComplex(wvParseStruct *ps);
int wvGetComplexParaBounds(int version,PAPX_FKP *fkp,U32 *fcFirst, U32 *fcLim, U32 currentcp,CLX *clx, BTE *bte, U32 *pos,int nobte, U32 piece,FILE *fd);
U32 wvSearchNextLargestFCPAPX_FKP(PAPX_FKP *fkp,U32 currentfc);
int wvQuerySamePiece(U32 fcTest,CLX *clx,U32 piece);
int wvGetComplexParafcFirst(int version,U32 *fcFirst,U32 currentfc,CLX *clx, BTE *bte, U32 *pos,int nobte,U32 piece,PAPX_FKP *fkp,FILE *fd);
U32 wvSearchNextSmallestFCPAPX_FKP(PAPX_FKP *fkp,U32 currentfc);
U32 wvGetPieceFromCP(U32 cp,CLX *clx);
int wvGetIndexFCInFKP_PAPX(PAPX_FKP *fkp,U32 currentfc);

void wvOLEFree(void);



int wvText(wvParseStruct *ps);
int wvHtml(wvParseStruct *ps);

/*
if you use these you have to close the FILE stream yourself

you can set them to NULL to turn them off if necessary
*/
void wvSetErrorStream(FILE *in);
void wvSetWarnStream(FILE *in);
void wvRealTrace(char *file, int line,char *fmt, ...);

#ifdef DEBUG
#define wvTrace(fmt, args...) wvRealTrace(__FILE__,__LINE__,fmt, ## args)
#else
#define wvTrace(fmt, args...)
#endif

void wvAssembleSimplePAP(PAP *apap,U32 fc,PAPX_FKP *fkp,STSH *stsh);

void wvAppendStr(char **orig,const char *add);
int wvParseConfig(state_data *myhandle);

void wvBeginDocument(expand_data *data);
void wvEndDocument(expand_data *data);

void wvInitStateData(state_data *data);
void wvListStateData(state_data *data);

int wvExpand(expand_data *myhandle,char *buf,int len);
int wvStrlen(const char *str);
void wvReleaseStateData(state_data *data);

U32 wvConvertCPToFC(U32 currentcp,CLX *clx);

void wvBeginPara(expand_data *data);
void wvEndPara(expand_data *data);

int wvGetComplexParafcLim(int first,U32 *fcLim,U32 currentfc,CLX *clx, BTE *bte, U32 *pos,int nobte,U32 piece,PAPX_FKP *fkp,FILE *fd);



int wvQuerySupported(FIB *fib,int *reason);

const char *wvReason(int reason);

void wvSetCharHandler(int (*proc)(wvParseStruct *,U16,U8));

typedef enum
	{
	DOCBEGIN,
	DOCEND,
	PARABEGIN,
	PARAEND
	} wvTag;

int wvHandleElement(wvParseStruct *ps,wvTag tag, PAP *apap);
void wvSetElementHandler(int (*proc)(wvParseStruct *,wvTag ,PAP *));
int wvHandleDocument(wvParseStruct *ps,wvTag tag);
void wvSetDocumentHandler(int (*proc)(wvParseStruct *,wvTag));

SprmName wvGetrgsprmPrm(U16 in);
void wvAssembleComplexPAP(int version,PAP *apap,U32 cpiece,STSH *stsh,CLX *clx);
U32 wvGetEndFCPiece(U32 piece,CLX *clx);
void wvInitSprm(Sprm *Sprm);


/*current addition position*/

typedef struct _MSOFBH
	{
	U32 ver : 4;
	U32 inst: 12;
	U32 fbt : 16;
	U32 cbLength;
	} MSOFBH;

/* FDGG - File DGG */
typedef struct _FDGG
   {
   U32 spidMax;     /* The current maximum shape ID */
   U32 cidcl;       /* The number of ID clusters (FIDCLs) */
   U32 cspSaved;    /* The total number of shapes saved */
                    /* (including deleted shapes, if undo */
                    /* information was saved) */
   U32 cdgSaved;    /* The total number of drawings saved */
   } FDGG;

/* File ID Cluster - used to save IDCLs */
typedef struct _FIDCL
   {
   U32 dgid;        /* DG owning the SPIDs in this cluster */
   U32 cspidCur;    /* number of SPIDs used so far */
   } FIDCL;

/* FBSE - File Blip Store Entry */
typedef struct _FBSE
   {
   U8      btWin32;    /* Required type on Win32 */
   U8      btMacOS;    /* Required type on Mac */
   U8      rgbUid[16]; /* Identifier of blip */
   U16     tag;        /* currently unused */
   U32     size;       /* Blip size in stream */
   U32     cRef;       /* Reference count on the blip */
   U32     foDelay;    /* File offset in the delay stream */
   U8      usage;      /* How this blip is used (MSOBLIPUSAGE) */
   U8      cbName;     /* length of the blip name */
   U8      unused2;    /* for the future */
   U8      unused3;    /* for the future */
   } FBSE; 


typedef enum
   {
   msoblipusagedefault,  /* all non-texture fill blips get this. */
   msoblipusagetexture,
   msoblipusagemax = 255 /* since this is stored in a byte */
   } msoblipusage;

typedef enum
   {                          /* GEL provided types... */
   msoblipERROR = 0,          /* An error occured during loading */
   msoblipUNKNOWN,            /* An unknown blip type */
   msoblipEMF,                /* Windows Enhanced Metafile */
   msoblipWMF,                /* Windows Metafile */
   msoblipPICT,               /* Macintosh PICT */
   msoblipJPEG,               /* JFIF */
   msoblipPNG,                /* PNG */
   msoblipDIB,                /* Windows DIB */
   msoblipFirstClient = 32,   /* First client defined blip type */
   msoblipLastClient  = 255   /* Last client defined blip type */
   } MSOBLIPTYPE;

typedef enum
   {
   msobiUNKNOWN = 0,
   msobiWMF  = 0x216,      /* Metafile header then compressed WMF */
   msobiEMF  = 0x3D4,      /* Metafile header then compressed EMF */
   msobiPICT = 0x542,      /* Metafile header then compressed PICT */
   msobiPNG  = 0x6E0,      /* One byte tag then PNG data */
   msobiJFIF = 0x46A,      /* One byte tag then JFIF data */
   msobiJPEG = msobiJFIF,
   msobiDIB  = 0x7A8,      /* One byte tag then DIB data */
   msobiClient=0x800      /* Clients should set this bit */
   } MSOBI;                     /* Blip signature as encoded in the MSOFBH.inst */

typedef enum
	{
	msofbtDggContainer = 0xF000,
	msofbtDgg = 0xF006,
	msofbtBSE = 0xF007,
	msofbtDg = 0xF008,
	msofbtOPT = 0xF00B,
	msofbtSp = 0xF00A,
	msofbtBlipFirst = 0xF018
	} MSOFBT;

typedef enum
   {
   msocompressionDeflate = 0,
   msocompressionNone = 254,    /* Used only if compression fails */
   msocompressionTest = 255    /* For testing only */
   } MSOBLIPCOMPRESSION;

typedef enum
   {
   msofilterAdaptive = 0,       /* PNG type - not used/supported for metafile */
   msofilterNone = 254,
   msofilterTest = 255         /* For testing only */
   } MSOBLIPFILTER;

typedef struct _MetaFileBlip
	{
		/* The secondary, or data, UID - should always be set. */
	U8  m_rgbUid[16];
	/* The primary UID - this defaults to 0, in which case the primary ID is
	that of the internal data. NOTE!: The primary UID is only saved to disk
	if (blip_instance ^ blip_signature == 1). Blip_instance is MSOFBH.inst and 
	blip_signature is one of the values defined in MSOBI */
	U8  m_rgbUidPrimary[16];    /* optional based on the above check*/

	/* Metafile Blip overhead = 34 bytes. m_cb gives the number of
	bytes required to store an uncompressed version of the file, m_cbSave
	is the compressed size.  m_mfBounds gives the boundary of all the
	drawing calls within the metafile (this may just be the bounding box
	or it may allow some whitespace, for a WMF this comes from the
	SetWindowOrg and SetWindowExt records of the metafile). */
	U32           m_cb;           /* Cache of the metafile size */
	RECT          m_rcBounds;     /* Boundary of metafile drawing commands */
	POINT         m_ptSize;       /* Size of metafile in EMUs */
	U32           m_cbSave;       /* Cache of saved size (size of m_pvBits) */
	U8            m_fCompression; /* MSOBLIPCOMPRESSION */
	U8            m_fFilter;      /* always msofilterNone */
	U8           *m_pvBits;       /* Compressed bits of metafile. */
	} MetaFileBlip;

typedef struct _BitmapBlip
	{
	/* The secondary, or data, UID - should always be set. */
	U8  m_rgbUid[16];
	/* The primary UID - this defaults to 0, in which case the primary ID is
	that of the internal data. NOTE!: The primary UID is only saved to disk
	if (blip_instance ^ blip_signature == 1). Blip_instance is MSOFBH.finst and 
	blip_signature is one of the values defined in MSOBI*/
	U8  m_rgbUidPrimary[16];    /* optional based on the above check*/
	U8  m_bTag;            
	U8  *m_pvBits;              /* raster bits of the blip*/
	} BitmapBlip;


typedef struct _FOPTE
	{
	/* this should be 16 bits for bitfields, and then 32 bit op*/
	U32 pid : 14;     /* Property ID */
	U32 fBid : 1;     /* value is a blip ID - only valid if fComplex is FALSE */
	U32 fComplex : 1; /* complex property, value is length */
	U32 op;
	} FOPTE;

typedef struct _FSP
   {
   U32 spid;           /* The shape id */
   U32 grfPersistent;
   } FSP;

struct _fopte_list
	{
	FOPTE afopte;
	struct _fopte_list *next;
	};

typedef struct _fopte_list fopte_list;

struct _fsp_list
	{
	FSP afsp;
	fopte_list *afopte_list;
	struct _fsp_list *next;
	};

typedef struct _fsp_list fsp_list;

struct _fbse_list
	{
	FBSE afbse;	
	char filename[4096];
	struct _fbse_list *next;
	};

typedef struct _fbse_list fbse_list;

/* FDG - File DG */
typedef struct _FDG
   {
   U32 csp;          /* The number of shapes in this drawing */
   U32 spidCur;      /* The last MSOSPID given to an SP in this DG */
   } FDG;

fsp_list *wvParseEscher(fbse_list **pic_list,U32 fcDggInfo,U32 lcbDggInfo,FILE *escherstream,FILE *delaystream);
void wvGetMSOFBH(MSOFBH *amsofbh,FILE *infd);
void wvGetFDGG(FDGG *afdgg,FILE *infd);
void wvGetFIDCL(FIDCL *afidcl,FILE *infd);
void wvGetFBSE(FBSE *afbse,FILE *infd);
char *wvGetMetafile(MetaFileBlip *amf,MSOFBH *amsofbh,FILE *infd);
char *wvGetBitmap(BitmapBlip *abm,MSOFBH  *amsofbh,FBSE *afbse,FILE *infd);
U32 wvGetFOPTE(FOPTE *afopte,FILE *infd);
void wvGetFSP(FSP *afsp,FILE *infd);
void wvGetFDG(FDG *afdg,FILE *infd);
int wvQueryDelayStream(FBSE *afbse);
fbse_list *wvGetSPID(U32 spid,fsp_list *afsp_list,fbse_list *afbse_list);



typedef struct _BITMAP
	{
	U8 bm[14];
	} BITMAP;

void wvGetBITMAP(BITMAP *bmp,FILE *infd);

typedef struct _rc
	{
	U8 bm[14];
	} rc;

void wvGetrc(rc *arc,FILE *infd);

typedef struct _PICF
	{
	U32 lcb;
	U16 cbHeader;
	S16 mfp_mm;
	S16 mfp_xExt;
	S16 mfp_yExt;
	S16 mfp_hMF;
	union
		{
		BITMAP bitmap;
		rc arc;
		} 
		obj;
	S16 dxaGoal;
	S16 dyaGoal;
	S16 mx;
	S16 my;
	S16 dxaCropLeft;
	S16 dyaCropTop;
	S16 dxaCropRight;

	S32 dyaCropBottom:16;
	U32  brcl:4;
	U32 fFrameEmpty:1;
	U32 fBitmap:1;
	U32 fDrawHatch:1;
	U32 fError:1;
	U32 bpp:8;

	BRC brcTop;
	BRC brcLeft;
	BRC brcBottom;
	BRC brcRight;
	S16 dxaOrigin;
	S16 dyaOrigin;
	S16 cProps;
	S8 *rgb;
	} PICF;

void wvGetPICF(PICF *apicf,FILE *infd,U32 offset);

/*Summary Information Stream*/

typedef struct _PropHeader
    {
    U16     byteOrder;
    U16     wFormat;
    U16     osVersion1;
    U16     osVersion2;
    U8    classId[16];
    U32    cSections;
    } PropHeader;

void wvGetPropHeader(PropHeader *header,FILE *file);

typedef struct _FIDAndOffset
	{
    U32 dwords[4];
    U32 dwOffset;
    } FIDAndOffset;

void wvGetFIDAndOffset(FIDAndOffset *fid,FILE *file);

typedef struct _aPro
		{
        U32 propID;
        U32 dwOffset;
    	} aPro;

typedef struct _SummaryInfo 
	{
    U32   cBytes;
    U32   cProps;
	aPro *aProps;
	U8 *data;
	} SummaryInfo;

int wvSumInfoOpenStream(SummaryInfo *si,FILE *stream);

void wvGetSummaryInfo(SummaryInfo *si,FILE *file,U32 offset);
void wvReleaseSummaryInfo(SummaryInfo *si);

typedef struct _vtB
	{
	U32 cBytes;
	char  *ch;
	} vtB;

#define VT_I4           0x03
#define VT_LPSTR        0x1E
#define VT_FILETIME     0x40
#define VT_WMF			0x47

typedef struct _PropValue
	{
    U32 vtType;
    union 
		{
        FILETIME      vtTime;
        S32          vtLong;
        vtB vtBSTR;
    	} vtValue;
	} PropValue;

/*String properties*/
#define PID_TITLE          0x02
#define PID_SUBJECT        0x03
#define PID_AUTHOR         0x04
#define PID_KEYWORDS       0x05
#define PID_COMMENTS       0x06
#define PID_TEMPLATE       0x07
#define PID_LASTAUTHOR     0x08
#define PID_REVNUMBER      0x09
#define PID_APPNAME        0x12

/*Time properties*/
#define PID_TOTAL_EDITTIME 0x0A
#define PID_LASTPRINTED    0x0B
#define PID_CREATED        0x0C
#define PID_LASTSAVED      0x0D

/*Long integer properties*/
#define PID_PAGECOUNT      0x0E
#define PID_WORDCOUNT      0x0F
#define PID_CHARCOUNT      0x10
#define PID_SECURITY       0x13

#define PID_THUMBNAIL	   0x11

/*bit masks for security long integer*/
#define AllSecurityFlagsEqNone         0x00
#define fSecurityPassworded            0x01
#define fSecurityRORecommended         0x02
#define fSecurityRO                    0x04
#define fSecurityLockedForAnnotations  0x08

int wvGetProperty(PropValue *Prop, SummaryInfo *si, U32 pid);
void wvReleaseProperty(PropValue *Prop);

int wvSumInfoGetString(char *lpStr, U16 cbStr, U32 pid, SummaryInfo *si);

int wvSumInfoGetLong(U32 *lpLong,U32 pid, SummaryInfo *si);

int wvSumInfoGetTime(U16 *yr, U16 *mon, U16 *day, U16 *hr, U16 *min, U16 *sec, U32 pid, SummaryInfo *si);

int wvSumInfoGetPreview(char *lpStr, U16 cbStr, U32 pid, SummaryInfo *si);

/*end of clean interface*/
















struct tTLP
	{
	U16 itl;
	U8 fShading;
	U8 fColor;
	U8 fHdrRows;
	U8 fLastRow;
	U8 fHdrCols;
	U8 fLastCol;
	};

typedef struct tTLP oTLP;

struct ttablelook
	{
	/* TOP BAR
	color for the top left entry
	color for the otherwise odd top entries
	color for the even top entries
	*/

	/* EVEN ROWS
	color for the left entry
	color for the otherwise odd row entries
	color for the even entries
	*/

	/* ODD ROWS
	color for the left entry
	color for the otherwise odd row entries
	color for the even entries
	*/
	
	char *color[9];
	};

typedef struct ttablelook tablelook;



struct tobj_by_spid
	{
	U16 spid;
	char *filename;
	struct tobj_by_spid *next;
	};

typedef struct tobj_by_spid obj_by_spid;

struct node
	{
	char streamname[255];
	char filename[PATH_MAX];
	struct node *next;
	int level;
	};

typedef struct node olestream;

struct tsep
    {
    U8 bkc;         /*break code*/
    U8 fTitlePage;  /*want title page*/
    U8 fAutoPgn;    /*unused*/
    U8 nfcPgn;      /*page no format*/
    U8 fUnlocked;   /*huh ?*/
    U8 cnsPgn;      /*huh ?*/
    U8 fPgnRestart; /*restart pg numering*/
    U8 fEndNote;    /*footnotes at end of sec or page*/
    U8 lnc;         /*huh ?*/
    U8 grpfIhdt;    /*not used*/
    U8 nLnnMod;
    U16 ccolM1;
    U16 pgnStart;
    U32 xaPage;
    U32 yaPage;
    U32 dxaLeft;
    U32 dxaRight;
    U32 dyaTop;
    U32 dyaBottom;
    U32 dzaGutter;
    };

typedef struct tsep sep;

struct tchp
    {
	unsigned short istd;

    U32 fBold:1;
    U32 fItalic:1;
	U32 fRMarkDel:1;	
	U32 fOutline:1; /*not imp yet*/
	U32 fFldVanish:1; /*not imp yet, internal to word*/
	U32 fSmallCaps:1;
	U32 fCaps:1;
	U32 fVanish:1; /*not imp yet*/
	U32 fRMark:1; /*not imp yet*/
	U32 fSpec:1; 
	U32 fStrike:1;
	U32 fObj:1;	/*not imp yet*/
	U32 fShadow:1;	/*not imp yet*/
	U32 fLowerCase:1;	/*not imp yet*/
	U32 fData:1;
	U32 fOle2:1;	/*not imp yet*/
	U32 fEmboss:1;	/*not imp yet*/
	U32 fImprint:1; /*not imp yet*/
	U32 fDStrike:1;
	U32 fUsePgsuSettings:1; /*not imp yet, dont know what it means*/
	U32 Reserved1:12;	/*unused*/

	U32 Reserved2;	/*unused*/

	U16 ftc;	/*not used in word 8*/
	U16 ftcAscii;
	U16 ftcFE;
	U16 ftcOther;

	U16 fontsize; /*half points*/
	U8 supersubscript;
	S16 fontcode;
	U16 fontspec;
	char color[8];
	U16 underline;
	U8 idctHint;
	U32 fcPic;

	U16 ibstRMark;
	U16 ibstRMarkDel;
	DTTM dttmRMark;
	DTTM dttmRMarkDel;

	U16 fPropRMark;
	U16 ibstPropRMark;
	DTTM dttmPropRMark;
	U8 sfxtText;
    };

typedef struct tchp chp;

struct tlist_def
	{
	U16 *list_string;	
	int len;
	S16 begin_no;
	int no_type;
	int fPrev;
	U32 id;
	chp achp;
	struct tlist_def *sub_def_list;
	};

typedef struct tlist_def list_def;

struct ttap
	{
	oTLP tlp;
	int tablewidth;
	S16 cellwidth[65];
	int cell_no;
	int shade_no;
	int cell_backs[65];
	int cell_fronts[65];
	int cell_pattern[65];
	int rowheight;
	};

typedef struct ttap tap;

struct tpap
    {
    unsigned short istd;
    U8 fInTable;
    U8 fTtp;
	U8 tableflag;
	int justify;
	int ilvl; /*list level, 0 to 8*/
	long ilfo; /*list index*/
	/*link to list information*/
	list_def *list_data;
	ANLD anld;
	tap ourtap;
	S16 leftmargin;
	S16 rightmargin;
	S16 firstline;
	U32 brcBottom;
	U32 brcLeft;
	U32 brcRight;
	U32 brcBetween;
	U16 dxaWidth;
	U32 dyaBefore;
	U32 dyaAfter;
	char *begin;
	char *end;
	char *prespace;
	char *postspace;
    };

typedef struct tpap pap;


struct field_pro
	{
	U32 *cps;
	FLD *flds;
	U32 no;
	};

typedef struct field_pro field_info;

struct tlist_info
	{
	/*
	now this is very hairy, i not sure how this is supposed to work
	so lists are a bit tentitive, basically theres no many things you 
	*can* do with lists, but hopefully this will sort out whether they
	are bulleted or enumerated, and ignore all sorts of shite like
	what kind of bullet were talking about, and whether some list
	items are numbered etc etc
	*/
	U8 *array;
	int count;
	int nooflsts;
	U32 *o_lst_ids;
	int **current_index_nos;
	list_def *o_list_def;
	U8 *level;

	U8 *lstarray;
	int lstcount;
	U32 nooflfos;
	U32 *lst_ids;
	list_def *a_list_def;
	int *overridecount;


	/*
	temp placed here, will eventually replace the other rubbish
	*/
	LFO *lfo;
	U32 nolfo;	
	LFOLVL *lfolvl;
	U32 nooflvl;
	LVL *lvl;

	LST *lst;
	U16 noofLST;
	};

typedef struct tlist_info list_info;

struct tsprm
	{
	U8 *list;
	struct tsprm *next;
	int len;
	};

typedef struct tsprm tSprm;

struct tcstyle
	{
	pap thepap;
	chp thechp;
	char *begin;
	char *end;
	char *name;
	char *prespace;
	char *postspace;
	char *Default;
	char *bold;
	char *italic;
	char *font;
	struct tcstyle *next;
	};

typedef struct tcstyle config_style;

struct _document_style
	{
	char *begin;
	int htwips;
	int vtwips;
	char *end;
	};

typedef struct _document_style document_style;

struct _element_style
	{
	char *begin;
	char *end;
	};

typedef struct _element_style element_style;

typedef enum
   {
   BOLD,  
   ITALIC,
   FONT
   } ele_type;

struct tstyle
	{
	/*temp put in hooks for new stylesheet*/
	STSH stsh;
	pap thepap;
	chp thechp;
	char *name;
	char *begin;
	char *end;
	char *Default;
	char *prespace;
	char *postspace;
	char *font;
	char *bold;
	char *italic;
	};

typedef struct tstyle style;

struct tbookmark_limits
	{
	U32 bookmark_b_no;
	U32 *bookmark_b_cps;
	BKF *bookmark_b_bkfs;
	U32 bookmark_e_no;
	U32 *bookmark_e_cps;
	};

typedef struct tbookmark_limits bookmark_limits;


struct ttextportions
	{
	U32 fcMin;
	U32 fcMac;
	U32 ccpText;
	U32 ccpFtn;
	U32 ccpHdd;
	U32 ccpAtn;
	U32 ccpEdn;
	U32 fcPlcfhdd;
	U32 lcbPlcfhdd;
	U32 *headercplist;
	U8 headercpno;

	U32 fndref_no;
	U32 fndtxt_no;
	U32 *fndRef;
	FRD *fndFRD;
	U32 *fndTxt;
	int list_footnotes[256];
	int list_foot_no;
	int auto_foot;
	int last_foot;

	U32 endref_no;
	U32 endtxt_no;
	U32 *endRef;
	FRD *endFRD;
	S16 *endTrueFRD;
	U32 *endTxt;
	int list_endnotes[256];
	int list_end_no;
	int auto_end;

	U32 andref_no;
	U32 *andRef;
	U32 andtxt_no;
	U32 *andTxt;
	int list_annotations[256];
	int list_anno_no;
	Xst *authors;
	STTBF annotations;
	bookmark_limits a_bookmarks;
	ATRD *the_atrd;
	int last_anno;
	
	bookmark_limits l_bookmarks;
	STTBF bookmarks;

	/*
	STTBF revisions;
	*/

	U32 *section_cps;
	SED *section_fcs;
	U32 section_nos;

	U32 noofficedraw;
	U32 *officedrawcps;
	FSPA *fspas; /*im ignoring the rest of the FSPA for now*/

	int noofblipdata;
	obj_by_spid *ablipdata;
	};

typedef struct ttextportions textportions;

#define IGNORENUM 0
#define DONTIGNORENUM 1
#define IGNOREALL 2


U16 read_16ubit(FILE *);
U32 read_32ubit(FILE *);

U32 sread_32ubit(U8 *in);
U16 sread_16ubit(U8 *in);
U8 sgetc(U8 *in);

U32 dread_32ubit(FILE *in,U8 **list);
U16 dread_16ubit(FILE *in,U8 **list);
U8 dgetc(FILE *in,U8 **list);

U32 bread_32ubit(U8 *in,U16 *pos);
U16 bread_16ubit(U8 *in,U16 *pos);
U8 bgetc(U8 *in,U16 *pos);


void cleanupstreams(char *analyze,char *slashtmp);
olestream * divide_streams(char *filename,char **analyze,char **slashtmp, char *argv0);
int decode_word8(wvParseStruct *ps,int core);
void get_table_info(FILE *tablefd,list_info *a_list_info,U32 fcSttbFnm,U32 lcbSttbFnm,U32 fcPlcfLst,U32 lcbPlcfLst,U32 fcPlfLfo,U32 lcbPlfLfo,style *sheet);

pap *get_pap(U32 pageindex,FILE *in,U32 charindex, U32 *nextfc,style *sheet,list_info *a_list_info);
chp *get_chp(U32 pageindex,FILE *in, FILE *data, U32 charindex, U32 *nextfc,style *sheet,U16 istd);
sep *get_sep(U32 offset,FILE *in);

void decode_clx(U32 startpiece,U32 begincp,U32 endcp,FILE *in,FILE *main,FILE *data,U32 fcClx,U32 lcbClx,U32 intervals,U32 chpintervals,U32 *plcfbtePapx,U32 *plcfbteChpx,field_info *all_fields[5],list_info *a_list_info,style *sheet,textportions *portions,FFN_STTBF *ffn_sttbf,int headfooterflag);
void decode_clx_header(U32 *rgfc,sep *asep,int nopieces,U32 startpiece,U32 begincp,U32 endcp,FILE *in,FILE *main,FILE *data,U32 fcClx,U32 lcbClx,U32 intervals,U32 chpintervals,U32 *plcfbtePapx,U32 *plcfbteChpx,field_info *all_fields[5],list_info *a_list_info,style *sheet,textportions *portions,FFN_STTBF *ffn_sttbf,int headerfooterflag);
void decode_clx_footer(U32 *rgfc,sep *asep,int nopieces,U32 startpiece,U32 begincp,U32 endcp,FILE *in,FILE *main,FILE *data,U32 fcClx,U32 lcbClx,U32 intervals,U32 chpintervals,U32 *plcfbtePapx,U32 *plcfbteChpx,field_info *all_fields[5],list_info *a_list_info,style *sheet,textportions *portions,FFN_STTBF *ffn_sttbf,int headerfooterflag);
int decode_clx_endnote(U32 *rgfc,sep *asep,int nopieces,U32 startpiece,U32 begincp,U32 endcp,FILE *in,FILE *main,FILE *data,U32 fcClx,U32 lcbClx,U32 intervals,U32 chpintervals,U32 *plcfbtePapx,U32 *plcfbteChpx,field_info *all_fields[5],list_info *a_list_info,style *sheet,textportions *portions,FFN_STTBF *ffn_sttbf,int headerfooterflag);

void decode_simple(FILE *mainfd,FILE *tablefd,FILE *data,U32 fcClx,U32 fcMin,U32 fcMac,U32 intervals,U32 chpintervals,U32 *plcfbtePapx,U32 *plcfbteChpx,field_info *all_fields[5],list_info *a_list_info,style *sheet,textportions *portions,FFN_STTBF *ffn_sttbf,int flag);
int decode_simple_footer(FILE *mainfd,FILE *tablefd,FILE *data,sep *asep,U32 fcClx,U32 fcMin,U32 fcMac,U32 intervals,U32 chpintervals,U32 *plcfbtePapx,U32 *plcfbteChpx,field_info *all_fields[5],list_info *a_list_info,style *sheet,textportions *portions,FFN_STTBF *ffn_sttbf,int flag);
int decode_simple_endnote(FILE *mainfd,FILE *tablefd,FILE *data,sep *asep,U32 fcClx,U32 fcMin,U32 fcMac,U32 intervals,U32 chpintervals,U32 *plcfbtePapx,U32 *plcfbteChpx,field_info *all_fields[5],list_info *a_list_info,style *sheet,textportions *portions,FFN_STTBF *ffn_sttbf,int flag);
void decode_simple_header(FILE *mainfd,FILE *tablefd,FILE *data,sep *asep,U32 fcClx,U32 fcMin,U32 fcMac,U32 intervals,U32 chpintervals,U32 *plcfbtePapx,U32 *plcfbteChpx,field_info *all_fields[5],list_info *a_list_info,style *sheet,textportions *portions,FFN_STTBF *ffn_sttbf,int flag);

int decode_letter(int letter,int flag,pap *apap, chp * achp,field_info *magic_fields,FILE *main,FILE *data,FFN_STTBF *ffn_sttbf,list_info *a_list_info,textportions *portions,int *issection,style *sheet);
void decode_f_reference(textportions *portions);
void decode_e_reference(textportions *portions);
void get_next_f_ref(textportions *portions,signed long *nextfootnote);
void get_next_e_ref(textportions *portions,signed long *nextendnote);
void decode_annotation(textportions *portions);

void decode_s_specials(pap *apap,chp *achp,list_info *a_list_info);
int decode_s_table(pap *apap,chp *achp,list_info *a_list_info,int silent);
void decode_e_specials(pap *apap,chp *achp,list_info *a_list_info);
int decode_e_table(pap *apap,chp *achp,list_info *a_list_info,int silent);

void decode_s_chp(chp *achp, FFN_STTBF *,style *);
void decode_e_chp(chp *achp);

void chpsoff(void);
void chpson(void);

void decode_list_nfc(int value,int no_type);
void decode_list_level(pap *apap,int inalist,int num);

int flushbreaks(int);

void decode_s_anld(pap *apap,chp *achp,list_info *a_list_info,FFN_STTBF *ffn_sttbf,style *sheet);
void decode_s_list(pap *apap,chp *achp,list_info *a_list_info,FFN_STTBF *ffn_sttbf,int num,style *sheet);
void decode_e_list(pap *apap,chp *achp,list_info *a_list_info);

void decode_field(FILE *main,field_info *magic_fields,long *cp,U8 *fieldwas,unsigned long *swallowcp1,unsigned long *swallowcp2);

int find_FKPno_papx(U32 fc,U32 *plcfbtePapx,U32 intervals);
int find_FKPno_chpx(U32 fc,U32 *plcfbteChpx,U32 intervals);
U32 find_FC_sepx(U32 cp,U32 *sepcp,textportions *portions);
U32 find_next_smallest_fc(U32 charindex,U32 pageindex, FILE *in, S16 *location,long *pos);
U32 find_next_biggest_fc(U32 charindex,U32 pageindex, FILE *in, U16 *location,long *pos);
U32 find_next_biggest_orequal_fc(U32 charindex,U32 pageindex, FILE *in, U16 *location,long *pos);

pap * get_complex_pap(U32 fc,U32 *plcfbtePapx,U16 i,U16 nopieces,U32 intervals,U32 *rgfc,FILE *main,U32 *avalrgfc,U32 *thenextone,U32 *paraendfc,int *paraendpiece,style *sheet,list_info *a_list_info);
chp * get_complex_chp(U32 fc,U32 *plcfbteChpx,U16 i,U16 nopieces,U32 chpintervals,U32 *rgfc,FILE *main,U32 *avalrgfc,U32 *thenextone,style *sheet,U16 istd);

void decode_gpprls(pap *apap,chp *achp,sep *asep,U16* gpprlindex,int index,tSprm *sprmlists, style *sheet);

style *decode_stylesheet(FILE *tablefd,U32 stsh,U32 stshlen,config_style *in_style);
void fill_pap(style *stylelist,int m,int b);

void decode_sprm(FILE* in,U16 clist,pap *retpap,chp *retchp,sep *retsep,U16 *pos,U8 **list, style *sheet,U16 istd);

void error(FILE *stream,char *fmt, ...);
void oprintf(int silentflag,char *fmt, ...);

int decode_symbol(U16 fontspec);
char *symbolfontdir(void);

int decode_wingding(U16 fontspec);
char *wingdingfontdir(void);

char *patterndir(void);

void decode_header(U32 *begin,U32 *len,textportions *portions,sep *asep);
void decode_header2(U32 *begin,U32 *len,textportions *portions);
void decode_footer(U32 *begin,U32 *len,textportions *portions,sep *asep);
void decode_footnote(U32 *begin,U32 *len,textportions *portions,int i);
void decode_endnote(U32 *begin,U32 *len,textportions *portions,int i);
void decode_footanno(U32 *begin,U32 *len,textportions *portions,int i);

int get_piecetable(FILE *in,U32 **rgfc,U32 **avalrgfc,U16 **sprm,U32 *clxcount);

int find_piece_cp(U32 sepcp,U32  *rgfc,int nopieces);

obj_by_spid * get_blips(U32 fcDggInfo,U32 lcbDggInfo,FILE *tablefd,FILE *mainfd,int *noofblips,int streamtype,obj_by_spid **realhead);
void output_draw(U32 cp,textportions *portions);

void do_indent(pap *apap);

U32 get_fc_from_cp(U32 acp,U32 *rgfc,U32 *avalrgfc,int nopieces);

void end_para(pap *apap, pap *newpap);

int isodd(int i);

/*
returns slot to use in index array which keeps track of how far each list
has got
*/
int decode_ilfo(pap *retpap,chp *achp,list_info *a_list_info,style *sheet,FFN_STTBF *ffn_sttbf);

void init_chp(chp * achp);
void init_pap(pap * apap);

/*result += modified - blank*/
void merge_chps(chp *blank,chp *modified,chp *result);

void init_chp_from_istd(U16 istd,style *sheet,chp *retchp);
void init_pap_from_istd(U16 istd,style *sheet,pap *retpap);

void get_para_bounds(int currentpiece,U32 fc,U32 *rgfc,U32 *avalrgfc, int nopieces, U32 *plcfbtePapx,U32 intervals, FILE *main);

char *ms_strlower(char *in);

/* returns 
0 for no error
1 for file doesn't exist
2 if it isnt an ole file
3 if its corrupt 
*/
int wvOLEDecode(FILE *input, FILE **mainfd, FILE **tablefd0, FILE **tablefd1,FILE **data,FILE **summary);
int wvOLESummaryStream(char *filename,FILE **summary);

long get_picture_header(U32 fcPic,FILE *data,U32 *len,U16 *datatype);

void cleanupglobals(void);
char *ms_basename(char *filename);
void outputimgsrc(char *filename, int width,int height);


U32 decode_b_bookmark(bookmark_limits *l_bookmarks, STTBF *bookmarks);
U32 decode_e_bookmark(bookmark_limits *l_bookmarks);

U32 decode_b_annotation(bookmark_limits *l_bookmarks);
U32 decode_e_annotation(bookmark_limits *l_bookmarks);

U16 *decode_hyperlink(int letter, unsigned long int *swallowcp1, unsigned long int *swallowcp2, U16 **deleteme);
U16 *decode_crosslink(int letter,unsigned long int *swallowcp1, unsigned long int *swallowcp2);

void decode_annotations(FILE *mainfd,FILE *tablefd,textportions *portions);

int decompress(FILE *inputfile,char *outputfile,U32 inlen,U32 outlen);
void myfreeOLEtree(void);

void output_tablebg(pap *apap);
int do_tablelooks(pap *apap);

int setdecom(void);

void pagebreak(void);
void columnbreak(void);
void sectionbreak(sep *asep);
void copy_tap(tap *rettap,tap *intap);
void check_auto_color(chp *achp);

Xst *extract_authors(FILE *tablefd,U32 fcGrpXstAtnOwners,U32 lcbGrpXstAtnOwners);
void extract_bookm_limits(bookmark_limits *l_bookmarks,FILE *tablefd,U32 fcPlcfbkf,U32 lcbPlcfbkf, U32 fcPlcfbkl,U32 lcbPlcfbkl);

int use_fontfacequery(chp *achp);

char *notoday(int no);

void convertwmf(char *filename);

int Parse (FILE * in,config_style **in_style,document_style **doc_style,element_style *ele_style);
int do_output_start(U32 *avalrgfc,int nopieces,document_style *doc_style);
void do_output_end(document_style *doc_style,int core,int tail);
char *argument(void);

int query_piece_cp(U32 *rgfc,U32* avalrgfc,int nopieces,U32 querycp,U32 *nextpiececp,int *flag_8_16);
int query_piece_cp_seek(U32 *rgfc,U32* avalrgfc,int nopieces,long int querycp,U32 *nextpiececp,int *flag_8_16,FILE *fd);
void fill_table_info(pap *apap,U32 tapfc1, U32 *plcfbtePapx,U32 intervals, FILE *mainfd,style *sheet,list_info *a_list_info);

char *expand_variables(char *in, pap *apap);
char *expand_element(char *in, char *fontface, char *color, char *size);
void init_sep(sep *asep);
char *get_image_prefix(void);

int add_t(int **vals,S16 *p,int plen);
int gcf(int high, int low);
int gcf_list(int *vals,int cno);
int allowedfont(style *sheet,U16 istd);

#define NOOFIDS 8

/*interim*/
U32 wvGetSPIDfromCP(U32 cp,textportions *portions);

/* have to have pap replaced with PAP, and change the text output code to the new ones, whenever they are ready*/
void wvGetListInfo(pap *apap, chp *achp,LFO *lfo, LFOLVL *lfolvl,LVL *lvl,U32 nolfo, LST *lst, U32 noofLST,style *sheet,FFN_STTBF *ffn_sttbf);
/* have to have pap replaced with PAP*/
void wvAddPAP_FromBucket(pap *pap,U8 *pointer8,U16 len,style *sheet);

/*we have to replace chp with CHP*/
void wvAddCHP_FromBucket(chp *achp,U8 *pointer8,U16 len,style *sheet);
void twvCopyCHP(chp *dest,chp *src);

#ifdef __cplusplus
}
#endif

#endif