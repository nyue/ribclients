#include "DeclarationManager.h"
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>

#include <vii_logger.h>

DeclarationManager::DeclarationManager()
{

  InitializeDefaultDeclarations();

#ifdef DEBUG
  DebugDumpDefinedDeclarations();
#endif // DEBUG
}

DeclarationManager::~DeclarationManager()
{
}

void DeclarationManager::Declare(const std::string& typeName,
				 const std::string& typeDeclaration)
{
  // Check if it is in the default declaration first
  DeclarationInfo di;
  MakeDeclarationInfo(typeDeclaration,di);
  DIC_Iter i = _diContainer.find(typeName);
  if (i != _diContainer.end() )
  {
    VII_LOG(INFO,"Re-declaring " << typeName.c_str());
    // Re-declaration
    i->second = di;
  }
  else
  {
    VII_LOG(INFO,"Declaring " << typeName.c_str());
    // New declaration
    _diContainer[typeName] = di;
  }
  VII_LOG(INFO,"_diContainer has " << _diContainer.size() << " items ");
}

void DeclarationManager::InitializeDefaultDeclarations()
{
  std::string p_str;
  std::string f_str;

  // RIB output
  p_str = "format";
  f_str = "string";
  Declare(p_str,f_str);

  p_str = "compression";
  f_str = "string";
  Declare(p_str,f_str);

  // Geometry
  p_str = "P";
  f_str = "point";
  Declare(p_str,f_str);

  p_str = "Pw"; // For NURBS curve and surface
  f_str = "float[4]";
  Declare(p_str,f_str);

  p_str = "N";
  f_str = "normal";
  Declare(p_str,f_str);

  p_str = "Z";
  f_str = "float";
  Declare(p_str,f_str);

  p_str = "st";
  f_str = "float[2]";
  Declare(p_str,f_str);

  // Display
  p_str = "fov";
  f_str = "float";
  Declare(p_str,f_str);

  p_str = "quantize";
  f_str = "float[4]";
  Declare(p_str,f_str);

  // Lights
  p_str = "intensity";
  f_str = "float";
  Declare(p_str,f_str);

  p_str = "from";
  f_str = "float[3]";
  Declare(p_str,f_str);

  p_str = "to";
  f_str = "float[3]";
  Declare(p_str,f_str);

  p_str = "lightcolor";
  f_str = "color";
  Declare(p_str,f_str);

  // Shaders
  p_str = "Kd";
  f_str = "float";
  Declare(p_str,f_str);
  p_str = "Ka";
  f_str = "float";
  Declare(p_str,f_str);
  p_str = "Ks";
  f_str = "float";
  Declare(p_str,f_str);
  p_str = "texturename";
  f_str = "string";
  Declare(p_str,f_str);

  p_str = "Cs";
  f_str = "color";
  Declare(p_str,f_str);
  p_str = "Os";
  f_str = "color";
  Declare(p_str,f_str);

  // Width/ConstantWidth
  p_str = "width";
  f_str = "float";
  Declare(p_str,f_str);
  p_str = "constantwidth";
  f_str = "float";
  Declare(p_str,f_str);

  // Attribute
  p_str = "name";
  f_str = "string";
  Declare(p_str,f_str);
}

void
DeclarationManager::MakeDeclarationInfo(const std::string& typeDeclaration,
                                        DeclarationInfo& di)
{
  VII_LOG(INFO,"MakeDeclarationInfo start processing \""
                << typeDeclaration.c_str() << "\"");
  std::string delimiters(" ");
  
  std::vector<std::string> tokens =
    TokenizeDeclaration(typeDeclaration,delimiters);

  size_t numTokens = tokens.size();
  std::string typeString;

  if (numTokens == 1)
  {
    di._class = DeclarationInfo::VARYING;
    VII_LOG(INFO,"numTokens == 1, assuming VARYING, type = "
                  << tokens[0].c_str());
    typeString = tokens[0];
  }
  else if (numTokens == 2)
  {
    di._class = String2Class(tokens[0]);
    VII_LOG(INFO,"numTokens == 2, detail = "
                  << tokens[0].c_str()
                  << ", type = "
                  << tokens[1].c_str());
    typeString = tokens[1];
  } else
    return;

  // Process the type
  // Find the first word before the character '[' or until the end of the string
  // Determine the type from this word
  size_t startPosition = typeString.find("[");
  if (startPosition == std::string::npos)
  {
    // Nothing found, extract the whole word
    // printf("typeString = %s\n",typeString.c_str());
    di._type = String2Type(typeString);
    di._arraysize = 0; // scalar
  }
  else
  {
    // This is an array, find out the array size
    size_t endPosition = typeString.rfind("]");
    std::string sizeString = typeString.substr(startPosition + 1,endPosition - startPosition - 1);
    std::string typeName = typeString.substr(0,startPosition);
    di._arraysize = atoi(sizeString.c_str());
    // printf("MakeDeclarationInfo %s[%d]\n",typeName.c_str(),di._size);
    di._type = String2Type(typeName);
  }
  VII_LOG(INFO,"MakeDeclarationInfo : numTokens " << numTokens);
}

