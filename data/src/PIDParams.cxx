#include "ProspectData/PIDParams.h"

using namespace Prospect;

PIDParams::PIDParams(){
  // muon veto energy
  muon_tot_E_llimit = 15*units::MeV;
  // muon veto time
  muon_veto_time = 100*units::microsecond;

  // neutron veto energy
  neutron_E_llimit = 0.25*units::MeV; 
  // neutron veto time  +- 100 us
  neutron_mult_veto_time = 100*units::microsecond;
  
  // prompt energy
  prompt_E[0] = 0.25 *units::MeV;
  prompt_E[1] = 10 * units::MeV;
  
  // delay energy
  delay_E[0] = 0.48*units::MeV;
  delay_E[1] = 0.62*units::MeV;
  
  // coincidence timing
  delta_t_pd[0] = 1*units::microsecond;
  delta_t_pd[1] = 120*units::microsecond;

  fid_cut_z[0]=-44.8*units::cm;
  fid_cut_z[1]=44.8*units::cm;

  delta_z[0] = 18*units::cm; // same 
  delta_z[1] = 14*units::cm; // adjacent
  delta_z[2] = 5*units::cm; // corner
  
  // neutrono PSD ...
  Double_t E_n[2]={0.01*units::MeV, 1e9*units::MeV};
  Double_t PSD_n_low[2]={0.21,0.21}; // PID
  Double_t PSD_n_high[2]={0.33,0.33};

  gPSD_neutron_low = new TGraph(2,E_n,PSD_n_low);
  gPSD_neutron_high = new TGraph(2,E_n,PSD_n_high);
  
  // gamma PSD ...
  Double_t E_g[2]={0.01*units::MeV, 1e9*units::MeV};
  Double_t PSD_g_low[2]={-0.01,-0.01};
  Double_t PSD_g_high[2]={0.21,0.21}; // gamma ...

  gPSD_gamma_low = new TGraph(2,E_g,PSD_g_low);
  gPSD_gamma_high = new TGraph(2,E_g, PSD_g_high);
}

PIDParams::~PIDParams(){
  delete gPSD_neutron_low;
  delete gPSD_neutron_high;
  delete gPSD_gamma_low;
  delete gPSD_gamma_high;
}

double PIDParams::get_delta_z_cut(int flag){
  if (flag==0){
    return delta_z[0];
  }else if (flag==1){
    return delta_z[1];
  }else{
    return delta_z[2];
  }
}

std::pair<double,double> PIDParams::get_neutron_PSD(double E){
  double val1 = gPSD_neutron_low->Eval(E);
  double val2 = gPSD_neutron_high->Eval(E);

  return std::make_pair(val1,val2);
}

std::pair<double,double> PIDParams::get_gamma_PSD(double E){
  double val1 = gPSD_gamma_low->Eval(E);
  double val2 = gPSD_gamma_high->Eval(E);

  return std::make_pair(val1,val2);
}


void PIDParams::set_muon_tot_E_llimit(double val){
  muon_tot_E_llimit = val;
}

double PIDParams::get_muon_tot_E_llimit(){
  return muon_tot_E_llimit;
}


void PIDParams::set_neutron_E_llimit(double val){
  neutron_E_llimit = val;
}

double PIDParams::get_neutron_E_llimit(){
  return neutron_E_llimit;
}




void PIDParams::set_prompt_E(double val1, double val2){
  prompt_E[0] = val1;
  prompt_E[1] = val2;
}

void PIDParams::set_delay_E(double val1, double val2){
  delay_E[0] = val1;
  delay_E[1] = val2;
}

void PIDParams::set_delta_t_pd(double val1, double val2){
  delta_t_pd[0] = val1;
  delta_t_pd[1] = val2;
}

std::pair<double,double> PIDParams::get_prompt_E(){
  return std::make_pair(prompt_E[0],prompt_E[1]);
}

std::pair<double,double> PIDParams::get_delay_E(){
  return std::make_pair(delay_E[0],delay_E[1]);
}

std::pair<double,double> PIDParams::get_delta_t_pd(){
  return std::make_pair(delta_t_pd[0],delta_t_pd[1]);
}
