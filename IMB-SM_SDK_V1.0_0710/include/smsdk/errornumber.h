#ifndef _ERRORNUMBER_H_
#define _ERRORNUMBER_H_

#include <vector>
using namespace std;

//========ȫ�ִ�����====================================//
extern const int PUB_SHARE_OK;								//�����ɹ�
extern const int PUB_SHARE_IPUTPARAMERR;					//�����������
extern const int PUB_SHARE_NEWMEMFAILED;					//�ڴ����ʧ��
extern const int PUB_SHARE_OPENFILEFAILED;					//���ļ�����
extern const int PUB_SHARE_XMLDOCERR;						//xml����
extern const int PUB_SHARE_HASHARITHFAILED;					//Hash����ʧ��
extern const int PUB_SHARE_RSAARITHENCFAILED;				//Rsa����ʧ��
extern const int PUB_SHARE_RSAARITHDECFAILED;				//Rsa����ʧ��
extern const int PUB_SHARE_SYMARITHENCFAILED;				//�ԳƼ���ʧ��
extern const int PUB_SHARE_SYMARITHDECFAILED;				//�Գƽ���ʧ��
extern const int PUB_SHARE_BASE64ENCFAILED;					//Base����ʧ��
extern const int PUB_SHARE_BASE64DECFAILED;					//Base����ʧ��
extern const int PUB_SHARE_ASN1CHAGEFAILED;					//ASN1�ڲ�ת��ʧ��
extern const int PUB_SHARE_INITERR;							//����(��)��ʼ��ʧ��
extern const int PUB_SHARE_OPENSSLCHANGETYPEERR;			//openssl���ַ�����֤��ת��ʧ��
extern const int PUB_SHARE_NOINITSecurityEnviroment;		//��ȫ����δ��ʼ��
extern const int PUB_SHARE_USERNOLOGIN;						//�û�δ��¼
extern const int PUB_SHARE_DEVICENOTREGISTER;				//�豸δע��
extern const int PUB_SHARE_CONEER;			            	//�����������ʧ��
extern const int PUB_SHARE_SENDDATAERR;			        	//���������������ʧ��
extern const int PUB_SHARE_REVICEBUFISNOTHING;				//�ӷ��������յ�������Ϊ��
extern const int PUB_SHARE_TIMESYNCERR;			        	//����ʱ�����
extern const int PUB_SHARE_OPENFILENOEXIST;					//Ҫ�򿪵��ļ�������  //add by yin 2010.10.11
//======================================================//


//======�㷨��ģ��======================================//
extern const int ARI_ARITHMATIC_INITHASHERR;				//��ʼ��hash����ʧ��
extern const int ARI_ARITHMATIC_PRIKEYENCERR;				//˽Կ����ʧ��
extern const int ARI_ARITHMATIC_CREATSIGNDATAERR;			//����ǩ������ʧ��
extern const int ARI_ARITHMATIC_PUBKEYENCERR;				//��Կ����ʧ��
extern const int ARI_ARITHMATIC_VERIFYERR;					//��֤ǩ��ʧ��
extern const int ARI_ARITHMATIC_BASE64ENCERR;				//base64����ʧ��
extern const int ARI_ARITHMATIC_BASE64DECERR;				//base64����ʧ��
extern const int ARI_ARITHMATIC_CREATRANDOMNUMERR;			//���������ʧ��
extern const int ARI_ARITHMATIC_SYMENCERR;					//�ԳƼ���ʧ��
extern const int ARI_ARITHMATIC_SYMINITERR;					//�ԳƼ��ܳ�ʼ�����ܲ���ʧ��
extern const int ARI_ARITHMATIC_SYMDECERR;					//��ȡ�ԳƼ�������ʧ��
extern const int ARI_ARITHMATIC_GETHASHDATAERR;				//��ȡhash��������ʧ��
extern const int ARI_ARITHMATIC_INITSIGNERR;				//init sign�㷨ʧ��
extern const int ARI_ARITHMATIC_UPDATESIGNERR;				//update sign�㷨ʧ��
extern const int ARI_ARITHMATIC_FINALSIGNERR;				//final sign�㷨ʧ��
extern const int ARI_ARITHMATIC_INITVERIFYERR;				//init verify�㷨ʧ��
extern const int ARI_ARITHMATIC_UPDATEVERIFYERR;			//update verify�㷨ʧ��
extern const int ARI_ARITHMATIC_FINALVERIFYERR;				//final verify�㷨ʧ��
extern const int ARI_ARITHMATIC_GENTKEYERR;					//������Կʧ��
extern const int ARI_ARITHMATIC_GENTCRCERR;					//����CRCʧ�� 20100720 by xiaozhengxiu add
extern const int ARI_ARITHMATIC_VERIFYCRCERR;				//��֤CRCʧ�� 20100720 by xiaozhengxiu add
extern const int ARI_ARITHMATIC_GENTRANDERR;				//���������ʧ�� //add by yin 6.7
extern const int ARI_ARITHMATIC_GENTKEYIDERR;				//����keyidʧ��>=4096
extern const int ARI_ARITHMATIC_GENRSAKEYPAIRERR;			//����RSA��Կ��ʧ��
extern const int ARI_ARITHMATIC_GENCERTREQERR;				//����֤������ʧ��
//======================================================//

//======��ȫ������ģ��==================================//
//x509������
extern const int SEC_X509REQ_CREATRSAKEYERR;				//����rsa��Կ��ʧ��
extern const int SEC_X509REQ_X509REQADDPUBKEYERR;			//������֤��ṹ������ӹ�Կʧ��
extern const int SEC_X509REQ_OPENSSLCHANGECODEERR;			//openssl�ڲ�ת��ʧ�ܣ��ַ���ת����������
extern const int SEC_X509REQ_CREATCERTNAMEENTRYERR;			//����֤������entryʧ��	
extern const int SEC_X509REQ_ADDCERTNAMEENTRYERR;			//���֤������entryʧ��
extern const int SEC_X509REQ_ADDRSATOEVPPKEYERR;			//���rsa��Կ��evppkey�ṹ��ʧ��
extern const int SEC_X509REQ_ADDCOUNTRYNAMEERR;				//��ӹ�������x509name�ṹ��ʧ��
extern const int SEC_X509REQ_ADDPROVINCENAMEERR;			//���ʡ������x509name�ṹ��ʧ��
extern const int SEC_X509REQ_ADDCITYNAMEERR;				//��ӳ�������x509name�ṹ��ʧ��
extern const int SEC_X509REQ_ADDORGNAMEERR;					//�����֯����x509name�ṹ��ʧ��
extern const int SEC_X509REQ_ADDDEPARTNAMEERR;				//��Ӳ�����Ϣ��x509name�ṹ��ʧ��
extern const int SEC_X509REQ_ADDCOMMONNAMEERR;				//���common��Ϣ��x509name�ṹ��ʧ��
extern const int SEC_X509REQ_ADDNAMETOX509REQERR;			//���x509name�ṹ�嵽x509req�ṹ��ʧ��

