/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName :  SM-Auditorium Security Message
FileName   ： Const.h 
Author     ： huweihua@dadimedia.com
Date       ： 10/03/01
Version    ： v1.0
Description： Auditorium Security Message constant definition
Others     :  
History    ： 
      < Author >    			< Date >             < Modification >
   huweihua@dadimedia.com        10/05/17            Add comment
   sunpeng@oristartech.com		 14/02/19			 Add  messages
********************************************/  

#ifndef _CONST_H_
#define _CONST_H_


//通用数据类型定义
//General Data Type definition
#ifdef WIN32
	typedef unsigned __int64    UInt64;    
#else
	typedef unsigned long long  UInt64;
#endif
    typedef unsigned char       UInt8;
    typedef unsigned int        UInt32;
    typedef unsigned char       TEXT;
    typedef char                Int8;
    typedef int                 Int32;

//tangquanfa add start
typedef unsigned short			UInt16;
const UInt32 KLV_KEY_LEN		= 16;
const UInt32 KLV_LEN_LEN		=  4;

//tangquanfa add end
	
//normative length
const  UInt32 UL_KEY_VALUE_LEN  = 16;    //the length of key in KLV structure
const  UInt32 UL_LEN_VALUE_LEN  =  4;    //the length of length in KLV structure
const  UInt32 REQUEST_ID_LEN    =  4;    //the length of request id
const  UInt32 USERNAME_MAX_LEN  = 18;    //the maximum length of user name
const  UInt32 PASSWORD_MAX_LEN  = 14;    //the maximum length of password
const  UInt32 USERID_MAX_LEN    = 58;    //the maximum length of user Certificate Thumbprint
const  UInt32 ROLE_MAX_LEN      = 8;     //the maximum length of user Certificate Thumbprint
const  UInt32 IP_MAX_LEN        = 16;    //the maximum length of IP
const  UInt32 KDM_ID_MAX_LEN    = 36;    //the maximum length of KDM ID
const  UInt32 CPL_ID_MAX_LEN    = 36;    //the maximum length of CPL ID

//General Response Elements
//通用回复状态值，取值为0-3
const UInt8 RRP_SUCCESSFUL  = 0;         //request successfully processed
const UInt8 RRP_FAILED      = 1;         //responder unable to process request
const UInt8 RRP_INVALID     = 2;         //invalid parameter or command structure
const UInt8 RESPONDERBUSY   = 3;         //responder too busy to process request

//Common UL Key Value for all ASM Commands
//SMPTE 430-6-2008定义
const UInt8 OBJECT_IDENTIFIER             	= 0x06; //Object ID
const UInt8 LABEL_SIZE                    	= 0x0E; //Length of UL
const UInt8 SUB_DESIGNATOR                	= 0x2B; //Sub identifier
const UInt8 SMPTE_DESIGNATOR              	= 0x34; //SMPTE identifier
const UInt8 REGISTRY_CATEGORY_DESIGNATOR  	= 0x02; //KLV Groups(Sets and Packs)
const UInt8 REGISTRY_DESIGNATOR           	= 0x05; //Fixed Length Pack
const UInt8 STRUCTURE_DESIGNATOR          	= 0x01; //Groups Dictionary 
const UInt8 VERSION_NUMBER                	= 0x01; //Registry Version: Dictionary version 1 
const UInt8 ITEM_DESIGNATOR               	= 0x02; //Administration
const UInt8 ORGANIZATION                  	= 0x07; //Access Control
const UInt8 APPLICATION                   	= 0x01; //Auditorium Security
const UInt8 RESERVED                      	= 0x00; //Not assigned

//Set/Pack Kind
//消息类型码定义
const UInt32 BAD_REQUEST_RESPONSE          	= 0x0101;  

const UInt32 TIME_REQUEST                  	= 0x0210;
const UInt32 TIME_RESPONSE                 	= 0x0211;          
const UInt32 EVENT_LIST_REQUEST            	= 0x0212;
const UInt32 EVENT_LIST_RESPONSE           	= 0x0213;
const UInt32 EVENT_ID_REQUEST              	= 0x0214;
const UInt32 EVENT_ID_RESPONSE             	= 0x0215;
const UInt32 SPB_QUERY_REQUEST             	= 0x0216;
const UInt32 SPB_QUERY_RESPONSE            	= 0x0217;

