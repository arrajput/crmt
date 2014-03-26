///////////////////////////////////////////////////
/// \class Line
/// \file Line.h
/// \brief
/// \author V. Genty < vic.genty@gmail.com >
///////////////////////////////////////////////////

#ifndef LINE_H 
#define LINE_H


#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include "math.h"


#include "TGraphErrors.h"
#include "TF1.h"
#include "TMath.h"

#include "Track.h"

namespace reco {

  class Line {
  
  private:
    double fGap;
    bool fisXZ;
  
    TGraphErrors *fTG;
    std::vector<TF1*> fFits;
    std::vector<std::pair<int,int> > fFittedTrack;
    std::pair<std::vector<reco::Track>,std::vector<reco::Track> > fTracks;
  

    std::pair<reco::Track,reco::Track> fBestTracks;
    TF1 *fBestLine;
    double fSlope;
    double fYinter;
    double fSlopeErr;
    double fYinterErr;
  

    double fAngle;
    double fAngleErr;
    double fCosAngle;
    double fChi;
    double fRChi;
    double fNdf;

    double fPvalue;
  
    int fLowCnt;
  
  public:
    Line(bool isXZ);
    virtual ~Line();
    bool do_track_reco(std::vector<reco::Track> tracks_top,std::vector<reco::Track> tracks_bot,double& gap);  
    void fit_tracks();
    void clear_lines();
    bool choose_best();

    void dump();
  
    inline double slope()     const { return fSlope;     }
    inline double yinter()    const { return fYinter;    }
    inline double slopeerr()  const { return fSlopeErr;  }
    inline double yintererr() const { return fYinterErr; }
    inline double angle()     const { return fAngle;     }
    inline double angleerr()  const { return fAngleErr;  }
    inline double chi()       const { return fChi;       }
    inline double rchi()      const { return fRChi;      }
    inline double ndf()       const { return fNdf;       }
    inline double pvalue()    const { return fPvalue;    }
    inline double cosangle()  const { return fCosAngle; }
  
    inline const std::pair<reco::Track,reco::Track>& get_best_tracks() const { return fBestTracks; }
  
  };

}

#endif
