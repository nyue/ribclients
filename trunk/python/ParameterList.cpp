#include "ParameterList.h"

#if PY_VERSION_HEX < 0x02050000
typedef int Py_ssize_t;
#endif

ParameterList::ParameterList(DeclarationManager& dm)
  : TParameterList<PyObject*>(dm)
{
}

ParameterList::~ParameterList()
{
}

/*
  \note From looking at the equivalent method in the Ruby extension the
  algorightm seems to be something along the line of
  \li Find how many token-value pair
  \li For each pair
  \li Store the token string
  \li Parse the value (collection of float, color, vector, string...) and
  store them
  After iterating through all the pairs, we'd have "pointer" to the items
  which we can than supply to the Ri*V() methods
 */
bool ParameterList::ProcessParameterList(PyObject* parameterlist)
{
  if (parameterlist == Py_None)
    return true;
  // std::cout << "ProcessParameterList" << std::endl;
  if (parameterlist != Py_None) {
    // std::cout << "parameterlist is not None" << std::endl;
    if (PyDict_Check(parameterlist)) {
      PyObject* pkey;
      PyObject* pvalue;
      int dictIndex = 0;
      Py_ssize_t ppos = 0; // Initialize to first item
      int nDictItems = PyDict_Size(parameterlist);
      // std::cout << "nDictItems [NICHOLAS] = " << nDictItems << std::endl;
      if (nDictItems == 0)
	return true; // Nothing to do
      Init(nDictItems);
      /*!
	\note Even though we know how many items there are in the dictionary,
	a while loop is used more as a convenience for leveraging PyDict_*
	APIs
       */
      while (PyDict_Next(parameterlist,&ppos,&pkey,&pvalue)) {
        // Check that key is a string type
        if (!PyString_CheckExact(pkey)) {
	  std::cerr << "Key is not a string" << std::endl;
          return false;
        }
        // Check that value is a list type
        if (!PyList_Check(pvalue)) {
	  std::cerr << "Key is not a list" << std::endl;
          return false;
        }
	
        // Display key
        char *keyString = PyString_AsString(pkey);
	/*
	std::cout << "Key item "
		  << dictIndex
		  << " is a string object = "
		  << keyString
		  << std::endl;
	*/
	_tokenStorage[dictIndex] = keyString;

        // Display value
        ExtractValue(pvalue, dictIndex, keyString);
	
	// Now update the pointers for the token string
	_tokens[dictIndex] = const_cast<char*>(_tokenStorage[dictIndex].c_str());

        dictIndex++;
      }
    }
  }
  return true;
}

std::ostream& operator <<(std::ostream &os,
			  const ParameterList &obj)
{
  os << obj._size << std::endl;
  for (size_t i=0;i<obj._size;i++)
    {
      os << "tokenStorage[" << i << "] is "
	 << "\""
	 << obj._tokenStorage[i].c_str()
	 << "\""
	 << "_tokens[" << i << "] is " << obj._tokens[i]
	 << std::endl;
    }
  // std::cout<< "DONE\n";
  return os;
}

