/****************************************************************************
Copyright (c) 2010 - 2020, Digital OristarTech Co., Ltd. All rights reserved.

ModuleName : DCI Security Log 
FileName   £ºDciLogClsSecurity.h
Author     £ºchenjingdong@oristartech.com
Date       £º2013-03-09
Version    £º v1.0
Description£ºDCI Security Log class definition on event security class   
Others     : 
History    £º

< Author >    			< Date >             < Modification >

****************************************************************************/
#ifndef DCI_LOG_CLS_SECURITY_H
#define DCI_LOG_CLS_SECURITY_H

#include "dcilogs/DciLog.h"

class CDciLogClsSecurity :
	public CDciLog
{
public:
	enum
	{
		SEC_UNKNOWN = CDciLog::DCI_SECURITY + 1, //DCI_SECURITY + 1 is a base number of Security Class.
		SEC_PLAYOUT,
		SEC_VALIDATION,
		SEC_KEY,
		SEC_ASM,
		SEC_OPERATIONS,
		SEC_TICKET
	};

public:
	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] modified by chenjingdong, 2013-05-17 start 
	/* CDciLogClsSecurity(void); */

	CDciLogClsSecurity(CDciLogRecordHeader::LogOutputMode eOutputMod = CDciLogRecordHeader::DCI_LOG_NORMAL);
	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] end
};

#endif
