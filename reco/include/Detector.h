///////////////////////////////////////////////////
/// \class Detector
/// \file Detector.h
/// \brief
/// \author V. Genty < vic.genty@gmail.com >
///////////////////////////////////////////////////

#ifndef DETECTOR_H 
#define DETECTOR_H

#include <utility>

#include "RecoModule.h"
#include "Line.h"

namespace reco {

  class Detector {
  
  private:
  
    double                           fGap;
    std::vector<RecoModule*>         fModules;
    std::pair<reco::Line,reco::Line> fLines = std::make_pair(reco::Line(true),reco::Line(false));

  public:

    Detector(double gap);
    virtual ~Detector();
  
    void init_modules();
    std::pair<reco::Line,reco::Line> recon_event(std::map<int, std::vector<int> >& eventdata, bool& good);
    void clean_event();

  };

}

#endif