//X509֤����
extern const int SEC_X509CERT_ADDVERSIONERR;				//��Ӱ汾��Ϣ��֤��ʧ��
extern const int SEC_X509CERT_ADDSNERR;						//������к���Ϣ��֤��ʧ��
extern const int SEC_X509CERT_ADDBEGINTIMEERR;				//�����Ч��ʼʱ����Ϣ��֤��ʧ��
extern const int SEC_X509CERT_ADDENDTIMEERR;				//�����Ч����ʱ����Ϣ��֤��ʧ��
extern const int SEC_X509CERT_ADDCANAMEINFOERR;				//��ӷ�������Ϣ��֤��ʧ��	
extern const int SEC_X509CERT_ADDSUBNAMEINFOERR;			//���ʵ��֤����Ϣ��֤��ʧ��
extern const int SEC_X509CERT_ADDPUBKEYERR;					//���ù�Կ��Ϣ��֤��ʧ��
extern const int SEC_X509CERT_SIGNERR;						//ǩ��ʧ��
extern const int SEC_X509CERT_VERIFYFAILED;					//��֤֤����Ч��ʧ��
extern const int SEC_X509CERT_INITX509STOREERR;				//��ʼ��X509_STORE ʧ��
extern const int SEC_X509CERT_READCERTNAMEERR;				//��ȡʵ��֤��������Ϣʧ��
extern const int SEC_X509CERT_BIOERR;						//�ж�BIO����ʧ��
extern const int SEC_X509CERT_CREATCERTFILEERR;				//����֤���ļ�ʧ��
extern const int SEC_X509CERT_CREATPRIKEYFILEERR;			//����˽Կ�ļ�ʧ��

//����x509֤����
extern const int SEC_X509INFO_DUPCERTERR;					//��¡cert�ṹ��ʧ��
extern const int SEC_X509INFO_READCERTERR;					//���ļ��ж�ȡ��cert�ṹ��ʧ��
extern const int SEC_X509INFO_READBEGINTIEMERR;				//��ȡ֤����Ч�Ŀ�ʼʱ��ʧ��
extern const int SEC_X509INFO_READENDTIMEERR;				//��ȡ֤����Ч�Ľ���ʱ��ʧ��
extern const int SEC_X509INFO_READPUBKEYERR;				//��ȡ֤�鹫Կʧ��
extern const int SEC_X509INFO_READARITHTYPEERR;				//��ȡ֤��ǩ���㷨����ʧ��
extern const int SEC_X509INFO_READSNERR;					//��ȡ֤�����к�ʧ��
extern const int SEC_X509INFO_READSUBCERTNAMEERR;			//��ȡʵ��֤����ʧ��
extern const int SEC_X509INFO_READCACERTNAMEERR;			//��ȡ֤�鷢������Ϣʧ�ܣ��ṹ�壩
extern const int SEC_X509INFO_GETCOUTRYNAMEERR;				//��ȡ������ʧ��
extern const int SEC_X509INFO_GETPROVINCENAMEERR;			//��ȡʡ����ʧ��
extern const int SEC_X509INFO_GETCITYNAMEERR;				//��ȡ������ʧ��
extern const int SEC_X509INFO_GETORGNAMEERR;				//��ȡ��֯��ʧ��
extern const int SEC_X509INFO_GETDEPARTNAMEERR;				//��ȡ������ʧ��
extern const int SEC_X509INFO_GETCACERTNAMEERR;				//��ȡ��������Ϣʧ�ܣ��ַ�����

//add by 6.8
extern const int SEC_X509INFO_GETEXTENERR;					//��ȡ��չʧ��
extern const int SEC_X509INFO_GETDNQERR;					//��ȡDNQʧ��
extern const int SEC_X509INFO_GETROLEERR;					//��ȡ��ɫʧ��
extern const int SEC_X509INFO_LOADCRLERR;					//����CRLʧ��
extern const int SEC_X509INFO_LOADERR;   					//����֤��ʧ��
extern const int SEC_X509INFO_NEWSTACKX509ERR;				//new stack of x509ʧ��
extern const int SEC_X509INFO_HASMOREROOTERR; 				//��֤�����һ�� 
extern const int SEC_X509INFO_HASNOROOTERR;  				//û���ҵ���֤��
extern const int SEC_X509INFO_CERTCHAINISNONEERR;			//֤����Ϊ��
extern const int SEC_X509INFO_CERTCHAINSORTERR;				//֤�����������
extern const int SEC_X509INFO_CERTTYPEERR;					//���õ�֤�����ʹ���
extern const int SEC_X509INFO_STORECTXINITERR;				//��ʼ��֤��store ctx����
extern const int SEC_X509INFO_LOADCERTLISTERR;				//֤��������ʧ��
extern const int SEC_X509INFO_TIMEVALIDATEERR;				//֤��ʱ����Ч�Դ���
extern const int SEC_X509INFO_HASNOLEAFERR;		    		//û��Ҷ��֤��
extern const int SEC_X509INFO_HASNOCERTCHAINOFSORTERR;		//�ź����֤����Ϊ��
extern const int SEC_X509INFO_INFOTOSTRINGERR;	  			//֤����Ϣ�ṹ��ת�ַ���ʧ��
extern const int SEC_X509INFO_INFOSTRINGTOOLENERR;			//֤����Ϣ�ַ��������

