#include <sstream>

#include <theta_sketch.hpp>
#include <theta_union.hpp>
#include <theta_intersection.hpp>
#include <theta_a_not_b.hpp>

#include "ext.h"

using datasketches::theta_sketch;
using datasketches::update_theta_sketch;
using datasketches::compact_theta_sketch;
using datasketches::theta_union;
using datasketches::theta_intersection;
using datasketches::theta_a_not_b;

using datasketches::DEFAULT_SEED;

using Rice::Arg;

void init_theta(Rice::Module& m) {
  Rice::define_class_under<theta_sketch>(m, "ThetaSketch")
    .define_method(
      "empty?",
      [](theta_sketch& self) {
        return self.is_empty();
      })
    .define_method(
      "estimate",
      [](theta_sketch& self) {
        return self.get_estimate();
      })
    .define_method(
      "lower_bound",
      [](theta_sketch& self, uint8_t num_std_devs) {
        return self.get_lower_bound(num_std_devs);
      })
    .define_method(
      "upper_bound",
      [](theta_sketch& self, uint8_t num_std_devs) {
        return self.get_upper_bound(num_std_devs);
      });

  Rice::define_class_under<compact_theta_sketch, theta_sketch>(m, "CompactThetaSketch")
    .define_singleton_function(
      "deserialize",
      [](const std::string& is) {
        std::istringstream iss(is);
        return compact_theta_sketch::deserialize(iss);
      });

  Rice::define_class_under<update_theta_sketch, theta_sketch>(m, "UpdateThetaSketch")
    .define_singleton_function(
      "new",
      [](uint8_t lg_k, double p, uint64_t seed) {
        update_theta_sketch::builder builder;
        builder.set_lg_k(lg_k);
        builder.set_p(p);
        builder.set_seed(seed);
        return builder.build();
      },
      Arg("lg_k")=datasketches::theta_constants::DEFAULT_LG_K, Arg("p")=1.0, Arg("seed")=DEFAULT_SEED)
    .define_method("compact", &update_theta_sketch::compact, Arg("ordered")=true)
    .define_method(
      "update",
      [](update_theta_sketch& self, Rice::Object datum) {
        if (FIXNUM_P(datum.value())) {
          return self.update(Rice::detail::From_Ruby<int64_t>().convert(datum));
        } else if (datum.is_a(rb_cNumeric)) {
          return self.update(Rice::detail::From_Ruby<double>().convert(datum));
        } else {
          return self.update(datum.to_s().str());
        }
      })
    .define_method(
      "estimate",
      [](update_theta_sketch& self) {
        return self.get_estimate();
      });

  Rice::define_class_under<theta_union>(m, "ThetaUnion")
    .define_singleton_function(
      "new",
      [](uint8_t lg_k, double p, uint64_t seed) {
        theta_union::builder builder;
        builder.set_lg_k(lg_k);
        builder.set_p(p);
        builder.set_seed(seed);
        return builder.build();
      },
      Arg("lg_k")=datasketches::theta_constants::DEFAULT_LG_K, Arg("p")=1.0, Arg("seed")=DEFAULT_SEED)
    .define_method("update", &theta_union::update<const theta_sketch&>)
    .define_method("result", &theta_union::get_result, Arg("ordered")=true);

  Rice::define_class_under<theta_intersection>(m, "ThetaIntersection")
    .define_constructor(Rice::Constructor<theta_intersection, uint64_t>(), Arg("seed")=DEFAULT_SEED)
    .define_method("update", &theta_intersection::update<const theta_sketch&>)
    .define_method("result", &theta_intersection::get_result, Arg("ordered")=true)
    .define_method("result?", &theta_intersection::has_result);

  Rice::define_class_under<theta_a_not_b>(m, "ThetaANotB")
    .define_constructor(Rice::Constructor<theta_a_not_b, uint64_t>(), Arg("seed")=DEFAULT_SEED)
    .define_method("compute", &theta_a_not_b::compute<const theta_sketch&, const theta_sketch&>, Arg("a"), Arg("b"), Arg("ordered")=true);
}
