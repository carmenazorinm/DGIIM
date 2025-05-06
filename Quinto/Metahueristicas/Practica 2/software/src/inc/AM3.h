#pragma once
#include <heuristicmh.h>

class AM3 : public MH {
public:
  AM3() : MH() {}
  virtual ~AM3() {}
  ResultMH optimize(Problem *problem, int maxevals) override;
};