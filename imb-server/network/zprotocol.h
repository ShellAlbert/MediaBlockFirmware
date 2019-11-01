/**
 * @file zprotocol.h
 * @date May 30,2014
 * @author zhangshaoyan@oristartech.com
 * @version 1.0
 * @brief define network protocol between clients and server
 */
#ifndef _ZPROTOCOL_H__
#define _ZPROTOCOL_H__
#include <zdata_types.h>

/**
 * @brief default server tcp listen port
 */
#define DEF_SERVER_TCP_PORT	1987

/**
 * @brief frame header added by zsy for stream data parse
 */
#define ZHEAD1	0x19
#define ZHEAD2	0x86
#define ZHEAD3	0x10
#define ZHEAD4	0x14
#define ZHEAD5	0x19
#define ZHEAD6	0x87
#define ZHEAD7	0x09
#define ZHEAD8	0x01

/**
 * @brief const code define
 * packet types: used to determine network packet types.
 * return codes: define return code information.
 */
enum
{

  /**
   * Iterator IMB card information.
   */
  PKT_QUERY_CARD_INFO = 0x0001, ///<SDK --> IMB server.
  PKT_QUERY_CARD_INFO_ACK = 0x0002, ///<IMB server --> SDK.

  /**
   * query cpu information.
   */
  PKT_QUERY_CPU_INFO = 0x0003, ///<SDK --> IMB server.
  PKT_QUERY_CPU_INFO_ACK = 0x0004, ///<IMB server --> SDK.

  /**
   * query memory information.
   */
  PKT_QUERY_MEM_INFO = 0x0005, ///<SDK --> IMB server.
  PKT_QUERY_MEM_INFO_ACK = 0x0006, ///<IMB server --> SDK.

  /**
   * read/write FPGA register.
   */
  PKT_RW_FPGA_REGISTER = 0x0007,  ///<SDK --> IMB server.
  PKT_RW_FPGA_REGISTER_ACK = 0x0008, ///<IMB server --> SDK.

  /**
   * transfer DMA data.
   * include video & audio.
   */
  PKT_TRANSFER_DMA_DATA = 0x0009,  ///<SDK --> IMB server.
  PKT_TRANSFER_DMA_DATA_ACK = 0x000A, ///<IMB server --> SDK.

  /**
   * open device file.
   */
  PKT_OPEN_DEVICE_FILE = 0x000B,  ///<SDK --> IMB server.
  PKT_OPEN_DEVICE_FILE_ACK = 0x000C, ///<IMB server --> SDK.

  /**
   * close device file.
   */
  PKT_CLOSE_DEVICE_FILE = 0x000D,
  PKT_CLOSE_DEVICE_FILE_ACK = 0x000E,

  /**
   * packet types for SM client & SM server.
   *
   * added by zhangshaoyan at October 14,2014.
   */

  /**
   * step2.
   * ret=sm->loadCertificateChainFile("certchain.data");
   */
  PKT_SM_LOAD_CERTCHAIN_FILE = 0x1001,
  PKT_SM_LOAD_CERTCHAIN_FILE_ACK = 0x1002,

  /**
   * step3.
   * ret=sm->loadPrivateKeyFile("SMStheLeafprikey.pem");
   */
  PKT_SM_LOAD_PRIVATEKEY_FILE = 0x1003,
  PKT_SM_LOAD_PRIVATEKEY_FILE_ACK = 0x1004,

  /**
   * step4.
   * ret=sm->connect();
   */
  PKT_SM_CONNECT = 0x1005,
  PKT_SM_CONNECT_ACK = 0x1006,

  /**
   * step5.
   * ret=sm->startSuite();
   */
  PKT_SM_STARTSUITE = 0x1007,
  PKT_SM_STARTSUITE_ACK = 0x1008,

  /**
   * step6.
   * ret=sm->uploadCplFile();
   */
  PKT_SM_UPLOAD_CPL_FILE = 0x1009,
  PKT_SM_UPLOAD_CPL_FILE_ACK = 0x100A,

  /**
   * step7.
   * ret=sm->uploadKdmFile();
   */
  PKT_SM_UPLOAD_KDM_FILE = 0x100B,
  PKT_SM_UPLOAD_KDM_FILE_ACK = 0x100C,

  /**
   * step8.
   * ret=sm->playShow();
   */
  PKT_SM_PLAYSHOW = 0x100D,
  PKT_SM_PLAYSHOW_ACK = 0x100E,

  /**
   * step9.
   * ret=sm->stopShow();
   *
   * TMmRc stopShow( const char *authId );
   */
  PKT_SM_STOPSHOW = 0x100F,
  PKT_SM_STOPSHOW_ACK = 0x1010,

  /**
   * step10.
   * ret=sm->purgeCpl();
   */
  PKT_SM_PURGECPL = 0x1011,
  PKT_SM_PURGECPL_ACK = 0x1012,

  /**
   * step11.
   * ret=sm->stopSuite();
   *
   * TMmRc stopSuite();
   */
  PKT_SM_STOPSUITE = 0x1013,
  PKT_SM_STOPSUITE_ACK = 0x1014,

