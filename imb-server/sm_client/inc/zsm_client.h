/*
 * zsm_client.h
 *
 *  Created on: Oct 17, 2014
 *      Author: root
 */

#ifndef ZSM_CLIENT_H_
#define ZSM_CLIENT_H_

#include <zdata_types.h>
#include <zclient_affair.h>
#include <zprotocol.h>
#include <zdevice_interface.h>
#include <zcmd_parse.h>
////////////////////////////////////////////////

/**
 * command parse for sm client & sm server.
 * added by zhangshaoyan October 17,2014.
 * To solve the problem of network crossing communicate with SM server.
 */
/**
 * temporary file path define.
 */

#define TMP_FILE_CERTIFICATE_CHAIN	"/tmp/__zsy_certificate_chain_file.dat"
#define TMP_FILE_PRIVATE_KEY		"/tmp/__zsy_private_key_file.pem"
#define TMP_FILE_CPL			"/tmp/__zsy_cpl_file.cpl"
#define TMP_FILE_KDM			"/tmp/__zsy_kdm_file.kdm"


/**
 * step2.
 * ret=sm->loadCertificateChainFile("certchain.data");
 */
extern zint32_t
cmd_sm_load_certificate_file (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);
/**
 * step3.
 * ret=sm->loadPrivateKeyFile("SMStheLeafprikey.pem");
 */
extern zint32_t
cmd_sm_load_privatekey_file (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);

/**
 * step4.
 * ret=sm->connect();
 */
extern zint32_t
cmd_sm_connect (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);

/**
 * step5.
 * ret=sm->startSuite();
 */
extern zint32_t
cmd_sm_start_suite (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);

/**
 * step6.
 * ret=sm->uploadCplFile();
 */
extern zint32_t
cmd_sm_upload_cpl_file (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);

/**
 * step7.
 * ret=sm->uploadKdmFile();
 */
extern zint32_t
cmd_sm_upload_kdm_file (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);

/**
 * step8.
 * ret=sm->playShow();
 */
extern zint32_t
cmd_sm_play_show (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);

/**
 * step9.
 * ret=sm->stopShow();
 */
extern zint32_t
cmd_sm_stop_show (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);

/**
 * step10.
 * ret=sm->purgeCpl();
 */
extern zint32_t
cmd_sm_purge_cpl (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);

/**
 * step11.
 * ret=sm->stopSuite();
 */
extern zint32_t
cmd_sm_stop_suite (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);

/**
 * added by zhangshaoyan at November 3,2014.
 * for support SM.
 */
/**
 * TMmRc checkShow( const inner_sm::UuidValue *cplUuidArray, uint32_t arrayLen, uint64_t checkTime, uint64_t *keyExpTime = 0 );
 */
extern zint32_t
cmd_sm_checkshow (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);
/**
 * TMmRc uploadKdmBuffer( const uint8_t *kdmBuffer, uint32_t bufferSize, AesKeyMap *subKeyArray = 0, uint32_t *numberOfEntries = 0 );
 */
extern zint32_t
cmd_sm_uploadkdmbuffer (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);
/**
 * TMmRc uploadCplBuffer( const uint8_t *cplBuffer, uint32_t bufferSize, CPL_ASSET_EXCEPTION assetExc = CplException_None );
 */
extern zint32_t
cmd_sm_uploadcplbuffer (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);
/**
 * TMmRc getCplList( inner_sm::UuidValue *cplUuidArray, uint32_t *arrayLen );
 */
extern zint32_t
cmd_sm_getcpllist (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);
/**
 * TMmRc getKdmList( const inner_sm::UuidValue &cplUuid, inner_sm::UuidValue *kdmUuidArray, uint32_t *arrayLen );
 */
extern zint32_t
cmd_sm_getkdmlist (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);
/**
 * TMmRc adjustTime( const char *authId, uint32_t diff );
 */
extern zint32_t
cmd_sm_adjusttime (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);

/**
 * TMmRc getCertificate( uint32_t which, uint8_t *buffer, uint32_t *buffersize );
 */
extern zint32_t
cmd_sm_getcertificate (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);
/**
 * TMmRc queryStatus( SM_OPERATION *smOp, SUITE_STATUS *suiteStat, uint64_t *secureTime, int32_t *time_adjust );
 */
extern zint32_t
cmd_sm_querystatus (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);

/**
 * TMmRc getLogReport( uint8_t *buffer, uint32_t *buffersize, uint64_t startTime, uint64_t endTime, uint64_t *lastLogTime );
 */
extern zint32_t
cmd_sm_getlogreport (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);

/**
 * TMmRc initiateMarriage( const char *authId );
 */
extern zint32_t
cmd_sm_initiatemarriage (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);
/**
 * TMmRc serviceDoorTamperTermination( const char *authId );
 */
extern zint32_t
cmd_sm_servicedoortampertermination (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);
/**
 * TMmRc getKeyMap( KeyMap *keymapArray, uint32_t *numberOfEntries );
 */
extern zint32_t
cmd_sm_getkeymap (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);
/**
 * TMmRc addCertificate( void *cert );
 */
extern zint32_t
cmd_sm_addcertificate (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);

/**
 * TMmRc usePrivateKey( void *pkey );
 */
extern zint32_t
cmd_sm_useprivatekey (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);

/**
 * TMmRc zeroize( const char *authId );
 */
extern zint32_t
cmd_sm_zeroize (ZTHREAD_CBS *cbs, ZPKT *pkt_fifo, ZPKTNET *pktnet);
#endif /* ZSM_CLIENT_H_ */
