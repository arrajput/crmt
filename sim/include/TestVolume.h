//////////////////////////////////////////////////////////////////////
/// \class TestVolume
/// \file TestVolume.h
/// \brief A class which describes a test volume
/// \author Douglas Davis < douglasdavis@utexas.edu >
//////////////////////////////////////////////////////////////////////

#ifndef TESTVOLUME_H
#define TESTVOLUME_H

#include <iostream>

namespace sim {

  class TestVolume {
    
  private:
    
    std::string fType;    ///< test volume type (box or sphere currently suppored)
    double      fRadius;  ///< sphere test volume radius
    double      fLength;  ///< box test volume length (x)
    double      fHeight;  ///< box test volume height (z)
    double      fWidth;   ///< box test volume width (y)
    double      fXO;      ///< test volume x center
    double      fYO;      ///< test volume y center
    double      fZO;      ///< test volume z center
    
  public:
    
    /// Default constructor
    TestVolume();
 
    /// Constructor for a sphere (type, radius)
    TestVolume(const std::string& type, const double& radius);

    /// Constructor for a box (type, length, width, height)
    TestVolume(const std::string& type, const double& length,
	       const double& width, const double& height);

    /// virtual destructor
    virtual ~TestVolume();
    
    /// Set the origin of the test volume
    void SetOrigin(const double& x, const double& y, const double& z);

    double GetLength() const;
    double GetWidth()  const;
    double GetHeight() const;
    double GetRadius() const;
    double GetXO()     const;
    double GetYO()     const;
    double GetZO()     const;

  };

}

inline double sim::TestVolume::GetLength() const { return fLength; }
inline double sim::TestVolume::GetWidth()  const { return fWidth;  }
inline double sim::TestVolume::GetHeight() const { return fHeight; }
inline double sim::TestVolume::GetRadius() const { return fRadius; }
inline double sim::TestVolume::GetXO()     const { return fXO;     }
inline double sim::TestVolume::GetYO()     const { return fYO;     }
inline double sim::TestVolume::GetZO()     const { return fZO;     }

#endif
