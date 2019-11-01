#ifndef DCI_LOG_RECORD_ELEMENT_H
#define DCI_LOG_RECORD_ELEMENT_H
#include "dcilogbase/DciLogRecordHeader.h"
#include "dcilogbase/DciLogRecordBody.h"
#include "dcilogbase/DciLogRecordSignature.h"
class CDciLogRecordElement
{
public:
	CDciLogRecordElement(void);
	virtual ~CDciLogRecordElement(void);
	CDciLogRecordHeader *GetRecordHeader(void);
	CDciLogRecordBody *GetRecordBody(void);
	CDciLogRecordSignature *GetRecordSignature(void);
	bool ValidateHeader(void);
	bool ValidateBody(void);
	bool ValidateSignature(void);
protected:
	CDciLogRecordHeader		*m_LogRecordHeader;
	CDciLogRecordBody		*m_LogRecordBody;
	CDciLogRecordSignature	*m_LogRecordSignature;
	char *	m_XmlBuf;
public:
	virtual const char * GetXmlString(void);
};
#endif
