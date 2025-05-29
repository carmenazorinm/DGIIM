#pragma once
#include "mh.h"
#include "snimp_problem.h"

class GRASP_NOBL: public MH {
public:
  ResultMH optimize(Problem *problem, int maxevals) override;

private:
  tSolution construirGreedyAleatorizado(Snimp *snimp);
};
