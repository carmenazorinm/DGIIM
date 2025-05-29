#pragma once
#include <mh.h>
#include "mhtrayectory.h"

class BLsmall : public MHTrayectory {
public:
  ResultMH optimize(Problem *problem, const int maxevals) override;
  ResultMH optimize(Problem *problem, const tSolution &current,
                    const tFitness fitness, const int maxevals) override;
};
