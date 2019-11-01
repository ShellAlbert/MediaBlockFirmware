/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  DCI Security Log 
FileName   £º DciLog.h
Author     £º majingshan@dadimedia.com
Date       £º 
Version    £º v1.0
Description£º DCI Security Log class definition
Others     :  
History    £º 
< Author >    			< Date >             < Modification >
cuijixin@dadimedia.com   10/09/13              Add comment
********************************************/
#ifndef DCI_LOG_H
#define DCI_LOG_H
#include "dcilogbase/DciLogRecord.h"
#include "dcilogbase/DciLogReport.h"
#include <string>
class CDciLog
{
public:
	typedef enum
	{
		CPLFormatError,
		CertFormatError,
		AssetHashError,
		AssetMissingError,
		SignatureError,
		KDMFormatError,
		CheckValueError,
		FrameMICError,
		FrameSequenceError,
		TrackFileIDError,
		ContentAuthenticatorError,
		TDLError,
		KeyTypeError,
		ValidityWindowError,
		TLSError,
		UnknownError,
		QuerySPBError,
		QuerySPBAlert,
		ASMMessageError,
		ASMLogRequestFailed,
		SoftwareFailure,
		AdjustmentRangeError,
	}DciLogException;
	typedef enum {CertThumbprint, DeviceUID} DeviceIdType;
	//[SecTermSM_v1.0_DCEventLog] added by chenjingdong, 2013-03-11 start
	//make sure each event class has a unique sequence number.  
	enum
	{
		DCI_UNKNOWN = 0,
		DCI_SECURITY = 1,
		DCI_OPERATIONAL = 200,
		DCI_HEALTH = 300,
		DCI_MAINTENANCE = 400,
		DCI_DEBUG = 500
	};
	//[SecTermSM_v1.0_DCEventLog] end
public:
	/****FUNCTION***************************************************
	*		 NAME : LoadXmlLog
	* DESCRIPTION : Load xml log file
	*       INPUT : strXmlDciLog : xml log file string
	*      OUTPUT : NULL
	*     RETURNS : true success; false fail
	*    CAUTIONS : 
	****************************************************************/
	virtual bool LoadXmlLog(const char *strXmlDciLog);
	
	/****FUNCTION***************************************************
	*		 NAME : AppendToSequence
	* DESCRIPTION : Append log record to log sequence
	*       INPUT : pLogSequence : Log sequence which log record should be append to
	*      OUTPUT : NULL
	*     RETURNS : true success; false fail
	*    CAUTIONS : 
	****************************************************************/
	bool AppendToSequence(CDciLogRecordSequence *pLogSequence);

	virtual ~CDciLog();
	
