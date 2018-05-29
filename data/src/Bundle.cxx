#include "ProspectData/Bundle.h"


#include <iostream>

using namespace Prospect;

Bundle::Bundle(long long evt,float E_total,float wPSD,double t0,int ts_runstart,float mE,int mSeg,float mX,float mY,float mZ,float mPSD,std::vector<int>& vSeg, std::vector<float>& vE, std::vector<float>& vZ, std::vector<float>& vPSD)
  : evt(evt)
  , E_total(E_total)
  , wPSD(wPSD)
  , t0(t0)
  , ts_runstart(ts_runstart)
  , mE(mE)
  , mSeg(mSeg)
  , mX(mX)
  , mY(mY)
  , mZ(mZ)
  , mPSD(mPSD)
  , vSeg(vSeg)
  , vE(vE)
  , vZ(vZ)
  , vPSD(vPSD)
{
  
}

Bundle::~Bundle(){
}

void Bundle::Print(){
  std::cout << "Event:  " << evt << std::endl;
  std::cout << "Energy: " << E_total << std::endl;
  std::cout << "PSD   : " << wPSD << std::endl;
  std::cout << "t0    : " << t0 << std::endl;
  std::cout << "startT: " << ts_runstart << std::endl;
  std::cout << "mE    : " << mE << std::endl;
  std::cout << "mSeg  : " << mSeg << std::endl;
  std::cout << "mX    : " << mX << std::endl;
  std::cout << "mY    : " << mY << std::endl;
  std::cout << "mZ    : " << mZ << std::endl;
  std::cout << "mPSD  : " << mPSD << std::endl;
  std::cout << "vSeg  : " << vSeg.size() << std::endl;
  std::cout << "vE    : " << vE.size() << std::endl;
  std::cout << "vZ    : " << vZ.size() << std::endl;
  std::cout << "vPSD  : " << vPSD.size() << std::endl;
  
}

