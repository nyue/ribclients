#include "ParameterList.h"

// Google Logging Framework
#include <glog/logging.h>
// #include <vii_logger.h>

// Python version specific handling

#if PY_VERSION_HEX < 0x02050000
typedef int Py_ssize_t;
#endif

/* Warning: This function will allocate a new string in Python 3,
 * so please call SWIG_Python_str_DelForPy3(x) to free the space.
 */
char*
VII_Python_str_AsChar(PyObject *str)
{
#if PY_VERSION_HEX >= 0x03000000
  char *cstr;
  char *newstr;
  Py_ssize_t len;
  str = PyUnicode_AsUTF8String(str);
  PyBytes_AsStringAndSize(str, &cstr, &len);
  newstr = (char *) malloc(len+1);
  memcpy(newstr, cstr, len+1);
  Py_XDECREF(str);
  return newstr;
#else
  return PyString_AsString(str);
#endif
}

#if PY_VERSION_HEX >= 0x03000000
#  define VII_Python_str_DelForPy3(x) free( (void*) (x) )
#else
#  define VII_Python_str_DelForPy3(x) 
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
  DLOG(INFO) << "ProcessParameterList";
  if (parameterlist != Py_None) {
      DLOG(INFO) << "parameterlist is not None";
    if (PyDict_Check(parameterlist)) {
      PyObject* pkey;
      PyObject* pvalue;
      int dictIndex = 0;
      Py_ssize_t ppos = 0; // Initialize to first item
      int nDictItems = PyDict_Size(parameterlist);
      DLOG(INFO) << "nDictItems [NICHOLAS] = " << nDictItems;
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
#if PY_VERSION_HEX >= 0x03000000
        if (!PyUnicode_CheckExact(pkey)) {
#else
        if (!PyString_CheckExact(pkey)) {
#endif // PY_VERSION_HEX >= 0x03000000
	  std::cerr << "Key is not a string" << std::endl;
          return false;
        }
        // Check that value is a list type
        if (!PyList_Check(pvalue)) {
	  std::cerr << "Key is not a list" << std::endl;
          return false;
        }
	
        // Display key
#if PY_VERSION_HEX >= 0x03000000
        char *keyString = VII_Python_str_AsChar(pkey);
#else
        char *keyString = PyString_AsString(pkey);
#endif // PY_VERSION_HEX >= 0x03000000
	DLOG(INFO) << "Key item"
                      << dictIndex
                      << " is a string object = "
                      << keyString
                      << std::endl;
	_tokenStorage[dictIndex] = keyString;

        // Display value
        ExtractValue(pvalue, dictIndex, keyString);
	
	// Now update the pointers for the token string
	_tokens[dictIndex] = const_cast<char*>(_tokenStorage[dictIndex].c_str());

        dictIndex++;

#if PY_VERSION_HEX >= 0x03000000
        VII_Python_str_DelForPy3(keyString);
#endif // PY_VERSION_HEX >= 0x03000000
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
  DLOG(INFO) <<  "DONE";
  return os;
}

void ParameterList::ExtractValue(PyObject* pvalue,
				 int dictIndex,
				 const char* keyString)
{
    DLOG(INFO) << "ExtractValue(" << keyString << ") start";
  if (!PyList_Check(pvalue))
    return;
  // From the token, find out what data type to expect
  DeclarationManager::DeclarationInfo di = _dm.GetDeclarationInfo(keyString);

  int numElements = PyList_Size(pvalue);
  DLOG(INFO) <<  "Num items in pvalue = " << numElements ;

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
#if PY_VERSION_HEX >= 0x03000000
      int isString = PyUnicode_Check(item);
      int isInt = PyLong_Check(item);
#else
      int isString = PyString_Check(item);
      int isInt = PyInt_Check(item);
#endif // PY_VERSION_HEX >= 0x03000000
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
#if PY_VERSION_HEX >= 0x03000000
	  fParm = static_cast<float>(PyLong_AsLong(item));
#else
	  fParm = static_cast<float>(PyInt_AsLong(item));
#endif // PY_VERSION_HEX >= 0x03000000
	} else if (isFloat) {
	  fParm = static_cast<float>(PyFloat_AsDouble(item));
	}
	_floatParamStorage.back()[parmIndex] = fParm;
	break;
      case DeclarationManager::DeclarationInfo::INTEGER:
	if (isInt) {
#if PY_VERSION_HEX >= 0x03000000
	  iParm = static_cast<RtInt>(PyLong_AsLong(item));
#else
	  iParm = static_cast<RtInt>(PyInt_AsLong(item));
#endif // PY_VERSION_HEX >= 0x03000000
	  _integerParamStorage.back()[parmIndex] = iParm;
	} else {
	  std::cerr << "Expecting integer parameter" << std::endl;
	}
	break;
      case DeclarationManager::DeclarationInfo::STRING:
	if (isString) {
#if PY_VERSION_HEX >= 0x03000000
            char *tempStr = VII_Python_str_AsChar(item);
            _stringParamStorage.back()[parmIndex] = tempStr;
            VII_Python_str_DelForPy3(tempStr);
#else
            sParm = PyString_AsString(item);
            _stringParamStorage.back()[parmIndex] = sParm;
#endif // PY_VERSION_HEX >= 0x03000000
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
#if PY_VERSION_HEX >= 0x03000000
      int isString = PyUnicode_Check(item);
#else
      int isString = PyString_Check(item);
#endif // PY_VERSION_HEX >= 0x03000000

      if (isString) {
#if PY_VERSION_HEX >= 0x03000000
          char *tempStr = VII_Python_str_AsChar(item);
          stringVector[i] = tempStr;
          VII_Python_str_DelForPy3(tempStr);
#else
          std::string s = PyString_AsString(item);
          stringVector[i] = s;
#endif // PY_VERSION_HEX >= 0x03000000
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
#if PY_VERSION_HEX >= 0x03000000
      int isInteger = PyLong_Check(item);
#else
      int isInteger = PyInt_Check(item);
#endif // PY_VERSION_HEX >= 0x03000000
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
	RtFloat value = static_cast<RtFloat>(PyFloat_AsDouble(item));
	floatVector[i] = value;
#if PY_VERSION_HEX >= 0x03000000
      } else if (PyLong_Check(item)) {
#else
      } else if (PyInt_Check(item)) {
#endif // PY_VERSION_HEX >= 0x03000000
	RtInt value = PyLong_AsLong(item);
	floatVector[i] = static_cast<float>(value);
      } else {
	throw std::invalid_argument("Expecting a float or int value");
      }
    }
  }
}