void ParameterList::ExtractValue(PyObject* pvalue,
				 int dictIndex,
				 const char* keyString)
{
  // std::cout << "ExtractValue() start" << std::endl;
  if (!PyList_Check(pvalue))
    return;
  // From the token, find out what data type to expect
  DeclarationManager::DeclarationInfo di = _dm.GetDeclarationInfo(keyString);

  int numElements = PyList_Size(pvalue);
  // std::cout << "Num items in pvalue = " << numElements << std::endl;

  // Prepare the correct storage type since we know what to expect
  std::vector<RtFloat> floatPlaceHolder;
  std::vector<std::string> stringPlaceHolder;
  std::vector<RtInt> integerPlaceHolder;
  FloatParamStorageIter fIter;
  IntegerParamStorageIter iIter;
  StringParamStorageIter sIter;
  switch (di._type) {
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

  for (int parmIndex=0;parmIndex<numElements;parmIndex++) {

    float fParm = 0.0f;
    RtInt iParm = 0;
    std::string sParm;

    PyObject* item = NULL;
    item = PyList_GetItem(pvalue,parmIndex);
    if (item != NULL) {
      int isString = PyString_Check(item);
      int isInt = PyInt_Check(item);
      int isFloat = PyFloat_Check(item);

      switch (di._type) {
      case DeclarationManager::DeclarationInfo::FLOAT:
      case DeclarationManager::DeclarationInfo::POINT:
      case DeclarationManager::DeclarationInfo::COLOR:
      case DeclarationManager::DeclarationInfo::VECTOR:
      case DeclarationManager::DeclarationInfo::NORMAL:
      case DeclarationManager::DeclarationInfo::MATRIX:
      case DeclarationManager::DeclarationInfo::HPOINT:
	if (isInt) {
	  fParm = static_cast<float>(PyInt_AsLong(item));
	} else if (isFloat) {
	  fParm = static_cast<float>(PyFloat_AsDouble(item));
	}
	_floatParamStorage.back()[parmIndex] = fParm;
	break;
      case DeclarationManager::DeclarationInfo::INTEGER:
	if (isInt) {
	  iParm = static_cast<RtInt>(PyInt_AsLong(item));
	  _integerParamStorage.back()[parmIndex] = iParm;
	} else {
	  std::cerr << "Expecting integer parameter" << std::endl;
	}
	break;
      case DeclarationManager::DeclarationInfo::STRING:
	if (isString) {
	  sParm = PyString_AsString(item);
	  _stringParamStorage.back()[parmIndex] = sParm;
	} else {
	  std::cerr << "Expecting string parameter" << std::endl;
	}
	break;
      default:
	throw std::runtime_error("Unknown type, unable to allocate storage");
      }
    }
  }
  
  // Now update the pointers for the token value pair
  switch (di._type) {
  case DeclarationManager::DeclarationInfo::FLOAT:
  case DeclarationManager::DeclarationInfo::POINT:
  case DeclarationManager::DeclarationInfo::COLOR:
  case DeclarationManager::DeclarationInfo::VECTOR:
  case DeclarationManager::DeclarationInfo::NORMAL:
  case DeclarationManager::DeclarationInfo::MATRIX:
  case DeclarationManager::DeclarationInfo::HPOINT:
    _parms[dictIndex] = &(_floatParamStorage.back()[0]);
    break;
  case DeclarationManager::DeclarationInfo::INTEGER:
    _parms[dictIndex] = &(_integerParamStorage.back()[0]);
    break;
  case DeclarationManager::DeclarationInfo::STRING:
    // _parms[i] = const_cast<char *>(stringParamStorage.back()[0].c_str());
#ifdef FRAGILE_METHOD
    _parms[dictIndex] = &(_stringParamStorage.back()[0]); // Fragile coding?
#else
    _rawCharPtrArray[_numPointers] = new char [_stringParamStorage.back()[0].length() + 1];
    strcpy(_rawCharPtrArray[_numPointers],_stringParamStorage.back()[0].c_str());
    _parms[dictIndex] = &(_rawCharPtrArray[_numPointers]);
    _numPointers++;
#endif // FRAGILE_METHOD
    break;
  default:
    throw std::runtime_error("[3] Unknown type, unable to allocate storage");
  }
}

void ParameterList::ConvertToSTLStringVector(PyObject* stringArray,
					     StringVec& stringVector)
{
  if (stringArray == Py_None)
    return;
  int numValues = PyList_Size(stringArray);
  if (numValues <= 0) {
    return;
  }
  if (numValues != static_cast<int>(stringVector.size())) {
    stringVector.resize(numValues);
  }
  for (int i=0;i<numValues;i++) {
    PyObject* item = NULL;
    item = PyList_GetItem(stringArray,i);
    if (item != NULL) {
      int isString = PyString_Check(item);
      if (isString) {
	std::string s = PyString_AsString(item);
	stringVector[i] = s;
      } else {
	throw std::invalid_argument("Expecting a string value");
      }
    }
  }
}

void ParameterList::ConvertToRtIntVector(PyObject* integerArray,
					 RtIntVector& integerVector)
{
  if (integerArray == Py_None)
    return;
  int numValues = PyList_Size(integerArray);
  if (numValues <= 0) {
    return;
  }
  if (numValues != static_cast<int>(integerVector.size())) {
    integerVector.resize(numValues);
  }
  for (int i=0;i<numValues;i++) {
    PyObject* item = NULL;
    item = PyList_GetItem(integerArray,i);
    if (item != NULL) {
      int isInteger = PyInt_Check(item);
      if (isInteger) {
	RtInt value = PyLong_AsLong(item);
	integerVector[i] = value;
      } else {
	throw std::invalid_argument("Expecting a integer value");
      }
    }
  }
}

void ParameterList::ConvertToRtFloatVector(PyObject* floatArray,
					   RtFloatVector& floatVector)
{
  if (floatArray == Py_None)
    return;
  int numValues = PyList_Size(floatArray);
  if (numValues <= 0) {
    return;
  }
  if (numValues != static_cast<int>(floatVector.size())) {
    floatVector.resize(numValues);
  }
  for (int i=0;i<numValues;i++) {
    PyObject* item = NULL;
    item = PyList_GetItem(floatArray,i);
    if (item != NULL) {
      if (PyFloat_Check(item)) {
	RtFloat value = PyFloat_AsDouble(item);
	floatVector[i] = value;
      } else if (PyInt_Check(item)) {
	RtInt value = PyLong_AsLong(item);
	floatVector[i] = static_cast<float>(value);
      } else {
	throw std::invalid_argument("Expecting a float or int value");
      }
    }
  }
}
