/****************************************************************************
Copyright (c) 2010 - 2020, Digital OristarTech Co., Ltd. All rights reserved.

ModuleName : DCI Security Log 
FileName   : DciLogValidatorCommon.h
Author     : chenjingdong@oristartech.com
Date       : 2013-07-12
Version    : v1.0
Description: a common definition for the class CDciLogReportValidator, which 
			 validates the DCI log report   
Others     : 
History    :

< Author >    			< Date >             < Modification >

****************************************************************************/
#ifndef DCI_LOG_VALIDATOR_COMMON_H
#define DCI_LOG_VALIDATOR_COMMON_H

#define MAX_STAT_NUMS 4 //bit len is 2, so the max numbers of status is 4

enum CheckStatus
{
	CHECK_UNKNOWN = 0,	//initiation status
	CHECK_ERR,
	CHECK_OK,
	CHECK_UNKNOWN1	//reserved
};

enum ValStatusID
{
	//
	LOAD_XML_RRPORT = 0,
	FIRST_REC_BODY_HASH,
	FIRST_REC_PREV_HEADER_HASH,
	FIRST_REC_FORMAT,
	FIRST_REC_SEQ_SIGN,
	//
	MID_REC_PREV_HEADER_HASH,
	MID_REC_BODY_HASH,
	MID_REC_FORMAT,
	//
	LAST_REC_PREV_HEADER_HASH,
	LAST_REC_BODY_HASH,
	LAST_REC_CUR_HEADER_HASH,
	LAST_REC_FORMAT,
	LAST_REC_SEQ_SIGN,
	//
	MAX_STAT_ID
};

struct ValStatusDesc
{
	unsigned int nStatIndex;
	const char* pStatDesc;
};