//��֤x509֤����
extern const int SEC_X509CERTS4302_GETROLEERR;				//��ȡ֤���ɫʧ��
extern const int SEC_X509CERTS4302_EXSITROLEERR;		  	//֤�鲻���ڽ�ɫ
extern const int SEC_X509CERTS4302_FORMATERR;			    //֤���ʽ��֤ʧ��
extern const int SEC_X509CERTS4302_LOADCERTERR;			  	//����֤��ʧ��
extern const int SEC_X509CERTS4302_LOADCRLERR;			  	//����CRLʧ��
extern const int SEC_X509CERTS4302_SORTCERTLISTERR;			//֤��������ʧ��
extern const int SEC_X509CERTS4302_VERIFYCERTLISTERR;		//֤������֤ʧ��
extern const int SEC_X509CERTS4302_LOADCERTLISTERR;			//֤��������ʧ��
extern const int SEC_X509CERTS4302_VERIFYVALIDITYTIMEERR;	//֤����Чʱ����֤ʧ��

//pkcs12������
extern const int SEC_P12CERT_SETCERTLISTERR;				//����֤�鵽֤����ʧ��
extern const int SEC_P12CERT_CHECKKEYPAIRERR;				//֤������Կ����һ����Կ��
extern const int SEC_P12CERT_ADDCERTTOBAGERR;				//���֤�鵽bag��ʧ��
extern const int SEC_P12CERT_ADDOTHERCERTNAMETOBAGERR;		//���֤�鸽������bag��ʧ��
extern const int SEC_P12CERT_CERTHASHERR;					//��֤����hash����ʧ��
extern const int SEC_P12CERT_ADDHASHVALUETOBAGERR;			//���֤��hash��Ϣ��bag��ʧ��
extern const int SEC_P12CERT_ADDKEYIDTOBAGERR;				//���keyid��openssl�У���bag��ʧ��
extern const int SEC_P12CERT_ADDBAGTOBAGSERR;				//���bag����bags��ʧ��
extern const int SEC_P12CERT_GETCERTLISTCERTERR;			//��ȡ֤������֤��ʧ��
extern const int SEC_P12CERT_CHANGEDATATOASN1ERR;			//��ͨ����ת��Ϊasn.1��������ʧ��
extern const int SEC_P12CERT_ADDDATATOBAGSERR;				//������ݵ�bags��ʧ��
extern const int SEC_P12CERT_ADDP7DATATOP7LISTERR;			//��pkcs7ģʽ������ӵ�pkcs7ģʽ����������ʧ��
extern const int SEC_P12CERT_CHANGEPRIKEYTOP8ERR;			//����Կ�����pcks8ģʽ
extern const int SEC_P12CERT_ADDKEYUSETOBAGSERR;			//����Կ��;��Ϣд��bags��ʧ��
extern const int SEC_P12CERT_CREATP12STRUCTERR;				//����p12�ṹ��ʧ��
extern const int SEC_P12CERT_CHANGBAGSTOP7ERR;				//��bags���ݱ��ת����pkcs7����ģʽʧ��
extern const int SEC_P12CERT_INITP12ERR;					//��ʼ��p12�ṹ��ʧ��
extern const int SEC_P12CERT_ADDP7TOP12ERR;					//����pkcs7���ݰ���Ϣ��p12�ṹ��ʧ��
extern const int SEC_P12CERT_P12HASHERR;					//���p12��Ϣ��hash����ʧ��
extern const int SEC_P12CERT_P12FILETOP12STRUCTERR;			//p12�ļ�ģʽת��Ϊp12�ṹ��ʧ��
extern const int SEC_P12CERT_READPRIKEYFROMP12ERR;			//����Կ�ļ��ж�ȡ��Կʧ��
extern const int SEC_P12CERT_BAGSTOP7STRUCTERR;				//��bags����������p7�ṹ��ʧ��
extern const int SEC_P12CERT_ADDFRIENDLYNAMETOBAGERR;		//��bag����Ӹ�����
extern const int SEC_P12CERT_WRITEPRIKEYTOBAGSERR;			//����Կд��bagsʧ��
extern const int SEC_P12CERT_P12STRUCTTOP12FILEERR;			//P12�ṹ��ģʽת�����ļ�ģʽʧ��

//p12������
extern const int SEC_P12INFO_RDDATAFROMBIOERR;				//��bioͨ���ж�ȡ����ʧ��
extern const int SEC_P12INFO_P12FILETOSTRUCT;				//���ļ�ģʽp12ת��Ϊ�ṹ��ģʽ
extern const int SEC_P12INFO_P12PASSWORDNOTRIGHT;			//p12�ļ�������֤ʧ��
extern const int SEC_P12INFO_GETP7INFOFROMP12ERR;			//��p12�����н���p7���ݰ�ʧ��
extern const int SEC_P12INFO_GETBAGFROMBAGSERR;				//��p7���ݰ��ж�ȡbags����ʧ��
extern const int SEC_P12INFO_RDKEYIDERR;					//p12��ȡkeyidʧ��
extern const int SEC_P12INFO_GETP8FROMP12ERR;				//p12��ȡpkcs8���ݰ�ʧ��
extern const int SEC_P12INFO_GETPRIKEYFROMP8ERR;			//p12��ȡpkcs8���е���Կʧ��
extern const int SEC_P12INFO_GETCERTFROMP12ERR;				//p12�л�ȡ֤�����ݰ�ʧ��
extern const int SEC_P12INFO_CERTTYPEERR;					//p12��֤�����ݰ��Ƿ�x509v3��ʽ
extern const int SEC_P12INFO_RDCERTERR;						//֤�����ݰ��ж�ȡ֤����Ϣʧ��
extern const int SEC_P12INFO_DEVICEP12NOTEXIT;				//Device.P12������
extern const int SEC_P12INFO_DEVICEP12CERTLISTNOTEXIT;		//�������豸P12�е�֤����Ϊ��
extern const int SEC_P12INFO_DEVICEP12LEAFCERTNOTEXIT;		//�������豸P12�е�Ҷ��֤��Ϊ��
extern const int SEC_P12INFO_DEVICEP12PRIVATEKEYNOTEXIT;	//�������豸P12�е�˽ԿΪ��
extern const int SEC_P12INFO_USERP12NOTEXIT;				//user.P12������,�ļ���Ϊ��
extern const int SEC_P12INFO_USERP12CERTLISTNOTEXIT;		//�������û�P12�е�֤����Ϊ��
extern const int SEC_P12INFO_USERP12LEAFCERTNOTEXIT;		//�������û�P12�е�Ҷ��֤��Ϊ��
extern const int SEC_P12INFO_USERP12PRIVATEKEYNOTEXIT;		//�������û�P12�е�˽ԿΪ��
extern const int SEC_P12INFO_TRUSTCAP12NOTEXIT;				//trustca.P12������,�ļ���Ϊ��
extern const int SEC_P12INFO_TRUSTCAP12CERTLISTNOTEXIT;		//������trustcaP12�е�֤����Ϊ��
extern const int SEC_P12INFO_TRUSTCAP12LEAFCERTNOTEXIT;		//������trustcaP12�е�Ҷ��֤��Ϊ��
extern const int SEC_P12INFO_PARSERP12ERR; 					//����p12����
extern const int SEC_P12INFO_PARSERP12NOTEXISTCALIST; 		//����p12��õ���֤����Ϊ��
//======================================================//

