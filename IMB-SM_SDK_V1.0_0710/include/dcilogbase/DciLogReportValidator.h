/****************************************************************************
Copyright (c) 2010 - 2020, Digital OristarTech Co., Ltd. All rights reserved.

ModuleName : DCI Security Log 
FileName   £ºDciLogReportValidator.h
Author     £ºchenjingdong@oristartech.com
Date       £º2013-07-12
Version    £ºv1.0
Description£ºa definition on the class CDciLogReportValidator, which validates 
			 the DCI log report   
Others     : 
History    £º

< Author >    			< Date >             < Modification >

****************************************************************************/
#ifndef DCI_LOG_REPORT_VALIDATOR_H
#define DCI_LOG_REPORT_VALIDATOR_H
#include "dcilogbase/DciLogValidatorCommon.h"

#define MAX_SEQ_NUMS 8
#define MAX_METHOD_NAME_LEN 128
#define MAX_REC_NUMS_PER_SEQ 1000000

#define IS_EXIT_ON_ERR (!m_rValidResult.bIsOk && m_rValidResult.eRunMod == EXIT_ON_ERR)
#define IS_ONE_IN_SEQ (m_rValidResult.valStat.nRecNumsInCurSeq == 1)

enum ValidMode //report type
{
	MOD_FILE = 1,	//the report validated is a file type.
	MOD_STRING	//the report validated is a string type.
};

enum OutputMode
{
	MOD_SILENT = 0,	//disable any output.
	MOD_VERBOSE	//display all information.
};

typedef enum
{
	EXIT_ON_ERR = 1,	//when an error appears, exit validation program.
	CONTINUE_ON_ERR //when an error appears, continue to run until end of program.
} Running_Mode;

enum RecordPosition
{
	FIRST_IN_REPORT = 1,	//also first in sequence.
	ONE_IN_REPORT,	//there is only one record in the report.
	LAST_IN_REPORT,	//also last in sequence.
	FIRST_IN_SEQ,
	MID_IN_SEQ,
	LAST_IN_SEQ,
	ONE_IN_LAST_SEQ //there is only one record in the last sequence.
};

struct ValStatusCode
{
	unsigned int nLoadXmlReport : 2;	//bit len is 2, so the max stat numbers is 4
	unsigned int nFirstRecBodyHash : 2;
	unsigned int nFirstRecPrevHeaderHash : 2;
	unsigned int nFirstRecFormat : 2;
	unsigned int nFirstRecSeqSign : 2;

	unsigned int nMidRecPrevHeaderHash : 2;
	unsigned int nMidRecBodyHash : 2;
	unsigned int nMidRecFormat : 2;

	unsigned int nLastRecPrevHeaderHash : 2;
	unsigned int nLastRecBodyHash : 2;
	unsigned int nLastRecCurHeaderHash : 2;
	unsigned int nLastRecFormat : 2;
	unsigned int nLastRecSeqSign : 2;
};	

struct ValErrorCode
{
	unsigned char nLoadXmlReport;
	unsigned char nFirstRecBodyHash;
	unsigned char nFirstRecPrevHeaderHash;
	unsigned char nFirstRecFormat;
	unsigned char nFirstRecSeqSign;

	unsigned char nMidRecPrevHeaderHash;
	unsigned char nMidRecBodyHash;
	unsigned char nMidRecFormat;

	unsigned char nLastRecPrevHeaderHash;
	unsigned char nLastRecBodyHash;
	unsigned char nLastRecCurHeaderHash;
	unsigned char nLastRecFormat;
	unsigned char nLastRecSeqSign;
};	

struct SeqCertStatus
{
	unsigned char nCertFmt : 2;	//if CHECK_OK, the format of certificate is ok.
	unsigned char nCertChain : 2; //if CHECK_OK, the chain of certificate is ok.
	unsigned char nCertTime : 2;	//if CHECK_OK, the time of certificate is valid.		
};

struct ValidStatus
{
	ValStatusCode statusCode;
	ValErrorCode errCode;
	unsigned int nSeqIndex;	//the index of first sequence is 1.
	unsigned int nRecIndexPerSeq;	//the index of first record contained in a sequence is 1.

	//a value of the element : SequenceLength, which records element numbers contained in the current sequence.
	unsigned int nRecNumsInCurSeq; 
	bool bIsSignedReport;
	SeqCertStatus statSeqCert; //the status of each sequence certificate

