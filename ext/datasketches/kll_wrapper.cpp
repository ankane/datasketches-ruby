#include <sstream>

#include <kll_sketch.hpp>

#include <rice/Constructor.hpp>
#include <rice/Module.hpp>

template<typename T>
void bind_kll_sketch(Rice::Module& m, const char* name) {
  Rice::define_class_under<datasketches::kll_sketch<T>>(m, name)
    .define_constructor(Rice::Constructor<datasketches::kll_sketch<T>, uint16_t>())
    .define_method("empty?", &datasketches::kll_sketch<T>::is_empty);
}

void init_kll(Rice::Module& m) {
  bind_kll_sketch<int>(m, "KllIntsSketch");
  bind_kll_sketch<float>(m, "KllFloatsSketch");
}
