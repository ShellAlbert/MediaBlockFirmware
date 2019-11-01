#ifndef _ERRORNUMBER_H_
#define _ERRORNUMBER_H_

#include <vector>
using namespace std;

//========全局错误码====================================//
extern const int PUB_SHARE_OK;								//操作成功
extern const int PUB_SHARE_IPUTPARAMERR;					//输入参数错误
extern const int PUB_SHARE_NEWMEMFAILED;					//内存分配失败
extern const int PUB_SHARE_OPENFILEFAILED;					//打开文件错误
extern const int PUB_SHARE_XMLDOCERR;						//xml错误
extern const int PUB_SHARE_HASHARITHFAILED;					//Hash运算失败
extern const int PUB_SHARE_RSAARITHENCFAILED;				//Rsa加密失败
extern const int PUB_SHARE_RSAARITHDECFAILED;				//Rsa解密失败
extern const int PUB_SHARE_SYMARITHENCFAILED;				//对称加密失败
extern const int PUB_SHARE_SYMARITHDECFAILED;				//对称解密失败
extern const int PUB_SHARE_BASE64ENCFAILED;					//Base编码失败
extern const int PUB_SHARE_BASE64DECFAILED;					//Base解码失败
extern const int PUB_SHARE_ASN1CHAGEFAILED;					//ASN1内部转码失败
extern const int PUB_SHARE_INITERR;							//变量(类)初始化失败
extern const int PUB_SHARE_OPENSSLCHANGETYPEERR;			//openssl中字符串与证书转换失败
extern const int PUB_SHARE_NOINITSecurityEnviroment;		//安全环境未初始化
extern const int PUB_SHARE_USERNOLOGIN;						//用户未登录
extern const int PUB_SHARE_DEVICENOTREGISTER;				//设备未注册
extern const int PUB_SHARE_CONEER;			            	//与服务器连接失败
extern const int PUB_SHARE_SENDDATAERR;			        	//向服务器发送数据失败
extern const int PUB_SHARE_REVICEBUFISNOTHING;				//从服务器接收到的数据为空
extern const int PUB_SHARE_TIMESYNCERR;			        	//设置时间错误
extern const int PUB_SHARE_OPENFILENOEXIST;					//要打开的文件不存在  //add by yin 2010.10.11
//======================================================//


//======算法类模块======================================//
extern const int ARI_ARITHMATIC_INITHASHERR;				//初始化hash运算失败
extern const int ARI_ARITHMATIC_PRIKEYENCERR;				//私钥加密失败
extern const int ARI_ARITHMATIC_CREATSIGNDATAERR;			//生成签名数据失败
extern const int ARI_ARITHMATIC_PUBKEYENCERR;				//公钥解密失败
extern const int ARI_ARITHMATIC_VERIFYERR;					//验证签名失败
extern const int ARI_ARITHMATIC_BASE64ENCERR;				//base64编码失败
extern const int ARI_ARITHMATIC_BASE64DECERR;				//base64解码失败
extern const int ARI_ARITHMATIC_CREATRANDOMNUMERR;			//生成随机数失败
extern const int ARI_ARITHMATIC_SYMENCERR;					//对称加密失败
extern const int ARI_ARITHMATIC_SYMINITERR;					//对称加密初始化加密参数失败
extern const int ARI_ARITHMATIC_SYMDECERR;					//获取对称加密数据失败
extern const int ARI_ARITHMATIC_GETHASHDATAERR;				//获取hash运算数据失败
extern const int ARI_ARITHMATIC_INITSIGNERR;				//init sign算法失败
extern const int ARI_ARITHMATIC_UPDATESIGNERR;				//update sign算法失败
extern const int ARI_ARITHMATIC_FINALSIGNERR;				//final sign算法失败
extern const int ARI_ARITHMATIC_INITVERIFYERR;				//init verify算法失败
extern const int ARI_ARITHMATIC_UPDATEVERIFYERR;			//update verify算法失败
extern const int ARI_ARITHMATIC_FINALVERIFYERR;				//final verify算法失败
extern const int ARI_ARITHMATIC_GENTKEYERR;					//生成密钥失败
extern const int ARI_ARITHMATIC_GENTCRCERR;					//生成CRC失败 20100720 by xiaozhengxiu add
extern const int ARI_ARITHMATIC_VERIFYCRCERR;				//验证CRC失败 20100720 by xiaozhengxiu add
extern const int ARI_ARITHMATIC_GENTRANDERR;				//生成随机数失败 //add by yin 6.7
extern const int ARI_ARITHMATIC_GENTKEYIDERR;				//生成keyid失败>=4096
extern const int ARI_ARITHMATIC_GENRSAKEYPAIRERR;			//生成RSA密钥对失败
extern const int ARI_ARITHMATIC_GENCERTREQERR;				//生成证书请求失败
//======================================================//

