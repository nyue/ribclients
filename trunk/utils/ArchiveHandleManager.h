#ifndef _ARCHIVEHANDLEMANAGER_H_
#define _ARCHIVEHANDLEMANAGER_H_

#include <map>
#include <ri.h>

#if (defined VERIFY_RIBCLIENT) || (defined AQSIS_RIBCLIENT) || (defined RDC_RIBCLIENT)
typedef RtPointer RtArchiveHandle;
#endif

class ArchiveHandleManager {
  typedef std::map<int,RtArchiveHandle> ArchiveHandleContainer;
  typedef ArchiveHandleContainer::iterator ArchiveHandleContainerIter;
  typedef ArchiveHandleContainer::const_iterator ArchiveHandleContainerCIter;
public:
  ArchiveHandleManager();
  virtual ~ArchiveHandleManager();
  int Add(RtArchiveHandle ah);
  RtArchiveHandle Get(int ahID);
private:
  int _lastArchiveHandleID;
  ArchiveHandleContainer _ahc;
};

#endif // _ARCHIVEHANDLEMANAGER_H_
