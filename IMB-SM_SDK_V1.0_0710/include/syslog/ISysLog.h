/********************************************* 
Copyright (C), 2010-2020, DADI MEDIA Co., Ltd.
ModuleName:  SysLog
FileName�� ISysLog.h
Author�� wuxuewen@dadimedia.com
Date�� 2010/06/10
Version�� v1.0
Description�� 
Others:  
History�� 
      < Author >    			< Date >             < Modification >
********************************************/ 

#ifndef __ISYSLOG_H__
#define __ISYSLOG_H__

// Log level 
#define LOG_DEB 0				
#define LOG_INF 1				
#define LOG_WAR 2
#define LOG_ERR 3
#define LOG_FAT 4
#define LOG_ALL	5

#define LOG_SAVE_PATH         "../syslog"   //add by huweihua

int InitSysLog(void);

class ISysLog
{
public:
	ISysLog(void){};
	virtual ~ISysLog(void){};
	//modify  by huweihua, add parameter 'filepath'
	virtual int Initialize(unsigned level, const char *filepath, const char *filename) = 0; //��ʼ����־ϵͳ(��־�������־�ļ���)
	virtual void logdebug(const char *fmt) = 0;		// ���������־��Ϣ
	virtual void loginfo(const char *fmt) = 0;		// ���һ����־��Ϣ
	virtual void logwarn(const char *fmt) = 0;		// ���������־��Ϣ
	virtual void logerror(const char *fmt) = 0;		// ���������־��Ϣ
	virtual void logfatal(const char *fmt) = 0;		// ������ش�����־��Ϣ

protected:
private:
};
#endif
