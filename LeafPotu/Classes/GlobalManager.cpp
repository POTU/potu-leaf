#include "GlobalManager.h"

GlobalManager* GlobalManager::singleton_GlobMgr;

GlobalManager::GlobalManager()
{
}

GlobalManager::~GlobalManager()
{
}

GlobalManager* GlobalManager::getInstance()
{
	if(!singleton_GlobMgr)
	{
		singleton_GlobMgr = new GlobalManager();
	}
	return singleton_GlobMgr;
}