#pragma once
#include "mh.h"
#include "snimp_problem.h"
#include "blsmall.h"

class GRASP_SIBL : public MH {
public:
  ResultMH optimize(Problem *problem, int maxevals) override;

private:
  tSolution construirGreedyAleatorizado(Snimp *snimp);
};
