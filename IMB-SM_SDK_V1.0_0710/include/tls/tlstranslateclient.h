/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  TLS communication 
FileName   ： tlstranslateclient.h
Author     ： huweihua@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： client of TLS communication
Others     :  
History    ： 
      < Author >    			< Date >             < Modification > 
********************************************/  
#ifndef _TLS_TRANSLATE_CLIENT_H_
#define _TLS_TRANSLATE_CLIENT_H_

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

#include <fcntl.h>
#include <memory.h>
#include <errno.h>
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


#include "p12/pkcs12info.h"
#include "smsdk/errornumber.h"


#ifdef WIN32
	#define    SOKLEN    int
#else
	#define    SOKLEN    socklen_t
#endif

class CTLS_Translate_Client
{
public:
    
    /************************************************* 
	Function   ： CTLS_Translate_Client()
	Description： constructor of CTLS_Translate_Client class
	Input      ： a_pP12CACertListFile:  P12 file including CA certificate list 
	              a_pP12CACertListFilePass: the password of P12 file specified by 'a_pP12CACertListFile'
	              a_pP12CertAndKeyFile: P12 file including local certificate and local private key 
	              a_pP12CertAndKeyFilePass: the password of P12 file specified by 'a_pP12CertAndKeyFile'
	Output     ： 
	Return     ：
	Others     :        
	*************************************************/
	CTLS_Translate_Client(
        const char  *a_pP12CACertListFile,
        const char  *a_pP12CACertListFilePass,
        const char  *a_pP12CertAndKeyFile,
        const char  *a_pP12CertAndKeyFilePass);

    /************************************************* 
	Function   ： CTLS_Translate_Client()
	Description： constructor of CTLS_Translate_Client class
	Input      ： a_pCertFile : local certificate
	              a_CACertFile: CA certificate list 
	              a_pKeyFile  : local private key 
	Output     ： 
	Return     ：
	Others     :        
	*************************************************/
	CTLS_Translate_Client(
        X509              *a_pCertFile, 
        vector<X509 *>    &a_CACertFile, 
        EVP_PKEY          *a_pKeyFile);	

	/************************************************* 
	Function   ： ~CTLS_Translate_Client()
	Description： destructor of CTLS_Translate_Client class
	Input      ： 
	Output     ： 
	Return     ：
	Others     :        
	*************************************************/ 
	~CTLS_Translate_Client();
	
    /************************************************* 
	Function   ： CTLS_Translate_Client_Init()
	Description： initailize TLS  Client
	Input      ： a_iVerifyFlag :TLS Verify mode. SSL_VERIFY_PEER or SSL_VERIFY_NONE
	Output     ： 
	Return     ：error code, refer to smsdk\errornumber.h
	Others     :        
	*************************************************/	
	int CTLS_Translate_Client_Init(const int a_iVerifyFlag);
	
    /************************************************* 
	Function   ： TLS_StartUp()
	Description： connect server on TLS layer
	Input      ： a_pIP   : server IP 
	              a_iPort : server port 	              
	Output     ： 
	Return     ： error code, refer to smsdk\errornumber.h
	Others     :        
	*************************************************/				
	int TLS_StartUp(
	const char  *a_pIP,
	const int    a_iPort);
	
	/************************************************* 
	Function   ： TLS_Read()
	Description： receive data from server 
	Input      ： a_pBuf    : data buffer
	              a_iSize   : the size of data to be received
	              a_iTimeOut: time out interval
	                  [a_iTimeOut < 0]  block forever
	                  [a_iTimeOut = 0]  none-block
	                  [a_iTimeOut > 0]  block 'a_iTimeOut' seconds                  
	Output     ： a_iSizeOut: the actually size of data received
	Return     ： error code, refer to smsdk\errornumber.h
	Others     :        
	*************************************************/
    int TLS_Read(/* in*/ void     *a_pBuf,       
                 /* in*/ const int a_iSize,        
                 /* in*/ int       a_iTimeOut,     
                 /*out*/ int      *a_iSizeOut);     

	/************************************************* 
	Function   ： TLS_Write()
	Description： send data to server 
	Input      ： a_pBuf    : data buffer
	              a_iSize   : the size of data to be sent
	              a_iTimeOut: time out interval
	                  [a_iTimeOut < 0]  block forever
	                  [a_iTimeOut = 0]  none-block
	                  [a_iTimeOut > 0]  block 'a_iTimeOut' seconds                   
	Output     ： a_iSizeOut: the actually size of data sent
	Return     ： error code, refer to smsdk\errornumber.h
	Others     :        
	*************************************************/
	int TLS_Write(/* in*/ void     *a_pbuf,        
                  /* in*/ const int a_iSize,        
                  /* in*/ int       a_iTimeOut,     
                  /*out*/ int      *a_iSizeOut);    

