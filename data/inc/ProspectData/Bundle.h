#ifndef Bundle_h
#define Bundle_h

#include "ProspectData/Units.h"
#include <vector>

namespace Prospect {
  class Bundle{
  public:
    Bundle(long long evt,float E_total,float wPSD,double t0,int ts_runstart,float mE,int mSeg,float mX,float mY,float mZ,float mPSD,std::vector<int>& vSeg, std::vector<float>& vE, std::vector<float>& vZ, std::vector<float>& vPSD);
    Bundle(Bundle *bundle);
    ~Bundle();

    void Print();

    void PID();

    bool is_muon(){return flag_muon;};
    bool is_showern(){return flag_showern;};
    bool is_delay_cand(){return flag_delay_cand;};
    bool is_prompt_cand(){return flag_prompt_cand;};
    double get_t0(){return t0;};
    long long get_evt(){return evt;};

    double get_delay_seg_E(){return delay_seg_E;};
    int get_delay_seg_no(){return delay_seg_no;};
    double get_delay_seg_PSD(){return delay_seg_PSD;};
    double get_delay_seg_Z(){return delay_seg_Z;};
    double get_delay_total_E(){return delay_total_E;};

    double get_prompt_maxseg_E(){return prompt_maxseg_E;};
    int get_prompt_maxseg_no(){return prompt_maxseg_no;};
    double get_prompt_maxseg_PSD(){return prompt_maxseg_PSD;};
    double get_prompt_maxseg_Z(){return prompt_maxseg_Z;};
    double get_prompt_total_E(){ return prompt_total_E;};

    
    long long evt;
    float E_total;
    float wPSD;
    double t0;
    int ts_runstart;
    float mE;
    int mSeg;
    float mX;
    float mY;
    float mZ;
    float mPSD;
    
    std::vector<int> vSeg;
    std::vector<float> vE;
    std::vector<float> vZ;
    std::vector<float> vPSD;

    bool flag_muon;
    bool flag_showern;
    bool flag_delay_cand;
    bool flag_prompt_cand;

    // the set of delayed variable ...
    double delay_seg_E;
    int delay_seg_no;
    double delay_seg_PSD;
    double delay_seg_Z;
    double delay_total_E;

    // the set of prompt variables ...
    double prompt_maxseg_E;
    int prompt_maxseg_no;
    double prompt_maxseg_PSD;
    double prompt_maxseg_Z;
    double prompt_total_E;
    
  };
}

#endif
