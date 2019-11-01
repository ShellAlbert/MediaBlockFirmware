/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： MessageULName.h
Author     ： huweihua@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message Key class(key in KLV struct)
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
********************************************/
#ifndef MESSAGELENGTH_H
#define MESSAGELENGTH_H

#include "package/Const.h"

class MessageULName
{

public:
	MessageULName();
	~MessageULName();   
	
    /************************************************* 
    Function   ：const UInt8 *GetULName()
    Description：获得KLV结构中的KEY值
    Input      ：无
    Output     ：KLV结构中的KEY值
    Return     ：KLV结构中的KEY值
    Others     : 无
    *************************************************/ 
	const UInt8 *GetULName();
	
	/************************************************* 
    Function   ：UInt32 ParseULName(UInt8 *)
    Description：解析KLV结构中的KEY值
    Input      ：MessageULName--包含KLV结构中的KEY的空间头地址
    Output     ：无
    Return     ：错误码,参见Const.h
    Others     : 无
    *************************************************/
	UInt32 ParseULName(/*in*/UInt8 *MessageULName);
	/************************************************* 
    Function   ：SetULName
    Description：设置KLV结构中的KEY值
    Input      ：PackSubType--ASM消息类型
    Output     ：ULNameBuf
    Return     ：错误码,参见Const.h
    Others     : 无
    *************************************************/
	UInt32 SetULName(/* in*/ UInt32 PackSubType, 
	                 /*out*/ UInt8 *ULNameBuf);
	/************************************************* 
    Function   : SetObjectID
    Description: 设置 ObjectID 位
    Input      : ObjectID--ObjectID
    Output     : 无
    Return     : 错误码,参见Const.h
    Others     : 无
    *************************************************/
	UInt32 SetObjectID(/*in*/UInt8 ObjectID);
	/************************************************* 
    Function   : SetLableSize
    Description: 设置 LableSize 位
    Input      : LableSize--LableSize
    Output     : 无
    Return     : 错误码,参见Const.h
    Others     : 无
    *************************************************/
	UInt32 SetLableSize(/*in*/UInt8 LableSize);
	/************************************************* 
    Function   : SetSubDesignator
    Description: 设置 SubDesignator 位
    Input      : SubDesignator--SubDesignator
    Output     : 无
    Return     : 错误码,参见Const.h
    Others     : 无
    *************************************************/
	UInt32 SetSubDesignator(/*in*/UInt8 SubDesignator);
	/************************************************* 
    Function   : SetSMPTEDesignator
    Description: 设置 SMPTEDesignator 位
    Input      : SMPTEDesignator--SMPTEDesignator
    Output     : 无
    Return     : 错误码,参见Const.h
    Others     : 无
    *************************************************/
	UInt32 SetSMPTEDesignator(/*in*/UInt8 SMPTEDesignator);
	/************************************************* 
    Function   : SetRegistryCategoryDesignator
    Description: 设置 RegistryCategoryDesignator 位
    Input      : RegistryCategoryDesignator--RegistryCategoryDesignator
    Output     : 无
    Return     : 错误码,参见Const.h
    Others     : 无
    *************************************************/
	UInt32 SetRegistryCategoryDesignator(/*in*/UInt8 RegistryCategoryDesignator);
	/************************************************* 
    Function   : SetRegistryDesignator
    Description: 设置 RegistryDesignator 位
    Input      : RegistryDesignator--RegistryDesignator
    Output     : 无
    Return     : 错误码,参见Const.h
    Others     : 无
    *************************************************/
	UInt32 SetRegistryDesignator(/*in*/UInt8 RegistryDesignator);
	/************************************************* 
    Function   : SetStructureDesignator
    Description: 设置 StructureDesignator 位
    Input      : StructureDesignator--StructureDesignator
    Output     : 无
    Return     : 错误码,参见Const.h
    Others     : 无
    *************************************************/
	UInt32 SetStructureDesignator(/*in*/UInt8 StructureDesignator);
	/************************************************* 
    Function   : SetVersionNumber
    Description: 设置 VersionNumber 位
    Input      : VersionNumber--VersionNumber
    Output     : 无
    Return     : 错误码,参见Const.h
    Others     : 无
    *************************************************/
	UInt32 SetVersionNumber(/*in*/UInt8 VersionNumber);
	/************************************************* 
    Function   : SetItemDesignator
    Description: 设置 ItemDesignator 位
    Input      : ItemDesignator--ItemDesignator
    Output     : 无
    Return     : 错误码,参见Const.h
    Others     : 无
    *************************************************/
	UInt32 SetItemDesignator(/*in*/UInt8 ItemDesignator);
	/************************************************* 
    Function   : SetOrganization
    Description: 设置 Organization 位
    Input      : Organization--Organization
    Output     : 无
    Return     : 错误码,参见Const.h
    Others     : 无
    *************************************************/
	UInt32 SetOrganization(/*in*/UInt8 Organization);
	/************************************************* 
    Function   : SetApplication
    Description: 设置 Application 位
    Input      : Application--Application
    Output     : 无
    Return     : 错误码,参见Const.h
    Others     : 无
    *************************************************/
	UInt32 SetApplication(/*in*/UInt8 Application);
	/************************************************* 
    Function   : SetPackType
    Description: 设置 PackType 位
    Input      : PackType--PackType
    Output     : 无
    Return     : 错误码,参见Const.h
    Others     : 无
    *************************************************/
	UInt32 SetPackType(/*in*/UInt8 PackType);
	/************************************************* 
    Function   : SetPackSubType
    Description: 设置 PackSubType 位
    Input      : PackSubType--PackSubType
    Output     : 无
    Return     : 错误码,参见Const.h
    Others     : 无
    *************************************************/
	UInt32 SetPackSubType(/*in*/UInt8 PackSubType);
	/************************************************* 
    Function   : SetReserved
    Description: 设置 Reserved 位
    Input      : Reserved--Reserved
    Output     : 无
    Return     : 错误码,参见Const.h
    Others     : 无
    *************************************************/
	UInt32 SetReserved(/*in*/UInt8 Reserved);
	
