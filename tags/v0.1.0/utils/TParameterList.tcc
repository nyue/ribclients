// -*- C++ -*-                                                                  
/*
 * Copyright Procedural Insight 2006
 * Author Nicholas Yue
 */

#include <stdexcept>

template <typename T> TParameterList<T>::TParameterList(DeclarationManager& dm)
  :_dm(dm)
   // ,_tokens(0)
   // ,_parms(0)
  ,_size(0)
  , _paramIndex(0)
  , _numPointers(0) /// experimental
{
  _rawCharPtrArray = new char* [1024];
}

template <typename T> TParameterList<T>::~TParameterList()
{
  cleanUpRawPointerArray();
}

template <typename T> void TParameterList<T>::Init(size_t numTVPairs)
{
  // std::cout << "TParameterList::Init() size is " << numTVPairs << std::endl;
  if (numTVPairs == 0)
    throw std::runtime_error("Init with zero size");
  _tokenStorage.resize(numTVPairs);
  parms.resize(numTVPairs);
  parameterType.resize(numTVPairs);
  _tokens.resize(numTVPairs);
  _parms.resize(numTVPairs);
  _size = numTVPairs;
  _paramIndex = 0;
  _numPointers = 0;
}

template <typename T> void TParameterList<T>::cleanUpRawPointerArray()
{
  // std::cout << "cleanUpRawPointerArray [START]" << std::endl;
  if ( _rawCharPtrArray != 0 )
  {
    for (size_t i = 0 ; i < _numPointers; i++)
    {
      if ( _rawCharPtrArray[i] != 0 )
        delete [] _rawCharPtrArray[i];
    }
    delete [] _rawCharPtrArray;
  }
  
  // std::cout << "cleanUpRawPointerArray [END]" << std::endl;
}

template <typename T> void TParameterList<T>::Update(size_t index,
                                                     std::string& tokenName,
                                                     RtFloatVector& floatParam)
{
  // Is this depreacted?
}

template <typename T> void TParameterList<T>::Update(size_t index,
                                                     std::string& tokenName,
                                                     RtIntVector& intParam)
{
  // Is this depreacted?
}

template <typename T> void TParameterList<T>::Update(size_t index,
                                                     std::string& tokenName,
                                                     StringVec& stringParam)
{
  // Is this depreacted?
}

template <typename T> void TParameterList<T>::Reinitialize()
{
  _tokenStorage.clear();
  parms.clear();
  parameterType.clear();
  _tokens.clear();
  _parms.clear();
  _size = 0;
  _paramIndex = 0;
}

template <typename T> void TParameterList<T>::CleanUpArgStorage()
{
  __STLstringArrayStorage.clear();
  _RtIntArrayStorage.clear();
  _RtFloatArrayStorage.clear();
  _RtStringArrayStorage.clear();
};

template <typename T> RtInt*
TParameterList<T>::AddRtIntArrayArg(RtIntVector input)
{
  _RtIntArrayStorage.push_back(input);
  return &(_RtIntArrayStorage.back()[0]);
}

template <typename T> RtFloat*
TParameterList<T>::AddRtFloatArrayArg(RtFloatVector input)
{
  _RtFloatArrayStorage.push_back(input);
  return &(_RtFloatArrayStorage.back()[0]);
}

template <typename T> RtString*
TParameterList<T>::AddRtStringArrayArg(StringVec input)
{
  __STLstringArrayStorage.push_back(input);
  RtStringVector rtv;
  _RtStringArrayStorage.push_back(rtv);
  size_t numElements = input.size();
  _RtStringArrayStorage.back().resize(numElements);
  for (size_t i=0;i<numElements;i++)
  {
    _RtStringArrayStorage.back()[i] = &(__STLstringArrayStorage.back()[i][0]);
  }
  return &(_RtStringArrayStorage.back()[0]);
}

template <typename T> RtToken*
TParameterList<T>::AddRtTokenArrayArg(StringVec input)
{
  __STLstringArrayStorage.push_back(input);
  RtTokenVector rtv;
  _RtTokenArrayStorage.push_back(rtv);
  size_t numElements = input.size();
  _RtTokenArrayStorage.back().resize(numElements);
  for (size_t i=0;i<numElements;i++)
  {
    _RtTokenArrayStorage.back()[i] = &(__STLstringArrayStorage.back()[i][0]);
  }
  return &(_RtTokenArrayStorage.back()[0]);
}

// == Emacs ================
// -------------------------
// Local variables:
// tab-width: 8
// indent-tabs-mode: nil
// c-basic-offset: 2
// end:
//
// == vi ===================
// -------------------------
// Format block
// ex:ts=2:sw=2:expandtab
// -------------------------