	unsigned char strCanonicalizationMethod[MAX_METHOD_NAME_LEN];
	unsigned char strSignatureMethod[MAX_METHOD_NAME_LEN];
	unsigned char strDigestMethod[MAX_METHOD_NAME_LEN];
};

struct ValidResultOfReport
{

#ifndef _NO_VALIDATION_FILTER_
	ValidResultOfReport(unsigned int eFilterID)
	{
		this->eFilterID = eFilterID;
	};

	unsigned int eFilterID;
#endif

	ValidStatus valStat;	//validation status related to certain specific record.
	bool bIsOk;	//if true, the validated report is ok.
	Running_Mode eRunMod;	
	bool bIsIgnoredMID_OK; //if true, don't display the ok status of MID_REC_*, except which is error. 
	bool bIsVerbose;	//if true, display all information.
	unsigned int nRealTotalRecNums;
	unsigned int nTotalRecNums;
	unsigned int arrRecNumsPerSeq[MAX_SEQ_NUMS];
};

class CDciLogSignCheck;
class CXmlNode;
class CXmlDocument;
class CValidationFilter;

class CDciLogReportValidator
{
//member methods
public:
	CDciLogReportValidator(ValidResultOfReport& rValidResult);
	virtual ~CDciLogReportValidator(void);

	/****FUNCTION***************************************************************
	 *		  NAME : ValidateReportByDom
	 * DESCRIPTION : deal with big XML file by DOM API
	 *       INPUT : const char * - running mode, default value is EXIT_ON_ERR. 
	 *             : ValidMode - validation mode, include MOD_FILE and MOD_STRING. 
	 *			   : Running_Mode - running mode, default value is EXIT_ON_ERR. 
	 *             : bool - if true, display all information related to the 
	 *                      validation of report, default value is true.
	 *      OUTPUT : none
	 *     RETURNS : success return true, fail return false
	 *    CAUTIONS : 
	 ****************************************************************************/
	bool ValidateReportByDom(const char * pReport, ValidMode eValMod = MOD_FILE, \
								Running_Mode eRunMod = EXIT_ON_ERR, bool bIsVerbose = true);

	/****FUNCTION***************************************************************
	 *		  NAME : ValidateReportBySax
	 * DESCRIPTION : deal with big XML file by SAX API.
	 *       INPUT : const char * - running mode, default value is EXIT_ON_ERR. 
	 *             : ValidMode - validation mode, include MOD_FILE and MOD_STRING. 
	 *			   : Running_Mode - running mode, default value is EXIT_ON_ERR. 
	 *             : bool - if true, display all information related to the 
	 *                      validation of report, default value is true.
	 *      OUTPUT : none
	 *     RETURNS : success return true, fail return false
	 *    CAUTIONS : 
	 ****************************************************************************/
	bool ValidateReportBySax(const char * pReport, ValidMode eValMod = MOD_FILE, \
								Running_Mode eRunMod = EXIT_ON_ERR, bool bIsVerbose = true);

	/****FUNCTION***************************************************************
	 *		  NAME : SetSeqSign
	 * DESCRIPTION : set the status of sequence signature
	 *       INPUT : RecordPosition - the position of current validated record. 
	 *             : CheckStatus - a check status to be set in the validation result, such as CHECK_OK.
	 *      OUTPUT : none
	 *     RETURNS : none
	 *    CAUTIONS : 
	 ****************************************************************************/
	void SetSeqSign(RecordPosition eRecPos, CheckStatus eStat);

	/****FUNCTION***************************************************************
	 *		  NAME : SetRecFormat
	 * DESCRIPTION : set the status of RecFormat.
	 *       INPUT : RecordPosition - the position of current validated record. 
	 *             : CheckStatus - a check status to be set in the validation result, such as CHECK_OK.
	 *      OUTPUT : none
	 *     RETURNS : none
	 *    CAUTIONS : 
	 ****************************************************************************/
	void SetRecFormat(RecordPosition eRecPos, CheckStatus eStat);

	/****FUNCTION***************************************************************
	 *		  NAME : SetErrIdOnSeqSign
	 * DESCRIPTION : set the error ID of sequence signature
	 *       INPUT : RecordPosition - the position of current validated record. 
	 *             : unsigned int - a check SubErrID to be set in the validation result.
	 *      OUTPUT : none
	 *     RETURNS : none
	 *    CAUTIONS : 
	 ****************************************************************************/
	void SetErrIdOnSeqSign(RecordPosition eRecPos, unsigned int nSubErrID);

