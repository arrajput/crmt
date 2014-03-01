//////////////////////////////////////////////////////////////////////
/// \file crmt.cxx
/// \brief Main file calls classes based on user arguments
/// \author Douglas Davis < douglasdavis@utexas.edu >
//////////////////////////////////////////////////////////////////////

/*! \mainpage The crmt software package (v1.0)
 *
 * \section intro_sec Introduction
 *
 * crmt is a simulation and reconstruction package for the *
 * UTuT detector at UT Austin. <BR>
 * The package is dependent on ROOT (http://root.cern.ch/) and Boost libraries <BR>
 * Tested versions of ROOT, v5-34-10 and later (as of 01/2014) <BR>
 * Tested versions of Boost, v1.55 <BR>
 *
 * \section install_sec Installation and running
 *
 * <BR>
 * === To compile with CMake === <BR>
 * $ mkdir build <BR>
 * $ cd build <BR>
 * $ cmake -DROOT_HOME=$ROOTSYS .. <BR>
 * $ make <BR>
 * <BR>
 * === Running === <BR>
 * (* return back to main directory (cd .. from previous step) *) <BR>
 * execute with: <BR>
 * $ bin/crmt <BR>
 * usage will be displayed <BR>
 * <BR>
 * === Tested Compilers === <BR>
 * * LLVM/Clang 3.3 on OS X <BR>
 * * LLVM/Clang 3.2 on Ubuntu <BR>
 * * GCC g++ 4.8.1 on Ubuntu <BR>
 *
 */

#include <iostream>
#include "TApplication.h"
#include <cstdlib>
#include <stdlib.h>
#include <algorithm>
#include "evd.h"
#include "ev3d.h"
#include "evg.h"
#include "Line.h"
#include "FileManager.h"
#include "Detector.h"
#include "Viewer.h"
#include "TLatex.h"
#include "TStyle.h"
#include "VStyle.h"
#include "boost/program_options.hpp"

