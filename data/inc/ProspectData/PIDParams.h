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
    
    
    
  };
}
