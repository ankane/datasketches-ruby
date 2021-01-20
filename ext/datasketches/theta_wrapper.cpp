#include <sstream>

#include <theta_sketch.hpp>

#include <rice/Constructor.hpp>
#include <rice/Module.hpp>

void init_theta(Rice::Module& m) {
  Rice::define_class_under<datasketches::theta_sketch>(m, "ThetaSketch")
    .define_method("empty?", &datasketches::theta_sketch::is_empty)
    .define_method("estimate", &datasketches::theta_sketch::get_estimate);
}