//======安全环境类模块==================================//
//x509请求类
extern const int SEC_X509REQ_CREATRSAKEYERR;				//生成rsa密钥对失败
extern const int SEC_X509REQ_X509REQADDPUBKEYERR;			//在请求证书结构体中添加公钥失败
extern const int SEC_X509REQ_OPENSSLCHANGECODEERR;			//openssl内部转码失败（字符串转换成整数）
extern const int SEC_X509REQ_CREATCERTNAMEENTRYERR;			//生成证书名字entry失败	
extern const int SEC_X509REQ_ADDCERTNAMEENTRYERR;			//添加证书名字entry失败
extern const int SEC_X509REQ_ADDRSATOEVPPKEYERR;			//添加rsa密钥到evppkey结构体失败
extern const int SEC_X509REQ_ADDCOUNTRYNAMEERR;				//添加国家名到x509name结构体失败
extern const int SEC_X509REQ_ADDPROVINCENAMEERR;			//添加省份名到x509name结构体失败
extern const int SEC_X509REQ_ADDCITYNAMEERR;				//添加城市名到x509name结构体失败
extern const int SEC_X509REQ_ADDORGNAMEERR;					//添加组织名到x509name结构体失败
extern const int SEC_X509REQ_ADDDEPARTNAMEERR;				//添加部门信息到x509name结构体失败
extern const int SEC_X509REQ_ADDCOMMONNAMEERR;				//添加common信息到x509name结构体失败
extern const int SEC_X509REQ_ADDNAMETOX509REQERR;			//添加x509name结构体到x509req结构体失败

//X509证书类
extern const int SEC_X509CERT_ADDVERSIONERR;				//添加版本信息到证书失败
extern const int SEC_X509CERT_ADDSNERR;						//添加序列号信息到证书失败
extern const int SEC_X509CERT_ADDBEGINTIMEERR;				//添加有效开始时间信息到证书失败
extern const int SEC_X509CERT_ADDENDTIMEERR;				//添加有效结束时间信息到证书失败
extern const int SEC_X509CERT_ADDCANAMEINFOERR;				//添加发行者信息到证书失败	
extern const int SEC_X509CERT_ADDSUBNAMEINFOERR;			//添加实体证书信息到证书失败
extern const int SEC_X509CERT_ADDPUBKEYERR;					//设置公钥信息到证书失败
extern const int SEC_X509CERT_SIGNERR;						//签名失败
extern const int SEC_X509CERT_VERIFYFAILED;					//验证证书有效性失败
extern const int SEC_X509CERT_INITX509STOREERR;				//初始化X509_STORE 失败
extern const int SEC_X509CERT_READCERTNAMEERR;				//读取实体证书名字信息失败
extern const int SEC_X509CERT_BIOERR;						//判断BIO操作失败
extern const int SEC_X509CERT_CREATCERTFILEERR;				//生成证书文件失败
extern const int SEC_X509CERT_CREATPRIKEYFILEERR;			//生成私钥文件失败

//解析x509证书类
extern const int SEC_X509INFO_DUPCERTERR;					//克隆cert结构体失败
extern const int SEC_X509INFO_READCERTERR;					//从文件中读取出cert结构体失败
extern const int SEC_X509INFO_READBEGINTIEMERR;				//获取证书有效的开始时间失败
extern const int SEC_X509INFO_READENDTIMEERR;				//获取证书有效的结束时间失败
extern const int SEC_X509INFO_READPUBKEYERR;				//读取证书公钥失败
extern const int SEC_X509INFO_READARITHTYPEERR;				//获取证书签名算法类型失败
extern const int SEC_X509INFO_READSNERR;					//获取证书序列号失败
extern const int SEC_X509INFO_READSUBCERTNAMEERR;			//获取实体证书名失败
extern const int SEC_X509INFO_READCACERTNAMEERR;			//获取证书发行者信息失败（结构体）
extern const int SEC_X509INFO_GETCOUTRYNAMEERR;				//获取国家名失败
extern const int SEC_X509INFO_GETPROVINCENAMEERR;			//获取省份名失败
extern const int SEC_X509INFO_GETCITYNAMEERR;				//获取城市名失败
extern const int SEC_X509INFO_GETORGNAMEERR;				//获取组织名失败
extern const int SEC_X509INFO_GETDEPARTNAMEERR;				//获取部门名失败
extern const int SEC_X509INFO_GETCACERTNAMEERR;				//获取发行者信息失败（字符串）

//add by 6.8
extern const int SEC_X509INFO_GETEXTENERR;					//获取扩展失败
extern const int SEC_X509INFO_GETDNQERR;					//获取DNQ失败
extern const int SEC_X509INFO_GETROLEERR;					//获取角色失败
extern const int SEC_X509INFO_LOADCRLERR;					//加载CRL失败
extern const int SEC_X509INFO_LOADERR;   					//加载证书失败
extern const int SEC_X509INFO_NEWSTACKX509ERR;				//new stack of x509失败
extern const int SEC_X509INFO_HASMOREROOTERR; 				//根证书多于一个 
extern const int SEC_X509INFO_HASNOROOTERR;  				//没有找到根证书
extern const int SEC_X509INFO_CERTCHAINISNONEERR;			//证书链为空
extern const int SEC_X509INFO_CERTCHAINSORTERR;				//证书链排序出错
extern const int SEC_X509INFO_CERTTYPEERR;					//设置的证书类型错误
extern const int SEC_X509INFO_STORECTXINITERR;				//初始化证书store ctx错误
extern const int SEC_X509INFO_LOADCERTLISTERR;				//证书链加载失败
extern const int SEC_X509INFO_TIMEVALIDATEERR;				//证书时间有效性错误
extern const int SEC_X509INFO_HASNOLEAFERR;		    		//没有叶子证书
extern const int SEC_X509INFO_HASNOCERTCHAINOFSORTERR;		//排好序的证书链为空
extern const int SEC_X509INFO_INFOTOSTRINGERR;	  			//证书信息结构体转字符串失败
extern const int SEC_X509INFO_INFOSTRINGTOOLENERR;			//证书信息字符串超最大长

