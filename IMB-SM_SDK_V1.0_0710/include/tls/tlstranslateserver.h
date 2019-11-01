/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  TLS communication 
FileName   £º tlstranslateserver.h
Author     £º huweihua@dadimedia.com
Date       £º 10/03/01
Version    £º v1.0
Description£º server of TLS communication
Others     :  
History    £º 
      < Author >    			< Date >             < Modification > 
********************************************/ 
#ifndef _TLS_TRANSLATE_SERVER_H_
#define _TLS_TRANSLATE_SERVER_H_

#ifdef WIN32    
	#include <windows.h>   
	#include <winsock.h>
#else
	#include <sys/socket.h>  
	#include <errno.h>
	#include <sys/types.h>  
	#include <netinet/in.h> 
	#include <arpa/inet.h>  
#endif

#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

#include <memory.h>

#include <openssl/rsa.h>
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/pkcs12.h>
#include <openssl/asn1.h>
#include <openssl/bio.h>
#include <openssl/x509.h>
#include <openssl/lhash.h>
#include <openssl/conf.h>
#include <openssl/txt_db.h>
#include <openssl/ossl_typ.h>
#include <openssl/e_os2.h>
#include <openssl/evp.h>
#include <openssl/pem2.h>
#include <openssl/crypto.h>
#include <openssl/pkcs12.h>
#include "smsdk/errornumber.h"

class CTLS_Translate_Server 
{
public:
	
    /************************************************* 
    Function   £º CTLS_Translate_Server()
    Description£º constructor of CTLS_Translate_Server class
    Input      £º a_pCertFile : server certificate
                  a_CACertFile: CA certificate list 
                  a_pKeyFile  : server private key 
    Output     £º 
    Return     £º
    Others     :        
    *************************************************/	
	CTLS_Translate_Server(        
	    X509              *a_pCertFile, 
        vector<X509 *>    &a_CACertFile, 
        EVP_PKEY          *a_pKeyFile);	
	
   /************************************************* 
    Function   £º ~CTLS_Translate_Server()
    Description£º destructor of CTLS_Translate_Server class
    Input      £º 
    Output     £º 
    Return     £º
    Others     :        
    *************************************************/
	~CTLS_Translate_Server();

    /************************************************* 
    Function   £º TLS_StartUp()
    Description£º connect server on TLS layer
    Input      £º a_pIP   : Server IP 
                  a_iPort : port server used
                  a_iVerifyFlag :TLS Verify mode. SSL_VERIFY_PEER or SSL_VERIFY_NONE
                  SSL_VERIFY_NONE: do not verify client
	              SSL_VERIFY_PEER: verify client
    Output     £º 
    Return     £º error code, refer to smsdk\errornumber.h
    Others     :        
    *************************************************/
	int TLS_StartUp(
	const char  *a_pIP,
	const int    a_iPort,
	const int    a_iVerifyFlag = SSL_VERIFY_PEER);

    /*************************************************
    Function   £º Tls_Accept()
    Description£º server waiting for connection from client
    Input      £º a_ppAcceptSSLStruct :SSL entity. 
    Output     £º 
    Return     £º error code, refer to smsdk\errornumber.h
    Others     :        
    *************************************************/	
	int Tls_Accept(SSL** a_ppAcceptSSLStruct);
	
    /************************************************* 
    Function   £º TLS_Read()
    Description£º receive data from client 
    Input      £º a_pSSLStruct: SSL entity
    			  a_pBuf    : data buffer
                  a_iSize   : the size of data to be received
                  a_iTimeOut: time out interval
	                  [a_iTimeOut < 0]  block forever
	                  [a_iTimeOut = 0]  none-block
	                  [a_iTimeOut > 0]  block 'a_iTimeOut' seconds                  
    Output     £º a_iSizeOut: the actually size of data received
    Return     £º error code, refer to smsdk\errornumber.h
    Others     :        
    *************************************************/
   
	int TLS_Read(/* in*/ SSL      *a_pSSLStruct,
				 /* in*/ void     *a_pBuf,          
				 /* in*/ const int a_iSize,        
				 /* in*/ int       a_iTimeOut,      
				 /*out*/ int      *a_iSizeOut);     
				 
