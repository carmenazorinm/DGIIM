#include <mh.h>

class LSall : public MH {
public:
  ResultMH optimize(Problem *problem, const int maxevals) override;
};
