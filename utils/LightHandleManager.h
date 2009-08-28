#ifndef _LIGHTHANDLEMANAGER_H_
#define _LIGHTHANDLEMANAGER_H_

#include <map>
#include <ri.h>

class LightHandleManager {
  typedef std::map<int,RtLightHandle> LightHandleContainer;
  typedef LightHandleContainer::iterator LightHandleContainerIter;
  typedef LightHandleContainer::const_iterator LightHandleContainerCIter;
public:
  LightHandleManager();
  virtual ~LightHandleManager();
  int Add(RtLightHandle lh);
  RtLightHandle Get(int lhID);
private:
  int _lastLightHandleID;
  LightHandleContainer _lhc;
};

#endif // _LIGHTHANDLEMANAGER_H_