  /**
   * added by zhangshaoyan at October 28,2014.
   * for support other features of SM.
   */

  /**
   * TMmRc getCplList( inner_sm::UuidValue *cplUuidArray, uint32_t *arrayLen );
   */
  PKT_SM_GETCPLLIST = 0x1015,
  PKT_SM_GETCPLLIST_ACK = 0x1016,

  /**
   * TMmRc getKdmList( const inner_sm::UuidValue &cplUuid, inner_sm::UuidValue *kdmUuidArray, uint32_t *arrayLen );
   */
  PKT_SM_GETKDMLIST = 0x1017,
  PKT_SM_GETKDMLIST_ACK = 0x1018,

  /**
   * TMmRc checkShow( const inner_sm::UuidValue *cplUuidArray, uint32_t arrayLen, uint64_t checkTime, uint64_t *keyExpTime = 0 );
   */
  PKT_SM_CHECKSHOW = 0x1019,
  PKT_SM_CHECKSHOW_ACK = 0x101A,

  /**
   * TMmRc adjustTime( const char *authId, uint32_t diff );
   */
  PKT_SM_ADJUSTTIME = 0x101B,
  PKT_SM_ADJUSTTIME_ACK = 0x101C,

  /**
   * TMmRc getCertificate( uint32_t which, uint8_t *buffer, uint32_t *buffersize );
   */
  PKT_SM_GETCERTIFICATE = 0x101D,
  PKT_SM_GETCERTIFICATE_ACK = 0x101E,

  /**
   * TMmRc queryStatus( SM_OPERATION *smOp, SUITE_STATUS *suiteStat, uint64_t *secureTime, int32_t *time_adjust );
   */
  PKT_SM_QUERYSTATUS = 0x1020,
  PKT_SM_QUERYSTATUS_ACK = 0x1021,

  /**
   * TMmRc getLogReport( uint8_t *buffer, uint32_t *buffersize, uint64_t startTime, uint64_t endTime, uint64_t *lastLogTime );
   */
  PKT_SM_GETLOGREPORT = 0x1022,
  PKT_SM_GETLOGREPORT_ACK = 0x1023,

  /**
   * TMmRc initiateMarriage( const char *authId );
   */
  PKT_SM_INITIATEMARRIAGE = 0x1024,
  PKT_SM_INITIATEMARRIAGE_ACK = 0x1025,

  /**
   * TMmRc serviceDoorTamperTermination( const char *authId );
   */
  PKT_SM_SERVICEDOORTAMPERTERMINATION = 0x1026,
  PKT_SM_SERVICEDOORTAMPERTERMINATION_ACK = 0x1027,

  /**
   * TMmRc getKeyMap( KeyMap *keymapArray, uint32_t *numberOfEntries );
   */
  PKT_SM_GETKEYMAP = 0x1028,
  PKT_SM_GETKEYMAP_ACK = 0x1029,

  /**
   * TMmRc addCertificate( void *cert );
   */
  PKT_SM_ADDCERTIFICATE = 0x102A,
  PKT_SM_ADDCERTIFICATE_ACK = 0x102B,

  /**
   * TMmRc usePrivateKey( void *pkey );
   */
  PKT_SM_USEPRIVATEKEY = 0x102C,
  PKT_SM_USEPRIVATEKEY_ACK = 0x102D,

  /**
   * TMmRc zeroize( const char *authId );
   */
  PKT_SM_ZEROIZE = 0x102E,
  PKT_SM_ZEROIZE_ACK = 0x102F,

  /**
   * TMmRc uploadCplBuffer(const uint8_t *cplBuffer, uint32_t bufferSize, CPL_ASSET_EXCEPTION assetExc = CplException_None);
   */
  PKT_SM_UPLOADCPLBUFFER = 0x1030,
  PKT_SM_UPLOADCPLBUFFER_ACK = 0x1031,

  /**
   * TMmRc uploadKdmBuffer(const uint8_t *kdmBuffer, uint32_t bufferSize, AesKeyMap *subKeyArray = 0, uint32_t *numberOfEntries = 0);
   */
  PKT_SM_UPLOADKDMBUFFER = 0x1032,
  PKT_SM_UPLOADKDMBUFFER_ACK = 0x1033,

  /**
   * Play mode control.
   * Modified by zhangshaoyan at November 21,2014.
   * Note:
   * Move Play mode control from SDK to IMB server.
   */
  /**
   * Start.
   */
  PKT_PLAY_MODE_START = 0x2000,
  PKT_PLAY_MODE_START_ACK = 0x2001,
  /**
   * Pause.
   */
  PKT_PLAY_MODE_PAUSE = 0x2002,
  PKT_PLAY_MODE_PAUSE_ACK = 0x2003,
  /**
   * Forward.
   */
  PKT_PLAY_MODE_FORWARD = 0x2004,
  PKT_PLAY_MODE_FORWARD_ACK = 0x2005,
  /**
   * Backward.
   */
  PKT_PLAY_MODE_BACKWARD = 0x2006,
  PKT_PLAY_MODE_BACKWARD_ACK = 0x2007,
  /**
   * Stop.
   */
  PKT_PLAY_MODE_STOP = 0x2008,
  PKT_PLAY_MODE_STOP_ACK = 0x2009,