    /************************************************* 
    Function   £º TLS_Write()
    Description£º send data to client 
    Input      £º a_pSSLStruct: SSL entity 
                  a_pBuf    : data buffer
	              a_iSize   : the size of data to be sent
	              a_iTimeOut: time out interval
	                  [a_iTimeOut < 0]  block forever
	                  [a_iTimeOut = 0]  none-block
	                  [a_iTimeOut > 0]  block 'a_iTimeOut' seconds                  
    Output     £º a_iSizeIn: the actually size of data send
    Return     £º error code, refer to smsdk\errornumber.h
    Others     :        
    *************************************************/  
	int TLS_Write(/* in*/ SSL      *a_pSSLStruct, 
                  /* in*/ void     *a_pbuf,      
                  /* in*/ const int a_iSize,      
                  /* in*/ int       a_iTimeOut,   
                  /*out*/ int      *a_iSizeIn);   

	/************************************************* 
    Function   £º TLS_Get_Peer_Cert()
    Description£º get certificate of client
    Input      £º a_pSSLStruct: SSL entity            
    Output     £º PeerCert: the certificate of client
    Return     £º error code, refer to smsdk\errornumber.h
    Others     :        
    *************************************************/
	int TLS_Get_Peer_Cert(/* in*/SSL        *a_pSSLStruct,  
						  /*out*/const X509 **PeerCert);    

	/************************************************* 
    Function   £º TLS_Close()
    Description£º Close the TLS connection 
    Input      £º a_pSSLStruct: SSL entity               
    Output     £º 
    Return     £º error code, refer to smsdk\errornumber.h
    Others     :        
    *************************************************/
	int TLS_Close(SSL  **a_pSSLStruct);
	
private:	
	
	/************************************************* 
    Function   £º TLS_InitSocket()
    Description£º establish connection on TCP layer
    Input      £º           
    Output     £º 
    Return     £º error code, refer to smsdk\errornumber.h
    Others     :        
    *************************************************/ 
	int TLS_InitSocket();

    /************************************************* 
    Function   £º TLS_Creat_HandShake()
    Description£º TLS-HandShake with client
    Input      £º a_iSocketHandle :Socket handle created by TLS_InitSocket            
    Output     £º a_ppSSL £ºSSL entity 
    Return     £º error code, refer to smsdk\errornumber.h
    Others     :        
    *************************************************/
	int TLS_Creat_HandShake(
        	/* in*/const int a_iSocketHandle, 
        	/*out*/SSL** a_ppSSL);

	/************************************************* 
    Function   £º TLS_SetData()
    Description£º configure parameters:certificate , private key , CA certificate list
    Input      £º           
    Output     £º 
    Return     £º error code, refer to smsdk\errornumber.h
    Others     :        
    *************************************************/
	int TLS_SetData();

	/************************************************* 
    Function   £º TLS_InitContext()
    Description£º initialization TLS context
    Input      £º a_iVerifyFlag £º ( SSL_VERIFY_NONE or SSL_VERIFY_PEER )
	              SSL_VERIFY_NONE: do not verify client
	              SSL_VERIFY_PEER: verify client
    Output     £º 
    Return     £º error code, refer to smsdk\errornumber.h
    Others     :        
    *************************************************/
	int TLS_InitContext(/*in*/const int a_iVerifyFlag);
	
	/************************************************* 
    Function   £º TLS_SetCaCertList()
    Description£º specify CA certificate list
    Input      £º a_CaCertList: CA certificate list 
    Output     £º 
    Return     £º error code, refer to smsdk\errornumber.h
    Others     :        
    *************************************************/
	int TLS_SetCaCertList(vector<X509*>& a_CaCertList);

	char            *m_pIP;				//the IP address of server	
	int              m_iPort;			//the port of server listening
	int              m_iSockHandle;		//socket descriptor 
	SSL_CTX         *m_pSSLContext;		//context of tls protocol
	SSL             *m_pSSLStruct;	    //SSL entity in context of tls protocol
    vector<X509 *>   m_CACertFile;      //save CA certificate list

	X509_STORE      *m_pStore;		    //save CA certificate list
	X509_STORE_CTX  *m_Ctx;		        //save information of store 
	X509            *m_pX509SubCert;	//save server certificate
	EVP_PKEY        *m_pSubCertKey;	    //save server private key	
};

#endif
