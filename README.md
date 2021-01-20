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

Most frequent

- [Frequent item sketch](#frequent-item-sketch)

Quantiles and histograms

- [KLL sketch](#kll-sketch)

Sampling

- [VarOpt sketch](#varopt-sketch)

### CPC Sketch

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

### HyperLogLog Sketch

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

## Frequent Item Sketch

Create a sketch

```ruby
sketch = DataSketches::FrequentStringsSketch.new(14)
```

## KLL Sketch

Create a sketch

```ruby
sketch = DataSketches::KllIntsSketch.new(14)
# or
sketch = DataSketches::KllFloatsSketch.new(14)
```

## VarOpt Sketch

Create a sketch

```ruby
sketch = DataSketches::VarOptSketch.new(14)
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