const UInt32 LE_KEY_LOAD_REQUEST           	= 0x0320;
const UInt32 LE_KEY_LOAD_RESPONSE          	= 0x0321;
const UInt32 LE_KEY_QUERY_ID_REQUEST       	= 0x0322;
const UInt32 LE_KEY_QUERY_ID_RESPONSE      	= 0x0323;
const UInt32 LE_KEY_QUERY_ALL_REQUEST      	= 0x0324;
const UInt32 LE_KEY_QUERY_ALL_RESPONSE     	= 0x0325;
const UInt32 LE_KEY_PURGE_ID_REQUEST       	= 0x0326;
const UInt32 LE_KEY_PURGE_ID_RESPONSE      	= 0x0327;
const UInt32 LE_KEY_PURGE_ALL_REQUEST      	= 0x0328;
const UInt32 LE_KEY_PURGE_ALL_RESPONSE     	= 0x0329;

const UInt32 START_SUITE_REQUEST           	= 0x0430;
const UInt32 START_SUITE_RESPONSE          	= 0x0431;          
const UInt32 STOP_SUITE_REQUEST            	= 0x0432;
const UInt32 STOP_SUITE_RESPONSE           	= 0x0433;
const UInt32 CPL_VALIDATE_REQUEST          	= 0x0434;
const UInt32 CPL_VALIDATE_RESPONSE         	= 0x0435;
const UInt32 KDM_VALIDATE_REQUEST          	= 0x0436;
const UInt32 KDM_VALIDATE_RESPONSE         	= 0x0437;
const UInt32 TIME_ADJUST_REQUEST           	= 0x0438;
const UInt32 TIME_ADJUST_RESPONSE          	= 0x0439;

//--add by huweihua for multi CPLs and KDMs--
const UInt32 CPLS_VALIDATE_REQUEST         	= 0x043A;
const UInt32 CPLS_VALIDATE_RESPONSE        	= 0x043B;
const UInt32 KDMS_VALIDATE_REQUEST         	= 0x043C;
const UInt32 KDMS_VALIDATE_RESPONSE        	= 0x043D;
//--end add--

//--added and modified by sunpeng--
const UInt32 ID_AUTHENTICATION_REQUEST     	= 0x1010;
const UInt32 ID_AUTHENTICATION_RESPONSE    	= 0x1011;
const UInt32 SET_CONFIG_REQUEST            	= 0x1012;
const UInt32 SET_CONFIG_RESPONSE           	= 0x1013;
const UInt32 GET_CONFIG_REQUEST          	= 0x1014;
const UInt32 GET_CONFIG_RESPONSE         	= 0x1015;
const UInt32 START_PLAY_REQUEST          	= 0x1016;
const UInt32 START_PLAY_RESPONSE         	= 0x1017;
const UInt32 STOP_PLAY_REQUEST             	= 0x1018;
const UInt32 STOP_PLAY_RESPONSE            	= 0x1019;
const UInt32 AUDIT_REQUEST                 	= 0x101A;
const UInt32 AUDIT_RESPONSE                	= 0x101B;
const UInt32 SMS_SPB_QUERY_REQUEST       	= 0x101C;
const UInt32 SMS_SPB_QUERY_RESPONSE      	= 0x101D;

const UInt32 GET_LOG_REQUEST               	= 0x1020;
const UInt32 GET_LOG_RESPONSE              	= 0x1021;
const UInt32 LOGOUT_REQUEST                	= 0x1022;
const UInt32 LOGOUT_RESPONSE               	= 0x1023;
const UInt32 SET_CERTCHAIN_REQUEST          = 0x1024;
const UInt32 SET_CERTCHAIN_RESPONSE         = 0x1025;
const UInt32 GET_CERTCHAIN_REQUEST          = 0x1026;
const UInt32 GET_CERTCHAIN_RESPONSE         = 0x1027;
const UInt32 CLEAR_CERT_REQUEST            	= 0x1028;
const UInt32 CLEAR_CERT_RESPONSE           	= 0x1029;
const UInt32 FIRMWARE_UPDATE_REQUEST   		= 0x102A;
const UInt32 FIRMWARE_UPDATE_RESPONSE    	= 0x102B;
const UInt32 CLEAR_CSPS_REQUEST         	= 0x102C;
const UInt32 CLEAR_CSPS_RESPONSE        	= 0x102D;

