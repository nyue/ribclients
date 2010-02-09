#include "LightHandleManager.h"

LightHandleManager::LightHandleManager()
  : _lastLightHandleID(0)
{

}


LightHandleManager::~LightHandleManager()
{

}

int LightHandleManager::Add(RtLightHandle lh)
{
  _lhc.insert(std::make_pair(_lastLightHandleID,lh));
  int returnValue = _lastLightHandleID;
  _lastLightHandleID++;

  return returnValue;
}


RtLightHandle LightHandleManager::Get(int lhID)
{
  return _lhc[lhID];
}

