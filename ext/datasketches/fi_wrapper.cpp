#include <sstream>

#include <frequent_items_sketch.hpp>

#include <rice/Constructor.hpp>
#include <rice/Module.hpp>

template<typename T>
void bind_fi_sketch(Rice::Module& m, const char* name) {
  Rice::define_class_under<datasketches::frequent_items_sketch<T>>(m, name)
    .define_constructor(Rice::Constructor<datasketches::frequent_items_sketch<T>, uint16_t>())
    .define_method("empty?", &datasketches::frequent_items_sketch<T>::is_empty);
}

void init_fi(Rice::Module& m) {
  bind_fi_sketch<std::string>(m, "FrequentStringsSketch");
}
