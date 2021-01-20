#include <sstream>

#include <theta_sketch.hpp>

#include <rice/Constructor.hpp>
#include <rice/Module.hpp>

void init_theta(Rice::Module& m) {
  Rice::define_class_under<datasketches::theta_sketch>(m, "ThetaSketch")
    .define_method("empty?", &datasketches::theta_sketch::is_empty)
    .define_method("estimate", &datasketches::theta_sketch::get_estimate)
    .define_method("lower_bound", &datasketches::theta_sketch::get_lower_bound)
    .define_method("upper_bound", &datasketches::theta_sketch::get_upper_bound)
    .define_method(
      "serialize",
      *[](datasketches::theta_sketch& self) {
        std::ostringstream oss;
        self.serialize(oss);
        return oss.str();
      });

  Rice::define_class_under<datasketches::update_theta_sketch, datasketches::theta_sketch>(m, "UpdateThetaSketch")
    .define_method("compact", &datasketches::theta_sketch::get_estimate)
    .define_singleton_method(
      "new",
      *[]() {
        datasketches::update_theta_sketch::builder builder;
        return builder.build();
      })
    .define_method(
      "update",
      *[](datasketches::update_theta_sketch& self, Rice::Object datum) {
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
      *[](datasketches::update_theta_sketch& self) {
        return self.get_estimate();
      })
    .define_singleton_method(
      "deserialize",
      *[](std::string& is) {
        std::istringstream iss(is);
        return datasketches::update_theta_sketch::deserialize(iss);
      });

  Rice::define_class_under<datasketches::compact_theta_sketch, datasketches::theta_sketch>(m, "CompactThetaSketch")
    .define_singleton_method(
      "deserialize",
      *[](std::string& is) {
        std::istringstream iss(is);
        return datasketches::compact_theta_sketch::deserialize(iss);
      });
}
