/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   �� MessageULName.h
Author     �� huweihua@dadimedia.com
Date       �� 10/03/01
Version    �� v1.0
Description�� Auditorium Security Message Key class(key in KLV struct)
Others     :  
History    �� 
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
    Function   ��const UInt8 *GetULName()
    Description�����KLV�ṹ�е�KEYֵ
    Input      ����
    Output     ��KLV�ṹ�е�KEYֵ
    Return     ��KLV�ṹ�е�KEYֵ
    Others     : ��
    *************************************************/ 
	const UInt8 *GetULName();
	
	/************************************************* 
    Function   ��UInt32 ParseULName(UInt8 *)
    Description������KLV�ṹ�е�KEYֵ
    Input      ��MessageULName--����KLV�ṹ�е�KEY�Ŀռ�ͷ��ַ
    Output     ����
    Return     ��������,�μ�Const.h
    Others     : ��
    *************************************************/
	UInt32 ParseULName(/*in*/UInt8 *MessageULName);
	/************************************************* 
    Function   ��SetULName
    Description������KLV�ṹ�е�KEYֵ
    Input      ��PackSubType--ASM��Ϣ����
    Output     ��ULNameBuf
    Return     ��������,�μ�Const.h
    Others     : ��
    *************************************************/
	UInt32 SetULName(/* in*/ UInt32 PackSubType, 
	                 /*out*/ UInt8 *ULNameBuf);
	/************************************************* 
    Function   : SetObjectID
    Description: ���� ObjectID λ
    Input      : ObjectID--ObjectID
    Output     : ��
    Return     : ������,�μ�Const.h
    Others     : ��
    *************************************************/
	UInt32 SetObjectID(/*in*/UInt8 ObjectID);
	/************************************************* 
    Function   : SetLableSize
    Description: ���� LableSize λ
    Input      : LableSize--LableSize
    Output     : ��
    Return     : ������,�μ�Const.h
    Others     : ��
    *************************************************/
	UInt32 SetLableSize(/*in*/UInt8 LableSize);
	/************************************************* 
    Function   : SetSubDesignator
    Description: ���� SubDesignator λ
    Input      : SubDesignator--SubDesignator
    Output     : ��
    Return     : ������,�μ�Const.h
    Others     : ��
    *************************************************/
	UInt32 SetSubDesignator(/*in*/UInt8 SubDesignator);
	/************************************************* 
    Function   : SetSMPTEDesignator
    Description: ���� SMPTEDesignator λ
    Input      : SMPTEDesignator--SMPTEDesignator
    Output     : ��
    Return     : ������,�μ�Const.h
    Others     : ��
    *************************************************/
	UInt32 SetSMPTEDesignator(/*in*/UInt8 SMPTEDesignator);
	/************************************************* 
    Function   : SetRegistryCategoryDesignator
    Description: ���� RegistryCategoryDesignator λ
    Input      : RegistryCategoryDesignator--RegistryCategoryDesignator
    Output     : ��
    Return     : ������,�μ�Const.h
    Others     : ��
    *************************************************/
	UInt32 SetRegistryCategoryDesignator(/*in*/UInt8 RegistryCategoryDesignator);
	/************************************************* 
    Function   : SetRegistryDesignator
    Description: ���� RegistryDesignator λ
    Input      : RegistryDesignator--RegistryDesignator
    Output     : ��
    Return     : ������,�μ�Const.h
    Others     : ��
    *************************************************/
	UInt32 SetRegistryDesignator(/*in*/UInt8 RegistryDesignator);
	/************************************************* 
    Function   : SetStructureDesignator
    Description: ���� StructureDesignator λ
    Input      : StructureDesignator--StructureDesignator
    Output     : ��
    Return     : ������,�μ�Const.h
    Others     : ��
    *************************************************/
	UInt32 SetStructureDesignator(/*in*/UInt8 StructureDesignator);
	/************************************************* 
    Function   : SetVersionNumber
    Description: ���� VersionNumber λ
    Input      : VersionNumber--VersionNumber
    Output     : ��
    Return     : ������,�μ�Const.h
    Others     : ��
    *************************************************/
	UInt32 SetVersionNumber(/*in*/UInt8 VersionNumber);
	/************************************************* 
    Function   : SetItemDesignator
    Description: ���� ItemDesignator λ
    Input      : ItemDesignator--ItemDesignator
    Output     : ��
    Return     : ������,�μ�Const.h
    Others     : ��
    *************************************************/
	UInt32 SetItemDesignator(/*in*/UInt8 ItemDesignator);
	/************************************************* 
    Function   : SetOrganization
    Description: ���� Organization λ
    Input      : Organization--Organization
    Output     : ��
    Return     : ������,�μ�Const.h
    Others     : ��
    *************************************************/
	UInt32 SetOrganization(/*in*/UInt8 Organization);
	/************************************************* 
    Function   : SetApplication
    Description: ���� Application λ
    Input      : Application--Application
    Output     : ��
    Return     : ������,�μ�Const.h
    Others     : ��
    *************************************************/
	UInt32 SetApplication(/*in*/UInt8 Application);
	/************************************************* 
    Function   : SetPackType
    Description: ���� PackType λ
    Input      : PackType--PackType
    Output     : ��
    Return     : ������,�μ�Const.h
    Others     : ��
    *************************************************/
	UInt32 SetPackType(/*in*/UInt8 PackType);
	/************************************************* 
    Function   : SetPackSubType
    Description: ���� PackSubType λ
    Input      : PackSubType--PackSubType
    Output     : ��
    Return     : ������,�μ�Const.h
    Others     : ��
    *************************************************/
	UInt32 SetPackSubType(/*in*/UInt8 PackSubType);
	/************************************************* 
    Function   : SetReserved
    Description: ���� Reserved λ
    Input      : Reserved--Reserved
    Output     : ��
    Return     : ������,�μ�Const.h
    Others     : ��
    *************************************************/
	UInt32 SetReserved(/*in*/UInt8 Reserved);
	
	/************************************************* 
    Function   : GetObjectID
    Description: ��ȡ ObjectID λ
    Input      : ��
    Output     : ��
    Return     : ObjectID λ
    Others     : ��
    *************************************************/
	UInt8 GetObjectID();
	/************************************************* 
    Function   : GetLableSize
    Description: ��ȡ LableSize λ
    Input      : ��
    Output     : ��
    Return     : LableSize λ
    Others     : ��
    *************************************************/
	UInt8 GetLableSize();
	/************************************************* 
    Function   : GetSubDesignator
    Description: ��ȡ SubDesignator λ
    Input      : ��
    Output     : ��
    Return     : SubDesignator λ
    Others     : ��
    *************************************************/
	UInt8 GetSubDesignator();
	/************************************************* 
    Function   : GetSMPTEDesignator
    Description: ��ȡ SMPTEDesignator λ
    Input      : ��
    Output     : ��
    Return     : SMPTEDesignator λ
    Others     : ��
    *************************************************/
	UInt8 GetSMPTEDesignator();
	/************************************************* 
    Function   : GetRegistryCategoryDesignator
    Description: ��ȡ RegistryCategoryDesignator λ
    Input      : ��
    Output     : ��
    Return     : RegistryCategoryDesignator λ
    Others     : ��
    *************************************************/
	UInt8 GetRegistryCategoryDesignator();
	/************************************************* 
    Function   : GetRegistryDesignator
    Description: ��ȡ RegistryDesignator λ
    Input      : ��
    Output     : ��
    Return     : RegistryDesignator λ
    Others     : ��
    *************************************************/
	UInt8 GetRegistryDesignator();
	/************************************************* 
    Function   : GetStructureDesignator
    Description: ��ȡ StructureDesignator λ
    Input      : ��
    Output     : ��
    Return     : StructureDesignator λ
    Others     : ��
    *************************************************/
	UInt8 GetStructureDesignator();
	/************************************************* 
    Function   : GetVersionNumber
    Description: ��ȡ VersionNumber λ
    Input      : ��
    Output     : ��
    Return     : VersionNumber λ
    Others     : ��
    *************************************************/
	UInt8 GetVersionNumber();
	/************************************************* 
    Function   : GetItemDesignator
    Description: ��ȡ ItemDesignator λ
    Input      : ��
    Output     : ��
    Return     : ItemDesignator λ
    Others     : ��
    *************************************************/
	UInt8 GetItemDesignator();
	/************************************************* 
    Function   : GetOrganization
    Description: ��ȡ Organization λ
    Input      : ��
    Output     : ��
    Return     : Organization λ
    Others     : ��
    *************************************************/
	UInt8 GetOrganization();
	/************************************************* 
    Function   : GetApplication
    Description: ��ȡ Application λ
    Input      : ��
    Output     : ��
    Return     : Application λ
    Others     : ��
    *************************************************/
	UInt8 GetApplication();
	/************************************************* 
    Function   : GetPackType
    Description: ��ȡ PackType λ
    Input      : ��
    Output     : ��
    Return     : PackType λ
    Others     : ��
    *************************************************/
	UInt8 GetPackType();
	/************************************************* 
    Function   : GetPackSubType
    Description: ��ȡ PackSubType λ
    Input      : ��
    Output     : ��
    Return     : PackSubType λ
    Others     : ��
    *************************************************/
	UInt8 GetPackSubType();
	/************************************************* 
    Function   : GetReserved
    Description: ��ȡ Reserved λ
    Input      : ��
    Output     : ��
    Return     : Reserved λ
    Others     : ��
    *************************************************/
	UInt8 GetReserved();

private:	
	UInt8 ULName[UL_KEY_VALUE_LEN];	//ASM message header

};

#endif