DeclarationManager::DeclarationInfo
DeclarationManager::GetDeclarationInfo(const std::string& tokenStr)
{
  DeclarationInfo di;
  std::string delimiter(" ");
  std::vector< std::string > tokenStrComponents = TokenizeDeclaration(tokenStr,delimiter);
  size_t numTokenComponents = tokenStrComponents.size();
  std::string declStr;
  VII_LOG(INFO,"tokenStr is " << tokenStr.c_str());
  VII_LOG(INFO,"numTokenComponents " << numTokenComponents);
  if (numTokenComponents>1)
    {
// #ifdef DEBUG (can we check Log4cxx debug conditionally ?)
      for (size_t i=0;i<numTokenComponents;i++) {
        VII_LOG(INFO,"tokenStrComponents[" << i << "] is "
                      << tokenStrComponents[i]);
      }
// #endif
      if (numTokenComponents == 2)
        {
          declStr = tokenStrComponents[0];
        }
      else if (numTokenComponents == 3)
        {
          declStr = tokenStrComponents[0] + " " + tokenStrComponents[1];
        }
      else
        {
          throw std::runtime_error("Degenerated embedded declaration");
        }
      MakeDeclarationInfo(declStr,di);
    }
  else
    {
      VII_LOG(INFO,"Searching for default token declarations : "
                    << tokenStr.c_str());
      DIC_ConstIter iter;
      iter = _diContainer.find(tokenStr);
      if (iter != _diContainer.end()) {
          di = iter->second;
      } else {
        throw std::runtime_error("Unknown token \"" + tokenStr + "\"");
      }
    }
  return di;
}

std::vector<std::string> DeclarationManager::TokenizeDeclaration(const std::string& str,
								 const std::string& delimiters)
{
  std::vector<std::string> tokens;
        
  // skip delimiters at beginning.
  std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
        
  // find first "non-delimiter".
  std::string::size_type pos = str.find_first_of(delimiters, lastPos);

  while (std::string::npos != pos || std::string::npos != lastPos)
  {
    // found a token, add it to the vector.
    tokens.push_back(str.substr(lastPos, pos - lastPos));
                
    // skip delimiters.  Note the "not_of"
    lastPos = str.find_first_not_of(delimiters, pos);
                
    // find next "non-delimiter"
    pos = str.find_first_of(delimiters, lastPos);
  }

  return tokens;
}

DeclarationManager::DeclarationInfo::StorageClass
DeclarationManager::String2Class(const std::string& detailStr)
{
  // constant, uniform, varying, vertex, facevarying and facevertex
  DeclarationInfo::StorageClass result = DeclarationInfo::UNKNOWN_CLASS;

  if (detailStr == std::string("constant"))
  {
    result = DeclarationInfo::CONSTANT;
  }
  else if (detailStr == std::string("uniform"))
  {
    result = DeclarationInfo::UNIFORM;
  }
  else if (detailStr == std::string("varying"))
  {
    result = DeclarationInfo::VARYING;
  }
  else if (detailStr == std::string("vertex"))
  {
    result = DeclarationInfo::VERTEX;
  }
  else if (detailStr == std::string("facevarying"))
  {
    result = DeclarationInfo::FACEVARYING;
  }
  else if (detailStr == std::string("facevertex"))
  {
    result = DeclarationInfo::FACEVERTEX;
  }

  return result;
}

DeclarationManager::DeclarationInfo::StorageType
DeclarationManager::String2Type(const std::string& typeStr)
{
  DeclarationInfo::StorageType result = DeclarationInfo::UNKNOWN_TYPE;
  VII_LOG(INFO,"String2Type typeStr = " << typeStr.c_str());
  if (typeStr == std::string("float"))
  {
    result = DeclarationInfo::FLOAT;
  }
  else if (typeStr == std::string("int"))
  {
    result = DeclarationInfo::INTEGER;
  }
  else if (typeStr == std::string("string"))
  {
    result = DeclarationInfo::STRING;
  }
  else if (typeStr == std::string("color"))
  {
    result = DeclarationInfo::COLOR;
  }
  else if (typeStr == std::string("point"))
  {
    result = DeclarationInfo::POINT;
  }
  else if (typeStr == std::string("vector"))
  {
    result = DeclarationInfo::VECTOR;
    VII_LOG(INFO,"String2Type found VECTOR");
  }
  else if (typeStr == std::string("normal"))
  {
    result = DeclarationInfo::NORMAL;
  }
  else if (typeStr == std::string("matrix"))
  {
    result = DeclarationInfo::MATRIX;
  }
  else if (typeStr == std::string("hpoint"))
  {
    result = DeclarationInfo::HPOINT;
  }

  return result;
}

void DeclarationManager::DebugDumpDefinedDeclarations() const
{
  std::cout << "DebugDumpDefinedDeclarations: START" << std::endl;
  std::cout << "_diContainer has "
            << _diContainer.size() << " items "
            << std::endl;
  DIC_ConstIter ei = _diContainer.end();
  for (DIC_ConstIter i=_diContainer.begin(); i!=ei; ++i)
    {
      std::cout << i->second << std::endl;
    }
  std::cout << "DebugDumpDefinedDeclarations: END" << std::endl;
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