//验证x509证书类
extern const int SEC_X509CERTS4302_GETROLEERR;				//获取证书角色失败
extern const int SEC_X509CERTS4302_EXSITROLEERR;		  	//证书不存在角色
extern const int SEC_X509CERTS4302_FORMATERR;			    //证书格式验证失败
extern const int SEC_X509CERTS4302_LOADCERTERR;			  	//加载证书失败
extern const int SEC_X509CERTS4302_LOADCRLERR;			  	//加载CRL失败
extern const int SEC_X509CERTS4302_SORTCERTLISTERR;			//证书链排序失败
extern const int SEC_X509CERTS4302_VERIFYCERTLISTERR;		//证书链验证失败
extern const int SEC_X509CERTS4302_LOADCERTLISTERR;			//证书链加载失败
extern const int SEC_X509CERTS4302_VERIFYVALIDITYTIMEERR;	//证书有效时间验证失败

//pkcs12生成类
extern const int SEC_P12CERT_SETCERTLISTERR;				//设置证书到证书链失败
extern const int SEC_P12CERT_CHECKKEYPAIRERR;				//证书与密钥不是一对密钥对
extern const int SEC_P12CERT_ADDCERTTOBAGERR;				//添加证书到bag中失败
extern const int SEC_P12CERT_ADDOTHERCERTNAMETOBAGERR;		//添加证书附加名到bag中失败
extern const int SEC_P12CERT_CERTHASHERR;					//对证书作hash运算失败
extern const int SEC_P12CERT_ADDHASHVALUETOBAGERR;			//添加证书hash信息到bag中失败
extern const int SEC_P12CERT_ADDKEYIDTOBAGERR;				//添加keyid（openssl中）到bag中失败
extern const int SEC_P12CERT_ADDBAGTOBAGSERR;				//添加bag包到bags中失败
extern const int SEC_P12CERT_GETCERTLISTCERTERR;			//获取证书链中证书失败
extern const int SEC_P12CERT_CHANGEDATATOASN1ERR;			//普通数据转化为asn.1编码数据失败
extern const int SEC_P12CERT_ADDDATATOBAGSERR;				//添加数据到bags中失败
extern const int SEC_P12CERT_ADDP7DATATOP7LISTERR;			//将pkcs7模式数据添加到pkcs7模式数据链表中失败
extern const int SEC_P12CERT_CHANGEPRIKEYTOP8ERR;			//将密钥保存成pcks8模式
extern const int SEC_P12CERT_ADDKEYUSETOBAGSERR;			//将密钥用途信息写入bags中失败
extern const int SEC_P12CERT_CREATP12STRUCTERR;				//生成p12结构体失败
extern const int SEC_P12CERT_CHANGBAGSTOP7ERR;				//将bags数据编程转换成pkcs7编码模式失败
extern const int SEC_P12CERT_INITP12ERR;					//初始化p12结构体失败
extern const int SEC_P12CERT_ADDP7TOP12ERR;					//设置pkcs7数据包信息到p12结构体失败
extern const int SEC_P12CERT_P12HASHERR;					//针对p12信息作hash运算失败
extern const int SEC_P12CERT_P12FILETOP12STRUCTERR;			//p12文件模式转换为p12结构体失败
extern const int SEC_P12CERT_READPRIKEYFROMP12ERR;			//从密钥文件中读取密钥失败
extern const int SEC_P12CERT_BAGSTOP7STRUCTERR;				//从bags数据中生成p7结构体失败
extern const int SEC_P12CERT_ADDFRIENDLYNAMETOBAGERR;		//在bag中添加附加名
extern const int SEC_P12CERT_WRITEPRIKEYTOBAGSERR;			//将密钥写入bags失败
extern const int SEC_P12CERT_P12STRUCTTOP12FILEERR;			//P12结构体模式转换成文件模式失败

//p12解析类
extern const int SEC_P12INFO_RDDATAFROMBIOERR;				//从bio通道中读取数据失败
extern const int SEC_P12INFO_P12FILETOSTRUCT;				//将文件模式p12转换为结构体模式
extern const int SEC_P12INFO_P12PASSWORDNOTRIGHT;			//p12文件密码验证失败
extern const int SEC_P12INFO_GETP7INFOFROMP12ERR;			//从p12数据中解析p7数据包失败
extern const int SEC_P12INFO_GETBAGFROMBAGSERR;				//从p7数据包中读取bags数据失败
extern const int SEC_P12INFO_RDKEYIDERR;					//p12获取keyid失败
extern const int SEC_P12INFO_GETP8FROMP12ERR;				//p12获取pkcs8数据包失败
extern const int SEC_P12INFO_GETPRIKEYFROMP8ERR;			//p12获取pkcs8包中的密钥失败
extern const int SEC_P12INFO_GETCERTFROMP12ERR;				//p12中获取证书数据包失败
extern const int SEC_P12INFO_CERTTYPEERR;					//p12中证书数据包是非x509v3格式
extern const int SEC_P12INFO_RDCERTERR;						//证书数据包中读取证书信息失败
extern const int SEC_P12INFO_DEVICEP12NOTEXIT;				//Device.P12不存在
extern const int SEC_P12INFO_DEVICEP12CERTLISTNOTEXIT;		//解析出设备P12中的证书链为空
extern const int SEC_P12INFO_DEVICEP12LEAFCERTNOTEXIT;		//解析出设备P12中的叶子证书为空
extern const int SEC_P12INFO_DEVICEP12PRIVATEKEYNOTEXIT;	//解析出设备P12中的私钥为空
extern const int SEC_P12INFO_USERP12NOTEXIT;				//user.P12不存在,文件名为空
extern const int SEC_P12INFO_USERP12CERTLISTNOTEXIT;		//解析出用户P12中的证书链为空
extern const int SEC_P12INFO_USERP12LEAFCERTNOTEXIT;		//解析出用户P12中的叶子证书为空
extern const int SEC_P12INFO_USERP12PRIVATEKEYNOTEXIT;		//解析出用户P12中的私钥为空
extern const int SEC_P12INFO_TRUSTCAP12NOTEXIT;				//trustca.P12不存在,文件名为空
extern const int SEC_P12INFO_TRUSTCAP12CERTLISTNOTEXIT;		//解析出trustcaP12中的证书链为空
extern const int SEC_P12INFO_TRUSTCAP12LEAFCERTNOTEXIT;		//解析出trustcaP12中的叶子证书为空
extern const int SEC_P12INFO_PARSERP12ERR; 					//解析p12错误
extern const int SEC_P12INFO_PARSERP12NOTEXISTCALIST; 		//解析p12后得到的证书链为空
//======================================================//