	/****FUNCTION***************************************************************
	 *		  NAME : SetErrIdOnRecFormat
	 * DESCRIPTION : set the error ID of RecFormat.
	 *       INPUT : RecordPosition - the position of current validated record. 
	 *             : unsigned int - a check SubErrID to be set in the validation result.
	 *      OUTPUT : none
	 *     RETURNS : none
	 *    CAUTIONS : 
	 ****************************************************************************/
	void SetErrIdOnRecFormat(RecordPosition eRecPos, unsigned int nSubErrID);

	/****FUNCTION***************************************************************
	 *		  NAME : GetValErrDesc
	 * DESCRIPTION : obtains a description on validation error specified by ValErrorID.
	 *       INPUT : ValErrorID - a unique ID of the validation error.
	 *             : unsigned int - a sub-error ID of the validation.
	 *      OUTPUT : none
	 *     RETURNS : const char* - a description on error.
	 *    CAUTIONS : 
	 ****************************************************************************/
	const char* GetValErrDesc(ValErrorID eValErrID, unsigned int nSubErrID) const;

	/****FUNCTION***************************************************************
	 *		  NAME : GetValErrDesc
	 * DESCRIPTION : obtains a description on validation error specified by Error Code.
	 *       INPUT : unsigned int - an error code of the validation.
	 *             : 
	 *      OUTPUT : none
	 *     RETURNS : const char* - a description on error.
	 *    CAUTIONS : 
	 ****************************************************************************/
	const char* GetValErrDesc(unsigned int nErrCode) const;

	/****FUNCTION***************************************************************
	 *		  NAME : GetValKeyStr
	 * DESCRIPTION : obtains a key XML string specified by ValKeyStrID.
	 *       INPUT : ValKeyStrID - a unique ID of the validation key string.
	 *      OUTPUT : none
	 *     RETURNS : const char* - a key string associated with the specified ID.
	 *    CAUTIONS : 
	 ****************************************************************************/
	const char* GetValKeyStr(ValKeyStrID eKeyStrID) const;

private:
	/****FUNCTION***************************************************************
	 *		  NAME : GetValStatDesc
	 * DESCRIPTION : obtains a description on validation status specified by ValStatusID.
	 *       INPUT : ValStatusID - a unique ID of the validation status.
	 *             : CheckStatus - a unique status of the validation.
	 *      OUTPUT : none
	 *     RETURNS : const char* - a status description.
	 *    CAUTIONS : 
	 ****************************************************************************/
	const char* GetValStatDesc(ValStatusID eValStatID, CheckStatus eValStat) const;

	/****FUNCTION***************************************************************
	 *		  NAME : RemoveAllNodes
	 * DESCRIPTION : remove all nodes from XML tree
	 *       INPUT : CXmlNode * - a pointer to the Xml node.
	 *      OUTPUT : none
	 *     RETURNS : none
	 *    CAUTIONS : 
	 ****************************************************************************/
	void RemoveAllNodes(CXmlNode *pRootNode);

	/****FUNCTION***************************************************************
	 *		  NAME : LoadXmlReport
	 * DESCRIPTION : load all XML elements from report.
	 *       INPUT : CXmlDocument* : a pointer to the Xml Doc
	 *             : const char * : report path or report string
	 *             : ValidMode : validation mode, include MOD_FILE and MOD_STRING. 
	 *      OUTPUT : none
	 *     RETURNS : success return 0, fail return -1
	 *    CAUTIONS : 
	 ****************************************************************************/
	int LoadXmlReport(CXmlDocument *pXmlDoc, const char * pReport, ValidMode eValMod);

	/****FUNCTION***************************************************************
	 *		  NAME : InitValidResult
	 * DESCRIPTION : init validation result of report
	 *       INPUT : Running_Mode - running mode, default value is EXIT_ON_ERR. 
	 *               bool - if true, display all information related to the 
	 *                      validation of report, default value is true.
	 *      OUTPUT : none
	 *     RETURNS : none
	 *    CAUTIONS : 
	 ****************************************************************************/
	void InitValidResult(Running_Mode eRunMod = EXIT_ON_ERR, bool bIsVerbose = true);

