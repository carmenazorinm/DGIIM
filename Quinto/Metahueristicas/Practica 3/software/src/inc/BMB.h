#pragma once
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "mhtrayectory.h"
#include "snimp_problem.h"

class BMB : public MH {
public:
  BMB() : MH() {}
  virtual ~BMB() {}
  ResultMH optimize(Problem *problem, int maxevals) override;
};