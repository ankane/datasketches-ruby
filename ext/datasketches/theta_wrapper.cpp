#include <sstream>

#include <theta_sketch.hpp>

#include <rice/Constructor.hpp>
#include <rice/Module.hpp>

void init_theta(Rice::Module& m) {
  Rice::define_class_under<datasketches::theta_sketch>(m, "ThetaSketch")
    .define_method("empty?", &datasketches::theta_sketch::is_empty)
    .define_method("estimate", &datasketches::theta_sketch::get_estimate);

  Rice::define_class_under<datasketches::update_theta_sketch, datasketches::theta_sketch>(m, "UpdateThetaSketch")
    .define_singleton_method(
      "new",
      *[]() {
        datasketches::update_theta_sketch::builder builder;
        return builder.build();
      });

  Rice::define_class_under<datasketches::compact_theta_sketch, datasketches::theta_sketch>(m, "CompactThetaSketch");
}