	/****FUNCTION***************************************************************
	 *		  NAME : ResetPrevHeaderHashStat
	 * DESCRIPTION : reset the status of PrevHeaderHash
	 *       INPUT : RecordPosition - the position of current validated record. 
	 *      OUTPUT : none
	 *     RETURNS : none
	 *    CAUTIONS : 
	 ****************************************************************************/
	void ResetPrevHeaderHashStat(RecordPosition eRecPos);

	/****FUNCTION***************************************************************
	 *		  NAME : ResetBodyHashStat
	 * DESCRIPTION : reset the status of BodyHash
	 *       INPUT : RecordPosition - the position of current validated record. 
	 *      OUTPUT : none
	 *     RETURNS : none
	 *    CAUTIONS : 
	 ****************************************************************************/
	void ResetBodyHashStat(RecordPosition eRecPos);

	/****FUNCTION***************************************************************
	 *		  NAME : ResetSeqSignStat
	 * DESCRIPTION : reset the status of SequenceSignature
	 *       INPUT : RecordPosition - the position of current validated record. 
	 *      OUTPUT : none
	 *     RETURNS : none
	 *    CAUTIONS : 
	 ****************************************************************************/
	void ResetSeqSignStat(RecordPosition eRecPos);

	/****FUNCTION***************************************************************
	 *		  NAME : ResetLastRecCurHeaderHash
	 * DESCRIPTION : reset the status of LastRecCurHeaderHash
	 *       INPUT : none
	 *      OUTPUT : none
	 *     RETURNS : none
	 *    CAUTIONS : 
	 ****************************************************************************/
	void ResetLastRecCurHeaderHash();

	/****FUNCTION***************************************************************
	 *		  NAME : SetLastRecCurHeaderHash
	 * DESCRIPTION : set the status of LastRecCurHeaderHash.
	 *       INPUT : CheckStatus - a check status to be set in the validation result, such as CHECK_OK.
	 *      OUTPUT : none
	 *     RETURNS : none
	 *    CAUTIONS : 
	 ****************************************************************************/
	void SetLastRecCurHeaderHash(CheckStatus eStat);

	/****FUNCTION***************************************************************
	 *		  NAME : SetPrevHeaderHash
	 * DESCRIPTION : set the status of PrevHeaderHash.
	 *       INPUT : RecordPosition - the position of current validated record. 
	 *             : CheckStatus - a check status to be set in the validation result, such as CHECK_OK.
	 *      OUTPUT : none
	 *     RETURNS : none
	 *    CAUTIONS : 
	 ****************************************************************************/
	void SetPrevHeaderHash(RecordPosition eRecPos, CheckStatus eStat);

	/****FUNCTION***************************************************************
	 *		  NAME : SetBodyHash
	 * DESCRIPTION : set the status of BodyHash
	 *       INPUT : RecordPosition - the position of current validated record. 
	 *             : CheckStatus - a check status to be set in the validation result, such as CHECK_OK.
	 *      OUTPUT : none
	 *     RETURNS : none
	 *    CAUTIONS : 
	 ****************************************************************************/
	void SetBodyHash(RecordPosition eRecPos, CheckStatus eStat);

	/****FUNCTION***************************************************************
	 *		  NAME : SetErrIdOnCurHeaderHash
	 * DESCRIPTION : set the error ID of LastRecCurHeaderHash.
	 *       INPUT : unsigned int - a check SubErrID to be set in the validation result.
	 *      OUTPUT : none
	 *     RETURNS : none
	 *    CAUTIONS : 
	 ****************************************************************************/
	void SetErrIdOnCurHeaderHash(unsigned int nSubErrID);

	/****FUNCTION***************************************************************
	 *		  NAME : SetErrIdOnPrevHeaderHash
	 * DESCRIPTION : set the error ID of PrevHeaderHash.
	 *       INPUT : RecordPosition - the position of current validated record. 
	 *			   : unsigned int - a check SubErrID to be set in the validation result.
	 *      OUTPUT : none
	 *     RETURNS : none
	 *    CAUTIONS : 
	 ****************************************************************************/
	void SetErrIdOnPrevHeaderHash(RecordPosition eRecPos, unsigned int nSubErrID);

	/****FUNCTION***************************************************************
	 *		  NAME : SetErrIdOnBodyHash
	 * DESCRIPTION : set the error ID of BodyHash
	 *       INPUT : RecordPosition - the position of current validated record. 
	 *             : unsigned int - a check SubErrID to be set in the validation result.
	 *      OUTPUT : none
	 *     RETURNS : none
	 *    CAUTIONS : 
	 ****************************************************************************/
	void SetErrIdOnBodyHash(RecordPosition eRecPos, unsigned int nSubErrID);

