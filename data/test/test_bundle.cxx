#include "ProspectData/Bundle.h"

#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"

using namespace std;
using namespace Prospect;

int main(int argc, char* argv[]){
  if (argc<2){
    
  }else{
    Long64_t evt;
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
    std::vector<int> *vSeg = new std::vector<int>;
    std::vector<float> *vE = new std::vector<float>;
    std::vector<float> *vZ = new std::vector<float>;
    std::vector<float> *vPSD = new std::vector<float>;

    TString filename = argv[1];
    TFile *file = new TFile(filename);
    TTree *T = (TTree*)file->Get("Event");

    T->SetBranchAddress("evt",&evt);
    T->SetBranchAddress("E_total",&E_total);
    T->SetBranchAddress("wPSD",&wPSD);
    T->SetBranchAddress("t0",&t0);
    T->SetBranchAddress("ts_runstart",&ts_runstart);
    T->SetBranchAddress("mE",&mE);
    T->SetBranchAddress("mSeg",&mSeg);
    T->SetBranchAddress("mX",&mX);
    T->SetBranchAddress("mY",&mY);
    T->SetBranchAddress("mZ",&mZ);
    T->SetBranchAddress("mPSD",&mPSD);
    T->SetBranchAddress("vSeg",&vSeg);
    T->SetBranchAddress("vE",&vE);
    T->SetBranchAddress("vZ",&vZ);
    T->SetBranchAddress("vPSD",&vPSD);
    
    
    
    std::cout << "Entries: " << T->GetEntries() << std::endl;

    T->GetEntry(0);

    Bundle *bundle = new Bundle(evt,E_total,wPSD,t0,ts_runstart,mE,mSeg,mX,mY,mZ,mPSD, (*vSeg), (*vE), (*vZ), (*vPSD));

    bundle->Print();
    
  }

  return 0;
}
