#include "ParameterList.h"
// #include <vld.h>

ParameterList::ParameterList(DeclarationManager& dm)
  : TParameterList<VALUE>(dm)
{
}

ParameterList::~ParameterList()
{
}

VALUE HashIterator(VALUE arg1, ParameterList* parmPtr)
{
  VALUE key, value;
  VALUE eRIBError; ///< Ruby exception value
  
  key = rb_ary_entry(arg1, 0);
  value = rb_ary_entry(arg1, 1);

  Check_Type(key,T_STRING);
  Check_SafeStr(key);
#ifdef RUBY_VERSION_POST_180
  std::string tokenStr = RSTRING_PTR(key);
#else
  std::string tokenStr = RSTRING(key)->ptr;
#endif // RUBY_VERSION_POST_180

  parmPtr->GetTokenStorage()[parmPtr->GetCurrentParamIndex()] = tokenStr;
  // std::cout << "Hash key : \"" << tokenStr.c_str() << "\"" << std::endl;

  Check_Type(value,T_ARRAY);
  struct RArray* pvp = RARRAY(value);
  size_t numElements = pvp->len;
  // std::cout << "Parameter array of size " << numElements << std::endl;
  if (numElements != 0) {
    // From the token, find out what data type to expect
    DeclarationManager::DeclarationInfo di =
      parmPtr->GetDM().GetDeclarationInfo(tokenStr);

    std::vector<RtFloat> floatPlaceHolder;
    std::vector<std::string> stringPlaceHolder;
    std::vector<RtInt> integerPlaceHolder;

    // Process according to the expected type
    { // START PROCESSING CODE

      // Setup the required storage size for an expected token type
      switch (di._type)	{
      case DeclarationManager::DeclarationInfo::FLOAT:
      case DeclarationManager::DeclarationInfo::POINT:
      case DeclarationManager::DeclarationInfo::COLOR:
      case DeclarationManager::DeclarationInfo::VECTOR:
      case DeclarationManager::DeclarationInfo::NORMAL:
      case DeclarationManager::DeclarationInfo::MATRIX:
      case DeclarationManager::DeclarationInfo::HPOINT:
	// std::cout << "Parameter is expecting float array" << std::endl;
	parmPtr->GetFloatParamStorage().push_back(floatPlaceHolder);
	parmPtr->GetFloatParamStorage().back().resize(numElements);
	break;
      case DeclarationManager::DeclarationInfo::INTEGER:
	// std::cout << "Parameter is expecting integer array" << std::endl;
	parmPtr->GetIntegerParamStorage().push_back(integerPlaceHolder);
	parmPtr->GetIntegerParamStorage().back().resize(numElements);
	break;
      case DeclarationManager::DeclarationInfo::STRING:
	// std::cout << "Parameter is expecting string array" << std::endl;
	parmPtr->GetStringParamStorage().push_back(stringPlaceHolder);
	parmPtr->GetStringParamStorage().back().resize(numElements);
	break;
      default:
	throw std::runtime_error("Unknown type, unable to allocate storage");
      }

      // Now extract the actual values
      for (size_t i=0;i<numElements;i++) {
	float fParm = 0.0f;
	RtInt iParm = 0;
	std::string sParm;
	VALUE parmVal = pvp->ptr[i];
	switch (di._type) {
	case DeclarationManager::DeclarationInfo::FLOAT:
	case DeclarationManager::DeclarationInfo::POINT:
	case DeclarationManager::DeclarationInfo::COLOR:
	case DeclarationManager::DeclarationInfo::VECTOR:
	case DeclarationManager::DeclarationInfo::NORMAL:
	case DeclarationManager::DeclarationInfo::MATRIX:
	case DeclarationManager::DeclarationInfo::HPOINT:
	  if (TYPE(parmVal) == T_FIXNUM) {
	    fParm = static_cast<float>(NUM2INT(parmVal));
	  } else if (TYPE(parmVal) == T_FLOAT) {
	    fParm = static_cast<float>(NUM2DBL(parmVal));
	  }
	  // std::cout << "fParm : " << fParm << std::endl;
	  parmPtr->GetFloatParamStorage().back()[i] = fParm;
	  break;
	case DeclarationManager::DeclarationInfo::INTEGER:
	  if (TYPE(parmVal) == T_FIXNUM) {
	    iParm = static_cast<RtInt>(NUM2INT(parmVal));
	    parmPtr->GetIntegerParamStorage().back()[i] = iParm;
	  } else {
	    std::cerr << "ERROR: Expecting integer parameter" << std::endl;
	  }
	  break;
	case DeclarationManager::DeclarationInfo::STRING:
	  if (TYPE(parmVal) == T_STRING) {
#ifdef RUBY_VERSION_POST_180
	    sParm = RSTRING_PTR(parmVal);
#else
	    sParm = RSTRING(parmVal)->ptr;
#endif // RUBY_VERSION_POST_180
	    parmPtr->GetStringParamStorage().back()[i] = sParm;
	  } else {
	    std::cerr << "ERROR: Expecting string parameter" << std::endl;
	  }
	  break;
	default:
	  throw std::runtime_error("Unknown type, unable to allocate storage");
	}
      }

      // Put the extracted values into retrieval and C-RIBClient compatible
      // pointer
      {
	size_t i = parmPtr->GetCurrentParamIndex();
	parmPtr->GetRIBClientCompatibleTokens()[i] =
	  const_cast<char*>(parmPtr->GetTokenStorage()[i].c_str());
	// Now update the pointers for the token value pair
	switch (di._type) {
	case DeclarationManager::DeclarationInfo::FLOAT:
	case DeclarationManager::DeclarationInfo::POINT:
	case DeclarationManager::DeclarationInfo::COLOR:
	case DeclarationManager::DeclarationInfo::VECTOR:
	case DeclarationManager::DeclarationInfo::NORMAL:
	case DeclarationManager::DeclarationInfo::MATRIX:
	case DeclarationManager::DeclarationInfo::HPOINT:
	  parmPtr->GetRIBClientCompatibleParms()[i] =
	    &(parmPtr->GetFloatParamStorage().back()[0]);
	  break;
	case DeclarationManager::DeclarationInfo::INTEGER:
	  parmPtr->GetRIBClientCompatibleParms()[i] =
	    &(parmPtr->GetIntegerParamStorage().back()[0]);
	  break;
	case DeclarationManager::DeclarationInfo::STRING:
	  parmPtr->GetRIBClientCompatibleParms()[i] =
	    &(parmPtr->GetStringParamStorage().back()[0]);
	  break;
	default:
	  throw std::runtime_error("Unknown type, unable to allocate storage");
	}
      }
    } // END PROCESSING CODE
  } else {
    std::string exceptionStr = "Null parameter value for : " + tokenStr;
    rb_raise(eRIBError, exceptionStr.c_str());
  }
  parmPtr->IncrementParamIndex();
  return Qnil;
}