  /**
   * UDP packet type for IP finder.
   */
  PKT_UDP_QUERY_SERVER_IP = 0x3000, ///<
  PKT_UDP_QUERY_SERVER_IP_ACK = 0x3001, ///<

  /**
   * subtitle related packet types.
   * added by zhangshaoyan at November 2,2014.
   */
  PKT_SUBTITLE_FILE = 0x4000, ///<
  PKT_SUBTITLE_FILE_ACK = 0x4001, ///<
  PKT_SUBTITLE_OVERLAY_ELEMENT = 0x4002, ///<
  PKT_SUBTITLE_OVERLAY_ELEMENT_ACK = 0x4003, ///<

  /**
   * thread status code
   */
  Thread_Status_Running = 0x5000,
  Thread_Status_Sleep = 0x5001,
  Thread_Status_Exit = 0x5002,
  /**
   * error code define list.
   * each section can expand to 100 items.
   */

  /**
   * general section.
   */
  ZRC_Success = 0, ///<success.
  ZRC_NullPointer = -1, ///<invalid null pointer.
  ZRC_MemOverFlow = -2, ///<too big data.
  ZRC_SystemCallFailed = -3, ///<system call failed.
  ZRC_OperationTimeout = -4, ///<timeout.

  /**
   * query information section.
   */
  ZRC_GetIMBCardInfoFailed = -100, ///<get remote IMB card information failed.
  ZRC_GetIMBCardCpuInfoFailed = -101, ///<get CPU information failed.
  ZRC_GetIMBCardMemInfoFailed = -102, ///<get Memory information failed.

  /**
   * device file & FPGA operation section.
   */
  ZRC_DeviceFileNotOpened = -200,
  ZRC_DeviceFileOpenFailed = -201, ///<open device file failed.
  ZRC_DeviceFileCloseFailed = -202, ///<close device file failed.
  ZRC_ReadFPGARegisterFailed = -203, ///<read FPGA register failed.
  ZRC_WriteFPGARegisterFailed = -204, ///<write FPGA register failed.
  ZRC_TransferDMADataFailed = -205, ///<transfer DMA data failed.
  ZRC_ActiveIPCoreFailed = -206, ///<active Intopix IP core failed.

  /**
   * socket related section.
   */
  ZRC_SocketNotCreate = -300,
  ZRC_SocketCreateFailed = -301,
  ZRC_SocketConnectFailed = -302,
  ZRC_SocketSendFailed = -303,
  ZRC_SocketRecvFailed = -304,
  ZRC_SocketClosed = -305,
  ZRC_SocketPacketNotExpected = -306, ///<not my expected packet.
  ZRC_SocketPacketDataError = -307, ///<packet data content error.

  /**
   * Local operation section.
   */
  ZRC_SharedPacketNotValid = -400, ///<shared packet object is not valid.
  ZRC_MmapStructureFailed = -401, ///<mmap structure object failed.
  ZRC_InvalidParameters = -402, ///<invalid function parameters.
  ZRC_OpenLocalFileFailed = -403, ///<open local file failed.
  ZRC_ReadLocalFileFailed = -404, ///<read local file failed.
  ZRC_WriteLocalFileFailed = -405, ///<write local file failed.
  ZRC_CloseLocalFileFailed = -406, ///<close local file failed.
  ZRC_MemAllocateFailed = -407, ///<allocate memory failed.
  ZRC_InvalidMvcDevice = -408, ///<invalid MvcDevice object.
  ZRC_RecvThreadCreateFailed = -409, ///<failed to create receive thread.
  ZRC_SendThreadCreateFailed = -410, ///<failed to create send thread.
  ZRC_InvalidPrivateObject = -411, ///<invalid private object.

