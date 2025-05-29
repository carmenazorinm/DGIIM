#pragma once
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "mhtrayectory.h"
#include "snimp_problem.h"

class ES : public MH {
public:
  ES() : MH() {}
  virtual ~ES() {}
  ResultMH optimize(Problem *problem, int maxevals) override;
  ResultMH optimize(Problem *problem, const tSolution &current, const tFitness fitness, const int maxevals);
};