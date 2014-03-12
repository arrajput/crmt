//////////////////////////////////////////////////////////////////////
/// \class MCTrack
/// \file MCTrack.h
/// \brief A class which describes the muon track in 3D
/// \author Douglas Davis < douglasdavis@utexas.edu >
//////////////////////////////////////////////////////////////////////

#ifndef MCTRACK_H
#define MCTRACK_H

#include <cmath>
#include <iostream>

namespace sim {

  class MCTrack {
    
  private:
    
    double fTx;        ///< x trajectory unit vector
    double fTy;        ///< y trajectory unit vector
    double fTz;        ///< z trajectory unit vector
    double fX0;        ///< x initial position
    double fY0;        ///< y initial position
    double fZ0;        ///< z initial position
    double fBottomX;   ///< bottom x point for drawing ev3d
    double fBottomY;   ///< bottom y point for drawing ev3d
    double fBottomZ;   ///< bottom z point for drawing ev3d
    double fTheta;     ///< theta, spherical zenith)
    double fPhi;       ///< phi, spherical polar)
    double fAngleXZ;   ///< xz projection zenith angle
    double fAngleYZ;   ///< yz projection zenith angle
    double fSlopeXZ;   ///< xz projection line slope
    double fSlopeYZ;   ///< yz projection line slope
    double fYintXZ;    ///< xz projection line y-int
    double fYintYZ;    ///< yz projection line y-int

  public:

    /// Default constructor
    MCTrack();

    /// Virtual destructor
    virtual ~MCTrack();

    /// Set's the initial position of the muon (x,y,z)
    void SetInitialPos(const double& x, const double& y, const double& z);

    /// Set's the angles in spherical 3D space (phi,theta)
    void SetMCTrackPropertiesFromPhiTheta(const double& phi, const double& theta);

    /// Set's the remaining attributes of the line from Phi and Theta
    void SetMCTrackPropertiesFromAngles();

    /// Manually sets the xz projection angle
    inline void SetAngleXZ(const double& x);

    /// Manually sets the yz projection angle
    inline void SetAngleYZ(const double& y);

    double Tx()      const;
    double Ty()      const;
    double Tz()      const;
    double X0()      const;
    double Y0()      const;
    double Z0()      const;
    double BottomX() const;
    double BottomY() const;
    double BottomZ() const;
    double Theta()   const;
    double Phi()     const;
    double AngleYZ() const;
    double AngleXZ() const;
    double SlopeXZ() const;
    double SlopeYZ() const;
    double YintXZ()  const;
    double YintYZ()  const;

  };

}

inline double sim::MCTrack::Tx()      const { return fTx;      }
inline double sim::MCTrack::Ty()      const { return fTy;      }
inline double sim::MCTrack::Tz()      const { return fTz;      }
inline double sim::MCTrack::X0()      const { return fX0;      }
inline double sim::MCTrack::Y0()      const { return fY0;      }
inline double sim::MCTrack::Z0()      const { return fZ0;      }
inline double sim::MCTrack::BottomX() const { return fBottomX; }
inline double sim::MCTrack::BottomY() const { return fBottomY; }
inline double sim::MCTrack::BottomZ() const { return fBottomZ; }
inline double sim::MCTrack::Theta()   const { return fTheta;   }
inline double sim::MCTrack::Phi()     const { return fPhi;     }
inline double sim::MCTrack::AngleXZ() const { return fAngleXZ; }
inline double sim::MCTrack::AngleYZ() const { return fAngleYZ; }
inline double sim::MCTrack::SlopeXZ() const { return fSlopeXZ; }
inline double sim::MCTrack::SlopeYZ() const { return fSlopeYZ; }
inline double sim::MCTrack::YintXZ()  const { return fYintXZ;  }
inline double sim::MCTrack::YintYZ()  const { return fYintYZ;  }

#endif