static ValStatusDesc g_ValStatDescTable[MAX_STAT_ID*MAX_STAT_NUMS] = \
{
	//Unknown list
	{CHECK_UNKNOWN*MAX_STAT_ID+LOAD_XML_RRPORT, "- LoadXmlReport .......................................unknown!"},
	{CHECK_UNKNOWN*MAX_STAT_ID+FIRST_REC_BODY_HASH, "- FirstRecBodyHash ....................................unknown!"},
	{CHECK_UNKNOWN*MAX_STAT_ID+FIRST_REC_PREV_HEADER_HASH, "- FirstRecPrevHeaderHash ..............................unknown!"},
	{CHECK_UNKNOWN*MAX_STAT_ID+FIRST_REC_FORMAT, "- FirstRecFormat ......................................unknown!"},
	{CHECK_UNKNOWN*MAX_STAT_ID+FIRST_REC_SEQ_SIGN, "- FirstRecSeqSign .....................................unknown!"},
	{CHECK_UNKNOWN*MAX_STAT_ID+MID_REC_PREV_HEADER_HASH, "- MidRecPrevHeaderHash ................................unknown!"},
	{CHECK_UNKNOWN*MAX_STAT_ID+MID_REC_BODY_HASH, "- MidRecBodyHash ......................................unknown!"},
	{CHECK_UNKNOWN*MAX_STAT_ID+MID_REC_FORMAT, "- MidRecFormat ........................................unknown!"},
	{CHECK_UNKNOWN*MAX_STAT_ID+LAST_REC_PREV_HEADER_HASH, "- LastRecPrevHeaderHash ...............................unknown!"},
	{CHECK_UNKNOWN*MAX_STAT_ID+LAST_REC_BODY_HASH, "- LastRecBodyHash .....................................unknown!"},
	{CHECK_UNKNOWN*MAX_STAT_ID+LAST_REC_CUR_HEADER_HASH, "- LastRecCurHeaderHash ................................unknown!"},
	{CHECK_UNKNOWN*MAX_STAT_ID+LAST_REC_FORMAT, "- LastRecFormat .......................................unknown!"},
	{CHECK_UNKNOWN*MAX_STAT_ID+LAST_REC_SEQ_SIGN, "- LastRecSeqSign ......................................unknown!"},
	//Error list
	{CHECK_ERR*MAX_STAT_ID+LOAD_XML_RRPORT, "- LoadXmlReport .......................................error!"},
	{CHECK_ERR*MAX_STAT_ID+FIRST_REC_BODY_HASH, "- FirstRecBodyHash ....................................error!"},
	{CHECK_ERR*MAX_STAT_ID+FIRST_REC_PREV_HEADER_HASH, "- FirstRecPrevHeaderHash ..............................error!"},
	{CHECK_ERR*MAX_STAT_ID+FIRST_REC_FORMAT, "- FirstRecFormat ......................................error!"},
	{CHECK_ERR*MAX_STAT_ID+FIRST_REC_SEQ_SIGN, "- FirstRecSeqSign .....................................error!"},
	{CHECK_ERR*MAX_STAT_ID+MID_REC_PREV_HEADER_HASH, "- MidRecPrevHeaderHash ................................error!"},
	{CHECK_ERR*MAX_STAT_ID+MID_REC_BODY_HASH, "- MidRecBodyHash ......................................error!"},
	{CHECK_ERR*MAX_STAT_ID+MID_REC_FORMAT, "- MidRecFormat ........................................error!"},
	{CHECK_ERR*MAX_STAT_ID+LAST_REC_PREV_HEADER_HASH, "- LastRecPrevHeaderHash ...............................error!"},
	{CHECK_ERR*MAX_STAT_ID+LAST_REC_BODY_HASH, "- LastRecBodyHash .....................................error!"},
	{CHECK_ERR*MAX_STAT_ID+LAST_REC_CUR_HEADER_HASH, "- LastRecCurHeaderHash ................................error!"},
	{CHECK_ERR*MAX_STAT_ID+LAST_REC_FORMAT, "- LastRecFormat .......................................error!"},
	{CHECK_ERR*MAX_STAT_ID+LAST_REC_SEQ_SIGN, "- LastRecSeqSign ......................................error!"},
	//OK list
	{CHECK_OK*MAX_STAT_ID+LOAD_XML_RRPORT, "- LoadXmlReport .......................................ok!"},
	{CHECK_OK*MAX_STAT_ID+FIRST_REC_BODY_HASH, "- FirstRecBodyHash ....................................ok!"},
	{CHECK_OK*MAX_STAT_ID+FIRST_REC_PREV_HEADER_HASH, "- FirstRecPrevHeaderHash ..............................ok!"},
	{CHECK_OK*MAX_STAT_ID+FIRST_REC_FORMAT, "- FirstRecFormat ......................................ok!"},
	{CHECK_OK*MAX_STAT_ID+FIRST_REC_SEQ_SIGN, "- FirstRecSeqSign .....................................ok!"},
	{CHECK_OK*MAX_STAT_ID+MID_REC_PREV_HEADER_HASH, "- MidRecPrevHeaderHash ................................ok!"},
	{CHECK_OK*MAX_STAT_ID+MID_REC_BODY_HASH, "- MidRecBodyHash ......................................ok!"},
	{CHECK_OK*MAX_STAT_ID+MID_REC_FORMAT, "- MidRecFormat ........................................ok!"},
	{CHECK_OK*MAX_STAT_ID+LAST_REC_PREV_HEADER_HASH, "- LastRecPrevHeaderHash ...............................ok!"},
	{CHECK_OK*MAX_STAT_ID+LAST_REC_BODY_HASH, "- LastRecBodyHash .....................................ok!"},
	{CHECK_OK*MAX_STAT_ID+LAST_REC_CUR_HEADER_HASH, "- LastRecCurHeaderHash ................................ok!"},
	{CHECK_OK*MAX_STAT_ID+LAST_REC_FORMAT, "- LastRecFormat .......................................ok!"},
	{CHECK_OK*MAX_STAT_ID+LAST_REC_SEQ_SIGN, "- LastRecSeqSign ......................................ok!"},
	//
	//Unknown1 list
	{CHECK_UNKNOWN1*MAX_STAT_ID+LOAD_XML_RRPORT, "- LoadXmlReport .......................................unknown1!"},
	{CHECK_UNKNOWN1*MAX_STAT_ID+FIRST_REC_BODY_HASH, "- FirstRecBodyHash ....................................unknown1!"},
	{CHECK_UNKNOWN1*MAX_STAT_ID+FIRST_REC_PREV_HEADER_HASH, "- FirstRecPrevHeaderHash ..............................unknown1!"},
	{CHECK_UNKNOWN1*MAX_STAT_ID+FIRST_REC_FORMAT, "- FirstRecFormat ......................................unknown1!"},
	{CHECK_UNKNOWN1*MAX_STAT_ID+FIRST_REC_SEQ_SIGN, "- FirstRecSeqSign .....................................unknown1!"},
	{CHECK_UNKNOWN1*MAX_STAT_ID+MID_REC_PREV_HEADER_HASH, "- MidRecPrevHeaderHash ................................unknown1!"},
	{CHECK_UNKNOWN1*MAX_STAT_ID+MID_REC_BODY_HASH, "- MidRecBodyHash ......................................unknown1!"},
	{CHECK_UNKNOWN1*MAX_STAT_ID+MID_REC_FORMAT, "- MidRecFormat ........................................unknown1!"},
	{CHECK_UNKNOWN1*MAX_STAT_ID+LAST_REC_PREV_HEADER_HASH, "- LastRecPrevHeaderHash ...............................unknown1!"},
	{CHECK_UNKNOWN1*MAX_STAT_ID+LAST_REC_BODY_HASH, "- LastRecBodyHash .....................................unknown1!"},
	{CHECK_UNKNOWN1*MAX_STAT_ID+LAST_REC_CUR_HEADER_HASH, "- LastRecCurHeaderHash ................................unknown1!"},
	{CHECK_UNKNOWN1*MAX_STAT_ID+LAST_REC_FORMAT, "- LastRecFormat .......................................unknown1!"},
	{CHECK_UNKNOWN1*MAX_STAT_ID+LAST_REC_SEQ_SIGN, "- LastRecSeqSign ......................................unknown1!"}
};

