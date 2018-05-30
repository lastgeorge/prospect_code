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
{
  particle_type = -1;
  for (size_t i=0;i!=vE.size();i++){
    vE.at(i) *= units::MeV;
    vZ.at(i) *= units::cm;
  }
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

  if (geometry.is_dead_seg(mSeg) || geometry.is_veto_seg(mSeg))
    return;
  
  // std::pair<double,double> n_PSD = pid_cuts.get_neutron_PSD(E_total);
  // std::pair<double,double> g_PSD = pid_cuts.get_gamma_PSD(E_total);
  // std::pair<double,double> he_n_E = pid_cuts.get_he_neutron_E();
  // std::pair<double,double> he_m_E = pid_cuts.get_he_muon_E(); 
  // std::pair<double,double> IBD_p_E = pid_cuts.get_prompt_E(); 
  // std::pair<double,double> IBD_d_E = pid_cuts.get_delay_E();
    
  // if (E_total > he_n_E.first && E_total < he_n_E.second && wPSD > n_PSD.first && wPSD < n_PSD.second){
  //   particle_type = 4; // neutron
  // }else if (E_total > he_m_E.first && E_total < he_m_E.second ){
  //   particle_type = 3; // muon
  // } else if (E_total > IBD_p_E.first && E_total < IBD_p_E.second && wPSD > g_PSD.first && wPSD < g_PSD.second){
  //   particle_type = 1;
  // } else if (E_total > IBD_d_E.first && E_total < IBD_d_E.second && wPSD > n_PSD.first && wPSD < n_PSD.second){
  //   particle_type = 2;
  // }
  
}
