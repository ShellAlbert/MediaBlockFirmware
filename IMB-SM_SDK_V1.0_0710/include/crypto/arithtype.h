#ifndef _ARITHTYPE_H_
#define _ARITHTYPE_H_

/*---------------------------------算法ID定义---------------------------*/
/*hash算法*/
extern const unsigned short SHA1_Hash_Algorithm;      //SHA-1算法
extern const unsigned short SHA256_Hash_Algorithm;   //SHA-256算法

/*非对称加解密算法*/
extern const unsigned short RSA_PublicKey_Encrypt;    //RSA公钥加密
extern const unsigned short RSA_PrivateKey_Decrypt;   //RSA私钥解密

/*对称加解密算法*/
extern const unsigned short AES_CFB_Encrypt_128_128;  //AES128位密钥CFB模式加密
extern const unsigned short AES_CFB_Decrypt_128_128;  //AES128位密钥CFB模式解密

/*预留
extern const unsigned short AES_CFB_Encrypt_128_192;  //AES192位密钥CFB模式加密
extern const unsigned short AES_CFB_Decrypt_128_192;  //AES192位密钥CFB模式解密
extern const unsigned short AES_CFB_Encrypt_128_256;  //AES256位密钥CFB模式加密
extern const unsigned short AES_CFB_Decrypt_128_256;  //AES256位密钥CFB模式解密
预留*/

/*签名和验证算法*/

extern const unsigned short RSA_Sign_With_SHA1;        //SHA1哈希值的RSA签名
extern const unsigned short RSA_Sign_With_SHA256;      //SHA256哈希值的RSA签名，add by xiaozhengxiu 20100423

extern const unsigned short RSA_Verify_With_SHA1;      //SHA1哈希值的RSA验证
extern const unsigned short RSA_Verify_With_SHA256;    //SHA256哈希值的RSA验证,add by zhangliang 2009.11.24

/*Base64编码和解码*/
extern const unsigned short Base64_Encrypt;            //Base64编码
extern const unsigned short Base64_Decrypt;            //Base64解码

#endif