//=======Tls通信========================================//
//tls通信客户端
extern const int TLS_CLIENT_INITTRANTYPEERR;				//初始化tls通信方式失败
extern const int TLS_CLIENT_INITTRANINFOERR;				//初始化tls通信配置信息失败
extern const int TLS_CLIENT_INITTRANCERTERR;				//初始化tls通信使用的实体证书失败
extern const int TLS_CLIENT_CERTPRIKEYNOTPAIR;				//tls通信的证书与私钥不匹配
extern const int TLS_CLIENT_NOTINITPRIKEY;					//未初始化tls通信使用的密钥
extern const int TLS_CLIENT_CREATSOCKETHANDLEERR;			//创建socket句柄失败
extern const int TLS_CLIENT_SOCKETCONNETFALED;				//socket链接服务器端失败
extern const int TLS_CLIENT_TLSCONNECTFAILED;				//tls CONNECT失败
extern const int TLS_CLIENT_SETSOCKETHANDLETOTLSFAILED;		//设置socket句柄到tls连接句柄中失败
extern const int TLS_CLIENT_SETOVERTIMEERR;					//设置超时时间失败
extern const int TLS_CLIENT_RDERR;							//tls读取数据失败
extern const int TLS_CLIENT_WRERR;							//tls写数据失败
extern const int TLS_CLIENT_CLOSESOCKETERR;					//关闭sockethandle失败
extern const int TLS_CLIENT_INITPRIKEYERR;					//初始化私钥失败
extern const int TLS_CLIENT_ADDCERTTOSTOREERR;				//添加证书到x509store失败
extern const int TLS_CLIENT_TIMEOUT;                    	//TLS超时add by huweihua  
extern const int TLS_CLIENT_INITCIPHERERR;              	//初始化TLS通信密钥算法失败add by huweihua
extern const int TLS_CLIENT_CLOSED;                     	//TLS连接已关闭add by huweihua   
extern const int TLS_CLIENT_SERVERCALISTNOTEXIST;       	//服务器端证书链不存在add by huweihua
extern const int TLS_CLIENT_LOCALCERTNOTEXIST;          	//客户端证书不存在add by huweihua
extern const int TLS_CLIENT_PRIVATEKEYNOTEXIST;         	//客户端私钥不存在add by huweihua
extern const int TLS_CLIENT_P12PASSWORDNOTEXIST;        	//p12文件密码不存在add by huweihua

//tls服务器端
extern const int TLS_SERVER_GETSOCKHANDLEERR;				//从tls通信句柄中读取socket句柄失败
extern const int TLS_SERVER_SOCKACCEPTERR;					//socket accept失败
extern const int TLS_SERVER_TLSACCEPTERR;					//tls accept失败
extern const int TLS_SERVER_SOCKBINDERR;					//tls bind失败
extern const int TLS_SERVER_LISTENERR;						//tls bind失败
extern const int TLS_SERVER_HANDSHACKERR;					//tls 握手失败
extern const int TLS_SERVER_INITPRIKEYERR;					//初始化私钥失败
extern const int TLS_SERVER_ADDCERTTOSTOREERR;				//添加证书到x509store失败
extern const int TLS_SERVER_INITTRANTYPEERR;				//初始化tls通信方式失败
extern const int TLS_SERVER_INITTRANINFOERR;				//初始化tls通信配置信息失败
extern const int TLS_SERVER_INITTRANCERTERR;				//初始化tls通信使用的实体证书失败
extern const int TLS_SERVER_CERTPRIKEYNOTPAIR;				//tls通信的证书与私钥不匹配
extern const int TLS_SERVER_NOTINITPRIKEY;					//未初始化tls通信使用的密钥
extern const int TLS_SERVER_CREATSOCKETHANDLEERR;			//创建socket句柄失败
extern const int TLS_SERVER_SOCKETCONNETFALED;				//socket链接服务器端失败
extern const int TLS_SERVER_TLSACCEPTFAILED;				//tls ACCEPT失败
extern const int TLS_SERVER_SETSOCKETHANDLETOTLSFAILED;		//设置socket句柄到tls连接句柄中失败
extern const int TLS_SERVER_SETOVERTIMEERR;					//设置超时时间失败
extern const int TLS_SERVER_RDERR;							//tls读取数据失败
extern const int TLS_SERVER_WRERR;							//tls写数据失败
extern const int TLS_SERVER_CLOSESOCKETERR;					//关闭sockethandle失败
extern const int TLS_SERVER_TIMEOUT;						//TLS超时到add by huweihua
extern const int TLS_SERVER_INITCIPHERERR;					//初始化TLS通信密钥算法失败add by huweihua
extern const int TLS_SERVER_CLOSED;                     	//TLS连接已关闭add by huweihua   
extern const int TLS_SERVER_CLIENTCALISTNOTEXIST;       	//客户端证书链不存在 add by huweihua
extern const int TLS_SERVER_LOCALCERTNOTEXIST;          	//服务器证书不存在 add by huweihua
extern const int TLS_SERVER_PRIVATEKEYNOTEXIST;         	//服务器私钥不存在 add by huweihua
//======================================================//

