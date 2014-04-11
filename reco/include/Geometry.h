///////////////////////////////////////////////////
/// \class Geometry
/// \file Geometry.h
/// \brief
/// \author V. Genty < vic.genty@gmail.com >
///////////////////////////////////////////////////

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>

namespace reco {

  class Geometry {

  private:
    std::string fName;
    std::pair<double,double> fLocation[4][64];
  
    double fId;
    double fGap;
  
    double fBottom;
    const double fWidth      = 1.04  ;
    const double fOffset     = 0.3333;
    const double fStopGap    = 0.48  ;
    const double fHalfHeight = 1.54  ;


  public:

    Geometry(const double &id,const double &gap);
    virtual ~Geometry();
  
    void set_coordinates();
    void dump();

    const std::pair<double,double>& location(const int& a, const int& b) const { return fLocation[a][b]; }

    double get_HalfHeight() const { return fHalfHeight; }
    double get_Width()      const { return fWidth;      }
  
  };

}

#endif

