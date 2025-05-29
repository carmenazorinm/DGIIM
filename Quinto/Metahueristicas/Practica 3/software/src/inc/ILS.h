#pragma once
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "mhtrayectory.h"
#include "snimp_problem.h"

class ILS : public MH {
public:
  ILS() : MH() {}
  virtual ~ILS() {}
  ResultMH optimize(Problem *problem, int maxevals) override;
};