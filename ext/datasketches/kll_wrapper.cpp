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
      })
    .define_method(
      "serialize",
      *[](datasketches::kll_sketch<T>& self) {
        std::ostringstream oss;
        self.serialize(oss);
        return oss.str();
      })
    // TODO change to summary?
    .define_method(
      "to_string",
      *[](datasketches::kll_sketch<T>& self) {
        return self.to_string();
      })
    .define_singleton_method(
      "deserialize",
      *[](std::string& is) {
        std::istringstream iss(is);
        return datasketches::kll_sketch<T>::deserialize(iss);
      });
}

void init_kll(Rice::Module& m) {
  bind_kll_sketch<int>(m, "KllIntsSketch");
  bind_kll_sketch<float>(m, "KllFloatsSketch");
}
