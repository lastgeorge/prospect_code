#include <vector>

namespace Prospect{
  class PIDParams {
    // high energy muon ...

    double he_muon_E[2]; // low and high range
    double he_muon_PSD[2]; // low and high range
    
    // veto ...
    double he_muon_veto_time;
    
    // high energy neutron ... 
    double he_neutron_E[2];
    double he_neutron_PSD[2];
    
    // veto ...
    double he_neutron_veto_time;
    
    // prompt signal
    double prompt_E[2];
    double prompt_PSD[2];

    // delay signal
    double delay_E[2];
    double delay_PSD[2];

    //delta t between prompt and delay
    double delta_t_pd[2];

  public:
    PIDParams();
    ~PIDParams();
    
    std::pair<double,double> get_he_muon_E();
    std::pair<double,double> get_he_muon_PSD();
    double get_he_muon_veto_time(){return he_muon_veto_time;};
    std::pair<double,double> get_he_neutron_E();
    std::pair<double,double> get_he_neutron_PSD();
    double get_he_neutron_veto_time(){return he_neutron_veto_time;};
    std::pair<double,double> get_prompt_E();
    std::pair<double,double> get_prompt_PSD();
    std::pair<double,double> get_delay_E();
    std::pair<double,double> get_delay_PSD();
    std::pair<double,double> get_delta_t_pd();

    void set_he_muon_E(double val1, double val2);
    void set_he_muon_PSD(double val1, double val2);
    void set_he_muon_veto_time(double val){he_muon_veto_time=val;};
    void set_he_neutron_E(double val1, double val2);
    void set_he_neutron_PSD(double val1, double val2);
    void set_he_neutron_veto_time(double val){he_neutron_veto_time=val;};
    void set_prompt_E(double val1, double val2);
    void set_prompt_PSD(double val1, double val2);
    void set_delay_E(double val1, double val2);
    void set_delay_PSD(double val1, double val2);
    void set_delta_t_pd(double val1, double val2);
    
  };
}
