#include <sstream>

#include <kll_sketch.hpp>

#include "ext.h"

using datasketches::kll_sketch;

namespace Rice::detail
{
  template<typename T>
  class To_Ruby<std::vector<T>>
  {
  public:
    VALUE convert(std::vector<T> const & x)
    {
      auto a = rb_ary_new2(x.size());
      for (const auto& v : x) {
        detail::protect(rb_ary_push, a, To_Ruby<T>().convert(v));
      }
      return a;
    }
  };
}

template<typename T>
void bind_kll_sketch(Rice::Module& m, const char* name) {
  Rice::define_class_under<kll_sketch<T>>(m, name)
    .define_constructor(Rice::Constructor<kll_sketch<T>, uint16_t>(), Rice::Arg("k")=datasketches::kll_constants::DEFAULT_K)
    .define_method("empty?", &kll_sketch<T>::is_empty)
    .define_method("n", &kll_sketch<T>::get_n)
    .define_method("num_retained", &kll_sketch<T>::get_num_retained)
    .define_method("estimation_mode?", &kll_sketch<T>::is_estimation_mode)
    .define_method("min_value", &kll_sketch<T>::get_min_item)
    .define_method("max_value", &kll_sketch<T>::get_max_item)
    .define_method(
      "quantile",
      [](kll_sketch<T>& self, double rank, bool inclusive) {
        return self.get_quantile(rank, inclusive);
      }, Rice::Arg("rank"), Rice::Arg("inclusive")=false)
    .define_method(
      "quantiles",
      [](kll_sketch<T>& self, Rice::Object obj, bool inclusive) {
        if (obj.is_a(rb_cArray)) {
          auto ranks = Rice::detail::From_Ruby<std::vector<double>>().convert(obj);
          return self.get_quantiles(&ranks[0], ranks.size(), inclusive);
        } else {
          return self.get_quantiles(Rice::detail::From_Ruby<size_t>().convert(obj), inclusive);
        }
      }, Rice::Arg("obj"), Rice::Arg("inclusive")=false)
    .define_method(
      "rank",
      [](kll_sketch<T>& self, const T item, bool inclusive) {
        return self.get_rank(item, inclusive);
      }, Rice::Arg("item"), Rice::Arg("inclusive")=false)
    .define_method(
      "pmf",
      [](kll_sketch<T>& self, const std::vector<T>& split_points, bool inclusive) {
        return self.get_PMF(&split_points[0], split_points.size(), inclusive);
      }, Rice::Arg("split_points"), Rice::Arg("inclusive")=false)
    .define_method(
      "cdf",
      [](kll_sketch<T>& self, const std::vector<T>& split_points, bool inclusive) {
        return self.get_CDF(&split_points[0], split_points.size(), inclusive);
      }, Rice::Arg("split_points"), Rice::Arg("inclusive")=false)
    .define_method(
      "merge",
      [](kll_sketch<T>& self, const kll_sketch<T>& other) {
        self.merge(other);
      })
    .define_method(
      "update",
      [](kll_sketch<T>& self, const T item) {
        self.update(item);
      })
    .define_method(
      "serialize",
      [](kll_sketch<T>& self) {
        std::ostringstream oss;
        self.serialize(oss);
        return oss.str();
      })
    // TODO change to summary?
    .define_method(
      "to_string",
      [](kll_sketch<T>& self) {
        return self.to_string();
      })
    .define_singleton_function(
      "deserialize",
      [](const std::string& is) {
        std::istringstream iss(is);
        return kll_sketch<T>::deserialize(iss);
      });
}

void init_kll(Rice::Module& m) {
  bind_kll_sketch<int>(m, "KllIntsSketch");
  bind_kll_sketch<float>(m, "KllFloatsSketch");
}
