#pragma once
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "mhtrayectory.h"
#include "snimp_problem.h"

class ILS_ES : public MH {
public:
  ILS_ES() : MH() {}
  virtual ~ILS_ES() {}
  ResultMH optimize(Problem *problem, int maxevals) override;
};