enum
{
	//bit length is 1
	LOAD_XML_RRPORT_ERR_0 = 0,
	LOAD_XML_RRPORT_ERR_1,
	//
	MAX_LOAD_XML_RRPORT_ERR_ID = LOAD_XML_RRPORT_ERR_1 + 1
};

enum
{
	//bit length is 1
	REC_PREV_HEADER_HASH_ERR_0 = 0,
	REC_PREV_HEADER_HASH_ERR_1,

	//
	MAX_REC_PREV_HEADER_HASH_ERR_ID = REC_PREV_HEADER_HASH_ERR_1 + 1
};

enum
{
	//bit length is 1
	REC_BODY_HASH_ERR_0 = 0,
	REC_BODY_HASH_ERR_1,

	//
	MAX_REC_BODY_HASH_ERR_ID = REC_BODY_HASH_ERR_1 + 1
};

enum
{
	//bit length is 1
	REC_CUR_HEADER_HASH_ERR_0 = 0,
	REC_CUR_HEADER_HASH_ERR_1,

	//
	MAX_REC_CUR_HEADER_HASH_ERR_ID = REC_CUR_HEADER_HASH_ERR_1 + 1
};

enum
{
	//bit length is 4
	REC_FORMAT_ERR_0 = 0,
	REC_FORMAT_ERR_1,
	REC_FORMAT_ERR_2,
	REC_FORMAT_ERR_3,
	REC_FORMAT_ERR_4,
	REC_FORMAT_ERR_5,
	REC_FORMAT_ERR_6,
	REC_FORMAT_ERR_7,
	REC_FORMAT_ERR_8,
	REC_FORMAT_ERR_9,
	REC_FORMAT_ERR_10,
	REC_FORMAT_ERR_11,
	REC_FORMAT_ERR_12,
	REC_FORMAT_ERR_13,
	REC_FORMAT_ERR_14,
	REC_FORMAT_ERR_15,

	//
	MAX_REC_FORMAT_ERR_ID = REC_FORMAT_ERR_15 + 1
};

enum
{
	//bit length is 4
	REC_SEQ_SIGN_ERR_0 = 0,
	REC_SEQ_SIGN_ERR_1,
	REC_SEQ_SIGN_ERR_2,
	REC_SEQ_SIGN_ERR_3,
	REC_SEQ_SIGN_ERR_4,
	REC_SEQ_SIGN_ERR_5,
	REC_SEQ_SIGN_ERR_6,
	REC_SEQ_SIGN_ERR_7,
	REC_SEQ_SIGN_ERR_8,
	REC_SEQ_SIGN_ERR_9,
	REC_SEQ_SIGN_ERR_10,
	REC_SEQ_SIGN_ERR_11,
	REC_SEQ_SIGN_ERR_12,
	REC_SEQ_SIGN_ERR_13,
	REC_SEQ_SIGN_ERR_14,
	REC_SEQ_SIGN_ERR_15,
	//
	MAX_REC_SEQ_SIGN_ERR_ID = REC_SEQ_SIGN_ERR_15 + 1
};