  /**
   * security manager section.
   */
  ZRC_SMLoadCertChainFileFailed = -500, ///<security manager load certificate chain file failed.
  ZRC_SMLoadPrivateKeyFileFailed = -501, ///<security manager load private key file failed.
  ZRC_SMConnectFailed = -502, ///<security manager connect failed.
  ZRC_SMStartSuiteFailed = -503, ///<security manager start suite failed.
  ZRC_SMUploadCplFileFailed = -504, ///<security manager upload cpl file failed.
  ZRC_SMUploadKdmFileFailed = -505, ///<security manger upload kdm file failed.
  ZRC_SMPlayShowFailed = -506, ///<security manager play show failed.
  ZRC_SMStopShowFailed = -507, ///<security manger stop show failed.
  ZRC_SMPurgeCplFailed = -508, ///<security manger purge cpl failed.
  ZRC_SMStopSuiteFailed = -509, ///<security manger stop suite failed.
  ZRC_SMGetCplListFailed = -510, ///<security manager get cpl list failed.
  ZRC_SMGetKdmListFailed = -511, ///<security manager get kdm list failed.
  ZRC_SMCheckShowFailed = -512, ///<security manager check show failed.
  ZRC_SMAdjustTimeFailed = -513, ///<security manager adjust time failed.
  ZRC_SMGetCertificateFailed = -514, ///<security manager get certificate failed.
  ZRC_SMQueryStatusFailed = -515, ///<security manager query status failed.
  ZRC_SMGetLogReportFailed = -516, ///<security manager get log report failed.
  ZRC_SMInitiateMarriageFailed = -517, ///<security manager initiate marriage failed.
  ZRC_SMServiceDoorTamperTerminationFailed = -518,
  ZRC_SMGetKeyMapFailed = -519,
  ZRC_SMAddCertificateFailed = -520,
  ZRC_SMUsePrivateKeyFailed = -521,
  ZRC_SMZeroizeFailed = -522,
  ZRC_SMUploadCplBufferFailed = -523,
  ZRC_SMUploadKdmBufferFailed = -524,

  /**
   * Play Mode Control section.
   */
  ZRC_PlayModeStartFailed = -600,
  ZRC_PlayModePauseFailed = -601,
  ZRC_PlayModeForwardFailed = -602,
  ZRC_PlayModeBackwardFailed = -603,
  ZRC_PlayModeStopFailed = -604,

  /**
   * Subtitle related error code define.
   */
  ZRC_SubtitleFileSendFailed = -700, ///<

  /**
   * boolean value.
   */
  ZRC_Yes = 0x1,
  ZRC_No = 0x0,
};

/**
 * @brief package structure stored in ZFIFO
 */
#define ZPKT_BUF_SIZE	(1024*1024*2) //2MB
#define BUFSIZE_2MB	(2*1024*1024)

//attention: 4 bytes aligned here!!!!
typedef struct
{
  zuint32_t type;	//package type
  zuint32_t len;	//package data len
  zuint8_t *data; 	//package data area
} ZPKT;

/**
 * @brief package structure transferring in network
 */
typedef struct
{
  zuint8_t head[8]; //header
  ZPKT *pkt; //package
} ZPKTNET;

/**
 * @brief query IMB Card number packet structure
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK-->IMB Server
   * IMB Server --> SDK.
   */
  zuint32_t *ptotal; ///<total number of /dev/imbx.
  zuint8_t *pcard; ///<imb0,imb1,....
} MMAP_QUERY_CARD_INFO;
extern zint32_t
mmap_query_card_info (MMAP_QUERY_CARD_INFO *mm, zuint8_t *buffer, zuint32_t direction);

/**
 * @brief query CPU information packet structure
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB Server.
   */

  /**
   * IMB Server --> SDK.
   */
  zint32_t *pret_code;
  zuint32_t *ptotal_cores;
  zuint32_t *pcores_freq;

} MMAP_QUERY_CPU_INFO;
extern zint32_t
mmap_query_cpu_info (MMAP_QUERY_CPU_INFO *mm, zuint8_t *buffer, zuint32_t direction);

/**
 * @brief query memory information packet structure
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB Server.
   */
  /**
   * IMB server --> SDK.
   */
  zint32_t *pret_code;
  zuint32_t *pmem_total;
  zuint32_t *pmem_free;
} MMAP_MEM_INFO;
extern zint32_t
mmap_mem_info (MMAP_MEM_INFO *mm, zuint8_t *buffer, zuint32_t direction);

/**
 * @brief read & write FPGA register package structure
 */
enum
{
  REGISTER_READ = 0x0, ///<read register operation
  REGISTER_WRITE = 0x1, ///<write register operation
};
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * IMB server --> SDK.
   * return code from ioctl().
   */
  zuint32_t *pret_code;

  /**
   * SDK-->IMB Server
   * IMB Server --> SDK.
   *
   * read or write mode.
   */
  zuint32_t *prd_wr;
  zuint32_t *pregs_address;
  zuint32_t *pregs_value;
} MMAP_FPGA_RW_REGISTER;
extern zint32_t
mmap_fpga_rw_register (MMAP_FPGA_RW_REGISTER *mm, zuint8_t *buffer, zuint32_t direction);

/**
 * @brief DMA data transfer packet structure
 */

/**
 * @brief open device file packet structure
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB Server.
   * device file number.
   * e.g:/dev/imb0,/dev/imb1.
   */
  zuint32_t *pfile_num;
  /**
   * IMB Server --> SDK.
   * return code from IMB Server.
   */
  zuint32_t *pret_code;
} MMAP_OPEN_DEVICE_FILE;
extern zint32_t
mmap_open_device_file (MMAP_OPEN_DEVICE_FILE *mm, zuint8_t *buffer, zuint32_t direction);

//////////////////////////////////////////////////////

/////////////////////////////////////////////////////
////////////////SM client & SM Server////////////////

/**
 * direction control.
 */
