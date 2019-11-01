#ifndef _COMMON_REPLANT_H_
#define _COMMON_REPLANT_H_
//
//	2010-03-02 ����ɽ
//	�����ƽ̨��ֲ�йصĹ���
//	���磺�̡߳�������ʱ���
//

#include <pthread.h>
#include <unistd.h>
#include <time.h>

#ifdef __cplusplus
extern "C"
{
#endif

//BEGIN_EVENT_NAMESPACE
namespace event {

namespace rp {

extern long get_microsec(long inc = 0);

//	caculate microsecond from t1 to t2
//	if t1 is bigger, return -num
extern long diff_microsec(long t1, long t2);

extern const char *get_module_filename();

//	ʱ����
class Datetime 
{
public:
	int year;	//	�꣬��2005�꼴Ϊ2005
	int month;	//	�£���12�¼�Ϊ12
	int day;	//	�գ������е���������25�ż�Ϊ25
	int week;	//	���ڼ���0-��������������
	int hour;
	int minute;
	int second;
	int usecond;	//	΢����
	time_t t;
	int daysec;
public:
	void now();		//	ȡ����ʱ��
	long long operator-(Datetime &dt);
};

class Lock 
{
public:
	Lock();
	~Lock();
	bool lock();
	void unlock();
private:
	pthread_mutex_t m_mutex;

public:
	class Key 
	{
public:
		Key(Lock *lk): m_lock(lk), m_open(false) {};
		~Key() {close(); };
		bool open() 
		{
			if (!m_lock)
				return false;
			if (m_open)
				return true;
			if (m_lock->lock()) 
			{
				m_open = true;
				return true;
			};
			return false;
		};
		void close() 
		{
			if (!m_lock)
				return;
			if (!m_open)
				return;
			m_lock->unlock();
			m_open = false;
		};
private:
		bool m_open;
		Lock *m_lock;
	};
};

/*
class Wait 
{
public:
	Wait();
	~Wait();
	void notify();
	bool wait(int us);
	bool lock();
	void unlock();
protected:
	pthread_mutex_t m_mutex;
	pthread_cond_t m_cond;
private:
	bool _wait(int us);
};
*/

class Thread 
{
public:
	Thread();
	~Thread();
	bool start();
	void stop();
	void notifyStop() {m_stopSig = true;};
	static void *_workFunc(void *arg);
	virtual void *workFunc();
protected:
	bool m_started;
	bool m_stopSig;
	pthread_t m_tid;
};

/*
class CondThread: public Thread 
{
public:
	CondThread();
	~CondThread();

	bool start();
	void stop();
	void wait(int us = -1);
	bool trylock();
	bool lock(int ms = -1);
	void unlock();
	void wake();
	virtual void *workFunc();
protected:
	pthread_mutex_t m_mutex;
	pthread_cond_t m_cond;
	bool m_locked;
};
*/

}	//namespace rp

}	//namespace event
//END_EVENT_NAMESPACE

#ifdef __cplusplus
}
#endif

#endif // !_COMMON_REPLANT_H_