//=======Tlsͨ��========================================//
//tlsͨ�ſͻ���
extern const int TLS_CLIENT_INITTRANTYPEERR;				//��ʼ��tlsͨ�ŷ�ʽʧ��
extern const int TLS_CLIENT_INITTRANINFOERR;				//��ʼ��tlsͨ��������Ϣʧ��
extern const int TLS_CLIENT_INITTRANCERTERR;				//��ʼ��tlsͨ��ʹ�õ�ʵ��֤��ʧ��
extern const int TLS_CLIENT_CERTPRIKEYNOTPAIR;				//tlsͨ�ŵ�֤����˽Կ��ƥ��
extern const int TLS_CLIENT_NOTINITPRIKEY;					//δ��ʼ��tlsͨ��ʹ�õ���Կ
extern const int TLS_CLIENT_CREATSOCKETHANDLEERR;			//����socket���ʧ��
extern const int TLS_CLIENT_SOCKETCONNETFALED;				//socket���ӷ�������ʧ��
extern const int TLS_CLIENT_TLSCONNECTFAILED;				//tls CONNECTʧ��
extern const int TLS_CLIENT_SETSOCKETHANDLETOTLSFAILED;		//����socket�����tls���Ӿ����ʧ��
extern const int TLS_CLIENT_SETOVERTIMEERR;					//���ó�ʱʱ��ʧ��
extern const int TLS_CLIENT_RDERR;							//tls��ȡ����ʧ��
extern const int TLS_CLIENT_WRERR;							//tlsд����ʧ��
extern const int TLS_CLIENT_CLOSESOCKETERR;					//�ر�sockethandleʧ��
extern const int TLS_CLIENT_INITPRIKEYERR;					//��ʼ��˽Կʧ��
extern const int TLS_CLIENT_ADDCERTTOSTOREERR;				//���֤�鵽x509storeʧ��
extern const int TLS_CLIENT_TIMEOUT;                    	//TLS��ʱadd by huweihua  
extern const int TLS_CLIENT_INITCIPHERERR;              	//��ʼ��TLSͨ����Կ�㷨ʧ��add by huweihua
extern const int TLS_CLIENT_CLOSED;                     	//TLS�����ѹر�add by huweihua   
extern const int TLS_CLIENT_SERVERCALISTNOTEXIST;       	//��������֤����������add by huweihua
extern const int TLS_CLIENT_LOCALCERTNOTEXIST;          	//�ͻ���֤�鲻����add by huweihua
extern const int TLS_CLIENT_PRIVATEKEYNOTEXIST;         	//�ͻ���˽Կ������add by huweihua
extern const int TLS_CLIENT_P12PASSWORDNOTEXIST;        	//p12�ļ����벻����add by huweihua

//tls��������
extern const int TLS_SERVER_GETSOCKHANDLEERR;				//��tlsͨ�ž���ж�ȡsocket���ʧ��
extern const int TLS_SERVER_SOCKACCEPTERR;					//socket acceptʧ��
extern const int TLS_SERVER_TLSACCEPTERR;					//tls acceptʧ��
extern const int TLS_SERVER_SOCKBINDERR;					//tls bindʧ��
extern const int TLS_SERVER_LISTENERR;						//tls bindʧ��
extern const int TLS_SERVER_HANDSHACKERR;					//tls ����ʧ��
extern const int TLS_SERVER_INITPRIKEYERR;					//��ʼ��˽Կʧ��
extern const int TLS_SERVER_ADDCERTTOSTOREERR;				//���֤�鵽x509storeʧ��
extern const int TLS_SERVER_INITTRANTYPEERR;				//��ʼ��tlsͨ�ŷ�ʽʧ��
extern const int TLS_SERVER_INITTRANINFOERR;				//��ʼ��tlsͨ��������Ϣʧ��
extern const int TLS_SERVER_INITTRANCERTERR;				//��ʼ��tlsͨ��ʹ�õ�ʵ��֤��ʧ��
extern const int TLS_SERVER_CERTPRIKEYNOTPAIR;				//tlsͨ�ŵ�֤����˽Կ��ƥ��
extern const int TLS_SERVER_NOTINITPRIKEY;					//δ��ʼ��tlsͨ��ʹ�õ���Կ
extern const int TLS_SERVER_CREATSOCKETHANDLEERR;			//����socket���ʧ��
extern const int TLS_SERVER_SOCKETCONNETFALED;				//socket���ӷ�������ʧ��
extern const int TLS_SERVER_TLSACCEPTFAILED;				//tls ACCEPTʧ��
extern const int TLS_SERVER_SETSOCKETHANDLETOTLSFAILED;		//����socket�����tls���Ӿ����ʧ��
extern const int TLS_SERVER_SETOVERTIMEERR;					//���ó�ʱʱ��ʧ��
extern const int TLS_SERVER_RDERR;							//tls��ȡ����ʧ��
extern const int TLS_SERVER_WRERR;							//tlsд����ʧ��
extern const int TLS_SERVER_CLOSESOCKETERR;					//�ر�sockethandleʧ��
extern const int TLS_SERVER_TIMEOUT;						//TLS��ʱ��add by huweihua
extern const int TLS_SERVER_INITCIPHERERR;					//��ʼ��TLSͨ����Կ�㷨ʧ��add by huweihua
extern const int TLS_SERVER_CLOSED;                     	//TLS�����ѹر�add by huweihua   
extern const int TLS_SERVER_CLIENTCALISTNOTEXIST;       	//�ͻ���֤���������� add by huweihua
extern const int TLS_SERVER_LOCALCERTNOTEXIST;          	//������֤�鲻���� add by huweihua
extern const int TLS_SERVER_PRIVATEKEYNOTEXIST;         	//������˽Կ������ add by huweihua
//======================================================//

