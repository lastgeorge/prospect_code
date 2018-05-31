#include "ProspectData/Bundle.h"
#include "ProspectData/Singleton.h"
#include "ProspectData/PIDParams.h"
#include "ProspectData/Geometry.h"

#include <iostream>

using namespace Prospect;

Bundle::Bundle(long long evt,float E_total,float wPSD,double t0,int ts_runstart,float mE,int mSeg,float mX,float mY,float mZ,float mPSD,std::vector<int>& vSeg, std::vector<float>& vE, std::vector<float>& vZ, std::vector<float>& vPSD)
  : evt(evt)
  , E_total(E_total*units::MeV)
  , wPSD(wPSD)
  , t0(t0*units::ns)
  , ts_runstart(ts_runstart)
  , mE(mE*units::MeV)
  , mSeg(mSeg)
  , mX(mX*units::cm)
  , mY(mY*units::cm)
  , mZ(mZ*units::cm)
  , mPSD(mPSD)
  , vSeg(vSeg)
  , vE(vE)
  , vZ(vZ)
  , vPSD(vPSD)
  , flag_muon(false)
  , flag_showern(false)
  , flag_delay_cand(false)
  , flag_prompt_cand(false)
  , delay_seg_E(0)
  , delay_seg_no(0)
  , delay_seg_PSD(0)
  , delay_seg_Z(0)
  , delay_total_E(0)
  , prompt_maxseg_E(0)
  , prompt_maxseg_no(0)
  , prompt_maxseg_PSD(0)
  , prompt_maxseg_Z(0)
  , prompt_total_E(0)
{
 
  for (size_t i=0;i!=vE.size();i++){
    vE.at(i) *= units::MeV;
    vZ.at(i) *= units::cm;
  }
}

Bundle::Bundle(Bundle* bundle)
  : evt(bundle->evt)
  , E_total(bundle->E_total)
  , wPSD(bundle->wPSD)
  , t0(bundle->t0)
  , ts_runstart(bundle->ts_runstart)
  , mE(bundle->mE)
  , mSeg(bundle->mSeg)
  , mX(bundle->mX)
  , mY(bundle->mY)
  , mZ(bundle->mZ)
  , mPSD(bundle->mPSD)
  , vSeg(bundle->vSeg)
  , vE(bundle->vE)
  , vZ(bundle->vZ)
  , vPSD(bundle->vPSD)
  , flag_muon(bundle->flag_muon)
  , flag_showern(bundle->flag_showern)
  , flag_delay_cand(bundle->flag_delay_cand)
  , flag_prompt_cand(bundle->flag_prompt_cand)
  , delay_seg_E(bundle->delay_seg_E)
  , delay_seg_no(bundle->delay_seg_no)
  , delay_seg_PSD(bundle->delay_seg_PSD)
  , delay_seg_Z(bundle->delay_seg_Z)
  , delay_total_E(bundle->delay_total_E)
  , prompt_maxseg_E (bundle->prompt_maxseg_E)
  , prompt_maxseg_no (bundle->prompt_maxseg_no)
  , prompt_maxseg_PSD (bundle->prompt_maxseg_PSD)
  , prompt_maxseg_Z (bundle->prompt_maxseg_Z)
  , prompt_total_E (bundle->prompt_total_E)
{
}


Bundle::~Bundle(){
}

void Bundle::Print(){
  std::cout << "Event:  " << evt << std::endl;
  std::cout << "Energy: " << E_total << std::endl;
  std::cout << "PSD   : " << wPSD << std::endl;
  std::cout << "t0    : " << t0 << std::endl;
  std::cout << "startT: " << ts_runstart << std::endl;
  std::cout << "mE    : " << mE << std::endl;
  std::cout << "mSeg  : " << mSeg << std::endl;
  std::cout << "mX    : " << mX << std::endl;
  std::cout << "mY    : " << mY << std::endl;
  std::cout << "mZ    : " << mZ << std::endl;
  std::cout << "mPSD  : " << mPSD << std::endl;
  std::cout << "vSeg  : " << vSeg.size() << std::endl;
  std::cout << "vE    : " << vE.size() << std::endl;
  std::cout << "vZ    : " << vZ.size() << std::endl;
  std::cout << "vPSD  : " << vPSD.size() << std::endl;
  
}