	/************************************************* 
	Function   ： TLS_Get_Peer_Cert()
	Description： get certificate of server
	Input      ：                 
	Output     ： PeerCert: the certificate of server
	Return     ： error code, refer to smsdk\errornumber.h
	Others     :        
	*************************************************/
    int TLS_Get_Peer_Cert(/*out*/const X509 **PeerCert);  //接收证书指针的地址

	/************************************************* 
	Function   ： TLS_Close()
	Description： Close the TLS connection 
	Input      ：                 
	Output     ：
	Return     ： error code, refer to smsdk\errornumber.h
	Others     :        
	*************************************************/
	int TLS_Close();
		
private:

	/************************************************* 
	Function   ： TLS_Creat_HandShake()
	Description： TLS-HandShake with server
	Input      ： a_iSocketHandle :Socket handle created by TLS_InitSocket           
	Output     ： 
	Return     ： error code, refer to smsdk\errornumber.h
	Others     :        
	*************************************************/
	int TLS_Creat_HandShake(/* in*/const int a_iSocketHandle);

    /************************************************* 
	Function   ： TLS_InitSocket()
	Description： establish connection on TCP layer
	Input      ：           
	Output     ： 
	Return     ： error code, refer to smsdk\errornumber.h
	Others     :        
	*************************************************/
	int TLS_InitSocket();

	/************************************************* 
	Function   ： TLS_SetData()
	Description： configure parameters:certificate , private key , CA certificate list
	Input      ：           
	Output     ： 
	Return     ： error code, refer to smsdk\errornumber.h
	Others     :        
	*************************************************/
	int TLS_SetData();
	
	/************************************************* 
	Function   ： TLS_InitContext()
	Description： initialize TLS context
	Input      ： a_iVerifyFlag:( SSL_VERIFY_NONE or SSL_VERIFY_PEER )
	              SSL_VERIFY_NONE: do not verify server
	              SSL_VERIFY_PEER: verify server
	Output     ： 
	Return     ： error code, refer to smsdk\errornumber.h
	Others     :        
	*************************************************/
	int TLS_InitContext(/*in*/const int a_iVerifyFlag);

	/************************************************* 
	Function   ： TLS_SetCaCertList()
	Description： specify CA certificate list
	Input      ： a_CaCertList: CA certificate list 
	Output     ： 
	Return     ： error code, refer to smsdk\errornumber.h
	Others     :        
	*************************************************/
	int TLS_SetCaCertList(/*in*/vector<X509*>& a_CaCertList);
	
	/************************************************* 
	Function   ： TCP_Connect_Nonblock()
	Description： establish a none-block connection with server on TCP layer
	Input      ： 	sockfd - SOCKET FD
				  	salen - size of 'saptr'
				  	nsec - timeout interval
	Output     ： saptr - a pointer to a 'sockaddr' object.
	Return     ： error code, refer to smsdk\errornumber.h
	Others     :        
	*************************************************/
    int TCP_Connect_Nonblock(
			/*in*/int                    sockfd, 
			/*in*/const struct sockaddr *saptr, 
			/*in*/SOKLEN                 salen, 
			/*in*/int                    nsec);

	char             *m_pIP;				 //the IP address of server
	int               m_iPort;				 //the port of server listening
	int               m_iSockHandle;	     //socket descriptor 
	SSL              *m_pSSLStruct;			 //SSL entity in context of tls protocol	
	SSL_CTX          *m_pSSLContext;		 //context of tls protocol

	X509_STORE       *m_pStore;	  	         //save CA certificate list
	vector<X509 *>    m_CACertFile;          //save CA certificate list
	X509             *m_pX509SubCert;		 //save client certificate
	EVP_PKEY         *m_pSubCertKey;	     //save client private key
	CPKCS12Info       m_tmpPkcs12Info;       //save information of P12 file
	
	//对P12文件处理需要的变量
	char             *m_pP12CACertListFileName;	   	//P12 file including CA certificate list
	char             *m_pP12CACertListPass;		   	//the password of P12 file including CA certificate list 
	char             *m_pP12CertAndKeyFileName;	   	//P12 file including local certificate and local private key 
	char             *m_pP12CertAndKeyPass;		   	//the password of P12 file including local certificate and local private key 

	short             TypeFlag;              		//the flag of cerificate type: 0=X509 1=P12   

};

#endif
