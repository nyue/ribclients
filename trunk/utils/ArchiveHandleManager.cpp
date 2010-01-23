#include "ArchiveHandleManager.h"
#include <iostream>

ArchiveHandleManager::ArchiveHandleManager()
  : _lastArchiveHandleID(0)
{
    // std::cout << "ArchiveHandleManager constructor " << std::endl;
}


ArchiveHandleManager::~ArchiveHandleManager()
{
    // std::cout << "ArchiveHandleManager destructor " << std::endl;
}

int ArchiveHandleManager::Add(RtArchiveHandle ah)
{
    // std::cout << "ArchiveHandleManager add " << std::endl;
  _ahc.insert(std::make_pair(_lastArchiveHandleID,ah));
  int returnValue = _lastArchiveHandleID;
  _lastArchiveHandleID++;

  return returnValue;
}


RtArchiveHandle ArchiveHandleManager::Get(int ahID)
{
  return _ahc[ahID];
}

