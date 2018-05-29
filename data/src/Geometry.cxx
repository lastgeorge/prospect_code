#include "ProspectData/Geometry.h"

#include <cmath>

using namespace Prospect;

Geometry::Geometry()
{
    WIDTH_X = 0.1461; // m
    WIDTH_Y = 0.1461; // m
    WIDTH_Z = 1.175; // m

    min_SegNo = 0;
    max_SegNo = 153;
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
  seg_no = Seg_No(nRow-1,nCol+1);
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

  int result = -1;
  if (std::fabs(nRow_1-nRow_2)<=1)
    result += fabs(nRow_1-nRow_2);
  if (std::fabs(nCol_1-nCol_2)<=1)
    result += fabs(nCol_1-nCol_2);
  return result;
}


Geometry::~Geometry()
{

}
