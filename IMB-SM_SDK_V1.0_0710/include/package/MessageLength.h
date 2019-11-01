/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� MessageLength.h
Author     �� huweihua@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message length class(length in KLV struct)
Others     :  
History    �� 
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
    Function   �� GetLength()
    Description�� returns message length in big-endian format
    Input      �� none	
    Output     �� none
    Return     �� message length
    Others     :        
    *************************************************/
	const UInt8 *GetLength();
	/************************************************* 
    Function   �� ParseMessageLength()
    Description�� parse message length in big-endian format
    Input      �� MessageLength	- message length in big-endian format
    Output     �� none
    Return     �� message length in integer foramt
    Others     :        
    *************************************************/
	UInt32 ParseMessageLength(/*in*/UInt8 *MessageLength);
	/************************************************* 
    Function   �� SetLength()
    Description�� set message length(integer value)
    Input      �� Length	- message length
    Output     �� none
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 SetLength(/*in*/UInt32 Length);
	/************************************************* 
    Function   �� SetLength()
    Description�� parse message length in big-endian format and output to buffer
    Input      �� Length	- message length
    Output     �� MessageLengthBuf	- big-endian length buffer
    Return     �� error code, refer to Const.h
    Others     :        
    *************************************************/
	UInt32 SetLength(/* in*/UInt32 Length, 
	                 /*out*/UInt8 *MessageLengthBuf);
private:
	UInt8 Length[UL_LEN_VALUE_LEN];	//length buffer
};

#endif
