#pragma once
#include <heuristicmh.h>

class AM2 : public MH {
public:
  AM2() : MH() {}
  virtual ~AM2() {}
  ResultMH optimize(Problem *problem, int maxevals) override;
};