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


class Line {
  
private:
  double fGap;
  bool fisXZ;
  
  TGraphErrors *fTG;
  std::vector<TF1*> fFits;
  std::vector<std::pair<int,int> > fFittedTrack;
  std::pair<std::vector<Track>,std::vector<Track> > fTracks;
  

  std::pair<Track,Track> fBestTracks;
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
  bool do_track_reco(std::vector<Track> tracks_top,std::vector<Track> tracks_bot,double& gap);  
  void fit_tracks();
  void clear_lines();
  bool choose_best();

  void dump();
  
  inline const double slope()     const { return fSlope;     }
  inline const double yinter()    const { return fYinter;    }
  inline const double slopeerr()  const { return fSlopeErr;  }
  inline const double yintererr() const { return fYinterErr; }
  inline const double angle()     const { return fAngle;     }
  inline const double angleerr()  const { return fAngleErr;  }
  inline const double chi()       const { return fChi;       }
  inline const double rchi()      const { return fRChi;      }
  inline const double ndf()       const { return fNdf;       }
  inline const double pvalue()    const { return fPvalue;    }
  inline const double cosangle()  const { return fCosAngle; }
  
  inline const std::pair<Track,Track> get_best_tracks() const { return fBestTracks; }
  
};

#endif