int main(int argc, char *argv[])
{

  reco::FileManager *fm = new reco::FileManager();
  namespace po = boost::program_options;
  po::options_description desc("\ncrmt Options.\n\nExample generation:\nTo generate a_file.root with 10000 events:\n  bin/crmt --generate a_file.root --num-events 10000\nTo display the true event display for file output/a_file.root event 53:\n  bin/crmt --display output/a_file.root --true --event-id 53\nExample reconstruction:\nTo reconstruct a_file.root:\n  bin/crmt -r output/a_file.root\nTo view reconstructed event display for a_file.root event 53:\n  bin/crmt -d output/recodata.root -R -e 53\n\nList of options");
  desc.add_options()
    ("help,h","Print help message")
    ("generate,g",po::value<std::string>(),
     "generate events -g output file name, requires --num-events,-n")
    ("display,d",po::value<std::string>(),
     "run the event display -d input file name, requires --event-id,-e and --sim,-s or --true,-t")
    ("true,t","true event display (without multiplexing)")
    ("sim,s","simulated event display (with multiplexing)")
    ("num-events,n",po::value<int>(),"set number of events")
    ("event-id,e",po::value<int>(),"event ID for display")
    ("reco,r",po::value<std::string>(),"reconstruct data file")
    ("reco-display,R","reconstructed event display flag");
  
  po::variables_map vm;
  po::store(po::parse_command_line(argc,argv,desc),vm);
  po::notify(vm);
  
  if ( vm.count("help") ) {
    std::cout << desc << std::endl;
    return 0;
  }
  
  else if ( vm.count("generate") ) {
    if ( vm.count("num-events") ) {
      sim::evg event_set(vm["generate"].as<std::string>(),
			 vm["num-events"].as<int>());
      event_set.RunEvents();
    }
    else
      std::cout << desc << std::endl;
  }
  
  else if ( vm.count("reco") ) {
    int nevents;
    fm->set_raw_data_name(vm["reco"].as<std::string>());
    nevents = fm->get_n_events();
    auto gap = fm->get_gap();
    fm->load_output_data("output/recodata.root");
    reco::Detector *dd = new reco::Detector(gap);
    bool good     = false;
    int  good_cnt = 0;

    for ( int i = 0; i < nevents; ++i ) {
      auto raw_data   = fm->get_raw_data(i);
      auto recon_data = dd->recon_event(raw_data,good);
      if ( good ) {
	fm->fill_event_tree(recon_data,i);
	good_cnt++;
      }
    }
    fm->finish();
  }
  
  else if ( vm.count("display") ) {
    if ( (vm.count("true") || vm.count("sim")) && vm.count("event-id") ) {
      TApplication tapp("tapp",&argc,argv);
      sim::evd display;
      display.InitFile(vm["display"].as<std::string>(),
		       vm["event-id"].as<int>());
      if ( vm.count("true") ) {
	Draw3DGL(vm["display"].as<std::string>(),true,vm["event-id"].as<int>());
	display.DrawTrue(); 
	tapp.Run();
      }
      else if ( vm.count("sim") ) {
	Draw3DGL(vm["display"].as<std::string>(),false,vm["event-id"].as<int>());
	display.DrawSim();
	tapp.Run();
      }
      else
	std::cout << desc << std::endl;
    }

    else if ( (vm.count("reco-display")) && (vm.count("event-id")) ) {
      set_style();
      const auto event = vm["event-id"].as<int>();
      auto file_name_arg = vm["display"].as<std::string>();
      fm->setup_reco_viewer(file_name_arg,event);
      auto gap = fm->get_gap();
      reco::Viewer *vv = new reco::Viewer(gap,fm->get_slope_yinter(),fm->get_hit_points());
      vv->setup();
      fm->print_reco_results();
      fm->print_sim_event();
      TApplication tapp("tapp",&argc,argv);
      TCanvas *can = new TCanvas("tgModules","tgModules",1300,570);
      TPad *padXZ = new TPad("padXZ","padXZ",0.0,0.0,0.5,1.0);
      TPad *padYZ = new TPad("padYZ","padYZ",0.5,0.0,1.0,1.0);
  
      padXZ->cd();
      TMultiGraph *tmgXZ = new TMultiGraph();
    
      tmgXZ->Add(vv->get_modules(1));
      tmgXZ->Add(vv->get_modules(3));
    
      vv->get_hit_points().first->SetMarkerStyle(8);
      tmgXZ->Add(vv->get_hit_points().first);
      tmgXZ->Draw("AP");
      (vv->get_recolines().first)->Draw("SAMES");
      tmgXZ->SetTitle(";z#rightarrow;x#rightarrow");
    
    
      padYZ->cd();
      TMultiGraph *tmgYZ = new TMultiGraph();
      tmgYZ->Add(vv->get_modules(0));
      tmgYZ->Add(vv->get_modules(2));
      vv->get_hit_points().second->SetMarkerStyle(8);
      tmgYZ->Add(vv->get_hit_points().second);
      tmgYZ->Draw("AP");
      (vv->get_recolines().second)->Draw("SAMES");

      tmgYZ->SetTitle(";z#rightarrow;y#rightarrow");
  
      can->cd();
      padXZ->Draw();
      padYZ->Draw();
    
      //Give TMultiGraph Axis
      padXZ->cd();
      tmgXZ->GetXaxis()->CenterTitle();
      tmgXZ->GetYaxis()->CenterTitle();
      TPaveText *XZ_title = new TPaveText(0.36,.93,.7,.95,"brNDC");
      XZ_title->SetTextSize(22);
      XZ_title->SetTextFont(63);
      XZ_title->SetBorderSize(0);
      XZ_title->SetFillColor(0);
      XZ_title->AddText("XZ plane");
      XZ_title->Draw();
      padXZ->Update();
      padXZ->Modified();
     
      padYZ->cd();
      tmgYZ->GetXaxis()->CenterTitle();
      tmgYZ->GetYaxis()->CenterTitle();
      TPaveText *YZ_title = new TPaveText(0.36,.93,.7,.95,"brNDC");
      YZ_title->SetTextSize(22);
      YZ_title->SetTextFont(63);
      YZ_title->SetBorderSize(0);
      YZ_title->SetFillColor(0);
      YZ_title->AddText("YZ plane");
      YZ_title->Draw();
      padYZ->Update();
      padYZ->Modified();
    
      tapp.Run();

    }

    else
      std::cout << desc << std::endl;
  }
  
  else
    std::cout << desc << std::endl;

  return 0;
}

