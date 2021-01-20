#include <sstream>

#include <hll.hpp>

#include <rice/Constructor.hpp>
#include <rice/Module.hpp>

void init_hll(Rice::Module& m) {
  Rice::define_class_under<datasketches::hll_sketch>(m, "HllSketch")
    .define_constructor(Rice::Constructor<datasketches::hll_sketch, int>())
    .define_method("lg_config_k", &datasketches::hll_sketch::get_lg_config_k)
    .define_method("compact?", &datasketches::hll_sketch::is_compact)
    .define_method("empty?", &datasketches::hll_sketch::is_empty)
    .define_method(
      "update",
      *[](datasketches::hll_sketch& self, Rice::Object datum) {
        if (FIXNUM_P(datum.value())) {
          return self.update(from_ruby<int64_t>(datum));
        } else if (datum.is_a(rb_cNumeric)) {
          return self.update(from_ruby<double>(datum));
        } else {
          return self.update(datum.to_s().str());
        }
      })
    .define_method(
      "estimate",
      *[](datasketches::hll_sketch& self) {
        return self.get_estimate();
      })
    .define_method(
      "serialize_compact",
      *[](datasketches::hll_sketch& self) {
        std::ostringstream oss;
        self.serialize_compact(oss);
        return oss.str();
      })
    .define_method(
      "serialize_updatable",
      *[](datasketches::hll_sketch& self) {
        std::ostringstream oss;
        self.serialize_updatable(oss);
        return oss.str();
      })
    // TODO change to summary?
    .define_method(
      "to_string",
      *[](datasketches::hll_sketch& self) {
        return self.to_string();
      })
    .define_singleton_method(
      "deserialize",
      *[](std::string& is) {
        std::istringstream iss(is);
        return datasketches::hll_sketch::deserialize(iss);
      });

  Rice::define_class_under<datasketches::hll_union>(m, "HllUnion")
    .define_constructor(Rice::Constructor<datasketches::hll_union, int>())
    .define_method(
      "update",
      *[](datasketches::hll_union& self, datasketches::hll_sketch& datum) {
        self.update(datum);
      })
    .define_method(
      "estimate",
      *[](datasketches::hll_union& self) {
        return self.get_estimate();
      });
}