VALUE ParameterList::parm_hash_iter(VALUE arg1, VALUE arg2)
{
  VALUE key, value;
  
  key = rb_ary_entry(arg1, 0);
  value = rb_ary_entry(arg1, 1);

  Check_Type(key,T_STRING);
  Check_SafeStr(key);
#ifdef RUBY_VERSION_POST_180
  std::string tokenStr = RSTRING_PTR(key);
#else
  std::string tokenStr = RSTRING(key)->ptr;
#endif // RUBY_VERSION_POST_180

  // std::cout << "Hash key : \"" << tokenStr.c_str() << "\"" << std::endl;

  Check_Type(value,T_ARRAY);
  struct RArray* tvp = RARRAY(value);
  if (tvp->len != 0)
  {
    // From the token, find out what data type to expect
    DeclarationManager::DeclarationInfo di = _dm.GetDeclarationInfo(tokenStr);
  }
  else
  {
    std::string exceptionStr = "Null parameter value for : " + tokenStr;
    rb_raise(eRIBError, exceptionStr.c_str());
  }
  return Qnil;
}

bool ParameterList::ProcessParameterList(VALUE parameterlist)
{
#ifdef TEST_CODE
  static VALUE tt_i(VALUE arg1, VALUE arg2) {
    VALUE key, value;
    
    key = rb_ary_entry(arg1, 0);
    value = rb_ary_entry(arg1, 1);
    /* do what you want with key and value */
    return Qnil;
  }
  
  static VALUE tt(VALUE arg1)
    {
      VALUE arg2 = INT2FIX(12);
      return rb_iterate(rb_each, arg1, tt_i, arg2);
    }
#endif
  struct RHash* tvp = RHASH(parameterlist);
#ifdef RUBY_VERSION_POST_180
  Init(tvp->ntbl->num_entries);
#else
  Init(tvp->tbl->num_entries);
#endif // RUBY_VERSION_POST_180
  // std::cout << "Number of entries in hashtable is " << tvp->tbl->num_entries << std::endl;
  VALUE result = rb_iterate(rb_each, parameterlist,
			    (VALUE (*)(...))&HashIterator,
			    (VALUE)this);
  return true;
}

