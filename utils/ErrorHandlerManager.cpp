#include "ErrorHandlerManager.h"

ErrorHandlerManager::ErrorHandlerManager()
  : _lastErrorHandlerID(0)
{

}


ErrorHandlerManager::~ErrorHandlerManager()
{

}

int ErrorHandlerManager::Add(RtErrorHandler eh)
{
  _ehc.insert(std::make_pair(_lastErrorHandlerID,eh));
  int returnValue = _lastErrorHandlerID;
  _lastErrorHandlerID++;

  return returnValue;
}


RtErrorHandler ErrorHandlerManager::Get(int ehID)
{
  return _ehc[ehID];
}

