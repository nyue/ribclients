/*
 * Copyright Procedural Insight 2006
 * Author Nicholas Yue
 */

#ifndef DECLARATIONMANAGER_H
#define DECLARATIONMANAGER_H

#ifdef _WIN32
#pragma warning( disable : 4786)
#endif // _WIN32

#include <string>
#include <map>
#include <vector>
#include <iostream>

/*!
  Manages the types declare via the RIBclient C-API
  called RiDeclare(). Non standard types need to be
  declared so that the API can determine storage
  requirement because data are passed by 1-dimensional
  array

  \brief Manages data types used within the RIB client
  and provide methods to query information of types and
  methods for declaring new types

  \note Ultimately, this class may not be necessary but
  at this moment, I thought I'd better sketch this out
  as I see a potential need for it. It is hope that since
  we have a one-to-one mapping of from Ruby to the C-API
  function RiDeclare(), it can make this class unnecessary.
 */
class DeclarationManager
{
public:
  struct DeclarationInfo
  {
    enum StorageClass { UNKNOWN_CLASS,
                        CONSTANT,
                        UNIFORM,
                        VARYING,
                        VERTEX,
                        FACEVARYING,
                        FACEVERTEX};
    enum StorageType { UNKNOWN_TYPE,
                       FLOAT,
                       INTEGER, 
                       STRING,
                       COLOR,
                       POINT,
                       VECTOR,
                       NORMAL,
                       MATRIX,
                       HPOINT };
    DeclarationInfo()
    : _class(UNKNOWN_CLASS)
    , _type(UNKNOWN_TYPE)
    , _arraysize(0)
    {
    }
    friend std::ostream& operator <<(std::ostream &os,
                                     const DeclarationInfo &obj)
    {
      os << "DeclarationInfo: class detail=";
      switch(obj._class)
        {
        case CONSTANT:
          os << "constant";
          break;
        case UNIFORM:
          os << "uniform";
          break;
        case VARYING:
          os << "varying";
          break;
        case VERTEX:
          os << "vertex";
          break;
        case FACEVARYING:
          os << "facevarying";
          break;
        case FACEVERTEX:
          os << "facevertex";
          break;
        default:
          os << "unknown";
        }
      os << " type=";
      switch (obj._type)
        {
        case FLOAT:
          os << "float";
          break;
        case STRING:
          os << "string";
          break;
        case VECTOR:
          os << "vector";
          break;
        case POINT:
          os << "point";
          break;
        default:
          os << "unknown";
        }
      os << " arraysize=" << obj._arraysize;
      return os;
    }
    // std::string _name;
    StorageClass _class;
    StorageType _type;
    size_t _arraysize;
  };
  typedef std::map<std::string,DeclarationInfo> DIContainer;
  typedef DIContainer::const_iterator DIC_ConstIter;
  typedef DIContainer::iterator DIC_Iter;
  typedef std::vector< std::string > StringArray;
public:
  DeclarationManager();
  virtual ~DeclarationManager();

  /*!
    \param typeName Name of the type being declared
    \param typeDeclaration Declaration information of the type
    \note Example: Declare("stz","uniform float[2]");
   */
  void Declare(const std::string& typeName,
               const std::string& typeDeclaration);

  /*
    \param tokenStr Retrieve the declaration structure from the given tokenStr
    \note This will handle embedded/implicit declaration e.g.
    \li "uniform float decay"
    \li "uniform float twistVector[3]"
    \li "float threshold" (assuming varying storage if storage specifier not provided)
   */
  DeclarationInfo GetDeclarationInfo(const std::string& tokenStr);

private:

  /*!
    \brief Defines default declarations like "P", "N" etc...
   */
  void InitializeDefaultDeclarations();

  /*!
    \brief Dump the internal declaration already defined
    \note Only for debugging purposes
   */
  void DebugDumpDefinedDeclarations() const;

  /*!
    \brief Initializes a DeclarationInfo object from the given string
    \note Algorithm
    \li Find out how many space separated token string is in the input
        parameter typeDeclaration
    \li If it is one, assume the detail is UNIFORM
    \li If not, extract the first token to determine the detail
    \li Check if the end token have the array subscript operator i.e. []
    \li If it does, extract the token between the left and right square
        bracket to determine the size
    \li If not, assume the size is one
   */
  void MakeDeclarationInfo(const std::string& typeDeclaration,
                           DeclarationInfo& di);

  /*!
    \brief Tokenize an STL string into an vector of tokens
    \note From http://www.digitalpeer.com/id/simple
    \param str Input string to be tokenize
    \param delimiters Delimiter used for tokenizing the input string
    \return std::vector<std::string> Array of tokens
   */
  std::vector<std::string> TokenizeDeclaration(const std::string& str,
					       const std::string& delimiters);

  /*!
    \brief Extract the storage detail associated with the declaration
   */
  DeclarationInfo::StorageClass String2Class(const std::string& detailStr);

  
  /*!
    \brief Extract the storage type associated with the declaration
   */
  DeclarationInfo::StorageType String2Type(const std::string& typeStr);

  DIContainer _diContainer; ///< Container for declaration (both default and user define BUT not embedded declaration)
};

#endif // DECLARATIONMANAGER_H

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
