# DataSketches

[DataSketches](https://datasketches.apache.org/) - sketch data structures - for Ruby

[![Build Status](https://github.com/ankane/datasketches/workflows/build/badge.svg?branch=master)](https://github.com/ankane/datasketches/actions)

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
sketch = DataSketches::CpcSketch.new(14)
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
u.estimate
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
sketch = DataSketches::KllIntsSketch.new(200)
# or
sketch = DataSketches::KllFloatsSketch.new(200)
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

View the [changelog](https://github.com/ankane/datasketches/blob/master/CHANGELOG.md)

## Contributing

Everyone is encouraged to help improve this project. Here are a few ways you can help:

- [Report bugs](https://github.com/ankane/datasketches/issues)
- Fix bugs and [submit pull requests](https://github.com/ankane/datasketches/pulls)
- Write, clarify, or fix documentation
- Suggest or add new features

To get started with development:

```sh
git clone --recursive https://github.com/ankane/datasketches.git
cd datasketches
bundle install
bundle exec rake compile
bundle exec rake test
```