	/************************************************* 
    Function   : GetObjectID
    Description: 读取 ObjectID 位
    Input      : 无
    Output     : 无
    Return     : ObjectID 位
    Others     : 无
    *************************************************/
	UInt8 GetObjectID();
	/************************************************* 
    Function   : GetLableSize
    Description: 读取 LableSize 位
    Input      : 无
    Output     : 无
    Return     : LableSize 位
    Others     : 无
    *************************************************/
	UInt8 GetLableSize();
	/************************************************* 
    Function   : GetSubDesignator
    Description: 读取 SubDesignator 位
    Input      : 无
    Output     : 无
    Return     : SubDesignator 位
    Others     : 无
    *************************************************/
	UInt8 GetSubDesignator();
	/************************************************* 
    Function   : GetSMPTEDesignator
    Description: 读取 SMPTEDesignator 位
    Input      : 无
    Output     : 无
    Return     : SMPTEDesignator 位
    Others     : 无
    *************************************************/
	UInt8 GetSMPTEDesignator();
	/************************************************* 
    Function   : GetRegistryCategoryDesignator
    Description: 读取 RegistryCategoryDesignator 位
    Input      : 无
    Output     : 无
    Return     : RegistryCategoryDesignator 位
    Others     : 无
    *************************************************/
	UInt8 GetRegistryCategoryDesignator();
	/************************************************* 
    Function   : GetRegistryDesignator
    Description: 读取 RegistryDesignator 位
    Input      : 无
    Output     : 无
    Return     : RegistryDesignator 位
    Others     : 无
    *************************************************/
	UInt8 GetRegistryDesignator();
	/************************************************* 
    Function   : GetStructureDesignator
    Description: 读取 StructureDesignator 位
    Input      : 无
    Output     : 无
    Return     : StructureDesignator 位
    Others     : 无
    *************************************************/
	UInt8 GetStructureDesignator();
	/************************************************* 
    Function   : GetVersionNumber
    Description: 读取 VersionNumber 位
    Input      : 无
    Output     : 无
    Return     : VersionNumber 位
    Others     : 无
    *************************************************/
	UInt8 GetVersionNumber();
	/************************************************* 
    Function   : GetItemDesignator
    Description: 读取 ItemDesignator 位
    Input      : 无
    Output     : 无
    Return     : ItemDesignator 位
    Others     : 无
    *************************************************/
	UInt8 GetItemDesignator();
	/************************************************* 
    Function   : GetOrganization
    Description: 读取 Organization 位
    Input      : 无
    Output     : 无
    Return     : Organization 位
    Others     : 无
    *************************************************/
	UInt8 GetOrganization();
	/************************************************* 
    Function   : GetApplication
    Description: 读取 Application 位
    Input      : 无
    Output     : 无
    Return     : Application 位
    Others     : 无
    *************************************************/
	UInt8 GetApplication();
	/************************************************* 
    Function   : GetPackType
    Description: 读取 PackType 位
    Input      : 无
    Output     : 无
    Return     : PackType 位
    Others     : 无
    *************************************************/
	UInt8 GetPackType();
	/************************************************* 
    Function   : GetPackSubType
    Description: 读取 PackSubType 位
    Input      : 无
    Output     : 无
    Return     : PackSubType 位
    Others     : 无
    *************************************************/
	UInt8 GetPackSubType();
	/************************************************* 
    Function   : GetReserved
    Description: 读取 Reserved 位
    Input      : 无
    Output     : 无
    Return     : Reserved 位
    Others     : 无
    *************************************************/
	UInt8 GetReserved();

private:	
	UInt8 ULName[UL_KEY_VALUE_LEN];	//ASM message header

};

#endif
