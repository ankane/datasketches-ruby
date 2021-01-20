#include <rice/Module.hpp>

void init_cpc(Rice::Module& m);
void init_hll(Rice::Module& m);
void init_kll(Rice::Module& m);

extern "C"
void Init_ext()
{
  Rice::Module m = Rice::define_module("DataSketches");
  init_cpc(m);
  init_hll(m);
  init_kll(m);
}