bool ParameterList::ProcessParameterListEx(VALUE parameterlist)
{
  struct RArray* tvp;
  if (TYPE(parameterlist) != T_ARRAY)
  {
    std::cerr << "ERROR: parameterlist is not an array, unable to proceed"
	      << std::endl;
    return false;
  }
  tvp = RARRAY(parameterlist);
#ifdef DEBUG
  std::cout << "parameterlist size " << tvp->len << std::endl;
#endif
  if (tvp->len != 0 && ((tvp->len) % 2) != 0)
  {
    // rb_raise(eRIBError,"Parameter list has odd number of items");
    std::cerr << "ERROR: Parameter list has odd number of items\n";
    return false;
  }
  size_t numTokenValuePairs = (tvp->len)/2;
#ifdef DEBUG
  std::cout << "numTokenValuePairs = " << numTokenValuePairs << std::endl;
#endif // DEBUG
  Init(numTokenValuePairs);
  // Main loop to process each token-value pair
  for (size_t i=0;i<numTokenValuePairs;i++)
  {
    // Get the ruby data for the token
    VALUE t = tvp->ptr[i*2];
    if (TYPE(t) != T_STRING)
    {
      std::cerr << "ERROR: Token is not a string type, unable to proceed"
		<< std::endl;
      return false;
    }
    // Get the ruby data for the parm
    VALUE p = tvp->ptr[i*2+1];
    if (TYPE(p) != T_ARRAY)
    {
      std::cerr << "ERROR: Value is not an array, unable to proceed"
		<< std::endl;
      return false;
    }

    // Save the token 
#ifdef RUBY_VERSION_POST_180
    std::string tokenStr(RSTRING_PTR(t));
#else
    std::string tokenStr(RSTRING(t)->ptr);
#endif // RUBY_VERSION_POST_180
#ifdef DEBUG
    std::cout << "Processing pair[" << i << "] token = "
	      << tokenStr.c_str() << std::endl;
#endif // DEBUG
    // tokenStorage.push_back(tokenStr); ///< \todo Do we still need this?
    _tokenStorage[i] = tokenStr;

    // From the token, find out what data type to expect
    DeclarationManager::DeclarationInfo di = _dm.GetDeclarationInfo(tokenStr);

    // Process (loop) and save the parm 
    struct RArray *pvp = RARRAY(p);
    size_t numElements = pvp->len;

    // Prepare the correct storage type since we know what to expect
    std::vector<RtFloat> floatPlaceHolder;
    std::vector<std::string> stringPlaceHolder;
    std::vector<RtInt> integerPlaceHolder;
    FloatParamStorageIter fIter;
    IntegerParamStorageIter iIter;
    StringParamStorageIter sIter;
    switch (di._type)	{
    case DeclarationManager::DeclarationInfo::FLOAT:
    case DeclarationManager::DeclarationInfo::POINT:
    case DeclarationManager::DeclarationInfo::COLOR:
    case DeclarationManager::DeclarationInfo::VECTOR:
    case DeclarationManager::DeclarationInfo::NORMAL:
    case DeclarationManager::DeclarationInfo::MATRIX:
    case DeclarationManager::DeclarationInfo::HPOINT:
      _floatParamStorage.push_back(floatPlaceHolder);
      _floatParamStorage.back().resize(numElements);
      break;
    case DeclarationManager::DeclarationInfo::INTEGER:
      _integerParamStorage.push_back(integerPlaceHolder);
      _integerParamStorage.back().resize(numElements);
      break;
    case DeclarationManager::DeclarationInfo::STRING:
      _stringParamStorage.push_back(stringPlaceHolder);
      _stringParamStorage.back().resize(numElements);
      break;
      break;
    default:
      throw std::runtime_error("[1] Unknown type, unable to allocate storage");
    }
#ifdef DEBUG
    std::cout << "Processing pair[" << i << "] params length = "
	      << numElements << std::endl;
#endif // DEBUG
    for (size_t parmIndex=0;parmIndex<numElements;parmIndex++)
    {
      float fParm = 0.0f;
      RtInt iParm = 0;
      std::string sParm;
      VALUE parmVal = pvp->ptr[parmIndex];
      switch (di._type)
      {
      case DeclarationManager::DeclarationInfo::FLOAT:
      case DeclarationManager::DeclarationInfo::POINT:
      case DeclarationManager::DeclarationInfo::COLOR:
      case DeclarationManager::DeclarationInfo::VECTOR:
      case DeclarationManager::DeclarationInfo::NORMAL:
      case DeclarationManager::DeclarationInfo::MATRIX:
      case DeclarationManager::DeclarationInfo::HPOINT:
	if (TYPE(parmVal) == T_FIXNUM)
	{
	  fParm = static_cast<float>(NUM2INT(parmVal));
#ifdef DEBUG
	  std::cout << "float (cast) parmVal[" << parmIndex
		    << "] = " << fParm << std::endl;
#endif // DEBUG
	}
	else if (TYPE(parmVal) == T_FLOAT)
	{
	  fParm = static_cast<float>(NUM2DBL(parmVal));
#ifdef DEBUG
	  std::cout << "float parmVal[" << parmIndex <<"] = "
		    << NUM2DBL(parmVal) << std::endl;
#endif // DEBUG
	}
	_floatParamStorage.back()[parmIndex] = fParm;
	break;
      case DeclarationManager::DeclarationInfo::INTEGER:
	if (TYPE(parmVal) == T_FIXNUM)
	{
	  iParm = static_cast<RtInt>(NUM2INT(parmVal));
#ifdef DEBUG
	  std::cout << "int hello parmVal[" << parmIndex << "] = "
		    << iParm << std::endl;
#endif // DEBUG
	  _integerParamStorage.back()[parmIndex] = iParm;
	}
	else
	{
	  std::cerr << "ERROR: Expecting integer parameter" << std::endl;
	}
	break;
      case DeclarationManager::DeclarationInfo::STRING:
	if (TYPE(parmVal) == T_STRING)
	{
#ifdef RUBY_VERSION_POST_180
	  sParm = RSTRING_PTR(parmVal);
#else
	  sParm = RSTRING(parmVal)->ptr;
#endif // RUBY_VERSION_POST_180

#ifdef DEBUG
	  std::cout << "string parmVal[" << parmIndex << "] = "
		    << sParm.c_str() << std::endl;
#endif // DEBUG
	  _stringParamStorage.back()[parmIndex] = sParm;
	}
	else
	{
	  std::cerr << "ERROR: Expecting string parameter" << std::endl;
	}
	break;
      default:
	throw std::runtime_error("[2] Unknown type, unable to allocate storage");
      }
    }

    _tokens[i] = const_cast<char*>(_tokenStorage[i].c_str());
    // Now update the pointers for the token value pair
    switch (di._type)
    {
    case DeclarationManager::DeclarationInfo::FLOAT:
    case DeclarationManager::DeclarationInfo::POINT:
    case DeclarationManager::DeclarationInfo::COLOR:
    case DeclarationManager::DeclarationInfo::VECTOR:
    case DeclarationManager::DeclarationInfo::NORMAL:
    case DeclarationManager::DeclarationInfo::MATRIX:
    case DeclarationManager::DeclarationInfo::HPOINT:
      _parms[i] = &(_floatParamStorage.back()[0]);
      break;
    case DeclarationManager::DeclarationInfo::INTEGER:
      _parms[i] = &(_integerParamStorage.back()[0]);
      break;
    case DeclarationManager::DeclarationInfo::STRING:
      // _parms[i] = const_cast<char *>(stringParamStorage.back()[0].c_str());
      _parms[i] = &(_stringParamStorage.back()[0]); ///< Fragile coding?
#ifdef DEBUG
      std::cout << "Assigned string " << _parms[i] << std::endl;
#endif // DEBUG
      break;
    default:
      throw std::runtime_error("[3] Unknown type, unable to allocate storage");
    }
  }
#ifdef DEBUG
  std::cout << "ProcessParameterList [END]" << std::endl
	    << *this << std::endl;
#endif // DEBUG
  return true;
}

