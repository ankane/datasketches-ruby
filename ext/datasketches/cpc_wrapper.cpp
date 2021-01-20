#include <sstream>

#include <cpc_sketch.hpp>

#include <rice/Constructor.hpp>
#include <rice/Module.hpp>

void init_cpc(Rice::Module& m) {
  Rice::define_class_under<datasketches::cpc_sketch>(m, "CpcSketch")
    .define_constructor(Rice::Constructor<datasketches::cpc_sketch, uint8_t>())
    .define_method("lg_k", &datasketches::cpc_sketch::get_lg_k)
    .define_method("empty?", &datasketches::cpc_sketch::is_empty)
    .define_method("lower_bound", &datasketches::cpc_sketch::get_lower_bound)
    .define_method("upper_bound", &datasketches::cpc_sketch::get_upper_bound)
    .define_method(
      "update",
      *[](datasketches::cpc_sketch& self, Rice::Object datum) {
        if (datum.is_a(rb_cInteger)) {
          return self.update(from_ruby<int64_t>(datum));
        } else if (datum.is_a(rb_cNumeric)) {
          return self.update(from_ruby<double>(datum));
        } else {
          return self.update(datum.to_s().str());
        }
      })
    .define_method(
      "estimate",
      *[](datasketches::cpc_sketch& self) {
        return self.get_estimate();
      })
    .define_method(
      "serialize",
      *[](datasketches::cpc_sketch& self) {
        std::ostringstream oss;
        self.serialize(oss);
        return oss.str();
      })
    // TODO change to summary?
    .define_method(
      "to_string",
      *[](datasketches::cpc_sketch& self) {
        return self.to_string();
      })
    .define_singleton_method(
      "deserialize",
      *[](std::string& is) {
        std::istringstream iss(is);
        return datasketches::cpc_sketch::deserialize(iss);
      });
}
