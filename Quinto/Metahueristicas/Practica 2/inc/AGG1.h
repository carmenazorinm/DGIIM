#pragma once
#include <heuristicmh.h>

class AGG_sinorden : public MH {
public:
  AGG_sinorden() : MH() {}
  virtual ~AGG_sinorden() {}
  ResultMH optimize(Problem *problem, int maxevals) override;
};