void ParameterList::ConvertToSTLStringVector(VALUE stringArray,
					     StringVec& stringVector)
{
  if (TYPE(stringArray) != T_ARRAY) {
    std::cerr << "ERROR: parameterlist is not an array, unable to proceed"
	      << std::endl;
    return;
  }
  struct RArray* tvp;
  tvp = RARRAY(stringArray);
  size_t numElements = tvp->len;
  stringVector.resize(numElements);
  for (size_t i=0;i<numElements;i++) {
#ifdef RUBY_VERSION_POST_180
    stringVector[i] = RSTRING_PTR(tvp->ptr[i]);
#else
    stringVector[i] = RSTRING(tvp->ptr[i])->ptr;
#endif // RUBY_VERSION_POST_180
  }
}

void ParameterList::ConvertToRtIntVector(VALUE integerArray,
					 RtIntVector& integerVector)
{
}

void ParameterList::ConvertToRtFloatVector(VALUE floatArray,
					   RtFloatVector& floatVector)
{
}

void ParameterList::VALUE2STLStringVector(VALUE stringArray,
					  StringVec& stringVector)
{
  if (TYPE(stringArray) != T_ARRAY) {
    std::cerr << "ERROR: parameterlist is not an array, unable to proceed"
	      << std::endl;
    return;
  }
  struct RArray* tvp;
  tvp = RARRAY(stringArray);
  size_t numElements = tvp->len;
  stringVector.resize(numElements);
  for (size_t i=0;i<numElements;i++) {
#ifdef RUBY_VERSION_POST_180
    stringVector[i] = RSTRING_PTR(tvp->ptr[i]);
#else
    stringVector[i] = RSTRING(tvp->ptr[i])->ptr;
#endif // RUBY_VERSION_POST_180
  }
}