enum
{
  DIRECTION_IMBSERVER_TO_SDK = 0x3306, ///<IMB server --> SDK.
  DIRECTION_SDK_TO_IMBSERVER = 0x3308, ///<SDK --> IMB server.
};

/**
 * step2.
 * ret=sm->loadCertificateChainFile("certchain.data");
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;

  /**
   * SDK --> IMB server --> SM server.
   * certificate chain file to SM server.
   */
  zuint32_t *pfile_len;
  zuint8_t *pfile_data;
} MMAP_SM_LOAD_CERTIFICATE_FILE;
/**
 * memory map plain buffer to MMAP_SM_LOAD_CERTIFICATE_FILE.
 * easy to operate.
 */
extern zint32_t
mmap_sm_load_certificate_file (MMAP_SM_LOAD_CERTIFICATE_FILE *sm, zuint8_t *buffer, zuint32_t direction);

/**
 * step3.
 * ret=sm->loadPrivateKeyFile("SMStheLeafprikey.pem");
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;

  /**
   * SDK --> IMB server --> SM server.
   * certificate chain file to SM server.
   */
  zuint32_t *pfile_len;
  zuint8_t *pfile_data;
} MMAP_SM_LOAD_PRIVATEKEY_FILE;
/**
 * memory map plain buffer to MMAP_SM_LOAD_PRIVATEKEY_FILE.
 * easy to operate.
 */
extern zint32_t
mmap_sm_load_private_file (MMAP_SM_LOAD_PRIVATEKEY_FILE *sm, zuint8_t *buffer, zuint32_t direction);

/**
 * step4.
 * ret=sm->connect();
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;

  /**
   * IMB server --> SM server.
   * parameters.
   */
  zuint32_t *pconnect_timeout; ///<unit:ms.
  zuint32_t *pconnect_retry_times;
} MMAP_SM_CONNECT;
/**
 * memory map plain buffer to MMAP_SM_CONNECT.
 * easy to operate.
 */
extern zint32_t
mmap_sm_connect (MMAP_SM_CONNECT *sm, zuint8_t *buffer, zuint32_t direction);

/**
 * step5.
 * ret=sm->startSuite();
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;
} MMAP_SM_STARTSUITE;
/**
 * memory map plain buffer to MMAP_SM_STARTSUITE.
 * easy to operate.
 */
extern zint32_t
mmap_sm_startsuite (MMAP_SM_STARTSUITE *sm, zuint8_t *buffer, zuint32_t direction);

/**
 * step6.
 * ret=sm->uploadCplFile();
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;

  /**
   * SDK --> IMB server --> SM server.
   * certificate chain file to SM server.
   */
  zuint32_t *pfile_len;
  zuint8_t *pfile_data;
} MMAP_SM_UPLOAD_CPL;
/**
 * memory map plain buffer to MMAP_SM_UPLOAD_CPL.
 * easy to operate.
 */
extern zint32_t
mmap_sm_uploadcpl (MMAP_SM_UPLOAD_CPL *sm, zuint8_t *buffer, zuint32_t direction);

/**
 * step7.
 * ret=sm->uploadKdmFile();
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;

  /**
   * SDK --> IMB server --> SM server.
   * certificate chain file to SM server.
   */
  zuint32_t *pfile_len;
  zuint8_t *pfile_data;
} MMAP_SM_UPLOAD_KDM;
/**
 * memory map plain buffer to MMAP_SM_UPLOAD_KDM.
 * easy to operate.
 */
extern zint32_t
mmap_sm_uploadkdm (MMAP_SM_UPLOAD_KDM *sm, zuint8_t *buffer, zuint32_t direction);

///////////////////////
//////////////////////
/////////////////////
#define AUTHID_LEN	512
#define UUID_LEN        16
/**
 * step8.
 * ret=sm->playShow();
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;

  /**
   * SDK --> IMB server --> SM server.
   */
  /**
   * authId.
   * maximum is 512 bytes.
   */
  zuint8_t *pauthId;
  zuint32_t *pauthId_len;

  /**
   * UuidValue,16 bytes.
   */
  zuint8_t *puuidValue;
  uint32_t *parrayLen;
  /**
   * uint64_t keyExpTime.
   */
  zuint32_t *pkeyExpTime_high;
  zuint32_t *pkeyExpTime_low;
} MMAP_SM_PLAYSHOW;
/**
 * memory map plain buffer to MMAP_SM_PLAYSHOW.
 * easy to operate.
 */
extern zint32_t
mmap_sm_playshow (MMAP_SM_PLAYSHOW *sm, zuint8_t *buffer, zuint32_t direction);

/**
 * step9.
 * ret=sm->stopShow();
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;

  /**
   * SDK --> IMB server --> SM server
   * parameters.
   */

  /**
   * m_pInnerSM->stopShow(authId);
   * maximum is 512 bytes.
   */
  zuint8_t *pauthId;
  zuint32_t *pauthId_len;
} MMAP_SM_STOPSHOW;
/**
 * memory map plain buffer to MMAP_SM_STOPSHOW.
 * easy to operate.
 */