enum ValErrorID //each item defined as follows is a base error ID. 
{
	//
	NO_ERR = 0,	//reserved now.
	LOAD_XML_RRPORT_ERR = NO_ERR + 1,
	FIRST_REC_BODY_HASH_ERR = LOAD_XML_RRPORT_ERR + MAX_LOAD_XML_RRPORT_ERR_ID,	
	FIRST_REC_PREV_HEADER_HASH_ERR = FIRST_REC_BODY_HASH_ERR + MAX_REC_BODY_HASH_ERR_ID,
	FIRST_REC_FORMAT_ERR = FIRST_REC_PREV_HEADER_HASH_ERR + MAX_REC_PREV_HEADER_HASH_ERR_ID,
	FIRST_REC_SEQ_SIGN_ERR = FIRST_REC_FORMAT_ERR + MAX_REC_FORMAT_ERR_ID,
	//
	MID_REC_PREV_HEADER_HASH_ERR = FIRST_REC_SEQ_SIGN_ERR + MAX_REC_SEQ_SIGN_ERR_ID, 
	MID_REC_BODY_HASH_ERR = MID_REC_PREV_HEADER_HASH_ERR + MAX_REC_PREV_HEADER_HASH_ERR_ID,
	MID_REC_FORMAT_ERR = MID_REC_BODY_HASH_ERR + MAX_REC_BODY_HASH_ERR_ID,
	//
	LAST_REC_PREV_HEADER_HASH_ERR = MID_REC_FORMAT_ERR + MAX_REC_FORMAT_ERR_ID,
	LAST_REC_BODY_HASH_ERR = LAST_REC_PREV_HEADER_HASH_ERR + MAX_REC_PREV_HEADER_HASH_ERR_ID,
	LAST_REC_CUR_HEADER_HASH_ERR = LAST_REC_BODY_HASH_ERR + MAX_REC_BODY_HASH_ERR_ID,
	LAST_REC_FORMAT_ERR = LAST_REC_CUR_HEADER_HASH_ERR + MAX_REC_CUR_HEADER_HASH_ERR_ID,
	LAST_REC_SEQ_SIGN_ERR = LAST_REC_FORMAT_ERR + MAX_REC_FORMAT_ERR_ID,
	//unknown error
	UNKNOWN_ERR = LAST_REC_SEQ_SIGN_ERR + MAX_REC_SEQ_SIGN_ERR_ID,	//it is a init error code.
	//
	MAX_ERR_ID = UNKNOWN_ERR + 1
};

struct ValErrorDesc
{
	unsigned int nErrIndex;
	const char* pErrDesc;
};

