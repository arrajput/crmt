#include <math.h>

void splitter() { 
  
  //read input file
  TFile input_file("daq_converted.root","READ");

  //read input trees
  TTree *volumetree = (TTree*)input_file.Get("TestVolumeTree");
  TTree *input_tree0 = (TTree*)input_file.Get("Mod0Tree");
  TTree *input_tree1 = (TTree*)input_file.Get("Mod1Tree");
  TTree *input_tree2 = (TTree*)input_file.Get("Mod2Tree");
  TTree *input_tree3 = (TTree*)input_file.Get("Mod3Tree");

  int nentries0 = input_tree0->GetEntries();
  std::clog << " input has " << nentries0 << " entries" << std::endl;
  
  //associate branches to input trees
  double gap;
  volumetree->SetBranchAddress("Gap",&gap);
  
  std::vector<int>HitPinsTop0;
  input_tree0->SetBranchAddress("HitPinsTop0",&(&HitPinsTop0));
  std::vector<int>HitPinsBot0;
  input_tree0->SetBranchAddress("HitPinsBot0",&(&HitPinsBot0));

  std::vector<int>HitPinsTop1;
  input_tree1->SetBranchAddress("HitPinsTop1",&(&HitPinsTop1));
  std::vector<int>HitPinsBot1;
  input_tree1->SetBranchAddress("HitPinsBot1",&(&HitPinsBot1));

  std::vector<int>HitPinsTop2;
  input_tree2->SetBranchAddress("HitPinsTop2",&(&HitPinsTop2));
  std::vector<int>HitPinsBot2;
  input_tree2->SetBranchAddress("HitPinsBot2",&(&HitPinsBot2));
  
  std:vector<int>HitPinsTop3;
  input_tree3->SetBranchAddress("HitPinsTop3",&(&HitPinsTop3));
  std:vector<int>HitPinsBot3;
  input_tree3->SetBranchAddress("HitPinsBot3",&(&HitPinsBot3));

  //loop over input trees
  int Nentries = 10000;
  int Nfiles = floor(nentries0/Nentries + 0.5);
  
  for(int iFile = 0; iFile<=Nfiles; iFile++){ 
      // make output file
      TFile output_file(Form("daq_split_%i.root",iFile),"RECREATE");
      
      // make output trees
      TTree *modtree0 = new TTree("Mod0Tree","Mod0Tree");
      TTree *modtree1 = new TTree("Mod1Tree","Mod1Tree");
      TTree *modtree2 = new TTree("Mod2Tree","Mod2Tree");
      TTree *modtree3 = new TTree("Mod3Tree","Mod3Tree");
      
      TTree *testvoltree = new TTree("TestVolumeTree","TestVolumeTree");
      double gapn = 411;
      testvoltree->Branch("Gap",&gapn);
      testvoltree->Fill();
      testvoltree->Write();
      
      //create branches for output trees
      
      std::vector<int>HitPinsTop0n;
      modtree0->Branch("HitPinsTop0",&(&HitPinsTop0));
      std::vector<int>HitPinsBot0n;
      modtree0->Branch("HitPinsBot0",&(&HitPinsBot0)); 

      std::vector<int>HitPinsTop1n;
      modtree1->Branch("HitPinsTop1",&(&HitPinsTop1));
      std::vector<int>HitPinsBot1n;
      modtree1->Branch("HitPinsBot1",&(&HitPinsBot1));

      std::vector<int>HitPinsTop2n;
      modtree2->Branch("HitPinsTop2",&(&HitPinsTop2));
      std::vector<int>HitPinsBot2n;
      modtree2->Branch("HitPinsBot2",&(&HitPinsBot2));

      std::vector<int>HitPinsTop3n;
      modtree3->Branch("HitPinsTop3",&(&HitPinsTop3));
      std::vector<int>HitPinsBot3n;
      modtree3->Branch("HitPinsBot3",&(&HitPinsBot3));
     
      //loop for splitting entries
      for(int i = 0; i<Nentries; i++){ 

	int ientry = Nentries*iFile + i ;
	
        if(ientry<nentries0){

	  input_tree0->GetEntry(ientry);
	  modtree0->Fill();

	  input_tree1->GetEntry(ientry);
	  modtree1->Fill();

	  input_tree2->GetEntry(ientry);
	  modtree2->Fill();

	  input_tree3->GetEntry(ientry);
	  modtree3->Fill();
	  	  
	     
	}//if statement
	
	
      }//2nd for loop over entries
         
     modtree0->Write();
     modtree1->Write();
     modtree2->Write();
     modtree3->Write();

     output_file.Close();


  }//1st for loop over trees       

 }//end file