//==========xml����ģ��==================================//
extern const int XML_XML_DATAEMPTY;							//���ص�XML����Ϊ��
extern const int XML_XML_DATAWRONGFORMAT;					//���ص�XML���ݸ�ʽ����
extern const int XML_XML_LOADDATAERR;						//δ����XML���ݻ����XML���ݸ�ʽ����
extern const int XML_XML_ADDNODENODEPATHERR;				//��ӽڵ�Ľڵ�·��Ϊ�գ����Ϊ�գ���Ĭ����ӵ������ڵ㣩
extern const int XML_XML_ADDNODEPATHERR;					//��ӵĽڵ�·���������ڵ�����Ϊ��
extern const int XML_XML_FINDNODEPATHERR;					//��ӵĽڵ�·���������ڵ������Ҳ���
extern const int XML_XML_NODENAMENOTEXIT;					//��ӵĽڵ�����������·����������
extern const int XML_XML_XMLDATAEMPTY;						//��ӵ�XML����Ϊ��
extern const int XML_XML_ADDXMLDATAERR;						//��ӵ�XML���ݸ�ʽ����
extern const int XML_XML_ADDNODEERR;						//��ӽڵ�ʧ��
extern const int XML_XML_DELNODEPATHEMPTY;					//ɾ���Ľڵ�·���������ڵ�����Ϊ��
extern const int XML_XML_DELNODEPATHNOTEXIT;				//ɾ���Ľڵ�·���������ڵ�����������
extern const int XML_XML_DELNODENOTEXIT;					//ɾ���Ľڵ�����������·����������
extern const int XML_XML_FINDXMLDATAERR;					//���ҽڵ�XML����ʧ��
extern const int XML_XML_DELNODEFAIL;						//ɾ���ڵ�ʧ��
extern const int XML_XML_MODIFYNODEPATHEMPTY;				//�޸ĵĽڵ�·���������ڵ�����Ϊ��
extern const int XML_XML_MODIFYNODEPATHNOTXEIXT;			//�޸ĵĽڵ�·���������ڵ�����������
extern const int XML_XML_MODIFYNODENAMENOTEXIT;				//�޸ĵĽڵ�����������·����������
extern const int XML_XML_MODIFYNODEERR;						//�޸Ľڵ�ʧ��
extern const int XML_XML_FINDNODEPATHEMPTY;					//���ҵĽڵ�·���������ڵ�����Ϊ��
extern const int XML_XML_FINDNODENAMENOTEXIT;				//���ҵĽڵ�����������·����������
extern const int XML_XML_FINDNODEPATHNOTEXIT;				//���ҵĽڵ�·���������ڵ�����������
extern const int XML_XML_FINDNOTFAIL;						//���ҽڵ�ʧ��
extern const int XML_XML_STOREXMLDATAEMPTY;					//Ҫ�����XML����Ϊ��
extern const int XML_XML_STOREXMLDATAFAIL;					//����XML����ʧ��
extern const int XML_XML_TEMPLATEINITERR;					//ģ���ʼ��ʧ��
extern const int XML_XML_TEMPLATEPARSEERR;					//ģ�����ʧ��
extern const int XML_XML_INITSENDMESSAGEFAIL;				//��Ϣ��ʼ��������Ϣʧ��
extern const int XML_XML_INITPARSEMESSAGEFAIL;				//��Ϣ��ʼ��������Ϣʧ��

extern const int XML_MSG_GETDIGESTMETHODERR;  				//��ȡժҪ��������
extern const int XML_MSG_GETSIGMETHODERR;     				//��ȡǩ���㷨����
extern const int XML_MSG_DIGESTVERIFYERR;     				//ժҪ��֤ʧ��
extern const int XML_MSG_SIGNVERIFYERR;       				//ǩ����֤ʧ��
extern const int XML_MSG_GETGENKEYMETHODERR;				//��ȡ������Կ�㷨����
extern const int XML_MSG_GETENCKEYMETHODERR;  				//��ȡ����Կ���м��ܵ��㷨����
extern const int XML_MSG_GETDEVICETYPEERR;					//��ȡ�豸���ʹ���
extern const int XML_MSG_GETKEYLENERR;		    			//��ȡ��Կ���ȴ���(��Կ������)
//======================================================//

//=========tcp/ip ͨ��ģ��==============================//
extern const int TRAN_SOCK_CONNECTERR;						//����ʧ��
extern const int TRAN_SOCK_HANDLEERR;						//��·δ����
extern const int TRAN_SOCK_SENDDATAERR;						//��������ʧ��
extern const int TRAN_SOCK_BUFEMPTY;						//��������Ϊ��
extern const int TRAN_SOCK_RECVDATAERR;						//��������ʧ��
extern const int TRAN_SOCK_RECVDATAWRONG;					//û����Ҫ���յ�����
//======================================================//

//==========��ͷģ��====================================//
extern const int HEAD_HTTP_ADDERR;							//��ӱ�ͷ��
extern const int HEAD_HTTP_SESSIONERR;						//��ͷ��û��session��session�Ƿ�
extern const int HEAD_HTTP_LENGTHERR;						//��ͷ���ȴ�
extern const int HEAD_HTTP_LENGTHEMPTY;						//��ͷ��û�����ݳ��Ȼ򳤶�Ϊ0
extern const int HEAD_HTTP_NOHAVEHEADDATA;					//û�б�ͷ����
//======================================================//