//==========xml解析模块==================================//
extern const int XML_XML_DATAEMPTY;							//加载的XML数据为空
extern const int XML_XML_DATAWRONGFORMAT;					//加载的XML数据格式错误
extern const int XML_XML_LOADDATAERR;						//未加载XML数据或加载XML数据格式错误
extern const int XML_XML_ADDNODENODEPATHERR;				//添加节点的节点路径为空（如果为空，则默认添加到二级节点）
extern const int XML_XML_ADDNODEPATHERR;					//添加的节点路径（包含节点名）为空
extern const int XML_XML_FINDNODEPATHERR;					//添加的节点路径（包含节点名）找不到
extern const int XML_XML_NODENAMENOTEXIT;					//添加的节点名（不包含路径）不存在
extern const int XML_XML_XMLDATAEMPTY;						//添加的XML数据为空
extern const int XML_XML_ADDXMLDATAERR;						//添加的XML数据格式错误
extern const int XML_XML_ADDNODEERR;						//添加节点失败
extern const int XML_XML_DELNODEPATHEMPTY;					//删除的节点路径（包含节点名）为空
extern const int XML_XML_DELNODEPATHNOTEXIT;				//删除的节点路径（包含节点名）不存在
extern const int XML_XML_DELNODENOTEXIT;					//删除的节点名（不包含路径）不存在
extern const int XML_XML_FINDXMLDATAERR;					//查找节点XML数据失败
extern const int XML_XML_DELNODEFAIL;						//删除节点失败
extern const int XML_XML_MODIFYNODEPATHEMPTY;				//修改的节点路径（包含节点名）为空
extern const int XML_XML_MODIFYNODEPATHNOTXEIXT;			//修改的节点路径（包含节点名）不存在
extern const int XML_XML_MODIFYNODENAMENOTEXIT;				//修改的节点名（不包含路径）不存在
extern const int XML_XML_MODIFYNODEERR;						//修改节点失败
extern const int XML_XML_FINDNODEPATHEMPTY;					//查找的节点路径（包含节点名）为空
extern const int XML_XML_FINDNODENAMENOTEXIT;				//查找的节点名（不包含路径）不存在
extern const int XML_XML_FINDNODEPATHNOTEXIT;				//查找的节点路径（包含节点名）不存在
extern const int XML_XML_FINDNOTFAIL;						//查找节点失败
extern const int XML_XML_STOREXMLDATAEMPTY;					//要保存的XML数据为空
extern const int XML_XML_STOREXMLDATAFAIL;					//保存XML数据失败
extern const int XML_XML_TEMPLATEINITERR;					//模板初始化失败
extern const int XML_XML_TEMPLATEPARSEERR;					//模板解析失败
extern const int XML_XML_INITSENDMESSAGEFAIL;				//消息初始化发送消息失败
extern const int XML_XML_INITPARSEMESSAGEFAIL;				//消息初始化解析消息失败

extern const int XML_MSG_GETDIGESTMETHODERR;  				//获取摘要方法错误
extern const int XML_MSG_GETSIGMETHODERR;     				//获取签名算法错误
extern const int XML_MSG_DIGESTVERIFYERR;     				//摘要验证失败
extern const int XML_MSG_SIGNVERIFYERR;       				//签名验证失败
extern const int XML_MSG_GETGENKEYMETHODERR;				//获取生成密钥算法错误
extern const int XML_MSG_GETENCKEYMETHODERR;  				//获取对密钥进行加密的算法错误
extern const int XML_MSG_GETDEVICETYPEERR;					//获取设备类型错误
extern const int XML_MSG_GETKEYLENERR;		    			//获取密钥长度错误(密钥请求类)
//======================================================//

//=========tcp/ip 通信模块==============================//
extern const int TRAN_SOCK_CONNECTERR;						//连接失败
extern const int TRAN_SOCK_HANDLEERR;						//链路未建立
extern const int TRAN_SOCK_SENDDATAERR;						//发送数据失败
extern const int TRAN_SOCK_BUFEMPTY;						//发送数据为空
extern const int TRAN_SOCK_RECVDATAERR;						//接收数据失败
extern const int TRAN_SOCK_RECVDATAWRONG;					//没有需要接收的数据
//======================================================//

//==========报头模块====================================//
extern const int HEAD_HTTP_ADDERR;							//添加报头错
extern const int HEAD_HTTP_SESSIONERR;						//报头中没有session或session非法
extern const int HEAD_HTTP_LENGTHERR;						//报头长度错
extern const int HEAD_HTTP_LENGTHEMPTY;						//报头中没有内容长度或长度为0
extern const int HEAD_HTTP_NOHAVEHEADDATA;					//没有报头数据
//======================================================//

