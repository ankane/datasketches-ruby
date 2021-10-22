# DataSketches Ruby

[DataSketches](https://datasketches.apache.org/) - sketch data structures - for Ruby

[![Build Status](https://github.com/ankane/datasketches-ruby/workflows/build/badge.svg?branch=master)](https://github.com/ankane/datasketches-ruby/actions)

## Installation

Add this line to your application’s Gemfile:

```ruby
gem 'datasketches'
```

## Sketch Families

Distinct counting

- [CPC sketch](#cpc-sketch)
- [HyperLogLog sketch](#hyperloglog-sketch)
- [Theta sketch](#theta-sketch)

Most frequent

- [Frequent item sketch](#frequent-item-sketch)

Quantiles and histograms

- [KLL sketch](#kll-sketch)

Sampling

- [VarOpt sketch](#varopt-sketch)

## CPC Sketch

Create a sketch

```ruby
sketch = DataSketches::CpcSketch.new
```

Add data

```ruby
sketch.update(1)
sketch.update(2.0)
sketch.update("three")
```

Estimate the count

```ruby
sketch.estimate
```

Save a sketch

```ruby
data = sketch.serialize
```

Load a sketch

```ruby
sketch = DataSketches::CpcSketch.deserialize(data)
```

Get the union

```ruby
u = DataSketches::CpcUnion.new(14)
u.update(sketch1)
u.update(sketch2)
u.result
```

## HyperLogLog Sketch

Create a sketch

```ruby
sketch = DataSketches::HllSketch.new(14)
```

Add data

```ruby
sketch.update(1)
sketch.update(2.0)
sketch.update("three")
```

Estimate the count

```ruby
sketch.estimate
```

Save a sketch

```ruby
data = sketch.serialize_updatable
# or
data = sketch.serialize_compact
```

Load a sketch

```ruby
sketch = DataSketches::HllSketch.deserialize(data)
```

Get the union

```ruby
u = DataSketches::HllUnion.new(14)
u.update(sketch1)
u.update(sketch2)
u.result
```

## Theta Sketch

Create a sketch

```ruby
sketch = DataSketches::UpdateThetaSketch.new
```

Add data

```ruby
sketch.update(1)
sketch.update(2.0)
sketch.update("three")
```

Estimate the count

```ruby
sketch.estimate
```

Save a sketch

```ruby
data = sketch.serialize
```

Load a sketch

```ruby
sketch = DataSketches::UpdateThetaSketch.deserialize(data)
```

Get the union

```ruby
u = DataSketches::ThetaUnion.new
u.update(sketch1)
u.update(sketch2)
u.result
```

Get the intersection

```ruby
i = DataSketches::ThetaIntersection.new
i.update(sketch1)
i.update(sketch2)
i.result
```

Compute A not B

```ruby
d = DataSketches::ThetaANotB.new
d.compute(a, b)
```

## Frequent Item Sketch

Create a sketch

```ruby
sketch = DataSketches::FrequentStringsSketch.new(64)
```

Add data

```ruby
sketch.update("a")
sketch.update("b")
sketch.update("c")
```

Estimate the frequency of an item

```ruby
sketch.estimate("a")
```

Save a sketch

```ruby
data = sketch.serialize
```

Load a sketch

```ruby
sketch = DataSketches::FrequentStringsSketch.deserialize(data)
```

## KLL Sketch

Create a sketch

```ruby
sketch = DataSketches::KllIntsSketch.new
# or
sketch = DataSketches::KllFloatsSketch.new
```

Add data

```ruby
sketch.update(1)
sketch.update(2)
sketch.update(3)
```

Get quantiles

```ruby
sketch.quantile(0.5)
sketch.quantiles([0.25, 0.5, 0.75])
sketch.quantiles(3)
```

Get the minimum and maximum values from the stream

```ruby
sketch.min_value
sketch.max_value
```

Save a sketch

```ruby
data = sketch.serialize
```

Load a sketch

```ruby
sketch = DataSketches::KllIntsSketch.deserialize(data)
```

Merge sketches

```ruby
sketch.merge(sketch2)
```

## VarOpt Sketch

Create a sketch

```ruby
sketch = DataSketches::VarOptSketch.new(14)
```

Add data

```ruby
sketch.update(1)
sketch.update(2.0)
sketch.update("three")
```

Sample data

```ruby
sketch.samples
```

## Credits

This library is modeled after the DataSketches [Python API](https://github.com/apache/datasketches-cpp/tree/master/python).

## History

View the [changelog](https://github.com/ankane/datasketches-ruby/blob/master/CHANGELOG.md)

## Contributing

Everyone is encouraged to help improve this project. Here are a few ways you can help:

- [Report bugs](https://github.com/ankane/datasketches-ruby/issues)
- Fix bugs and [submit pull requests](https://github.com/ankane/datasketches-ruby/pulls)
- Write, clarify, or fix documentation
- Suggest or add new features

To get started with development:

```sh
git clone --recursive https://github.com/ankane/datasketches-ruby.git
cd datasketches-ruby
bundle install
bundle exec rake compile
bundle exec rake test
```