	/****FUNCTION***************************************************
	*		 NAME : CDciLog
	* DESCRIPTION : Constructor function of CDciLog class
	*       INPUT : NULL
	*      OUTPUT : NULL
	*     RETURNS : NULL
	*    CAUTIONS : 
	****************************************************************/
	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] modified by chenjingdong, 2013-05-17 start 
	/* CDciLog(void); */

	CDciLog(CDciLogRecordHeader::LogOutputMode eOutputMod = CDciLogRecordHeader::DCI_LOG_NORMAL);
	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] end
	
	/****FUNCTION***************************************************
	*		 NAME : Validate
	* DESCRIPTION : Validate the xml header, xml body, xml signature
	*       INPUT : NULL
	*      OUTPUT : NULL
	*     RETURNS : invalid header,return DCI_LOG_INVALID_HEADER;invalid body, return DCI_LOG_INVALID_BODY;
	*				invalid xml signature, return DCI_LOG_INVALID_SIGNATURE; success return DCI_LOG_SUCCESS
	*    CAUTIONS : 
	****************************************************************/
	virtual int Validate(void);

	/****FUNCTION***************************************************
	*		 NAME : GetHeaderHash
	* DESCRIPTION : Getthe xml header's hash value
	*       INPUT : NULL
	*      OUTPUT : strHeaderHash : xml header's hash value string
	*     RETURNS : success return true; fail return false
	*    CAUTIONS : 
	****************************************************************/
	bool GetHeaderHash(std::string &strHeaderHash);

	/****FUNCTION***************************************************
	*		 NAME : GetBodyHash
	* DESCRIPTION : Getthe xml body's hash value
	*       INPUT : NULL
	*      OUTPUT : strBodyHash : xml body's hash value string
	*     RETURNS : success return true; fail return false
	*    CAUTIONS : 
	****************************************************************/
	bool GetBodyHash(std::string &strBodyHash);

	/****FUNCTION***************************************************
	*		 NAME : GetHeaderHashNodeValue
	* DESCRIPTION : Get the xml previous header's hash value
	*       INPUT : NULL
	*      OUTPUT : strHeaderHash : xml header's hash value string
	*     RETURNS : success return true; fail return false
	*    CAUTIONS : 
	****************************************************************/
	bool GetHeaderHashNodeValue(std::string &strHeaderHash);

	/****FUNCTION***************************************************
	*		 NAME : GetBodyHashNodeValue
	* DESCRIPTION : Get the record xml body's hash value
	*       INPUT : NULL
	*      OUTPUT : strHeaderHash : xml body's hash value string
	*     RETURNS : success return true; fail return false
	*    CAUTIONS : 
	****************************************************************/
	bool GetBodyHashNodeValue(std::string &strBodyHash);

	/****FUNCTION***************************************************
	*		 NAME : GetRecordString
	* DESCRIPTION : Get the xml record string
	*       INPUT : NULL
	*      OUTPUT : NULL
	*     RETURNS : success return point to the record string; fail return NULL
	*    CAUTIONS : 
	****************************************************************/
	const char *GetRecordString(void);
	/*set header info*/
	/****FUNCTION***************************************************
	*		 NAME : SetTimeStamp
	* DESCRIPTION : Set the record xml header's time stamp
	*       INPUT : strTimeStamp : time stamp
	*      OUTPUT : NULL
	*     RETURNS : success return true; fail return false
	*    CAUTIONS : 
	****************************************************************/
	bool SetTimeStamp(const char *strTimeStamp);

	/****FUNCTION***************************************************
	*		 NAME : GetTimeStamp
	* DESCRIPTION : Get the record xml header's time stamp
	*       INPUT : NULL
	*      OUTPUT : NULL
	*     RETURNS : success return time stamp; fail return NULL
	*    CAUTIONS : 
	****************************************************************/
	const char *GetTimeStamp(void);

	/****FUNCTION***************************************************
	*		 NAME : SetDeviceSourceID
	* DESCRIPTION : Set the Device Source ID
	*       INPUT : strPrimaryID    : primary id
	*				primaryIDType   : primary id type
	*               strSecondaryID  : secondary id
	*               secondaryIDType : secondary id type
	*      OUTPUT : NULL
	*     RETURNS : success return true; fail return false
	*    CAUTIONS : 
	****************************************************************/
	bool SetDeviceSourceID(const char *strPrimaryID, DeviceIdType primaryIDType, const char *strSecondaryID = NULL, DeviceIdType secondaryIDType = CertThumbprint);

	/****FUNCTION***************************************************
	*		 NAME : SetPreviousHeaderHash
	* DESCRIPTION : Set the previous header hash
	*       INPUT : strHeaderHash : string pointer to header hash
	*      OUTPUT : NULL
	*     RETURNS : success return true; fail return false
	*    CAUTIONS : 
	****************************************************************/
	bool SetPreviousHeaderHash(const char *strHeaderHash);

	/****FUNCTION***************************************************
	*		 NAME : SetEventSequence
	* DESCRIPTION : Set the event sequence 
	*       INPUT : strEventSequence : string pointer to Event Sequence
	*      OUTPUT : NULL
	*     RETURNS : success return true; fail return false
	*    CAUTIONS : 
	****************************************************************/
	bool SetEventSequence(const char *strEventSequence);

	/****FUNCTION***************************************************
	*		 NAME : SetContentID
	* DESCRIPTION : Set content id 
	*       INPUT : strContentID : string pointer to Content ID
	*      OUTPUT : NULL
	*     RETURNS : success return true; fail return false
	*    CAUTIONS : 
	****************************************************************/
	virtual bool SetContentID(const char *strContentID);
	/*set body info*/
	/****FUNCTION***************************************************
	*		 NAME : AddParameter
	* DESCRIPTION : Add Parameter to the xml record body
	*       INPUT : strName          : Parameter name;
	*				strValue         : Parameter value;
	*               strNameScope     : Parameter name scope;
	*               strValueAttrName : Parameter attribute name;
	*               strValueAttrVal  : Parameter attribute value
	*      OUTPUT : NULL
	*     RETURNS : success return true; fail return false
	*    CAUTIONS : 
	****************************************************************/
	virtual bool AddParameter(const char *strName, const char *strValue, const char *strNameScope = NULL, const char *strValueAttrName = NULL, const char *strValueAttrVal = NULL);
	
	/****FUNCTION***************************************************
	*		 NAME : AddException
	* DESCRIPTION : Add a exception
	*       INPUT : exception        : exception name;
	*               strValue         : exception value;
	*               strNameScope     : exception name scope
	*               strValueAttrName : exception attribute name
	*               strValueAttrVal  : exception attribute value
	*      OUTPUT : NULL
	*     RETURNS : success return true; fail return false
	*    CAUTIONS : 
	****************************************************************/
	bool AddException(DciLogException exception, const char *strValue, const char *strNameScope = NULL, const char *strValueAttrName = "xsi:type", const char *strValueAttrVal = "xs:string");
	
	/****FUNCTION***************************************************
	*		 NAME : AddReferencedID
	* DESCRIPTION : Add a Referenced ID
	*       INPUT : strName      : Referenced ID name;
	*               strValue     : Referenced ID value;
	*               strNameScope : Referenced name scope;
	*      OUTPUT : NULL
	*     RETURNS : success return true; fail return false
	*    CAUTIONS : 
	****************************************************************/
	virtual bool AddReferencedID(const char *strName, const char *strValue, const char *strNameScope = NULL);
	
	/****FUNCTION***************************************************
	*		 NAME : SetRecordExtensionID
	* DESCRIPTION : Set Record Extension ID
	*       INPUT : strID : Record Extension ID;
	*      OUTPUT : NULL
	*     RETURNS : success return true; fail return false
	*    CAUTIONS : 
	****************************************************************/	
	bool SetRecordExtensionID(const char * strID);

	/****FUNCTION***************************************************
	*		 NAME : SetRecordTextExtension
	* DESCRIPTION : Set the Record Text Extension
	*       INPUT : strTextID              : Record Text ID name;
	*               strDescription         : Description value;
	*               strDescriptionLanguage : Description Language;
	*      OUTPUT : NULL
	*     RETURNS : success return true; fail return false
	*    CAUTIONS : 
	****************************************************************/
	bool SetRecordTextExtension(const char *strTextID, const char *strDescription, const char *strDescriptionLanguage = NULL);
	
	/****FUNCTION***************************************************
	*		 NAME : GetDciDeviceDescription
	* DESCRIPTION : Get the DCI device description
	*       INPUT : NULL
	*      OUTPUT : NULL
	*     RETURNS : success return a pointer to the DciDeviceDescription; fail return NULL
	*    CAUTIONS : 
	****************************************************************/	
	CDciDeviceDescription *GetDciDeviceDescription(void);
	/*set signature info*/

	/****FUNCTION***************************************************
	*		 NAME : SetHeaderPlacement
	* DESCRIPTION : Set Header Placement node value
	*       INPUT : headerPlacement socpe start\stop
	*      OUTPUT : NULL
	*     RETURNS : success return true; fail return false
	*    CAUTIONS : 
	****************************************************************/
	bool SetHeaderPlacement(CDciLogRecordSignature::HeaderPlacement headerPlacement);

	/****FUNCTION***************************************************
	*		 NAME : SetSequenceLength
	* DESCRIPTION : Set SequenceLength node value
	*       INPUT : iSequenceLength : Sequence Length
	*      OUTPUT : NULL
	*     RETURNS : success return true; fail return false
	*    CAUTIONS : 
	****************************************************************/
	bool SetSequenceLength(int iSequenceLength);

	/****FUNCTION***************************************************
	*		 NAME : SetRecordAuthData
	* DESCRIPTION : Set RecordAuthData node value
	*       INPUT : strHeaderHash       : header's hash value
	*               strAuthDataID       : AuthData ID
	*               strX509IssuerName   : X509 certificate issuer name
	*               strX509SerialNumber : X509 certificate serial number
	*      OUTPUT : NULL
	*     RETURNS : success return true; fail return false
	*    CAUTIONS : 
	****************************************************************/
	bool SetRecordAuthData(const char *strHeaderHash, const char *strAuthDataID, const char *strX509IssuerName, const char *strX509SerialNumber);
	
	/****FUNCTION***************************************************
	*		 NAME : GetDsigSignature
	* DESCRIPTION : Get the Dsig signature
	*       INPUT : NULL
	*      OUTPUT : NULL
	*     RETURNS : success return a pointer to a CDsigSignature object; fail return NULL
	*    CAUTIONS : 
	****************************************************************/
	CDsigSignature * GetDsigSignature(void);

	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] added by chenjingdong, 2013-05-17 start
	/****FUNCTION***************************************************
	*		 NAME : GetOutputModeByHeader
	* DESCRIPTION : obtains output mode from the record header
	*       INPUT : NULL
	*      OUTPUT : NULL
	*     RETURNS : CDciLogRecordHeader::LogOutputMode
	*    CAUTIONS : 
	****************************************************************/
	CDciLogRecordHeader::LogOutputMode GetOutputModeByHeader() const 
	{
		return m_LogRecord ? m_LogRecord->GetOutputModeByHeader() : CDciLogRecordHeader::DCI_LOG_NORMAL; 
	};

	/****FUNCTION***************************************************
	*		 NAME : GetOutputModeByBody
	* DESCRIPTION : obtains output mode from the record body
	*       INPUT : NULL
	*      OUTPUT : NULL
	*     RETURNS : CDciLogRecordHeader::LogOutputMode
	*    CAUTIONS : 
	****************************************************************/
	//CDciLogRecordHeader::LogOutputMode GetOutputModeByBody() const
	//{
	//	return m_LogRecord ? m_LogRecord->GetOutputModeByBody() : CDciLogRecordHeader::DCI_LOG_NORMAL;
	//};
	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] end

protected:
	CDciLogRecord *m_LogRecord;		//DCI log record 
};

#endif
