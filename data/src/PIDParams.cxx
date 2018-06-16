#include "ProspectData/PIDParams.h"

using namespace Prospect;

PIDParams::PIDParams(){
  // muon veto energy
  muon_tot_E_llimit = 15*units::MeV;
  // muon veto time
  muon_showern_veto_time = 200*units::microsecond;
  muon_veto_time = 100*units::microsecond;

  muon_upstream_veto_time = -10*units::microsecond; // same for below ... 
  
  // neutron veto energy
  neutron_E_llimit = 0.25*units::MeV; 
  // neutron veto time  +- 100 us
  neutron_mult_veto_time = 180*units::microsecond;

  nn_veto_time = 240*units::microsecond;
  
  // prompt energy
  prompt_E[0] = 0.4 *units::MeV;
  prompt_E[1] = 15 * units::MeV;
  
  // delay energy
  delay_E[0] = 0.47*units::MeV;
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
  Double_t E_n[24]={0.1*units::MeV, 0.11*units::MeV,
		    0.25*units::MeV, 0.4*units::MeV, 0.6136364*units::MeV, 0.8863636*units::MeV, 1.1136364*units::MeV,
		    1.7045455*units::MeV, 2.2727273*units::MeV, 3.0681818*units::MeV, 3.7272727*units::MeV , 4.3636365*units::MeV,
		    5.068182*units::MeV, 5.8863635*units::MeV , 6.818182*units::MeV , 7.909091*units::MeV , 9.068182*units::MeV ,
		    10.090909*units::MeV, 11.181818*units::MeV, 12.431818*units::MeV, 13.204545*units::MeV, 14.204545*units::MeV,
		    14.863636*units::MeV, 15*units::MeV};
  Double_t PSD_n_low[24]={0.35,0.35,
			  0.28,0.22,0.21023256,0.20179704,0.1938055,
			  0.18581395, 0.18270613, 0.18004228, 0.17693447, 0.17560254,
			  0.17293869, 0.17116278, 0.1693869, 0.1658351, 0.16361523,
			  0.1622833, 0.1605074, 0.1587315, 0.15828753, 0.1569556,
			  0.15651163, 0.15651163};

    
  Double_t PSD_n_high[24]={0.6,0.6,0.6,0.6,0.6,
			   0.6,0.6,0.6,0.6,0.6,
			   0.6,0.6,0.6,0.6,0.6,
			   0.6,0.6,0.6,0.6,0.6,
			   0.6,0.6,0.6,0.6};

  gPSD_neutron_low = new TGraph(24,E_n,PSD_n_low);
  gPSD_neutron_high = new TGraph(24,E_n,PSD_n_high);
  
  // gamma PSD ...
  Double_t E_g[24]={0.1*units::MeV, 0.11*units::MeV, 0.25*units::MeV, 0.4*units::MeV, 0.6136364*units::MeV, 0.8863636*units::MeV, 1.1136364*units::MeV,
		    1.7045455*units::MeV, 2.2727273*units::MeV, 3.0681818*units::MeV, 3.7272727*units::MeV , 4.3636365*units::MeV,
		    5.068182*units::MeV, 5.8863635*units::MeV , 6.818182*units::MeV , 7.909091*units::MeV , 9.068182*units::MeV ,
		    10.090909*units::MeV, 11.181818*units::MeV, 12.431818*units::MeV, 13.204545*units::MeV, 14.204545*units::MeV,
		    14.863636*units::MeV, 15*units::MeV};
  Double_t PSD_g_low[24]={-0.01,-0.01,-0.01,-0.01,-0.01,
			  -0.01,-0.01,-0.01,-0.01,-0.01,
			  -0.01,-0.01,-0.01,-0.01,-0.01,
			  -0.01,-0.01,-0.01,-0.01,-0.01,
			  -0.01,-0.01,-0.01,-0.01};
  Double_t PSD_g_high[24]={0.35,0.35,
    0.28,0.22,0.21023256,0.20179704,0.1938055,
			  0.18581395, 0.18270613, 0.18004228, 0.17693447, 0.17560254,
			  0.17293869, 0.17116278, 0.1693869, 0.1658351, 0.16361523,
			  0.1622833, 0.1605074, 0.1587315, 0.15828753, 0.1569556,
			  0.15651163, 0.15651163}; // gamma ...

  gPSD_gamma_low = new TGraph(24,E_g,PSD_g_low);
  gPSD_gamma_high = new TGraph(24,E_g, PSD_g_high);
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
