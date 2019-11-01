/****************************************************************************
Copyright (c) 2010 - 2020, Digital OristarTech Co., Ltd. All rights reserved.

ModuleName : DCI Security Log 
FileName   : DciLogSignatureCheck.h
Author     : chenjingdong@oristartech.com
Date       : 2013-07-12
Version    : v1.0
Description: a definition of the class CDciLogSignCheck, which provides
			 validating function on DCI log report.  
Others     : 
History    :

< Author >    			< Date >             < Modification >

****************************************************************************/
#ifndef DCI_LOG_XML_SIGNER_H
#define DCI_LOG_XML_SIGNER_H

#define MAX_CERT_BASE64_LEN 4096
#define MAX_CERT_CHAIN_LEN 3 //the chain of the DC certificate just only 
//has 3 levels: root, sec-level and leaf-level

enum X509SerialNumber
{
	SM_ROOT = 1,	//SM - security management
	SM_SEC_LEVEL,
	SM_LEAF		
};

enum SeqCertStatID
{
	//
	SEQ_CERT_FORMAT = 0,
	SEQ_CERT_CHAIN,
	SEQ_CERT_TIME,
	//
	MAX_SEQ_CERT_STAT_ID
};

struct SeqCertStatDesc
{
	unsigned int nStatIndex;
	const char* pStatDesc;
};

static SeqCertStatDesc g_CertStatDescTab[MAX_SEQ_CERT_STAT_ID*MAX_STAT_NUMS] = \
{
	//Unknown list
	{CHECK_UNKNOWN*MAX_SEQ_CERT_STAT_ID+SEQ_CERT_FORMAT, "- The verified cert format of the X509Data .......unknown!"},													  
	{CHECK_UNKNOWN*MAX_SEQ_CERT_STAT_ID+SEQ_CERT_CHAIN, "- The verified certificate chain .................unknown!"},							 
	{CHECK_UNKNOWN*MAX_SEQ_CERT_STAT_ID+SEQ_CERT_TIME, "- The time of certificate.........................unknown!"},
	//Error list
	{CHECK_ERR*MAX_SEQ_CERT_STAT_ID+SEQ_CERT_FORMAT, "- The verified cert format of the X509Data ...........err!"},												  
	{CHECK_ERR*MAX_SEQ_CERT_STAT_ID+SEQ_CERT_CHAIN, "- The verified certificate chain .....................err!"},
	{CHECK_ERR*MAX_SEQ_CERT_STAT_ID+SEQ_CERT_TIME, "- The time of certificate.........................invalid!"},
	//OK list
	{CHECK_OK*MAX_SEQ_CERT_STAT_ID+SEQ_CERT_FORMAT, "- The verified cert format of the X509Data ............ok!"},										     
	{CHECK_OK*MAX_SEQ_CERT_STAT_ID+SEQ_CERT_CHAIN, "- The verified certificate chain ......................ok!"},
	{CHECK_OK*MAX_SEQ_CERT_STAT_ID+SEQ_CERT_TIME, "- The time of certificate...........................valid!"},
	//Unknown1 list
	{CHECK_UNKNOWN1*MAX_SEQ_CERT_STAT_ID+SEQ_CERT_FORMAT, "- The verified cert format of the X509Data ......unknown1!"},
	{CHECK_UNKNOWN1*MAX_SEQ_CERT_STAT_ID+SEQ_CERT_CHAIN, "- The verified certificate chain ................unknown1!"},
	{CHECK_UNKNOWN1*MAX_SEQ_CERT_STAT_ID+SEQ_CERT_TIME, "- The time of certificate........................unknown1!"},
};

class CDciLogReportValidator;
struct SecInfo_st;

class CDciLogSignCheck
{
public:
	CDciLogSignCheck(CDciLogReportValidator& rOwner);
	virtual ~CDciLogSignCheck(void);

	/****FUNCTION***************************************************************
	 *		  NAME : VerifyCertChain
	 * DESCRIPTION : verify a certificate chain of the DCI SM
	 *       INPUT : CXmlNode* - a pointer to the current node.
	 *             : RecordPosition - the position of current validated record.
	 *      OUTPUT : none
	 *     RETURNS : success return true, fail return false
	 *    CAUTIONS : 
	 ****************************************************************************/
	bool VerifyCertChain(CXmlNode *pCurrentNode, RecordPosition eRecPos);

	/****FUNCTION***************************************************************
	 *		  NAME : VerifySign
	 * DESCRIPTION : verify the XML signature of DCI log report.
	 *       INPUT : CXmlNode* - a pointer to the current node.
	 *             : RecordPosition - the position of current validated record.
	 *      OUTPUT : none
	 *     RETURNS : success return true, fail return false
	 *    CAUTIONS : 
	 ****************************************************************************/
	bool VerifySign(CXmlNode *pCurrentNode, RecordPosition eRecPos);

	/****FUNCTION***************************************************************
	 *		  NAME : GetCertStatDesc
	 * DESCRIPTION : obtains a description on certificate status specified by SeqCertStatID.
	 *       INPUT : SeqCertStatID - a unique ID of the certificate status.
	 *             : CheckStatus - a unique status of the sequence certificate.
	 *      OUTPUT : none
	 *     RETURNS : const char* - a status description on sequence certificate.
	 *    CAUTIONS : 
	 ****************************************************************************/
	const char* GetCertStatDesc(SeqCertStatID eCertStatID, CheckStatus eCertStat) const;

private:
	/****FUNCTION***************************************************************
	 *		  NAME : InitSecInfo
	 * DESCRIPTION : init the member variable : m_SecInfo
	 *       INPUT : none
	 *      OUTPUT : none
	 *     RETURNS : none
	 *    CAUTIONS : 
	 ****************************************************************************/
	void InitSecInfo();

	/****FUNCTION***************************************************************
	 *		  NAME : ReleaseSecInfo
	 * DESCRIPTION : release all resources related to the member variable : m_SecInfo
	 *       INPUT : none
	 *      OUTPUT : none
	 *     RETURNS : none
	 *    CAUTIONS : 
	 ****************************************************************************/
	void ReleaseSecInfo();


private:
	CDciLogReportValidator& m_rValidator;

	//note: before exiting, release all resources related to the obj: m_SecInfo.
	SecInfo_st* m_pSecInfo;
};

#endif