//======================���ݹ���ģ��====================//
extern const int CON_MANAGE_SETHEADERR;             		//��������ͷʧ��
extern const int CON_MANAGE_GETHEADERR;             		//��ȡ����ͷʧ��
extern const int CON_MANAGE_KEYRGISTRSPMSGTYPERR;   		//��Կע����Ӧ��Ϣ���ʹ���
extern const int CON_MANAGE_KEYGENERRSPMSGTYPERR;   		//��Կ������Ӧ��Ϣ���ʹ���
extern const int CON_MANAGE_GETSERVERKEYERR;        		//��ȡ���������ɵ���Կʧ��
extern const int CON_MANAGE_GETSERVERINSDOIERR;     		//��ȡ���������ɵ�InstanceDOIʧ��
extern const int CON_MANAGE_GETSERVERMASDOIERR;     		//��ȡ���������ɵ�MasterDOIʧ��
extern const int CON_MANAGE_CONDIGINSMSGTYPERR;     		//����ʵ��ע����Ӧ��Ϣ���ʹ���
extern const int CON_MANAGE_CONASSIDFMSGTYPERR;     		//������ʵ����Ӧ��Ϣ���ʹ���
extern const int CON_MANAGE_GENERATEKEYERR;         		//������Կʧ��
extern const int CON_MANAGE_GENERATEKEYIDERR;       		//������ԿIDʧ��
//======================================================//

//==========�豸����ģ��================================//
extern const int DEVICE_MANAGE_GETTYPEERR;         			//��ȡ�豸����ʧ��
extern const int DEVICE_MANAGE_GENDEVICEIDERR;     			//�����豸ID����
extern const int DEVICE_MANAGE_GETDEVICEINFOERR;   			//��ȡ�豸��Ϣʧ��
extern const int DEVICE_MANAGE_SETDEVICEREQERR;    			//����ע���豸������Ϣʧ��
extern const int DEVICE_MANAGE_RESPONSEMSGTYPERR;  			//��Ӧ����Ϣ���ʹ���
extern const int DEVICE_MANAGE_GETP12PATHERR;      			//��ȡp12�ļ�������
//======================================================//

//==========SM�豸����ģ��==============================//
extern const int SM_DEVICE_MANAGE_ADDDEVICEERR;       		//����豸ʧ��
extern const int SM_DEVICE_MANAGE_DELETEDEVICEERR;    		//ɾ���豸ID����
extern const int SM_DEVICE_MANAGE_GETDEVICEINFOERR;   		//��ȡ�豸��Ϣʧ��
//======================================================//

//==========SM֤�����ģ��==============================//
extern const int SM_CERT_MANAGE_IMPORTCERTERR;   			//����֤��ʧ��
extern const int SM_CERT_MANAGE_DESTORYCERTERR;  			//����֤��ʧ��
extern const int SM_CERT_MANAGE_VERIFYCERTERR;   			//��֤֤��ʧ��
extern const int SM_CERT_MANAGE_EXPORTCERTISNONE;   		//Ҫ������֤�鲻���� //add by yin 2010.10.11
extern const int SM_CERT_MANAGE_DESTROYCERTISNONE;   		//Ҫɾ����֤�鲻���� //add by yin 2010.10.11
//======================================================//

//==========KDM����ģ��=================================//
extern const int SM_KDMPARSER_LOADETMSCHEMAERR;       		//����etm��schemaʧ��
extern const int SM_KDMPARSER_LOADKDMSCHEMAERR;       		//����KDM��schemaʧ��
extern const int SM_KDMPARSER_KDMFORMATERR;           		//KDM��ʽ��֤ʧ��
extern const int SM_KDMPARSER_GETCERTCHAINERR;   		  	//��ȡKDM֤����ʧ��
extern const int SM_KDMPARSER_LOADCERTCHAINERR;   			//����KDM֤����ʧ��
extern const int SM_KDMPARSER_VERIFYCERTFORMATERR;    		//KDM֤�����е�֤���ʽ��֤ʧ��
extern const int SM_KDMPARSER_VERIFYCERTCHAINERR;   		//KDM��֤֤����ʧ��
extern const int SM_KDMPARSER_GETISSUEDATEERR;   			//��ȡKDM����ʱ��ʧ��
extern const int SM_KDMPARSER_GETCERTVALIDITYTIMEERR; 		//��ȡ֤����Чʱ��ʧ��
extern const int SM_KDMPARSER_GETVALIDITYTIMEERR;   		//��ȡKDM��Чʱ��ʧ��
extern const int SM_KDMPARSER_ISSUEDATEERR;   				//KDM����ʱ�䲻��֤�����Ч��֮��
extern const int SM_KDMPARSER_VALIDITYTIMEERR;   			//KDM��Чʱ�䲻��֤�����Ч��֮��
extern const int SM_KDMPARSER_NOTINVALIDITYTIMEERR;   		//��ǰʱ�䲻��KDM��Чʱ��֮��
extern const int SM_KDMPARSER_VERIFYSIGNATUREERR;   		//KDMǩ����֤ʧ��
extern const int SM_KDMPARSER_VERIFYTDLERR;   				//TDL��֤ʧ��
extern const int SM_KDMPARSER_NODEEXISTERR;   				//KDM�ڵ�����Դ���
extern const int SM_KDMPARSER_NODEVALUEERR;   				//KDM�ڵ�ֵ����
extern const int SM_KDMPARSER_NODEATTRIBUTEERR;   			//KDM�ڵ�����ֵ����
extern const int SM_KDMPARSER_DECNODEVALUEERR;   			//KDM���ܺ���������ֵ����
extern const int SM_KDMPARSER_GETCONTENTKEYERR;   			//��ȡ������Կʧ��
extern const int SM_KDMPARSER_GETCPLIDERR;   				//��ȡCPLIdʧ��
extern const int SM_KDMPARSER_GETSIGNERTHUMBPRINTERR; 		//��ȡǩ��֤��ָ��ʧ��
extern const int SM_KDMPARSER_GETKDMIDERR;            		//��ȡKDMIdʧ��
extern const int SM_KDMPARSER_KEYIDMATCHERR;          		//CPL�е�KeyId��KDM�е�KeyIdƥ��ʧ��
extern const int SM_KDMPARSER_KEYIDEXISTERR;          		//KDM�е�KeyIdList�µ�KeyId�ڵ㲻����
//======================================================//

