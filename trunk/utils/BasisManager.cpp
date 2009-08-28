#include "BasisManager.h"
#include <iostream>

BasisManager::BasisManager()
  : _lastUserBasisID(0)
{
  Initialize();
#ifdef DEBUG
  DebugPrintAll();
#endif // DEBUG
}

BasisManager::~BasisManager()
{
}

void BasisManager::Set(RtBasis* newBasis,
		       int basisID)
{
  _basis[basisID] = newBasis;
}

void BasisManager::Get(RtBasis** newBasis,
		       int basisID)
{
  *newBasis = _basis[basisID];
}

void BasisManager::Initialize()
{
  Set(&RiBezierBasis,     BEZIERBASIS);
  Set(&RiBSplineBasis,    BSPLINEBASIS);
  Set(&RiCatmullRomBasis, CATMULLROMBASIS);
  Set(&RiHermiteBasis,    HERMITEBASIS);
  Set(&RiPowerBasis,      POWERBASIS);
}

void BasisManager::DebugPrintAll()
{
  std::cout << "BasisManager size " << size() << std::endl;
  RtBasisContainer::iterator ie = _basis.end();
  RtBasisContainer::iterator iter = _basis.begin();
  for (;iter!=ie;++iter)
  {
    std::cout << "\tBasis[" << iter->first << "]" << std::endl;
    for (size_t i=0;i<4;i++)
    {
      std::cout << "\t\t";
      for (size_t j=0;j<4;j++)
      {
	std::cout << (*iter->second)[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }
}

size_t BasisManager::size() const
{
  return _basis.size();
}