//======================内容管理模块====================//
extern const int CON_MANAGE_SETHEADERR;             		//生成内容头失败
extern const int CON_MANAGE_GETHEADERR;             		//获取内容头失败
extern const int CON_MANAGE_KEYRGISTRSPMSGTYPERR;   		//密钥注册响应消息类型错误
extern const int CON_MANAGE_KEYGENERRSPMSGTYPERR;   		//密钥请求响应消息类型错误
extern const int CON_MANAGE_GETSERVERKEYERR;        		//获取服务器生成的密钥失败
extern const int CON_MANAGE_GETSERVERINSDOIERR;     		//获取服务器生成的InstanceDOI失败
extern const int CON_MANAGE_GETSERVERMASDOIERR;     		//获取服务器生成的MasterDOI失败
extern const int CON_MANAGE_CONDIGINSMSGTYPERR;     		//内容实例注册响应消息类型错误
extern const int CON_MANAGE_CONASSIDFMSGTYPERR;     		//新内容实例响应消息类型错误
extern const int CON_MANAGE_GENERATEKEYERR;         		//生成密钥失败
extern const int CON_MANAGE_GENERATEKEYIDERR;       		//生成密钥ID失败
//======================================================//

//==========设备管理模块================================//
extern const int DEVICE_MANAGE_GETTYPEERR;         			//获取设备类型失败
extern const int DEVICE_MANAGE_GENDEVICEIDERR;     			//生成设备ID错误
extern const int DEVICE_MANAGE_GETDEVICEINFOERR;   			//获取设备信息失败
extern const int DEVICE_MANAGE_SETDEVICEREQERR;    			//设置注册设备请求信息失败
extern const int DEVICE_MANAGE_RESPONSEMSGTYPERR;  			//响应的消息类型错误
extern const int DEVICE_MANAGE_GETP12PATHERR;      			//获取p12文件名错误
//======================================================//

//==========SM设备管理模块==============================//
extern const int SM_DEVICE_MANAGE_ADDDEVICEERR;       		//添加设备失败
extern const int SM_DEVICE_MANAGE_DELETEDEVICEERR;    		//删除设备ID错误
extern const int SM_DEVICE_MANAGE_GETDEVICEINFOERR;   		//获取设备信息失败
//======================================================//

//==========SM证书管理模块==============================//
extern const int SM_CERT_MANAGE_IMPORTCERTERR;   			//导入证书失败
extern const int SM_CERT_MANAGE_DESTORYCERTERR;  			//销毁证书失败
extern const int SM_CERT_MANAGE_VERIFYCERTERR;   			//验证证书失败
extern const int SM_CERT_MANAGE_EXPORTCERTISNONE;   		//要导出的证书不存在 //add by yin 2010.10.11
extern const int SM_CERT_MANAGE_DESTROYCERTISNONE;   		//要删除的证书不存在 //add by yin 2010.10.11
//======================================================//

//==========KDM解析模块=================================//
extern const int SM_KDMPARSER_LOADETMSCHEMAERR;       		//加载etm的schema失败
extern const int SM_KDMPARSER_LOADKDMSCHEMAERR;       		//加载KDM的schema失败
extern const int SM_KDMPARSER_KDMFORMATERR;           		//KDM格式验证失败
extern const int SM_KDMPARSER_GETCERTCHAINERR;   		  	//获取KDM证书链失败
extern const int SM_KDMPARSER_LOADCERTCHAINERR;   			//加载KDM证书链失败
extern const int SM_KDMPARSER_VERIFYCERTFORMATERR;    		//KDM证书链中的证书格式验证失败
extern const int SM_KDMPARSER_VERIFYCERTCHAINERR;   		//KDM验证证书链失败
extern const int SM_KDMPARSER_GETISSUEDATEERR;   			//获取KDM发行时间失败
extern const int SM_KDMPARSER_GETCERTVALIDITYTIMEERR; 		//获取证书有效时间失败
extern const int SM_KDMPARSER_GETVALIDITYTIMEERR;   		//获取KDM有效时间失败
extern const int SM_KDMPARSER_ISSUEDATEERR;   				//KDM发行时间不在证书的有效性之内
extern const int SM_KDMPARSER_VALIDITYTIMEERR;   			//KDM有效时间不在证书的有效性之内
extern const int SM_KDMPARSER_NOTINVALIDITYTIMEERR;   		//当前时间不在KDM有效时间之内
extern const int SM_KDMPARSER_VERIFYSIGNATUREERR;   		//KDM签名验证失败
extern const int SM_KDMPARSER_VERIFYTDLERR;   				//TDL验证失败
extern const int SM_KDMPARSER_NODEEXISTERR;   				//KDM节点存在性错误
extern const int SM_KDMPARSER_NODEVALUEERR;   				//KDM节点值错误
extern const int SM_KDMPARSER_NODEATTRIBUTEERR;   			//KDM节点属性值错误
extern const int SM_KDMPARSER_DECNODEVALUEERR;   			//KDM解密后明文内容值错误
extern const int SM_KDMPARSER_GETCONTENTKEYERR;   			//获取内容密钥失败
extern const int SM_KDMPARSER_GETCPLIDERR;   				//获取CPLId失败
extern const int SM_KDMPARSER_GETSIGNERTHUMBPRINTERR; 		//获取签名证书指纹失败
extern const int SM_KDMPARSER_GETKDMIDERR;            		//获取KDMId失败
extern const int SM_KDMPARSER_KEYIDMATCHERR;          		//CPL中的KeyId和KDM中的KeyId匹配失败
extern const int SM_KDMPARSER_KEYIDEXISTERR;          		//KDM中的KeyIdList下的KeyId节点不存在
//======================================================//

