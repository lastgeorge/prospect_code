#ifndef Bundle_h
#define Bundle_h

#include "ProspectData/Units.h"
#include <vector>

namespace Prospect {
  class Bundle{
  public:
    Bundle(long long evt,float E_total,float wPSD,double t0,int ts_runstart,float mE,int mSeg,float mX,float mY,float mZ,float mPSD,std::vector<int>& vSeg, std::vector<float>& vE, std::vector<float>& vZ, std::vector<float>& vPSD);
    ~Bundle();

    void Print();

    void PID();

    int get_particle_type() {return particle_type;};
    int get_t0(){return t0;};
    
  protected:
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

    int particle_type;
    
  };
}

#endif