	/****FUNCTION***************************************************************
	 *		  NAME : CheckRecHashValue
	 * DESCRIPTION : check the hash value related to record
	 *       INPUT : const char* - a hash value, which had been saved in the validated report.
	 *             : CXmlNode * - a node contained relevant hashed sub-nodes.
	 *      OUTPUT : none
	 *     RETURNS : success return true, fail return false
	 *    CAUTIONS : 
	 ****************************************************************************/
	bool CheckRecHashValue(const char* pSavedHashValue, CXmlNode * pHashNode);

	/****FUNCTION***************************************************************
	 *		  NAME : CheckRecBodyHash
	 * DESCRIPTION : check recordBodyHash
	 *       INPUT : CXmlNode - the current node.
	 *             : RecordPosition - the position of current validated record. 
	 *      OUTPUT : none
	 *     RETURNS : success return true, fail return false
	 *    CAUTIONS : 
	 ****************************************************************************/
	bool CheckRecBodyHash(CXmlNode * pCurrentNode, RecordPosition eRecPos);

	/****FUNCTION***************************************************************
	 *		  NAME : CheckRecPrevHeaderHash
	 * DESCRIPTION : check previousHeaderHash
	 *       INPUT : CXmlNode* - the previous node.
	 *             : CXmlNode* - the current node.
	 *             : RecordPosition - the position of current validated record. 
	 *      OUTPUT : none
	 *     RETURNS : success return true, fail return false
	 *    CAUTIONS : 
	 ****************************************************************************/
	bool CheckRecPrevHeaderHash(CXmlNode * pPreviousNode, CXmlNode * pCurrentNode, RecordPosition eRecPos);

	/****FUNCTION***************************************************************
	 *		  NAME : CheckRecCurHeaderHash
	 * DESCRIPTION : check the currentHeaderHash of record
	 *       INPUT : CXmlNode* - the current node.
	 *      OUTPUT : none
	 *     RETURNS : success return true, fail return false
	 *    CAUTIONS : 
	 ****************************************************************************/
	bool CheckRecCurHeaderHash(CXmlNode * pCurrentNode);

	/****FUNCTION***************************************************************
	 *		  NAME : CheckSignature
	 * DESCRIPTION : check the signature
	 *       INPUT : CXmlNode* - the current node.
	 *             : RecordPosition - the position of current validated record. 
	 *      OUTPUT : none
	 *     RETURNS : success return true, fail return false
	 *    CAUTIONS : 
	 ****************************************************************************/
	bool CheckSignature(CXmlNode * pCurrentNode, RecordPosition eRecPos);

	/****FUNCTION***************************************************************
	 *		  NAME : CheckSignedValue
	 * DESCRIPTION : check the value of signature
	 *       INPUT : CXmlNode* - the current node.
	 *      OUTPUT : none
	 *     RETURNS : success return true, fail return false
	 *    CAUTIONS : 
	 ****************************************************************************/
	bool CheckSignedValue(CXmlNode * pCurrentNode, RecordPosition eRecPos);

	/****FUNCTION***************************************************************
	 *		  NAME : CheckRecordSignature
	 * DESCRIPTION : check RecordSignature
	 *       INPUT : CXmlNode* - the current node.
	 *             : RecordPosition - the position of current validated record. 
	 *      OUTPUT : none
	 *     RETURNS : success return true, fail return false
	 *    CAUTIONS : 
	 ****************************************************************************/
	bool CheckRecordSignature(CXmlNode * pCurrentNode, RecordPosition eRecPos);

	/****FUNCTION***************************************************************
	 *		  NAME : CheckRecHashedNode
	 * DESCRIPTION : check the hashed node of record
	 *       INPUT : CXmlNode* - the previous node.
	 *             : CXmlNode* - the current node.
	 *             : RecordPosition - the position of current validated record. 
	 *      OUTPUT : none
	 *     RETURNS : success return true, fail return false
	 *    CAUTIONS : 
	 ****************************************************************************/
	bool CheckRecHashedNode(CXmlNode * pPreviousNode, CXmlNode * pCurrentNode, RecordPosition eRecPos);

