// ======================================================================
//
// Class to define a bounding box in 2D, plus bounding box for measure
//
// History:
//
// 31.08.2001 Mika Heiskanen
//
//	Implemented
//
// ======================================================================

#pragma once

#include <NFmiGlobals.h>

namespace Imagine
{
class NFmiEsriBox
{
 public:
  // Constructors, destructors

  NFmiEsriBox(void);

#ifdef NO_COMPILER_OPTIMIZED
  ~NFmiEsriBox(void);
  NFmiEsriBox(const NFmiEsriBox& theBox);
  NFmiEsriBox& operator=(const NFmiEsriBox& theBox);
#endif

  void Init(void);

  // Data access

  bool IsValid(void) const { return itsValidity; }
  double Xmin(void) const { return itsXmin; }
  double Xmax(void) const { return itsXmax; }
  double Ymin(void) const { return itsYmin; }
  double Ymax(void) const { return itsYmax; }
  double Mmin(void) const { return itsMmin; }
  double Mmax(void) const { return itsMmax; }
  double Zmin(void) const { return itsZmin; }
  double Zmax(void) const { return itsZmax; }
  // Update utilities

  void Update(double theX, double theY, double theM, double theZ);
  void Update(double theX, double theY, double theM);
  void Update(double theX, double theY);

  void Update(const NFmiEsriBox& theBox);

 private:
  bool itsValidity = false;
  double itsXmin = 0.0;
  double itsXmax = 0.0;
  double itsYmin = 0.0;
  double itsYmax = 0.0;
  double itsMmin = 0.0;
  double itsMmax = 0.0;
  double itsZmin = 0.0;
  double itsZmax = 0.0;
};

}  // namespace Imagine

// ======================================================================
