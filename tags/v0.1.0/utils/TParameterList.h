/*
 * Copyright Procedural Insight 2006
 * Author Nicholas Yue
 */

#ifndef TPARAMETERLIST_H
#define TPARAMETERLIST_H

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <ri.h>
#include "DeclarationManager.h"

/*!
  This process in input parameter list pass in as a Ruby array and
  processed into a suitable form form i.e. RtToken and RtVoid, for
  passing on to the underlying C-API of the RIB-client library

  \brief Represents the parameters pass into a given RIB client API
 */
template <typename T> class TParameterList
{
  enum ParameterType {STG_FLOAT, STG_STRING};
public:
  typedef std::vector<RtFloat>  RtFloatVector;
  typedef std::vector<RtInt>    RtIntVector;
  typedef std::vector<RtString> RtStringVector;
  typedef std::vector<RtToken>  RtTokenVector;
  // 
  typedef std::vector<std::string>  StringVec;
  // RtFloat
  typedef std::list< std::vector<RtFloat> > FloatParamStorageType;
  typedef FloatParamStorageType::iterator FloatParamStorageIter;
  typedef FloatParamStorageType::const_iterator FloatParamStorageCIter;
  // RtInt
  typedef std::list< std::vector<RtInt> > IntegerParamStorageType;
  typedef IntegerParamStorageType::iterator IntegerParamStorageIter;
  typedef IntegerParamStorageType::const_iterator IntegerParamStorageCIter;
  // RtString
  typedef std::list< std::vector<std::string> > StringParamStorageType;
  typedef StringParamStorageType::iterator StringParamStorageIter;
  typedef StringParamStorageType::const_iterator StringParamStorageCIter;

  typedef std::list< RtString > StringPtrParamStorageType;
  typedef StringPtrParamStorageType::iterator StringPtrParamStorageIter;
  typedef StringPtrParamStorageType::const_iterator StringPtrParamStorageCIter;

  typedef std::list< RtStringVector > StringPtrParamStorageTypeEx;
  typedef std::list< RtTokenVector > TokenPtrParamStorageTypeEx;

  TParameterList();
  TParameterList(DeclarationManager& dm);
  virtual ~TParameterList();

  const DeclarationManager& GetDM() const { return _dm; };
  DeclarationManager& GetDM() { return _dm; };

  StringVec& GetTokenStorage() { return _tokenStorage; };
  FloatParamStorageType& GetFloatParamStorage() { return _floatParamStorage; };
  IntegerParamStorageType& GetIntegerParamStorage() { return _integerParamStorage; };
  StringParamStorageType& GetStringParamStorage() { return _stringParamStorage; };

  RtToken* GetRIBClientCompatibleTokens() { return &(_tokens[0]);};
  RtPointer* GetRIBClientCompatibleParms() { return &(_parms[0]);};

  /*!
    \note Algorithm
    \li Retrieve parameterlist as a ruby Array object
    \li Assert that the number of items in the Array object is an even number
        [token/value pair] or zero
    \li Assert that every token is a String object
    \li Create storage for each value (so as to retrieve address)
    \li Build up the tokens[] and parms[] array in the reference
        argument _param
    \note Check the rbogl.c code for examples on packing ruby arrays to
          C-arrays
    \return bool Succesfully processed the parameterlist?
    \param parameterlist Parameter list object from Ruby
   */
  virtual bool ProcessParameterList(T parameterlist) = 0;

  /*!
    \brief Returns a const pointer to the token array
    \return const RtToken*
   */
  // const RtToken* GetTokens() const;

  /*!
    \brief Returns a const pointer to the parm array
    \return const RtPointer*
   */
  // const RtPointer* GetParms() const;

  inline size_t size() const { return _size; };

  /*!
    Given a langauge dependent object which represents any array of strings
    updates the equivalent std::vector<std::string>
    \param[in] stringArray Language specific object
    \param[out] stringVector STL string container
   */
  virtual void ConvertToSTLStringVector(T stringArray,
                                        StringVec& stringVector) = 0;
  
  /*!
    Given a langauge dependent object which represents any array of integer
    updates the equivalent std::vector<RtInt>
    \param[in] stringArray Language specific object
    \param[out] stringVector STL string container
   */
  virtual void ConvertToRtIntVector(T integerArray,
                                    RtIntVector& integerVector) = 0;
  
  /*!
    Given a langauge dependent object which represents any array of float
    updates the equivalent std::vector<RtFloat>
    \param[in] stringArray Language specific object
    \param[out] stringVector STL string container
   */
  virtual void ConvertToRtFloatVector(T floatArray,
                                      RtFloatVector& floatVector) = 0;
  
  /*!
    Re-initialize the object to the original constructed state
    Useful when we want to reuse this object many times
   */
  void Reinitialize();

  /*!
    I have problem with Ruby's rb_iterate because it requires a C function
    pointer. To use a normal C function, I need to pass a pointer to these
    TParameterList derive object has it result in an explosion of various
    methods to get and set stuff which would otherwise be fine as protected
    member for derived class.
   */
  size_t GetCurrentParamIndex() const {
    // std::cout << "GetCurrentParamIndex() = " << _paramIndex << std::endl;
    return _paramIndex;
  };
  void IncrementParamIndex() { _paramIndex++;};

#ifdef ANDY_HELP_AVAILABLE
  /*!
    \brief Dumps out the content
   */
  virtual friend std::ostream& operator <<(std::ostream &os,
                                           const TParameterList<T> &obj) = 0;
#endif // ANDY_HELP_AVAILABLE

protected:  

  void Init(size_t numTVPairs);
  void cleanUpRawPointerArray(); /// experimental

  StringVec _tokenStorage;
  DeclarationManager& _dm;
  FloatParamStorageType _floatParamStorage;
  IntegerParamStorageType _integerParamStorage;
  StringParamStorageType _stringParamStorage;
  std::vector<RtToken> _tokens;
  std::vector<RtPointer> _parms;
  size_t _size;
  char** _rawCharPtrArray; /// experimental
  size_t _numPointers;

private:
  void Update(size_t index, std::string& tokenName, RtFloatVector& floatParam);
  void Update(size_t index, std::string& tokenName, RtIntVector& intParam);
  void Update(size_t index, std::string& tokenName, StringVec& stringParam);


  std::vector<ParameterType> parameterType;
  std::vector<void *> parms;
  StringPtrParamStorageType ptrParamStorage;
  size_t _paramIndex;

public: // Make storage private with accesor after testing

  /*!
    \remark The reason for storing these vector inside a list is this; In some
    RIBClient API call, there are multiple argument of type *RtInt or *RtFloat
    so the idea is to store each of them in a list and "clean up" all these
    at the end of every "wrap" function via the %typemap (ret) block of code
   */
  StringParamStorageType      __STLstringArrayStorage; ///< internal
  IntegerParamStorageType     _RtIntArrayStorage;
  FloatParamStorageType       _RtFloatArrayStorage;
  StringPtrParamStorageTypeEx _RtStringArrayStorage;
  TokenPtrParamStorageTypeEx  _RtTokenArrayStorage;
  /*!
    Clean up the 5 std::list of storage so that it is ready to be used
    \@todo Do some unit test on memory leakage
   */
  void CleanUpArgStorage();
  RtInt* AddRtIntArrayArg(RtIntVector input);
  RtFloat* AddRtFloatArrayArg(RtFloatVector input);
  RtString* AddRtStringArrayArg(StringVec input);
  RtToken* AddRtTokenArrayArg(StringVec input);
};

#include "TParameterList.tcc"

#endif // PARAMETER_LIST

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
