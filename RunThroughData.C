
#include "TFile.h"
#include "TTree.h"
#include <string>
#include <TMath.h>
#include <math.h>

void EachData (std::string name, TH2F* proj_hist);

void RunThroughData() {
  
  int heightM = 10;
  double planesize = 9000.;
  int nbins = 50;
  
    TH2F *proj_hist = new TH2F("proj_hist", Form("Projection Plane %d Meters Above Old Detector Position",heightM), nbins, -planesize, planesize, nbins, -planesize, planesize);
    TH2F *proj_hist1 = new TH2F("proj_hist1", Form("Projection Plane %d Meters Above New Detector Position", heightM), nbins, -planesize, planesize, nbins, -planesize, planesize);
  
    EachData(heightM,"0degreco.root", proj_hist);
    EachData(heightM,"45degreco1.root",proj_hist1);
    proj_hist->Draw("COLZ");
    
    TCanvas*  other = new TCanvas();
    proj_hist1->Draw("COLZ");

    TH2F *h2 = new TH2F("img_hist", Form("Image of Building at %d Meters", heightM), nbins, -planesize, planesize, nbins, -planesize, planesize);
    
    for(int i = 0; i < h2->GetNbinsX() + 2; i++)
      {  
	for(int j = 0; j < h2->GetNbinsY() + 2; j++)
	{
	  double val1 = proj_hist->GetBinContent(i,j);
	  double val2 = proj_hist1->GetBinContent(i,j);
	  h2->SetBinContent(i,j,log(val1/303723) - log(val2/977543));
	}

      }  

    TCanvas* img = new TCanvas();
    gStyle->SetPalette(55);
    h2->Draw("COLZ");
    h2->GetXaxis()->SetTitle("Image X Direction (mm)");
    h2->GetYaxis()->SetTitle("Image Y Direction (mm)");
    h2->GetXaxis()->CenterTitle();
    h2->GetYaxis()->CenterTitle(); 
    h2->GetYaxis()->SetTitleOffset(1.5);
    h2->GetXaxis()->SetTitleOffset(1.5);
    h2->SetStats(0);
    
}

void EachData (int heightM, std::string name, TH2F* proj_hist) {

    TFile *f = TFile::Open(name.c_str());
    if(f==0) {
        printf("Failed to find file");
        return;
    }

    TTree *XZ_tree = (TTree*)f->Get("Event Tree XZ");
    TTree *YZ_tree = (TTree*)f->Get("Event Tree YZ");

    double x_inter;
    XZ_tree->SetBranchAddress("Yinter",&x_inter);
    double y_inter;
    YZ_tree->SetBranchAddress("Yinter",&y_inter);
    double x_slope;
    XZ_tree->SetBranchAddress("Slope",&x_slope);
    double y_slope;
    YZ_tree->SetBranchAddress("Slope",&y_slope);
      
    int nentries = XZ_tree->GetEntries();

    for(int i = 0; i < nentries; i++) {
        XZ_tree->GetEvent(i);
        YZ_tree->GetEvent(i);

        double x = x_inter + heightM*1000*(x_slope);
        double y = y_inter + heightM*1000*(y_slope);
        proj_hist->Fill(x,y);
	proj_hist->GetXaxis()->SetTitle("Projection Plane X Direction (mm)");
	proj_hist->GetYaxis()->SetTitle("Projection Plane Y Direction (mm)");
	proj_hist->GetXaxis()->CenterTitle();
	proj_hist->GetYaxis()->CenterTitle(); 
	proj_hist->GetYaxis()->SetTitleOffset(1.5);
	proj_hist->GetXaxis()->SetTitleOffset(1.5);
	
    }

}
