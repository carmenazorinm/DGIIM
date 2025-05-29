#pragma once
#include <heuristicmh.h>

class AM1 : public MH {
public:
  AM1() : MH() {}
  virtual ~AM1() {}
  ResultMH optimize(Problem *problem, int maxevals) override;
};