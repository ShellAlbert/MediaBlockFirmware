#ifndef _DATA_TYPES_H_
#define _DATA_TYPES_H_

/// 内容密钥信息结构体
struct content_key 
{
	unsigned char keyType[4];	//密钥类型：MDIK(图像密钥),MDAK(音频密钥),MDSK(字幕密钥),FMIK(图像水印密钥),FMAK(音频水印密钥)
	unsigned char keyID[16];	//密钥ID
	unsigned char keyData[16];	//密钥值
	unsigned char trackfileID[16];	//轨迹文件ID  
	unsigned char HMACkeyData[16];	//HMACkey值
};

/// 水印加密信息结构体
struct forensic_data
{
	union
	{
		unsigned char wm_info[5]; 
		unsigned char wm_key[16];
	}u;	
};

#endif