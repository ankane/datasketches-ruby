require_relative "test_helper"

class KllSketchTest < Minitest::Test
  def test_ints
    sketch = DataSketches::KllIntsSketch.new(200)
    assert sketch.empty?
    sketch.update(1)
    sketch.update(2)
    sketch.update(3)

    assert_equal 1, sketch.min_value
    assert_equal 3, sketch.max_value
    assert_in_delta 2, sketch.quantile(0.5)
    assert_equal [1, 1, 2, 3, 3], sketch.quantiles([0, 0.25, 0.5, 0.75, 1])

    data = sketch.serialize
    assert_equal 44, data.bytesize

    sketch = DataSketches::KllIntsSketch.deserialize(data)
    assert_equal 1, sketch.min_value
    assert_equal 3, sketch.max_value
    assert_in_delta 2, sketch.quantile(0.5)
  end

  def test_floats
    sketch = DataSketches::KllFloatsSketch.new(200)
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
end