	/****FUNCTION***************************************************************
	 *		  NAME : CheckFirstRecInSeq
	 * DESCRIPTION : check the first record in sequence or in report.
	 *       INPUT : CXmlNode* - the previous node.
	 *             : CXmlNode* - the current node.
	 *             : RecordPosition - the position of current validated record. 
	 *      OUTPUT : none
	 *     RETURNS : success return true, fail return false
	 *    CAUTIONS : 
	 ****************************************************************************/
	bool CheckFirstRecInSeq(CXmlNode * pPreviousNode, CXmlNode * pCurrentNode, RecordPosition eRecPos);

	/****FUNCTION***************************************************************
	 *		  NAME : CheckLastRecInReport
	 * DESCRIPTION : check the last record in report.
	 *       INPUT : CXmlNode* - the previous node.
	 *             : CXmlNode* - the current node.
	 *             : RecordPosition - the position of current validated record. 
	 *      OUTPUT : none
	 *     RETURNS : success return true, fail return false.
	 *    CAUTIONS : 
	 ****************************************************************************/
	bool CheckLastRecInReport(CXmlNode * pPreviousNode, CXmlNode * pCurrentNode, RecordPosition eRecPos);

	/****FUNCTION***************************************************************
	 *		  NAME : CheckNonLastRecInReport
	 * DESCRIPTION : check the element, which is not a last record of report
	 *       INPUT : CXmlNode* - the previous node.
	 *             : CXmlNode* - the current node.
	 *             : RecordPosition - the position of current validated record. 
	 *      OUTPUT : none
	 *     RETURNS : success return true, fail return false
	 *    CAUTIONS : 
	 ****************************************************************************/
	bool CheckNonLastRecInReport(CXmlNode * pPreviousNode, CXmlNode * pCurrentNode, RecordPosition& rRecPos);

	/****FUNCTION***************************************************************
	 *		  NAME : PrintStat_FIRST_IN_REPORT
	 * DESCRIPTION : print validation status on the FIRST_IN_REPORT record.
	 *       INPUT : none 
	 *      OUTPUT : none
	 *     RETURNS : success return true, fail return false
	 *    CAUTIONS : 
	 ****************************************************************************/
	bool PrintStat_FIRST_IN_REPORT();

	/****FUNCTION***************************************************************
	 *		  NAME : PrintStat_FIRST_IN_SEQ
	 * DESCRIPTION : print validation status on the FIRST_IN_SEQ record.
	 *       INPUT : none 
	 *      OUTPUT : none
	 *     RETURNS : success return true, fail return false
	 *    CAUTIONS : 
	 ****************************************************************************/
	bool PrintStat_FIRST_IN_SEQ();

	/****FUNCTION***************************************************************
	 *		  NAME : PrintStat_MID_IN_SEQ
	 * DESCRIPTION : print validation status on the MID_IN_SEQ record.
	 *       INPUT : none 
	 *      OUTPUT : none
	 *     RETURNS : success return true, fail return false
	 *    CAUTIONS : 
	 ****************************************************************************/
	bool PrintStat_MID_IN_SEQ();

	/****FUNCTION***************************************************************
	 *		  NAME : PrintStat_LAST_IN_SEQ
	 * DESCRIPTION : print validation status on the LAST_IN_SEQ record.
	 *       INPUT : none 
	 *      OUTPUT : none
	 *     RETURNS : success return true, fail return false
	 *    CAUTIONS : 
	 ****************************************************************************/
	bool PrintStat_LAST_IN_SEQ();

	/****FUNCTION***************************************************************
	 *		  NAME : PrintStat_LAST_IN_REPORT
	 * DESCRIPTION : print validation status on the LAST_IN_REPORT record.
	 *       INPUT : none 
	 *      OUTPUT : none
	 *     RETURNS : none
	 *    CAUTIONS : 
	 ****************************************************************************/
	void PrintStat_LAST_IN_REPORT();

	/****FUNCTION***************************************************************
	 *		  NAME : DisplayValidStat
	 * DESCRIPTION : check the validation status of report
	 *       INPUT : RecordPosition - the position of current validated record. 
	 *      OUTPUT : none
	 *     RETURNS : none
	 *    CAUTIONS : 
	 ****************************************************************************/
	void DisplayValidStat(RecordPosition eRecPos);

//member variables
public:
	ValidResultOfReport& m_rValidResult;

private:
	CXmlNode		*m_RootNode;
	CXmlDocument	*m_XmlDoc;

	CDciLogSignCheck* m_pSignChecker;

#ifndef _NO_VALIDATION_FILTER_
	CValidationFilter *m_pValFilter;
#endif

};

#endif
