#ifndef _CONCRETE_SECURITY_MANAGER_H_
#define _CONCRETE_SECURITY_MANAGER_H_
#include <string>
#include <openssl/ssl.h>

#ifdef QUITCMD
extern bool autoquitflag;
#endif

//[IMBSM v1.0_DCEventLog] added by chenjingdong, 2014-05-30 start
#define MAX_LOG_STR_LEN 256

//log type
typedef enum
{
	SECURITY_LOG,		//安全日志    //security log
	SM_LOG,				//sm系统日志  //system running log
	PROJECTOR_LOG,		//放映机日志  //projector log
}DciSmLogType;
//[IMBSM v1.0_DCEventLog] end

//log level
typedef enum
{
	ERROR,
	WARN,
	INFO,
	DEBUG,
	FATAL,
}DciSmLogLevel;

extern const int DCI_SM_SUCCESS;
extern const int DCI_SM_FAIL_TO_INIT_TLS_CLIENT_MUTEX;
extern const int DCI_SM_FAIL_TO_INGORE_PIPE_SIGNAL;
extern const int DCI_SM_FAIL_TO_INIT_LOG_QUEUE;
extern const int DCI_SM_FAIL_TO_CREATE_TLS_CLIENT;
extern const int DCI_SM_FAIL_TO_INIT_TLS_CMD_QUEUE;
extern const int DCI_SM_FAIL_TO_INIT_TIMING_TASK_QUEUE;
extern const int DCI_SM_FAIL_TO_CREATE_TLS_CLIENT_THREAD;
extern const int DCI_SM_FAIL_TO_INIT_TLS_SERVER_THREAD;
extern const int DCI_SM_FAIL_TO_CREATE_TLS_SERVER_THREAD;
extern const int DCI_SM_FAIL_TO_START_TLS_SERVER;
extern const int DCI_SM_FAIL_TO_INIT_FIPS_MODE;
extern const int DCI_SM_SHA256_TEST_NOT_PASS;
extern const int DCI_SM_AES_128_CFB_TEST_NOT_PASS;
extern const int DCI_SM_RSA_TEST_NOT_PASS;
extern const int DCI_SM_FAIL_TO_OPEN_MB_INTERFACE;
extern const int DCI_SM_FAIL_TO_RETRIEVE_CSPS;
extern const int DCI_SM_FAIL_TO_OPEN_CERT_FILE;
extern const int DCI_SM_FAIL_TO_CREATE_CERT_BUFFER;
extern const int DCI_SM_FAIL_TO_READ_CERT;
extern const int DCI_SM_FAIL_TO_LOAD_CERT;
extern const int DCI_SM_INVALID_CERT_FORMAT;
extern const int DCI_SM_INVALID_CERT_CHAIN;
extern const int DCI_SM_FAIL_TO_PARSE_CERT_CHAIN;
extern const int DCI_SM_FAIL_TO_GET_PUBLIC_KEY;
extern const int DCI_SM_FAIL_TO_CREATE_TMP_KEY_FILE;
extern const int DCI_SM_FAIL_TO_WRITE_TMP_KEY_FILE;
extern const int DCI_SM_FAIL_TO_CREATE_EVP_PRIVATE_KEY;
extern const int DCI_SM_FAIL_TO_DELETE_TMP_KEY_FILE;
extern const int DCI_SM_FAIL_TO_CONVERT_LEAF_CERT;
extern const int DCI_SM_FAIL_TO_CONVERT_PUBLIC_KEY;
extern const int DCI_SM_FAIL_TO_CONVERT_PRIVATE_KEY;
extern const int DCI_SM_FAIL_TO_EXTRACT_CERT_FROM_LIST;
extern const int DCI_SM_FAIL_TO_EXTRACT_CERT_INFO;
extern const int DCI_SM_FAIL_TO_LOAD_INI_FILE;
extern const int DCI_SM_FAIL_TO_READ_INI_FILE;
extern const int DCI_SM_NOT_INITIALIZED;
extern const int DCI_SM_USER_NOT_LOGIN;
extern const int DCI_SM_CPL_ID_NOT_EXIST;
extern const int DCI_SM_KDM_ID_NOT_EXIST;
extern const int DCI_SM_AUDIT_SECURITY_LOG_NOT_PASS;
extern const int DCI_SM_FAIL_TO_START_LOGFILE_TRANS_SERVER;  	//add by huweihua
extern const int DCI_SM_HARDWARE_TEST_FAIL;                   	//add by huweihua
extern const int DCI_SM_FAIL_TO_CREATE_CATCH_MOVIE_EXCP_THREAD;	//add by huweihua
extern const int DCI_SM_FAIL_TO_INIT_LOG_DIRECTORY; 			//add by huweihua
extern const int DCI_SM_FAIL_TO_INIT_LOG_THREAD;       			//add by huweihua
extern const int DCI_SM_HARDWARE_OPEN_DRIVER_ERROR;    			//add by huweihua
extern const int DCI_SM_HARDWARE_READ_DRIVER_ERROR;				//add by huweihua
extern const int DCI_SM_FAIL_TO_INIT_SYS_TIME;   				//add by sunpeng
extern const int DCI_SM_FAIL_TO_INIT_DSP;          				//add by huweihua
extern const int DCI_SM_FAIL_TO_OPEN_DSP;          				//add by huweihua
extern const int DCI_SM_FIRMWARE_INTEGRITY_TEST_FAIL;  			//add by sunpeng

class ConcreteSecurityManager 
{
public:
	virtual int Start();
	virtual void Stop(void);
	
	virtual int  GetKDMID(std::string &pkdmid);
	virtual bool GetFMIKFlag();
	virtual bool GetFMAKFlag();
	virtual int  GetAuthID(std::string &puserid);
	virtual int  GetCPLID(std::string &pcplid);
	virtual int  GetDevicethumb(std::string &pdevicethumb);
	virtual int  SetPlayoutCompleteFlag(int iscompleteflag);
	virtual int  InsertLog(DciSmLogLevel level, const char *msg);
	
public:
	static ConcreteSecurityManager *GetSecurityManager(void);
private:
	ConcreteSecurityManager(void);
	static ConcreteSecurityManager *m_SecurityManager;
};

#endif
