/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   £º MessageLength.h
Author     £º huweihua@dadimedia.com
Date       £º 10/03/01
Version    £º v1.0
Description£º Auditorium Security Message length class(length in KLV struct)
Others     :  
History    £º 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef MESSAGEULNAME_H
#define MESSAGEULNAME_H

#include "package/Const.h"

class MessageLength
{
public:
	MessageLength();
	~MessageLength();
	/************************************************* 
    Function   £º GetLength()
    Description£º returns message length in big-endian format
    Input      £º none	
    Output     £º none
    Return     £º message length
    Others     :        
    *************************************************/
	const UInt8 *GetLength();
	/************************************************* 
    Function   £º ParseMessageLength()
    Description£º parse message length in big-endian format
    Input      £º MessageLength	- message length in big-endian format
    Output     £º none
    Return     £º message length in integer foramt
    Others     :        
    *************************************************/
	UInt32 ParseMessageLength(/*in*/UInt8 *MessageLength);
	/************************************************* 
    Function   £º SetLength()
    Description£º set message length(integer value)
    Input      £º Length	- message length
    Output     £º none
    Return     £º error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 SetLength(/*in*/UInt32 Length);
	/************************************************* 
    Function   £º SetLength()
    Description£º parse message length in big-endian format and output to buffer
    Input      £º Length	- message length
    Output     £º MessageLengthBuf	- big-endian length buffer
    Return     £º error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 SetLength(/* in*/UInt32 Length, 
	                 /*out*/UInt8 *MessageLengthBuf);
private:
	UInt8 Length[UL_LEN_VALUE_LEN];	//length buffer
};

#endif
