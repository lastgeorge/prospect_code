#include "ProspectData/Geometry.h"
#include "ProspectData/Singleton.h"
#include "ProspectData/PIDParams.h"
#include "ProspectData/Bundle.h"
#include "ProspectData/IBD.h"

#include <iostream>
#include <list>
#include <set>

#include "TFile.h"
#include "TString.h"
#include "TTree.h"


using namespace Prospect;
using namespace std;

int main(int argc, char* argv[])
{
  if (argc < 3) {
    cerr << "usage: prospect-process /path/to/dat.root #flag" << endl;
    return 1;
  }else{
   
    
    // define singleton ... 

    PIDParams& pid_cuts = Singleton<PIDParams>::Instance();

    
    std::pair<double,double> IBD_delta_t = pid_cuts.get_delta_t_pd();
      

    
    Geometry& geometry = Singleton<Geometry>::Instance();
    
    // geometry ... 
    
    long long evt;
    float E_total;
    float wPSD;
    double t0;
    int ts_runstart;
    float mE;
    int mSeg;
    float mX;
    float mY;
    float mZ;
    float mPSD;
    std::vector<int> *vSeg = new std::vector<int>;
    std::vector<float> *vE = new std::vector<float>;
    std::vector<float> *vZ = new std::vector<float>;
    std::vector<float> *vPSD = new std::vector<float>;

    TString filename = argv[1];
    int save_file_no = atoi(argv[2]);
    TFile *file = new TFile(filename);
    TTree *T = (TTree*)file->Get("Event");

    T->SetBranchAddress("evt",&evt);
    T->SetBranchAddress("E_total",&E_total);
    T->SetBranchAddress("wPSD",&wPSD);
    T->SetBranchAddress("t0",&t0);
    T->SetBranchAddress("ts_runstart",&ts_runstart);
    T->SetBranchAddress("mE",&mE);
    T->SetBranchAddress("mSeg",&mSeg);
    T->SetBranchAddress("mX",&mX);
    T->SetBranchAddress("mY",&mY);
    T->SetBranchAddress("mZ",&mZ);
    T->SetBranchAddress("mPSD",&mPSD);
    T->SetBranchAddress("vSeg",&vSeg);
    T->SetBranchAddress("vE",&vE);
    T->SetBranchAddress("vZ",&vZ);
    T->SetBranchAddress("vPSD",&vPSD);
    

     
    TFile *file1 = new TFile(Form("temp_%d.root",save_file_no),"RECREATE");
    
    TTree *T_delay = new TTree("T_delay","T_delay");
    T_delay->SetDirectory(file1);

    // TTree *T_prompt = new TTree("T_prompt","T_prompt");
    // T_prompt->SetDirectory(file1);
    
    double delay_seg_E;
    int delay_seg_no;
    double delay_seg_PSD;
    double delay_seg_Z;
    double delay_total_E;
   
    T_delay->Branch("delay_seg_E",&delay_seg_E,"delay_seg_E/D");
    T_delay->Branch("delay_seg_no",&delay_seg_no,"delay_seg_no/I");
    T_delay->Branch("delay_seg_PSD",&delay_seg_PSD,"delay_seg_PSD/D");
    T_delay->Branch("delay_seg_Z",&delay_seg_Z,"delay_seg_Z/D");
    T_delay->Branch("delay_total_E",&delay_total_E,"delay_total_E/D");

    double time_to_prev_muon;
    double time_to_prev_showern;
    double time_to_prev_delay;
    T_delay->Branch("time_to_prev_muon",&time_to_prev_muon,"time_to_prev_muon/D");
    T_delay->Branch("time_to_prev_showern",&time_to_prev_showern,"time_to_prev_showern/D");
    T_delay->Branch("time_to_prev_delay",&time_to_prev_delay,"time_to_prev_delay/D");
    
    double prompt_maxseg_E;
    int prompt_maxseg_no;
    double prompt_maxseg_PSD;
    double prompt_maxseg_Z;
    double prompt_total_E;
    // T_prompt->Branch("prompt_maxseg_E",&prompt_maxseg_E,"prompt_maxseg_E/D");
    // T_prompt->Branch("prompt_maxseg_no",&prompt_maxseg_no,"prompt_maxseg_no/I");
    // T_prompt->Branch("prompt_maxseg_PSD",&prompt_maxseg_PSD,"prompt_maxseg_PSD/D");
    // T_prompt->Branch("prompt_maxseg_Z",&prompt_maxseg_Z,"prompt_maxseg_Z/D");
    // T_prompt->Branch("prompt_total_E",&prompt_total_E,"prompt_total_E/D");

    TTree *T_IBD = new TTree("T_IBD","T_IBD");
    T_IBD->SetDirectory(file1);
    
    T_IBD->Branch("delay_seg_E",&delay_seg_E,"delay_seg_E/D");
    T_IBD->Branch("delay_seg_no",&delay_seg_no,"delay_seg_no/I");
    T_IBD->Branch("delay_seg_PSD",&delay_seg_PSD,"delay_seg_PSD/D");
    T_IBD->Branch("delay_seg_Z",&delay_seg_Z,"delay_seg_Z/D");
    T_IBD->Branch("delay_total_E",&delay_total_E,"delay_total_E/D");
    T_IBD->Branch("prompt_maxseg_E",&prompt_maxseg_E,"prompt_maxseg_E/D");
    T_IBD->Branch("prompt_maxseg_no",&prompt_maxseg_no,"prompt_maxseg_no/I");
    T_IBD->Branch("prompt_maxseg_PSD",&prompt_maxseg_PSD,"prompt_maxseg_PSD/D");
    T_IBD->Branch("prompt_maxseg_Z",&prompt_maxseg_Z,"prompt_maxseg_Z/D");
    T_IBD->Branch("prompt_total_E",&prompt_total_E,"prompt_total_E/D");
    int flag_geometry;
    T_IBD->Branch("flag_geometry",&flag_geometry,"flag_geometry/I");
    double delta_t;
    T_IBD->Branch("delta_t",&delta_t,"delta_t/D");

    TTree *T_sum = new TTree("T_sum","T_sum");
    T_sum->SetDirectory(file1);
    double total_time;
    double total_veto_time;
    T_sum->Branch("total_time",&total_time,"total_time/D");
    T_sum->Branch("total_veto_time",&total_veto_time,"total_veto_time/D");
    
    
    std::cout << "Total Entries: " << T->GetEntries()/1e6 << " M"  << std::endl;
    
    
    
    double start_time;
    double end_time;
    std::vector<std::pair<double,double>> veto_times;
    veto_times.push_back(std::make_pair(0,0));
    
    int showern_count = 0;
    int showern_muon_count = 0;
    
    int delayn_count = 0;

    double prev_muon_time=-1;
    double prev_showern_time=-1;
    double prev_delay_time = -1;
    
    std::list<Bundle*> prompt_list; // save all the prompt

    std::list<Bundle*> delay_list;
    std::list<std::pair<Bundle*, Bundle*>> IBD_list;
    std::set<Bundle*> saved_bundles;
    
    for (int i=0;i!=T->GetEntries();i++){
      if (i%1000000==0) std::cout << "Events: " << i/1000000 << " M" << std::endl;
      T->GetEntry(i);
      if (i==0){
	start_time = t0*units::ns;
      }else if (i==T->GetEntries()-1){
	end_time = t0*units::ns;
      }
      
      Bundle *bundle = new Bundle(evt,E_total,wPSD,t0,ts_runstart,mE,mSeg,mX,mY,mZ,mPSD, (*vSeg), (*vE), (*vZ), (*vPSD));

      bundle->PID();

      // std::cout << i << " " << t0 << std::endl;

      // if (i==500000) break;
      
      if (bundle->is_muon()){

	if (bundle->is_showern()){
	  if (veto_times.size()==0){
	    veto_times.push_back(std::make_pair(bundle->get_t0()+pid_cuts.get_muon_upstream_veto_time() ,
						bundle->get_t0()+pid_cuts.get_muon_showern_veto_time()+IBD_delta_t.second));
	  }else{
	    if (bundle->get_t0()+pid_cuts.get_muon_upstream_veto_time()> veto_times.back().second){
	      veto_times.push_back(std::make_pair(bundle->get_t0()+pid_cuts.get_muon_upstream_veto_time(),
						  bundle->get_t0()+pid_cuts.get_muon_showern_veto_time()+IBD_delta_t.second));
	    }else{
	      veto_times.back().second = bundle->get_t0() + pid_cuts.get_muon_showern_veto_time()+IBD_delta_t.second;
	    }
	  }
	}else{
	  if (veto_times.size()==0){
	    veto_times.push_back(std::make_pair(bundle->get_t0()+pid_cuts.get_muon_upstream_veto_time() ,
						bundle->get_t0()+pid_cuts.get_muon_veto_time()+IBD_delta_t.second));
	  }else{
	    if (bundle->get_t0()+pid_cuts.get_muon_upstream_veto_time()> veto_times.back().second){
	      veto_times.push_back(std::make_pair(bundle->get_t0()+pid_cuts.get_muon_upstream_veto_time(),
						  bundle->get_t0()+pid_cuts.get_muon_veto_time()+IBD_delta_t.second));
	    }else{
	      veto_times.back().second = bundle->get_t0() + pid_cuts.get_muon_veto_time()+IBD_delta_t.second;
	    }
	  }
	}
	
	
      }else if (bundle->is_showern()){
	if (!bundle->is_delay_cand()){
	  
	  if (veto_times.size()==0){
	    veto_times.push_back(std::make_pair(bundle->get_t0()+pid_cuts.get_muon_upstream_veto_time() ,
						bundle->get_t0()+pid_cuts.get_neutron_mult_veto_time()+IBD_delta_t.second));
	  }else{
	    if (bundle->get_t0()+pid_cuts.get_muon_upstream_veto_time()> veto_times.back().second){
	      veto_times.push_back(std::make_pair(bundle->get_t0()+pid_cuts.get_muon_upstream_veto_time(),
						  bundle->get_t0()+pid_cuts.get_neutron_mult_veto_time()+IBD_delta_t.second));
	    }else{
	      veto_times.back().second = bundle->get_t0() + pid_cuts.get_neutron_mult_veto_time()+IBD_delta_t.second;
	    }
	  }
	}
      }
      

      

      bool flag_save_bundle = false;
      
      
      
      if (bundle->is_prompt_cand()){
	prompt_list.push_back(bundle);
	flag_save_bundle = true;
      }

      // good delay candidate
      if (bundle->is_delay_cand()){
	
	if (bundle->get_t0() > veto_times.back().second){
	  std::vector<std::list<Bundle*>::iterator> to_be_removed;

	  // loop through prompt list and remove anything outside a window, delete them
	  for (auto it = prompt_list.begin(); it!=prompt_list.end(); it++){
	    if (bundle->get_t0() - (*it)->get_t0() > IBD_delta_t.second){
	      to_be_removed.push_back(it);
	      delete (*it);
	    }
	  }
	  if (to_be_removed.size()>0){
	    prompt_list.erase(to_be_removed.front(), to_be_removed.back());
	    prompt_list.erase(to_be_removed.back());
	  }

	  int n_mult = 0;
	  std::vector<std::pair<Bundle*,Bundle*> > temp_IBDs;
	  for (auto it = prompt_list.begin(); it!=prompt_list.end(); it++){
	    if (checkIBD(std::make_pair(*it,bundle))  ){
	      temp_IBDs.push_back(std::make_pair(*it,bundle));
	    }
	  }
	  
	  //if (temp_IBDs.size()==1 ){
	  if (temp_IBDs.size()>0 ){
	    bool flag_save = true;

	    if (delay_list.size()>0){
	      if ((bundle->get_t0() - delay_list.back()->get_t0()) < pid_cuts.get_nn_veto_time())
	    	flag_save = false;
	    }
	    
	    if (flag_save){
	      Bundle *prompt = new Bundle(temp_IBDs.front().first);
	      IBD_list.push_back(std::make_pair(prompt,temp_IBDs.front().second));
	      flag_save_bundle = true;
	    }
	  }
	  //  std::cout << temp_IBDs.size() << std::endl;
	  
	  
	}
      }
      
      if (bundle->is_delay_cand()){
	if (bundle->get_t0() > veto_times.back().second){

	  if (IBD_list.size()>0)
	    if (IBD_list.back().second->get_t0()!=bundle->get_t0() &&
	  	bundle->get_t0() - IBD_list.back().second->get_t0()<  pid_cuts.get_nn_veto_time()){
	      std::vector<std::list<std::pair<Bundle*,Bundle*> >::iterator> to_be_removed;
	      // check IBDs ahead of them ... 
	      for (auto it=IBD_list.begin(); it!= IBD_list.end(); it++){
	  	if ( it->second->get_t0()!=bundle->get_t0() &&
		     bundle->get_t0() - it->second->get_t0() <  pid_cuts.get_nn_veto_time())
	  	  to_be_removed.push_back(it);
	      }
	      if (to_be_removed.size()>0){
	  	IBD_list.erase(to_be_removed.front(),to_be_removed.back());
	  	IBD_list.erase(to_be_removed.back());
	      }
	    }
	  

	  delay_seg_E = bundle->get_delay_seg_E()/units::MeV;
	  delay_seg_no = bundle->get_delay_seg_no();
	  delay_seg_PSD = bundle->get_delay_seg_PSD();
	  delay_total_E = bundle->get_delay_total_E()/units::MeV;
	  time_to_prev_muon = (bundle->get_t0() - prev_muon_time)/units::microsecond;
	  time_to_prev_showern = (bundle->get_t0() - prev_showern_time)/units::microsecond;
	  time_to_prev_delay =  (bundle->get_t0() - prev_delay_time)/units::microsecond;
	  T_delay->Fill();
	  
	  delay_list.push_back(bundle);
	  prev_delay_time = bundle->get_t0();
	  flag_save_bundle = true;

	  
	}
      }
      
      if (bundle->is_showern()&& (!(bundle->is_muon())) && (!bundle->is_delay_cand()))
	prev_showern_time = bundle->get_t0();
      
      if (bundle->is_muon() && (!bundle->is_showern()))
	prev_muon_time = bundle->get_t0();
      
      if (!flag_save_bundle)
	delete bundle;
      
    }
    
    std::cout << "Total time: " << (end_time - start_time)/units::second << " seconds" << std::endl;
    double tot_veto_time = 0;
    for (size_t i=0;i!=veto_times.size();i++){
      if (veto_times.at(i).first < start_time)
	veto_times.at(i).first = start_time;
      if (veto_times.at(i).second > end_time)
	veto_times.at(i).second = end_time;
      if (veto_times.at(i).second - veto_times.at(i).first>0)
	tot_veto_time += veto_times.at(i).second - veto_times.at(i).first;
    }

    std::cout << "Total veto segs: " << veto_times.size() << " total veto time " << tot_veto_time/units::second << " seconds" << std::endl;

    total_time = (end_time - start_time)/units::second;
    total_veto_time = tot_veto_time/units::second;
    T_sum->Fill();
    
    
    //    std::cout << showern_count << " " << showern_muon_count << std::endl;
    

    // for (auto it=delay_list.begin(); it!=delay_list.end(); it++){
    //   Bundle *bundle = *it;
    //   delay_seg_E = bundle->get_delay_seg_E()/units::MeV;
    //   delay_seg_no = bundle->get_delay_seg_no();
    //   delay_seg_PSD = bundle->get_delay_seg_PSD();
    //   delay_total_E = bundle->get_delay_total_E()/units::MeV;
    //   time_to_prev_muon = (bundle->get_t0() - prev_muon_time)/units::microsecond;
    //   time_to_prev_showern = (bundle->get_t0() - prev_showern_time)/units::microsecond;
    //   time_to_prev_delay =  (bundle->get_t0() - prev_delay_time)/units::microsecond;
    //   T_delay->Fill();
    // }

    for (auto it = IBD_list.begin(); it!=IBD_list.end(); it++){
      Bundle* bundle1 = it->first;
      Bundle* bundle2 = it->second;
      
      prompt_maxseg_E = bundle1->get_prompt_maxseg_E()/units::MeV;
      prompt_maxseg_no = bundle1->get_prompt_maxseg_no();
      prompt_maxseg_PSD = bundle1->get_prompt_maxseg_PSD();
      prompt_maxseg_Z = bundle1->get_prompt_maxseg_Z()/units::cm;
      prompt_total_E = bundle1->get_prompt_total_E()/units::MeV;
      
      delay_seg_E = bundle2->get_delay_seg_E()/units::MeV;
      delay_seg_no = bundle2->get_delay_seg_no();
      delay_seg_PSD = bundle2->get_delay_seg_PSD();
      delay_seg_Z = bundle2->get_delay_seg_Z()/units::cm;
      delay_total_E = bundle2->get_delay_total_E()/units::MeV;
      
      flag_geometry = geometry.RowColDiff(bundle1->get_prompt_maxseg_no(), bundle2->get_delay_seg_no());
      delta_t = bundle2->get_t0() - bundle1->get_t0();
      T_IBD->Fill();
    }
    
    
    file1->Write();
    file1->Close();
  }



}
