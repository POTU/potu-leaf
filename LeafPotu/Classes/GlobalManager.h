#ifndef GLO_MGR_H
#define GLO_MGR_H

class GlobalManager
{
public:
	GlobalManager();
	~GlobalManager();

	static GlobalManager* getInstance();

private:
	static GlobalManager* singleton_GlobMgr;
};

#endif