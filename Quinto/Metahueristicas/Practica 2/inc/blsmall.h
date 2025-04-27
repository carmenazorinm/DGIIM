#include <mh.h>

class BLsmall : public MH {
public:
  ResultMH optimize(Problem *problem, const int maxevals) override;
};
