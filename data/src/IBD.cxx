#include "ProspectData/IBD.h"
#include "ProspectData/Geometry.h"
#include "ProspectData/Singleton.h"
#include "ProspectData/PIDParams.h"

using namespace Prospect;

bool Prospect::checkIBD(std::pair<Bundle*, Bundle*> IBD_cand){
  // assuming other things have been checked
  Bundle *prompt = IBD_cand.first;
  Bundle *delay = IBD_cand.second;

  PIDParams& pid_cuts = Singleton<PIDParams>::Instance();
  Geometry& geometry = Singleton<Geometry>::Instance();
  
  std::pair<double,double> IBD_delta_t = pid_cuts.get_delta_t_pd();
  // check coincidence time
  if (delay->get_t0()-prompt->get_t0() >= IBD_delta_t.first &&
      delay->get_t0()-prompt->get_t0() < IBD_delta_t.second){
    // check coincidence vertex
    int flag_geometry = geometry.RowColDiff(prompt->get_prompt_maxseg_no(), delay->get_delay_seg_no());
    if (flag_geometry==0){
      if (fabs(prompt->get_prompt_maxseg_Z() - delay->get_delay_seg_Z())<pid_cuts.get_delta_z_cut(0)){
	return true;
      }
    }else if (flag_geometry==1){
      if (fabs(prompt->get_prompt_maxseg_Z() - delay->get_delay_seg_Z())<pid_cuts.get_delta_z_cut(1)){
	return true;
      }
    }else if (flag_geometry==2){
      if (fabs(prompt->get_prompt_maxseg_Z() - delay->get_delay_seg_Z())<pid_cuts.get_delta_z_cut(2)){
	return true;
      }
    }
  }
  


  return false;
}


bool Prospect::checkacc(std::pair<Bundle*, Bundle*> IBD_cand){
  // assuming other things have been checked
  Bundle *prompt = IBD_cand.first;
  Bundle *delay = IBD_cand.second;

  PIDParams& pid_cuts = Singleton<PIDParams>::Instance();
  Geometry& geometry = Singleton<Geometry>::Instance();
  
  // check coincidence vertex
  int flag_geometry = geometry.RowColDiff(prompt->get_prompt_maxseg_no(), delay->get_delay_seg_no());
  if (flag_geometry==0){
    if (fabs(prompt->get_prompt_maxseg_Z() - delay->get_delay_seg_Z())<pid_cuts.get_delta_z_cut(0)){
      return true;
    }
  }else if (flag_geometry==1){
    if (fabs(prompt->get_prompt_maxseg_Z() - delay->get_delay_seg_Z())<pid_cuts.get_delta_z_cut(1)){
      return true;
    }
  }else if (flag_geometry==2){
    if (fabs(prompt->get_prompt_maxseg_Z() - delay->get_delay_seg_Z())<pid_cuts.get_delta_z_cut(2)){
      return true;
    }
  }
  
  return false;
}
