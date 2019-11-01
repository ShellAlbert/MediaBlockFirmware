/****************************************************************************
Copyright (c) 2010 - 2020, Digital OristarTech Co., Ltd. All rights reserved.

ModuleName  : IMB-SM SDK
FileName    £ºBaseClassPrivate.h
Author      : chenjingdong@oristartech.com
Date        : 2014-06-30
Version     : v1.0
Description £ºA definition of the class : BaseClassPrivate, which is a base class for all private objects.   
Others      : 
History     : 

< Author >    			< Date >             < Modification >

****************************************************************************/
#ifndef _MVC2API_BASECLASSPRIVATE_H_
#define _MVC2API_BASECLASSPRIVATE_H_

#include "../mvc2api_types.h"

#ifdef MVC2API_DEBUG
#include <stdio.h>
#endif


namespace mvc2
{

	#define NULL 0

	class BaseClassPrivate
	{
	public:
		BaseClassPrivate() : m_nRefCount(0) { addRef(); };
		virtual ~BaseClassPrivate() {};

		/****FUNCTION***************************************************************
		*		 NAME : addRef
		* DESCRIPTION : add a reference to this class, and RefCount + 1.
		*       INPUT : null
		*      OUTPUT : null
		*     RETURNS : int, return current value of the reference count
		*    CAUTIONS : 
		****************************************************************************/
		virtual int addRef() 
		{
			return ++m_nRefCount;
		};

		/****FUNCTION***************************************************************
		*		 NAME : release
		* DESCRIPTION : release a reference to this class, and RefCount - 1.
		*       INPUT : null
		*      OUTPUT : null
		*     RETURNS : int, return current value of the reference count
		*    CAUTIONS : 
		****************************************************************************/
		virtual int release() 
		{
			int nCount = --m_nRefCount;

			if (!nCount) 
				delete this;

			return nCount;
		};

		/****FUNCTION***************************************************************
		*		 NAME : testMvc2api
		* DESCRIPTION : an interface to test all methods implemented in this class.
		*       INPUT : null
		*      OUTPUT : null
		*     RETURNS : null
		*    CAUTIONS : 
		****************************************************************************/
		virtual void testMvc2api() {};

	private:
		int32_t m_nRefCount;
	};
}

#endif