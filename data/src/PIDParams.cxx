#include "ProspectData/PIDParams.h"

using namespace Prospect;

PIDParams::PIDParams(){
  // muon veto energy
  he_muon_E[0] = 15*units::MeV;
  he_muon_E[1] = 1e9;

  // muon veto time
  he_muon_veto_time = 100*units::microsecond;

  // neutron veto energy
  he_neutron_E[0] = 1*units::MeV; // place holder ... 
  he_neutron_E[1] = 1e9;
  
  // neutron veto time
  he_neutron_veto_time = 200*units::microsecond;

  // prompt energy
  prompt_E[0] = 0.1 *units::MeV;
  prompt_E[1] = 10 * units::MeV;
  
  
  // delay energy
  delay_E[0] = 0.48*units::MeV;
  delay_E[1] = 0.62*units::MeV;
  
  // coincidence timing
  delta_t_pd[0] = 1*units::microsecond;
  delta_t_pd[1] = 120*units::microsecond;

  fid_cut_z[0]=-89.6*units::cm;
  fid_cut_z[1]=89.6*units::cm;

  delta_z[0] = 18*units::cm; // same 
  delta_z[1] = 14*units::cm; // adjacent
  delta_z[2] = 5*units::cm; // corner
    
  // neutrono PSD ...
  Double_t E_n[2]={0.01*units::MeV, 1e9*units::MeV};
  Double_t PSD_n_low[2]={0.2,0.2};
  Double_t PSD_n_high[2]={0.32,0.32};

  gPSD_neutron_low = new TGraph(2,E_n,PSD_n_low);
  gPSD_neutron_high = new TGraph(2,E_n,PSD_n_high);
  
  // gamma PSD ...
  Double_t E_g[2]={0.01*units::MeV, 1e9*units::MeV};
  Double_t PSD_g_low[2]={0.05,0.05};
  Double_t PSD_g_high[2]={0.2,0.2};

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


void PIDParams::set_he_muon_E(double val1, double val2){
  he_muon_E[0] = val1;
  he_muon_E[1] = val2;
}

std::pair<double,double> PIDParams::get_he_muon_E(){
  return std::make_pair(he_muon_E[0],he_muon_E[1]);
}


void PIDParams::set_he_neutron_E(double val1, double val2){
  he_neutron_E[0] = val1;
  he_neutron_E[1] = val2;
}

std::pair<double,double> PIDParams::get_he_neutron_E(){
  return std::make_pair(he_neutron_E[0],he_neutron_E[1]);
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
