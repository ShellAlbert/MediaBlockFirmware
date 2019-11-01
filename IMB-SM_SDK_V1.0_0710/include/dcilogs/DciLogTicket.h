/****************************************************************************
Copyright (c) 2010 - 2020, Digital OristarTech Co., Ltd. All rights reserved.

ModuleName : DCI Security Log 
FileName   £ºDciLogTicket.h
Author     £ºchenjingdong@oristartech.com
Date       £º2013-03-13
Version    £º v1.0
Description£ºDCI Security Log class definition on ticket event   
Others     : 
History    £º

< Author >    			< Date >             < Modification >

****************************************************************************/
#ifndef DCI_LOG_TICKET_H
#define DCI_LOG_TICKET_H

#include "dcilogs/DciLogClsSecurity.h"

//At present, there are only two kinds of ticket operations : sale ticket and revoke ticket.
enum TicketEventSubType
{
	TICKET_UNKNOWN = CDciLogClsSecurity::SEC_TICKET + 1, //SEC_TICKET + 1 is a base number of TicketEventSubType.
	SPB_SALE_TICKET,
	SPB_REVOKE_TICKET
};

//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] modified by chenjingdong, 2013-05-17 start
/* #define PARAMETER_NUMS 11 */

#define MAX_PARA_VALUE_LEN 32
#define MAX_REC_VALUE_LEN 256

enum TicketParaToken
{
	TRADE_ID = 0,
	CINEMA_CODE,
	FILM_CODE,
	HALL_CODE,
	SEAT_CODE,
	SHOW_DATE,
	SHOW_TIME,
	SHOW_SEQUENCE,
	TICKET_PRICE,
	TICKET_TYPE,
	TICKET_CODE,
	ADVANCE,
	//
	PARAMETER_NUMS
};
struct TicketPara
{
	TicketParaToken eParaIndex;
	const char* pParaName; 
};
static TicketPara arrParaNameList[PARAMETER_NUMS] = \
{
	{TRADE_ID, "TradeID"},
	{CINEMA_CODE, "CinemaCode"},
	{FILM_CODE, "FilmCode"},
	{HALL_CODE, "HallCode"},
	{SEAT_CODE, "SeatCode"},
	{SHOW_DATE, "ShowDate"},
	{SHOW_TIME, "ShowTime"},
	{SHOW_SEQUENCE, "ShowSequence"},
	{TICKET_PRICE, "TicketPrice"},
	{TICKET_TYPE, "TicketType"},
	{TICKET_CODE, "TicketCode"},
	{ADVANCE, "Advance"}
};
//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] end 

class CDciLogTicket :
	public CDciLogClsSecurity
{
public:

	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] modified by chenjingdong, 2013-05-17 start 
	/* CDciLogTicket(TicketEventSubType eEvtSubType = TICKET_UNKNOWN); */

	CDciLogTicket(TicketEventSubType eEvtSubType = TICKET_UNKNOWN, \
		CDciLogRecordHeader::LogOutputMode eOutputMod = CDciLogRecordHeader::DCI_LOG_NORMAL);
	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] end

	virtual ~CDciLogTicket();

	/****FUNCTION***************************************************************
	*		 NAME : Validate
	* DESCRIPTION : validate log parameter 
	*       INPUT : null
	*      OUTPUT : null
	*     RETURNS : success return DCI_LOG_SUCCESS, fail return error number
	*    CAUTIONS : 
	****************************************************************************/
	virtual int Validate(void);
	
	/****FUNCTION***************************************************************
	*		 NAME : AddParameter
	* DESCRIPTION : Add Parameter to the Xml file
	*       INPUT : strName : Parameter name
	*               strValue : Parameter value
	*               strNameScope : Parameter name scope
	*               strValueAttrName : Parameter value attribute name
	*               strValueAttrVal : Parameter value attribute value
	*      OUTPUT : null
	*     RETURNS : success return true, fail return false
	*    CAUTIONS : 
	****************************************************************************/
	virtual bool AddParameter(const char *strName, const char *strValue, const char *strNameScope = NULL, \
										const char *strValueAttrName = NULL, const char *strValueAttrVal = NULL);

	/****FUNCTION***************************************************************
	*		 NAME : GetAddParaCounts
	* DESCRIPTION : obtains the numbers of parameter 
	*       INPUT : null
	*      OUTPUT : null
	*     RETURNS : return the counts adding parameter successfully
	*    CAUTIONS : 
	****************************************************************************/
	unsigned int GetAddParaCounts(void) const { return m_nAddParaCounts; };

	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] added by chenjingdong, 2013-05-17 start
	/****FUNCTION***************************************************************
	 *		  NAME : FlushParas
	 * DESCRIPTION : Flush all Parameters into the XML file
	 *       INPUT : none
	 *      OUTPUT : none
	 *     RETURNS : success return true, fail return false
	 *    CAUTIONS : 
	 ****************************************************************************/
	bool FlushParas(void);
	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] end

private:
	/****FUNCTION***************************************************************
	*		 NAME : IsValidName
	* DESCRIPTION : verify whether the name of parameter is ok.
	*       INPUT : strName : Parameter name
	*      OUTPUT : null
	*     RETURNS : success return DCI_LOG_SUCCESS, fail return DCI_LOG_INSUFFICIENT_PARAMETERS
	*    CAUTIONS : 
	****************************************************************************/
	int IsValidName(const char *strName);

private:
	TicketEventSubType m_eEvtSubType;
	bool m_bIsParamAdded; //true : add all valid parameters successfully.
	unsigned int m_nAddParaCounts; //record the counts adding parameter successfully

	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] added by chenjingdong, 2013-05-17 start
	unsigned int m_ParaIndex;
	char* m_ParasValue[PARAMETER_NUMS];
	//[DC_SecTermSM_v1.1_EvtLogModule_v1.1] end
};

#endif