RtFloat ParameterList::VALUE2RtFloat(VALUE number)
{
  double result = 0.0;
  switch (TYPE(number)) {
  case T_FIXNUM:
  case T_BIGNUM:
    result = (double)NUM2INT(number);
    break;
  case T_FLOAT:
    result = NUM2DBL(number);
    break;
  default:
    rb_raise(eRIBError,"Numerical values required as argument");
  }
  return static_cast<RtFloat>(result);
}

void ParameterList::VALUE2RtFloatVector(VALUE numberArray,
					RtFloatVector& floatVector)
{
  if (TYPE(numberArray) != T_ARRAY) {
    std::cerr << "ERROR: parameterlist is not an array, unable to proceed"
	      << std::endl;
    return;
  }
  struct RArray* tvp;
  tvp = RARRAY(numberArray);
  size_t numElements = tvp->len;
  floatVector.resize(numElements);
  for (size_t i=0;i<numElements;i++) {
    VALUE t = tvp->ptr[i];
    floatVector[i] = VALUE2RtFloat(t);
  }
}

void ParameterList::VALUE2RtIntVector(VALUE numberArray,
				      RtIntVector& integerVector)
{
  if (TYPE(numberArray) != T_ARRAY) {
    std::cerr << "ERROR: parameterlist is not an array, unable to proceed"
	      << std::endl;
    return;
  }
  struct RArray* tvp;
  tvp = RARRAY(numberArray);
  size_t numElements = tvp->len;
  integerVector.resize(numElements);
  // std::cout << "VALUE2RtIntVector numElements=" << numElements << std::endl;
  for (size_t i=0;i<numElements;i++) {
    VALUE t = tvp->ptr[i];
    RtInt value = NUM2INT(t);
    // std::cout << "VALUE2RtIntVector value=" << value << std::endl;
    integerVector[i] = value;
  }
}

void ParameterList::VALUE2RtMatrix(VALUE numberArray,
				   RtMatrix matrix)
{
  ParameterList::RtFloatVector floatVector;
  VALUE2RtFloatVector(numberArray,floatVector);
  if (floatVector.size() != 16) {
    rb_raise(eRIBError,"Bad array size");
  }
  for (size_t i= 0;i<4;i++) {
    for (size_t j= 0;j<4;j++)	{
      matrix[i][j] = floatVector[j+i*4];
    }
  }
}

std::ostream& operator <<(std::ostream &os,
			  const ParameterList &obj)
{
  os << obj._size << std::endl;
  for (size_t i=0;i<obj._size;i++)
  {
    os << "_tokenStorage[" << i << "] is "
       << "\""
       << obj._tokenStorage[i].c_str()
       << "\""
       << "_tokens[" << i << "] is " << obj._tokens[i]
       << std::endl;
  }
  // std::cout<< "DONE\n";
  return os;
}