static ValErrorDesc g_ValErrDescTable[MAX_ERR_ID] = \
{
	//
	{NO_ERR, "- Every thing is OK!"},
		//
	{LOAD_XML_RRPORT_ERR, "- LoadXmlReport error0!"},
	{LOAD_XML_RRPORT_ERR + 1, "- LoadXmlReport error1!"},
	//
	{FIRST_REC_BODY_HASH_ERR, "- FirstRecBodyHash error0!"},
	{FIRST_REC_BODY_HASH_ERR + 1, "- FirstRecBodyHash error1!"},
	//
	{FIRST_REC_PREV_HEADER_HASH_ERR, "- FirstRecPrevHeaderHash error0!"},
	{FIRST_REC_PREV_HEADER_HASH_ERR + 1, "- FirstRecPrevHeaderHash error1!"},
	//
	{FIRST_REC_FORMAT_ERR, "- FirstRecFormat error0!"},
	{FIRST_REC_FORMAT_ERR + 1, "- FirstRecFormat error1!"},
	{FIRST_REC_FORMAT_ERR + 2, "- FirstRecFormat error2!"},
	{FIRST_REC_FORMAT_ERR + 3, "- FirstRecFormat error3!"},
	{FIRST_REC_FORMAT_ERR + 4, "- FirstRecFormat error4!"},
	{FIRST_REC_FORMAT_ERR + 5, "- FirstRecFormat error5!"},
	{FIRST_REC_FORMAT_ERR + 6, "- FirstRecFormat error6!"},
	{FIRST_REC_FORMAT_ERR + 7, "- FirstRecFormat error7!"},
	{FIRST_REC_FORMAT_ERR + 8, "- FirstRecFormat error8!"},
	{FIRST_REC_FORMAT_ERR + 9, "- FirstRecFormat error9!"},	//reserved now
	{FIRST_REC_FORMAT_ERR + 10, "- FirstRecFormat error10!"}, //reserved now
	{FIRST_REC_FORMAT_ERR + 11, "- FirstRecFormat error11!"}, //reserved now
	{FIRST_REC_FORMAT_ERR + 12, "- FirstRecFormat error12!"}, //reserved now
	{FIRST_REC_FORMAT_ERR + 13, "- FirstRecFormat error13!"}, //reserved now
	{FIRST_REC_FORMAT_ERR + 14, "- FirstRecFormat error14!"}, //reserved now
	{FIRST_REC_FORMAT_ERR + 15, "- FirstRecFormat error15!"}, //reserved now
	//
	{FIRST_REC_SEQ_SIGN_ERR, "- FirstRecSeqSign error0!"},
	{FIRST_REC_SEQ_SIGN_ERR + 1, "- FirstRecSeqSign error1!"},
	{FIRST_REC_SEQ_SIGN_ERR + 2, "- FirstRecSeqSign error2!"},
	{FIRST_REC_SEQ_SIGN_ERR + 3, "- FirstRecSeqSign error3!"},
	{FIRST_REC_SEQ_SIGN_ERR + 4, "- FirstRecSeqSign error4!"},
	{FIRST_REC_SEQ_SIGN_ERR + 5, "- FirstRecSeqSign error5!"},
	{FIRST_REC_SEQ_SIGN_ERR + 6, "- FirstRecSeqSign error6!"},
	{FIRST_REC_SEQ_SIGN_ERR + 7, "- FirstRecSeqSign error7!"},
	{FIRST_REC_SEQ_SIGN_ERR + 8, "- FirstRecSeqSign error8!"},
	{FIRST_REC_SEQ_SIGN_ERR + 9, "- FirstRecSeqSign error9!"},
	{FIRST_REC_SEQ_SIGN_ERR + 10, "- FirstRecSeqSign error10!"},
	{FIRST_REC_SEQ_SIGN_ERR + 11, "- FirstRecSeqSign error11!"},
	{FIRST_REC_SEQ_SIGN_ERR + 12, "- FirstRecSeqSign error12!"},
	{FIRST_REC_SEQ_SIGN_ERR + 13, "- FirstRecSeqSign error13!"},
	{FIRST_REC_SEQ_SIGN_ERR + 14, "- FirstRecSeqSign error14!"},
	{FIRST_REC_SEQ_SIGN_ERR + 15, "- FirstRecSeqSign error15!"},
	//
	{MID_REC_PREV_HEADER_HASH_ERR, "- MidRecPrevHeaderHash error0!"},
	{MID_REC_PREV_HEADER_HASH_ERR + 1, "- MidRecPrevHeaderHash error1!"},
	//
	{MID_REC_BODY_HASH_ERR, "- MidRecBodyHash error0!"},
	{MID_REC_BODY_HASH_ERR + 1, "- MidRecBodyHash error1!"},
	//
	{MID_REC_FORMAT_ERR, "- MidRecFormat error0!"},
	{MID_REC_FORMAT_ERR + 1, "- MidRecFormat error1!"},
	{MID_REC_FORMAT_ERR + 2, "- MidRecFormat error2!"},
	{MID_REC_FORMAT_ERR + 3, "- MidRecFormat error3!"},
	{MID_REC_FORMAT_ERR + 4, "- MidRecFormat error4!"},
	{MID_REC_FORMAT_ERR + 5, "- MidRecFormat error5!"},
	{MID_REC_FORMAT_ERR + 6, "- MidRecFormat error6!"},
	{MID_REC_FORMAT_ERR + 7, "- MidRecFormat error7!"},
	{MID_REC_FORMAT_ERR + 8, "- MidRecFormat error8!"},
	{MID_REC_FORMAT_ERR + 9, "- MidRecFormat error9!"},	//reserved now
	{MID_REC_FORMAT_ERR + 10, "- MidRecFormat error10!"}, //reserved now
	{MID_REC_FORMAT_ERR + 11, "- MidRecFormat error11!"}, //reserved now
	{MID_REC_FORMAT_ERR + 12, "- MidRecFormat error12!"}, //reserved now
	{MID_REC_FORMAT_ERR + 13, "- MidRecFormat error13!"}, //reserved now
	{MID_REC_FORMAT_ERR + 14, "- MidRecFormat error14!"}, //reserved now
	{MID_REC_FORMAT_ERR + 15, "- MidRecFormat error15!"}, //reserved now
	//
	{LAST_REC_PREV_HEADER_HASH_ERR, "- LastRecPrevHeaderHash error0!"},
	{LAST_REC_PREV_HEADER_HASH_ERR + 1, "- LastRecPrevHeaderHash error1!"},
	//
	{LAST_REC_BODY_HASH_ERR, "- LastRecBodyHash error0!"},
	{LAST_REC_BODY_HASH_ERR + 1, "- LastRecBodyHash error1!"},
	//
	{LAST_REC_CUR_HEADER_HASH_ERR, "- LastRecCurHeaderHash error0!"},
	{LAST_REC_CUR_HEADER_HASH_ERR + 1, "- LastRecCurHeaderHash error1!"},
	//
	{LAST_REC_FORMAT_ERR, "- LastRecFormat error0!"},
	{LAST_REC_FORMAT_ERR + 1, "- LastRecFormat error1!"},
	{LAST_REC_FORMAT_ERR + 2, "- LastRecFormat error2!"},
	{LAST_REC_FORMAT_ERR + 3, "- LastRecFormat error3!"},
	{LAST_REC_FORMAT_ERR + 4, "- LastRecFormat error4!"},
	{LAST_REC_FORMAT_ERR + 5, "- LastRecFormat error5!"},
	{LAST_REC_FORMAT_ERR + 6, "- LastRecFormat error6!"},
	{LAST_REC_FORMAT_ERR + 7, "- LastRecFormat error7!"},
	{LAST_REC_FORMAT_ERR + 8, "- LastRecFormat error8!"},
	{LAST_REC_FORMAT_ERR + 9, "- LastRecFormat error9!"},   //reserved now
	{LAST_REC_FORMAT_ERR + 10, "- LastRecFormat error10!"}, //reserved now
	{LAST_REC_FORMAT_ERR + 11, "- LastRecFormat error11!"}, //reserved now
	{LAST_REC_FORMAT_ERR + 12, "- LastRecFormat error12!"}, //reserved now
	{LAST_REC_FORMAT_ERR + 13, "- LastRecFormat error13!"}, //reserved now
	{LAST_REC_FORMAT_ERR + 14, "- LastRecFormat error14!"}, //reserved now
	{LAST_REC_FORMAT_ERR + 15, "- LastRecFormat error15!"}, //reserved now
	//
	{LAST_REC_SEQ_SIGN_ERR, "- LastRecSeqSign error0!"},
	{LAST_REC_SEQ_SIGN_ERR + 1, "- LastRecSeqSign error1!"},
	{LAST_REC_SEQ_SIGN_ERR + 2, "- LastRecSeqSign error2!"},
	{LAST_REC_SEQ_SIGN_ERR + 3, "- LastRecSeqSign error3!"},
	{LAST_REC_SEQ_SIGN_ERR + 4, "- LastRecSeqSign error4!"},
	{LAST_REC_SEQ_SIGN_ERR + 5, "- LastRecSeqSign error5!"},
	{LAST_REC_SEQ_SIGN_ERR + 6, "- LastRecSeqSign error6!"},
	{LAST_REC_SEQ_SIGN_ERR + 7, "- LastRecSeqSign error7!"},
	{LAST_REC_SEQ_SIGN_ERR + 8, "- LastRecSeqSign error8!"},
	{LAST_REC_SEQ_SIGN_ERR + 9, "- LastRecSeqSign error9!"},
	{LAST_REC_SEQ_SIGN_ERR + 10, "- LastRecSeqSign error10!"},
	{LAST_REC_SEQ_SIGN_ERR + 11, "- LastRecSeqSign error11!"},
	{LAST_REC_SEQ_SIGN_ERR + 12, "- LastRecSeqSign error12!"},
	{LAST_REC_SEQ_SIGN_ERR + 13, "- LastRecSeqSign error13!"},
	{LAST_REC_SEQ_SIGN_ERR + 14, "- LastRecSeqSign error14!"},
	{LAST_REC_SEQ_SIGN_ERR + 15, "- LastRecSeqSign error15!"},
	//
	{UNKNOWN_ERR, "- Unknown error!"}
};

