///////////////////////////////////////////////////
/// \class Fiber
/// \file Fiber.h
/// \brief
/// \author V. Genty < vic.genty@gmail.com >
///////////////////////////////////////////////////

#ifndef FIBER_H
#define FIBER_H

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <cmath>

namespace reco {

  class Fiber {

  private:

    int                      fid;
    double                   fx;
    double                   fy;
    int                      fpixel;
    int                      fpin;
    std::pair<double,double> fCoords;
  
  public:

    Fiber();
    virtual ~Fiber();
  
    void set_id(int a);
    void set_x(double a);
    void set_y(double a);
    void set_pin(int a);
    void set_pixel(int a);
    void dump();
    bool near(Fiber b);
    void set_coords(std::pair<double,double> coords);
  
    int    id()    const { return fid;    }
    double x()     const { return fx;     }
    double y()     const { return fy;     }
    int    pin()   const { return fpin;   }
    int    pixel() const { return fpixel; }   
  
    const std::pair<double,double>& coords()     const { return fCoords; }
    const std::pair<double,double>& get_coords() const { return fCoords; }

  };

}

#endif
