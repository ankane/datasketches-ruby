require_relative "test_helper"

class KllSketchTest < Minitest::Test
  def test_ints
    sketch = DataSketches::KllIntsSketch.new
    assert sketch.empty?
    sketch.update(1)
    sketch.update(2)
    sketch.update(3)

    assert_equal 1, sketch.min_value
    assert_equal 3, sketch.max_value
    assert_in_delta 2, sketch.quantile(0.5)
    assert_equal [1, 1, 2, 3, 3], sketch.quantiles([0, 0.25, 0.5, 0.75, 1])
    assert_equal [1, 2, 3], sketch.quantiles(3)
    assert_in_delta 0, sketch.rank(1)
    assert_in_delta 1, sketch.rank(4)
    # TODO better test
    assert sketch.pmf([1, 2, 3])
    assert sketch.cdf([1, 2, 3])

    data = sketch.serialize
    assert_equal 44, data.bytesize

    sketch = DataSketches::KllIntsSketch.deserialize(data)
    assert_equal 1, sketch.min_value
    assert_equal 3, sketch.max_value
    assert_in_delta 2, sketch.quantile(0.5)
  end

  def test_floats
    sketch = DataSketches::KllFloatsSketch.new
    assert sketch.empty?
    sketch.update(1)
    sketch.update(2)
    sketch.update(3)

    assert_in_delta 1, sketch.min_value
    assert_in_delta 3, sketch.max_value
    assert_in_delta 2, sketch.quantile(0.5)
    assert_equal [1, 1, 2, 3, 3], sketch.quantiles([0, 0.25, 0.5, 0.75, 1])

    data = sketch.serialize
    assert_equal 44, data.bytesize

    sketch = DataSketches::KllFloatsSketch.deserialize(data)
    assert_in_delta 1, sketch.min_value
    assert_in_delta 3, sketch.max_value
    assert_in_delta 2, sketch.quantile(0.5)
  end

  def test_merge
    sketch = DataSketches::KllIntsSketch.new
    sketch.update(1)

    other = DataSketches::KllIntsSketch.new
    other.update(2)

    sketch.merge(other)
    assert_equal 2, sketch.max_value
  end

  def test_empty
    sketch = DataSketches::KllIntsSketch.new

    error = assert_raises do
      sketch.quantile(0.5)
    end
    assert_equal "operation is undefined for an empty sketch", error.message

    error = assert_raises do
      sketch.quantiles([0, 0.25, 0.5, 0.75, 1])
    end
    assert_equal "operation is undefined for an empty sketch", error.message

    error = assert_raises do
      sketch.rank(1)
    end
    assert_equal "operation is undefined for an empty sketch", error.message
  end
end