//==========CPL��֤ģ��=================================//
extern const int SM_CPLVERIFY_LOADCPLSCHEMAERR;   			//����CPL��schemaʧ��
extern const int SM_CPLVERIFY_FORMATERR;          			//CPL��ʽ��֤ʧ��
extern const int SM_CPLVERIFY_CONTENTERR;   		  		//CPL������֤ʧ��
extern const int SM_CPLVERIFY_VERIFYSIGNATUREERR; 			//CPLǩ����֤ʧ��
extern const int SM_CPLVERIFY_VERIFYCERTFORMATERR;			//CPL֤���ʽ��֤ʧ��
extern const int SM_CPLVERIFY_MISSINGSIGNATRUEERR;			//CPLǩ��������
extern const int SM_CPLVERIFY_GETCPLIDERR;          		//��ȡCPLIdʧ��
extern const int SM_CPLVERIFY_GETTRACKFILEIDERR;    		//��ȡ�켣�ļ�IDʧ��
extern const int SM_CPLVERIFY_GETKEYIDERR;          		//��ȡKeyIdʧ��
//======================================================//

//==========PKL��֤ģ��=================================//
extern const int SM_PKLVERIFY_LOADCPLSCHEMAERR;   			//����PKL��schemaʧ��
extern const int SM_PKLVERIFY_FORMATERR;          			//PKL��ʽʧ��
extern const int SM_PKLVERIFY_ASSETMAPPARSERERR;  			//xml����ASSETMAP�ļ�ʧ��
extern const int SM_PKLVERIFY_CONTENTERR;   		  		//PKL������֤ʧ��
extern const int SM_PKLVERIFY_VERIFYSIGNATUREERR; 			//PKLǩ����֤ʧ��  
extern const int SM_PKLVERIFY_UUIDFORMATERR; 				//uuid��ʽ��֤ʧ��[RFC-4122]
//======================================================//

//==========SECURITYENVIROMENTģ��======================//
extern const int SM_SECENV_GETCSPINFOERR;					//��ȡcspinfoʧ��
extern const int SM_SECENV_GETPRIVATEKEYERR;				//��ȡ˽Կʧ��
extern const int SM_SECENV_GETLEAFCERTERR;					//��ȡҶ��֤��ʧ��
extern const int SM_SECENV_GETCERTCHAINERR;					//��ȡ֤����ʧ��
extern const int SM_SECENV_GETHASHOFCERTCHAINERR;			//����֤���ļ���hashֵʧ��
extern const int SM_SECENV_CMPHASHOFCERTCHAINERR;			//�Ƚϼ����֤���ļ���hashֵ��Ԥ�洢��hash����
extern const int SM_SECENV_CHECKKEYPAIRERR;      			//�豸֤����˽Կ��ƥ��
extern const int SM_SECENV_GETUSERLEAFCERTERR;   			//��ȡ�û�֤��ʧ�� add by yin 2011.8.25
extern const int SM_SECENV_GETOFFICERLEAFCERTERR; 			//��ȡ��ȫ��֤��ʧ�� add by yin 2011.8.25
//======================================================//

//==========���ô�����==================================//
extern const int SM_DMP_OPENERR;  							//��ȫ�洢��û�д�
//======================================================//

