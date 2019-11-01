#ifndef _UDPFT_BITTBL_H_
#define _UDPFT_BITTBL_H_
//	udpft/bittbl.h
//	2010-09-13 by ShanLanshan

class Bittbl 
{
public:
	static const int 
		transfered = 1,
		untransfered = 0,
		sended = 2,
		stateCount = 3;
public:
	Bittbl();
	~Bittbl();
	void setSize(int size);
	int getSize() const;
	void setBit(int idx, char c = transfered);
	char getBit(int idx);
	int getPos(int beginIdx, char c = untransfered);
	int cacuCount(int beginIdx, char c = untransfered);
	void setData(char *data, int len);
private:
	int m_size;
	char *m_bmp;
};

#endif // !_UDPFT_BITTBL_H_
