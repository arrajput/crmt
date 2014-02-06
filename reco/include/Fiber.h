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


class Fiber {

private:
  int fid;
  double fx;
  double fy;
  std::pair<double,double> fCoords;
  int fpixel;
  int fpin;  
  
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
  
  
  inline const int    id()    const { return fid;    }
  inline const double x()     const { return fx;     }
  inline const double y()     const { return fy;     }
  inline const int    pin()   const { return fpin;   }
  inline const int    pixel() const { return fpixel; }   
  
  inline const std::pair<double,double> coords()     const { return fCoords; }
  inline const std::pair<double,double> get_coords() const { return fCoords; }
};

#endif
