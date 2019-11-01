/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * $Id: XMLInteger.hpp,v 1.1.1.1 2014/05/23 08:41:19 wangruxia.oristartech.com Exp $
 */

#if !defined(XERCESC_INCLUDE_GUARD_XML_INTEGER_HPP)
#define XERCESC_INCLUDE_GUARD_XML_INTEGER_HPP

#include <xercesc/util/XMemory.hpp>

XERCES_CPP_NAMESPACE_BEGIN

class XMLUTIL_EXPORT XMLInteger : public XMemory
{
public:

	/**
	 * Constructs a newly allocated <code>XMLInteger</code> object
     *
	 * @param      intVal   the <code>integer</code>
	 */

	XMLInteger(const int intVal);

	~XMLInteger();

	/**
	 * Returns the built in integer value.
	 */
    int intValue() const;

private:
    // -----------------------------------------------------------------------
    //  Unimplemented constructors and operators
    // -----------------------------------------------------------------------
    XMLInteger(const XMLInteger&);
    XMLInteger& operator=(const XMLInteger&);

    // -----------------------------------------------------------------------
    //  Private data members
    //
	//  fData
    //     the value
    //
    // -----------------------------------------------------------------------
    int         fData;

};

inline XMLInteger::XMLInteger(const int intVal)
:fData(intVal)
{
}

inline XMLInteger::~XMLInteger()
{
}

inline int XMLInteger::intValue() const
{
    return fData;
}

XERCES_CPP_NAMESPACE_END

#endif
