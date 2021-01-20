#include <sstream>

#include <kll_sketch.hpp>

#include <rice/Constructor.hpp>
#include <rice/Module.hpp>

template<typename T>
void bind_kll_sketch(Rice::Module& m, const char* name) {
  Rice::define_class_under<datasketches::kll_sketch<T>>(m, name)
    .define_constructor(Rice::Constructor<datasketches::kll_sketch<T>, uint16_t>())
    .define_method("empty?", &datasketches::kll_sketch<T>::is_empty)
    .define_method("min_value", &datasketches::kll_sketch<T>::get_min_value)
    .define_method("max_value", &datasketches::kll_sketch<T>::get_max_value)
    .define_method("quantile", &datasketches::kll_sketch<T>::get_quantile)
    .define_method(
      "update",
      *[](datasketches::kll_sketch<T>& self, const T item) {
        self.update(item);
      });
}

void init_kll(Rice::Module& m) {
  bind_kll_sketch<int>(m, "KllIntsSketch");
  bind_kll_sketch<float>(m, "KllFloatsSketch");
}
