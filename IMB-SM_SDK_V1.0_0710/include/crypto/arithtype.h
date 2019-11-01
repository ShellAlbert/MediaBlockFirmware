#ifndef _ARITHTYPE_H_
#define _ARITHTYPE_H_

/*---------------------------------�㷨ID����---------------------------*/
/*hash�㷨*/
extern const unsigned short SHA1_Hash_Algorithm;      //SHA-1�㷨
extern const unsigned short SHA256_Hash_Algorithm;   //SHA-256�㷨

/*�ǶԳƼӽ����㷨*/
extern const unsigned short RSA_PublicKey_Encrypt;    //RSA��Կ����
extern const unsigned short RSA_PrivateKey_Decrypt;   //RSA˽Կ����

/*�ԳƼӽ����㷨*/
extern const unsigned short AES_CFB_Encrypt_128_128;  //AES128λ��ԿCFBģʽ����
extern const unsigned short AES_CFB_Decrypt_128_128;  //AES128λ��ԿCFBģʽ����

/*Ԥ��
extern const unsigned short AES_CFB_Encrypt_128_192;  //AES192λ��ԿCFBģʽ����
extern const unsigned short AES_CFB_Decrypt_128_192;  //AES192λ��ԿCFBģʽ����
extern const unsigned short AES_CFB_Encrypt_128_256;  //AES256λ��ԿCFBģʽ����
extern const unsigned short AES_CFB_Decrypt_128_256;  //AES256λ��ԿCFBģʽ����
Ԥ��*/

/*ǩ������֤�㷨*/

extern const unsigned short RSA_Sign_With_SHA1;        //SHA1��ϣֵ��RSAǩ��
extern const unsigned short RSA_Sign_With_SHA256;      //SHA256��ϣֵ��RSAǩ����add by xiaozhengxiu 20100423

extern const unsigned short RSA_Verify_With_SHA1;      //SHA1��ϣֵ��RSA��֤
extern const unsigned short RSA_Verify_With_SHA256;    //SHA256��ϣֵ��RSA��֤,add by zhangliang 2009.11.24

/*Base64����ͽ���*/
extern const unsigned short Base64_Encrypt;            //Base64����
extern const unsigned short Base64_Decrypt;            //Base64����

#endif
