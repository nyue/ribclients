#include "ObjectHandleManager.h"

ObjectHandleManager::ObjectHandleManager()
  : _lastObjectHandleID(0)
{

}


ObjectHandleManager::~ObjectHandleManager()
{

}

int ObjectHandleManager::Add(RtObjectHandle oh)
{
  _ohc.insert(std::make_pair(_lastObjectHandleID,oh));
  int returnValue = _lastObjectHandleID;
  _lastObjectHandleID++;

  return returnValue;
}


RtObjectHandle ObjectHandleManager::Get(int ohID)
{
  return _ohc[ohID];
}

