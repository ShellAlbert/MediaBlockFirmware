#ifndef _MBFT_FTDMN_H_
#define _MBFT_FTDMN_H_
//	mbft/ftdmn.h
//	2010-09-19 by Shan Lanshan
#include "common/replant.h"
#include <string.h>


class Ftdmn: public event::rp::Thread {
public:
	Ftdmn() {m_path[0] = '\0';};
	void setPath(const char *path) {strcpy(m_path, path);};
protected:
	virtual void *workFunc();
private:
	char m_path[256];
};


#endif // !_MBFT_FTDMN_H_
