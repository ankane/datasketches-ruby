#include <sstream>

#include <var_opt_sketch.hpp>

#include <rice/Array.hpp>
#include <rice/Constructor.hpp>
#include <rice/Module.hpp>

template<typename T>
void bind_vo_sketch(Rice::Module &m, const char* name) {
  Rice::define_class_under<datasketches::var_opt_sketch<T>>(m, "VarOptSketch")
    .define_constructor(Rice::Constructor<datasketches::var_opt_sketch<T>, uint32_t>())
    .define_method("k", &datasketches::var_opt_sketch<T>::get_k)
    .define_method("n", &datasketches::var_opt_sketch<T>::get_n)
    .define_method("num_samples", &datasketches::var_opt_sketch<T>::get_num_samples)
    .define_method("empty?", &datasketches::var_opt_sketch<T>::is_empty)
    .define_method("reset", &datasketches::var_opt_sketch<T>::reset)
    .define_method(
      "samples",
      *[](datasketches::var_opt_sketch<T>& self) {
        auto a = Rice::Array();
        for (auto item : self) {
          auto t = Rice::Array();
          t.push(item.first);
          t.push(item.second);
          a.push(t);
        }
        return a;
      })
    .define_method(
      "update",
      *[](datasketches::var_opt_sketch<T>& self, const T item) {
        self.update(item);
      });
}

void init_vo(Rice::Module& m) {
  bind_vo_sketch<Rice::Object>(m, "VarOptSketch");
}
