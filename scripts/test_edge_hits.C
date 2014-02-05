{
  TFile *the_file = new TFile("../output/sdf.root","READ");
  TTree *the_tree = (TTree*)the_file->Get("SimulationTree");
  bool Coincidence;
  bool IdentifierHit[4];
  bool SimMod0[256];
  bool SimMod1[256];
  bool SimMod2[256];
  bool SimMod3[256];
  the_tree->SetBranchAddress("IdentifierHit",IdentifierHit);
  the_tree->SetBranchAddress("SimMod0",      SimMod0);
  the_tree->SetBranchAddress("SimMod1",      SimMod1);
  the_tree->SetBranchAddress("SimMod2",      SimMod2);
  the_tree->SetBranchAddress("SimMod3",      SimMod3);
  the_tree->SetBranchAddress("Coincidence", &Coincidence);
  for ( unsigned int i = 0; i < the_tree->GetEntries(); ++i ) {
    the_tree->GetEntry(i);
    int counter0 = 0;
    int counter1 = 0;
    int counter2 = 0;
    int counter3 = 0;
    if ( IdentifierHit[1] && IdentifierHit[2] && IdentifierHit[0] && IdentifierHit[3] && Coincidence) {
      for ( unsigned int j = 64; j < 128; j++ ) {
	if ( SimMod0[j] )
	  counter0++;
	if ( SimMod1[j] )
	  counter1++;
	if ( SimMod2[j] )
	  counter2++;
	if ( SimMod3[j] )
	  counter3++;
      }
      if ( counter0 == 0 || counter1 == 0 || counter2 == 0 || counter3 == 0 )
	cout << i << endl;
    }
  }
}