extern zint32_t
mmap_sm_stopshow (MMAP_SM_STOPSHOW *sm, zuint8_t *buffer, zuint32_t direction);

/**
 * step10.
 * ret=sm->purgeCpl();
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;

  /**
   * SDK --> IMB server --> SM server
   * parameters.
   */
  zuint8_t *puuidValue;
} MMAP_SM_PURGECPL;
/**
 * memory map plain buffer to MMAP_SM_PURGECPL.
 * easy to operate.
 */
extern zint32_t
mmap_sm_purgecpl (MMAP_SM_PURGECPL *sm, zuint8_t *buffer, zuint32_t direction);

/**
 * step11.
 * ret=sm->stopSuite();
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;
} MMAP_SM_STOPSUITE;
/**
 * memory map plain buffer to MMAP_SM_STOPSUITE.
 * easy to operate.
 */
extern zint32_t
mmap_sm_stopsuite (MMAP_SM_STOPSUITE *sm, zuint8_t *buffer, zuint32_t direction);

/**
 * added by zhangshaoyan at October 28,2014.
 * for support other features of SM.
 */
/**
 * TMmRc uploadKdmBuffer( const uint8_t *kdmBuffer, uint32_t bufferSize, AesKeyMap *subKeyArray = 0, uint32_t *numberOfEntries = 0 );
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB server --> SM server.
   */
  zuint32_t *pbuffersize;
  zuint8_t *pkdmbuffer;
  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;

} MMAP_SM_UPLOADKDMBUFFER;
/**
 * memory map plain buffer to MMAP_SM_UPLOADKDMBUFFER.
 * easy to operate.
 */
extern zint32_t
mmap_sm_uploadkdmbuffer (MMAP_SM_UPLOADKDMBUFFER *sm, zuint8_t *buffer, zuint32_t direction);

/**
 * TMmRc uploadCplBuffer( const uint8_t *cplBuffer, uint32_t bufferSize, CPL_ASSET_EXCEPTION assetExc = CplException_None );
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB server --> SM server.
   */
  zuint32_t *passetExc;
  zuint32_t *pbuffersize;
  zuint8_t *pcplbuffer;
  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;

} MMAP_SM_UPLOADCPLBUFFER;
/**
 * memory map plain buffer to MMAP_SM_UPLOADCPLBUFFER.
 * easy to operate.
 */
extern zint32_t
mmap_sm_uploadcplbuffer (MMAP_SM_UPLOADCPLBUFFER *sm, zuint8_t *buffer, zuint32_t direction);

/**
 * TMmRc getCplList( inner_sm::UuidValue *cplUuidArray, uint32_t *arrayLen );
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB server --> SM server.
   */

  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;
  zuint32_t *parrayLen;
  zuint8_t *pcplUuidArray;

} MMAP_SM_GETCPLLIST;
/**
 * memory map plain buffer to MMAP_SM_GETCPLLIST.
 * easy to operate.
 */
extern zint32_t
mmap_sm_getcpllist (MMAP_SM_GETCPLLIST *sm, zuint8_t *buffer, zuint32_t direction);

/**
 * TMmRc getKdmList( const inner_sm::UuidValue &cplUuid, inner_sm::UuidValue *kdmUuidArray, uint32_t *arrayLen );
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB server --> SM server.
   */
  zuint32_t *pcpluuid_len;
  zuint8_t *pcpluuid;

  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;
  zuint32_t *parrayLen;
  zuint8_t *pkdmUuidArray;

} MMAP_SM_GETKDMLIST;
/**
 * memory map plain buffer to MMAP_SM_GETKDMLIST.
 * easy to operate.
 */
extern zint32_t
mmap_sm_getkdmlist (MMAP_SM_GETKDMLIST *sm, zuint8_t *buffer, zuint32_t direction);
/**
 * TMmRc checkShow( const inner_sm::UuidValue *cplUuidArray, uint32_t arrayLen, uint64_t checkTime, uint64_t *keyExpTime = 0 );
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB server --> SM server.
   */
  zuint32_t *pchecktime_high;
  zuint32_t *pchecktime_low;

  zuint32_t *parraylen;
  zuint8_t *pcpluuidarray;

  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;
  zuint32_t *pkeyExpTime_high;
  zuint32_t *pkeyExpTime_low;

} MMAP_SM_CHECKSHOW;
/**
 * memory map plain buffer to MMAP_SM_CHECKSHOW.
 * easy to operate.
 */
extern zint32_t
mmap_sm_checkshow (MMAP_SM_CHECKSHOW *sm, zuint8_t *buffer, zuint32_t direction);

/**
 * TMmRc adjustTime( const char *authId, uint32_t diff );
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB server --> SM server.
   */
  zuint32_t *pdiff;
  zuint32_t *pauthId_len;
  zuint8_t *pauthId;

  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;

} MMAP_SM_ADJUSTTIME;
/**
 * memory map plain buffer to MMAP_SM_ADJUSTTIME.
 * easy to operate.
 */
extern zint32_t
mmap_sm_adjusttime (MMAP_SM_ADJUSTTIME *sm, zuint8_t *buffer, zuint32_t direction);

