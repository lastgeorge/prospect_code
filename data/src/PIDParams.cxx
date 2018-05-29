#include "ProspectData/PIDParams.h"

using namespace Prospect;

PIDParams::PIDParams(){
  
}

PIDParams::~PIDParams(){
  
}

void PIDParams::set_he_muon_E(double val1, double val2){
  he_muon_E[0] = val1;
  he_muon_E[1] = val2;
}

std::pair<double,double> PIDParams::get_he_muon_E(){
  return std::make_pair(he_muon_E[0],he_muon_E[1]);
}


void PIDParams::set_he_muon_PSD(double val1, double val2){
  he_muon_PSD[0] = val1;
  he_muon_PSD[1] = val2;
}

std::pair<double,double> PIDParams::get_he_muon_PSD(){
  return std::make_pair(he_muon_PSD[0],he_muon_PSD[1]);
}

void PIDParams::set_he_neutron_E(double val1, double val2){
  he_neutron_E[0] = val1;
  he_neutron_E[1] = val2;
}

std::pair<double,double> PIDParams::get_he_neutron_E(){
  return std::make_pair(he_neutron_E[0],he_neutron_E[1]);
}

void PIDParams::set_he_neutron_PSD(double val1, double val2){
  he_neutron_PSD[0] = val1;
  he_neutron_PSD[1] = val2;
}

std::pair<double,double> PIDParams::get_he_neutron_PSD(){
  return std::make_pair(he_neutron_PSD[0],he_neutron_PSD[1]);
}


void PIDParams::set_prompt_E(double val1, double val2){
  prompt_E[0] = val1;
  prompt_E[1] = val2;
}
void PIDParams::set_prompt_PSD(double val1, double val2){
  prompt_PSD[0] = val1;
  prompt_PSD[1] = val2;
}
void PIDParams::set_delay_E(double val1, double val2){
  delay_E[0] = val1;
  delay_E[1] = val2;
}
void PIDParams::set_delay_PSD(double val1, double val2){
  delay_PSD[0] = val1;
  delay_PSD[1] = val2;
}
void PIDParams::set_delta_t_pd(double val1, double val2){
  delta_t_pd[0] = val1;
  delta_t_pd[1] = val2;
}

std::pair<double,double> PIDParams::get_prompt_E(){
  return std::make_pair(prompt_E[0],prompt_E[1]);
}
std::pair<double,double> PIDParams::get_prompt_PSD(){
  return std::make_pair(prompt_PSD[0],prompt_PSD[1]);
}
std::pair<double,double> PIDParams::get_delay_E(){
  return std::make_pair(delay_E[0],delay_E[1]);
}
std::pair<double,double> PIDParams::get_delay_PSD(){
  return std::make_pair(delay_PSD[0],delay_PSD[1]);
}
std::pair<double,double> PIDParams::get_delta_t_pd(){
  return std::make_pair(delta_t_pd[0],delta_t_pd[1]);
}
