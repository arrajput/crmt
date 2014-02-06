#ifndef TRACK_H
#define TRACK_H

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include "math.h"

#include "TMath.h"

#include "Fiber.h"

class Track {
  
private:
  std::vector<Fiber> fFibers;
  bool fHasOneEach;
  int fid;
  bool fChosen = false;

  
  
public:
  Track();
  virtual ~Track();
  
  void add_fiber(Fiber a);
  void set_id(int a);

  bool contains(Fiber a);
  void dump();
  //void fit();
  //void calculate_angle();
  //void reconstruct();
  void chosen(bool a){fChosen = a;};
  void hasoneeach(bool a);
  //bool is_chosen(){return fChosen;}

  inline const int                id()            const { return fid;            }
  inline const int                size()          const { return fFibers.size(); }
  inline const std::vector<Fiber> fibers()        const { return fFibers;        }
  inline const bool               is_hasoneeach() const { return fHasOneEach;    }

};

#endif