//==========CPL验证模块=================================//
extern const int SM_CPLVERIFY_LOADCPLSCHEMAERR;   			//加载CPL的schema失败
extern const int SM_CPLVERIFY_FORMATERR;          			//CPL格式验证失败
extern const int SM_CPLVERIFY_CONTENTERR;   		  		//CPL内容验证失败
extern const int SM_CPLVERIFY_VERIFYSIGNATUREERR; 			//CPL签名验证失败
extern const int SM_CPLVERIFY_VERIFYCERTFORMATERR;			//CPL证书格式验证失败
extern const int SM_CPLVERIFY_MISSINGSIGNATRUEERR;			//CPL签名不存在
extern const int SM_CPLVERIFY_GETCPLIDERR;          		//获取CPLId失败
extern const int SM_CPLVERIFY_GETTRACKFILEIDERR;    		//获取轨迹文件ID失败
extern const int SM_CPLVERIFY_GETKEYIDERR;          		//获取KeyId失败
//======================================================//

//==========PKL验证模块=================================//
extern const int SM_PKLVERIFY_LOADCPLSCHEMAERR;   			//加载PKL的schema失败
extern const int SM_PKLVERIFY_FORMATERR;          			//PKL格式失败
extern const int SM_PKLVERIFY_ASSETMAPPARSERERR;  			//xml解析ASSETMAP文件失败
extern const int SM_PKLVERIFY_CONTENTERR;   		  		//PKL内容验证失败
extern const int SM_PKLVERIFY_VERIFYSIGNATUREERR; 			//PKL签名验证失败  
extern const int SM_PKLVERIFY_UUIDFORMATERR; 				//uuid格式验证失败[RFC-4122]
//======================================================//

//==========SECURITYENVIROMENT模块======================//
extern const int SM_SECENV_GETCSPINFOERR;					//获取cspinfo失败
extern const int SM_SECENV_GETPRIVATEKEYERR;				//获取私钥失败
extern const int SM_SECENV_GETLEAFCERTERR;					//获取叶子证书失败
extern const int SM_SECENV_GETCERTCHAINERR;					//获取证书链失败
extern const int SM_SECENV_GETHASHOFCERTCHAINERR;			//计算证书文件的hash值失败
extern const int SM_SECENV_CMPHASHOFCERTCHAINERR;			//比较计算出证书文件的hash值与预存储的hash不符
extern const int SM_SECENV_CHECKKEYPAIRERR;      			//设备证书与私钥不匹配
extern const int SM_SECENV_GETUSERLEAFCERTERR;   			//获取用户证书失败 add by yin 2011.8.25
extern const int SM_SECENV_GETOFFICERLEAFCERTERR; 			//获取安全官证书失败 add by yin 2011.8.25
//======================================================//

//==========公用错误码==================================//
extern const int SM_DMP_OPENERR;  							//安全存储区没有打开
//======================================================//

//===============CSP管理================================//
extern const int CSP_MANAGE_DMP_OPENERR;  					//安全存储区没有打开
extern const int CSP_MANAGE_DMP_SET_CSPS_ENCKEYERR; 		//安全存储区设置csps_enckey返回失败
extern const int CSP_MANAGE_DMP_GET_CSPS_ENCKEYERR; 		//安全存储区获取csps_enckey返回失败
extern const int CSP_MANAGE_DMP_SET_CSPS_RANDSEEDERR; 		//安全存储区设置csps_randseed返回失败
extern const int CSP_MANAGE_DMP_GET_CSPS_RANDSEEDERR;		//安全存储区获取csps_randseed返回失败
extern const int CSP_MANAGE_DMP_SET_CSPS_DEVICEPRIKEYERR;	//安全存储区设置csps_deviceprikey返回失败
extern const int CSP_MANAGE_DMP_GET_CSPS_DEVICEPRIKEYERR;	//安全存储区获取csps_deviceprikey返回失败
extern const int CSP_MANAGE_DMP_SET_CSPS_SEEDKEYERR;		//安全存储区设置csps_seedkey返回失败
extern const int CSP_MANAGE_DMP_GET_CSPS_SEEDKEYERR;		//安全存储区获取csps_seedkey返回失败
extern const int CSP_MANAGE_DMP_SET_CSPS_IVERR;				//安全存储区设置csps_iv返回失败
extern const int CSP_MANAGE_DMP_GET_CSPS_IVERR;				//安全存储区获取csps_iv返回失败
extern const int CSP_MANAGE_DMP_SET_CSPS_HMACKEYERR;		//安全存储区设置csps_hmackey返回失败
extern const int CSP_MANAGE_DMP_GET_CSPS_HMACKEYERR;		//安全存储区获得csps_hmackey返回失败
extern const int CSP_MANAGE_DMP_SET_CSPS_HMACVALUEERR;		//安全存储区设置csps_hmacvalue返回失败
extern const int CSP_MANAGE_DMP_GET_CSPS_HMACVALUEERR;		//安全存储区获得csps_hmacvalue返回失败
extern const int CSP_MANAGE_DMP_SET_CSPS_FIRMWAREKEYERR;	//安全存储区设置csps_firmwarekey返回失败
extern const int CSP_MANAGE_DMP_GET_CSPS_FIRMWAREKEYERR;	//安全存储区获得csps_firmwarekey返回失败
extern const int CSP_MANAGE_DMP_SET_CSPS_TIMEVALUEERR;		//安全存储区设置csps_timevalue返回失败
extern const int CSP_MANAGE_DMP_GET_CSPS_TIMEVALUEERR;		//安全存储区获取csps_timevalue返回失败
extern const int CSP_MANAGE_DMP_SET_CSPS_KEKERR;			//安全存储区设置csps_kek返回失败
extern const int CSP_MANAGE_DMP_GET_CSPS_KEKERR;			//安全存储区获得csps_kek返回失败
extern const int CSP_MANAGE_CSPS_CLEARALLCSPSERR;			//清空所有csps返回失败
extern const int CSP_MANAGE_CSPS_SETALLCSPSERR;				//设置所有csps返回失败
extern const int CSP_MANAGE_CSPS_RESETCSPSERR;				//重置所有csps返回失败	
extern const int CSP_MANAGE_CSPS_SETCSPSERR;				//设置csps返回失败
extern const int CSP_MANAGE_CSPS_GETCSPSERR;				//获得所有csps返回失败
//add by yin 2010.10.11
extern const int CSP_MANAGE_SMCERTFILE_NOEXSIT;				//SM证书文件不存在
extern const int CSP_MANAGE_SMCAFILE_NOEXSIT;				//SM CA证书文件不存在
extern const int CSP_MANAGE_SMSCAFILE_NOEXSIT;				//SMS CA证书文件不存在
extern const int CSP_MANAGE_PROJECTCAFILE_NOEXSIT;			//PROJECT CA证书文件不存在
extern const int CSP_MANAGE_ALLCERTFILE_NOEXSIT;			//系统中不存在任何证书文件
//add by yin 2011.8.25
extern const int CSP_MANAGE_USERCERTFILE_NOEXSIT;           //普通用户证书文件不存在
extern const int CSP_MANAGE_OFFICERCERTFILE_NOEXSIT;       	//安全官证书文件不存在
extern const int CSP_MANAGE_USERCAFILE_NOEXSIT;            	//普通用户证书链文件不存在
extern const int CSP_MANAGE_OFFICERCAFILE_NOEXSIT;          //安全官证书链文件不存在
//add by yin 2011.9.9
extern const int CSP_MANAGE_PARSERCSPVALUE_LENISZERO;       //解析从硬件中获得CSP值的实际长度为0
//======================================================//

