#include "ContextHandleManager.h"

ContextHandleManager::ContextHandleManager()
  : _lastContextHandleID(0)
{

}


ContextHandleManager::~ContextHandleManager()
{

}

int ContextHandleManager::Add(RtContextHandle ch)
{
  _chc.insert(std::make_pair(_lastContextHandleID,ch));
  int returnValue = _lastContextHandleID;
  _lastContextHandleID++;

  return returnValue;
}


RtContextHandle ContextHandleManager::Get(int chID)
{
  return _chc[chID];
}