enum ValKeyStrID
{
	//
	REPORT_ROOT = 0,
	REPORT_ELEMENT,
	//
	ELEMENT_HEADER,
	ELEMENT_BODY,	
	ELEMENT_SIGN,		
	//
	HEADER_PREV_HEADER_HASH,
	HEADER_BODY_HASH,	
	//
	SIGN_HEADER_PLACEMENT,
	SIGN_SEQ_LEN,
	SIGN_REC_AUTH_DATA,
	SIGN_SIGNATURE,	
	//
	SIGNATURE_INFO,
	SIGNATURE_VALUE,				
	//
	SIGNATURE_INFO_DIGEST_VALUE,
	SIGNATURE_INFO_CANONIC_METHOD,
	SIGNATURE_INFO_SIGNATURE_METHOD,
	SIGNATURE_INFO_DIGEST_METHOD,
	//
	REC_AUTH_DATA_HEADER_HASH,
	//
	X509_DATA,
	//
	X509_DATA_ISSUER_NAME,
	X509_DATA_SERIAL_NUM,
	X509_DATA_CERTIFICATE,
	//
	MAX_KEY_STR_ID = X509_DATA_CERTIFICATE + 1
};

struct ValKeyIDPair
{
	unsigned int nId;
	const char* pKeyStr;
};