/**
 * TMmRc getCertificate( uint32_t which, uint8_t *buffer, uint32_t *buffersize );
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB server --> SM server.
   */
  zuint32_t *pwhich;

  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;
  zuint32_t *pbuffersize;
  zuint8_t *pbuffer;

} MMAP_SM_GETCERTIFICATE;
/**
 * memory map plain buffer to MMAP_SM_GETCERTIFICATE.
 * easy to operate.
 */
extern zint32_t
mmap_sm_getcertificate (MMAP_SM_GETCERTIFICATE *sm, zuint8_t *buffer, zuint32_t direction);

/**
 * TMmRc queryStatus( SM_OPERATION *smOp, SUITE_STATUS *suiteStat, uint64_t *secureTime, int32_t *time_adjust );
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB server --> SM server.
   */

  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;
  zuint32_t *psm_operation;
  zuint32_t *psuite_status;
  zuint32_t *psecureTime_high;
  zuint32_t *psecureTime_low;
  zuint32_t *ptime_adjust;

} MMAP_SM_QUERYSTATUS;
/**
 * memory map plain buffer to MMAP_SM_QUERYSTATUS.
 * easy to operate.
 */
extern zint32_t
mmap_sm_querystatus (MMAP_SM_QUERYSTATUS *sm, zuint8_t *buffer, zuint32_t direction);

/**
 * TMmRc getLogReport( uint8_t *buffer, uint32_t *buffersize, uint64_t startTime, uint64_t endTime, uint64_t *lastLogTime );
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB server --> SM server.
   */
  zuint32_t *pstartTime_high;
  zuint32_t *pstartTime_low;
  zuint32_t *pendTime_high;
  zuint32_t *pendTime_low;

  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;
  zuint32_t *plastLogTime_high;
  zuint32_t *plastLogTime_low;
  zuint32_t *pbuffersize;
  zuint8_t *pbuffer;

} MMAP_SM_GETLOGREPORT;
/**
 * memory map plain buffer to MMAP_SM_GETLOGREPORT.
 * easy to operate.
 */
extern zint32_t
mmap_sm_getlogreport (MMAP_SM_GETLOGREPORT *sm, zuint8_t *buffer, zuint32_t direction);

/**
 * TMmRc initiateMarriage( const char *authId );
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB server --> SM server.
   */
  zuint32_t *pauthId_len;
  zuint8_t *pauthId;

  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;
} MMAP_SM_INITIATEMARRIAGE;
/**
 * memory map plain buffer to MMAP_SM_INITIATEMARRIAGE.
 * easy to operate.
 */
extern zint32_t
mmap_sm_initiatemarriage (MMAP_SM_INITIATEMARRIAGE *sm, zuint8_t *buffer, zuint32_t direction);

/**
 * TMmRc serviceDoorTamperTermination( const char *authId );
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB server --> SM server.
   */
  zuint32_t *pauthId_len;
  zuint8_t *pauthId;

  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;
} MMAP_SM_SERVICEDOORTAMPERTERMINATION;
/**
 * memory map plain buffer to MMAP_SM_SERVICEDOORTAMPERTERMINATION.
 * easy to operate.
 */
extern zint32_t
mmap_sm_servicedoortampertermination (MMAP_SM_SERVICEDOORTAMPERTERMINATION *sm, zuint8_t *buffer, zuint32_t direction);

/**
 * TMmRc getKeyMap( KeyMap *keymapArray, uint32_t *numberOfEntries );
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB server --> SM server.
   */
  zuint32_t *pkey_id_len;
  zuint8_t *pkey_id;

  zuint32_t *pkdm_id_len;
  zuint8_t *pkdm_id;

  zuint32_t *pkey_index;
  zuint32_t *pkey_type;

  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;
} MMAP_SM_GETKEYMAP;
/**
 * memory map plain buffer to MMAP_SM_GETKEYMAP.
 * easy to operate.
 */
extern zint32_t
mmap_sm_getkeymap (MMAP_SM_GETKEYMAP *sm, zuint8_t *buffer, zuint32_t direction);

/**
 * TMmRc addCertificate( void *cert );
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB server --> SM server.
   */
  zuint32_t *pcert_len;
  zuint8_t *pcert;

  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;
} MMAP_SM_ADDCERTIFICATE;
/**
 * memory map plain buffer to MMAP_SM_ADDCERTIFICATE.
 * easy to operate.
 */
extern zint32_t
mmap_sm_addcertificate (MMAP_SM_ADDCERTIFICATE *sm, zuint8_t *buffer, zuint32_t direction);

/**
 * TMmRc usePrivateKey( void *pkey );
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB server --> SM server.
   */
  zuint32_t *pkey_len;
  zuint8_t *pkey;

  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;
} MMAP_SM_USEPRIVATEKEY;
/**
 * memory map plain buffer to MMAP_SM_USEPRIVATEKEY.
 * easy to operate.
 */
