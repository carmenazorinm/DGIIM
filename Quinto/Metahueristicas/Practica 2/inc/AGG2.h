#pragma once
#include <heuristicmh.h>

class AGG_conorden : public MH {
public:
  AGG_conorden() : MH() {}
  virtual ~AGG_conorden() {}
  ResultMH optimize(Problem *problem, int maxevals) override;
};