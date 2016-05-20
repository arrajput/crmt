
/*run macro in the terminal with the following command template:

  echo outputfilename.root inputfilename.root | root -b -l convert_daq_to_simulation_data.C 

*/

#include <string>
#include <iostream>
#include "TFile.h"
#include "TTree.h"

void convert_daq_data_to_simulation_data(){

  // read input file
  
  using namespace std;
  string outputfile;
  cin >> outputfile;
  std::string inputfilename;
  cin >> inputfilename;
  std::clog << "input file name is " << inputfilename << std::endl;
  
  TFile *input_file = new TFile(inputfilename.c_str());

  // read input tree

  TTree *input_tree = (TTree*)input_file->Get("data_tree");
  
  int nentries = input_tree->GetEntries();
  std::clog << " input has " << nentries << " nentries " << std::endl;
  
  // associate variables to input tree

  int nsignals_;
  input_tree->SetBranchAddress("nsignals",&nsignals_);
  int nchannels_per_event_[1000];
  input_tree->SetBranchAddress("nchannels_per_event",nchannels_per_event_);
  int event_number_[1000];
  input_tree->SetBranchAddress("event_number",event_number_);
  int packet_number_[1000];
  input_tree->SetBranchAddress("packet_number",packet_number_);
  Bool_t type_[1000];
  input_tree->SetBranchAddress("type",type_);
  int board_address_[1000];
  input_tree->SetBranchAddress("board_address",board_address_);
  Double_t time_[1000];
  input_tree->SetBranchAddress("time",time_);
  Double_t n_layers_;
  input_tree->SetBranchAddress("n_layers",&n_layers_);
  int channels_[1000][128];
  input_tree->SetBranchAddress("channels",channels_);

  // make output file

  TFile output_file(outputfile.c_str(), "RECREATE");
  
  // make output trees

  TTree *modtree0 = new TTree("Mod0Tree","Mod0Tree");
  TTree *modtree1 = new TTree("Mod1Tree","Mod1Tree");
  TTree *modtree2 = new TTree("Mod2Tree","Mod1Tree");
  TTree *modtree3 = new TTree("Mod3Tree","Mod3Tree");

  // edit physical module separation value 
  
  TTree *testvoltree = new TTree("TestVolumeTree","TestVolumeTree");
  double _gap;
  testvoltree->Branch("Gap",&_gap);
  _gap = 409.575; //set accordingly in millimeters so the reco will be correct
  testvoltree->Fill();
  testvoltree->Write();

  /* TTree *timetree = new TTree("TimeTree","TimeTree");
  std::vector<double> times;
  timetree->Branch("Times",&times);

  std::vector<double> event_numbers;
  timetree->Branch("Event_number",&event_numbers);*/
  

  // associate branches to output trees

  std::vector<int>HitPinsTop0;
  modtree0->Branch("HitPinsTop0",&HitPinsTop0);
  std::vector<int>HitPinsBot0;
  modtree0->Branch("HitPinsBot0",&HitPinsBot0);

  std::vector<int>HitPinsTop1;
  modtree1->Branch("HitPinsTop1",&HitPinsTop1);
  std::vector<int>HitPinsBot1;
  modtree1->Branch("HitPinsBot1",&HitPinsBot1);
  
  std::vector<int>HitPinsTop2;
  modtree2->Branch("HitPinsTop2",&HitPinsTop2);
  std::vector<int>HitPinsBot2;
  modtree2->Branch("HitPinsBot2",&HitPinsBot2);

  std::vector<int>HitPinsTop3;
  modtree3->Branch("HitPinsTop3",&HitPinsTop3);
  std::vector<int>HitPinsBot3;
  modtree3->Branch("HitPinsBot3",&HitPinsBot3);

  // loop over input tree
  for(int ientry=0; ientry<nentries; ientry++){

    // load input values into variables
    input_tree->GetEntry(ientry); 

    HitPinsBot0.clear();
    HitPinsTop0.clear();
    HitPinsBot1.clear();
    HitPinsTop1.clear();
    HitPinsBot2.clear();
    HitPinsTop2.clear();
    HitPinsBot3.clear();
    HitPinsTop3.clear();

    // convert input to output based on the pins that were hit
     for(size_t is=0; is<nsignals_; is++){

       /*if( is >= 1000 ){
	
	 std::clog << " problem: is " << is << std::endl;
	break;
	}*/

       // times.push_back(time_[is]);
       // event_numbers.push_back(event_number_[is]);

      for(size_t ich=0; ich<nchannels_per_event_[is]; ich++){

	if( ich >= 128 ){
	  std::clog << " problem: ich " << ich << std::endl;
	  break;
	}


	int the_channel = channels_[is][ich];
	int q  = ((the_channel-1)/32.);
	int r = (the_channel-1)%32;
	if (q == 0 ){
	  if(r <= 15  && r >= 0)
	    HitPinsTop0.push_back(r);
	  else if(r>=16 && r <=31)
	    HitPinsBot0.push_back(r);
	}
	
	if (q == 1 ){
	  if(r <= 15  && r >= 0)
	    HitPinsTop1.push_back(r);
	  else if(r>=16 && r <=31)
	    HitPinsBot1.push_back(r);
	}
	
	if (q == 2){
	  if(r <= 15 && r>=0)
	    HitPinsTop2.push_back(r);
	  else if(r>=16 && r<=31)
	    HitPinsBot2.push_back(r);
	}
	
	if (q == 3){
	  if(r <= 15 && r>=0)
	    HitPinsTop3.push_back(r);
	  else if(r>=16 && r <=31)
	    HitPinsBot3.push_back(r);
	}

	// std::cout << " q " << q << " r " << r << " ch " << the_channel << std::endl;

	//std::clog << " is " << is << " ich " << ich << " channel " << the_channel << " q " << q << " r " << r << std::endl;
	
	}// loop on input channels from a board

     } // loop on input signals (boards in coincidence)

    modtree0->Fill();
    modtree1->Fill();
    modtree2->Fill();
    modtree3->Fill();

    // timetree->Fill();
      
  } // loop on input entries

  
  // write output tree

   output_file.cd();  
   modtree0->Write();
   modtree1->Write();
   modtree2->Write();
   modtree3->Write();
  // timetree->Write();
  
  exit(0);
  
}