extern zint32_t
mmap_sm_useprivatekey (MMAP_SM_USEPRIVATEKEY *sm, zuint8_t *buffer, zuint32_t direction);

/**
 * TMmRc zeroize( const char *authId );
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB server --> SM server.
   */
  zuint32_t *pauthId_len;
  zuint8_t *pauthId;

  /**
   * SM server --> IMB server --> SDK.
   * return code from SM server.
   */
  zuint32_t *pret_code;
} MMAP_SM_ZEROIZE;
/**
 * memory map plain buffer to MMAP_SM_ZEROIZE.
 * easy to operate.
 */
extern zint32_t
mmap_sm_zeroize (MMAP_SM_ZEROIZE *sm, zuint8_t *buffer, zuint32_t direction);
/**
 * Play control.
 * Modified by zhangshaoyan at November 21,2014.
 * Note:
 * Move Play mode control from SDK to IMB server.
 */
/**
 * Start.
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB server.
   * no data need to be send here.
   */

  /**
   * IMB server --> SDK.
   * return code form imb server.
   */
  zuint32_t *pret_code;
} MMAP_PLAY_MODE_START;
extern zint32_t
mmap_play_mode_start (MMAP_PLAY_MODE_START *pms, zuint8_t *buffer, zuint32_t direction);
/**
 * Pause.
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB server.
   * no data need to be send here.
   */

  /**
   * IMB server --> SDK.
   * return code form imb server.
   */
  zuint32_t *pret_code;
} MMAP_PLAY_MODE_PAUSE;
extern zint32_t
mmap_play_mode_pause (MMAP_PLAY_MODE_PAUSE *pmp, zuint8_t *buffer, zuint32_t direction);
/**
 * Forward.
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB server.
   * no data need to be send here.
   */

  /**
   * IMB server --> SDK.
   * return code form imb server.
   */
  zuint32_t *pret_code;
} MMAP_PLAY_MODE_FORWARD;
extern zint32_t
mmap_play_mode_forward (MMAP_PLAY_MODE_FORWARD *pmf, zuint8_t *buffer, zuint32_t direction);

/**
 * Backward.
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB server.
   * no data need to be send here.
   */

  /**
   * IMB server --> SDK.
   * return code form imb server.
   */
  zuint32_t *pret_code;
} MMAP_PLAY_MODE_BACKWARD;
extern zint32_t
mmap_play_mode_backward (MMAP_PLAY_MODE_BACKWARD *pmb, zuint8_t *buffer, zuint32_t direction);

/**
 * Stop.
 */
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB server.
   * no data need to be send here.
   */

  /**
   * IMB server --> SDK.
   * return code form imb server.
   */
  zuint32_t *pret_code;
} MMAP_PLAY_MODE_STOP;
extern zint32_t
mmap_play_mode_stop (MMAP_PLAY_MODE_STOP *pms, zuint8_t *buffer, zuint32_t direction);

/**
 * subtitle related packet types.
 * added by zhangshaoyan at November 2,2014.
 */
#define SUBTITLE_FILENAME_LEN   128
#define UUID_LEN        16
#define SUBTITLE_SYNC_HEAD1     0x11111111
#define SUBTITLE_SYNC_HEAD2     0x99999999
#define SUBTITLE_SYNC_HEAD3     0x88888888
#define SUBTITLE_SYNC_HEAD4     0x77777777
enum
{
  Subtitle_File_Type_XML = 0x1014, ///<
  Subtitle_File_Type_TTF = 0x1015, ///<
  Subtitle_File_Type_TTC = 0x1016, ///<
  Subtitle_File_Type_PNG = 0x1017, ///<
};
typedef struct
{
  /**
   * valid data length.
   * contains itself.
   */
  zuint32_t *pvalid_len;

  /**
   * SDK --> IMB server.
   * no data need to be send here.
   */
  /**
   * Frame Header for DMA transfer.
   */
  zuint32_t *pFrameType; ///< 4 bytes,must be 'MDSK'
  zuint32_t *pFrameLength; ///< 4 bytes,frame length.
  zuint8_t *pEncryFlag; ///< 1 bytes,encrypt or not flag
  zuint8_t *pKeyId; ///< 16 bytes,all zeros.

  /**
   * Frame Data Section.
   */
  zuint32_t *pSyncHead1;
  zuint32_t *pSyncHead2;
  zuint32_t *pSyncHead3;
  zuint32_t *pSyncHead4;
  zuint32_t *pFileType;
  zuint32_t *pFileLength; ///<file length.
  zuint8_t *pFileData; ///<file name length+filename,file data length+file data.
  //here should include timeOffSet value,4 bytes,added by zsy@2016/3/8.

  /**
   * IMB server --> SDK.
   * return code form imb server.
   */
  zuint32_t *pret_code;
} MMAP_SUBTITLE_FILE;
extern zint32_t
mmap_subtitle_file (MMAP_SUBTITLE_FILE *mm, zuint8_t *buffer, zuint32_t direction);
#endif //_ZPROTOCOL_H__
/**
 * the end of file,tagged by ZSY
 */
