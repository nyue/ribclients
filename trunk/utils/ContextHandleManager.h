#ifndef _CONTEXTHANDLEMANAGER_H_
#define _CONTEXTHANDLEMANAGER_H_

#include <map>
#include <ri.h>

class ContextHandleManager {
  typedef std::map<int,RtContextHandle> ContextHandleContainer;
  typedef ContextHandleContainer::iterator ContextHandleContainerIter;
  typedef ContextHandleContainer::const_iterator ContextHandleContainerCIter;
public:
  ContextHandleManager();
  virtual ~ContextHandleManager();
  int Add(RtContextHandle ch);
  RtContextHandle Get(int chID);
private:
  int _lastContextHandleID;
  ContextHandleContainer _chc;
};

#endif // _CONTEXTHANDLEMANAGER_H_