//===============CSP����================================//
extern const int CSP_MANAGE_DMP_OPENERR;  					//��ȫ�洢��û�д�
extern const int CSP_MANAGE_DMP_SET_CSPS_ENCKEYERR; 		//��ȫ�洢������csps_enckey����ʧ��
extern const int CSP_MANAGE_DMP_GET_CSPS_ENCKEYERR; 		//��ȫ�洢����ȡcsps_enckey����ʧ��
extern const int CSP_MANAGE_DMP_SET_CSPS_RANDSEEDERR; 		//��ȫ�洢������csps_randseed����ʧ��
extern const int CSP_MANAGE_DMP_GET_CSPS_RANDSEEDERR;		//��ȫ�洢����ȡcsps_randseed����ʧ��
extern const int CSP_MANAGE_DMP_SET_CSPS_DEVICEPRIKEYERR;	//��ȫ�洢������csps_deviceprikey����ʧ��
extern const int CSP_MANAGE_DMP_GET_CSPS_DEVICEPRIKEYERR;	//��ȫ�洢����ȡcsps_deviceprikey����ʧ��
extern const int CSP_MANAGE_DMP_SET_CSPS_SEEDKEYERR;		//��ȫ�洢������csps_seedkey����ʧ��
extern const int CSP_MANAGE_DMP_GET_CSPS_SEEDKEYERR;		//��ȫ�洢����ȡcsps_seedkey����ʧ��
extern const int CSP_MANAGE_DMP_SET_CSPS_IVERR;				//��ȫ�洢������csps_iv����ʧ��
extern const int CSP_MANAGE_DMP_GET_CSPS_IVERR;				//��ȫ�洢����ȡcsps_iv����ʧ��
extern const int CSP_MANAGE_DMP_SET_CSPS_HMACKEYERR;		//��ȫ�洢������csps_hmackey����ʧ��
extern const int CSP_MANAGE_DMP_GET_CSPS_HMACKEYERR;		//��ȫ�洢�����csps_hmackey����ʧ��
extern const int CSP_MANAGE_DMP_SET_CSPS_HMACVALUEERR;		//��ȫ�洢������csps_hmacvalue����ʧ��
extern const int CSP_MANAGE_DMP_GET_CSPS_HMACVALUEERR;		//��ȫ�洢�����csps_hmacvalue����ʧ��
extern const int CSP_MANAGE_DMP_SET_CSPS_FIRMWAREKEYERR;	//��ȫ�洢������csps_firmwarekey����ʧ��
extern const int CSP_MANAGE_DMP_GET_CSPS_FIRMWAREKEYERR;	//��ȫ�洢�����csps_firmwarekey����ʧ��
extern const int CSP_MANAGE_DMP_SET_CSPS_TIMEVALUEERR;		//��ȫ�洢������csps_timevalue����ʧ��
extern const int CSP_MANAGE_DMP_GET_CSPS_TIMEVALUEERR;		//��ȫ�洢����ȡcsps_timevalue����ʧ��
extern const int CSP_MANAGE_DMP_SET_CSPS_KEKERR;			//��ȫ�洢������csps_kek����ʧ��
extern const int CSP_MANAGE_DMP_GET_CSPS_KEKERR;			//��ȫ�洢�����csps_kek����ʧ��
extern const int CSP_MANAGE_CSPS_CLEARALLCSPSERR;			//�������csps����ʧ��
extern const int CSP_MANAGE_CSPS_SETALLCSPSERR;				//��������csps����ʧ��
extern const int CSP_MANAGE_CSPS_RESETCSPSERR;				//��������csps����ʧ��	
extern const int CSP_MANAGE_CSPS_SETCSPSERR;				//����csps����ʧ��
extern const int CSP_MANAGE_CSPS_GETCSPSERR;				//�������csps����ʧ��
//add by yin 2010.10.11
extern const int CSP_MANAGE_SMCERTFILE_NOEXSIT;				//SM֤���ļ�������
extern const int CSP_MANAGE_SMCAFILE_NOEXSIT;				//SM CA֤���ļ�������
extern const int CSP_MANAGE_SMSCAFILE_NOEXSIT;				//SMS CA֤���ļ�������
extern const int CSP_MANAGE_PROJECTCAFILE_NOEXSIT;			//PROJECT CA֤���ļ�������
extern const int CSP_MANAGE_ALLCERTFILE_NOEXSIT;			//ϵͳ�в������κ�֤���ļ�
//add by yin 2011.8.25
extern const int CSP_MANAGE_USERCERTFILE_NOEXSIT;           //��ͨ�û�֤���ļ�������
extern const int CSP_MANAGE_OFFICERCERTFILE_NOEXSIT;       	//��ȫ��֤���ļ�������
extern const int CSP_MANAGE_USERCAFILE_NOEXSIT;            	//��ͨ�û�֤�����ļ�������
extern const int CSP_MANAGE_OFFICERCAFILE_NOEXSIT;          //��ȫ��֤�����ļ�������
//add by yin 2011.9.9
extern const int CSP_MANAGE_PARSERCSPVALUE_LENISZERO;       //������Ӳ���л��CSPֵ��ʵ�ʳ���Ϊ0
//======================================================//

//===============KEY����================================//
extern const int KEY_MANAGE_DMP_OPENERR;					//��ȫ�洢��û�д�
extern const int KEY_MANAGE_GENERATERAND_ERR;				//���������ʧ��
extern const int KEY_MANAGE_GENERATEKEK_ERR;				//�������ݼ�����Կʧ��
extern const int KEY_MANAGE_GENERATELEKEYID_ERR;			//����LE keyIDʧ��
extern const int KEY_MANAGE_GENERATELEKEYDATA_ERR;			//����LE keydataʧ��
extern const int KEY_MANAGE_GENERATELEKEYATTRIDATA_ERR;		//����LE keyattridataʧ��
extern const int KEY_MANAGE_GENERATECONTENTKEY_ERR;			//����������Կʧ��
extern const int KEY_MANAGE_GENERATECONTENTKEYNULL_ERR;		//��������Կ
extern const int KEY_MANAGE_DMP_SET_CEKERR;					//��Ӳ���洢������Կʧ��
extern const int KEY_MANAGE_GENERATELEKEYNULL_ERR;			//��LE��Կ
extern const int KEY_MANAGE_DMP_SET_CINELINKKEYERR;			//��Ӳ���洢cinelink keyʧ��
extern const int KEY_MANAGE_LOADLDKEY_ERR;					//����LDkeyʧ��
extern const int KEY_MANAGE_DMP_CLEARCEKERR;				//���Ӳ���洢�е�������Կʧ��
extern const int KEY_MANAGE_DMP_CLEARCINELINKKEYERR;		//���Ӳ���洢�е���·��Կʧ��
extern const int KEY_MANAGE_SETCINELINKENABLEERR;      		//���ô���·���ܹ���ʧ��   //add by yin 2011.8.25 start 
extern const int KEY_MANAGE_SETCINELINKDISABLEERR;      	//���ùر���·���ܹ���ʧ��
extern const int KEY_MANAGE_SETFORENSICMARKINGINFERR;   	//����ˮӡ��Ϣʧ��
extern const int KEY_MANAGE_SETFORENSICMARKINGKEYERR;   	//����ˮӡ��Կʧ��
extern const int KEY_MANAGE_SETFORENSICMARKINGENABLEERR;    //���ô�ˮӡ����ʧ��
extern const int KEY_MANAGE_SETFORENSICMARKINGDISABLEERR;   //���ùر�ˮӡ����ʧ�� //add by yin 2011.8.25 end
//======================================================//

//===============�����֤===============================//
//extern const int Authentication_DMP_OPENERR;				//�����֤ģ�鰲ȫ�洢��û�д�
extern const int AUTHENTICATION_NOTHEUSERERR;				//�����֤ģ��û�д��û�
extern const int AUTHENTICATION_PASSWORDERR;				//�����֤ģ���������
extern const int AUTHENTICATION_RIGHTOFREPONSEISNULLERR;	//�����֤��Ӧ��û��Ȩ����Ϣ
extern const int AUTHENTICATION_DMP_GETUSERINFOERR;			//��Ӳ���洢�л���û���Ϣʧ��
extern const int AUTHENTICATION_X509CERT_SIGNERR;			//�������֤������Ϣǩ��ʧ��
//======================================================//

class CDrmError
{
	
public:
	CDrmError();
	virtual ~CDrmError();
	
	int GetErrorNumber() const; 			//��ȡ������
	int SetErrorNumber(int ErrorNumber); 	//���ô�����
	
private:
	vector<int> m_Error;					//������
	
};

extern CDrmError pubError;	

#endif
