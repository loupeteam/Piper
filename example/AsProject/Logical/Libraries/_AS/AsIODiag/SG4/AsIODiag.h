/* Automation Studio generated header file */
/* Do not edit ! */

#ifndef _ASIODIAG_
#define _ASIODIAG_
#ifdef __cplusplus
extern "C" 
{
#endif

#include <bur/plctypes.h>

#include <runtime.h>

#ifndef _BUR_PUBLIC
#define _BUR_PUBLIC
#endif
/* Datatypes and datatypes of function blocks */
typedef struct DiagCreateInfo
{
	/* VAR_INPUT (analog) */
	unsigned long infoKind;
	/* VAR_OUTPUT (analog) */
	unsigned short status;
	unsigned long ident;
	unsigned long nrEntries;
	/* VAR (analog) */
	unsigned short StateMan;
	unsigned short ErrMan;
	unsigned long Init;
	/* VAR_INPUT (digital) */
	plcbit enable;
} DiagCreateInfo_typ;

typedef struct DiagDisposeInfo
{
	/* VAR_INPUT (analog) */
	unsigned long ident;
	/* VAR_OUTPUT (analog) */
	unsigned short status;
	/* VAR (analog) */
	unsigned short StateMan;
	unsigned short ErrMan;
	unsigned long Init;
	/* VAR_INPUT (digital) */
	plcbit enable;
} DiagDisposeInfo_typ;

typedef struct DiagGetNumInfo
{
	/* VAR_INPUT (analog) */
	unsigned long ident;
	unsigned long index;
	unsigned long infoCode;
	/* VAR_OUTPUT (analog) */
	unsigned short status;
	unsigned long value;
	/* VAR_INPUT (digital) */
	plcbit enable;
} DiagGetNumInfo_typ;

typedef struct DiagGetStrInfo
{
	/* VAR_INPUT (analog) */
	unsigned long ident;
	unsigned long index;
	unsigned long infoCode;
	unsigned long pBuffer;
	unsigned long bufferLen;
	/* VAR_OUTPUT (analog) */
	unsigned short status;
	unsigned long stringLen;
	/* VAR_INPUT (digital) */
	plcbit enable;
} DiagGetStrInfo_typ;



/* Prototyping of functions and function blocks */
_BUR_PUBLIC void DiagCreateInfo(struct DiagCreateInfo* inst);
_BUR_PUBLIC void DiagDisposeInfo(struct DiagDisposeInfo* inst);
_BUR_PUBLIC void DiagGetNumInfo(struct DiagGetNumInfo* inst);
_BUR_PUBLIC void DiagGetStrInfo(struct DiagGetStrInfo* inst);
_BUR_PUBLIC plcbit DiagCpuIsSimulated(void);
_BUR_PUBLIC plcbit DiagCpuIsARsim(void);


/* Constants */
#ifdef _REPLACE_CONST
 #define brNO_FAMILY 255U
 #define brX2X 10U
 #define brC200 9U
 #define brC300 8U
 #define brADDON 7U
 #define brPANEL 6U
 #define brPOWERPANEL 5U
 #define brAUTOMATION_RUNTIME 4U
 #define brLOGIGSCANNER 3U
 #define br2003 2U
 #define br2005 1U
 #define br2010 0U
 #define asdiagALL 3U
 #define asdiagCONFIGURED 2U
 #define asdiagPLUGGED 1U
 #define asdiagHARDWARE_DEVICE_TAG 1007U
 #define asdiagHARDWARE_MODULE_NAME 1006U
 #define asdiagCONFIG_BUS 1005U
 #define asdiagPLUGGED_BUS 1004U
 #define asdiagCONFIG_MODULE 1003U
 #define asdiagPLUGGED_MODULE 1002U
 #define asdiagPATH 1001U
 #define asdiagSERIAL_NUMBER 8U
 #define asdiagCONFIG_USETYPE 7U
 #define asdiagPLUGGED_USETYPE 6U
 #define asdiagCONFIG_FAMILY 5U
 #define asdiagPLUGGED_FAMILY 4U
 #define asdiagCONFIG_MODNO 3U
 #define asdiagPLUGGED_MODNO 2U
 #define asdiagMODUL_STATE 1U
 #define asdiagERR_INFOKIND 30805U
 #define asdiagERR_INFOCODE 30804U
 #define asdiagERR_INDEX 30803U
 #define asdiagERR_IDENT 30802U
 #define asdiagERR_NOMEM 30801U
#else
 _GLOBAL_CONST unsigned char brNO_FAMILY;
 _GLOBAL_CONST unsigned char brX2X;
 _GLOBAL_CONST unsigned char brC200;
 _GLOBAL_CONST unsigned char brC300;
 _GLOBAL_CONST unsigned char brADDON;
 _GLOBAL_CONST unsigned char brPANEL;
 _GLOBAL_CONST unsigned char brPOWERPANEL;
 _GLOBAL_CONST unsigned char brAUTOMATION_RUNTIME;
 _GLOBAL_CONST unsigned char brLOGIGSCANNER;
 _GLOBAL_CONST unsigned char br2003;
 _GLOBAL_CONST unsigned char br2005;
 _GLOBAL_CONST unsigned char br2010;
 _GLOBAL_CONST unsigned long asdiagALL;
 _GLOBAL_CONST unsigned long asdiagCONFIGURED;
 _GLOBAL_CONST unsigned long asdiagPLUGGED;
 _GLOBAL_CONST unsigned long asdiagHARDWARE_DEVICE_TAG;
 _GLOBAL_CONST unsigned long asdiagHARDWARE_MODULE_NAME;
 _GLOBAL_CONST unsigned long asdiagCONFIG_BUS;
 _GLOBAL_CONST unsigned long asdiagPLUGGED_BUS;
 _GLOBAL_CONST unsigned long asdiagCONFIG_MODULE;
 _GLOBAL_CONST unsigned long asdiagPLUGGED_MODULE;
 _GLOBAL_CONST unsigned long asdiagPATH;
 _GLOBAL_CONST unsigned long asdiagSERIAL_NUMBER;
 _GLOBAL_CONST unsigned long asdiagCONFIG_USETYPE;
 _GLOBAL_CONST unsigned long asdiagPLUGGED_USETYPE;
 _GLOBAL_CONST unsigned long asdiagCONFIG_FAMILY;
 _GLOBAL_CONST unsigned long asdiagPLUGGED_FAMILY;
 _GLOBAL_CONST unsigned long asdiagCONFIG_MODNO;
 _GLOBAL_CONST unsigned long asdiagPLUGGED_MODNO;
 _GLOBAL_CONST unsigned long asdiagMODUL_STATE;
 _GLOBAL_CONST unsigned short asdiagERR_INFOKIND;
 _GLOBAL_CONST unsigned short asdiagERR_INFOCODE;
 _GLOBAL_CONST unsigned short asdiagERR_INDEX;
 _GLOBAL_CONST unsigned short asdiagERR_IDENT;
 _GLOBAL_CONST unsigned short asdiagERR_NOMEM;
#endif




#ifdef __cplusplus
};
#endif
#endif /* _ASIODIAG_ */