static ValKeyIDPair g_ValKeyIDMap[MAX_KEY_STR_ID] = \
{
	//
	{REPORT_ROOT, "./LogReport"},
	{REPORT_ELEMENT, "./LogRecordElement"},
	//
	{ELEMENT_HEADER, "./LogRecordHeader"},
	{ELEMENT_BODY,	"./LogRecordBody"},
	{ELEMENT_SIGN, "./LogRecordSignature"},		
	//
	{HEADER_PREV_HEADER_HASH, "./LogRecordHeader/previousHeaderHash"},
	{HEADER_BODY_HASH, "./LogRecordHeader/recordBodyHash"},	
	//
	{SIGN_HEADER_PLACEMENT, "./LogRecordSignature/HeaderPlacement"},
	{SIGN_SEQ_LEN, "./LogRecordSignature/SequenceLength"},
	{SIGN_REC_AUTH_DATA, "./LogRecordSignature/RecordAuthData"},
	{SIGN_SIGNATURE, "./LogRecordSignature/Signature"},	
	//
	{SIGNATURE_INFO, "./LogRecordSignature/Signature/SignedInfo"},
	{SIGNATURE_VALUE, "./LogRecordSignature/Signature/SignatureValue"},				
	//
	{SIGNATURE_INFO_DIGEST_VALUE, "./LogRecordSignature/Signature/SignedInfo/Reference/DigestValue"},
	{SIGNATURE_INFO_CANONIC_METHOD, "./LogRecordSignature/Signature/SignedInfo/CanonicalizationMethod"},
	{SIGNATURE_INFO_SIGNATURE_METHOD, "./LogRecordSignature/Signature/SignedInfo/SignatureMethod"},
	{SIGNATURE_INFO_DIGEST_METHOD, "./LogRecordSignature/Signature/SignedInfo/Reference/DigestMethod"},
	//
	{REC_AUTH_DATA_HEADER_HASH, "./LogRecordSignature/RecordAuthData/RecordHeaderHash"},
	//
	{X509_DATA, "./LogRecordSignature/Signature/KeyInfo/X509Data"},
	//
	{X509_DATA_ISSUER_NAME, "./X509IssuerSerial/X509IssuerName"},
	{X509_DATA_SERIAL_NUM, "./X509IssuerSerial/X509SerialNumber"},
	{X509_DATA_CERTIFICATE, "./X509Certificate"}
};

#endif
