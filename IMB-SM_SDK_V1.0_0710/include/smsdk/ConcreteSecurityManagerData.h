#ifndef _CONCRETE_SECURITY_MANAGER_DATA_H_
#define _CONCRETE_SECURITY_MANAGER_DATA_H_

#define CONFIG_FILE                "./smconfig"
#define SECURITY_LOG_DIRECTORY     "./seclog"
#define SECURITY_LOG_LIST_FILE     "loglist.log"
#define SECURITY_LOG_LASTHASH      "lastheaderhash"
#define PROJECTOR_LOG_DIRECTORY    "./projlog"
#define LOG_REPORT_FILE            "./logreport"
#define LOG_SAVE_PATH              "../syslog"   //add by huweihua

#define SMS_ROOT_CA_CERT           "SMSrootCAcert.pem"
#define SMS_LEVEL_CA_CERT          "SMSsecLevelCAcert.pem"
//#define PROJECTOR_ROOT_CA_CERT     "PROJECTrootCAcert.pem"
//#define PROJECTOR_LEVEL_CA_CERT    "PROJECTsecLevelCAcert.pem"

#define XILINX_V6_FW_FILE			"./x_v6.bit"
#define XILINX_V6_CRC_FILE			"./x_v6.crc"
#define XILINX_S6J_FW_FILE			"./x_s6j.bit"
#define XILINX_S6J_CRC_FILE			"./x_s6j.crc"
#define XILINX_S6M_FW_FILE			"./x_s6m.bit"
#define XILINX_S6M_CRC_FILE			"./x_s6m.crc"
#define XILINX_TEMP_UPDATE_FILE		"./updatepack.tar.gz"
#define SM_SW_FILE					"./secmanager.bit"
#define SM_CRC_FILE					"./secmanager.crc"


//计时任务类型
const unsigned int RECONNECT     		= 0x01;		//重连
const unsigned int QUERYSPB      		= 0x02;		//查询放映机的状态
const unsigned int PLAYTIMEOUT   		= 0x03;		//播放

//number constant
const unsigned int THUMBPRINT_SIZE		= 28;		//指纹长度
const unsigned int SIGNED_VLAUE_SIZE	= 512;		//签名值长度
//const unsigned int MAX_PUB_KEY_LEN	= 2048;		//最大公钥长度
//const unsigned int MAX_PRI_KEY_LEN	= 2048;		//最大私钥长度

const int ASM_SUCCESS					= 0;
const int ASM_ERR_INVALID_MESSAGE_TYPE	= 1;
const int ASM_ERR_INVALID_MESSAGE_LEN	= 2;
const int ASM_ERR_FAILED_TO_READ		= 3;
const int ASM_ERR_INSUFFICIENT_BUFFER	= 4;
const int ASM_ERR_TLS_CONNECTION_CLOSED	= 5;

//operation rights
//const unsigned int OPERATION_RIGHT_START_SUITE				= 0x01;
//const unsigned int OPERATION_RIGHT_STOP_SUITE					= 0x02;
//const unsigned int OPERATION_RIGHT_CPL_VALIDATE				= 0x04;
//const unsigned int OPERATION_RIGHT_KDM_VALIDATE				= 0x08;
//const unsigned int OPERATION_RIGHT_TIME_ADJUST				= 0x10;
//const unsigned int OPERATION_RIGHT_ID_AUTHENTICATION			= 0x20;
//const unsigned int OPERATION_RIGHT_SET_CONFIG					= 0x40;
//const unsigned int OPERATION_RIGHT_RESET_CONFIG				= 0x80;
//const unsigned int OPERATION_RIGHT_CLEAR_CONFIG				= 0x100;
//const unsigned int OPERATION_RIGHT_STOP_PLAY					= 0x100;
//const unsigned int OPERATION_RIGHT_AUDIT						= 0x400;
//const unsigned int OPERATION_RIGHT_CONDITION_DETEC			= 0x800;


//------old version-------------
//struct FPGAItr {
//	static const int
//		FrameSequencePlayed = 0,
//		FrameSequenceError = 1,
//		TrackFileIDError = 2,
//		CheckValueError = 3,
//		FrameMICError = 4,
//		UnormalPlay = 5,
//		count = 6;
//
//	static const int
//		hderrBegin = 24,
//		pci = 24,
//		adv202_3 = 25,
//		adv202_2 = 26,
//		adv202_1 = 37,
//		ddr3 = 28,
//		ddr2 = 29,
//		ddr1 = 30,
//		hderrEnd = 31;
//};


//-----new version----------
struct FPGAItr {
	static const int
		FrameSequencePlayed = 0,
		FrameSequenceError = 1,
		TrackFileIDError = 2,
		CheckValueError = 3,
		FrameMICError = 4;

	static const int
		hderrBegin = 15,
		FPGAAESCBCError = 16,
		FPGAAESECBError = 17,
		FPGAHmacError = 18,
		DDRError = 19,
		hderrEnd = 20;
};

struct FPGAData 
{
	//	INTEGRATY_CHECK_STATUS;
	unsigned int m_itrMask : 32;
	//unsigned int m_fill_INTEGRATY_CHECK_STATUS : 26;

	//	INFO WORD0
	unsigned int m_firstFrame : 24;
	unsigned int m_fill_INFO0 : 7;
	unsigned int m_flagAV: 1;

	//	INFO WORD1
	unsigned int m_lastFrame : 24;
	unsigned int m_fill_INFO1 : 8;

	//	INFO WORD2
	unsigned int m_currFrame : 24;
	unsigned int m_fill_INFO2 : 8;

	
	unsigned long m_keyTfi[4];
	unsigned long m_frmTfi[4];
public:
	FPGAData() 
	{
		memset(this, 0, sizeof(*this));
	};
	bool operator==(FPGAData &him) {return memcmp(&him, this, sizeof(him)) == 0;};
public:
	bool hasItr(int itr) {return m_itrMask & (1 << itr);};
	bool isAudio() {return m_flagAV == 0;};
	bool isVideo() {return m_flagAV == 1;};
};

struct DmpPack 
{
	char body[1];
	FPGAData *getFPGAData() 
	{
		return reinterpret_cast<FPGAData*>(body);
	};
	
	void setFPGAData(FPGAData *p) 
	{
		setLen(sizeof(FPGAData));
		*(reinterpret_cast<FPGAData*>(body)) = *p;
	};
	
	bool hasItr(int itr) {return getFPGAData()->hasItr(itr);};
	bool isAudio() {return getFPGAData()->isAudio();};
	bool isVideo() {return getFPGAData()->isVideo();};

	int getLen() 
	{
		return sizeof(FPGAData);
	};
	int getAllLen() 
	{
		return getLen();
	};
	
	void setLen(int len) 
	{
		/*
		char tmp[8];
		sprintf(tmp, "%04d", len);
		memcpy(m_len, tmp, sizeof(m_len));
		*/
	};
};

#endif
