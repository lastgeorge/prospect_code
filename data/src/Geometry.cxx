#include "ProspectData/Geometry.h"

#include <cmath>

using namespace Prospect;

Geometry::Geometry()
{
  WIDTH_X = 0.1461*units::m; // m
  WIDTH_Y = 0.1461*units::m; // m
  WIDTH_Z = 1.175*units::m; // m

  min_SegNo = 0;
  max_SegNo = 153;

  int dead_set_nos[33]={0,  1,  2,  3, 4, 5, 6,  9,  10, 11,
			12, 13, 18, 21,23,24,27, 32, 34, 40,
			44, 52, 68, 73,79,86,102,107,115,122,
			127,130,139
  };
  for (int i=0;i!=33;i++){
    dead_segs.insert(dead_set_nos[i]);
  }
  int veto_set_nos[48]={0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
			10, 11 ,12, 13, 25, 26, 27, 41, 55, 69,
			83, 97, 111,125,139,153,152,151,150,149,
			148,147,146,145,144,143,142,141,140,126,
			112,98, 84, 70, 56, 42, 28, 14};
  for (int i=0;i!=48;i++){
    veto_segs.insert(veto_set_nos[i]);
  }
}

bool Geometry::is_dead_seg(int segNo){
  if (dead_segs.find(segNo)==dead_segs.end()){
    return false;
  }else{
    return true;
  }
}

bool Geometry::is_veto_seg(int segNo){
  if (veto_segs.find(segNo)==veto_segs.end()){
    return false;
  }else{
    return true;
  }
}

int Geometry::SegRow(int segNo)
{
    return segNo/14;
}

int Geometry::SegCol(int segNo)
{
    return segNo - SegRow(segNo)*14;
}

float Geometry::SegX(int segNo)
{
    return (SegCol(segNo)-6.5) * WIDTH_X;
}

float Geometry::SegY(int segNo)
{
    return (SegRow(segNo)-5) * WIDTH_Y;
}

int Geometry::Seg_No(int nRow, int nCol){
  int SegNo = nCol + 14*nRow;
  if (SegNo >= min_SegNo && SegNo <=max_SegNo){
    return SegNo;
  }else{
    return -1;
  }
}

std::set<int> Geometry::AdjSegs(int segNo){
  int nRow = SegRow(segNo);
  int nCol = SegCol(segNo);

  std::set<int> seg_nos;
  int seg_no = Seg_No(nRow+1,nCol);
  if (seg_no!=-1){
    seg_nos.insert(seg_no);
  }
  seg_no = Seg_No(nRow-1,nCol);
  if (seg_no!=-1){
    seg_nos.insert(seg_no);
  }
  seg_no = Seg_No(nRow,nCol+1);
  if (seg_no!=-1){
    seg_nos.insert(seg_no);
  }
  seg_no = Seg_No(nRow,nCol-1);
  if (seg_no!=-1){
    seg_nos.insert(seg_no);
  }
  return seg_nos;
}
std::set<int> Geometry::CorSegs(int segNo){
  int nRow = SegRow(segNo);
  int nCol = SegCol(segNo);

  std::set<int> seg_nos;
  int seg_no = Seg_No(nRow+1,nCol+1);
  if (seg_no!=-1){
    seg_nos.insert(seg_no);
  }
  seg_no = Seg_No(nRow-1,nCol+1);
  if (seg_no!=-1){
    seg_nos.insert(seg_no);
  }
  seg_no = Seg_No(nRow+1,nCol-1);
  if (seg_no!=-1){
    seg_nos.insert(seg_no);
  }
  seg_no = Seg_No(nRow-1,nCol-1);
  if (seg_no!=-1){
    seg_nos.insert(seg_no);
  }
  return seg_nos;
}

std::set<int> Geometry::SurSegs(int segNo){
  std::set<int> seg_nos;
  std::set<int> seg_nos1 = AdjSegs(segNo);
  std::set<int> seg_nos2 = CorSegs(segNo);
  seg_nos.insert(seg_nos1.begin(), seg_nos1.end());
  seg_nos.insert(seg_nos2.begin(), seg_nos2.end());
}

int Geometry::RowColDiff(int segNo1, int segNo2){
  int nRow_1 = SegRow(segNo1);
  int nCol_1 = SegCol(segNo1);

  int nRow_2 = SegRow(segNo2);
  int nCol_2 = SegCol(segNo2);

  // 0 same ... 
  // 1 adj ...
  // 2 corner ...
  // -1 not connected ... 
  
  int result = 0;
  if (std::fabs(nRow_1-nRow_2)<=1){
    result += fabs(nRow_1-nRow_2);
  }else{
    result = -1;
    return result;
  }
  if (std::fabs(nCol_1-nCol_2)<=1){
    result += fabs(nCol_1-nCol_2);
  }else{
    result = -1;
    return result;
  }
  
  if (result >2) result = -1;

  

  
  return result;
}


Geometry::~Geometry()
{

}
