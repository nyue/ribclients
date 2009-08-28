#include "ParameterList.h"

ParameterList::ParameterList(DeclarationManager& dm)
  : TParameterList<void*>(dm)
{
}

ParameterList::~ParameterList()
{
}

bool ParameterList::ProcessParameterList(void* parameterlist)
{
  return true;
}

void ParameterList::NewRtStringVector(void* stringArray,
				      RtStringVector& stringVector)
{
}

void ParameterList::ConvertToSTLStringVector(void* stringArray,
					     StringVec& stringVector)
{
}