//===============KEY管理================================//
extern const int KEY_MANAGE_DMP_OPENERR;					//安全存储区没有打开
extern const int KEY_MANAGE_GENERATERAND_ERR;				//生成随机数失败
extern const int KEY_MANAGE_GENERATEKEK_ERR;				//生成内容加密密钥失败
extern const int KEY_MANAGE_GENERATELEKEYID_ERR;			//生成LE keyID失败
extern const int KEY_MANAGE_GENERATELEKEYDATA_ERR;			//生成LE keydata失败
extern const int KEY_MANAGE_GENERATELEKEYATTRIDATA_ERR;		//生成LE keyattridata失败
extern const int KEY_MANAGE_GENERATECONTENTKEY_ERR;			//生成内容密钥失败
extern const int KEY_MANAGE_GENERATECONTENTKEYNULL_ERR;		//无内容密钥
extern const int KEY_MANAGE_DMP_SET_CEKERR;					//向硬件存储内容密钥失败
extern const int KEY_MANAGE_GENERATELEKEYNULL_ERR;			//无LE密钥
extern const int KEY_MANAGE_DMP_SET_CINELINKKEYERR;			//向硬件存储cinelink key失败
extern const int KEY_MANAGE_LOADLDKEY_ERR;					//加载LDkey失败
extern const int KEY_MANAGE_DMP_CLEARCEKERR;				//清除硬件存储中的内容密钥失败
extern const int KEY_MANAGE_DMP_CLEARCINELINKKEYERR;		//清除硬件存储中的链路密钥失败
extern const int KEY_MANAGE_SETCINELINKENABLEERR;      		//设置打开链路加密功能失败   //add by yin 2011.8.25 start 
extern const int KEY_MANAGE_SETCINELINKDISABLEERR;      	//设置关闭链路加密功能失败
extern const int KEY_MANAGE_SETFORENSICMARKINGINFERR;   	//设置水印信息失败
extern const int KEY_MANAGE_SETFORENSICMARKINGKEYERR;   	//设置水印密钥失败
extern const int KEY_MANAGE_SETFORENSICMARKINGENABLEERR;    //设置打开水印功能失败
extern const int KEY_MANAGE_SETFORENSICMARKINGDISABLEERR;   //设置关闭水印功能失败 //add by yin 2011.8.25 end
//======================================================//

//===============身份认证===============================//
//extern const int Authentication_DMP_OPENERR;				//身份认证模块安全存储区没有打开
extern const int AUTHENTICATION_NOTHEUSERERR;				//身份认证模块没有此用户
extern const int AUTHENTICATION_PASSWORDERR;				//身份认证模块密码错误
extern const int AUTHENTICATION_RIGHTOFREPONSEISNULLERR;	//身份认证响应中没有权限信息
extern const int AUTHENTICATION_DMP_GETUSERINFOERR;			//从硬件存储中获得用户信息失败
extern const int AUTHENTICATION_X509CERT_SIGNERR;			//对身份认证请求消息签名失败
//======================================================//

class CDrmError
{
	
public:
	CDrmError();
	virtual ~CDrmError();
	
	int GetErrorNumber() const; 			//获取错误码
	int SetErrorNumber(int ErrorNumber); 	//设置错误码
	
private:
	vector<int> m_Error;					//错误码
	
};

extern CDrmError pubError;	

#endif
