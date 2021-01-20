#include <sstream>

#include <var_opt_sketch.hpp>

#include <rice/Constructor.hpp>
#include <rice/Module.hpp>

template<typename T>
void bind_vo_sketch(Rice::Module &m, const char* name) {
  Rice::define_class_under<datasketches::var_opt_sketch<T>>(m, "VarOptSketch")
    .define_constructor(Rice::Constructor<datasketches::var_opt_sketch<T>, uint32_t>())
    .define_method("k", &datasketches::var_opt_sketch<T>::get_k)
    .define_method("n", &datasketches::var_opt_sketch<T>::get_n)
    .define_method(
      "update",
      *[](datasketches::var_opt_sketch<T>& self, const T item) {
        self.update(item);
      });
}

void init_vo(Rice::Module& m) {
  bind_vo_sketch<Rice::Object>(m, "VarOptSketch");
}
