#ifndef _MANAGE_MSP430_STATUS_H_
#define _MANAGE_MSP430_STATUS_H_

/// XLQ:msp430的个数
//#define MSP430_MAX_NUM 2

class Manage_MSP430_Status
{
public:
    Manage_MSP430_Status();
    ~Manage_MSP430_Status();


    /// XLQ:获得微动开关的状态，1字节
    int set_msp430_status(unsigned char *pstatus, 
        unsigned int status_len);
    int get_msp430_status(unsigned char *pstatus, 
        unsigned int status_len,
        unsigned int *pstatus_len);

    /// XLQ:40
    int set_csps_hmackey(unsigned char *phmackey, 
        unsigned int hmackey_len);
    int get_csps_hmackey(unsigned char *phmackey, 
        unsigned int hmackey_len, 
        unsigned int *phmackey_len);

    /// XLQ:32
    int set_csps_hmacvalue(unsigned char *phmacvalue, 
        unsigned int hmacvalue_len);
    int get_csps_hmacvalue(unsigned char *phmacvalue, 
        unsigned int hmacvalue_len, 
        unsigned int *phmacvalue_len);

    /// XLQ:2048
    int set_csps_deviceprikey(unsigned char *pdevp12, 
        unsigned int devp12_len);
    int get_csps_deviceprikey(unsigned char *pdevp12, 
        unsigned int devp12_len, 
        unsigned int *pdevp12_len);

    /// XLQ:40
    int set_csps_randseed(unsigned char *prandseed, 
        unsigned int randseed_len);
    int get_csps_randseed(unsigned char *prandseed, 
        unsigned int randseed_len, 
        unsigned int *prandseed_len);

    /// XLQ:40
    int set_csps_seedkey(unsigned char *pseedkey, 
        unsigned int seedkey_len);
    int get_csps_seedkey(unsigned char *pseedkey, 
        unsigned int seedkey_len, 
        unsigned int *pseedkey_len);

    /// XLQ:24
    int set_csps_firmwarekey(unsigned char *pfirmwarekey, 
        unsigned int firmwarekey_len);
    int get_csps_firmwarekey(unsigned char *pfirmwarekey, 
        unsigned int firmwarekey_len, 
        unsigned int *pfirmwarekey_len);

    /// XLQ:96
    int set_userinfo(unsigned char *puserinfo, 
        unsigned int userinfo_len);
    int get_userinfo(unsigned char *puserinfo, 
        unsigned int userinfo_len,
        unsigned int *puserinfo_len);

    /// 2320
    int set_csps(unsigned char *pcsps, 
        unsigned int csps_len);
    int get_csps(unsigned char *pcsps, 
        unsigned int csps_len, 
        unsigned int *pcsps_len);

    int clear_csps(void);

private:

    int Open_MSP430_Dev(char *devPath);
    int Close_MSP430_Dev(int fd);
    int Ioctl_MSP430_Dev(int fd, int mode);
    int Read_MSP430_Dev(int fd, unsigned char *value);
    int Write_MSP430_Dev(int fd, unsigned char value);


    int Set_MSP430_Value(unsigned char *buf_data, 
        unsigned int buf_len,
        int csps_position);
    int Get_MSP430_Value(unsigned char *buf_data, 
        unsigned int buf_len,
        unsigned int *buf_data_len,
        int csps_position);


    int msp430;
};

#endif
