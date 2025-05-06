#pragma once
#include <heuristicmh.h>

class AGE_sinorden : public MH {
public:
  AGE_sinorden() : MH() {}
  virtual ~AGE_sinorden() {}
  ResultMH optimize(Problem *problem, int maxevals) override;
};