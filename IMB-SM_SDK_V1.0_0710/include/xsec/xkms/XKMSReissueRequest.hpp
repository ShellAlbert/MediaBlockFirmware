/*
 * Copyright 2006 The Apache Software Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * XSEC
 *
 * XKMSReissueRequest := Interface for RegisterRequest Messages
 *
 * $Id: XKMSReissueRequest.hpp,v 1.1.1.1 2014/05/23 08:41:20 wangruxia.oristartech.com Exp $
 *
 */

#ifndef XKMSREISSUEREQUEST_INCLUDE 
#define XKMSREISSUEREQUEST_INCLUDE 

// XSEC Includes

#include <xsec/framework/XSECDefs.hpp>
#include <xsec/xkms/XKMSRequestAbstractType.hpp>
#include <xsec/xkms/XKMSStatus.hpp>

class DSIGSignature;
class XKMSAuthentication;
class XKMSReissueKeyBinding;

/**
 * @ingroup xkms
 */

/**
 * @brief Interface definition for the ReissueRequest elements
 *
 * The \<ReissueRequest\> is one of the message types of
 * the X-KRMS service.  It is used when a client wishes to request
 * the service reissue a key binding (e.g. a cert).
 *
 * The schema definition for ReissueRequest is as follows :
 *
 * \verbatim
   <!-- ReissueRequest -->
   <element name="ReissueRequest" type="xkms:ReissueRequestType"/>
   <complexType name="ReissueRequestType">
      <complexContent>
         <extension base="xkms:RequestAbstractType">
            <sequence>
               <element ref="xkms:ReissueKeyBinding"/>
               <element ref="xkms:Authentication"/>
               <element ref="xkms:ProofOfPossession" minOccurs="0"/>
            </sequence>
         </extension>
      </complexContent>
   </complexType>
   <element name="ReissueKeyBinding" type="xkms:KeyBindingType"/>
   <!-- /ReissueRequest -->
\endverbatim
 */

class XKMSReissueRequest : public XKMSRequestAbstractType {

	/** @name Constructors and Destructors */
	//@{

protected:

	XKMSReissueRequest() {};

public:

	virtual ~XKMSReissueRequest() {};

	/** @name Getter Interface Methods */
	//@{

	/**
	 * \brief Return the element at the base of the message
	 */

	virtual XERCES_CPP_NAMESPACE_QUALIFIER DOMElement * getElement(void) const = 0;

	/**
	 * \brief Obtain the ReissueKeyBinding element
	 *
	 * The ReissueKeyBinding element is the core of the ReissueRequest message, and
	 * defines the key information that a Reissue is required for.
	 *
	 * @returns A pointer to the XKMSPrototypeKeyBinding element
	 */

	virtual XKMSReissueKeyBinding * getReissueKeyBinding(void) const = 0;

	/**
	 * \brief Get the Authentication element
	 *
	 * The Authentication element of the ReissueRequest is used by the client to
	 * authenticate the request to the server.
	 *
	 * @return A pointer to the Authentication structure 
	 */

	virtual XKMSAuthentication * getAuthentication (void) const = 0;

	/**
	 * \brief Get the signature used to prove possession of the private key
	 *
	 * When the client presents a request for a key generated by them, this element
	 * is used to show that the client is authorised to make this request using this
	 * key.
	 *
	 * @return A pointer to the proof of possession Signature object (or NULL if none
	 * was defined
	 */

	virtual DSIGSignature * getProofOfPossessionSignature(void) const = 0;

	//@}

	/** @name Setter Interface Methods */
	//@{

	/** \brief Add a ReissueKeyBinding element
	 *
	 * Set a ReissueKeyBinding element in the Request message.  The returned
	 * object can be manipulated to add KeyInfo elements to the Request.
	 *
	 * @param status The status value to add into the ReissueKeyBinding structure
	 * @returns A pointer to the newly created ReissueKeyBinding object, or
	 * the pointer to extant object if one already existed.
	 */

	virtual XKMSReissueKeyBinding * addReissueKeyBinding(XKMSStatus::StatusValue status) = 0;

	/** \brief Add an Authentication element
	 *
	 * Set a Authentication element in the Request message.  The returned
	 * object can be manipulated to add Authentication information to the request.
	 *
	 * @returns A pointer to the newly created Authenticaton object, or
	 * the pointer to extant object if one already existed.
	 */

	virtual XKMSAuthentication * addAuthentication(void) = 0;


	/**
	 * \brief Add a ProofOfPossession signature to the message
	 *
	 * Allows the application to add a new ProofOfPossession signature into a 
	 * ReissueRequest element
	 *
	 * @note the client application will need to set the key and sign the
	 * message - however the appropriate reference (to the ReissueKeyBinding
	 * element) will be set.  This implies that the ReissueKeyBinding *must*
	 * be added prior to the call to this method.
	 *
	 * @returns the new Signature structure
	 */

	virtual DSIGSignature * addProofOfPossessionSignature(
		canonicalizationMethod cm = CANON_C14N_NOC,
		signatureMethod	sm = SIGNATURE_DSA,
		hashMethod hm = HASH_SHA1) = 0;
	
	//@}

private:

	// Unimplemented
	XKMSReissueRequest(const XKMSReissueRequest &);
	XKMSReissueRequest & operator = (const XKMSReissueRequest &);

};

#endif /* XKMSREISSUEREQUEST_INCLUDE */
