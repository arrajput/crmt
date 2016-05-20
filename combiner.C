/*   Merge a number of .root files into one output file.
   *
   * Execute the function like this from the command line:
   *
   * echo outputfile.root input1.root input2.root... | root -b -l combiner.C
   *
   */

#include <string>
#include <iostream>

  #include "TList.h"
  #include "TFile.h"
  #include "TTree.h"

  // Change this line if your TTree has a different name
  const char *Tree1 = "Event Tree XZ";
  const char *Tree2 = "Event Tree YZ";
  const char *Tree3 = "Event Tree 3D"; 

void combiner(){

    using namespace std;

    string outfile;
    cin >> outfile;

    TList tree_list1;
    TList tree_list2;
    TList tree_list3;
    std::string filename;

    Int_t total_events = 0;

    while(cin >> filename) {

      TFile *f = new TFile(filename.c_str());

      TTree *tree1 = (TTree*)f->Get(Tree1);
      TTree *tree2 = (TTree*)f->Get(Tree2);
      TTree *tree3 = (TTree*)f->Get(Tree3);
      
      cout << "Adding file: " << filename << endl;

      tree_list1.Add(tree1);
      tree_list2.Add(tree2);
      tree_list3.Add(tree3);

      total_events += (Int_t)tree2->GetEntries();
    }

    cout << "Opening output file: " << outfile << endl;
    TFile output(outfile.c_str(), "RECREATE");

    cout << "Merging trees now..." << endl;
    TTree::MergeTrees(&tree_list1);
    TTree::MergeTrees(&tree_list2);
    TTree::MergeTrees(&tree_list3);
    output.Write();
    output.Close();

    cout << "Total Events: " << total_events << endl;

}
