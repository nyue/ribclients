#ifndef _OBJECTHANDLEMANAGER_H_
#define _OBJECTHANDLEMANAGER_H_

#include <map>
#include <ri.h>

class ObjectHandleManager {
  typedef std::map<int,RtObjectHandle> ObjectHandleContainer;
  typedef ObjectHandleContainer::iterator ObjectHandleContainerIter;
  typedef ObjectHandleContainer::const_iterator ObjectHandleContainerCIter;
public:
  ObjectHandleManager();
  virtual ~ObjectHandleManager();
  int Add(RtObjectHandle oh);
  RtObjectHandle Get(int ohID);
private:
  int _lastObjectHandleID;
  ObjectHandleContainer _ohc;
};

#endif // _OBJECTHANDLEMANAGER_H_