const UInt32 INGEST_KDM_REQUEST        		= 0x1030;
const UInt32 INGEST_KDM_RESPONSE       		= 0x1031;
const UInt32 INGEST_CPL_REQUEST       		= 0x1032;
const UInt32 INGEST_CPL_RESPONSE      		= 0x1033;
const UInt32 DELETE_KDM_REQUEST            	= 0x1034;
const UInt32 DELETE_KDM_RESPONSE           	= 0x1035;
const UInt32 DELETE_CPL_REQUEST       		= 0x1036;
const UInt32 DELETE_CPL_RESPONSE      		= 0x1037;
const UInt32 GET_CERTIFICATE_REQUEST       	= 0x1038;
const UInt32 GET_CERTIFICATE_RESPONSE      	= 0x1039;
const UInt32 GET_CPLLIST_REQUEST       		= 0x103A;
const UInt32 GET_CPLLIST_RESPONSE      		= 0x103B;
const UInt32 GET_KDMLIST_REQUEST       		= 0x103C;
const UInt32 GET_KDMLIST_RESPONSE      		= 0x103D;
const UInt32 GET_KEYMAP_REQUEST       		= 0x103E;
const UInt32 GET_KEYMAP_RESPONSE      		= 0x103F;

const UInt32 INIT_MARRIAGE_REQUEST       	= 0x1040;
const UInt32 INIT_MARRIAGE_RESPONSE      	= 0x1041;
const UInt32 SDTAMP_TERM_REQUEST       		= 0x1042;
const UInt32 SDTAMP_TERM_RESPONSE      		= 0x1043;

const UInt32 GETFILE_REQUEST				= 0x2051;
const UInt32 GETFILE_RESPONSE				= 0x2052;
//--end add--

//error code
//函数返回错误码定义
const UInt32 SUCCESSE              = 0;  //successfully processed
const UInt32 PARAMETER_ERROR       = 1;  //invalid parameter 
const UInt32 ADDKLVKEYVALUE_ERROR  = 2;  //add key in KLV structure error
const UInt32 ADDKLVLENVALUE_ERROR  = 3;  //add length in KLV structure error
const UInt32 ADDREQUESTID_ERROR    = 4;  //add request id error
const UInt32 PARSEREQUESTID_ERROR  = 5;  //parse request id error


//add by huweihua 2010-10-29
//code of each config

const UInt32 SYS_PROJIP              = 0x0001;  //add by huweihua
const UInt32 SYS_LEFLAG              = 0x0002;  //add by huweihua
const UInt32 SYS_PROJ_CERTCHAINFLAG  = 0x0003;  //add by huweihua
const UInt32 SYS_TIMEZONE            = 0x0004;  //add by huweihua
const UInt32 SYS_LOGTRANSFER_IP      = 0x0005;  //add by sunpeng

const UInt32 SYS_VERSION             = 0x1001;  //add by huweihua
const UInt32 SYS_DEVICEID            = 0x1002;  //add by huweihua
const UInt32 SYS_CONFIGFILE          = 0x1003;  //add by huweihua
const UInt32 SYS_TIME          		 = 0x1004; 	//add by sunpeng

//add by huweihua 2010-10-29
//the maximum length  of each config

const UInt32 SYS_PROJIP_LEN              = 16;  //add by huweihua
const UInt32 SYS_LEFLAG_LEN              = 1;  //add by huweihua
const UInt32 SYS_PROJ_CERTCHAINFLAG_LEN  = 1;  //add by huweihua
const UInt32 SYS_TIMEZONE_LEN            = 3;  //add by huweihua

#endif
