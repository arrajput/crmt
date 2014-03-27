///////////////////////////////////////////////////
/// \class Track
/// \file Track.h
/// \brief
/// \author V. Genty < vic.genty@gmail.com >
///////////////////////////////////////////////////

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

namespace reco {

  class Track {
  
  private:
    std::vector<reco::Fiber> fFibers;
    bool fHasOneEach;
    int fid;
    bool fChosen = false;

  
  
  public:
    Track();
    virtual ~Track();
  
    void add_fiber(reco::Fiber a);
    void set_id(int a);

    bool contains(reco::Fiber a) const;
    void dump();
    //void fit();
    //void calculate_angle();
    //void reconstruct();
    void chosen(bool a){fChosen = a;};
    void hasoneeach(bool a);
    //bool is_chosen(){return fChosen;}

    inline       int                       id()            const { return fid;            }
    inline       int                       size()          const { return fFibers.size(); }
    inline const std::vector<reco::Fiber>& fibers()        const { return fFibers;        }
    inline       bool                      is_hasoneeach() const { return fHasOneEach;    }

  };

}

#endif
