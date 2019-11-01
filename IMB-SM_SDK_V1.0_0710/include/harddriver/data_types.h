#ifndef _DATA_TYPES_H_
#define _DATA_TYPES_H_

/// ������Կ��Ϣ�ṹ��
struct content_key 
{
	unsigned char keyType[4];	//��Կ���ͣ�MDIK(ͼ����Կ),MDAK(��Ƶ��Կ),MDSK(��Ļ��Կ),FMIK(ͼ��ˮӡ��Կ),FMAK(��Ƶˮӡ��Կ)
	unsigned char keyID[16];	//��ԿID
	unsigned char keyData[16];	//��Կֵ
	unsigned char trackfileID[16];	//�켣�ļ�ID  
	unsigned char HMACkeyData[16];	//HMACkeyֵ
};

/// ˮӡ������Ϣ�ṹ��
struct forensic_data
{
	union
	{
		unsigned char wm_info[5]; 
		unsigned char wm_key[16];
	}u;	
};

#endif