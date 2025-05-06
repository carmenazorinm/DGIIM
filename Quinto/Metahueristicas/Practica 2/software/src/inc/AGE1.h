#pragma once
#include <heuristicmh.h>

class AGE_conorden : public MH {
public:
  AGE_conorden() : MH() {}
  virtual ~AGE_conorden() {}
  ResultMH optimize(Problem *problem, int maxevals) override;
};