#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <set>

namespace Prospect {
  class Geometry {
  public:
    Geometry();
    virtual ~Geometry();
    
    int SegRow(int segNo);
    int SegCol(int segNo);
    float SegX(int segNo);
    float SegY(int segNo);
    int Seg_No(int nRow, int nCol);

    int RowColDiff(int segNo1, int segNo2);
    
    std::set<int> AdjSegs(int segNo);
    std::set<int> CorSegs(int segNo);
    std::set<int> SurSegs(int segNo);
    
    float WIDTH_X; // m
    float WIDTH_Y; // m
    float WIDTH_Z; // m

    int min_SegNo;
    int max_SegNo;
    
  };
}

#endif
