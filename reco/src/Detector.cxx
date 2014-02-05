#include "Detector.h"

Detector::Detector(double gap){
  fGap = gap;
  init_modules();
}

Detector::~Detector(){}

void Detector::init_modules() {
  for (int i = 0; i<4; ++i)
    fModules.push_back(new RecoModule(i,fGap));
  
}


std::pair<Line,Line> Detector::recon_event(std::map<int, std::vector<int> >& eventdata,bool& good) {  
  //Clear reco events before new
  clean_event();
  
  good = false;
  for(auto module : eventdata){
    if(fModules[module.first]->check_event(module.second) && eventdata.size() == 4) {
      fModules[module.first]->find_hit_fibers(module.second);
      fModules[module.first]->fill_fibers();
      fModules[module.first]->clusterize();
      fModules[module.first]->attach();
      good = true;
    
    } else {
      good  = false;
      break;
    }
  }
  
  bool goody_mob[2];
  if(good){
    
    goody_mob[0] = fLines.first.do_track_reco(fModules[1]->get_Tracks(),
					      fModules[3]->get_Tracks(),
					      fGap); //XZ
    goody_mob[1] = fLines.second.do_track_reco(fModules[0]->get_Tracks(),
					       fModules[2]->get_Tracks(),
					       fGap); //YZ
  }
  
  if (!goody_mob[0] || !goody_mob[1])
    good = false;
 
  
  return fLines;

}

void Detector::clean_event(){
  
  for(auto module : fModules)
    module->clear();
  
  fLines.first.clear_lines();
  fLines.second.clear_lines();
}
