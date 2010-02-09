#ifndef _ERRORHANDLERMANAGER_H_
#define _ERRORHANDLERMANAGER_H_

#include <map>
#include <ri.h>

class ErrorHandlerManager {
  typedef std::map<int,RtErrorHandler> ErrorHandlerContainer;
  typedef ErrorHandlerContainer::iterator ErrorHandlerContainerIter;
  typedef ErrorHandlerContainer::const_iterator ErrorHandlerContainerCIter;
public:
  ErrorHandlerManager();
  virtual ~ErrorHandlerManager();
  int Add(RtErrorHandler f);
  RtErrorHandler Get(int fID);
private:
  int _lastErrorHandlerID;
  ErrorHandlerContainer _ehc;
};

#endif // _ERRORHANDLERMANAGER_H_
