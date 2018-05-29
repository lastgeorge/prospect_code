#include "ProspectData/Units.h"

#include <vector>

#include "TGraph.h"

namespace Prospect{
  class PIDParams {
    // high energy muon ...

    double he_muon_E[2]; // low and high range
   
    
    // veto ...
    double he_muon_veto_time;
    
    // high energy neutron ... 
    double he_neutron_E[2];
    
    
    // veto ...
    double he_neutron_veto_time;
    
    // prompt signal
    double prompt_E[2];
    

    // delay signal
    double delay_E[2];
   

    //delta t between prompt and delay
    double delta_t_pd[2];

    
    double fid_cut_z[2];
    double delta_z[3];

    TGraph *gPSD_neutron_low;
    TGraph *gPSD_neutron_high;

    TGraph *gPSD_gamma_low;
    TGraph *gPSD_gamma_high;
    
  public:
    PIDParams();
    ~PIDParams();
    
    std::pair<double,double> get_he_muon_E();
    
    double get_he_muon_veto_time(){return he_muon_veto_time;};
    std::pair<double,double> get_he_neutron_E();
    
    double get_he_neutron_veto_time(){return he_neutron_veto_time;};
    std::pair<double,double> get_prompt_E();
   
    std::pair<double,double> get_delay_E();
    
    std::pair<double,double> get_delta_t_pd();

    void set_he_muon_E(double val1, double val2);
    
    void set_he_muon_veto_time(double val){he_muon_veto_time=val;};
    void set_he_neutron_E(double val1, double val2);
    
    void set_he_neutron_veto_time(double val){he_neutron_veto_time=val;};
    void set_prompt_E(double val1, double val2);
    
    void set_delay_E(double val1, double val2);
    
    void set_delta_t_pd(double val1, double val2);

    std::pair<double,double> get_fid_z_cut(){return std::make_pair(fid_cut_z[0],fid_cut_z[1]);};
    double get_delta_z_cut(int flag);

    std::pair<double,double> get_neutron_PSD(double E);
    std::pair<double,double> get_gamma_PSD(double E);
    
  };
}