void Bundle::PID(){
  PIDParams& pid_cuts = Singleton<PIDParams>::Instance();
  Geometry& geometry = Singleton<Geometry>::Instance();

  // if (geometry.is_dead_seg(mSeg) || geometry.is_veto_seg(mSeg))
  //   return;
  
  std::pair<double,double> n_PSD = pid_cuts.get_neutron_PSD(E_total);
  std::pair<double,double> g_PSD = pid_cuts.get_gamma_PSD(E_total);

  double muon_tot_E_llimit = pid_cuts.get_muon_tot_E_llimit();
  
  double neutron_E_llimit = pid_cuts.get_neutron_E_llimit();
  
  std::pair<double,double> IBD_p_E = pid_cuts.get_prompt_E(); 
  std::pair<double,double> IBD_d_E = pid_cuts.get_delay_E();
  
  std::pair<double,double> fid_z_cut = pid_cuts.get_fid_z_cut();
    
  if (E_total > muon_tot_E_llimit ){
    flag_muon = true;
  }
  
  for (size_t i=0;i!=vE.size();i++){
    if (vE.at(i)>neutron_E_llimit && vPSD.at(i) > n_PSD.first && vPSD.at(i) < n_PSD.second){
      flag_showern = true;
      break;
    }
  }

  
  
  if (!flag_muon){
    flag_prompt_cand = true;
    
    for (size_t i=0;i!=vE.size();i++){
      if (geometry.is_dead_seg(vSeg.at(i)) || geometry.is_veto_seg(vSeg.at(i)) || vE.at(i) <0.01*units::MeV
	  || vSeg.at(i)<geometry.min_SegNo || vSeg.at(i)>geometry.max_SegNo
	  || vZ.at(i) < fid_z_cut.first || vZ.at(i) > fid_z_cut.second)
	continue;
      
      if (vE.at(i) > IBD_d_E.first && vE.at(i) < IBD_d_E.second &&
	  vPSD.at(i) > n_PSD.first && vPSD.at(i) < n_PSD.second){
	flag_delay_cand = true;
	flag_prompt_cand = false;
	delay_seg_E = vE.at(i);
	delay_seg_no = vSeg.at(i);
	delay_seg_PSD = vPSD.at(i);
	delay_seg_Z = vZ.at(i);
	
      }else if (vE.at(i)>0.1*units::MeV && vPSD.at(i) > g_PSD.first && vPSD.at(i) < g_PSD.second ){
	if (vE.at(i) > prompt_maxseg_E){
	  prompt_maxseg_E = vE.at(i);
	  prompt_maxseg_no = vSeg.at(i);
	  prompt_maxseg_PSD = vPSD.at(i);
	  prompt_maxseg_Z = vZ.at(i);
	}
      }else{
	flag_prompt_cand = false;
      }

      
      delay_total_E += vE.at(i);
      prompt_total_E += vE.at(i);
      
    }
    
    if (prompt_total_E < IBD_p_E.first || prompt_total_E > IBD_p_E.second )
      flag_prompt_cand = false;
    if (delay_total_E > delay_seg_E + 0.1*units::MeV)
      flag_delay_cand = false;
  }

 
  
  // if (E_total > he_n_E.first && E_total < he_n_E.second && wPSD > n_PSD.first && wPSD < n_PSD.second){
  //   particle_type = 4; // neutron

  
  // } else if (E_total > IBD_p_E.first && E_total < IBD_p_E.second && wPSD > g_PSD.first && wPSD < g_PSD.second){
  //   particle_type = 1;
  // } else if (E_total > IBD_d_E.first && E_total < IBD_d_E.second && wPSD > n_PSD.first && wPSD < n_PSD.second){
  //   particle_type = 2;
  // }
  
}
