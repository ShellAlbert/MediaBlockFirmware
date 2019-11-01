#ifndef _SHOWLISTMANAGER_H_
#define _SHOWLISTMANAGER_H_

#include <string>
#include <vector>
#include <map>
//#include "harddriver/mbdriver_ioctl.h"		//deleted by sunpeng at 20121205
#include "harddriver/data_types.h"				//added by sunpeng at 20131213
#include "package/Const.h"
using namespace std;

//const unsigned int  CPL_ID_MAX_LEN = 36; 
//const unsigned int  KDM_ID_MAX_LEN = 36;

class ShowNode
{
private:
	class CPLNode;
	class KDMNode;
		
public:
	enum 
	{
		SUCCEED = 0,
		SETERROR = 1
	};

	ShowNode();
	~ShowNode();
		
	void ClearKDM();
	
	CPLNode *GetCPLNode();
	KDMNode *GetKDMNode();
	
	int SetCPL(CPLNode *QouteCPL);
	int SetCPL(const unsigned char *NewCPLID, unsigned int PreCheckRst, int NewCPLConnentLen, const unsigned char *NewCPLConnent);
	
	const unsigned char *GetCPLID();
	const unsigned char* GetCPLConnent();
	unsigned int GetCPLPreCheakRst();
	bool HasSameCPL(const unsigned char*NewCPLID);	
	
	int SetKDM(KDMNode *QouteKDM);
	int SetKDM(const unsigned char *NewKDMID, int NewKDMConnentLen, const unsigned char *NewKDMConnent);
		
	const unsigned char *GetKDMID();
	const unsigned char *GetKDMConnent();
	bool HasSameKDM(const unsigned char*NewKDMID);

	void DisplayShowInfo();

	bool GetCPLQuoteflage();
	bool GetKDMQuoteflage();	
		
	void SetEncryptionFlag(bool flag);	
	bool GetEncryptionFlag();
	
	void SetCPLDuration(unsigned int Duration);	
	unsigned int GetCPLDuration();
		
	void SetContentKeysNotValidBefore(unsigned int Time);	
	unsigned int GetContentKeysNotValidBefore();
	
	void SetContentKeysNotValidAfter(unsigned int Time);	
	unsigned int GetContentKeysNotValidAfter();
	
	void SetAudioFMFlag(bool NewAudioFMFlag);	
	bool GetAudioFMFlag();
	
	void SetImageFMFlag(bool NewImageFMFlag);	
	bool GetImageFMFlag();
	
	vector<char*> CPLCertThumbprintList;
	map<string,string>  TrackId2KeyId;
	vector<content_key> ContentKeyList; 	
	
private:
	CPLNode *InvolveCPLNode;
	KDMNode *InvolveKDMNode;
	bool CPLQuoteFlag;	
	bool KDMQuoteFlag;
};

class ShowList
{
public:
	ShowList(int CompNum);
	~ShowList();
	ShowNode &operator[](int i);	
	unsigned int size();
	void ClearAllKDM();
	unsigned int GetShowDuration();
 
private:
	unsigned int CompNumber;
	ShowNode *ShowListhead;
};

class ShowNode::CPLNode
{
public:
	CPLNode()
	{
		CPLConnent = NULL;
		EncryptionFlag = false;
		PreCheckRst = 0;
		Duration = 0;
		CPLID = new unsigned char[CPL_ID_MAX_LEN+1];
		memset(CPLID, 0, CPL_ID_MAX_LEN+1);
	};

	~CPLNode()
	{
		delete []CPLID;
		if(NULL != CPLConnent)
			delete []CPLConnent;	
	}
	
	bool           EncryptionFlag;	
	unsigned int   PreCheckRst;
	unsigned char *CPLConnent; 
	unsigned char *CPLID;
	unsigned int   Duration;
};

class ShowNode::KDMNode
{
public:
	KDMNode()
	{
		KDMConnent = NULL;
		ContentKeysNotValidBefore = 0;
		ContentKeysNotValidAfter = 0;
		KDMID = new unsigned char[KDM_ID_MAX_LEN+1];	
		memset(KDMID, 0, KDM_ID_MAX_LEN+1);
		AudioFMFlag = false;
		ImageFMFlag = false;
	}

	~KDMNode()
	{
		delete []KDMID;
		if(NULL != KDMConnent)
			delete []KDMConnent;

	}
	unsigned char *KDMID;
	unsigned char *KDMConnent;
	unsigned int  ContentKeysNotValidBefore;
	unsigned int  ContentKeysNotValidAfter; 
	bool          AudioFMFlag;
	bool          ImageFMFlag;
};

#endif
