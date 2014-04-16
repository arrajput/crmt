//////////////////////////////////////////////////////////////////////
/// \file TestVolume.cxx
/// \brief TestVolume class methods
/// \author Douglas Davis < douglasdavis@utexas.edu >
//////////////////////////////////////////////////////////////////////

#include "TestVolume.h"

namespace sim {
  
  TestVolume::TestVolume() {}
  
  TestVolume::TestVolume(const std::string& type, const double& radius) :
    fType(type),
    fRadius(radius),
    fLength(0),
    fHeight(0),
    fWidth(0)
  {
    if ( type != "sphere" ) {
      std::cout << "Test Volume Constructor Bad" << std::endl;
      return;
    }
  }
  
  TestVolume::TestVolume(const std::string& type, const double& length, 
			 const double& width, const double& height) :
    fType(type),
    fRadius(0),
    fLength(length),
    fHeight(height),
    fWidth(width)
  {
    if ( type != "box" ) {
      std::cout << "Test Volume Constructor Bad" << std::endl;
      return;
    }
  }
  
  TestVolume::~TestVolume() {}

  void TestVolume::SetOrigin(const double& x, const double& y, const double& z)
  {
    fXO = x;
    fYO = y;
    fZO = z;
  }
  
}
