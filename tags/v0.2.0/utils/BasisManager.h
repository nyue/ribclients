#ifndef _BASISMANAGER_H_
#define _BASISMANAGER_H_

#include <map>
#include <ri.h>

/*!
  \brief Manages the default basis and the creation of new basis
  \remark There are two ways to handle/define basis in the Ruby interface
  via string or number array. String are for predefined basis as defined in
  the specification, number array is for user defined basis.
  \remark All function which process RtBasis parameter should use BasisManager.
  \remark It's important to note that various Ri tokens e.g. RiBezierBasis
  and RiBezierStep are not defined until after RiBegin() is called. Hence
  it is recommended that BasisManager's instance be created after RiBegin()
  \remark I have decided to change the referencing of Basis via integer ids
  rather than string-name
 */
class BasisManager
{
  typedef std::map<int, RtBasis*> RtBasisContainer;
public:
  enum {
    BEZIERBASIS     = -1,
    BSPLINEBASIS    = -2,
    CATMULLROMBASIS = -3,
    HERMITEBASIS    = -4,
    POWERBASIS      = -5
  };

  BasisManager();
  virtual ~BasisManager();

  /*!
    \brief Retrieve a pointer to the predefined basis, if the given basis
    name is not found, it returns the default RiBezierBasis (since the
    RI specification always defaults to RiBezierBasis)
    \param [out] newBasis Pointer to a Basis matrix
    \param [in] basisID Basis identifier
    \li < 0 for predefined and reserved Basis
    \li > 0 for user defined basis
    \li == 0 as marker
    \todo I don't like the RtBasis**, smells funny
   */
  void Get(RtBasis** newBasis,
	   int basisID);

private:
  /*!
    \brief Setup a new basis and associate it with the given basis name
    \param [in] newBasis Basis matrix
    \param [in] basisID Basis identifier
    \todo I don't like the RtBasis*, smells funny
   */
  void Set(RtBasis* newBasis, int basisID);

  /*!
    \brief Initialize the default basis as defined in the RI specifcation.
    \remark Contains implementation specific basis e.g. PRMan RiPowerBasis only
            when build/link with PRMan RIB client library.
    \todo Ensure that the basis name are common or else the lookup will fail
   */
  void Initialize();

  void DebugPrintAll();

  size_t size() const;

  RtBasisContainer _basis;

  int _lastUserBasisID;
};

#endif //  _BASISMANAGER_H_
